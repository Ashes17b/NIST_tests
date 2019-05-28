#pragma once

#include "runs_test.hpp"

namespace runs_test {

    using bytes = std::vector<uint8_t>;

    class Runs_test_boltach : public Runs_test
    {
        public:
            Runs_test_boltach() = default;
            Runs_test_boltach(const Runs_test_boltach &runs_test_boltach) = default;
            Runs_test_boltach(Runs_test_boltach &&runs_test_boltach) = default;
            Runs_test_boltach& operator=(const Runs_test_boltach &runs_test_boltach) = default;
            Runs_test_boltach& operator=(Runs_test_boltach &&runs_test_boltach) = default;
            ~Runs_test_boltach() = default;

            void read(std::string filename = "") override;

            /**
             * Determine if the prerequisite Frequency test is passed: If it can be shown that |pi - 0.5| >= tau, then the
             * Runs test need not be performed (i. e., the test should not have been run because of a failure to
             * pass test 1, the Frequency (Monobit) test). If the test is not applicable, then the P-value is set to 0.0000.
             * Note that for this test, tau = 2 / sqrt( pi ) has been pre-defined in the test code.
             * 
             * For the example in this section, since tau = 2 / sqrt( 10 ) ~ 0.63246, then |pi - 0.5| = 0.1 < tau, 
             * and the test is not run.
             * 
             * Since the observed value pi is within the selected bounds, the runs test is applicable.
            */
            double run_test() const override;

        private:
            /**
             * Compute the pre-test proportion pi of ones in the input sequence
             * For example, if seq = 1001101011, then n = 10 and pi = 6 / 10 = 3 / 5.
             * 
             * Compute the test statistic V_{ n }(obs) = sum_{ i }( r(k) ) + 1, where i = { 0,...,n - 1 }
             * r(k) = 0 if bit_{ k } = bit_{ k + 1 }, and r(k) = 1 otherwise.
             * 
             * Since bits = 1001101011, then
             *                 V_{ n }(obs) = ( 1 + 0 + 1 + 0 + 1 + 1 + 1 + 1 + 0 ) + 1 = 7.
            */
            std::pair<double, uint64_t> count_v_and_ones() const;

            bytes _buffer;
    };  

} //namespace runs_test