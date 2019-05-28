#include "../libraries/runs_test_boltach.hpp"

namespace runs_test {

    void Runs_test_boltach::read(std::string filename /* = "" */)
    {
        if (filename.empty())
            std::cerr << "Filename is undefined" << std::endl;
        else
            std::cout << "Read from(Runs_test Boltach) " << filename << std::endl;

        std::ifstream f(filename, std::ios::binary | std::ios::in);

        if (!f.is_open()) {
            std::cerr << "Could NOT find " + filename << std::endl;
            return;
        }

        _buffer.reserve(get_size_file(filename));

        char c;
        while (f.get(c))
            for (int i = 7; i >= 0; --i)
                _buffer.push_back((c >> i) & 1);

        f.close();
    }

    double Runs_test_boltach::run_test() const {
        std::cout << "Started performing runs_test Boltach" << std::endl;
        assert(!_buffer.empty());

        auto n = _buffer.size();
        double tau = 2 / sqrt(_buffer.size());
        std::pair<double, double> pi_v = count_v_and_ones();

        if (std::fabs(pi_v.first - 0.5) >= tau) {
            std::cerr << "|pi - 0.5| >= tau => the test is not run" << std::endl;
            return 0.0;
        }

        return erfc((std::fabs(pi_v.second - 2.0 * n * pi_v.first * (1.0 - pi_v.first))) / (2.0 * sqrt(2.0 * n) * pi_v.first * (1.0 - pi_v.first)));
    }

    std::pair<double, uint64_t> Runs_test_boltach::count_v_and_ones() const {
        uint64_t v = 0;
        double countOnes = 0;

        for (std::size_t i = 0; i < _buffer.size(); ++i) {
            if (_buffer[i] != _buffer[i + 1] && i < _buffer.size() - 1)
                ++v;
            if (_buffer[i] == 1)
                ++countOnes;
        }

        return std::make_pair(countOnes / _buffer.size(), v + 1);
    }

    std::size_t Runs_test_boltach::get_size_file(std::string filename) const {
        std::ifstream f(filename, std::ios::binary | std::ios::in | std::ifstream::ate);
        return f.tellg();
    }

} //namespace runs_test