#pragma once

#include "spectral_test.hpp"

namespace spectral_test {

    using bytes_vecherko = std::vector<int>;
    using base = std::complex<double>;

    class Spectral_test_vecherko : public Spectral_test {
    public:
        Spectral_test_vecherko() = default;
        Spectral_test_vecherko(const Spectral_test_vecherko &spectral_test_vecherko) = default;
        Spectral_test_vecherko(Spectral_test_vecherko &&spectral_test_vecherko) = default;
        Spectral_test_vecherko& operator=(const Spectral_test_vecherko &spectral_test_vecherko) = default;
        Spectral_test_vecherko& operator=(Spectral_test_vecherko &&spectral_test_vecherko) = default;
        ~Spectral_test_vecherko() = default;

        void read(std::string filename = "") override;

        double run_test() override;

    private:
    
        std::vector<base> runFFT();
        std::vector<double> getModuls(const std::vector<base> &v);
        double getN1(const std::vector<double> &v, double T);
        void fft(std::vector<base> & a, bool invert); 
        void replaceZeros(std::vector<int> &v);
        
        std::size_t get_size_file(std::string filename) const;

        bytes_vecherko _buffer;
        int numbers_of_bits;
    };
} //namespace runs_test