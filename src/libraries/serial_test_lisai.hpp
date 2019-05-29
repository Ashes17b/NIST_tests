#pragma once

#include "serial_test.hpp"
#include "cephes.h"

namespace serial_test {

    using bytes = std::vector<uint8_t>;

    class Serial_test_lisai : public Serial_test {        
    public:
        Serial_test_lisai() = default;
        Serial_test_lisai(const Serial_test_lisai &serial_test_lisai) = default;
        Serial_test_lisai(Serial_test_lisai &&serial_test_lisai) = default;
        Serial_test_lisai& operator=(const Serial_test_lisai &serial_test_lisai) = default;
        Serial_test_lisai& operator=(Serial_test_lisai &&serial_test_lisai) = default;
        ~Serial_test_lisai() = default;

        void read(std::string filename = "") override;

        /**
         * This will be some about Serial Test (maybe, or not)
         * 
        */
        std::pair<double, double> run_test() const override;

    private:
        /**
         * Calculate some important things
         * 
        */
        double psi2(bytes epsilon, int m, int n) const;
        
        std::size_t get_size_file(std::string filename) const;

        bytes _buffer;
    };  

} //namespace runs_test