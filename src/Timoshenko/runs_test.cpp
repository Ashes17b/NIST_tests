#include <fstream>
#include <iterator>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <cmath>
#include <ctime>
#include <algorithm>


using namespace std;


uint64_t count_ones( const vector<int8_t> &bits ) 
{
    uint64_t count = 0;
    for ( int bit = 0; bit < bits.size(); bit++ )
        if ( bits[bit] == 1 )
            count++; 

    return count;
}

pair<uint64_t, uint64_t> ones_V_counter( const vector<int8_t> &bits ) 
{
    uint64_t ones = 0;
    uint64_t v = 1; 
    for ( int bit = 0; bit < bits.size(); bit++ ){
        if ( bits[bit] == 1 )
            ones++;
        if ( bits[bit] != bits[bit + 1] && bits.size() - 1)
            v++; 
    }

    return make_pair(ones, v);
}

uint64_t count_V( const vector<int8_t> &bits ) 
{
    uint64_t V = 0;
    for ( int bit = 0; bit < bits.size() - 1; bit++ )
        if ( bits[bit] != bits[bit + 1] )
            V++; 

    return V;
}

vector<int8_t> read_file( string filename )
{
    ifstream f(filename, ios::binary | ios::in);
    char c;
    vector<int8_t> bits;

    while (f.get(c)){
        for ( auto i = 7; i >= 0; --i ) 
            bits.push_back(((c >> i) & 1));
    }
    f.close();

    return bits;
}

double runs_test( const vector<int8_t> &bits ) 
{
    try
    {
        clock_t t_start = clock();
        uint64_t n = bits.size();
        double p_value = 0;
        
        pair<uint64_t, uint64_t> p = ones_V_counter(bits);
        uint64_t ones = p.first;
        double pi = (double)ones / (double)n;
        cout << "pi: " << pi << endl;

        double tau = 2 / sqrt(n);
        cout << "tau: " << tau << endl;
        if ( fabs(pi - 0.5) >= tau ) {
            cout << "Prerequisite Frequency test is failed. Sequence is non-random" << endl;
            printf("Time taken: %.2fs\n", (double)(clock() - t_start) / CLOCKS_PER_SEC);
            return p_value;
        }
        
        uint64_t V = p.second;
        cout << "V: " << V << endl;

        p_value = erfc(fabs(V - 2.0 * (double)(n) * pi * (1.0 - pi)) /  (2.0 * pi * (1.0 - pi) * sqrt((double)(2*n))));

        printf("Time taken: %.2fs\n", (double)(clock() - t_start) / CLOCKS_PER_SEC);

        return p_value;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}


int main()
{
    for ( int i = 1; i < 9; i++ ) {
        string filename ="seq/seq" + to_string(i) + ".bin";
        vector<int8_t> bits = read_file(filename);
        cout << "\nSeq " << i << endl;
        cout << "Runs test: " << endl;
        cout << "p_value: " << runs_test(bits) << endl;
    }

    // vector<int8_t> bits = read_file("seq/seq8.bin");
    // random_excursions_test(bits);

    // int count = 0;
    // for (const auto &i: bits ) {
    //     cout << (int)i;
    //     if ( count > 100 )
    //         break;
    //     count++;
    // }
    // cout << endl;
    return 0;
}