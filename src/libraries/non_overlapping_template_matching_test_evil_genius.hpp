#pragma once

#include "non_overlapping_template_matching_test.hpp"

namespace non_overlapping_template_matching_test {

    using bytes_evil_genius = std::vector<bool>;

    class Non_overlapping_template_matching_test_evil_genius : public Non_overlapping_template_matching_test {
    public:
        Non_overlapping_template_matching_test_evil_genius() = default;
        Non_overlapping_template_matching_test_evil_genius(const Non_overlapping_template_matching_test_evil_genius &non_overlapping_template_matching_test_evil_genius) = default;
        Non_overlapping_template_matching_test_evil_genius(Non_overlapping_template_matching_test_evil_genius &&non_overlapping_template_matching_test_evil_genius) = default;
        Non_overlapping_template_matching_test_evil_genius &operator=(const Non_overlapping_template_matching_test_evil_genius &non_overlapping_template_matching_test_evil_genius) = default;
        Non_overlapping_template_matching_test_evil_genius &operator=(Non_overlapping_template_matching_test_evil_genius &&non_overlapping_template_matching_test_evil_genius) = default;
        ~Non_overlapping_template_matching_test_evil_genius() = default;

        void read(std::string filename = "") override;

        long double run_test(std::size_t number_of_blocks = 16, std::string _pattern = "000000001") const override;

    private:
        void prefix_function(bytes_evil_genius &prefix) const;

        std::size_t find_first(std::size_t from, std::size_t to, bytes_evil_genius &prefix) const;

        long double upper_incomplete_gamma(unsigned s, long double x) const;

        std::size_t get_size_file(std::string filename) const;

        bytes_evil_genius _buffer;
        bytes_evil_genius _pattern;
    };

} //namespace non_overlapping_template_matching_test