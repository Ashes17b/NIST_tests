#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>


int n = 0;
int L = 0;
int Q = 0;
double expectedValue = 0;
double variance = 0;


std::vector<uint8_t> ReadFile(const std::string& fileName) {
    std::ifstream fin(fileName, std::ios::binary);
    fin.seekg(0, std::ios::end);
    n = fin.tellg();
    fin.seekg(0);
    std::vector<uint8_t> buf(n);
    fin.read((char*)&buf[0], n);
    fin.close();
    return buf;
}


void ChooseL() {
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


std::vector<int> Initialize(const std::vector<uint8_t>& buf) {
    std::vector<int> T(pow(2, L));
    uint32_t number = 0;
    for (int i = 0; i < Q * L; ++i) {
        uint32_t idx = i >> 3;
        uint8_t bias = 7- (i & 7);
        number <<= 1;
        number |= (buf[idx] >> bias) & 1;
        if (i % L == L - 1) {
            T[number] = (i + 1) / L;
            number ^= number;
        }
    }
    return T;
}


double Examine(const std::vector<uint8_t>& buf, int K, std::vector<int>& T) {
    double sum = 0;
    uint32_t number = 0;
    for (int i = Q * L; i < (Q + K) * L; ++i) {
        uint32_t idx = i >> 3;
        uint8_t bias = 7- (i & 7);
        number <<= 1;
        number |= (buf[idx] >> bias) & 1;
        if (i % L == L - 1) {
            sum += log2((i + 1) / L - T[number]);
            T[number] = (i + 1) / L;
            number ^= number;
        }
    }
    return sum;
}


double Pvalue(double fn, int K) {
    double c = 0.7 - 0.8 / L + (4. + 32. / L) *
            pow(1. * K, - 3. / L) / 15.;
    double sigma = c * sqrt(variance / K);
    return erfc(fabs((fn - expectedValue) / sqrt(2) / sigma));
}


void Universal(const std::vector<uint8_t>& buf) {
    n *= 8;
    ChooseL();
    if (L == 0) {
        std::cout << "Short sequence";
        return;
    }
    int K = n / L - Q;
    std::cout << "n = "<< n << std::endl;
    std::cout << "L = "<< L << std::endl;
    std::cout << "Q = "<< Q << std::endl;
    std::cout << "K = "<< K << std::endl;

    std::vector<int> T = Initialize(buf);
    double sum = Examine(buf, K, T);
    double fn = sum / K;
    std::cout << "f_n = " << fn << std::endl;
    double pvalue = Pvalue(fn, K);
    std::cout << "pvalue = " << pvalue << std::endl;
    if (pvalue < 0.01) {
        std::cout << "\t\tNON-RANDOM\t\t" << std::endl;
    } else {
        std::cout << "\t\tRANDOM\t\t" << std::endl;
    }
}


int main() {
    int numOfSeq = 3;
    std::string fileName = "seq" + std::to_string(numOfSeq) +".bin";
    std::cout << "\t\t SEQ "<< numOfSeq << std::endl;
    std::vector<uint8_t> buf = ReadFile("../seq/" + fileName);
    Universal(buf);
    std::cout << "==========================================" << std::endl;
    return 0;
}
