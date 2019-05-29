#pragma once

#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>

namespace serial_test {

    class Serial_test {
    public:

        Serial_test() = default;

        virtual void read(std::string filename = "") = 0;

        virtual std::pair<double, double> run_test() const = 0;

        virtual ~Serial_test() = default;
    };

} // namespace serial_test