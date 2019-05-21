#include <boost/math/special_functions/gamma.hpp>
#include <iostream>
#include <fstream>
#include "Source.h"


using namespace std;
const int m = 9;//10
string temoString = "100010001";//template


long long counter(char* buf, int pos ,int buf_size, int* temp) {
	long long counter_l = 0;
	int temp_counter = 0;
	for (int i = pos*buf_size; i < (pos+1)*buf_size; i++) {
		for (int j = 7; j >= 0; --j) {
			if (((buf[i] >> j) & 1) == temp[temp_counter]) {
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
double gamma_inc(double a, double x)
{
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

float poisson_z(float x, float mu) {
	static const float twoThirds = 2.0f / 3.0f;
	float w = sqrt((x + 0.5f) / mu) - 1.0f;
	float coeff = w >= 0.0f ? 0.085f : 0.15f;
	return (x - mu + twoThirds) / sqrtf(mu*(1.0f + w*(0.68f + w*coeff)));
}


void init(int* mas, int m) {
	for (int i = 0; i < m; i++) {
		if (temoString[i] == '0')
			mas[i] = 0;
		else
			mas[i] = 1;
	}
}

int main() {
	ifstream in("D:\\Downloads\\Visual Studio 2015\\Projects\\Lab_Test7\\seq8.bin", ios::binary);
	in.seekg(0, ios::end); // если курсор в начале файла, перемещаем курсор в конец файла.
	int n = in.tellg(); // функция выдаст конечное положнние курсора относительно начала файла в байтах.
	in.seekg(0, ios::beg);
	char * buf = new char[n];
	in.read(buf, n); 
	n *= 8;
	int M = (int)(0.1*n);
	int N = floor((double)n/M);
	int * temp = new int[m];
	init(temp,m);
	for (int i = 0;i < m;i++)
		cout<<temp[i]<<' ';
	cout << endl;
	long long* counters = new long long[N];
	for (int i = 0; i < N; i++) {
		counters[i] = counter(buf, i, (int)M / 8, temp);
		cout << counters[i] <<endl;
	}
	double mean = (M - m + 1) / pow(2, m), disp = M*((1/ pow(2, m))-(2*m-1)/ pow(2, 2*m));
	cout << mean << " " << disp << endl;
	double stat = 0;
	for (int i = 0; i < N; i++)
		stat += pow(counters[i] - mean, 2) / disp;
	cout<<boost::math::gamma_q(N/2,stat/2)<<endl;
	cout << cephes_igamc(N / 2, stat / 2) << endl;
	in.close();
	delete[] temp;
	delete[] buf;
	return 0;
}