#include "../libraries/runs_test_timoshenko.hpp"

namespace runs_test {

    void Runs_test_timoshenko::read(std::string filename /* = "" */) {
        if (filename.empty())
            std::cerr << "Filename is undefined" << std::endl;
        else 
            std::cout << "Read from(Runs_test Timoshenko) " << filename << std::endl;
        
        std::ifstream f(filename, std::ios::binary | std::ios::in);

        if (!f.is_open()) {
            std::cerr << "Could NOT find " + filename << std::endl;
            return;
        }
    
        _buffer.reserve(get_size_file(filename));

        char c;
        while (f.get(c)) 
            for (int i = 7; i >= 0; --i)
                _buffer.emplace_back(((c >> i) & 1));

        f.close();
    }

    double Runs_test_timoshenko::run_test() const {
        std::cout << "Started performing runs_test Timoshenko" << std::endl;
        assert(!_buffer.empty());

        auto n = _buffer.size();
        double p_value = 0;
        
        std::pair<uint64_t, uint64_t> p = ones_V_counter();
        uint64_t ones = p.first;
        double pi = (double)ones / (double)n;
        // std::cout << "pi: " << pi << std::endl;

        double tau = 2 / sqrt(n);
        // std::cout << "tau: " << tau << std::endl;
        if ( fabs(pi - 0.5) >= tau ) {
            std::cout << "Prerequisite Frequency test is failed. Sequence is non-random" << std::endl;
            return p_value;
        }
        
        uint64_t V = p.second;
        // std::cout << "V: " << V << std::endl;

        p_value = erfc(fabs(V - 2.0 * (double)(n) * pi * (1.0 - pi)) /  (2.0 * pi * (1.0 - pi) * sqrt((double)(2*n))));

        return p_value;
    }

    std::pair<uint64_t, uint64_t> Runs_test_timoshenko::ones_V_counter() const {
        assert(!_buffer.empty());

        uint64_t ones = 0;
        uint64_t v = 1; 
        for ( int bit = 0; bit < _buffer.size(); bit++ ){
            if ( _buffer[bit] == 1 )
                ones++;
            if ( _buffer[bit] != _buffer[bit + 1] && _buffer.size() - 1)
                v++; 
        }

        return std::make_pair(ones, v);
    }
    
    std::size_t Runs_test_timoshenko::get_size_file(std::string filename) const {
        std::ifstream f(filename, std::ios::binary | std::ios::in | std::ifstream::ate);
        return f.tellg();
    }

} //namespace runs_test
