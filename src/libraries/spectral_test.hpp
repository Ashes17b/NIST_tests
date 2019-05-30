#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>
#include <cassert>
#include <iterator>
#include <complex>
#include <algorithm>

namespace spectral_test {

    class Spectral_test {
    public:

        Spectral_test() = default;

        virtual void read(std::string filename = "") = 0;

        virtual double run_test() = 0;

        virtual ~Spectral_test() = default;
    };

} // namespace spectral_test