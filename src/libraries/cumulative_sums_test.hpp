#pragma once

#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>

namespace cumulative_sums_test { 

    class Cumulative_sums_test {
    public:
        Cumulative_sums_test() = default;

        virtual void read(std::string filename = "") = 0;

        virtual double run_test() const = 0;

        virtual ~Cumulative_sums_test() = default;
    };

} // namespace cumulative_sums_test