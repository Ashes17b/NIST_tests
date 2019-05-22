#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

namespace runs_test {

    void run(std::string filename) 
    {
        std::ifstream f(filename, std::ios::binary | std::ios::in);

        if (!f.is_open())
        {
            std::cerr << "Could NOT find " + filename << std::endl;
            return;
        }

        std::vector<int8_t> buffer;

        char c;
        while (f.get(c))
            for (int i = 7; i >= 0; --i)
                buffer.push_back((((c >> i) & 1) * 2) - 1);

        f.close();

        std::cout << filename + ": ";
        printf("P-value runs_test: %.8f\n", runs_test::test(buffer));
        std::cout << std::endl;
    }

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
    std::pair<double, uint64_t> count_v_and_ones( const std::vector<uint8_t> &bits )
    {
        uint64_t v = 0;
        double countOnes = 0;

        for ( size_t i = 0; i < bits.size(); ++i )
        {
            if ( bits[i] != bits[i + 1] && i < bits.size() - 1 )
                ++v;
            if ( bits[i] == 1 )
                ++countOnes;
        }

        return { countOnes / bits.size(), v + 1 };
    }

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
    double test( const std::vector<uint8_t> &bits ) 
    {
        uint64_t n = bits.size();
        double tau = 2 / sqrt( n );
        auto [ pi, v ] = count_v_and_ones( bits );

        if ( std::fabs(pi - 0.5) >= tau ) 
        {
            std::cerr << "|pi - 0.5| >= tau => the test is not run" << std::endl;
            return 0.0;
        }

        return erfc( ( std::fabs( v - 2.0 * n * pi * (1.0 - pi) ) ) / ( 2.0 * sqrt( 2.0 * n ) * pi * ( 1.0 - pi ) ) ) ;
    }

}//namespace runs_test