#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


void read_from_file(std::vector<bool>& sequence, const char* file_name)
{
    sequence.clear();
    std::ostringstream stream;
    std::ifstream fin(file_name, std::ios::binary);
    stream << fin.rdbuf();
    fin.close();
    std::string byte_sequence = stream.str();
    sequence.reserve(byte_sequence.length() << 3);
    for (size_t i = 0; i < byte_sequence.size(); ++i)
    {
        for (unsigned char mask = 128; mask > 0; mask >>= 1)
        {
            sequence.push_back(byte_sequence[i] & mask);
        }
    }
}

void prefix_function(const std::vector<bool>& pattern, std::vector<size_t>& result)
{
    result.assign(pattern.size(), 0);
    for (size_t i = 1; i < result.size(); ++i)
    {
        size_t border = result[i - 1];
        while (border > 0 && pattern[border] != pattern[i])
        {
            border = result[border - 1];
        }
        if (pattern[border] == pattern[i])
        {
            ++border;
        }
        result[i] = border;
    }
}

size_t find_first(const std::vector<bool>& sequence, size_t from, size_t to, const std::vector<bool>& pattern, const std::vector<size_t>& prefix)
{
    for (size_t matched_values = 0; from + pattern.size() <= to; )
    {
        while (matched_values < pattern.size() && sequence[from + matched_values] == pattern[matched_values])
        {
            ++matched_values;
        }
        if (matched_values == pattern.size())
        {
            return from;
        }
        if (matched_values > 0)
        {
            from += matched_values - prefix[matched_values - 1];
            matched_values = prefix[matched_values - 1];
        }
        else
        {
            ++from;
        }
    }
    return to;
}

long double upper_incomplete_gamma(unsigned s, long double x)
{
    unsigned s0;
    long double dividend, divisor;
    long double exp_x = exp(-x);
    if (s & 1)
    {
        s0 = 1;
        divisor = sqrt(atan(1.l) * 4.l);
        dividend = divisor * erfc(sqrt(x));
    }
    else
    {
        s0 = 2;
        dividend = exp_x;
        divisor = 1.l;
    }
    for (; s0 < s; s0 += 2)
    {
        dividend = fma(dividend, s0 / 2.l, pow(x, s0 / 2.l) * exp_x);
        divisor *= s0 / 2.l;
    }
    return dividend / divisor;
}

long double non_overlapping_template_matching(const std::vector<bool>& sequence, const std::vector<bool>& pattern, size_t number_of_blocks)
{
    size_t block_size = sequence.size() / number_of_blocks;
    long double chi2 = 0.l;
    long double mean = (block_size - pattern.size() + 1.l) / (1 << pattern.size());
    long double variance = block_size * (1.l / (1 << pattern.size()) - ((pattern.size() << 1) - 1.l) / (1 << (pattern.size() << 1)));
    std::vector<size_t> prefix;
    prefix_function(pattern, prefix);
    for (size_t from = 0, to = block_size; to <= sequence.size(); to += block_size)
    {
        size_t occurences = 0;
        from = find_first(sequence, from, to, pattern, prefix);
        while (from < to)
        {
            ++occurences;
            from = find_first(sequence, from + pattern.size(), to, pattern, prefix);
        }
        chi2 += pow(occurences - mean, 2.l) / variance;
    }
    return upper_incomplete_gamma(number_of_blocks, chi2 / 2.l);
}


int main()
{
    std::ios::sync_with_stdio(false);
    std::vector<bool> sequence;
    std::vector<bool> pattern(9);
    pattern.back() = true;
    read_from_file(sequence, "input.in");
    std::ofstream fout("output.out");
    fout.setf(std::ios::fixed, std::ios::floatfield);
    fout.precision(5);
    fout << non_overlapping_template_matching(sequence, pattern, 64) << std::endl;
    fout.close();
    return 0;
}
