#pragma once

#define _USE_MATH_DEFINES
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>
#include <cstdlib>

namespace longest_runs_test {

    class Longest_runs_test {
    public:
        Longest_runs_test() = default;

        virtual void read(std::string filename = "") = 0;

        virtual double run_test() const = 0;

        virtual ~Longest_runs_test() = default;
    };

} // namespace longest_runs_test