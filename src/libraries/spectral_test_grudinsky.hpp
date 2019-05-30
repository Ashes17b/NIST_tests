#pragma once

#include "spectral_test.hpp"

namespace spectral_test {

    using bytes = double *;

    class Spectral_test_grudinsky : public Spectral_test {
    public:
        Spectral_test_grudinsky() = default;
        Spectral_test_grudinsky(const Spectral_test_grudinsky &spectral_test_grudinsky) = default;
        Spectral_test_grudinsky(Spectral_test_grudinsky &&spectral_test_grudinsky) = default;
        Spectral_test_grudinsky& operator=(const Spectral_test_grudinsky &spectral_test_grudinsky) = default;
        Spectral_test_grudinsky& operator=(Spectral_test_grudinsky &&spectral_test_grudinsky) = default;
        ~Spectral_test_grudinsky() = default;

        void read(std::string filename = "") override;

        double run_test() override;

    private:
        void dittt(int size);
        bytes _buffer;
        int numbers_of_bits;
        std::size_t get_size_file(std::string filename) const;
        double f(double x, double a);
        int largest_pow(int n);
    };
} //namespace spectral_test