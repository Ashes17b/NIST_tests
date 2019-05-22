#include "runs_test.hpp"
#include "random_excursion_variant_test.hpp"

int main()
{
    runs_test::run("../seq/seq1.bin");
    
    random_excursion_variant_test::run("../seq/seq1.bin");

    return 0;
}