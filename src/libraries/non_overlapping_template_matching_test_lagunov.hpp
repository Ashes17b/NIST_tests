#pragma once

#include "non_overlapping_template_matching_test.hpp"
#include "../libraries/cephes.h"

namespace non_overlapping_template_matching_test {

    using bytes = std::vector<int8_t>;

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

        double run_test() const override;

    private:
        
        int calculate_W(const std::vector<int8_t>& seq, int s, int e, const std::vector<int8_t>& temp, int M) const;
        double mean(int M, int m) const;
        double variance(int M, int m) const;
        double hi_square(int M, int m, std::vector<int>& W) const;
        double igamc(int N, int M, int m, std::vector<int>& W) const;

        bytes _buffer;
    };  

} //namespace non_overlapping_template_matching_test