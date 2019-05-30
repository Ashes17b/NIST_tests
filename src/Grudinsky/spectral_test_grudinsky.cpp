#include "../libraries/spectral_test_grudinsky.hpp"

namespace spectral_test {

    void Spectral_test_grudinsky::read(std::string filename) {
        if (filename.empty())
            std::cerr << "Filename is undefined" << std::endl;
        else
            std::cout << "Read from(Spectral_test Grudinsky) " << filename << std::endl;

        std::ifstream fin(filename, std::ios::binary);
        int n = get_size_file(filename);
        char * buf = new char[n];

        fin.read(buf, n);
        n *= 8;
        numbers_of_bits = n;
        int npow = pow(2, largest_pow(n));
        _buffer = new double [npow + 1];

        for(int i = 0; i < npow / 8; i++)
            for(int j = 7; j >= 0; j--)
                _buffer[i * 8 + 7 - j] = 2 * ((buf[i] >> j) & 1) - 1;
    }

    double Spectral_test_grudinsky::run_test() {
        std::cout << "Started performing spectral_test Grudinsky" << std::endl;
        int npow = pow(2, largest_pow(numbers_of_bits));
        double N0 = 0.95 * npow / 2;
        
        dittt(npow / 2);
        
        double T = sqrt(log(20) * npow);
        int N1 = 0;
        for(int i = 0; i < npow; i += 2)
            if(sqrt(pow(_buffer[i], 2) + pow(_buffer[i + 1], 2)) < T)
                N1++;

        double d = (N1 - N0) / sqrt(npow * 0.95 * 0.05 / 4);

        double p_value = erfc(fabs(d / sqrt(2)));
        delete [] _buffer;
        return p_value;
    }

    void Spectral_test_grudinsky::dittt(int size)
    {
        double wtemp, wr, wpr, wpi, wi, theta;
        double tempr, tempi;
        int N = size;
        int i = 0, j = 0, n = 0, k = 0, m = 0, isign = -1,istep,mmax;

        bytes data;
        data = &_buffer[0] - 1;
        n = N*2;
        j = 1;
        // do the bit-reversal
        for (i = 1; i < n; i += 2) {
            if (j > i) {
                std::swap(data[j], data[i]);
                std::swap(data[j+1], data[i+1]);
            }
            m = n >> 1;

            while (m >= 2 && j > m) {
                j -= m;
                m >>= 1;
            }
            j +=m;
        }
        mmax = 2;
        while (n > mmax) {
            istep = mmax << 1;
            theta = isign*(6.28318530717959/mmax);
            wtemp = sin(0.5*theta);
            wpr = -2.0*wtemp*wtemp;
            wpi = sin(theta);
            wr = 1.0;
            wi = 0.0;
            for (m = 1; m < mmax; m += 2) {
                for (i = m; i <= n; i += istep) {
                    j = i + mmax;
                    tempr = wr*data[j] - wi*data[j+1];
                    tempi = wr*data[j+1] + wi*data[j];
                    data[j] = data[i] - tempr;
                    data[j+1] = data[i+1] - tempi;
                    data[i] = data[i] + tempr;
                    data[i+1] = data[i+1] + tempi;
                }
                wtemp = wr;
                wr += wtemp*wpr - wi*wpi;
                wi += wtemp*wpi + wi*wpr;
            }
            mmax = istep;
        }
    }

    std::size_t Spectral_test_grudinsky::get_size_file(std::string filename) const {
        std::ifstream f(filename, std::ios::binary | std::ios::in | std::ifstream::ate);
        return f.tellg();
    }

    int Spectral_test_grudinsky::largest_pow(int n)
    {
        int i = 0;
        while(n != 1)
        {
            n /= 2;
            i++;
        }
        return i;
    }
    
    double Spectral_test_grudinsky::f(double x, double a) {
        return exp(-x) * pow(x, a - 1);
    }
} //namespace spectral_test