#pragma once

#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>

namespace runs_test { 

    class Runs_test {
    public:
        Runs_test() = default;

        virtual void read(std::string filename = "") = 0;

        virtual double run_test() const = 0;

        virtual ~Runs_test() = default;
    };

} // namespace runs_test