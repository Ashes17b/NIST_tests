#pragma once

#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>

namespace random_excursion_variant_test {

    class Random_excursion_variant_test {
    public:
        Random_excursion_variant_test() = default;

        virtual void read(std::string filename = "") = 0;

        virtual double run_test() const = 0;

        virtual ~Random_excursion_variant_test() = default;
    };

} // namespace random_excursion_variant_test