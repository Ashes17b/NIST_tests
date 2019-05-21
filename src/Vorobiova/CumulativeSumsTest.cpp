#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>

using namespace std;



char* epsilon;

//функция распределения
double cephes_normal(double x) {
	double arg, result, sqrt2 = 1.414213562373095048801688724209698078569672;

	if (x > 0) {
		arg = x / sqrt2;
		result = 0.5 * (1 + erf(arg));
	}
	else {
		arg = -x / sqrt2;
		result = 0.5 * (1 - erf(arg));
	}

	return(result);
}

/*Целью этого теста является максимальное отклонение (от нуля) случайного блуждания, 
определяемое совокупной суммой скорректированных (-1, +1) цифр в последовательности.
Цель теста - определить, является ли
кумулятивная сумма частичных последовательностей,
встречающихся в тестируемой последовательности, слишком велика или слишком мала относительно ожидаемого поведения этой кумулятивной
суммы для случайных последовательностей. Эта накопительная сумма может рассматриваться как случайная прогулка.
Для случайной последовательности отклонения случайного блуждания должны быть близки к нулю. Для некоторых типов
неслучайных последовательностей отклонения этого случайного блуждания от нуля будут большими.*/
void CumulativeSums(int n) {
	int		S, sup, inf, z, zrev, k;
	double	sum1, sum2, p_value;

	S = 0;
	sup = 0;
	inf = 0;
	for (k = 0; k<n; k++) {
		epsilon[k] ? S++ : S--;
		if (S > sup)
			sup++;
		if (S < inf)
			inf--;
		//Наибольшая экскурсия из источника накопленных сумм в соответствующей (-1, +1) последовательности.
		z = (sup > -inf) ? sup : -inf;
		zrev = (sup - S > S - inf) ? sup - S : S - inf;
	}

	// forward
	sum1 = 0.0;
	for (k = (-n / z + 1) / 4; k <= (n / z - 1) / 4; k++) {
		sum1 += cephes_normal(((4 * k + 1)*z) / sqrt(n));
		sum1 -= cephes_normal(((4 * k - 1)*z) / sqrt(n));
	}
	sum2 = 0.0;
	for (k = (-n / z - 3) / 4; k <= (n / z - 1) / 4; k++) {
		sum2 += cephes_normal(((4 * k + 3)*z) / sqrt(n));
		sum2 -= cephes_normal(((4 * k + 1)*z) / sqrt(n));
	}

	p_value = 1.0 - sum1 + sum2;
	printf("%f %s\n\n", p_value, p_value < 0.01 ? "FAILURE" : "SUCCESS");
	
	// backwards
	sum1 = 0.0;
	for (k = (-n / zrev + 1) / 4; k <= (n / zrev - 1) / 4; k++) {
		sum1 += cephes_normal(((4 * k + 1)*zrev) / sqrt(n));
		sum1 -= cephes_normal(((4 * k - 1)*zrev) / sqrt(n));
	}
	sum2 = 0.0;
	for (k = (-n / zrev - 3) / 4; k <= (n / zrev - 1) / 4; k++) {
		sum2 += cephes_normal(((4 * k + 3)*zrev) / sqrt(n));
		sum2 -= cephes_normal(((4 * k + 1)*zrev) / sqrt(n));
	}
	p_value = 1.0 - sum1 + sum2;

	printf("%f %s\n\n", p_value, p_value < 0.01 ? "FAILURE" : "SUCCESS");
}


int main() {
	
	ifstream cin("../seq/seq" + to_string(8) + ".bin", ios_base::binary);
	cin.seekg(0, ios::end);
	int size = cin.tellg();
	epsilon = new char[8 * size];
	cin.seekg(0);
	char trash;
	for (int i = 0; i < 8 * size; ++i) {
		if (!(i & 7)) {
			cin.read(&trash, 1);
		}
		char shift = (i & 7);
		epsilon[i] = (trash >> shift) & 1;
	}
	CumulativeSums(8 * size);
	system("pause");
	return 0;
}
