#include "libraries/tests.hpp"

using namespace runs_test;
using namespace random_excursion_variant_test;
using namespace random_excursions_test;
using namespace serial_test;
using namespace spectral_test;
using namespace non_overlapping_template_matching_test;
using namespace longest_runs_test;
using namespace approximate_entropy_test;
using namespace binary_matrix_rank_test;
using namespace linear_complexity_test;

int main()
{
    std::string file_name = "../seq/seq7.bin";
    
    std::cout << "----------------------------------------------------------------------" << std::endl;

    Runs_test_boltach r_test_boltach;

    auto t1 = std::chrono::high_resolution_clock::now();
    r_test_boltach.read(file_name);
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
    r_e_v_test_boltach.read(file_name);
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
    r_test_timoshenko.read(file_name);
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
    r_e_test_timoshenko.read(file_name);
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
    
    Random_excursions_test_bondarev r_e_test_bondarev;

    t1 = std::chrono::high_resolution_clock::now();
    r_e_test_bondarev.read(file_name);
    t2 = std::chrono::high_resolution_clock::now();

    duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    p_value = r_e_test_bondarev.run_test();
    t2 = std::chrono::high_resolution_clock::now();

    duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value random_excursions_test: %.8f\n", p_value);

    std::cout << "----------------------------------------------------------------------" << std::endl;

    Longest_runs_test_bondarev longest_runs_test_bondarev;

    t1 = std::chrono::high_resolution_clock::now();
    longest_runs_test_bondarev.read(file_name);
    t2 = std::chrono::high_resolution_clock::now();

    duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    p_value = longest_runs_test_bondarev.run_test();
    t2 = std::chrono::high_resolution_clock::now();

    duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value longest_runs_test: %.8f\n", p_value);

    std::cout << "----------------------------------------------------------------------" << std::endl;

    Non_overlapping_template_matching_test_vecherko n_o_t_m_test_vecherko;

    t1 = std::chrono::high_resolution_clock::now();
    n_o_t_m_test_vecherko.read(file_name);
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
    serial_test_lisai.read(file_name);
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
    spectral_test_lisai.read(file_name);
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
    serial_test_zakrevsky.read(file_name);
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

    std::cout << "----------------------------------------------------------------------" << std::endl;

    Linear_complexity_test_vecherko l_c_test_vecherko;

    t1 = std::chrono::high_resolution_clock::now();
    l_c_test_vecherko.read("../seq/seq5.bin");
    t2 = std::chrono::high_resolution_clock::now();

    duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    p_value = l_c_test_vecherko.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value linear_complexity_test: %.8f\n", p_value);

    std::cout << "----------------------------------------------------------------------" << std::endl;

    Approximate_entropy_test_grudinsky appr_entr_test_grudinsky;

    t1 = std::chrono::high_resolution_clock::now();
    appr_entr_test_grudinsky.read(file_name);
    t2 = std::chrono::high_resolution_clock::now();

    duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    p_value = appr_entr_test_grudinsky.run_test();
    t2 = std::chrono::high_resolution_clock::now();

    duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value approximate_entropy_test: %.8f\n", p_value);

    std::cout << "----------------------------------------------------------------------" << std::endl;
    
    Binary_matrix_rank_test_vecherko b_m_r_test_vecherko;

    t1 = std::chrono::high_resolution_clock::now();
    b_m_r_test_vecherko.read("../seq/seq7.bin");
    t2 = std::chrono::high_resolution_clock::now();

    duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    p_value = b_m_r_test_vecherko.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    
    duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value binary_matrix_rank_test_vecherko: %.8f\n", p_value);

    std::cout << "----------------------------------------------------------------------" << std::endl;

    Spectral_test_vecherko spectral_test_vecherko;

    t1 = std::chrono::high_resolution_clock::now();
    spectral_test_vecherko.read("../seq/seq7.bin");
    t2 = std::chrono::high_resolution_clock::now();

    duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    p_value = spectral_test_vecherko.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    
    duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value spectral_test_vecherko: %.8f\n", p_value);

    std::cout << "----------------------------------------------------------------------" << std::endl;

    Spectral_test_grudinsky spectral_test_grudinsky;

    t1 = std::chrono::high_resolution_clock::now();
    spectral_test_grudinsky.read("../seq/seq7.bin");
    t2 = std::chrono::high_resolution_clock::now();

    duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    p_value = spectral_test_grudinsky.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    
    duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value spectral_test_grudinsky: %.8f\n", p_value);

    std::cout << "----------------------------------------------------------------------" << std::endl;

    return 0;
}