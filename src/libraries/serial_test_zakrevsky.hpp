#pragma once

#include "serial_test.hpp"
#include "cephes.h"

namespace serial_test {

    using bytes = std::vector<uint8_t>;

    class Serial_test_zakrevsky : public Serial_test {        
    public:
        Serial_test_zakrevsky() = default;
        Serial_test_zakrevsky(const Serial_test_zakrevsky &serial_test_zakrevsky) = default;
        Serial_test_zakrevsky(Serial_test_zakrevsky &&serial_test_zakrevsky) = default;
        Serial_test_zakrevsky& operator=(const Serial_test_zakrevsky &serial_test_zakrevsky) = default;
        Serial_test_zakrevsky& operator=(Serial_test_zakrevsky &&serial_test_zakrevsky) = default;
        ~Serial_test_zakrevsky() = default;

        void read(std::string filename = "") override;

        std::pair<double, double> run_test() const override;

    private:
        void counter(int m, int* temp, int n, int w) const;
        std::size_t get_size_file(std::string filename) const;

        bytes _buffer;
        int numbers_of_bits;
        int param_m = 2;
    };  

} //namespace serial_test