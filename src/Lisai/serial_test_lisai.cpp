#include "../libraries/serial_test_lisai.hpp"
#include "../libraries/cephes.h"

namespace serial_test {

    void Serial_test_lisai::read(std::string filename, int param_m) {
        if (filename.empty())
            std::cerr << "Filename is undefined" << std::endl;
        else
            std::cout << "Read from(Serial_test Lisai) " << filename << std::endl;

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

    std::pair<double, double> Serial_test_lisai::run_test(int param_m) const {
        std::cout << "Started performing serial_test Lisai" << std::endl;
        assert(!_buffer.empty());

        auto n = _buffer.size();
        auto m = param_m;
        double	p_value1, p_value2, psim0, psim1, psim2, del1, del2;
        
        psim0 = psi2(_buffer, m, n);
        psim1 = psi2(_buffer, m-1, n);
        psim2 = psi2(_buffer, m-2, n);
        
        del1 = psim0 - psim1;
        del2 = psim0 - 2.0 * psim1 + psim2;
        
        p_value1 = cephes_igamc(pow(2, m-2), del1 / 2.0);
        p_value2 = cephes_igamc(pow(2, m-3), del2 / 2.0);
        
        return std::make_pair(p_value1, p_value2);
    }

    std::size_t Serial_test_lisai::get_size_file(std::string filename) const {
        std::ifstream f(filename, std::ios::binary | std::ios::in | std::ifstream::ate);
        return f.tellg();
    }

    double Serial_test_lisai::psi2(bytes epsilon, int m, int n) const {
        int	max_value = (int)pow(2, m);
        double	sum;
        
        if ( (m == 0) || (m == -1) )
            return 0.0;

        int	*P = new int[max_value];

        for (int i = 0; i < max_value; i++ )
            P[i] = 0;

        int k = 0;
        int bit;

        // read first m bit:
        int i = 0, j = 0;
        int how_much_bits_is_counted = 0;
        for ( ; i < n && how_much_bits_is_counted < m; i++ ) {
            for ( j = 7; j >= 0 && how_much_bits_is_counted < m; --j, how_much_bits_is_counted ++ ) {
                bit = ((epsilon[i] >> j) & 1);
                k += (bit & 1) * pow(2, m - how_much_bits_is_counted - 1);
            }
        }
        P[k] ++; 
        int j_hat = j;
        // ok, read other bits:
        for ( i --; i < n; i ++ ) {
            for ( j = j_hat; j >= 0; --j ) {
                bit = ((epsilon[i] >> j) & 1);
                k = (k << 1) ^ (bit & 1);
                if ( k >= max_value) {
                    k = k ^ max_value;
                }
                P[k] ++;
            }
            j_hat = 7;
        }
        // its zeros at the end:
        for ( i = 0; i < m - 1; i ++ ) {
            bit = 0;
            k = (k << 1) ^ (bit & 1);
            if ( k >= max_value) {
                k = k ^ max_value;
            }
            P[k] ++;
        }

        sum = 0.0;
        for (int i = 0; i < max_value; i++ )
            sum += pow(P[i], 2);
        sum = (sum * pow(2, m)/(double)n) - (double)n;
        delete [] P;

        return sum;
    }
} //namespace serial_test