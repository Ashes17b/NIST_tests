#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

namespace random_excursion_variant_test {

    void run(const std::string filename)
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
                buffer.push_back(((c >> i) & 1));

        f.close();

        std::cout << filename + ": ";
        printf("P-value random_excursion_variant_test: %.8f\n", random_excursion_variant_test::test(buffer));
        std::cout << std::endl;
    }

    std::pair< uint64_t, std::vector<int64_t> > build_the_partial_sum_and_J( const std::vector<uint8_t> &bits )
    {
        std::vector<int64_t> count(19, 0);
        int64_t sum = 0;
        uint64_t J = 0;

        for ( size_t i = 0; i < bits.size(); ++i )
        {
            sum += bits[i];
            
            if ( sum == 0 )
                ++J;

            if ( fabs(sum) < 10 )
                ++count[sum < 0 ? count.size() + sum : sum];
        }
        if ( bits[bits.size() - 1] )
            ++J;
        count[0] += 2;

        return { J, count };
    }

    double test( const std::vector<uint8_t> &bits )
    {
        const auto &[J, count] = build_the_partial_sum_and_J( bits );

        double p_value, min_p_value = 1;

        if ( J < 500 )
        {
            std::cerr << "J < 500 => sequence not random" << std::endl;
            return 0.0;
        }

        for ( int i = -9; i < 10; ++i )
        {
            if ( i == 0 )
                continue;

            int numerator = std::fabs(count[i < 0 ? count.size() + i : i] - J);
            auto denominator = sqrt(2.0 * J * ( ( 4.0 * std::fabs(i) ) - 2) );
            
            p_value =  erfc( numerator / denominator );

            if ( p_value < 0.01 )
            {
                std::cerr << "p_value < 0.01 => sequence not random" << std::endl;
                return 0.0;
            }

            if ( min_p_value > p_value )
                min_p_value = p_value;
        }

        return min_p_value;
    }

} //namespace random_excursion_variant_test