#pragma once

#include "random_excursions_test.hpp"

namespace random_excursions_test {

    using bytes = std::vector<uint8_t>;

    class Random_excursions_test_timoshenko : public Random_excursions_test
    {
    public:
        Random_excursions_test_timoshenko() = default;
        Random_excursions_test_timoshenko(const Random_excursions_test_timoshenko &Random_excursions_test_timoshenko) = default;
        Random_excursions_test_timoshenko(Random_excursions_test_timoshenko &&Random_excursions_test_timoshenko) = default;
        Random_excursions_test_timoshenko &operator=(const Random_excursions_test_timoshenko &Random_excursions_test_timoshenko) = default;
        Random_excursions_test_timoshenko &operator=(Random_excursions_test_timoshenko &&Random_excursions_test_timoshenko) = default;
        ~Random_excursions_test_timoshenko() = default;

        void read(std::string filename = "") override;

        double run_test() const override;

    private:
        std::size_t get_size_file(std::string filename) const;
        
        bytes _buffer;
    };

} //namespace random_excursions_test