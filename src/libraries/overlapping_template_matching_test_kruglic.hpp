#pragma once

#include "overlapping_template_matching_test.hpp"

namespace overlapping_template_matching_test {

    using bytes = std::vector<uint8_t>;

    class Overlapping_template_matching_test_kruglic : public Overlapping_template_matching_test
    {
    public:
        Overlapping_template_matching_test_kruglic() = default;
        Overlapping_template_matching_test_kruglic(const Overlapping_template_matching_test_kruglic &overlapping_template_matching_test_kruglic) = default;
        Overlapping_template_matching_test_kruglic(Overlapping_template_matching_test_kruglic &&overlapping_template_matching_test_kruglic) = default;
        Overlapping_template_matching_test_kruglic& operator=(const Overlapping_template_matching_test_kruglic &overlapping_template_matching_test_kruglic) = default;
        Overlapping_template_matching_test_kruglic& operator=(Overlapping_template_matching_test_kruglic &&overlapping_template_matching_test_kruglic) = default;
        ~Overlapping_template_matching_test_kruglic() = default;

        void read(std::string filename = "") override;

        double run_test() const override;

    private:

        int Counter(int numberOfBlock, int blockSize) const;
        double Pi(int u, double eta) const;
        double MyIgamc(double chi2) const;
        double OverlappingTemplateMatchings() const;

        bytes _buffer;
        const int m = 13;
        int n;
        const int K = 5;
        const int M = pow(2., 14);
    };  

} //namespace overlapping_template_matching_test