#include "../libraries/cumulative_sums_test_vorobiova.hpp"

namespace cumulative_sums_test {

    void Cumulative_sums_test_vorobiova::read(std::string filename /* = "" */) {
        if (filename.empty())
            std::cerr << "Filename is undefined" << std::endl;
        else 
            std::cout << "Read from(Cumulative_sums_test Vorobiova) " << filename << std::endl;

        std::ifstream f(filename, std::ios_base::binary | std::ios::in);

        if (!f.is_open()) {
            std::cerr << "Could NOT find " + filename << std::endl;
            return;
        }

        f.seekg(0, std::ios::end);
        size = f.tellg();
        _buffer.resize(8 * size);
        f.seekg(0);
        char trash;
        for (int i = 0; i < 8 * size; ++i) {
            if (!(i & 7)) {
                f.read(&trash, 1);
            }
            char shift = (i & 7);
            _buffer[i] = (trash >> shift) & 1;
        }
    }

    double Cumulative_sums_test_vorobiova::run_test() const {
        std::cout << "Started performing cumulative_sums_test Vorobiova" << std::endl;
        assert(!_buffer.empty());

        return cumulative_sums(size);
    }

    double Cumulative_sums_test_vorobiova::cephes_normal(double x) const {
        double arg, result, sqrt2 = 1.414213562373095048801688724209698078569672;

        if (x > 0) {
            arg = x / sqrt2;
            result = 0.5 * (1 + erf(arg));
        }
        else {
            arg = -x / sqrt2;
            result = 0.5 * (1 - erf(arg));
        }

        return(result);
    }

    double Cumulative_sums_test_vorobiova::cumulative_sums(int n) const {
        int		S, sup, inf, z, zrev, k;
        double	sum1, sum2, p_value;

        S = 0;
        sup = 0;
        inf = 0;
        for (k = 0; k<n; k++) {
            _buffer[k] ? S++ : S--;
            if (S > sup)
                sup++;
            if (S < inf)
                inf--;
            z = (sup > -inf) ? sup : -inf;
            zrev = (sup - S > S - inf) ? sup - S : S - inf;
        }

        sum1 = 0.0;
        for (k = (-n / z + 1) / 4; k <= (n / z - 1) / 4; k++) {
            sum1 += cephes_normal(((4 * k + 1)*z) / sqrt(n));
            sum1 -= cephes_normal(((4 * k - 1)*z) / sqrt(n));
        }
        sum2 = 0.0;
        for (k = (-n / z - 3) / 4; k <= (n / z - 1) / 4; k++) {
            sum2 += cephes_normal(((4 * k + 3)*z) / sqrt(n));
            sum2 -= cephes_normal(((4 * k + 1)*z) / sqrt(n));
        }

        p_value = 1.0 - sum1 + sum2;
        
        sum1 = 0.0;
        for (k = (-n / zrev + 1) / 4; k <= (n / zrev - 1) / 4; k++) {
            sum1 += cephes_normal(((4 * k + 1)*zrev) / sqrt(n));
            sum1 -= cephes_normal(((4 * k - 1)*zrev) / sqrt(n));
        }
        sum2 = 0.0;
        for (k = (-n / zrev - 3) / 4; k <= (n / zrev - 1) / 4; k++) {
            sum2 += cephes_normal(((4 * k + 3)*zrev) / sqrt(n));
            sum2 -= cephes_normal(((4 * k + 1)*zrev) / sqrt(n));
        }
        p_value = 1.0 - sum1 + sum2;

        return p_value;
    }

} //namespace cumulative_sums_test