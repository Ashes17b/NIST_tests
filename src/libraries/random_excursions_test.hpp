#pragma once

#define _USE_MATH_DEFINES
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>

namespace random_excursions_test {

    class Random_excursions_test {
    public:
        Random_excursions_test() = default;

        virtual void read(std::string filename = "") = 0;

        virtual double run_test() const = 0;

        virtual ~Random_excursions_test() = default;
    };

} // namespace random_excursions_test