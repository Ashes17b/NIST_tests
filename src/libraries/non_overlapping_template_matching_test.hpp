#pragma once

#include <iostream>
#include <sstream>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>

namespace non_overlapping_template_matching_test {

    class Non_overlapping_template_matching_test {
    public:
        Non_overlapping_template_matching_test() = default;

        virtual void read(std::string filename = "") = 0;

        virtual long double run_test(std::size_t number_of_blocks = 16, std::string __pattern = "000000001") const = 0;

        virtual ~Non_overlapping_template_matching_test() = default;
    };

} // namespace non_overlapping_template_matching_test