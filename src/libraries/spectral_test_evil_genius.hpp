#pragma once

#include "spectral_test.hpp"

namespace spectral_test {

    using bytes_evil_genius = std::vector<int>;
    using base = std::complex<double>;

    class Spectral_test_evil_genius : public Spectral_test {
    public:
        Spectral_test_evil_genius() = default;
        Spectral_test_evil_genius(const Spectral_test_evil_genius &spectral_test_evil_genius) = default;
        Spectral_test_evil_genius(Spectral_test_evil_genius &&spectral_test_evil_genius) = default;
        Spectral_test_evil_genius& operator=(const Spectral_test_evil_genius &spectral_test_evil_genius) = default;
        Spectral_test_evil_genius& operator=(Spectral_test_evil_genius &&spectral_test_evil_genius) = default;
        ~Spectral_test_evil_genius() = default;

        void read(std::string filename = "") override;

        double run_test() override;

    private:
    
        std::vector<base> runFFT();
        std::vector<double> getModuls(const std::vector<base> &v);
        double getN1(const std::vector<double> &v, double T);
        void fft(std::vector<base> & a, bool invert); 
        void replaceZeros(std::vector<int> &v);
        
        std::size_t get_size_file(std::string filename) const;

        bytes_evil_genius _buffer;
        int numbers_of_bits;
    };
} //namespace runs_test