#pragma once

#include "binary_matrix_rank_test.hpp"

namespace binary_matrix_rank_test {

    using bytes = std::vector<int>;

    class Binary_matrix_rank_test_evil_genius : public Binary_matrix_rank_test {
    public:
        Binary_matrix_rank_test_evil_genius() = default;
        Binary_matrix_rank_test_evil_genius(const Binary_matrix_rank_test_evil_genius &binary_matrix_rank_test_evil_genius) = default;
        Binary_matrix_rank_test_evil_genius(Binary_matrix_rank_test_evil_genius &&binary_matrix_rank_test_evil_genius) = default;
        Binary_matrix_rank_test_evil_genius& operator=(const Binary_matrix_rank_test_evil_genius &binary_matrix_rank_test_evil_genius) = default;
        Binary_matrix_rank_test_evil_genius& operator=(Binary_matrix_rank_test_evil_genius &&binary_matrix_rank_test_evil_genius) = default;
        ~Binary_matrix_rank_test_evil_genius() = default;

        void read(std::string filename = "") override;
        
        double run_test(int M = 32, int Q = 32) const override;

    private:
        
        int getMatrixRank(std::vector<std::vector<int> > &matrix, bool inv = false) const;

        double hiSqCompute(int f_m, int f_m_1, int N) const;

        std::size_t get_size_file(std::string filename) const;

        bytes _buffer;
    };  

} //namespace binary_matrix_rank_test