#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <ctime>
#include "cephes.h"

using namespace std;



double psi2(char * epsilon, int m, int n)
{
	int	max_value = (int)pow(2, m);
	double	sum;
	
	if ( (m == 0) || (m == -1) )
		return 0.0;

	int	*P = new int[max_value];

	for (int i = 0; i < max_value; i++ )
		P[i] = 0;

    int k = 0;
    int bit;

    // read first m bit:
    int i = 0, j = 0;
    int how_much_bits_is_counted = 0;
    for ( i; i < n && how_much_bits_is_counted < m; i ++ ) {
        for ( j = 7; j >= 0 && how_much_bits_is_counted < m; --j, how_much_bits_is_counted ++ ) {
            bit = ((epsilon[i] >> j) & 1);
            k += (bit & 1) * pow(2, m - how_much_bits_is_counted - 1);
        }
    }
	P[k] ++;  // cout << k << " "; // << endl;
    // cout << "i : " << i << " j : " << j << endl;
    int j_hat = j;
    // ok, read other bits:
    for ( i --; i < n; i ++ ) {
        for ( j = j_hat; j >= 0; --j ) {
            bit = ((epsilon[i] >> j) & 1);
            k = (k << 1) ^ (bit & 1);
            if ( k >= max_value) {
                k = k ^ max_value;
            }
            // cout << k << " ";
			P[k] ++;
        }
        j_hat = 7;
    }
    // its zeros at the end:
    for ( i = 0; i < m - 1; i ++ ) {
        bit = 0;
        k = (k << 1) ^ (bit & 1);
        if ( k >= max_value) {
            k = k ^ max_value;
        }
		P[k] ++;  // cout << k << " ";
    }
	// <-----

	// for (int i = 0; i < max_value; i ++) {
	// 	cout << "i:"  << i << " P: " << P[i] << endl;
	// }
	sum = 0.0;
	for (int i = 0; i < max_value; i++ )
		sum += pow(P[i], 2);
	sum = (sum * pow(2, m)/(double)n) - (double)n;
	delete [] P;
	cout << "m: " << m << ", sum: " << sum << endl;

    return sum;
}


void read_file(char * array, string filename) {
    ifstream f(filename, ios::binary | ios::in);
    char c;
    int i = 0;
    int count = 0;
    while (f.get(c)){
		array[i] = (int)c;
		i ++;
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

int main() {
    string filename = "../../seq/seq1.bin";
	cout << "Number of file? ";
	char s;
	cin >> s;
	filename[13] = s;
    cout << "File name : " << filename << endl;
    int i = 0, n = 0, n_ = 1, m = 2;

    n = get_file_size(filename); // how much bytes in file
    cout << "Bytes in file : " << n << endl;
	cout << "m? ";
	cin >> m;
	cout << "(m, n): (" << m << ", " << n << ")" << endl;
    char * bytes_array = new char[n];

	cout << "Reading file..." << endl;
	clock_t t_start = clock();

    read_file(bytes_array, filename);
	printf("Time taken: %.2fs\n", (double)(clock() - t_start) / CLOCKS_PER_SEC);

	// print first 10 bytes:
    for (int i = 0; i < 10; i ++) {
        cout << bytes_array[i] << " ";
    }
    cout << endl;
    // delete [] bytes_array;
    // return 0;
    long double	p_value1, p_value2, psim0, psim1, psim2, del1, del2;
	t_start = clock();
	psim0 = psi2(bytes_array, m, n);
	printf("Time taken for m = %d: %.2fs\n", m, (double)(clock() - t_start) / CLOCKS_PER_SEC);

	t_start = clock();
	psim1 = psi2(bytes_array, m-1, n);
	printf("Time taken for m = %d: %.2fs\n", m-1, (double)(clock() - t_start) / CLOCKS_PER_SEC);

	t_start = clock();
	psim2 = psi2(bytes_array, m-2, n);
	printf("Time taken for m = %d: %.2fs\n", m-2, (double)(clock() - t_start) / CLOCKS_PER_SEC);

    cout << "psim0: " << psim0 << endl;
    cout << "psim1: " << psim1 << endl; 
    cout << "psim2: " << psim2 << endl; 

	del1 = psim0 - psim1;
	del2 = psim0 - 2.0 * psim1 + psim2;
	cout << "del1: " << del1 << endl;
	cout << "del2: " << del2 << endl;

	p_value1 = cephes_igamc(pow(2, m-2), del1 / 2.0);
	p_value2 = cephes_igamc(pow(2, m-3), del2 / 2.0);
	cout << p_value1 << endl;
	cout << p_value2 << endl;

    delete [] bytes_array;
    return 0;
}