#pragma once

#include <iostream>
#include <chrono>

class Nist_tests_interface {
private:
    void run_all_runs_test() const; // << 1
    void run_all_random_excursion_variant_test() const; // << 2
    void run_all_random_excursions_test() const; // << 3
    void run_all_longest_runs_test() const; // << 4
    void run_all_non_overlapping_template_matching_test() const; // << 5
    void run_all_serial_test() const; // << 6
    void run_all_spectral_test() const; // << 7
    void run_all_linear_complexity_test() const; // << 8
    void run_all_approximate_entropy_test() const; // << 9
    void run_all_binary_matrix_rank_test() const; // << 10
    void run_all_cumulative_sums_test() const; // << 11
    void run_all_overlapping_template_matching_test() const; // << 12
    void run_all_maurers_test() const; // << 13

public:
    Nist_tests_interface();
    Nist_tests_interface(const Nist_tests_interface &nist_tests_interface) = default;
    Nist_tests_interface(Nist_tests_interface &&nist_tests_interface) = default;
    Nist_tests_interface& operator=(const Nist_tests_interface &nist_tests_interface) = default;
    Nist_tests_interface& operator=(Nist_tests_interface &&nist_tests_interface) = default;
    ~Nist_tests_interface() = default;

private:
    std::string file_name;

    void started_instructions();

    void started_instructions_runs_test() const;
    void runs_test_boltach() const;
    void runs_test_timoshenko() const;

    void started_instructions_random_excursion_variant_test() const;
    void random_excursion_variant_test_boltach() const;
}; 