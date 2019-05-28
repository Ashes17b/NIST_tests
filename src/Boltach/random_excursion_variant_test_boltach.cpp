#include "../libraries/random_excursion_variant_test_boltach.hpp"

namespace random_excursion_variant_test {

    void Random_excursion_variant_test_boltach::read(std::string filename /* = "" */) {
        if (filename.empty())
            std::cerr << "Filename is undefined" << std::endl;
        else
            std::cout << "Read from(Runs_test Boltach) " << filename << std::endl;

        std::ifstream f(filename, std::ios::binary | std::ios::in);

        if (!f.is_open()) {
            std::cerr << "Could NOT find " + filename << std::endl;
            return;
        }

        std::size_t size = f.tellg();
        _buffer.reserve(size);

        char c;
        while (f.get(c))
            for (int j = 7; j >= 0; --j)
                _buffer.emplace_back(((c >> j) & 1));

        f.close();
    }

    double Random_excursion_variant_test_boltach::run_test() const {
        std::cout << "Started performing runs_test Boltach" << std::endl;
        assert(!_buffer.empty());

        const std::pair<uint64_t, std::vector<int64_t> > &J_count = build_the_partial_sum_and_J();

        double p_value, min_p_value = 1;

        if (J_count.first < 500) {
            std::cerr << "J < 500 => sequence not random" << std::endl;
            return 0.0;
        }

        for (int i = -9; i < 10; ++i) {
            if (i == 0)
                continue;

            int numerator = std::fabs(J_count.second[i < 0 ? J_count.second.size() + i : i] - J_count.first);
            auto denominator = sqrt(2.0 * J_count.first * ((4.0 * std::fabs(i)) - 2));

            p_value = erfc(numerator / denominator);

            if (p_value < 0.01) {
                std::cerr << "p_value < 0.01 => sequence not random" << std::endl;
                return 0.0;
            }

            if (min_p_value > p_value)
                min_p_value = p_value;
        }

        return min_p_value;
    }

    std::pair<uint64_t, std::vector<int64_t> > Random_excursion_variant_test_boltach::build_the_partial_sum_and_J() const
    {
        std::vector<int64_t> count(19, 0);
        int64_t sum = 0;
        uint64_t J = 0;

        for (size_t i = 0; i < _buffer.size(); ++i)
        {
            sum += _buffer[i];

            if (sum == 0)
                ++J;

            if (fabs(sum) < 10)
                ++count[sum < 0 ? count.size() + sum : sum];
        }
        if (_buffer[_buffer.size() - 1])
            ++J;
        count[0] += 2;

        return std::make_pair(J, count);
        }

} //namespace random_excursion_variant_test