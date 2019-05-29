#pragma once

#include "approximate_entropy_test.hpp"

namespace approximate_entropy_test {

    using bytes = std::vector<uint8_t>;

    class Approximate_entropy_test_grudinsky : public Approximate_entropy_test {
    private:
        std::string _filename;
    
    public:
        Approximate_entropy_test_grudinsky() = default;
        Approximate_entropy_test_grudinsky(const Approximate_entropy_test_grudinsky &approximate_entropy_test_grudinsky) = default;
        Approximate_entropy_test_grudinsky(Approximate_entropy_test_grudinsky &&approximate_entropy_test_grudinsky) = default;
        Approximate_entropy_test_grudinsky& operator=(const Approximate_entropy_test_grudinsky &approximate_entropy_test_grudinsky) = default;
        Approximate_entropy_test_grudinsky& operator=(Approximate_entropy_test_grudinsky &&approximate_entropy_test_grudinsky) = default;
        ~Approximate_entropy_test_grudinsky() = default;

        void read(std::string filename = "") override;

        double run_test() override;

    private:
        void dittt(int size);
        bytes _buffer;
        int numbers_of_bytes;
        std::size_t get_size_file(std::string filename) const;
        double f(double x, double a);
        int largest_pow(int n);
        int param_m = 4;
    };
} //namespace approximate_entropy_test