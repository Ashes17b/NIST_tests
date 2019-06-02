#pragma once

#include <algorithm>
#include <iostream>
#include <chrono>
#include <map>

class Nist_tests_interface {
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

    void print_statistic() const;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    void started_instructions_runs_test() const;
    void runs_test_boltach() const;
    void runs_test_timoshenko() const;
    void run_all_runs_test() const; // << 1
    ////////////////////////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////////////////////////
    void started_instructions_random_excursion_variant_test() const;
    void random_excursion_variant_test_boltach() const;
    void run_all_random_excursion_variant_test() const; // << 2
    ////////////////////////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////////////////////////
    void started_instructions_random_excursions_test() const;
    void random_excursions_test_timoshenko() const;
    void random_excursions_test_bondarev() const;
    void run_all_random_excursions_test() const; // << 3
    ////////////////////////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////////////////////////
    void started_instructions_longest_runs_test() const;
    void longest_runs_test_bondarev() const;
    void run_all_longest_runs_test() const; // << 4
    ////////////////////////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////////////////////////
    void started_instructions_non_overlapping_template_matching_test() const;
    void non_overlapping_template_matching_test_vecherko() const;
    void non_overlapping_template_matching_test_lagunov() const;
    void non_overlapping_template_matching_test_zakrevsky() const;
    void run_all_non_overlapping_template_matching_test() const; // << 5
    ////////////////////////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////////////////////////
    void started_instructions_serial_test() const;
    void serial_test_lisai() const;
    void serial_test_zakrevsky() const;
    void run_all_serial_test() const; // << 6
    ////////////////////////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////////////////////////
    void started_instructions_spectral_test() const;
    void spectral_test_lisai() const;
    void spectral_test_vecherko() const;
    void spectral_test_grudinsky() const;
    void run_all_spectral_test() const; // << 7
    ////////////////////////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////////////////////////
    void started_instructions_linear_complexity_test() const;
    void linear_complexity_test_vecherko() const;
    void linear_complexity_test_lagunov() const;
    void run_all_linear_complexity_test() const; // << 8
    ////////////////////////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////////////////////////
    void started_instructions_approximate_entropy_test() const;
    void approximate_entropy_test_grudinsky() const;
    void run_all_approximate_entropy_test() const; // << 9
    ////////////////////////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////////////////////////
    void started_instructions_binary_matrix_rank_test() const;
    void binary_matrix_rank_test_vecherko() const;
    void run_all_binary_matrix_rank_test() const; // << 10
    ////////////////////////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////////////////////////
    void started_instructions_cumulative_sums_test() const;
    void cumulative_sums_test_vorobiova() const;
    void run_all_cumulative_sums_test() const; // << 11
    ////////////////////////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////////////////////////
    void started_instructions_overlapping_template_matching_test() const;
    void overlapping_template_matching_test_kruglic() const;
    void run_all_overlapping_template_matching_test() const; // << 12
    ////////////////////////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////////////////////////
    void started_instructions_maurers_test() const;
    void maurers_test_kruglic() const;
    void run_all_maurers_test() const; // << 13
    ////////////////////////////////////////////////////////////////////////////////////////////////
}; 