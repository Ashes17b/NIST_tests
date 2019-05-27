#include "runs_test_boltach.hpp"

namespace runs_test {

    void Runs_test_boltach::read() {
        std::ifstream f(_filename, std::ios::binary | std::ios::in);

        if (!f.is_open()) {
            std::cerr << "Could NOT find " + _filename << std::endl;
            return;
        }
    
        std::size_t size = f.tellg();
        _buffer.reserve(size);

        char c;
        while (f.get(c)) 
            for (int j = 7; j >= 0; --j)
                _buffer.emplace_back((((c >> j) & 1) * 2) - 1);

        f.close();
    }

    double Runs_test_boltach::run_test() const {
        assert(!_buffer.empty());

        auto n = _buffer.size();
        double tau = 2 / sqrt(_buffer.size());
        auto [pi, v] = count_v_and_ones();

        if (std::fabs(pi - 0.5) >= tau)
        {
            std::cerr << "|pi - 0.5| >= tau => the test is not run" << std::endl;
            return 0.0;
        }

        return erfc((std::fabs(v - 2.0 * n * pi * (1.0 - pi))) / (2.0 * sqrt(2.0 * n) * pi * (1.0 - pi)));
    }

    std::pair<double, uint64_t> Runs_test_boltach::count_v_and_ones() const {
        assert(!_buffer.empty());

        uint64_t v = 0;
        double countOnes = 0;

        for (std::size_t i = 0; i < _buffer.size(); ++i)
        {
            if (_buffer[i] != _buffer[i + 1] && i < _buffer.size() - 1)
                ++v;
            if (_buffer[i] == 1)
                ++countOnes;
        }

        return {countOnes / _buffer.size(), v + 1};
    }

} //namespace runs_test