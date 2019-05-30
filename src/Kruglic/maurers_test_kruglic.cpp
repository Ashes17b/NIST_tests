#include "../libraries/maurers_test_kruglic.hpp"

namespace maurers_test {

    void Maurers_test_kruglic::read(std::string filename /* = "" */) {
        if (filename.empty())
            std::cerr << "Filename is undefined" << std::endl;
        else 
            std::cout << "Read from(Maurers_test Kruglic) " << filename << std::endl;
        
        std::ifstream f(filename, std::ios::binary | std::ios::in);

        if (!f.is_open()) {
            std::cerr << "Could NOT find " + filename << std::endl;
            return;
        }

        f.seekg(0, std::ios::end);
        n = f.tellg();
        f.seekg(0);
        _buffer.resize(n);
        f.read((char*)&_buffer[0], n);
        f.close();
        n *= 8;
    }

    double Maurers_test_kruglic::run_test() const {
        std::cout << "Started performing maurers_test Kruglic" << std::endl;
        assert(!_buffer.empty());
        double p = Universal();

        return p;
    }

    void Maurers_test_kruglic::ChooseL(int& L, int& Q, double& expectedValue, double& variance) const{
        if (n >= 387840 && n < 904960) {
            L = 6;
            Q = 640;
            expectedValue = 5.2177052;
            variance = 2.954;
        } else if(n >= 904960 && n < 2068480) {
            L = 7;
            Q = 1280;
            expectedValue = 6.1962507;
            variance = 3.125;
        } else if(n >= 2068480 && n < 4654080) {
            L = 8;
            Q = 2560;
            expectedValue = 7.1836656;
            variance = 3.238;
        } else if(n >= 4654080 && n < 10342400) {
            L = 9;
            Q = 5120;
            expectedValue = 8.1764248;
            variance = 3.311;
        } else if(n >= 10342400 && n < 22753280) {
            L = 10;
            Q = 10240;
            expectedValue = 9.1723243;
            variance = 3.356;
        } else if(n >= 22753280 && n < 49643520) {
            L = 11;
            Q = 20480;
            expectedValue = 10.170032;
            variance = 3.384;
        } else if(n >= 49643520 && n < 107560960) {
            L = 12;
            Q = 40960;
            expectedValue = 11.168765;
            variance = 3.401;
        } else if(n >= 107560960 && n < 231669760) {
            L = 13;
            Q = 81920;
            expectedValue = 12.168070;
            variance = 3.410;
        } else if(n >= 231669760 && n < 496435200) {
            L = 14;
            Q = 163840;
            expectedValue = 13.167693;
            variance = 3.416;
        } else if(n >= 496435200 && n < 1059061760) {
            L = 15;
            Q = 327680;
            expectedValue = 14.167488;
            variance = 3.419;
        } else if(n >= 1059061760) {
            L = 16;
            Q = 655360;
            expectedValue = 15.167379;
            variance = 3.421;
        } else {
            return;
        }
    }


    std::vector<int> Maurers_test_kruglic::Initialize(int L, int Q) const {
        std::vector<int> T(pow(2, L));
        uint32_t number = 0;
        for (int i = 0; i < Q * L; ++i) {
            uint32_t idx = i >> 3;
            uint8_t bias = 7- (i & 7);
            number <<= 1;
            number |= (_buffer[idx] >> bias) & 1;
            if (i % L == L - 1) {
                T[number] = (i + 1) / L;
                number ^= number;
            }
        }
        return T;
    }


    double Maurers_test_kruglic::Examine(int K, std::vector<int>& T, int L, int Q) const {
        double sum = 0;
        uint32_t number = 0;
        for (int i = Q * L; i < (Q + K) * L; ++i) {
            uint32_t idx = i >> 3;
            uint8_t bias = 7- (i & 7);
            number <<= 1;
            number |= (_buffer[idx] >> bias) & 1;
            if (i % L == L - 1) {
                sum += log2((i + 1) / L - T[number]);
                T[number] = (i + 1) / L;
                number ^= number;
            }
        }
        return sum;
    }


    double Maurers_test_kruglic::Pvalue(double fn, int K, int L, double expectedValue, double variance) const {
        double c = 0.7 - 0.8 / L + (4. + 32. / L) *
                pow(1. * K, - 3. / L) / 15.;
        double sigma = c * sqrt(variance / K);
        return erfc(fabs((fn - expectedValue) / sqrt(2) / sigma));
    }


    double Maurers_test_kruglic::Universal() const {
        int L = 0;
        int Q = 0;
        double expectedValue = 0;
        double variance = 0;
        ChooseL(L, Q, expectedValue, variance);
        int K = n / L - Q;
        std::vector<int> T = Initialize(L, Q);
        double sum = Examine(K, T, L, Q);
        double fn = sum / K;
        double pvalue = Pvalue(fn, K, L, expectedValue, variance);
        return pvalue;
    }

} //namespace maurers_test