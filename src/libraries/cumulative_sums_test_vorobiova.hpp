#pragma once

#include "cumulative_sums_test.hpp"

namespace cumulative_sums_test {

    using bytes = std::vector<char>;

    class Cumulative_sums_test_vorobiova : public Cumulative_sums_test
    {
    public:
        Cumulative_sums_test_vorobiova() = default;
        Cumulative_sums_test_vorobiova(const Cumulative_sums_test_vorobiova &cumulative_sums_test_vorobiova) = default;
        Cumulative_sums_test_vorobiova(Cumulative_sums_test_vorobiova &&cumulative_sums_test_vorobiova) = default;
        Cumulative_sums_test_vorobiova& operator=(const Cumulative_sums_test_vorobiova &cumulative_sums_test_vorobiova) = default;
        Cumulative_sums_test_vorobiova& operator=(Cumulative_sums_test_vorobiova &&cumulative_sums_test_vorobiova) = default;
        ~Cumulative_sums_test_vorobiova() = default;

        void read(std::string filename = "") override;

        double run_test() const override;

    private:
    
        double cephes_normal(double x) const;
        double cumulative_sums(int n) const;

        bytes _buffer;
        int size;
    };  

} //namespace cumulative_sums_test