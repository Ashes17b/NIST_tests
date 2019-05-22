#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>

using namespace std;

typedef unsigned char byte;

const char* input = "input.in";
const char* output = "output.out";

struct bytes {
    byte* seq;
    int  len;
    bytes(byte* seq, int len) {
        this->seq = seq;
        this->len = len;
    }
    ~bytes() {
        delete seq;
    }
};

double lfsr_test(byte* seq, int len);
double igamc2(unsigned int s2, double x);
bytes* read_file(char const *filename);
void write_file(const char* filename, double pvalue);

int main() {
    bytes* bytes = read_file(input);
    double pvalue = lfsr_test(bytes->seq, bytes->len);
    write_file(output, pvalue);
    delete bytes;
}

bytes* read_file(char const *filename) {
    ifstream ifs(filename, ios::binary|ios::ate);
    ifstream::pos_type pos = ifs.tellg();
    char* buffer =  new char[pos];
    ifs.seekg(0, ios::beg);
    ifs.read(buffer, pos);
    return new bytes((byte*)buffer, pos);
}

void write_file(const char* filename, double pvalue) {
    FILE *out = fopen(filename, "wt");
    fprintf(out, "%.5f", pvalue);
    fclose(out);
}


const double PI  =3.141592653589793238463;

#define M 50
#define K 6

int linear_complexity(byte* seq, int offset, int len);
double theoretical_mean(int m);
int neg_one_pow(int n);
double igamc(unsigned int s, double x);
double igamc2(unsigned int s2, double x);
int get_v_index(double t);

double lfsr_test(byte* seq, int len) {
    int n = 8 * len;
    cout << endl;
    int N = n/M;
    int v[7] = {0, 0, 0, 0, 0, 0, 0};
    double pi[7] = {0.010417, 0.03125, 0.125, 0.5, 0.25, 0.0625, 0.020833};
    double mu = theoretical_mean(M);

    int byte_add = M/8;
    int bit_add  = M%8;
    int offset = 0;
    for (int i=0; i<N; i++) {
        int l = (double) linear_complexity(seq, offset, M);
        double t = neg_one_pow(M)*(l-mu) + 2.0/9.0;
        v[get_v_index(t)]++;

        seq += byte_add;
        offset + bit_add;
        if (offset >= 8) {
            seq++;
            offset -= 8;
        }
    };
    double chi2 = 0;
    for(int i=0; i<=K; i++) {
        double den = N * pi[i];
        double num = v[i] - den;
        chi2 += num * num / den;
    }
    return igamc2(K, chi2/2.0);
}

int get_v_index(double t) {
    if (t <= -2.5) {
        return 0;
    } else if (t <= -1.5) {
        return 1;
    } else if (t <= -0.5) {
        return 2;
    } else if (t <= 0.5) {
        return 3;
    } else if (t <= 1.5) {
        return 4;
    } else if (t <= 2.5) {
        return 5;
    } else {
        return 6;
    }
}

double theoretical_mean(int m) {
    return m/2.0 + (9.0 + neg_one_pow(m+1))/36.0 - (m/3.0 + 2.0/9.0)/pow(2.0L, (long double)m);
}

int neg_one_pow(int n) {
    return n%2 == 0 ? 1 : -1;
}

template <typename T> void arraycopy(T* src, T* dest, int len) {
    for(int i=0; i<len; i++) {
        dest[i] = src[i];
    }
}

template <typename number> number* zero_arr(int size) {
    number* arr = new number[size];
    for(int i=0; i<size; i++) {
        arr[i] = 0;
    }
    return arr;
}

int linear_complexity(byte* seq, int offset, int N) {
    //int max_shift_size = (N+7)/8;
    bool* b = zero_arr<bool>(N);
    bool* c = zero_arr<bool>(N);
    bool* t = zero_arr<bool>(N);
    bool* t2;
    b[0] = true; // 1000 0000
    c[0] = true; // 1000 0000
    int l = 0;
    int m = -1;
    for (int n = offset; n < offset + N; n++) {
        // calculate discrepancy
        bool d = 0;
        int seq_bit_idx = n%8;
        int seq_byte_idx = n/8;
        byte seq_byte = (seq[seq_byte_idx] >> (7 - seq_bit_idx));
        for (int i = 0; i <= l; i++) {
            d ^= c[i] & (seq_byte & 1);
            seq_bit_idx--;
            if (seq_bit_idx >= 0) {
                seq_byte >>= 1;
            } else {
                seq_byte_idx--;
                seq_bit_idx = 7;
                seq_byte = seq[seq_byte_idx];
            }
        }
        // actions according to results
        if (d == 1) {
            if (l <= n / 2) {
                arraycopy(c, t, l+1);
                int shift = n - m;
                int b_size = m == -1 ? 1 : m + 1;
                for (int tj = shift, bj = 0; bj < b_size; bj++, tj++) {
                    t[tj] ^= b[bj];
                }
                t2 = b;
                b = c;
                c = t;
                t = t2;
                l = n + 1 - l;
                m = n;
            } else {
                int shift = n - m;
                int b_size = m == -1 ? 1 : m + 1;
                for (int cj = shift, bj = 0; bj < b_size; bj++, cj++) {
                    c[cj] ^= b[bj];
                }
            }
        }
    }
    delete b;
    delete c;
    delete t;
    return l;
}

double igamc(unsigned int s, double x) {
    double sum = 1;
    double element = 1;
    for(int k=1; k<s; k++) {
        element *= x;
        element /= k;
        sum += element;
    }
    return exp(-x) * sum;
}

double gamma(unsigned int s2) {
    double g = 1;
    double s = s2 / 2.0;
    while (s > 1) {
        s -= 1;
        g *= s;
    }
    if (s2 %2 == 0) {
        return g;
    } else {
        return sqrt(PI) * g;
    }
}

double igamc2(unsigned int s2, double x) {
    if(s2 % 2 == 0) {
        return igamc(s2/2, x);
    } else {
        // G(s, x) = (s-1) * G(s-1, x) + x^(s-1)*exp(-x)
        // G(1, x) = exp(-x)
        // G(1/2, x) = sqrt(PI) * erfc(sqrt(x))
        double c = sqrt(x) * exp(-x);
        double m = 0.5;
        double g = sqrt(PI)*erfc(sqrt(x));
        for(int i=3; i<=s2; i+=2) {
            g = m * g + c;
            m += 1;
            c *= x;
        }
        return g / gamma(s2);
    }
}