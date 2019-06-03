#include "../libraries/approximate_entropy_test_grudinsky.hpp"
#include "../libraries/cephes.h"

namespace approximate_entropy_test {

    void Approximate_entropy_test_grudinsky::read(std::string filename, int param_m) {
        if (filename.empty())
            std::cerr << "Filename is undefined" << std::endl;
        else
            std::cout << "Read from(Approximate_entropy_test Grudinsky) " << filename << std::endl;

        std::ifstream f(filename, std::ios::binary);
        numbers_of_bytes = get_size_file(filename);
        int n = numbers_of_bytes;
        int m = param_m;
        _buffer.reserve(n + m / 8 + 1);
        char c;
        while (f.get(c)) 
            _buffer.emplace_back(c);
        f.close();

        for(int i = 0; i < m / 8 + 2; i++)
            _buffer[n + i] = _buffer[i];
    }

    double Approximate_entropy_test_grudinsky::run_test(int param_m) {
        std::cout << "Started performing approximate_entropy_test Grudinsky" << std::endl;
        int m = param_m;
        int v = pow(2, m);
        int n = numbers_of_bytes;
        int *counter = new int [v];
        for(int i = 0; i < v; i++)
            counter[i] = 0;

        int count = m, cur = 0;
        for(int i = 0; i < m / 8 + 1; i++)
            for(int j = 7; j >= 0; j--)
                if(count == 0)
                    break;
                else
                {
                    cur += pow(2, count - 1)*((_buffer[i] >> j) & 1);
                    count--;
                }
        
        for(int i = 0; i <= n + m / 8; i++)
            for(int j = 7; j >= 0; j--)
            {
                cur <<= 1;
                if(cur >= v)
                    cur -= v;
                cur += (_buffer[i] >> j) & 1;
                if((i < m / 8) || (i == m / 8 && j > 8 - m % 8) || (i == n + m / 8 && j < 9 - m % 8))
                    counter[cur]--;
                counter[cur]++;
            }
        
            n *= 8;
    double sum = 0;
    for(int i = 0; i < v; i++)
        if(counter[i] != 0)
            sum += counter[i] * 1.0 / n * log(counter[i] * 1.0 / n);

    m++;
    v = pow(2, m);

    counter = new int [v];
    n /= 8;

    cur = 0;

    count = m;
    for(int i = 0; i < m / 8 + 1; i++)
        for(int j = 7; j >= 0; j--)
            if(count == 0)
                break;
            else
            {
                cur += pow(2, count - 1)*((_buffer[i] >> j) & 1);
                count--;
            }

        for(int i = 0; i < v; i++)
            counter[i] = 0;

        for(int i = 0; i <= n + m / 8; i++)
            for(int j = 7; j >= 0; j--)
            {
                cur <<= 1;
                if(cur >= v)
                    cur -= v;
                cur += (_buffer[i] >> j) & 1;
                if((i < m / 8) || (i == m / 8 && j > 8 - m % 8) || (i == n + m / 8 && j < 9 - m % 8))
                    counter[cur]--;
                counter[cur]++;
            }

        n *= 8;
        double ApEn = sum;
        sum = 0;
        for(int i = 0; i < v; i++)
            if(counter[i] != 0)
                sum += counter[i] * 1.0 / n * log(counter[i] * 1.0 / n);

        ApEn -= sum;

        double ksi2 = 2 * n * (log(2) - ApEn);
        v /= 4;

        double p_value = cephes_igamc(v, ksi2 / 2);

        delete [] counter;
        return p_value;
    }
    
    // double Approximate_entropy_test_grudinsky::f(double x, double a) {
    //     return exp(-x) * pow(x, a - 1);
    // }

    std::size_t Approximate_entropy_test_grudinsky::get_size_file(std::string filename) const {
        std::ifstream f(filename, std::ios::binary | std::ios::in | std::ifstream::ate);
        return f.tellg();
    }
} //namespace approximate_entropy_test