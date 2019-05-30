#include "libraries/interface.hpp"
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
using namespace cumulative_sums_test;
using namespace overlapping_template_matching_test;
using namespace maurers_test;

Nist_tests_interface::Nist_tests_interface() {
    started_instructions();
}

void Nist_tests_interface::started_instructions() {
    std::cout << "                S T A T I S T I C A L   T E S T S" << std::endl;
	std::cout << "                _________________________________\n" << std::endl;
	std::cout << "    [01] Runs test                              [02] Random excursion variant test" << std::endl;
	std::cout << "    [03] Random excursion test                  [04] Longest Run of Ones" << std::endl;
	std::cout << "    [05] Non overlapping template matching test [06] Serial test" << std::endl;
	std::cout << "    [07] Spectral test (DFF test)               [08] Linear complexity test" << std::endl;
	std::cout << "    [09] Approximate entropy test               [10] Binary matrix rank test" << std::endl;
	std::cout << "    [11] Cumulative sums test                   [12] Overlapping template matching test" << std::endl;
	std::cout << "    [13] Maurers Test\n"  << std::endl;

    int number_of_test = 0;
    std::cout << "Choose STATISTICAL TEST - ";
	std::cin >> number_of_test;
    if (number_of_test < 1 && number_of_test > 13) {
        std::cerr << "Incorrect number of test, try again" << std::endl;
        return started_instructions();
    }

    std::cout << "Choose path to file - ";
    std::cin >> file_name;
    if (file_name.empty()) {
        std::cerr << "File path incorrect, try again" << std::endl;
        return started_instructions();
    }

    switch(number_of_test) {
        case 1: started_instructions_runs_test(); 
                break;
        case 2: started_instructions_random_excursion_variant_test(); 
                break;
        // case 3: 
    }

    uint8_t exit = 1;
    std::cout << "Do you want to continue or complete the execution(enter 0 for exit)?" << std::endl;
    std::cin >> exit;
    if (!exit)
        started_instructions();
}

void Nist_tests_interface::started_instructions_runs_test() const {
    int number_of_runs_test = 0;
    std::cout << " W E L C O M E  TO  R U N S  T E S T" << std::endl;
    std::cout << "____________________________________\n" << std::endl;
    std::cout << "[01] Runs test Boltach    [02] Runs test Timoshenko\n" << std::endl;
    std::cout << "Enter test implementation number or empty for run all - " << std::endl;
    std::cin >> number_of_runs_test;

    if (number_of_runs_test == 0)
        run_all_runs_test();
    else if (number_of_runs_test < 1 && number_of_runs_test > 2) {
        std::cerr << "Incorrect number of test, try again" << std::endl;
        return started_instructions_runs_test();
    }

    switch(number_of_runs_test) {
        case 1: runs_test_boltach();
                break;
        case 2: runs_test_timoshenko();
                break;
    }
}

void Nist_tests_interface::runs_test_boltach() const {
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
}

void Nist_tests_interface::runs_test_timoshenko() const {
    std::cout << "----------------------------------------------------------------------" << std::endl;

    Runs_test_timoshenko r_test_timoshenko;

    auto t1 = std::chrono::high_resolution_clock::now();
    r_test_timoshenko.read(file_name);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    auto p_value = r_test_timoshenko.run_test();
    t2 = std::chrono::high_resolution_clock::now();

    auto duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value runs_test: %.8f\n", p_value);
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

void Nist_tests_interface::run_all_runs_test() const {
    runs_test_boltach();
    runs_test_timoshenko();
}

void Nist_tests_interface::started_instructions_random_excursion_variant_test() const {
    int number_of_random_excursion_variant_test = 0;
    std::cout << " W E L C O M E  TO  R A N D O M  E X C U R S I O N  V A R I A N T  T E S T" << std::endl;
    std::cout << "__________________________________________________________________________\n" << std::endl;
    std::cout << "[01] Random excursion variant test Boltach  \n" << std::endl;
    std::cout << "Enter test implementation number or empty for run all - " << std::endl;
    std::cin >> number_of_random_excursion_variant_test;

    if (number_of_random_excursion_variant_test == 0)
        run_all_random_excursion_variant_test();
    else if (number_of_random_excursion_variant_test < 1 && number_of_random_excursion_variant_test > 1) {
        std::cerr << "Incorrect number of test, try again" << std::endl;
        return started_instructions_random_excursion_variant_test();
    }
    
    switch(number_of_random_excursion_variant_test) {
        case 1: random_excursion_variant_test_boltach();
                break;
    }
}

void Nist_tests_interface::random_excursion_variant_test_boltach() const {
    std::cout << "----------------------------------------------------------------------" << std::endl;
    Random_excursion_variant_test_boltach r_e_v_test_boltach;

    auto t1 = std::chrono::high_resolution_clock::now();
    r_e_v_test_boltach.read(file_name);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    auto p_value = r_e_v_test_boltach.run_test();
    t2 = std::chrono::high_resolution_clock::now();

    auto duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value random_excursion_variant_test: %.8f\n", p_value);
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

void Nist_tests_interface::run_all_random_excursion_variant_test() const {
    random_excursion_variant_test_boltach();
}