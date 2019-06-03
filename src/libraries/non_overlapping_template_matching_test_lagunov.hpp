#pragma once

#include "non_overlapping_template_matching_test.hpp"
#include "../libraries/cephes.h"

namespace non_overlapping_template_matching_test {

    using bytes_lagunov = std::vector<int8_t>;

    class Non_overlapping_template_matching_test_lagunov : public Non_overlapping_template_matching_test
    {
    public:
        Non_overlapping_template_matching_test_lagunov() = default;
        Non_overlapping_template_matching_test_lagunov(const Non_overlapping_template_matching_test_lagunov &non_overlapping_template_matching_test_lagunov) = default;
        Non_overlapping_template_matching_test_lagunov(Non_overlapping_template_matching_test_lagunov &&non_overlapping_template_matching_test_lagunov) = default;
        Non_overlapping_template_matching_test_lagunov& operator=(const Non_overlapping_template_matching_test_lagunov &non_overlapping_template_matching_test_lagunov) = default;
        Non_overlapping_template_matching_test_lagunov& operator=(Non_overlapping_template_matching_test_lagunov &&non_overlapping_template_matching_test_lagunov) = default;
        ~Non_overlapping_template_matching_test_lagunov() = default;

        void read(std::string filename = "") override;

        long double run_test(std::size_t number_of_blocks = 16, std::string _pattern = "000000001") const override;

    private:
        
        int calculate_W(int s, int e, const std::string _pattern, int M) const;
        double mean(int M, int m) const;
        double variance(int M, int m) const;
        double hi_square(int M, int m, std::vector<int>& W) const;
        double igamc(int N, int M, int m, std::vector<int>& W) const;

        bytes_lagunov _buffer;
    };  

} //namespace non_overlapping_template_matching_test