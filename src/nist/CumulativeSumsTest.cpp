/*
 * File:   CumulativeSumsTest.cpp
 * Author: jk
 *
 * Created on 14. Dezember 2010, 00:01
 */

#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

#include "Cephes.h"

#include "CumulativeSumsTest.h"

CumulativeSumsTest::CumulativeSumsTest(int _mode) :
    AbstractTest(),
    mode(_mode)
{
}


CumulativeSumsTest::~CumulativeSumsTest()
{
}

void CumulativeSumsTest::setMode(int _mode)
{
    mode = _mode;
}

int CumulativeSumsTest::getMode()
{
    return mode;
}


double CumulativeSumsTest::runTest()
{
/* original code:
void
CumulativeSums(int n)
{
	int		S, sup, inf, z, zrev, k;
	double	sum1, sum2, p_value;

	S = 0;
	sup = 0;
	inf = 0;
	for ( k=0; k<n; k++ ) {
		epsilon[k] ? S++ : S--;
		if ( S > sup )
			sup++;
		if ( S < inf )
			inf--;
		z = (sup > -inf) ? sup : -inf;
		zrev = (sup-S > S-inf) ? sup-S : S-inf;
	}

	// forward
	sum1 = 0.0;
	for ( k=(-n/z+1)/4; k<=(n/z-1)/4; k++ ) {
		sum1 += cephes_normal(((4*k+1)*z)/sqrt(n));
		sum1 -= cephes_normal(((4*k-1)*z)/sqrt(n));
	}
	sum2 = 0.0;
	for ( k=(-n/z-3)/4; k<=(n/z-1)/4; k++ ) {
		sum2 += cephes_normal(((4*k+3)*z)/sqrt(n));
		sum2 -= cephes_normal(((4*k+1)*z)/sqrt(n));
	}

	p_value = 1.0 - sum1 + sum2;

	fprintf(stats[TEST_CUSUM], "\t\t      CUMULATIVE SUMS (FORWARD) TEST\n");
	fprintf(stats[TEST_CUSUM], "\t\t-------------------------------------------\n");
	fprintf(stats[TEST_CUSUM], "\t\tCOMPUTATIONAL INFORMATION:\n");
	fprintf(stats[TEST_CUSUM], "\t\t-------------------------------------------\n");
	fprintf(stats[TEST_CUSUM], "\t\t(a) The maximum partial sum = %d\n", z);
	fprintf(stats[TEST_CUSUM], "\t\t-------------------------------------------\n");

	if ( isNegative(p_value) || isGreaterThanOne(p_value) )
		fprintf(stats[TEST_CUSUM], "\t\tWARNING:  P_VALUE IS OUT OF RANGE\n");

	fprintf(stats[TEST_CUSUM], "%s\t\tp_value = %f\n\n", p_value < ALPHA ? "FAILURE" : "SUCCESS", p_value);
	fprintf(results[TEST_CUSUM], "%f\n", p_value);

	// backwards
	sum1 = 0.0;
	for ( k=(-n/zrev+1)/4; k<=(n/zrev-1)/4; k++ ) {
		sum1 += cephes_normal(((4*k+1)*zrev)/sqrt(n));
		sum1 -= cephes_normal(((4*k-1)*zrev)/sqrt(n));
	}
	sum2 = 0.0;
	for ( k=(-n/zrev-3)/4; k<=(n/zrev-1)/4; k++ ) {
		sum2 += cephes_normal(((4*k+3)*zrev)/sqrt(n));
		sum2 -= cephes_normal(((4*k+1)*zrev)/sqrt(n));
	}
	p_value = 1.0 - sum1 + sum2;

	fprintf(stats[TEST_CUSUM], "\t\t      CUMULATIVE SUMS (REVERSE) TEST\n");
	fprintf(stats[TEST_CUSUM], "\t\t-------------------------------------------\n");
	fprintf(stats[TEST_CUSUM], "\t\tCOMPUTATIONAL INFORMATION:\n");
	fprintf(stats[TEST_CUSUM], "\t\t-------------------------------------------\n");
	fprintf(stats[TEST_CUSUM], "\t\t(a) The maximum partial sum = %d\n", zrev);
	fprintf(stats[TEST_CUSUM], "\t\t-------------------------------------------\n");

	if ( isNegative(p_value) || isGreaterThanOne(p_value) )
		fprintf(stats[TEST_CUSUM], "\t\tWARNING:  P_VALUE IS OUT OF RANGE\n");

	fprintf(stats[TEST_CUSUM], "%s\t\tp_value = %f\n\n", p_value < ALPHA ? "FAILURE" : "SUCCESS", p_value); fflush(stats[TEST_CUSUM]);
	fprintf(results[TEST_CUSUM], "%f\n", p_value); fflush(results[TEST_CUSUM]);
}

 */
    seekPos(0);
    uint64_t nob = getNrOfBits();

    if (nob < 100) {
        fprintf(stderr,"CumulativeSumsTest::runTest(): Data should contain at least 100 Bits!\n");
        return 0.0;
    }

    int     S, sup, inf, z, zrev, k;
    double  sum1, sum2, p_value;
    z = 0;
    zrev = 0;

    S = 0;
    sup = 0;
    inf = 0;
    for ( k=0; k<(int)nob; k++ ) {
            getBit(k) ? S++ : S--;
            if ( S > sup )
                    sup++;
            if ( S < inf )
                    inf--;
            z = (sup > -inf) ? sup : -inf;
            zrev = (sup-S > S-inf) ? sup-S : S-inf;
    }

    p_value = 0.0;
    if (mode == 0) {
        // forward
        sum1 = 0.0;
        for ( k=(-(int)nob/z+1)/4; k<=((int)nob/z-1)/4; k++ ) {
                sum1 += Cephes::cephes_normal(((4*k+1)*z)/sqrt(nob));
                sum1 -= Cephes::cephes_normal(((4*k-1)*z)/sqrt(nob));
        }
        sum2 = 0.0;
        for ( k=(-(int)nob/z-3)/4; k<=((int)nob/z-1)/4; k++ ) {
                sum2 += Cephes::cephes_normal(((4*k+3)*z)/sqrt(nob));
                sum2 -= Cephes::cephes_normal(((4*k+1)*z)/sqrt(nob));
        }

        p_value = 1.0 - sum1 + sum2;
    } else {
        // backwards
        sum1 = 0.0;
        for ( k=(-(int)nob/zrev+1)/4; k<=((int)nob/zrev-1)/4; k++ ) {
                sum1 += Cephes::cephes_normal(((4*k+1)*zrev)/sqrt(nob));
                sum1 -= Cephes::cephes_normal(((4*k-1)*zrev)/sqrt(nob));
        }
        sum2 = 0.0;
        for ( k=(-(int)nob/zrev-3)/4; k<=((int)nob/zrev-1)/4; k++ ) {
                sum2 += Cephes::cephes_normal(((4*k+3)*zrev)/sqrt(nob));
                sum2 -= Cephes::cephes_normal(((4*k+1)*zrev)/sqrt(nob));
        }
        p_value = 1.0 - sum1 + sum2;
    }

    return p_value;

}

