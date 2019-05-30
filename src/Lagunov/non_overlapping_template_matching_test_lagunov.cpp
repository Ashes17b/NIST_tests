#include "../libraries/non_overlapping_template_matching_test_lagunov.hpp"
#include "../libraries/cephes.h"

namespace non_overlapping_template_matching_test {

    void Non_overlapping_template_matching_test_lagunov::read(std::string filename /* = "" */) {
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

    double Non_overlapping_template_matching_test_lagunov::run_test() const {
        std::cout << "non_overlapping_template_matching_test Lagunov" << std::endl;
        assert(!_buffer.empty());

        int N = 16;
        std::vector<int8_t> temp = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
        int m = temp.size();
        std::vector<int> w(N);
        int M = _buffer.size() / N;
        for (int i = 0; i < N; i++) {
            int start = M*i;
            int end = M*(i + 1);
            w[i] = calculate_W(_buffer, start, end, temp, M);
        }
        double p = igamc(N, M, m, w);
        return p;
    }

    int Non_overlapping_template_matching_test_lagunov::calculate_W(const std::vector<int8_t>& seq, int s, int e, const std::vector<int8_t>& temp, int M) const {
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

    double Non_overlapping_template_matching_test_lagunov::mean(int M, int m) const{
        return (M - m + 1) / pow(2, m);
    }

    double Non_overlapping_template_matching_test_lagunov::variance(int M, int m) const{
        return M*((1 / pow(2, m)) - ((2*m - 1) / pow(2, 2*m)));
    }

    double Non_overlapping_template_matching_test_lagunov::hi_square(int M, int m, std::vector<int>& W) const{
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

    double Non_overlapping_template_matching_test_lagunov::igamc(int N, int M, int m, std::vector<int>& W) const{
        double hi = hi_square(M, m, W);
        double gamma = cephes_igamc(N / 2, hi / 2);
        return gamma;
    }

} //namespace non_overlapping_template_matching_test