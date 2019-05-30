#pragma once

#include "spectral_test.hpp"

namespace spectral_test {

    using bytes = double *;

    class Spectral_test_lisai : public Spectral_test {
    public:
        Spectral_test_lisai() = default;
        Spectral_test_lisai(const Spectral_test_lisai &spectral_test_lisai) = default;
        Spectral_test_lisai(Spectral_test_lisai &&spectral_test_lisai) = default;
        Spectral_test_lisai& operator=(const Spectral_test_lisai &spectral_test_lisai) = default;
        Spectral_test_lisai& operator=(Spectral_test_lisai &&spectral_test_lisai) = default;
        ~Spectral_test_lisai() = default;

        void read(std::string filename = "") override;

        double run_test() override;

    private:
        void dittt(int size);
        double test_result(int n);
        bytes _buffer;
        int numbers_of_bits;
        std::size_t get_size_file(std::string filename) const;
    };
} //namespace spectral_test