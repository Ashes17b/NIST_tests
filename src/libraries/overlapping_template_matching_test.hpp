#pragma once

#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>

namespace overlapping_template_matching_test { 

    class Overlapping_template_matching_test {
    public:
        Overlapping_template_matching_test() = default;

        virtual void read(std::string filename = "") = 0;

        virtual double run_test() const = 0;

        virtual ~Overlapping_template_matching_test() = default;
    };

} // namespace overlapping_template_matching_test