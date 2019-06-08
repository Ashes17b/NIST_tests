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

void random_excursions_variant(const std::vector<bool>& sequence, std::vector<long double>& results)
{
    std::vector<size_t> counts(19);
    results.resize(18);
    long long state = 0;
    for (size_t i = 0; i < sequence.size(); ++i)
    {
        if (sequence[i])
        {
            ++state;
        }
        else
        {
            --state;
        }
        if (-9 <= state && state <= 9)
        {
            ++counts[state + 9];
        }
    }
    long double cycles = 1 + counts[9];
    for (size_t state = 9; state > 0; --state)
    {
        results[9 - state] = erfc(fabs(counts[9 - state] - cycles) / sqrt(cycles * ((state << 3) - 4)));
    }
    for (size_t state = 1; state < 10; ++state)
    {
        results[8 + state] = erfc(fabs(counts[9 + state] - cycles) / sqrt(cycles * ((state << 3) - 4)));
    }
}


int main()
{
    std::ios::sync_with_stdio(false);
    std::vector<bool> sequence;
    std::vector<long double> results;
    read_from_file(sequence, "input.in");
    std::ofstream fout("output.out");
    fout.setf(std::ios::fixed, std::ios::floatfield);
    fout.precision(5);
    random_excursions_variant(sequence, results);
    for (size_t i = 0; i < results.size(); ++i)
    {
        fout << results[i] << std::endl;
    }
    fout.close();
    return 0;
}
