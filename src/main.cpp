#include "libraries/tests.hpp"

using namespace runs_test;
using namespace random_excursion_variant_test;
using namespace random_excursions_test;
using namespace serial_test;
using namespace spectral_test;
using namespace non_overlapping_template_matching_test;

int main()
{
    std::cout << "----------------------------------------------------------------------" << std::endl;

    Runs_test_boltach r_test_boltach;

    auto t1 = std::chrono::high_resolution_clock::now();
    r_test_boltach.read("../seq/seq7.bin");
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
    r_e_v_test_boltach.read("../seq/seq7.bin");
    t2 = std::chrono::high_resolution_clock::now();

    duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    p_value = r_e_v_test_boltach.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value random_excursion_variant_test: %.8f\n", p_value);

    std::cout << "----------------------------------------------------------------------" << std::endl;

    Runs_test_timoshenko r_test_timoshenko;

    t1 = std::chrono::high_resolution_clock::now();
    r_test_timoshenko.read("../seq/seq7.bin");
    t2 = std::chrono::high_resolution_clock::now();
    duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    p_value = r_test_timoshenko.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value runs_test: %.8f\n", p_value);

    std::cout << "----------------------------------------------------------------------" << std::endl;

    Random_excursions_test_timoshenko r_e_test_timoshenko;

    t1 = std::chrono::high_resolution_clock::now();
    r_e_test_timoshenko.read("../seq/seq7.bin");
    t2 = std::chrono::high_resolution_clock::now();

    duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    p_value = r_e_test_timoshenko.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value random_excursions_test: %.8f\n", p_value);

    std::cout << "----------------------------------------------------------------------" << std::endl;

    Non_overlapping_template_matching_test_vecherko n_o_t_m_test_vecherko;

    t1 = std::chrono::high_resolution_clock::now();
    n_o_t_m_test_vecherko.read("../seq/seq7.bin");
    t2 = std::chrono::high_resolution_clock::now();

    duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    p_value = n_o_t_m_test_vecherko.run_test(16);
    t2 = std::chrono::high_resolution_clock::now();
    duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value non_overlapping_template_matching_test: %.8f\n", p_value);

    std::cout << "----------------------------------------------------------------------" << std::endl;
    
    Serial_test_lisai serial_test_lisai;

    t1 = std::chrono::high_resolution_clock::now();
    serial_test_lisai.read("../seq/seq7.bin");
    t2 = std::chrono::high_resolution_clock::now();
    
    duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    auto p_value_for_serial = serial_test_lisai.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value serial_test: %.8f %.8f\n", p_value_for_serial.first, p_value_for_serial.second);

    std::cout << "----------------------------------------------------------------------" << std::endl;

    Spectral_test_lisai spectral_test_lisai;

    t1 = std::chrono::high_resolution_clock::now();
    spectral_test_lisai.read("../seq/seq7.bin");
    t2 = std::chrono::high_resolution_clock::now();

    t1 = std::chrono::high_resolution_clock::now();
    p_value  = spectral_test_lisai.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value spectral_test: %.8f\n", p_value);

    std::cout << "----------------------------------------------------------------------" << std::endl;

    Serial_test_zakrevsky serial_test_zakrevsky;

    t1 = std::chrono::high_resolution_clock::now();
    serial_test_zakrevsky.read("../seq/seq7.bin");
    t2 = std::chrono::high_resolution_clock::now();

    duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    p_value_for_serial = serial_test_zakrevsky.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value serial_test: %.8f %.8f\n", p_value_for_serial.first, p_value_for_serial.second);

    return 0;

}