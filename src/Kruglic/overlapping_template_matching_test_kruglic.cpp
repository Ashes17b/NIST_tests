#include "../libraries/overlapping_template_matching_test_kruglic.hpp"

namespace overlapping_template_matching_test {

    void Overlapping_template_matching_test_kruglic::read(std::string filename /* = "" */) {
        if (filename.empty())
            std::cerr << "Filename is undefined" << std::endl;
        else 
            std::cout << "Read from(Overlapping_template_matching_test Kruglic) " << filename << std::endl;
        
        std::ifstream f(filename, std::ios::binary | std::ios::in);

        if (!f.is_open()) {
            std::cerr << "Could NOT find " + filename << std::endl;
            return;
        }

        f.seekg(0, std::ios::end);
        n = f.tellg();
        f.seekg(0);
        _buffer.resize(n);
        f.read((char*)&_buffer[0], n);
        f.close();
        n *= 8;
    }

    double Overlapping_template_matching_test_kruglic::run_test() const {
        std::cout << "Started performing overlapping_template_matching_test Kruglic" << std::endl;
        assert(!_buffer.empty());

        return OverlappingTemplateMatchings();
    }

    int Overlapping_template_matching_test_kruglic::Counter(int numberOfBlock, int blockSize) const {
        int counter_l = 0;
        int counter = 0;
        for (size_t i = numberOfBlock * blockSize * 8; i < (numberOfBlock + 1) * blockSize * 8; ++i) {
            uint32_t idx = i >> 3;
            uint8_t bias = (i & 7);
            if (_buffer[idx] & (1 << bias)) {
                ++counter_l;
            } else {
                counter_l = 0;
            }
            if (counter_l >= m) {
                ++counter;
            }
        }
        return counter;
    }


    double Overlapping_template_matching_test_kruglic::Pi(int u, double eta) const {
        int	l;
        double	sum, p;
        if (u == 0) {
            p = exp(-eta);
        } else {
            sum = 0.0;
            for (l = 1; l <= u; l++)
                sum += exp(-eta - u * log(2) + l * log(eta)
                        - lgamma(l + 1) + lgamma(u) -
                        lgamma(l) -lgamma(u - l + 1));
            p = sum;
        }
        return p;
    }


    double Overlapping_template_matching_test_kruglic::MyIgamc(double chi2) const {
        if (!(K & 1)) {
            double sum = 1;
            double prev = 1;
            double x = chi2 / 2.;
            int fact = 1;
            int s = K / 2;
            for (int i = 1; i < s; ++i) {
                prev *= x;
                prev /= i;
                sum += prev;
                fact *= i;
            }
            double gamma = fact * sum * exp(-x);
            return gamma / tgamma(s);
        } else {
            double s = 1. * K / 2.;
            double x = chi2 / 2.;
            double firstGamma = sqrt(acos(-1)) * erfc(sqrt(x));
            double nextGamma = 0;
            double k = 0.5;
            double x_power = sqrt(x);
            while (k < s - 0.5) {
                nextGamma = k * firstGamma + x_power * exp(-x);
                firstGamma = nextGamma;
                ++k;
                x_power *= x;
            }
            return nextGamma / tgamma(s);
        }
    }


    double Overlapping_template_matching_test_kruglic::OverlappingTemplateMatchings() const {

        int N = n / M;

        double lambda = (1. * M - 1. * m + 1.) / pow(2, m);
       
        double eta = lambda / 2.;

        std::vector<int> nu(K + 1, 0);
        for (size_t i = 0; i < N; ++i) {
            int count = Counter(i, (int) M / 8);
            if (count < K) {
                nu[count]++;
            } else {
                nu[K]++;
            }
        }

        std::vector<double> pi(K + 1);
        if (K == 5 && m == 9) {
            pi = {0.364091, 0.185659, 0.139381, 0.100571, 0.0704323, 0.139865};
        } else {
            double sum = 0.;
            double min = 2;
            for (size_t i = 0; i < K; i++) {
                pi[i] = Pi(i, eta);
                if (min > pi[i]) {
                    min = pi[i];
                }
                sum += pi[i];
            }

            pi[K] = 1 - sum;
            if (min > pi[K]) {
                min = pi[K];
            }
        }

        double chi2 = 0.;
        for (size_t i = 0; i < K + 1; ++i) {
            chi2 += pow(1. * nu[i] - 1. * N * pi[i], 2) / pi[i];
        }
        chi2 /= (double)N;

        double p_value = MyIgamc(chi2);
        return p_value;
    }

} //namespace overlapping_template_matching_test_kruglic