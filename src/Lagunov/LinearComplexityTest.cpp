#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <ctime>
#include "Cephes.h"

#define _USE_MATH_DEFINES

using namespace std;

vector<int8_t> read_file(const std::string filename) {
    ifstream f(filename, ios::binary | ios::in);
    vector<int8_t> buffer;
    char c;
    while ( f.get(c) ) 
    {
        for ( int i = 7; i >= 0; --i ) 
            buffer.push_back(((c >> i) & 1));
    }
    f.close();
    return buffer;
}

double mean(int M) {
    return (M / 2) + ((9 + pow(-1, M+1)) / 36) - ((M/3 + 2/9) / pow(2, M));
}

vector<double> calculate_T(int M, vector<int> L) {
    vector<double> T;
    double mu = mean(M);
    for (int i = 0; i < L.size(); i++) {
        T.push_back(pow(-1, M)*(L[i] - mu) + (2/9));
    }
    return T;
}

vector<int> calculate_nu(int M, vector<int> L) {
    vector<int> nu;
    nu.resize(7);
    vector<double> T;
    T = calculate_T(M, L);
    for (int i = 0; i < T.size(); i++) {
        if (T[i] <= -2.5)
            nu[0] += 1;
        if ((T[i] > -2.5) && (T[i] <= -1.5))
            nu[1] += 1;
        if ((T[i] > -1.5) && (T[i] <= -0.5))
            nu[2] += 1;
        if ((T[i] > -0.5) && (T[i] <= 0.5))
            nu[3] += 1;
        if ((T[i] > 0.5) && (T[i] <= 1.5))
            nu[4] += 1;
        if ((T[i] > 1.5) && (T[i] <= 2.5))
            nu[5] += 1;
        if (T[i] > 2.5)
            nu[6] += 1;
    }
    cout << "nu vector: " << endl;
    for (int i = 0; i < 7; i++)
        cout << nu[i] << " ";
    cout << endl;
    return nu;
}

double hi_square(int M, int N, vector<int> L) {
    vector<double> pi;
    pi.push_back(0.010417);
    pi.push_back(0.03125);
    pi.push_back(0.125);
    pi.push_back(0.5);
    pi.push_back(0.25);
    pi.push_back(0.0625);
    pi.push_back(0.020833);
    vector<int> nu;
    nu = calculate_nu(M, L);
    double hi_square = 0;
    for (int i = 0; i < 7; i++)
        hi_square += (pow(nu[i] - N*pi[i], 2) / (N*pi[i]));
    cout << "hi_square = " << hi_square << endl;
    return hi_square;
}

double igamc(int N, int M, vector<int> L) {
    double hi = hi_square(M, N, L);
    cout << hi << endl;
    double gamma = Cephes::cephes_igamc(7 / 2, hi / 2);
    return gamma;
}

// double igamc(int N, int M, vector<int> L) {
//     double hi = hi_square(M, N, L);
//     cout << hi << endl;
//     double x = hi / 2;
//     double half_gamma = (sqrt(M_PI)/2)*erfc(sqrt(x)) + pow(x, 1/2)*exp(-x);
//     double x1 = pow(x, 3/2)*exp(-x);
//     double x2 = pow(x, 5/2)*exp(-x);
//     return (5/2)*((3/2)*(half_gamma) + x1) + x2;
// }

int berlekamp_massey(vector<int8_t>& s, int n) {
    int L, N, m, d;
    vector<int8_t> c;
    vector<int8_t> b;
    vector<int8_t> t;

    c.resize(n);
    b.resize(n);
    t.resize(n);
    b[0] = 1;
    c[0] = 1;
    N = 0;
    L = 0;
    m = -1;
                
    while (N < n) {
        d = s[N];
        for (int i = 1; i <= L; i++) 
            d ^= (c[i] & s[N-i]);
        if (d == 1) {
            t = { c };
            for (int i = 0; (i + N - m) < n; i++)
                c[i + N - m] ^= b[i];
            if (2*L <= N) {
                L = (N + 1 - L);
                m = N;
                b = { t };
            }
        }
        N++;
    }
    return L;
}

int main() {
    vector<int8_t> sequence1;
    vector<int8_t> sequence2;
    vector<int8_t> sequence3;
    vector<int8_t> sequence4;
    vector<int8_t> sequence5;
    vector<int8_t> sequence6;
    vector<int8_t> sequence7;
    vector<int8_t> sequence8;
    sequence1 = read_file("seq1.bin");
    sequence2 = read_file("seq2.bin");
    sequence3 = read_file("seq3.bin");
    sequence4 = read_file("seq4.bin");
    sequence5 = read_file("seq5.bin");
    sequence6 = read_file("seq6.bin");
    sequence7 = read_file("seq7.bin");
    sequence8 = read_file("seq8.bin");

    cout << sequence1.size() << endl;
    cout << sequence2.size() << endl;
    cout << sequence3.size() << endl;
    cout << sequence4.size() << endl;
    cout << sequence5.size() << endl;
    cout << sequence6.size() << endl;
    cout << sequence7.size() << endl;
    cout << sequence8.size() << endl;

    vector<int8_t> v = {1, 1, 0, 0, 1, 0, 1, 1, 1, 0};
    vector<int8_t> v2 = {1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1};
    cout << berlekamp_massey(v2, v2.size()) << endl;
    
    int N = 160000;

    clock_t tStart = clock();
    vector<int> l;
    int M = sequence1.size() / N;
    for (int i = 0; i < N; i++) {
        vector<int8_t> block;
        for (int j = 0; j < M; j++) {
            block.push_back(sequence1[M*i + j]);
        }
        l.push_back(berlekamp_massey(block, block.size()));
        block.clear();
    }
    cout << igamc(N, M, l) << endl; 
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    N = 160000;
    l.clear();
    tStart = clock();
    M = sequence2.size() / N;
    for (int i = 0; i < N; i++) {
        vector<int8_t> block;
        for (int j = 0; j < M; j++) {
            block.push_back(sequence2[M*i + j]);
        }
        l.push_back(berlekamp_massey(block, block.size()));
        block.clear();
    }
    cout << igamc(N, M, l) << endl; 
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    N = 167936;
    l.clear();
    tStart = clock();
    M = sequence3.size() / N;
    for (int i = 0; i < N; i++) {
        vector<int8_t> block;
        for (int j = 0; j < M; j++) {
            block.push_back(sequence3[M*i + j]);
        }
        l.push_back(berlekamp_massey(block, block.size()));
        block.clear();
    }
    cout << igamc(N, M, l) << endl; 
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC); 

    N = 160000;
    l.clear();
    tStart = clock();
    M = sequence4.size() / N;
    for (int i = 0; i < N; i++) {
        vector<int8_t> block;
        for (int j = 0; j < M; j++) {
            block.push_back(sequence4[M*i + j]);
        }
        l.push_back(berlekamp_massey(block, block.size()));
        block.clear();
    }
    cout << igamc(N, M, l) << endl;
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC); 

    N = 160000;
    l.clear();
    tStart = clock();
    M = sequence5.size() / N;
    for (int i = 0; i < N; i++) {
        vector<int8_t> block;
        for (int j = 0; j < M; j++) {
            block.push_back(sequence5[M*i + j]);
        }
        l.push_back(berlekamp_massey(block, block.size()));
        block.clear();
    }
    cout << igamc(N, M, l) << endl; 
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    N = 16776;
    l.clear();
    tStart = clock();
    M = sequence6.size() / N;
    for (int i = 0; i < N; i++) {
        vector<int8_t> block;
        for (int j = 0; j < M; j++) {
            block.push_back(sequence6[M*i + j]);
        }
        l.push_back(berlekamp_massey(block, block.size()));
        block.clear();
    }
    cout << igamc(N, M, l) << endl; 
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    N = 4000;
    l.clear();
    tStart = clock();
    M = sequence7.size() / N;
    for (int i = 0; i < N; i++) {
        vector<int8_t> block;
        for (int j = 0; j < M; j++) {
            block.push_back(sequence7[M*i + j]);
        }
        l.push_back(berlekamp_massey(block, block.size()));
        block.clear();
    }
    cout << igamc(N, M, l) << endl; 
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    N = 160000;
    l.clear();
    tStart = clock();
    M = sequence8.size() / N;
    for (int i = 0; i < N; i++) {
        vector<int8_t> block;
        for (int j = 0; j < M; j++) {
            block.push_back(sequence8[M*i + j]);
        }
        l.push_back(berlekamp_massey(block, block.size()));
        block.clear();
    }
    cout << igamc(N, M, l) << endl; 
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    return 0;
}