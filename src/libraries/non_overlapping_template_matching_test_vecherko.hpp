#pragma once

#include "non_overlapping_template_matching_test.hpp"

namespace non_overlapping_template_matching_test {

    using bytes_vecherko = std::vector<bool>;

    class Non_overlapping_template_matching_test_vecherko : public Non_overlapping_template_matching_test {
    public:
        Non_overlapping_template_matching_test_vecherko() = default;
        Non_overlapping_template_matching_test_vecherko(const Non_overlapping_template_matching_test_vecherko &non_overlapping_template_matching_test_vecherko) = default;
        Non_overlapping_template_matching_test_vecherko(Non_overlapping_template_matching_test_vecherko &&non_overlapping_template_matching_test_vecherko) = default;
        Non_overlapping_template_matching_test_vecherko &operator=(const Non_overlapping_template_matching_test_vecherko &non_overlapping_template_matching_test_vecherko) = default;
        Non_overlapping_template_matching_test_vecherko &operator=(Non_overlapping_template_matching_test_vecherko &&non_overlapping_template_matching_test_vecherko) = default;
        ~Non_overlapping_template_matching_test_vecherko() = default;

        void read(std::string filename = "") override;

        long double run_test(std::size_t number_of_blocks = 16, std::string _pattern = "000000001") const override;

    private:
        void prefix_function(bytes_vecherko &prefix) const;

        std::size_t find_first(std::size_t from, std::size_t to, bytes_vecherko &prefix) const;

        long double upper_incomplete_gamma(unsigned s, long double x) const;

        std::size_t get_size_file(std::string filename) const;

        bytes_vecherko _buffer;
        bytes_vecherko _pattern;
    };

} //namespace non_overlapping_template_matching_test