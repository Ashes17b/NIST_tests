#include "../libraries/random_excursions_test_timoshenko.hpp"

namespace random_excursions_test {

    void Random_excursions_test_timoshenko::read(std::string filename /* = "" */) {
        if (filename.empty())
            std::cerr << "Filename is undefined" << std::endl;
        else
            std::cout << "Read from(Random_excursions_test_timoshenko Timoshenko) " << filename << std::endl;

        std::ifstream f(filename, std::ios::binary | std::ios::in);

        if (!f.is_open()) {
            std::cerr << "Could NOT find " + filename << std::endl;
            return;
        }

        _buffer.reserve(get_size_file(filename)*8);

        char c;
        while (f.get(c))
            for (int i = 7; i >= 0; --i)
                _buffer.emplace_back(((c >> i) & 1));

        f.close();
    }

    double Random_excursions_test_timoshenko::run_test() const {
        std::cout << "Started performing random_excursions_test Timoshenko" << std::endl;
        assert(!_buffer.empty());

        std::vector<int> sums;
        std::vector<int> cycle;
        int pos = 0;
        int J = 0;
        
        for ( int i = 0; i < _buffer.size(); i++ ) {
            pos += (_buffer[i] * 2 - 1);
            sums.push_back(pos);
            if ( pos == 0 ) {
                J++;
                cycle.push_back(i);
            }
        }
        if ( sums[_buffer.size() - 1] != 0 )
            J++;

        cycle.push_back(_buffer.size());
        
        // cout << "J=" << J << endl;

        double nu[6][8];
        int	stateX[8] = { -4, -3, -2, -1, 1, 2, 3, 4 };
        int	counter[8] = { 0 };
        int b;
        double min_p_value = 0;
        double pi[7][6] = {{0.5 ,0.25, 0.125, 0.0625, 0.0312, 0.0312},
            {0.7500, 0.0625, 0.0469, 0.0352, 0.0264, 0.0791},
            {0.8333, 0.0278 ,0.0231, 0.0193, 0.0161, 0.0804},
            {0.8750, 0.0156, 0.0137, 0.0120, 0.0105, 0.0733},
            {0.9000, 0.0100, 0.0090, 0.0081, 0.0073, 0.0656},
            {0.9167, 0.0069, 0.0064, 0.0058, 0.0053, 0.0588},
            {0.9286, 0.0051, 0.0047, 0.0044, 0.0041, 0.0531}};
        double p_value;

        if ( J < fmax(500., 0.005 * sqrt(_buffer.size())) ) 
            std::cerr << "THERE ARE AN INSUFFICIENT NUMBER OF CYCLES. The randomness hypothesis is rejected." << std::endl;
        else {
            int cycle_start = 0;
            int cycle_stop = cycle[1];
            for ( int k = 0; k < 6; k++ )
                for ( int i = 0; i < 8; i++ )
                    nu[k][i] = 0.;
            for ( int j = 1; j <= J; j++ ) {                           
                for ( int i = 0; i < 8; i++ )
                    counter[i] = 0;
                for ( int i = cycle_start; i < cycle_stop; i++ ) {
                    if ( (sums[i] >= 1 && sums[i] <= 4) || (sums[i] >= -4 && sums[i] <= -1) ) {
                        if (sums[i] < 0 )
                            b = 4;
                        else
                            b = 3;
                        counter[sums[i] + b]++;
                    }
                }
                cycle_start = cycle[j] + 1;
                if ( j < J )
                    cycle_stop = cycle[j + 1];

                for ( int i = 0; i < 8; i++ ) {
                    if ( (counter[i] >= 0) && (counter[i] <= 4) )
                        nu[counter[i]][i]++;
                    else if ( counter[i] >= 5 )
                        nu[5][i]++;
                }
            }
            
            int x;
            double denominator, numerator, chisq;
                for ( int i = 0; i < 8; i++ ) {
                    x = stateX[i];
                    chisq = 0.;
                    for ( int k = 0; k < 6; k++ ) {
                        numerator = pow((double)nu[k][i] - ((double)J * (pi[abs(x) - 1][k])), 2);
                        denominator = J * pi[abs(x) - 1][k];
                        chisq += numerator / denominator;
                    }
                    double gamma0_5 = sqrt(M_PI) * erfc(sqrt(chisq / 2.0)) / tgamma(0.5); 
                    double gamma1_5 = (gamma0_5 * 0.5 + pow(chisq / 2.0, 0.5) * exp(-chisq / 2.0)) / tgamma(1.5);
                    p_value = (gamma1_5 * 1.5 + pow(chisq / 2.0, 1.5) * exp(-chisq / 2.0)) / tgamma(2.5);

                    // cout << x <<" : chisq = " << chisq <<" : p_value = " << p_value << endl;
                    if (i == 0)
                        min_p_value = p_value;
                    else
                        min_p_value = p_value < min_p_value ? p_value : min_p_value;
                }
        }
        // if ( min_p_value < 0.01 )
        //     cout << "Sequence is non-random." << endl;
        // else 
        //     cout << "Sequence is random." << endl;
        
        return min_p_value;
    }

    std::size_t Random_excursions_test_timoshenko::get_size_file(std::string filename) const {
        std::ifstream f(filename, std::ios::binary | std::ios::in | std::ifstream::ate);
        return f.tellg();
    }

} //namespace random_excursions_test