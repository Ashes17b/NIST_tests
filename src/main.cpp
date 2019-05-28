#include "libraries/tests.hpp"

using namespace runs_test;
using namespace random_excursion_variant_test;

int main()
{
    std::cout << "----------------------------------------------------------------------" << std::endl;

    Runs_test_boltach r_test_boltach;

    auto t1 = std::chrono::high_resolution_clock::now();
    r_test_boltach.read("../seq/seq8.bin");
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    auto p_value = r_test_boltach.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    auto duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value runs_test: %.8f\n", p_value);

    std::cout << "----------------------------------------------------------------------" << std::endl;

    Random_excursion_variant_test_boltach r_e_v_test_boltach;

    t1 = std::chrono::high_resolution_clock::now();
    r_e_v_test_boltach.read("../seq/seq8.bin");
    t2 = std::chrono::high_resolution_clock::now();

    duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    p_value = r_e_v_test_boltach.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value runs_test: %.8f\n", p_value);

    std::cout << "----------------------------------------------------------------------" << std::endl;

    return 0;
}