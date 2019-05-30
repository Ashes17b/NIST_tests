#pragma once

#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>

namespace maurers_test { 

    class Maurers_test {
    public:
        Maurers_test() = default;

        virtual void read(std::string filename = "") = 0;

        virtual double run_test() const = 0;

        virtual ~Maurers_test() = default;
    };

} // namespace maurers_test