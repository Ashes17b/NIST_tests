#pragma once

#include "maurers_test.hpp"

namespace maurers_test {

    using bytes = std::vector<uint8_t>;

    class Maurers_test_kruglic : public Maurers_test
    {
    public:
        Maurers_test_kruglic() = default;
        Maurers_test_kruglic(const Maurers_test_kruglic &maurers_test_kruglic) = default;
        Maurers_test_kruglic(Maurers_test_kruglic &&maurers_test_kruglic) = default;
        Maurers_test_kruglic& operator=(const Maurers_test_kruglic &maurers_test_kruglic) = default;
        Maurers_test_kruglic& operator=(Maurers_test_kruglic &&maurers_test_kruglic) = default;
        ~Maurers_test_kruglic() = default;

        void read(std::string filename = "") override;

        double run_test() const override;

    private:
    
        void ChooseL(int& L, int& Q, double& expectedValue, double& variance) const;
        std::vector<int> Initialize(int L, int Q) const;
        double Examine(int K, std::vector<int>& T, int L, int Q) const;
        double Pvalue(double fn, int K, int L, double expectedValue, double variance) const;
        double Universal() const;

        bytes _buffer;
        int n = 0;
    };  

} //namespace maurers_test