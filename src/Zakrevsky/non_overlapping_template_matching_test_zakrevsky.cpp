#include "../libraries/non_overlapping_template_matching_test_zakrevsky.hpp"
#include "../libraries/cephes.h"

namespace non_overlapping_template_matching_test {

    void Non_overlapping_template_matching_test_zakrevsky::read(std::string filename /* = "" */) {
        if (filename.empty())
            std::cerr << "Filename is undefined" << std::endl;
        else 
            std::cout << "Read from(Non_overlapping_template_matching_test Zakrevsky) " << filename << std::endl;
        
        std::ifstream f(filename, std::ios::binary | std::ios::in);

        if (!f.is_open()) {
            std::cerr << "Could NOT find " + filename << std::endl;
            return;
        }

        f.seekg(0, std::ios::end);
        size = f.tellg();
        f.seekg(0, std::ios::beg);
       
        char c;
        while(f.get(c))
            _buffer.push_back(c);
    
        size *= 8;

        f.close();
    }

    double Non_overlapping_template_matching_test_zakrevsky::run_test() const {
        std::cout << "Started performing non_overlapping_template_matching_test Zakrevsky" << std::endl;
        assert(!_buffer.empty());
        int M = (int)(0.1*size);
        int N = floor((double)size/M);
        int * temp = new int[m];
        init(temp,m);
        long long* counters = new long long[N];
        for (int i = 0; i < N; i++) {
            counters[i] = counter(i, (int)M / 8, temp);
        }
        double mean = (M - m + 1) / pow(2, m), disp = M*((1/ pow(2, m))-(2*m-1)/ pow(2, 2*m));
        double stat = 0;
        for (int i = 0; i < N; i++)
            stat += pow(counters[i] - mean, 2) / disp;
        delete[] temp;
        return cephes_igamc(N / 2, stat / 2);
    }

    long long Non_overlapping_template_matching_test_zakrevsky::counter(int pos ,int buf_size, int* temp) const {
        long long counter_l = 0;
        int temp_counter = 0;
        for (int i = pos*buf_size; i < (pos+1)*buf_size; i++) {
            for (int j = 7; j >= 0; --j) {
                if (((_buffer[i] >> j) & 1) == temp[temp_counter]) {
                    temp_counter++;
                    if (temp_counter == m) {
                        counter_l++;
                        temp_counter = 0;
                    }
                }
                else {
                    j += temp_counter;
                    temp_counter = 0;
                    if (j > 7) {
                        i--;
                        j -= 8;
                    }
                }
            }
	    }
	    return counter_l;
    }
    double Non_overlapping_template_matching_test_zakrevsky::gamma_inc(double a, double x) const {
        double sum = 0;
        double term = 1.0 / a;
        int n = 1;
        while (term != 0) {
            sum = sum + term;
            term = term*(x / (a + n));
            n++;
        }
        return pow(x, a)*exp(-1 * x)*sum;
    }

    float Non_overlapping_template_matching_test_zakrevsky::poisson_z(float x, float mu) const {
        static const float twoThirds = 2.0f / 3.0f;
        float w = sqrt((x + 0.5f) / mu) - 1.0f;
        float coeff = w >= 0.0f ? 0.085f : 0.15f;
        return (x - mu + twoThirds) / sqrtf(mu*(1.0f + w*(0.68f + w*coeff)));
    }


    void Non_overlapping_template_matching_test_zakrevsky::init(int* mas, int m) const {
        for (int i = 0; i < m; i++) {
            if (temoString[i] == '0')
                mas[i] = 0;
            else
                mas[i] = 1;
        }
    }

} //namespace non_overlapping_template_matching_test