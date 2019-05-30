#pragma once

#include "longest_runs_test.hpp"

namespace longest_runs_test {

    using bytes = std::vector<uint8_t>;

    class Longest_runs_test_bondarev : public Longest_runs_test
    {
    public:
        Longest_runs_test_bondarev() = default;
        Longest_runs_test_bondarev(const Longest_runs_test_bondarev &Longest_runs_test_bondarev) = default;
        Longest_runs_test_bondarev(Longest_runs_test_bondarev &&Longest_runs_test_bondarev) = default;
        Longest_runs_test_bondarev &operator=(const Longest_runs_test_bondarev &Longest_runs_test_bondarev) = default;
        Longest_runs_test_bondarev &operator=(Longest_runs_test_bondarev &&Longest_runs_test_bondarev) = default;
        ~Longest_runs_test_bondarev() = default;

        void read(std::string filename = "") override;

        double run_test() const override;

    private:
        std::size_t get_size_file(std::string filename) const;

        double igamc_c(int K, double chi2) const;
        
        bytes _buffer;
    };

} //namespace longest_runs_test