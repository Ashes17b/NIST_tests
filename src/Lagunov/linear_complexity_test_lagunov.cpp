#include "../libraries/linear_complexity_test_lagunov.hpp"
#include "../libraries/cephes.h"

namespace linear_complexity_test {

    void Linear_complexity_test_lagunov::read(std::string filename /* = "" */) {
        if (filename.empty())
            std::cerr << "Filename is undefined" << std::endl;
        else 
            std::cout << "Read from(Linear_complexity_test Lagunov) " << filename << std::endl;
        
        std::ifstream f(filename, std::ios::binary | std::ios::in);

        if (!f.is_open()) {
            std::cerr << "Could NOT find " + filename << std::endl;
            return;
        }

        char c;
        while ( f.get(c) ) 
        {
            for ( int i = 7; i >= 0; --i ) 
                _buffer.push_back(((c >> i) & 1));
        }
        f.close();
    }

    double Linear_complexity_test_lagunov::run_test(int param_m) const {
        std::cout << "Started performing linear_complexity_test Lagunov" << std::endl;
        assert(!_buffer.empty());

        std::vector<int> l;
        int M = param_m;
        int N = _buffer.size() / M;
        for (int i = 0; i < N; i++) {
            std::vector<int8_t> block;
            for (int j = 0; j < M; j++) {
                block.push_back(_buffer[M*i + j]);
            }
            l.push_back(berlekamp_massey(block, block.size()));
            block.clear();
        }
        return igamc(N, M, l); 
    }

    double Linear_complexity_test_lagunov::mean(int M) const {
        return (M / 2) + ((9 + pow(-1, M+1)) / 36) - ((M/3 + 2/9) / pow(2, M));
    }

    std::vector<double> Linear_complexity_test_lagunov::calculate_T(int M, std::vector<int> L) const {
        std::vector<double> T;
        double mu = mean(M);
        for (int i = 0; i < L.size(); i++) {
            T.push_back(pow(-1, M)*(L[i] - mu) + (2/9));
        }
        return T;
    }

    std::vector<int> Linear_complexity_test_lagunov::calculate_nu(int M, std::vector<int> L) const {
        std::vector<int> nu;
        nu.resize(7);
        std::vector<double> T;
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
        return nu;
    }

    double Linear_complexity_test_lagunov::hi_square(int M, int N, std::vector<int> L) const {
        std::vector<double> pi;
        pi.push_back(0.010417);
        pi.push_back(0.03125);
        pi.push_back(0.125);
        pi.push_back(0.5);
        pi.push_back(0.25);
        pi.push_back(0.0625);
        pi.push_back(0.020833);
        std::vector<int> nu;
        nu = calculate_nu(M, L);
        double hi_square = 0;
        for (int i = 0; i < 7; i++)
            hi_square += (pow(nu[i] - N*pi[i], 2) / (N*pi[i]));
        return hi_square;
    }

    double Linear_complexity_test_lagunov::igamc(int N, int M, std::vector<int> L) const {
        double hi = hi_square(M, N, L);
        double gamma = cephes_igamc(7 / 2, hi / 2);
        return gamma;
    }

    int Linear_complexity_test_lagunov::berlekamp_massey(std::vector<int8_t>& s, int n) const {
        int L, N, m, d;
        std::vector<int8_t> c;
        std::vector<int8_t> b;
        std::vector<int8_t> t;

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

} //namespace linear_complexity_test