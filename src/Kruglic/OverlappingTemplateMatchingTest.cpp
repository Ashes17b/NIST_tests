#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>


int m = 13;

int n;
int K = 5;
int M = pow(2., 14);


int Counter(const std::vector<uint8_t>& buf, int numberOfBlock, int blockSize) {
    int counter_l = 0;
    int counter = 0;
    for (size_t i = numberOfBlock * blockSize * 8; i < (numberOfBlock + 1) * blockSize * 8; ++i) {
        uint32_t idx = i >> 3;
        uint8_t bias = (i & 7);
        if (buf[idx] & (1 << bias)) {
            ++counter_l;
        } else {
            counter_l = 0;
        }
        if (counter_l >= m) {
            ++counter;
        }
    }
    return counter;
}


double Pi(int u, double eta) {
    int	l;
    double	sum, p;
    if (u == 0) {
        p = exp(-eta);
    } else {
        sum = 0.0;
        for (l = 1; l <= u; l++)
            sum += exp(-eta - u * log(2) + l * log(eta)
                    - lgamma(l + 1) + lgamma(u) -
                    lgamma(l) -lgamma(u - l + 1));
        p = sum;
    }
    return p;
}


double MyIgamc(double chi2) {
    if (!(K & 1)) {
        double sum = 1;
        double prev = 1;
        double x = chi2 / 2.;
        int fact = 1;
        int s = K / 2;
        for (int i = 1; i < s; ++i) {
            prev *= x;
            prev /= i;
            sum += prev;
            fact *= i;
        }
        double gamma = fact * sum * exp(-x);
        return gamma / tgamma(s);
    } else {
        double s = 1. * K / 2.;
        double x = chi2 / 2.;
        double firstGamma = sqrt(acos(-1)) * erfc(sqrt(x));
        double nextGamma = 0;
        double k = 0.5;
        double x_power = sqrt(x);
        while (k < s - 0.5) {
            nextGamma = k * firstGamma + x_power * exp(-x);
            firstGamma = nextGamma;
            ++k;
            x_power *= x;
        }
        return nextGamma / tgamma(s);
    }
}


void OverlappingTemplateMatchings(const std::vector<uint8_t>& buf) {

    n *= 8;
    std::cout << "n = " << n << " - the length in bits  " << std::endl;

    std::cout << "m = " << m << " - the length in bits of the template " << std::endl;
    if (pow(2, m) / (1. * M) > 2) {
        std::cout << "Bad m";
        return;
    }

    /*M, N*/
    std::cout << "M = " << M << std::endl;
    int N = n / M;
    std::cout << "N = " << N << std::endl;
    if (N <= 0) {
        std::cout << "N <= 0";
        return;
    }
    std::cout << "check  M * N = " << M * N << std::endl;
    if (n - N * M < 0) {
        std::cout << "n - N * M < 0";
        return;
    }

    /*lambda, eta*/
    double lambda = (1. * M - 1. * m + 1.) / pow(2, m);
    std::cout << "lambda = " << lambda << std::endl;
    if (lambda > 3 || lambda < 1) {
        std::cout << "Bad lambda";
        return;
    }
    double eta = lambda / 2.;
    std::cout << "eta = " << eta << std::endl;

    /*nu*/
    std::ofstream cout("output.txt");
    std::vector<int> nu(K + 1, 0);
    for (size_t i = 0; i < N; ++i) {
        int count = Counter(buf, i, (int) M / 8); //???
        if (count < K) {
            nu[count]++;
        } else {
            nu[K]++;
        }
    }

    /*PI*/
    std::vector<double> pi(K + 1);
    if (K == 5 && m == 9) {
        pi = {0.364091, 0.185659, 0.139381, 0.100571, 0.0704323, 0.139865};
        std::cout << "pi = ";
        for (auto i: pi) {
            std::cout << i << " ";
        }
        std::cout << "check N * min{pi} =  " << N * 0.0704323 << " > 5" << std::endl;
        if (N * 0.0704323 < 5) {
            std::cout << "No, N * min{pi} < 5" << std::endl;
            return;
        }
    } else {
        double sum = 0.;
        double min = 2;
        for (size_t i = 0; i < K; i++) {
            pi[i] = Pi(i, eta);
            if (min > pi[i]) {
                min = pi[i];
            }
            sum += pi[i];
        }

        pi[K] = 1 - sum;
        if (min > pi[K]) {
            min = pi[K];
        }
        std::cout << "pi = ";
        for (auto i: pi) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        std::cout << "check N * min{pi} =  " << N * min << " > 5" << std::endl;
        if (N * min < 5) {
            std::cout << "No, N * min{pi} < 5" << std::endl;
            return;
        }
    }
    std::cout << "nu = ";
    for (auto item: nu) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    std::cout << "PI * N = ";
    for (auto item: pi) {
        std::cout << item * N << " ";
    }
    std::cout << std::endl;

    /*Check*/
    double chi2 = 0.;
    for (size_t i = 0; i < K + 1; ++i) {
        chi2 += pow(1. * nu[i] - 1. * N * pi[i], 2) / pi[i];
    }
    chi2 /= (double)N;
    std::cout << "chi2 = " << chi2 << std::endl;

    double p_value = MyIgamc(chi2);
    std::cout << "pvalue = " << p_value << std::endl;
    if (p_value < 0.01) {
        std::cout << "\t\tNON-RANDOM\t\t" << std::endl;
    } else {
        std::cout << "\t\tRANDOM\t\t" << std::endl;
    }

}


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


int main() {
    int numOfSeq = 7;
    std::string fileName = "seq" + std::to_string(numOfSeq) +".bin";
    std::cout << "\t\t SEQ "<< numOfSeq << std::endl;
    std::vector<uint8_t> buf = ReadFile("../seq/" + fileName);
    OverlappingTemplateMatchings(buf);
    std::cout << "======================================================" << std::endl;

    return 0;
}
