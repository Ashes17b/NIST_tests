#include "../libraries/longest_runs_test_bondarev.hpp"

namespace longest_runs_test {

    void Longest_runs_test_bondarev::read(std::string filename /* = "" */) {
        if (filename.empty())
            std::cerr << "Filename is undefined" << std::endl;
        else
            std::cout << "Read from(Longest_runs_test_bondarev Bondarev) " << filename << std::endl;

        std::ifstream f(filename, std::ios::binary | std::ios::in);

        if (!f.is_open()) {
            std::cerr << "Could NOT find " + filename << std::endl;
            return;
        }

        _buffer.reserve(get_size_file(filename));

        char c;
        while (f.get(c))
            _buffer.emplace_back(c);
        f.close();
    }

    double Longest_runs_test_bondarev::run_test() const {
        std::cout << "Started performing longest_runs_test Bondarev" << std::endl;
        assert(!_buffer.empty());

        double chi2, pi[7];
        double p_value;
        int run, v_n_obs, N, i, j, K, M, V[7];
        int n = _buffer.size();
        unsigned int nu[7] = { 0, 0, 0, 0, 0, 0, 0 };

        if (n < 128 / 8) {
            std::cerr << "n = " << n << " is too short" << std::endl; 
            return 0.0;
        }
        if (n < 6272 / 8) {
            K = 3;
            M = 8 / 8;
            V[0] = 1;
            V[1] = 2;
            V[2] = 3;
            V[3] = 4;
            pi[0] = 0.2148;
            pi[1] = 0.3672;
            pi[2] = 0.2305;
            pi[3] = 0.1875;
        }
        else if (n < 750000 / 8) {
            K = 5;
            M = 128 / 8;
            V[0] = 4;
            V[1] = 5;
            V[2] = 6;
            V[3] = 7;
            V[4] = 8;
            V[5] = 9;
            pi[0] = 0.1174;
            pi[1] = 0.2430;
            pi[2] = 0.2493;
            pi[3] = 0.1752;
            pi[4] = 0.1027;
            pi[5] = 0.1124;
        }
        else {
            K = 6;
            M = 10000 / 8;
            V[0] = 10;
            V[1] = 11;
            V[2] = 12;
            V[3] = 13;
            V[4] = 14;
            V[5] = 15;
            V[6] = 16;
            pi[0] = 0.0882;
            pi[1] = 0.2092;
            pi[2] = 0.2483;
            pi[3] = 0.1933;
            pi[4] = 0.1208;
            pi[5] = 0.0675;
            pi[6] = 0.0727;
        }

        N = n / M;
        //cout << N << endl;
        for (i = 0; i<N; i++) {
            v_n_obs = 0;
            run = 0;
            for (int k = 0; k<M; k++) {
                for (int j = 7; j >= 0; j--) {
                    if (((_buffer[i*M + k] >> j) & 1) == 1) {
                        run++;
                        if (run > v_n_obs)
                            v_n_obs = run;
                    }
                    else
                        run = 0;
                }
            }
            if (v_n_obs < V[0])
                nu[0]++;
            for (j = 0; j <= K; j++) {
                if (v_n_obs == V[j])
                    nu[j]++;
            }
            if (v_n_obs > V[K])
                nu[K]++;
        }

        chi2 = 0.0;
        /*for (int i = 0; i < K; i++) {
        cout << nu[i] << endl;
        }*/

        for (i = 0; i <= K; i++)
            chi2 += pow(nu[i] - N * pi[i], 2) / (N * pi[i]);
        // cout << "chi2 " << chi2 << endl;

        //pval1 = igamc(K / 2, chi2 / 2.0);
        //pval2 = cephes_igamc((double)(K / 2.0), chi2 / 2.0);
        p_value = igamc_c(K, chi2);

        return p_value;
    }

    std::size_t Longest_runs_test_bondarev::get_size_file(std::string filename) const {
        std::ifstream f(filename, std::ios::binary | std::ios::in | std::ifstream::ate);
        return f.tellg();
    }

    double Longest_runs_test_bondarev::igamc_c(int K, double chi2) const {
        if (K % 2 == 0) {
            int a = K / 2;
            double x = chi2 / 2.0;

            double sum = 1;
            double mult = 1;
            int fact = 1;

            for (int i = 1; i < a; i++) {
                mult *= x / i;
                sum += mult;
                fact *= i;
            }
            double upgamma = fact * sum * exp(-x);
            return upgamma / tgamma(a);
        }
        else {
            double a = 1. * K / 2.;
            double x = chi2 / 2.;
            double firstGamma = sqrt(acos(-1)) * erfc(sqrt(x));
            double nextGamma = 0;
            for (double k = 0.5, x_power = sqrt(x); k < a - 0.5; k++) {
                nextGamma = k * firstGamma + x_power * exp(-x);
                firstGamma = nextGamma;
                x_power *= x;
            }
            return nextGamma / tgamma(a);
        }
    }

} //namespace random_excursions_test