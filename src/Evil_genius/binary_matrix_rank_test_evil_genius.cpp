#include "../libraries/binary_matrix_rank_test_evil_genius.hpp"

namespace binary_matrix_rank_test {

    void Binary_matrix_rank_test_evil_genius::read(std::string filename /* = "" */) {
        if (filename.empty())
            std::cerr << "Filename is undefined" << std::endl;
        else
            std::cout << "Read from(Binary_matrix_rank_test Evil_genius) " << filename << std::endl;

        std::ifstream f(filename, std::ios::binary | std::ios::in);

        if (!f.is_open()) {
            std::cerr << "Could NOT find " + filename << std::endl;
            return;
        }

        _buffer.reserve(get_size_file(filename)*8);

        char c;
        while(f.get(c)) {
            for(int i = 0; i < 8; ++i)
                if(c & ((char)(1<<i)))
                    _buffer.push_back(1);
                else
                    _buffer.push_back(0);
            reverse(_buffer.end() - 8, _buffer.end());
        }

        f.close();
    }

    double Binary_matrix_rank_test_evil_genius::run_test(int M /* = 32 */, int Q /* = 32 */) const {
        std::cout << "Started performing binary_matrix_rank_test Evil_genius" << std::endl;
        assert(!_buffer.empty());

        std::vector<std::vector<int> > bin_matrix(M, std::vector<int> (Q, 0));
        int cur = 0;
        int f_m = 0, f_m_1 = 0, f_other = 0;
        while(_buffer.size() >= cur + M * Q)
        {
            for(int i = 0; i < M; ++i)
            {
                for(int j = 0; j < Q; ++j)
                    bin_matrix[i][j] = _buffer[cur++];
            }
            int rnq = getMatrixRank(bin_matrix);
            if(rnq == M)
                f_m++;
            else if(rnq == M-1)
                f_m_1++;
            else
                f_other++;
        }

        double hi_sq = hiSqCompute(f_m, f_m_1, f_m+f_m_1+f_other);
        double p_value = exp(-hi_sq/2.0);

        return p_value;
    }

    int Binary_matrix_rank_test_evil_genius::getMatrixRank(std::vector<std::vector<int> > &matrix, bool inv /* = false */) const {
        int n = matrix.size();
        int m = matrix[0].size();

        for (int i = 0; i < n; ++i) {

            if (matrix[i][i] == 0) {
                for (int j = i + 1; j < n; ++j) {
                    if (matrix[j][i]) {
                        for (int k = i; k < m; ++k)
                            std::swap(matrix[i][k], matrix[j][k]);
                        break;
                    }
                }
            }

            if (matrix[i][i] == 0)
                continue;
            else {
                for (int j = i + 1; j < n; ++j)
                    if (matrix[j][i])
                        for (int k = i; k < m; ++k)
                            matrix[j][k] ^= matrix[i][k];
            }
        }

        int rnk = 0;
        if (inv) {
            for(int i = 0; i < n; ++i)
                if(std::vector<int>(m, 0) != matrix[i])
                    ++rnk;
        }
        else {
            std::vector<std::vector<int> > tmp = matrix;
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < m; ++j)
                    tmp[i][j] = matrix[n-i-1][m-j-1];
            return getMatrixRank(tmp, true);
        }

        return rnk;
    }

    double Binary_matrix_rank_test_evil_genius::hiSqCompute(int f_m, int f_m_1, int N) const {
        double ans = (f_m  - 0.2888*N)*(f_m  - 0.2888*N)/(0.2888*N);
        ans += (f_m_1  - 0.5776*N)*(f_m_1  - 0.5776*N)/(0.5776*N);
        ans += (N - f_m - f_m_1 - 0.1336*N)*(N - f_m - f_m_1 - 0.1336*N)/(0.1336*N);
        return ans;
    }

    std::size_t Binary_matrix_rank_test_evil_genius::get_size_file(std::string filename) const {
        std::ifstream f(filename, std::ios::binary | std::ios::in | std::ifstream::ate);
        return f.tellg();
    }

} //namespace binary_matrix_rank_test