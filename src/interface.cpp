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


////////////////////////////////////////////////////////////////////////////////////////////////
std::map<double, std::string> test_read_stat;
std::map<double, std::string> test_task_stat;
std::map<double, std::string> test_stat;
////////////////////////////////////////////////////////////////////////////////////////////////
void Nist_tests_interface::print_statistic() const {
    std::cout << "----------------------------------------------------------------------" << std::endl;
    std::cout << "Result for read time: " << std::endl;
    for (const auto &results : test_read_stat) 
        std::cout << results.first << "\t" << results.second << std::endl;
    std::cout << std::endl;

    std::cout << "Result for task time: " << std::endl;
    for (const auto &results : test_task_stat) 
        std::cout << results.first << "\t" << results.second << std::endl;
    std::cout << std::endl;

    std::cout << "The best implementation is " << test_stat.begin()->first << "\t" << test_stat.begin()->second << std::endl;
    test_read_stat.clear();
    test_task_stat.clear();
    test_stat.clear();
    std::cout << "----------------------------------------------------------------------" << std::endl;
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

    std::string input;
    int number_of_test = 0;
    std::cout << "Choose STATISTICAL TEST(or 0 for run all) - ";

    std::cin >> input;

    try {
        number_of_test = stoi(input);
    } catch(std::exception &e) {
        std::cout << "Incorrect number of test, " << e.what() << std::endl;
        started_instructions();
    }

    if (number_of_test < 0 && number_of_test > 13) {
        std::cerr << "Incorrect number of test, try again" << std::endl;
        started_instructions();
    }

    std::cout << "Choose path to file - ";
    std::cin >> file_name;
    if (file_name.empty()) {
        std::cerr << "File path incorrect, try again" << std::endl;
        started_instructions();
    }

    switch(number_of_test) {
        case 0: run_all_tests(); 
                break;
        case 1: started_instructions_runs_test(); 
                break;
        case 2: started_instructions_random_excursion_variant_test(); 
                break;
        case 3: started_instructions_random_excursions_test();
                break;
        case 4: started_instructions_longest_runs_test();
                break;
        case 5: started_instructions_non_overlapping_template_matching_test();
                break;
        case 6: started_instructions_serial_test();
                break;
        case 7: started_instructions_spectral_test();
                break;
        case 8: started_instructions_linear_complexity_test();
                break;
        case 9: started_instructions_approximate_entropy_test();
                break;
        case 10: started_instructions_binary_matrix_rank_test();
                break;
        case 11: started_instructions_cumulative_sums_test();
                break;
        case 12: started_instructions_overlapping_template_matching_test();
                break;
        case 13: started_instructions_maurers_test();
                break;
    }
    test_read_stat.clear();
    test_task_stat.clear();
    test_stat.clear();

    std::string exit;
    std::cout << "Do you want to continue or complete the execution(Enter exit for shutdown)?" << std::endl;
    std::cin >> exit;
    if (exit != "exit" && exit != "Exit")
        started_instructions();
}

void Nist_tests_interface::run_all_tests() const {
    run_all_runs_test();
    run_all_random_excursion_variant_test();
    run_all_random_excursions_test();
    run_all_longest_runs_test();
    run_all_non_overlapping_template_matching_test();
    run_all_serial_test();
    run_all_spectral_test();
    run_all_linear_complexity_test();
    run_all_approximate_entropy_test();
    run_all_binary_matrix_rank_test();
    run_all_cumulative_sums_test();
    run_all_overlapping_template_matching_test();
    run_all_maurers_test();
}

////////////////////////////////////////////////////////////////////////////////////////////////

void Nist_tests_interface::started_instructions_runs_test() const {
    int number_of_runs_test = 0;
    std::cout << " W E L C O M E  TO  R U N S  T E S T " << std::endl;
    std::cout << "_____________________________________\n" << std::endl;
    std::cout << "[01] Runs test Boltach    [02] Runs test Timoshenko\n" << std::endl;
    std::cout << "Enter test implementation number or 0 for run all - " << std::endl;
    std::cin >> number_of_runs_test;

    if (number_of_runs_test == 0)
        run_all_runs_test();
    else if (number_of_runs_test < 1 && number_of_runs_test > 2) {
        std::cerr << "Incorrect number of test, try again" << std::endl;
        started_instructions_runs_test();
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
    test_read_stat.insert({duration_read, "Boltach"});
    test_task_stat.insert({duration_task, "Boltach"});
    test_stat.insert({duration_read + duration_task, "Boltach"});
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
    test_read_stat.insert({duration_read, "Timoshenko"});
    test_task_stat.insert({duration_task, "Timoshenko"});
    test_stat.insert({duration_read + duration_task, "Timoshenko"});
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

void Nist_tests_interface::run_all_runs_test() const {
    runs_test_boltach();
    runs_test_timoshenko();

    print_statistic();
}

////////////////////////////////////////////////////////////////////////////////////////////////

void Nist_tests_interface::started_instructions_random_excursion_variant_test() const {
    int number_of_random_excursion_variant_test = 0;
    std::cout << " W E L C O M E  TO  R A N D O M  E X C U R S I O N  V A R I A N T  T E S T " << std::endl;
    std::cout << "___________________________________________________________________________\n" << std::endl;
    std::cout << "[01] Random excursion variant test Boltach  \n" << std::endl;
    std::cout << "Enter test implementation number or 0 for run all - " << std::endl;
    std::cin >> number_of_random_excursion_variant_test;

    if (number_of_random_excursion_variant_test == 0)
        run_all_random_excursion_variant_test();
    else if (number_of_random_excursion_variant_test < 1 && number_of_random_excursion_variant_test > 1) {
        std::cerr << "Incorrect number of test, try again" << std::endl;
        started_instructions_random_excursion_variant_test();
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
    test_read_stat.insert({duration_read, "Boltach"});
    test_task_stat.insert({duration_task, "Boltach"});
    test_stat.insert({duration_read + duration_task, "Boltach"});
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

void Nist_tests_interface::run_all_random_excursion_variant_test() const {
    random_excursion_variant_test_boltach();

    print_statistic();
}

////////////////////////////////////////////////////////////////////////////////////////////////

void Nist_tests_interface::started_instructions_random_excursions_test() const {
    int number_of_random_excursions_test = 0;
    std::cout << " W E L C O M E  TO  R A N D O M  E X C U R S I O N S  T E S T " << std::endl;
    std::cout << "______________________________________________________________\n" << std::endl;
    std::cout << "[01] Random excursions test Timoshenko    [02] Random excursions test Bondarev\n" << std::endl;
    std::cout << "Enter test implementation number or 0 for run all - " << std::endl;
    std::cin >> number_of_random_excursions_test;

    if (number_of_random_excursions_test == 0)
        run_all_random_excursions_test();
    else if (number_of_random_excursions_test < 1 && number_of_random_excursions_test > 2) {
        std::cerr << "Incorrect number of test, try again" << std::endl;
        started_instructions_random_excursions_test();
    }
    
    switch(number_of_random_excursions_test) {
        case 1: random_excursions_test_timoshenko();
                break;
        case 2: random_excursions_test_bondarev();
                break;
    }
}

void Nist_tests_interface::random_excursions_test_timoshenko() const {
    std::cout << "----------------------------------------------------------------------" << std::endl;
    Random_excursions_test_timoshenko r_e_test_timoshenko;

    auto t1 = std::chrono::high_resolution_clock::now();
    r_e_test_timoshenko.read(file_name);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    auto p_value = r_e_test_timoshenko.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    
    auto duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);
    
    printf("\nP-value random_excursions_test: %.8f\n", p_value);
    test_read_stat.insert({duration_read, "Timoshenko"});
    test_task_stat.insert({duration_task, "Timoshenko"});
    test_stat.insert({duration_read + duration_task, "Timoshenko"});
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

void Nist_tests_interface::random_excursions_test_bondarev() const {

    std::cout << "----------------------------------------------------------------------" << std::endl;
    Random_excursions_test_bondarev r_e_test_bondarev;

    auto t1 = std::chrono::high_resolution_clock::now();
    r_e_test_bondarev.read(file_name);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    auto p_value = r_e_test_bondarev.run_test();
    t2 = std::chrono::high_resolution_clock::now();

    auto duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value random_excursions_test: %.8f\n", p_value);
    test_read_stat.insert({duration_read, "Bondarev"});
    test_task_stat.insert({duration_task, "Bondarev"});
    test_stat.insert({duration_read + duration_task, "Bondarev"});
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

void Nist_tests_interface::run_all_random_excursions_test() const {
    random_excursions_test_timoshenko();
    random_excursions_test_bondarev();

    print_statistic();
}

////////////////////////////////////////////////////////////////////////////////////////////////

void Nist_tests_interface::started_instructions_longest_runs_test() const {
    int number_of_longest_runs_test = 0;
    std::cout << " W E L C O M E  TO  L O N G E S T  R U N S  T E S T " << std::endl;
    std::cout << "____________________________________________________\n" << std::endl;
    std::cout << "[01] Longest runs test Bondarev\n" << std::endl;
    std::cout << "Enter test implementation number or 0 for run all - " << std::endl;
    std::cin >> number_of_longest_runs_test;

    if (number_of_longest_runs_test == 0)
        run_all_longest_runs_test();
    else if (number_of_longest_runs_test < 1 && number_of_longest_runs_test > 1) {
        std::cerr << "Incorrect number of test, try again" << std::endl;
        started_instructions_longest_runs_test();
    }
    
    switch(number_of_longest_runs_test) {
        case 1: longest_runs_test_bondarev();
                break;
    }
}

void Nist_tests_interface::longest_runs_test_bondarev() const {
    std::cout << "----------------------------------------------------------------------" << std::endl;
    Longest_runs_test_bondarev longest_runs_test_bondarev;

    auto t1 = std::chrono::high_resolution_clock::now();
    longest_runs_test_bondarev.read(file_name);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    auto p_value = longest_runs_test_bondarev.run_test();
    t2 = std::chrono::high_resolution_clock::now();

    auto duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value longest_runs_test: %.8f\n", p_value);
    test_read_stat.insert({duration_read, "Bondarev"});
    test_task_stat.insert({duration_task, "Bondarev"});
    test_stat.insert({duration_read + duration_task, "Bondarev"});
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

void Nist_tests_interface::run_all_longest_runs_test() const {
    longest_runs_test_bondarev();

    print_statistic();
}

////////////////////////////////////////////////////////////////////////////////////////////////

void Nist_tests_interface::started_instructions_non_overlapping_template_matching_test() const {
    int number_of_non_overlapping_template_matching_test = 0;
    std::cout << " W E L C O M E  TO  N O N  O V E R L A P P I N G  T E M P L A T E  M A T C H I N G  T E S T " << std::endl;
    std::cout << "____________________________________________________________________________________________\n" << std::endl;
    std::cout << "[01] Non overlapping template matching test Vecherko  [02] Non overlapping template matching test Lagunov" << std::endl;
    std::cout << "[03] Non overlapping template matching test Zakrevsky\n" << std::endl;
    std::cout << "Enter test implementation number or 0 for run all - " << std::endl;
    std::cin >> number_of_non_overlapping_template_matching_test;

    if (number_of_non_overlapping_template_matching_test == 0)
        run_all_non_overlapping_template_matching_test();
    else if (number_of_non_overlapping_template_matching_test < 1 && number_of_non_overlapping_template_matching_test > 3) {
        std::cerr << "Incorrect number of test, try again" << std::endl;
        started_instructions_non_overlapping_template_matching_test();
    }
    
    switch(number_of_non_overlapping_template_matching_test) {
        case 1: non_overlapping_template_matching_test_vecherko();
                break;
        case 2: non_overlapping_template_matching_test_lagunov();
                break;
        case 3: non_overlapping_template_matching_test_zakrevsky();
                break;
    }
}

void Nist_tests_interface::non_overlapping_template_matching_test_vecherko() const {
    std::cout << "----------------------------------------------------------------------" << std::endl;
    Non_overlapping_template_matching_test_vecherko n_o_t_m_test_vecherko;

    auto t1 = std::chrono::high_resolution_clock::now();
    n_o_t_m_test_vecherko.read(file_name);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    auto p_value = n_o_t_m_test_vecherko.run_test();
    t2 = std::chrono::high_resolution_clock::now();

    auto duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value non_overlapping_template_matching_test: %.8Lf\n", p_value);
    test_read_stat.insert({duration_read, "Vecherko"});
    test_task_stat.insert({duration_task, "Vecherko"});
    test_stat.insert({duration_read + duration_task, "Vecherko"});
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

void Nist_tests_interface::non_overlapping_template_matching_test_lagunov() const {
    std::cout << "----------------------------------------------------------------------" << std::endl;
    Non_overlapping_template_matching_test_lagunov n_o_t_m_test_lagunov;

    auto t1 = std::chrono::high_resolution_clock::now();
    n_o_t_m_test_lagunov.read(file_name);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    auto p_value = n_o_t_m_test_lagunov.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    
    auto duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value non_overlapping_template_matching_test: %.8Lf\n", p_value);
    test_read_stat.insert({duration_read, "Lagunov"});
    test_task_stat.insert({duration_task, "Lagunov"});
    test_stat.insert({duration_read + duration_task, "Lagunov"});
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

void Nist_tests_interface::non_overlapping_template_matching_test_zakrevsky() const {
    std::cout << "----------------------------------------------------------------------" << std::endl;
    Non_overlapping_template_matching_test_zakrevsky n_o_t_m_test_zakrevsky;

    auto t1 = std::chrono::high_resolution_clock::now();
    n_o_t_m_test_zakrevsky.read(file_name);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    auto p_value = n_o_t_m_test_zakrevsky.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    
    auto duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value non_overlapping_template_matching_test: %.8Lf\n", p_value);
    test_read_stat.insert({duration_read, "Zakrevsky"});
    test_task_stat.insert({duration_task, "Zakrevsky"});
    test_stat.insert({duration_read + duration_task, "Zakrevsky"});
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

void Nist_tests_interface::run_all_non_overlapping_template_matching_test() const {
    non_overlapping_template_matching_test_vecherko();
    non_overlapping_template_matching_test_lagunov();
    non_overlapping_template_matching_test_zakrevsky();

    print_statistic();
}

////////////////////////////////////////////////////////////////////////////////////////////////

void Nist_tests_interface::started_instructions_serial_test() const {
    int number_of_serial_test = 0;
    std::cout << " W E L C O M E  TO  S E R I A L  T E S T " << std::endl;
    std::cout << "_________________________________________\n" << std::endl;
    std::cout << "[01] Serial test Lisai  [02] Serial test Zakrevsky\n" << std::endl;
    std::cout << "Enter test implementation number or 0 for run all - " << std::endl;
    std::cin >> number_of_serial_test;

    if (number_of_serial_test == 0)
        run_all_serial_test();
    else if (number_of_serial_test < 1 && number_of_serial_test > 2) {
        std::cerr << "Incorrect number of test, try again" << std::endl;
        started_instructions_serial_test();
    }
    
    switch(number_of_serial_test) {
        case 1: serial_test_lisai();
                break;
        case 2: serial_test_zakrevsky();
                break;
    }
}

void Nist_tests_interface::serial_test_lisai() const {
    std::cout << "----------------------------------------------------------------------" << std::endl;
    Serial_test_lisai serial_test_lisai;

    auto t1 = std::chrono::high_resolution_clock::now();
    serial_test_lisai.read(file_name);
    auto t2 = std::chrono::high_resolution_clock::now();
    
    auto duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    auto p_value_for_serial = serial_test_lisai.run_test();
    t2 = std::chrono::high_resolution_clock::now();

    auto duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value serial_test: %.8f %.8f\n", p_value_for_serial.first, p_value_for_serial.second);
    test_read_stat.insert({duration_read, "Lisai"});
    test_task_stat.insert({duration_task, "Lisai"});
    test_stat.insert({duration_read + duration_task, "Lisai"});
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

void Nist_tests_interface::serial_test_zakrevsky() const {
    std::cout << "----------------------------------------------------------------------" << std::endl;
    Serial_test_zakrevsky serial_test_zakrevsky;

    auto t1 = std::chrono::high_resolution_clock::now();
    serial_test_zakrevsky.read(file_name);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    auto p_value_for_serial = serial_test_zakrevsky.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    
    auto duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value serial_test: %.8f %.8f\n", p_value_for_serial.first, p_value_for_serial.second);
    test_read_stat.insert({duration_read, "Zakrevsky"});
    test_task_stat.insert({duration_task, "Zakrevsky"});
    test_stat.insert({duration_read + duration_task, "Zakrevsky"});
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

void Nist_tests_interface::run_all_serial_test() const {
    serial_test_lisai();
    serial_test_zakrevsky();

    print_statistic();
}

////////////////////////////////////////////////////////////////////////////////////////////////

void Nist_tests_interface::started_instructions_spectral_test() const {
    int number_of_spectral_test = 0;
    std::cout << " W E L C O M E  TO  S P E C T R A L  T E S T " << std::endl;
    std::cout << "_____________________________________________\n" << std::endl;
    std::cout << "[01] Spectral test Lisai  [02] Spectral test Vecherko" << std::endl;
    std::cout << "[03] Spectral test Grudinsky\n" << std::endl;
    std::cout << "Enter test implementation number or 0 for run all - " << std::endl;
    std::cin >> number_of_spectral_test;

    if (number_of_spectral_test == 0)
        run_all_spectral_test();
    else if (number_of_spectral_test < 1 && number_of_spectral_test > 3) {
        std::cerr << "Incorrect number of test, try again" << std::endl;
        started_instructions_spectral_test();
    }
    
    switch(number_of_spectral_test) {
        case 1: spectral_test_lisai();
                break;
        case 2: spectral_test_vecherko();
                break;
        case 3: spectral_test_grudinsky();
                break;
    }
}

void Nist_tests_interface::spectral_test_lisai() const {
    std::cout << "----------------------------------------------------------------------" << std::endl;
    Spectral_test_lisai spectral_test_lisai;

    auto t1 = std::chrono::high_resolution_clock::now();
    spectral_test_lisai.read(file_name);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    auto p_value  = spectral_test_lisai.run_test();
    t2 = std::chrono::high_resolution_clock::now();

    auto duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value spectral_test: %.8f\n", p_value);
    test_read_stat.insert({duration_read, "Lisai"});
    test_task_stat.insert({duration_task, "Lisai"});
    test_stat.insert({duration_read + duration_task, "Lisai"});
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

void Nist_tests_interface::spectral_test_vecherko() const {
    std::cout << "----------------------------------------------------------------------" << std::endl;
    Spectral_test_vecherko spectral_test_vecherko;

    auto t1 = std::chrono::high_resolution_clock::now();
    spectral_test_vecherko.read(file_name);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    auto p_value = spectral_test_vecherko.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    
    auto duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value spectral_test: %.8f\n", p_value);
    test_read_stat.insert({duration_read, "Vecherko"});
    test_task_stat.insert({duration_task, "Vecherko"});
    test_stat.insert({duration_read + duration_task, "Vecherko"});
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

void Nist_tests_interface::spectral_test_grudinsky() const {
    std::cout << "----------------------------------------------------------------------" << std::endl;
    Spectral_test_grudinsky spectral_test_grudinsky;

    auto t1 = std::chrono::high_resolution_clock::now();
    spectral_test_grudinsky.read(file_name);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    auto p_value = spectral_test_grudinsky.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    
    auto duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value spectral_test: %.8f\n", p_value);
    test_read_stat.insert({duration_read, "Grudinsky"});
    test_task_stat.insert({duration_task, "Grudinsky"});
    test_stat.insert({duration_read + duration_task, "Grudinsky"});
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

void Nist_tests_interface::run_all_spectral_test() const {
    spectral_test_lisai();
    spectral_test_vecherko();
    spectral_test_grudinsky();

    print_statistic();
}

////////////////////////////////////////////////////////////////////////////////////////////////

void Nist_tests_interface::started_instructions_linear_complexity_test() const {
    int number_of_linear_complexity_test = 0;
    std::cout << " W E L C O M E  TO  L I N E A R  C O M P L E X I T Y  T E S T " << std::endl;
    std::cout << "______________________________________________________________\n" << std::endl;
    std::cout << "[01] Linear complexity test Vecherko  [02] Linear complexity test Lagunov\n" << std::endl;
    std::cout << "Enter test implementation number or 0 for run all - " << std::endl;
    std::cin >> number_of_linear_complexity_test;

    if (number_of_linear_complexity_test == 0)
        run_all_linear_complexity_test();
    else if (number_of_linear_complexity_test < 1 && number_of_linear_complexity_test > 2) {
        std::cerr << "Incorrect number of test, try again" << std::endl;
        started_instructions_linear_complexity_test();
    }
    
    switch(number_of_linear_complexity_test) {
        case 1: linear_complexity_test_vecherko();
                break;
        case 2: linear_complexity_test_lagunov();
                break;
    }
}

void Nist_tests_interface::linear_complexity_test_vecherko() const {
    std::cout << "----------------------------------------------------------------------" << std::endl;
    Linear_complexity_test_vecherko l_c_test_vecherko;

    auto t1 = std::chrono::high_resolution_clock::now();
    l_c_test_vecherko.read(file_name);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    auto p_value = l_c_test_vecherko.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    
    auto duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value linear_complexity_test: %.8f\n", p_value);
    test_read_stat.insert({duration_read, "Vecherko"});
    test_task_stat.insert({duration_task, "Vecherko"});
    test_stat.insert({duration_read + duration_task, "Vecherko"});
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

void Nist_tests_interface::linear_complexity_test_lagunov() const {
    std::cout << "----------------------------------------------------------------------" << std::endl;
    Linear_complexity_test_lagunov l_c_t_test_lagunov;

    auto t1 = std::chrono::high_resolution_clock::now();
    l_c_t_test_lagunov.read(file_name);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    auto p_value = l_c_t_test_lagunov.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    
    auto duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value Linear_complexity_test: %.8f\n", p_value);
    test_read_stat.insert({duration_read, "Lagunov"});
    test_task_stat.insert({duration_task, "Lagunov"});
    test_stat.insert({duration_read + duration_task, "Lagunov"});
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

void Nist_tests_interface::run_all_linear_complexity_test() const {
    linear_complexity_test_vecherko();
    linear_complexity_test_lagunov();

    print_statistic();
}

////////////////////////////////////////////////////////////////////////////////////////////////

void Nist_tests_interface::started_instructions_approximate_entropy_test() const {
    int number_of_approximate_entropy_test = 0;
    std::cout << " W E L C O M E  TO  A L L  A P P R O X I M A T E  E N T R O P Y  T E S T " << std::endl;
    std::cout << "_________________________________________________________________________\n" << std::endl;
    std::cout << "[01] Approximate entropy test Grudinsky\n" << std::endl;
    std::cout << "Enter test implementation number or 0 for run all - " << std::endl;
    std::cin >> number_of_approximate_entropy_test;

    if (number_of_approximate_entropy_test == 0)
        run_all_approximate_entropy_test();
    else if (number_of_approximate_entropy_test < 1 && number_of_approximate_entropy_test > 1) {
        std::cerr << "Incorrect number of test, try again" << std::endl;
        started_instructions_approximate_entropy_test();
    }
    
    switch(number_of_approximate_entropy_test) {
        case 1: approximate_entropy_test_grudinsky();
                break;
    }
}

void Nist_tests_interface::approximate_entropy_test_grudinsky() const {
    std::cout << "----------------------------------------------------------------------" << std::endl;
    Approximate_entropy_test_grudinsky appr_entr_test_grudinsky;

    auto t1 = std::chrono::high_resolution_clock::now();
    appr_entr_test_grudinsky.read(file_name);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    auto p_value = appr_entr_test_grudinsky.run_test();
    t2 = std::chrono::high_resolution_clock::now();

    auto duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value approximate_entropy_test: %.8f\n", p_value);
    test_read_stat.insert({duration_read, "Grudinsky"});
    test_task_stat.insert({duration_task, "Grudinsky"});
    test_stat.insert({duration_read + duration_task, "Grudinsky"});
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

void Nist_tests_interface::run_all_approximate_entropy_test() const {
    approximate_entropy_test_grudinsky();

    print_statistic();
}

////////////////////////////////////////////////////////////////////////////////////////////////

void Nist_tests_interface::started_instructions_binary_matrix_rank_test() const {
    int number_of_binary_matrix_rank_test = 0;
    std::cout << " W E L C O M E  TO  B I N A R Y  M A T R I X  R A N K  T E S T " << std::endl;
    std::cout << "_______________________________________________________________\n" << std::endl;
    std::cout << "[01] Binary matrix rank test Vecherko\n" << std::endl;
    std::cout << "Enter test implementation number or 0 for run all - " << std::endl;
    std::cin >> number_of_binary_matrix_rank_test;

    if (number_of_binary_matrix_rank_test == 0)
        run_all_binary_matrix_rank_test();
    else if (number_of_binary_matrix_rank_test < 1 && number_of_binary_matrix_rank_test > 1) {
        std::cerr << "Incorrect number of test, try again" << std::endl;
        started_instructions_binary_matrix_rank_test();
    }
    
    switch(number_of_binary_matrix_rank_test) {
        case 1: binary_matrix_rank_test_vecherko();
                break;
    }
}

void Nist_tests_interface::binary_matrix_rank_test_vecherko() const {
    std::cout << "----------------------------------------------------------------------" << std::endl;
    Binary_matrix_rank_test_vecherko b_m_r_test_vecherko;

    auto t1 = std::chrono::high_resolution_clock::now();
    b_m_r_test_vecherko.read(file_name);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    auto p_value = b_m_r_test_vecherko.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    
    auto duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value binary_matrix_rank_test: %.8f\n", p_value);
    test_read_stat.insert({duration_read, "Vecherko"});
    test_task_stat.insert({duration_task, "Vecherko"});
    test_stat.insert({duration_read + duration_task, "Vecherko"});
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

void Nist_tests_interface::run_all_binary_matrix_rank_test() const {
    binary_matrix_rank_test_vecherko();

    print_statistic();
}

////////////////////////////////////////////////////////////////////////////////////////////////

void Nist_tests_interface::started_instructions_cumulative_sums_test() const {
    int number_of_cumulative_sums_test = 0;
    std::cout << " W E L C O M E  TO  C U M U L A T I V E  S U M S  T E S T " << std::endl;
    std::cout << "__________________________________________________________\n" << std::endl;
    std::cout << "[01] Cumulative sums test Vorobiova\n" << std::endl;
    std::cout << "Enter test implementation number or 0 for run all - " << std::endl;
    std::cin >> number_of_cumulative_sums_test;

    if (number_of_cumulative_sums_test == 0)
        run_all_cumulative_sums_test();
    else if (number_of_cumulative_sums_test < 1 && number_of_cumulative_sums_test > 1) {
        std::cerr << "Incorrect number of test, try again" << std::endl;
        started_instructions_cumulative_sums_test();
    }
    
    switch(number_of_cumulative_sums_test) {
        case 1: cumulative_sums_test_vorobiova();
                break;
    }
}

void Nist_tests_interface::cumulative_sums_test_vorobiova() const {
    std::cout << "----------------------------------------------------------------------" << std::endl;
    Cumulative_sums_test_vorobiova c_s_test_vorobiova;

    auto t1 = std::chrono::high_resolution_clock::now();
    c_s_test_vorobiova.read(file_name);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    auto p_value = c_s_test_vorobiova.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    
    auto duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value cumulative_sums_test: %.8f\n", p_value);
    test_read_stat.insert({duration_read, "Vorobiova"});
    test_task_stat.insert({duration_task, "Vorobiova"});
    test_stat.insert({duration_read + duration_task, "Vorobiova"});
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

void Nist_tests_interface::run_all_cumulative_sums_test() const {
    cumulative_sums_test_vorobiova();

    print_statistic();
}

////////////////////////////////////////////////////////////////////////////////////////////////

void Nist_tests_interface::started_instructions_overlapping_template_matching_test() const {
    int number_of_coverlapping_template_matching_test = 0;
    std::cout << " W E L C O M E  TO  O V E R L A P P I N G  T E M P L A T E  M A T C H I N G  T E S T " << std::endl;
    std::cout << "_____________________________________________________________________________________\n" << std::endl;
    std::cout << "[01] Overlapping template matching test Kruglic\n" << std::endl;
    std::cout << "Enter test implementation number or 0 for run all - " << std::endl;
    std::cin >> number_of_coverlapping_template_matching_test;

    if (number_of_coverlapping_template_matching_test == 0)
        run_all_overlapping_template_matching_test();
    else if (number_of_coverlapping_template_matching_test < 1 && number_of_coverlapping_template_matching_test > 1) {
        std::cerr << "Incorrect number of test, try again" << std::endl;
        started_instructions_overlapping_template_matching_test();
    }
    
    switch(number_of_coverlapping_template_matching_test) {
        case 1: overlapping_template_matching_test_kruglic();
                break;
    }
}

void Nist_tests_interface::overlapping_template_matching_test_kruglic() const {
    std::cout << "----------------------------------------------------------------------" << std::endl;
    Overlapping_template_matching_test_kruglic o_t_m_test_kruglic;

    auto t1 = std::chrono::high_resolution_clock::now();
    o_t_m_test_kruglic.read(file_name);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    auto p_value = o_t_m_test_kruglic.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    
    auto duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value overlapping_template_matching_test: %.8f\n", p_value);
    test_read_stat.insert({duration_read, "Kruglic"});
    test_task_stat.insert({duration_task, "Kruglic"});
    test_stat.insert({duration_read + duration_task, "Kruglic"});
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

void Nist_tests_interface::run_all_overlapping_template_matching_test() const {
    overlapping_template_matching_test_kruglic();

    print_statistic();
}

////////////////////////////////////////////////////////////////////////////////////////////////

void Nist_tests_interface::started_instructions_maurers_test() const {
    int number_of_maurers_test = 0;
    std::cout << " W E L C O M E  TO  M A U R E R S  T E S T " << std::endl;
    std::cout << "___________________________________________\n" << std::endl;
    std::cout << "[01] Maurers test Kruglic\n" << std::endl;
    std::cout << "Enter test implementation number or 0 for run all - " << std::endl;
    std::cin >> number_of_maurers_test;

    if (number_of_maurers_test == 0)
        run_all_maurers_test();
    else if (number_of_maurers_test < 1 && number_of_maurers_test > 1) {
        std::cerr << "Incorrect number of test, try again" << std::endl;
        started_instructions_maurers_test();
    }
    
    switch(number_of_maurers_test) {
        case 1: maurers_test_kruglic();
                break;
    }
}

void Nist_tests_interface::maurers_test_kruglic() const {
    std::cout << "----------------------------------------------------------------------" << std::endl;

    Maurers_test_kruglic m_test_kruglic;

    auto t1 = std::chrono::high_resolution_clock::now();
    m_test_kruglic.read(file_name);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    auto p_value = m_test_kruglic.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    
    auto duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value maurers_test: %.8f\n", p_value);
    test_read_stat.insert({duration_read, "Kruglic"});
    test_task_stat.insert({duration_task, "Kruglic"});
    test_stat.insert({duration_read + duration_task, "Kruglic"});
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

void Nist_tests_interface::run_all_maurers_test() const {
    maurers_test_kruglic();

    print_statistic();
}

////////////////////////////////////////////////////////////////////////////////////////////////