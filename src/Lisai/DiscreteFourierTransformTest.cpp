#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
// #include <stdio.h>
// #include <stdlib.h>
#include <cmath>
// #define TRSIZ 8
#define SWAP(a,b) tempr=(a); (a)=(b); (b)=tempr

using namespace std;

void dittt1(double * data1, int TRSIZ)
{
    double wtemp, wr, wpr, wpi, wi, theta;
    double tempr, tempi;
    int N = TRSIZ;
    int i = 0, j = 0, n = 0, k = 0, m = 0, isign = -1,istep,mmax;
    // double data1[2*TRSIZ] = {1,0,-1,0,1,0,1,0,-1,0,1,0,-1,0,1,0};

    double *data;
    data = &data1[0] - 1;
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
                // printf("\ni = %d ,j = %d, m = %d, wr = %f , wi = %f",(i-1)/2,(j-1)/2,m,wr,wi);
            }
            // printf("\nm = %d ,istep = %d, mmax = %d, wr = %f , wi = %f, Z = %f",m,istep,mmax,wr,wi,atan(wi/wr)/(6.28318530717959/(1.0*n/2)));
            wtemp = wr;
            wr += wtemp*wpr - wi*wpi;
            wi += wtemp*wpi + wi*wpr;
        }
        mmax = istep;
    }

    // print the results
    // printf("\nFourier components from the DIT algorithm:");
    // for (k = 0; k < 2*N; k +=2 )
    // printf("\n%f%f", data[k+1], data[k+2]);
}

void dittt(double * data1, int TRSIZ)
{
    double wtemp, wr, wpr, wpi, wi, theta;
    double tempr, tempi;
    int N = TRSIZ;
    int i = 0, j = 0, n = 0, k = 0, m = 0, isign = -1,istep,mmax;
    // double data1[2*TRSIZ] = {0,0,1,0,4,0,9,0,2,0,3,0,4,0,5,0};
    double *data;
    data = &data1[0] - 1;
    n = N*2;
    mmax = n/2;
    // calculate the FFT
    while (mmax >= 2) {
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
                tempr = data[i];
                tempi = data[i+1];
                data[i] = data[i] + data[j];
                data[i+1] = data[i+1] + data[j+1];
                data[j] = tempr - data[j];
                data[j+1] = tempi - data[j+1];
                tempr = wr*data[j] - wi*data[j+1];
                tempi = wr*data[j+1] + wi*data[j];
                data[j] = tempr;
                data[j+1] = tempi;
                // printf("\ni = %d ,j = %d, m = %d, wr = %f , wi = %f",(i-1)/2,(j-1)/2,m,wr,wi);
            }
            // printf("\nm = %d ,istep = %d, mmax = %d, wr = %f , wi = %f, Z = %f",m,istep,mmax,wr,wi,atan(wi/wr)/(6.28318530717959/(1.0*n/2)));
            wtemp = wr;
            wr += wtemp*wpr - wi*wpi;
            wi += wtemp*wpi + wi*wpr;
        }
        mmax = mmax/2;
    }
    // do the bit-reversal
    j = 1;
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
    // print the results
    // printf("\nFourier components from the DIF algorithm:");
    // for (k = 0; k < 2*N; k +=2 )
    // printf("\n%f%f", data[k+1], data[k+2]);
} // end of diftt()

void read_file(double * array, int n, string filename) {
    ifstream f(filename, ios::binary | ios::in);
    char c;
    int i = 0;
    int count = 0;
    while (f.get(c)){
        for ( auto j = 7; j >= 0; --j ) {
            array[i] = (((c >> j) & 1) * 2 - 1);
            array[i + 1] = 0;
            i += 2;

            count += 1;
            if (count >= n ) {
                cout << "Bits read : " << count << endl;
                f.close();
                return;
            }
        }
        
    }
    f.close();
}

int get_file_size(std::string filename) // path to file
{
    ifstream f(filename, ios::binary | ios::in);
    char c;
    int count = 0;
    while (f.get(c))
        count += 1;
    f.close();
    return count;
}

double test_result(double * X, int n) {
    double * m = new double [n / 2];
    int count = 0;
    double upperBound, percentile, N_l, N_o, d, p_value;

    for (int i = 0; i < n / 2; i ++)
    	m[i] = sqrt(pow(X[2*i],2)+pow(X[2*i+1],2)); 
    cout << "|>   m:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << m[i] << endl;
    }
    count = 0;				       /* CONFIDENCE INTERVAL */
	upperBound = sqrt(2.995732274*n);
    cout << "upperBound : " << upperBound << endl;
	for(int i = 0; i < n / 2; i ++)
		if ( m[i] < upperBound )
			count ++;
    cout << "Count : " << count << endl;
	percentile = (double)count/(n/2)*100;
	N_l = (double) count;       /* number of peaks less than h = sqrt(3*n) */
	N_o = (double) 0.95*n/2.0;
    cout << "N_o : " << N_o << " N_l : " << N_l << endl; 
	d = (N_l - N_o)/sqrt(n/4.0*0.95*0.05);
	p_value = erfc(fabs(d)/sqrt(2.0));
    cout << "pval : " << p_value << endl;
    delete [] m;
}

int main() {
    // dittt();

    string filename = "../seq/seq1.bin";
    cout << "File name : " << filename << endl;
    int i = 0, n = 0, n_ = 1;
    n = get_file_size(filename); // how much bytes in file
    cout << "Bytes in file : " << n << endl;
    n *= 8; // get numbers of bits
    cout << "Bits in file : " << n << endl;
    bool powerOfTwo = !(n == 0) && !(n & (n - 1));
    if (!(n == 0) && !(n & (n - 1))) {
        n_ = n;
    }
    else {
        while(n_ * 2 < n){
            n_ *= 2;
        }
    }
    // n_ = 16777216;
    cout << "How much bitch we will read : " << n_ << endl;
    double * complex_bits_array = new double[n_ * 2];
    clock_t t_start = clock();
    
    read_file(complex_bits_array, n_, filename);
    for (int i = 0; i < 50; i += 2) {
        cout << complex_bits_array[i] << ' ';
    }
    // for (int i = 0; i < 32; i+=2) {
    //     cout << complex_bits_array[i] << " "  << complex_bits_array[i + 1] << endl;
    // }
    cout << endl;
    printf("Time taken: %.2fs\n", (double)(clock() - t_start) / CLOCKS_PER_SEC);
    printf("Start DFT\n");
    t_start = clock();
    // dittt1(complex_bits_array, n_);
    for (int i = 0; i < 32; i+=2) {
        cout << complex_bits_array[i] << " "  << complex_bits_array[i + 1] << endl;
    }
    printf("Time taken: %.2fs\n", (double)(clock() - t_start) / CLOCKS_PER_SEC);

    // test_result(complex_bits_array, n_);

    delete [] complex_bits_array;
    return 0;

}
