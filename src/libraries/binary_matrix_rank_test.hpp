#pragma once

#include <iostream>
#include <complex>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <chrono>

namespace binary_matrix_rank_test { 

    class Binary_matrix_rank_test {
    public:
        Binary_matrix_rank_test() = default;

        virtual void read(std::string filename = "") = 0;

        virtual double run_test(int M = 32, int Q = 32) const = 0;

        virtual ~Binary_matrix_rank_test() = default;
    };

} // namespace binary_matrix_rank_test
