#include "../libraries/random_excursions_test_bondarev.hpp"

namespace random_excursions_test {

    void Random_excursions_test_bondarev::read(std::string filename /* = "" */) {
        if (filename.empty())
            std::cerr << "Filename is undefined" << std::endl;
        else
            std::cout << "Read from(Random_excursions_test_bondarev Bondarev) " << filename << std::endl;

        std::ifstream f(filename, std::ios::binary | std::ios::in);

        if (!f.is_open()) {
            std::cerr << "Could NOT find " + filename << std::endl;
            return;
        }

        _buffer.reserve(get_size_file(filename));

        char c;
        while (f.get(c))
            for (int i = 7; i >= 0; --i)
                _buffer.emplace_back(((c >> i) & 1));

        f.close();
    }

    double Random_excursions_test_bondarev::run_test() const {
        std::cout << "Started performing random_excursions_test Bondarev" << std::endl;
        assert(!_buffer.empty());

        int     b, i, j, k, J, x;
        int     cycleStart, cycleStop, *cycle = NULL, *S_k = NULL;
        int     stateX[8] = { -4, -3, -2, -1, 1, 2, 3, 4 };
        int     counter[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
        double  p_value, sum, constraint, nu[6][8];
        double min_p_value = 0;
        int n = _buffer.size();
        double  pi1[7][6] = { { 0.5000, 0.2500, 0.1250, 0.0625, 0.0312, 0.0312 },
        { 0.7500, 0.0625, 0.0469, 0.0352, 0.0264, 0.0791 },
        { 0.8333, 0.0278, 0.0231, 0.0193, 0.0161, 0.0804 },
        { 0.8750, 0.0156, 0.0137, 0.0120, 0.0105, 0.0733 },
        { 0.9000, 0.0100, 0.0090, 0.0081, 0.0073, 0.0656 },
        { 0.9167, 0.0069, 0.0064, 0.0058, 0.0053, 0.0588 },
        { 0.9286, 0.0051, 0.0047, 0.0044, 0.0041, 0.0531 } };

        if (((S_k = (int *)calloc(n, sizeof(int))) == NULL) || ((cycle = (int *)calloc(fmax(1000, n / 100), sizeof(int))) == NULL)) {
            std::cerr << "Random Excursions Test:  Insufficent Work Space Allocated." << std::endl;
            assert(S_k);
            free(S_k);
            assert(cycle);
            free(cycle);
            // if (S_k != NULL)
            //     free(S_k);
            // if (cycle != NULL)
            //     free(cycle);
            return 0.0;
        }

        J = 0;
        S_k[0] = 2 * _buffer[0] - 1;
        for (i = 1; i < n; i++) {
            S_k[i] = S_k[i - 1] + 2 * _buffer[i] - 1;
            if (S_k[i] == 0) {
                J++;
                if (J > fmax(1000, n / 100)) {
                    std::cerr << "ERROR IN FUNCTION randomExcursions:  EXCEEDING THE MAX NUMBER OF CYCLES EXPECTED" << std::endl;
                    free(S_k);
                    free(cycle);
                    return 0.0;
                }
                cycle[J] = i;
            }
        }
        if (S_k[n - 1] != 0)
            J++;
        cycle[J] = n;

        constraint = fmax(0.005*pow(n, 0.5), 500);
        if (J < constraint) {
            std::cerr << "WARNING:  TEST NOT APPLICABLE.  THERE ARE AN INSUFFICIENT NUMBER OF CYCLES.\n" << std::endl;
        }
        else {
            
            cycleStart = 0;
            cycleStop = cycle[1];
            for (k = 0; k < 6; k++)
                for (i = 0; i < 8; i++)
                    nu[k][i] = 0.;
            for (j = 1; j <= J; j++) {
                for (i = 0; i < 8; i++)
                    counter[i] = 0;
                for (i = cycleStart; i < cycleStop; i++) {
                    if ((S_k[i] >= 1 && S_k[i] <= 4) || (S_k[i] >= -4 && S_k[i] <= -1)) {
                        if (S_k[i] < 0)
                            b = 4;
                        else
                            b = 3;
                        counter[S_k[i] + b]++;
                    }
                }
                cycleStart = cycle[j] + 1;
                if (j < J)
                    cycleStop = cycle[j + 1];

                for (i = 0; i < 8; i++) {
                    if ((counter[i] >= 0) && (counter[i] <= 4))
                        nu[counter[i]][i]++;
                    else if (counter[i] >= 5)
                        nu[5][i]++;
                }
            }

            for (i = 0; i < 8; i++) {
                x = stateX[i];
                sum = 0.0;
                for (k = 0; k < 6; k++) {
                        sum = 0.0;
                        for (k = 0; k < 6; k++) {
                            int t = abs(x);
                            double chisl = nu[k][i] - J*pi1[t - 1][k];
                            chisl = pow(chisl, 2);
                            double znam = J*pi1[t - 1][k];
                            sum += chisl / znam;
                        }
                    
                    p_value = igamc_c(5, sum);

                    if (i == 0)
                        min_p_value = p_value;
                    else
                        min_p_value = p_value < min_p_value ? p_value : min_p_value;
                }
            }

            free(S_k);
            free(cycle);
        }

        return min_p_value;
    }

    std::size_t Random_excursions_test_bondarev::get_size_file(std::string filename) const {
        std::ifstream f(filename, std::ios::binary | std::ios::in | std::ifstream::ate);
        return f.tellg();
    }

    double Random_excursions_test_bondarev::igamc_c(int K, double chi2) const {
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