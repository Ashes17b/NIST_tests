#pragma once

#include "non_overlapping_template_matching_test.hpp"
#include "cephes.h"

namespace non_overlapping_template_matching_test {

    using bytes1 = std::vector<char>;

    class Non_overlapping_template_matching_test_zakrevsky : public Non_overlapping_template_matching_test
    {
    public:
        Non_overlapping_template_matching_test_zakrevsky() = default;
        Non_overlapping_template_matching_test_zakrevsky(const Non_overlapping_template_matching_test_zakrevsky &non_overlapping_template_matching_test_zakrevsky) = default;
        Non_overlapping_template_matching_test_zakrevsky(Non_overlapping_template_matching_test_zakrevsky &&non_overlapping_template_matching_test_zakrevsky) = default;
        Non_overlapping_template_matching_test_zakrevsky& operator=(const Non_overlapping_template_matching_test_zakrevsky &non_overlapping_template_matching_test_zakrevsky) = default;
        Non_overlapping_template_matching_test_zakrevsky& operator=(Non_overlapping_template_matching_test_zakrevsky &&non_overlapping_template_matching_test_zakrevsky) = default;
        ~Non_overlapping_template_matching_test_zakrevsky() = default;

        void read(std::string filename = "") override;

        double run_test() const override;

    private:
        long long counter(int pos ,int buf_size, int* temp) const;
        double gamma_inc(double a, double x) const;
        float poisson_z(float x, float mu) const;
        void init(int* mas, int m) const;

        bytes1 _buffer;
        int size;
        const int m = 9;
        std::string temoString = "100010001";
    };  

} //namespace non_overlapping_template_matching_test