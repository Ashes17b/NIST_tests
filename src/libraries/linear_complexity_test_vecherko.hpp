#pragma once

#include "linear_complexity_test.hpp"

namespace linear_complexity_test {

    typedef unsigned char byte;
    
    struct bytes {
        byte* seq;
        int  len;
        bytes(byte* seq, int len) {
            this->seq = seq;
            this->len = len;
        }
        ~bytes() {
            delete seq;
        }
    };

    class Linear_complexity_test_vecherko : public Linear_complexity_test
    {
    public:
        Linear_complexity_test_vecherko() = default;
        Linear_complexity_test_vecherko(const Linear_complexity_test_vecherko &Linear_complexity_test_vecherko) = default;
        Linear_complexity_test_vecherko(Linear_complexity_test_vecherko &&Linear_complexity_test_vecherko) = default;
        Linear_complexity_test_vecherko &operator=(const Linear_complexity_test_vecherko &Linear_complexity_test_vecherko) = default;
        Linear_complexity_test_vecherko &operator=(Linear_complexity_test_vecherko &&Linear_complexity_test_vecherko) = default;
        ~Linear_complexity_test_vecherko() = default;

        void read(std::string filename = "") override;

        double run_test(int param_m = 50) const override;

    private:
        std::size_t get_size_file(std::string filename) const;
        double theoretical_mean(int m) const;
        int neg_one_pow(int n) const;
        int linear_complexity(byte* seq, int offset, int N) const;
        int get_v_index(double t) const;
        double igamc(unsigned int s, double x) const;
        double gamma(unsigned int s2) const;
        double igamc2(unsigned int s2, double x) const;

        bytes* _buffer;

        template <typename T> void arraycopy(T* src, T* dest, int len) const {
            for(int i=0; i<len; i++) {
                dest[i] = src[i];
            }
        }

        template <typename number> number* zero_arr(int size) const {
            number* arr = new number[size];
            for(int i=0; i<size; i++) {
                arr[i] = 0;
            }
            return arr;
        }

    };

} //namespace linear_complexity_test