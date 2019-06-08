#include "../libraries/non_overlapping_template_matching_test_evil_genius.hpp"

namespace non_overlapping_template_matching_test {

    void Non_overlapping_template_matching_test_evil_genius::read(std::string filename /* = "" */) {
        if (filename.empty())
            std::cerr << "Filename is undefined" << std::endl;
        else
            std::cout << "Read from(Non_overlapping_template_matching_test Evil_genius) " << filename << std::endl;

        std::ostringstream stream;
        std::ifstream f(filename, std::ios::binary | std::ios::in);

        if (!f.is_open()) {
            std::cerr << "Could NOT find " + filename << std::endl;
            return;
        }

        stream << f.rdbuf();
        f.close();

        std::string byte_sequence = stream.str();
        _buffer.reserve(byte_sequence.length() << 3);
        for (size_t i = 0; i < byte_sequence.size(); ++i)
            for (unsigned char mask = 128; mask > 0; mask >>= 1)
                _buffer.push_back(byte_sequence[i] & mask);

    }

    long double Non_overlapping_template_matching_test_evil_genius::run_test(std::size_t number_of_blocks /* = 16 */, std::string _pattern /*= "000000001"  */) const {
        std::cout << "Started performing non_overlapping_template_matching_test Evil_genius" << std::endl;
        assert(!_buffer.empty());
        assert(!_pattern.empty());

        size_t block_size = _buffer.size() / number_of_blocks;
        long double chi2 = 0.l;
        long double mean = (block_size - _pattern.size() + 1.l) / (1 << _pattern.size());
        long double variance = block_size * (1.l / (1 << _pattern.size()) - ((_pattern.size() << 1) - 1.l) / (1 << (_pattern.size() << 1)));
        
        bytes_evil_genius prefix;
        prefix_function(prefix);

        for (size_t from = 0, to = block_size; to <= _buffer.size(); to += block_size) {
            size_t occurences = 0;
            from = find_first(from, to, prefix);
            while (from < to) {
                ++occurences;
                from = find_first(from + _pattern.size(), to, prefix);
            }
            chi2 += pow(occurences - mean, 2.l) / variance;
        }
        return upper_incomplete_gamma(number_of_blocks, chi2 / 2.l);
    }

    void Non_overlapping_template_matching_test_evil_genius::prefix_function(bytes_evil_genius &prefix) const {
        prefix.assign(_pattern.size(), 0);

        for (size_t i = 1; i < prefix.size(); ++i) {
            size_t border = prefix[i - 1];
            while (border > 0 && _pattern[border] != _pattern[i])
                border = prefix[border - 1];
            
            if (_pattern[border] == _pattern[i])
                ++border;
            
            prefix[i] = border;
        }
    }

    std::size_t Non_overlapping_template_matching_test_evil_genius::find_first(std::size_t from, std::size_t to, bytes_evil_genius &prefix) const {
        for (size_t matched_values = 0; from + _pattern.size() <= to;) {
        
            while (matched_values < _pattern.size() && _buffer[from + matched_values] == _pattern[matched_values]) 
                ++matched_values;
            
            if (matched_values == _pattern.size()) 
                return from;
            
            if (matched_values > 0) {
                from += matched_values - prefix[matched_values - 1];
                matched_values = prefix[matched_values - 1];
            }
            else 
                ++from;
        }
        return to;
    }

    long double Non_overlapping_template_matching_test_evil_genius::upper_incomplete_gamma(unsigned s, long double x) const {
        unsigned s0;
        long double dividend, divisor;
        long double exp_x = exp(-x);
        if (s & 1) {
            s0 = 1;
            divisor = sqrt(atan(1.l) * 4.l);
            dividend = divisor * erfc(sqrt(x));
        }
        else {
            s0 = 2;
            dividend = exp_x;
            divisor = 1.l;
        }
        for (; s0 < s; s0 += 2) {
            dividend = fma(dividend, s0 / 2.l, pow(x, s0 / 2.l) * exp_x);
            divisor *= s0 / 2.l;
        }
        return dividend / divisor;
    }

    std::size_t Non_overlapping_template_matching_test_evil_genius::get_size_file(std::string filename) const {
        std::ifstream f(filename, std::ios::binary | std::ios::in | std::ifstream::ate);
        return f.tellg();
    }

} //namespace non_overlapping_template_matching_test_evil_genius
