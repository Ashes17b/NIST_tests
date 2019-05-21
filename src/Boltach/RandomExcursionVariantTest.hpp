#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>

namespace random_excursion_variant_test {

    template <typename Container>
    std::tuple< uint64_t, std::vector<int64_t> > build_the_partial_sum_and_J( const Container &bits )
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

    template< typename Container>
    double test( const Container &bits )
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