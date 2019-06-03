#include "../libraries/serial_test_zakrevsky.hpp"
#include "../libraries/cephes.h"

namespace serial_test {

    void Serial_test_zakrevsky::read(std::string filename, int param_m) {
        if (filename.empty())
            std::cerr << "Filename is undefined" << std::endl;
        else
            std::cout << "Read from(Serial_test Zakrevsky) " << filename << std::endl;

        std::ifstream f(filename, std::ios::binary | std::ios::in);

        if (!f.is_open()) {
            std::cerr << "Could NOT find " + filename << std::endl;
            return;
        }
        int n = get_size_file(filename);
        int r = param_m;
        int w = ceil((r - 1) / 8);
        _buffer.reserve(n + w);

        char c;
        while (f.get(c)) 
            _buffer.emplace_back(c);
        f.close();

        for (int i = 0; i < w; i++) {
            _buffer[n + i] = 0;
        }
        numbers_of_bits = n * 8;
    }

    std::pair<double, double> Serial_test_zakrevsky::run_test(int param_m) const {
        std::cout << "Started performing serial_test Zakrevsky" << std::endl;
        int n = numbers_of_bits;
        int r = param_m;
        int w = ceil((r - 1) / 8);
        int * masM = new int[(int)pow(2, r)];
        int * masM_1 = new int[(int)pow(2, r - 1)];
        int * masM_2 = new int[(int)pow(2, r - 2)];

        //заполнение
        for (int i = 0; i < pow(2, r); i++) {
            masM[i] = 0;
        }
        for (int i = 0; i < pow(2, r - 1); i++) {
            masM_1[i] = 0;
        }
        for (int i = 0; i < pow(2, r - 2); i++) {
            masM_2[i] = 0;
        }

        counter(r, masM, n / 8, w);
        counter(r - 1, masM_1, n / 8, w);
        counter(r - 2, masM_2, n / 8, w);
        double fiM = 0, fiM_1 = 0, fiM_2 = 0;
        for (int i = 0; i < pow(2, r); i++) {
            fiM += pow(masM[i], 2);
        }
        fiM /= n;
        fiM *= pow(2, r);
        for (int i = 0; i < pow(2, r - 1); i++) {
            fiM_1 += pow(masM_1[i], 2);
        }
        fiM_1 /= n ;
        fiM_1 *= pow(2, r-1);
        for (int i = 0; i < pow(2, r - 2); i++) {
            fiM_2 += pow(masM_2[i], 2);
        }
        fiM_2 /= n ;
        fiM_2 *= pow(2, r-2);
        fiM -= n; fiM_1 -= n; fiM_2 -= n;
        double delta_m = fiM - fiM_1;
        double delta2_m = fiM - 2 * fiM_1 + fiM_2;
        delete[] masM;
        delete[] masM_1;
        delete[] masM_2;

        return std::make_pair(
            cephes_igamc(pow(2, r - 2), delta_m/2), 
            cephes_igamc(pow(2, r - 3), delta2_m/2)
            );
        // return std::make_pair(0.0, 0.0);
    }

    void Serial_test_zakrevsky::counter(int m, int* temp, int n, int w) const {
        int number = 0;
        int first = 0;
        int exit = m;
        while (exit >= 8)
            exit -= 8;
        int local_k = pow(2, m);
        //	long counter_l = 0;
        //	int temp_counter = 0;
        for (int i = 0; i < n + w; i++) {
            for (int j = 7; j >= 0; --j) {
                if (first != m) {
                    first++;
                    number = number << 1;
                    number += (_buffer[i] >> j) & 1;
                }
                else {
                    //cout << number<<endl;
                    number = number << 1;
                    number += (_buffer[i] >> j) & 1;
                    if (number >= local_k)
                        number -= local_k;
                    temp[number]++;
                }
                if (i == n + w - 1 && j == 7 - exit + 1)
                    return;
            }
        }
        return;
    }

    std::size_t Serial_test_zakrevsky::get_size_file(std::string filename) const {
        std::ifstream f(filename, std::ios::binary | std::ios::in | std::ifstream::ate);
        return f.tellg();
    }
} //namespace serial_test


