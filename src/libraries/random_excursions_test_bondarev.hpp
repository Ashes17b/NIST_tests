#pragma once

#include "random_excursions_test.hpp"

namespace random_excursions_test {

    using bytes = std::vector<uint8_t>;

    class Random_excursions_test_bondarev : public Random_excursions_test
    {
    public:
        Random_excursions_test_bondarev() = default;
        Random_excursions_test_bondarev(const Random_excursions_test_bondarev &Random_excursions_test_bondarev) = default;
        Random_excursions_test_bondarev(Random_excursions_test_bondarev &&Random_excursions_test_bondarev) = default;
        Random_excursions_test_bondarev &operator=(const Random_excursions_test_bondarev &Random_excursions_test_bondarev) = default;
        Random_excursions_test_bondarev &operator=(Random_excursions_test_bondarev &&Random_excursions_test_bondarev) = default;
        ~Random_excursions_test_bondarev() = default;

        void read(std::string filename = "") override;

        double run_test() const override;

    private:
        std::size_t get_size_file(std::string filename) const;

        double igamc_c(int K, double chi2) const;
        
        bytes _buffer;
    };

} //namespace random_excursions_test