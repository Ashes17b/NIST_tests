#pragma once

#include "random_excursion_variant_test.hpp"

namespace random_excursion_variant_test {

    using bytes = std::vector<uint8_t>;

    class Random_excursion_variant_test_boltach : public Random_excursion_variant_test
    {
    public:
        Random_excursion_variant_test_boltach() = default;
        Random_excursion_variant_test_boltach(const Random_excursion_variant_test_boltach &Random_excursion_variant_test_boltach) = default;
        Random_excursion_variant_test_boltach(Random_excursion_variant_test_boltach &&Random_excursion_variant_test_boltach) = default;
        Random_excursion_variant_test_boltach &operator=(const Random_excursion_variant_test_boltach &Random_excursion_variant_test_boltach) = default;
        Random_excursion_variant_test_boltach &operator=(Random_excursion_variant_test_boltach &&Random_excursion_variant_test_boltach) = default;
        ~Random_excursion_variant_test_boltach() = default;

        void read(std::string filename = "") override;

        double run_test() const override;

    private:
        std::pair<uint64_t, std::vector<int64_t> > build_the_partial_sum_and_J() const;

        bytes _buffer;
    };

} //namespace random_excursion_variant_test