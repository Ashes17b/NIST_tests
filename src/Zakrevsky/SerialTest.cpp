#include <boost/math/special_functions/gamma.hpp>
#include <iostream>
#include <fstream>


using namespace std;
const int r = 2;//до 23-24
const int k = pow(2, r);


void counter(char* buf, int m, int* temp, int n, int w) {
	int number = 0;
	int first = 0;
	int exit = m;
	while (exit >= 8)
		exit -= 8;
	int local_k = pow(2, m);
	//	long counter_l = 0;
	//	int temp_counter = 0;
	for (int i = 0; i < n + w; i++) {
		for (int j = 7; j >= 0; --j) {
			if (first != m) {
				first++;
				number = number << 1;
				number += (buf[i] >> j) & 1;
			}
			else {
				//cout << number<<endl;
				number = number << 1;
				number += (buf[i] >> j) & 1;
				if (number >= local_k)
					number -= local_k;
				temp[number]++;
			}
			if (i == n + w - 1 && j == 7 - exit + 1)
				return;
		}
	}
	return;
}



int main() {
	ifstream in("D:\\Downloads\\Visual Studio 2015\\Projects\\Lab_Test7\\seq7.bin", ios::binary);
	in.seekg(0, ios::end); // если курсор в начале файла, перемещаем курсор в конец файла.
	int n = in.tellg(); // функция выдаст конечное положнние курсора относительно начала файла в байтах.
	in.seekg(0, ios::beg);
	int w = ceil((r - 1) / 8);
	char * buf = new char[n + w];
	in.read(buf, n);
	in.close();
	for (int i = 0; i < w; i++) {
		buf[n + i] = 0;
	}
	n *= 8;

	int * masM = new int[pow(2, r)];
	int * masM_1 = new int[pow(2, r - 1)];
	int * masM_2 = new int[pow(2, r - 2)];

	//заполнение
	for (int i = 0; i < pow(2, r); i++) {
		masM[i] = 0;
	}
	for (int i = 0; i < pow(2, r - 1); i++) {
		masM_1[i] = 0;
	}
	for (int i = 0; i < pow(2, r - 2); i++) {
		masM_2[i] = 0;
	}


	counter(buf, r, masM, n / 8, w);
	for (int i = 0; i < pow(2, r); i++) {
		cout << masM[i] << endl;
	}
	cout << endl;
	counter(buf, r - 1, masM_1, n / 8, w);
	for (int i = 0; i < pow(2, r - 1); i++) {
		cout << masM_1[i] << endl;
	}
	cout << endl;
	counter(buf, r - 2, masM_2, n / 8, w);
	for (int i = 0; i < pow(2, r - 2); i++) {
		cout << masM_2[i] << endl;
	}
	cout << endl;
	double fiM = 0, fiM_1 = 0, fiM_2 = 0;
	for (int i = 0; i < pow(2, r); i++) {
		fiM += pow(masM[i], 2);
	}
	fiM /= n;
	fiM *= pow(2, r);
	for (int i = 0; i < pow(2, r - 1); i++) {
		fiM_1 += pow(masM_1[i], 2);
	}
	fiM_1 /= n ;
	fiM_1 *= pow(2, r-1);
	for (int i = 0; i < pow(2, r - 2); i++) {
		fiM_2 += pow(masM_2[i], 2);
	}
	fiM_2 /= n ;
	fiM_2 *= pow(2, r-2);
	fiM -= n; fiM_1 -= n; fiM_2 -= n;
	cout << fiM << endl << fiM_1 << endl << fiM_2 << endl;
	double delta_m = fiM - fiM_1;
	double delta2_m = fiM - 2 * fiM_1 + fiM_2;
	cout << endl;
	cout << pow(2, r - 2) <<" "<<delta_m << endl << pow(2, r - 3) <<" "<< delta2_m << endl;
	cout << boost::math::gamma_q(pow(2, r - 2), delta_m/2) << endl;
	cout << boost::math::gamma_q(pow(2, r - 3), delta2_m/2) << endl;
	//	cout << boost::math::gamma_q(N / 2, stat / 2) << endl;	
	delete[] buf;
	cout << "End?" << endl;
	delete[] masM;
	
	delete[] masM_1;
	delete[] masM_2;
	cout << "End" << endl;

	
	return 0;
}