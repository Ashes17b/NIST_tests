#include "../libraries/spectral_test_lisai.hpp"
#define SWAP(a,b) tempr=(a); (a)=(b); (b)=tempr

namespace spectral_test {

    void Spectral_test_lisai::read(std::string filename) {
        if (filename.empty())
            std::cerr << "Filename is undefined" << std::endl;
        else
            std::cout << "Read from(Spectral_test Lisai) " << filename << std::endl;

        std::ifstream f(filename, std::ios::binary | std::ios::in);
        std::size_t size = get_size_file(filename);

        size *= 8;
        int n_ = 1;      
        if (!(size == 0) && !(size & (size - 1))) {
            n_ = size;
        }
        else {
            while(n_ * 2 < size){
                n_ *= 2;
            }
        }
        numbers_of_bits = n_;
        n_ *= 2;
        if (!f.is_open()) {
            std::cerr << "Could NOT find " + filename << std::endl;
            return;
        }

        _buffer = new double[n_];

        char c;
        int i = 0, count_bit = 0;
        while (f.get(c)) {
            for (int j = 7; j >= 0; --j) {
                _buffer[i] = ((((c >> j) & 1) * 2) - 1);
                _buffer[i + 1] = 0;
                i += 2;

                count_bit += 1;
                if (count_bit >= numbers_of_bits ) {
                    f.close();
                    std::cout << "end of read" << std::endl;
                    return;
                }
            }
        }
        std::cout << "end of read" << std::endl;
        f.close();
    }

    double Spectral_test_lisai::run_test() {
        std::cout << "Started performing spectral_test Lisai" << std::endl;

        auto n = numbers_of_bits;
        double	p_value1, p_value2, psim0, psim1, psim2, del1, del2;
        
        dittt( n );
        double p_value = test_result( n );

        delete [] _buffer;
        return p_value;
    }

    void Spectral_test_lisai::dittt(int size)
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
                SWAP(data[j], data[i]);
                SWAP(data[j+1], data[i+1]);
            }
            m = n >> 1;

            while (m >= 2 && j > m) {
                j -= m;
                m >>= 1;
            }
            j +=m;
        }
        // calculate the FFT
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

    double Spectral_test_lisai::test_result( int n ) {
        double * m = new double [n / 2];
        int count = 0;
        double upperBound, percentile, N_l, N_o, d, p_value;

        for (int i = 0; i < n / 2; i ++)
            m[i] = sqrt(pow(_buffer[2*i],2)+pow(_buffer[2*i+1],2)); 

        count = 0;				       /* CONFIDENCE INTERVAL */
        upperBound = sqrt(2.995732274*n);
        for(int i = 0; i < n / 2; i ++)
            if ( m[i] < upperBound )
                count ++;
        percentile = (double)count/(n/2)*100;
        N_l = (double) count;       /* number of peaks less than h = sqrt(3*n) */
        N_o = (double) 0.95*n/2.0;
        d = (N_l - N_o)/sqrt(n/4.0*0.95*0.05);
        p_value = erfc(fabs(d)/sqrt(2.0));
        delete [] m;

        return p_value;
    }

    std::size_t Spectral_test_lisai::get_size_file(std::string filename) const {
        std::ifstream f(filename, std::ios::binary | std::ios::in | std::ifstream::ate);
        return f.tellg();
    }
} //namespace spectral_test