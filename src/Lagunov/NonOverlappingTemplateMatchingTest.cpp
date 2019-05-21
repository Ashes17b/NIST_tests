#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <ctime>
#include <list>
#include "Cephes.h"

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

int calculate_W(const vector<int8_t>& seq, int s, int e, const vector<int8_t>& temp, int M) {
    long int t = 0;
    int W = 0;
    for (int i = 0; i < temp.size(); i++)
        t += pow(2, i)*temp[i];
    for (int i = s; i < e; i++) {
        long int ksi = 0;
        for (int j = 0; j < temp.size(); j++)
            ksi += pow(2, j)*seq[i+j];
        if (ksi == t)
            W++;
    }
    return W;
}

int calculate_w(const vector<int8_t>& seq, int s, int e, const vector<int8_t>& temp) {
    int W = 0;
    int i = s;
    while (i < e) {
        int count = 0;
        int j = 0;
        while (j < temp.size()) {
            if (seq[i + j] ^ temp[j] == 0)
                count++;
            else {
                break;
            }
            j++;
        }
        i++;
        if (count == temp.size())
            W++;
    }
    return W;
}

double mean(int M, int m) {
    return (M - m + 1) / pow(2, m);
}

double variance(int M, int m) {
    return M*((1 / pow(2, m)) - ((2*m - 1) / pow(2, 2*m)));
}

double hi_square(int M, int m, vector<int>& W) {
    double mu = 0.0;
    double sigma = 0.0;
    mu = mean(M, m);
    sigma = variance(M, m);
    double hi = 0.0;
    for (int i = 0; i < W.size(); i++) {
        hi += pow(W[i] - mu, 2) / sigma;
    }
    return hi;
}

double igamc(int N, int M, int m, vector<int>& W) {
    double hi = hi_square(M, m, W);
    double gamma = Cephes::cephes_igamc(N / 2, hi / 2);
    return gamma;
}


// int flp2 (int x){
//     x = x | (x >> 1);
//     x = x | (x >> 2);
//     x = x | (x >> 4);
//     x = x | (x >> 8);
//     x = x | (x >> 16);
//     return x - (x >> 1);
// }

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
    
    int N = 16;
    vector<int8_t> temp = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    int m = temp.size();
    clock_t tStart = clock();
    vector<int> w(N);
    int M = sequence1.size() / N;
    for (int i = 0; i < N; i++) {
        int start = M*i;
        int end = M*(i + 1);
        w[i] = calculate_W(sequence1, start, end, temp, M);
    }
    double p = igamc(N, M, m, w);
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    cout << p << endl;
    exit(0);
    w.clear();
    tStart = clock();
    M = sequence2.size() / N;
    for (int i = 0; i < N; i++) {
        int start = M*i;
        int end = M*(i + 1);
        w.push_back(calculate_W(sequence2, start, end, temp, M));
    }
    cout << igamc(N, M, m, w) << endl; 
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    w.clear();
    tStart = clock();
    M = sequence3.size() / N;
    for (int i = 0; i < N; i++) {
        int start = M*i;
        int end = M*(i + 1);
        w.push_back(calculate_W(sequence3, start, end, temp, M));
    }
    cout << igamc(N, M, m, w) << endl; 
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    w.clear();
    tStart = clock();
    M = sequence4.size() / N;
    for (int i = 0; i < N; i++) {
        int start = M*i;
        int end = M*(i + 1);
        w.push_back(calculate_W(sequence4, start, end, temp, M));
    }
    cout << igamc(N, M, m, w) << endl; 
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    w.clear();
    tStart = clock();
    M = sequence5.size() / N;
    for (int i = 0; i < N; i++) {
        int start = M*i;
        int end = M*(i + 1);
        w.push_back(calculate_W(sequence5, start, end, temp, M));
    }
    cout << igamc(N, M, m, w) << endl; 
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    w.clear();
    tStart = clock();
    M = sequence6.size() / N;
    for (int i = 0; i < N; i++) {
        int start = M*i;
        int end = M*(i + 1);
        w.push_back(calculate_W(sequence6, start, end, temp, M));
    }
    cout << igamc(N, M, m, w) << endl; 
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    w.clear();
    tStart = clock();
    M = sequence7.size() / N;
    for (int i = 0; i < N; i++) {
        int start = M*i;
        int end = M*(i + 1);
        w.push_back(calculate_W(sequence7, start, end, temp, M));
    }
    cout << igamc(N, M, m, w) << endl; 
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    w.clear();
    tStart = clock();
    M = sequence8.size() / N;
    for (int i = 0; i < N; i++) {
        int start = M*i;
        int end = M*(i + 1);
        w.push_back(calculate_W(sequence8, start, end, temp, M));
    }
    cout << igamc(N, M, m, w) << endl; 
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
}