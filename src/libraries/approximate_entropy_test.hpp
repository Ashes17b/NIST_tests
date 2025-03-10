#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>
#include <cassert>

namespace approximate_entropy_test {

    class Approximate_entropy_test {
    public:

        Approximate_entropy_test() = default;

        virtual void read(std::string filename = "", int param_m = 4) = 0;

        virtual double run_test(int param_m = 4) = 0;

        virtual ~Approximate_entropy_test() = default;
    };

} // namespace approximate_entropy_test