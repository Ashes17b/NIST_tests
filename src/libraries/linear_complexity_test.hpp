#pragma once

#define _USE_MATH_DEFINES
#define M 50
#define K 6

#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>
#include <cstdlib>

namespace linear_complexity_test {

    class Linear_complexity_test {
    public:
        Linear_complexity_test() = default;

        virtual void read(std::string filename = "") = 0;

        virtual double run_test() const = 0;

        virtual ~Linear_complexity_test() = default;
    };

} // namespace linear_complexity_test