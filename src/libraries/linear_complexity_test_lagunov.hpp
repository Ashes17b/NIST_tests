#pragma once

#include "linear_complexity_test.hpp"
#include "../libraries/cephes.h"

namespace linear_complexity_test {

    using bytes_lagunov = std::vector<int8_t>;

    class Linear_complexity_test_lagunov : public Linear_complexity_test
    {
    public:
        Linear_complexity_test_lagunov() = default;
        Linear_complexity_test_lagunov(const Linear_complexity_test_lagunov &inear_complexity_test_lagunov) = default;
        Linear_complexity_test_lagunov(Linear_complexity_test_lagunov &&linear_complexity_test_lagunov) = default;
        Linear_complexity_test_lagunov& operator=(const Linear_complexity_test_lagunov &linear_complexity_test_lagunov) = default;
        Linear_complexity_test_lagunov& operator=(Linear_complexity_test_lagunov &&linear_complexity_test_lagunov) = default;
        ~Linear_complexity_test_lagunov() = default;

        void read(std::string filename = "") override;

        double run_test(int param_m = 50) const override;

    private:
        
        double mean(int M) const;
        std::vector<double> calculate_T(int M, std::vector<int> L) const;
        std::vector<int> calculate_nu(int M, std::vector<int> L) const;
        double hi_square(int M, int N, std::vector<int> L) const;
        double igamc(int N, int M, std::vector<int> L) const;
        int berlekamp_massey(std::vector<int8_t>& s, int n) const;

        bytes_lagunov _buffer;
    };  

} //namespace linear_complexity_test