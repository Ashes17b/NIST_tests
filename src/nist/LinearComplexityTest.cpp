/*
 * File:   LinearComplexityTest.cpp
 * Author: jk
 *
 * Created on 13. Dezember 2010, 22:27
 */
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

#include "Cephes.h"
#include "Matrix.h"

#include "LinearComplexityTest.h"

LinearComplexityTest::LinearComplexityTest(bool _autoBlockSize, int blockSize) :
    AbstractTest(),
    autoBlockSize(_autoBlockSize),
    M(blockSize)
{
}


LinearComplexityTest::~LinearComplexityTest()
{
}

void LinearComplexityTest::setAutoBlockSize(bool enable)
{
    autoBlockSize = enable;
}

bool LinearComplexityTest::getAutoBlockSize()
{
    return autoBlockSize;
}

void LinearComplexityTest::setBlockSize(int _M)
{
    M = _M;
}

int LinearComplexityTest::getBlockSize()
{
    return M;
}


double LinearComplexityTest::runTest()
{
/* original code:
void
LinearComplexity(int M, int n)
{
	int       i, ii, j, d, N, L, m, N_, parity, sign, K = 6;
	double    p_value, T_, mean, nu[7], chi2;
	double    pi[7] = { 0.01047, 0.03125, 0.12500, 0.50000, 0.25000, 0.06250, 0.020833 };
	BitSequence  *T, *P, *B_, *C;

	N = (int)floor(n/M);
	if ( ((B_ = (BitSequence *) calloc(M, sizeof(BitSequence))) == NULL) ||
		 ((C  = (BitSequence *) calloc(M, sizeof(BitSequence))) == NULL) ||
		 ((P  = (BitSequence *) calloc(M, sizeof(BitSequence))) == NULL) ||
		 ((T  = (BitSequence *) calloc(M, sizeof(BitSequence))) == NULL) ) {
		printf("Insufficient Memory for Work Space:: Linear Complexity Test\n");
		if ( B_!= NULL )
			free(B_);
		if ( C != NULL )
			free(C);
		if ( P != NULL )
			free(P);
		if ( T != NULL )
			free(T);
		return;
	}


	fprintf(stats[TEST_LINEARCOMPLEXITY], "-----------------------------------------------------\n");
	fprintf(stats[TEST_LINEARCOMPLEXITY], "\tL I N E A R  C O M P L E X I T Y\n");
	fprintf(stats[TEST_LINEARCOMPLEXITY], "-----------------------------------------------------\n");
	fprintf(stats[TEST_LINEARCOMPLEXITY], "\tM (substring length)     = %d\n", M);
	fprintf(stats[TEST_LINEARCOMPLEXITY], "\tN (number of substrings) = %d\n", N);
	fprintf(stats[TEST_LINEARCOMPLEXITY], "-----------------------------------------------------\n");
	fprintf(stats[TEST_LINEARCOMPLEXITY], "        F R E Q U E N C Y                            \n");
	fprintf(stats[TEST_LINEARCOMPLEXITY], "-----------------------------------------------------\n");
	fprintf(stats[TEST_LINEARCOMPLEXITY], "  C0   C1   C2   C3   C4   C5   C6    CHI2    P-value\n");
	fprintf(stats[TEST_LINEARCOMPLEXITY], "-----------------------------------------------------\n");
	fprintf(stats[TEST_LINEARCOMPLEXITY], "\tNote: %d bits were discarded!\n", n%M);

	for ( i=0; i<K+1; i++ )
		nu[i] = 0.00;
	for ( ii=0; ii<N; ii++ ) {
		for ( i=0; i<M; i++ ) {
			B_[i] = 0;
			C[i] = 0;
			T[i] = 0;
			P[i] = 0;
		}
		L = 0;
		m = -1;
		d = 0;
		C[0] = 1;
		B_[0] = 1;

		// DETERMINE LINEAR COMPLEXITY
		N_ = 0;
		while ( N_ < M ) {
			d = (int)epsilon[ii*M+N_];
			for ( i=1; i<=L; i++ )
				d += C[i] * epsilon[ii*M+N_-i];
			d = d%2;
			if ( d == 1 ) {
				for ( i=0; i<M; i++ ) {
					T[i] = C[i];
					P[i] = 0;
				}
				for ( j=0; j<M; j++ )
					if ( B_[j] == 1 )
						P[j+N_-m] = 1;
				for ( i=0; i<M; i++ )
					C[i] = (C[i] + P[i])%2;
				if ( L <= N_/2 ) {
					L = N_ + 1 - L;
					m = N_;
					for ( i=0; i<M; i++ )
						B_[i] = T[i];
				}
			}
			N_++;
		}
		if ( (parity = (M+1)%2) == 0 )
			sign = -1;
		else
			sign = 1;
		mean = M/2.0 + (9.0+sign)/36.0 - 1.0/pow(2, M) * (M/3.0 + 2.0/9.0);
		if ( (parity = M%2) == 0 )
			sign = 1;
		else
			sign = -1;
		T_ = sign * (L - mean) + 2.0/9.0;

		if ( T_ <= -2.5 )
			nu[0]++;
		else if ( T_ > -2.5 && T_ <= -1.5 )
			nu[1]++;
		else if ( T_ > -1.5 && T_ <= -0.5 )
			nu[2]++;
		else if ( T_ > -0.5 && T_ <= 0.5 )
			nu[3]++;
		else if ( T_ > 0.5 && T_ <= 1.5 )
			nu[4]++;
		else if ( T_ > 1.5 && T_ <= 2.5 )
			nu[5]++;
		else
			nu[6]++;
	}
	chi2 = 0.00;
	for ( i=0; i<K+1; i++ )
		fprintf(stats[TEST_LINEARCOMPLEXITY], "%4d ", (int)nu[i]);
	for ( i=0; i<K+1; i++ )
		chi2 += pow(nu[i]-N*pi[i], 2) / (N*pi[i]);
	p_value = cephes_igamc(K/2.0, chi2/2.0);

	fprintf(stats[TEST_LINEARCOMPLEXITY], "%9.6f%9.6f\n", chi2, p_value); fflush(stats[TEST_LINEARCOMPLEXITY]);
	fprintf(results[TEST_LINEARCOMPLEXITY], "%f\n", p_value); fflush(results[TEST_LINEARCOMPLEXITY]);

	free(B_);
	free(P);
	free(C);
	free(T);
}
 */
    seekPos(0);
    uint64_t nob = getNrOfBits();
    if (nob < 1000000) {
        fprintf(stderr,"LinearComplexityTest::runTest(): "
                       "Data should contain at least 1000000 Bits!\n");
        return 0.0;
    }

    if (autoBlockSize) {
        // if set value is not ok, i.e. default value, then estimate M
        if (!((M >= 500) && (floor(nob/M) >= 200) && (M <= 5000))){
            M = (int)sqrt(nob);
            if (M > 5000)
                M = 5000;
            if (M < 500)
                M = 500;
        }
    }

    int       i, ii, j, d, N, L, m, N_, parity, sign, K = 6;
    double    p_value, T_, mean, nu[7], chi2;
    double    pi[7] = { 0.01047, 0.03125, 0.12500, 0.50000, 0.25000, 0.06250, 0.020833 };
    Matrix::BitSequence  *T, *P, *B_, *C;
    P = NULL;
    C = NULL;

    N = (int)floor(nob/M);

    if ((N < 200) || (M < 500) || (M > 5000)) {
        fprintf(stderr,"LinearComplexityTest::runTest(): "
                       "BlockSize does not fit 500 <= M <= 5000!\n");
        return 0.0;
    }

    if ( ((B_ = (Matrix::BitSequence *) calloc(M, sizeof(Matrix::BitSequence))) == NULL) ||
         ((C  = (Matrix::BitSequence *) calloc(M, sizeof(Matrix::BitSequence))) == NULL) ||
         ((P  = (Matrix::BitSequence *) calloc(M, sizeof(Matrix::BitSequence))) == NULL) ||
         ((T  = (Matrix::BitSequence *) calloc(M, sizeof(Matrix::BitSequence))) == NULL) )
    {
        fprintf(stderr,"LinearComplexityTest::runTest(): "
                       "Insufficient Memory for Work Space!\n");
        if ( B_!= NULL )
                free(B_);
        if ( C != NULL )
                free(C);
        if ( P != NULL )
                free(P);
        if ( T != NULL )
                free(T);
        return 0.0;
    }


    for ( i=0; i<K+1; i++ )
            nu[i] = 0.00;
    for ( ii=0; ii<N; ii++ ) {
            for ( i=0; i<M; i++ ) {
                    B_[i] = 0;
                    C[i] = 0;
                    T[i] = 0;
                    P[i] = 0;
            }
            L = 0;
            m = -1;
            d = 0;
            C[0] = 1;
            B_[0] = 1;

            // DETERMINE LINEAR COMPLEXITY
            N_ = 0;
            while ( N_ < M ) {
                    d = (int)getBit(ii*M+N_);
                    for ( i=1; i<=L; i++ )
                            d += C[i] * getBit(ii*M+N_-i);
                    d = d%2;
                    if ( d == 1 ) {
                            for ( i=0; i<M; i++ ) {
                                    T[i] = C[i];
                                    P[i] = 0;
                            }
                            for ( j=0; j<M; j++ )
                                    if ( B_[j] == 1 )
                                            P[j+N_-m] = 1;
                            for ( i=0; i<M; i++ )
                                    C[i] = (C[i] + P[i])%2;
                            if ( L <= N_/2 ) {
                                    L = N_ + 1 - L;
                                    m = N_;
                                    for ( i=0; i<M; i++ )
                                            B_[i] = T[i];
                            }
                    }
                    N_++;
            }
            if ( (parity = (M+1)%2) == 0 )
                    sign = -1;
            else
                    sign = 1;
            mean = M/2.0 + (9.0+sign)/36.0 - 1.0/pow(2, M) * (M/3.0 + 2.0/9.0);
            if ( (parity = M%2) == 0 )
                    sign = 1;
            else
                    sign = -1;
            T_ = sign * (L - mean) + 2.0/9.0;

            if ( T_ <= -2.5 )
                    nu[0]++;
            else if ( T_ > -2.5 && T_ <= -1.5 )
                    nu[1]++;
            else if ( T_ > -1.5 && T_ <= -0.5 )
                    nu[2]++;
            else if ( T_ > -0.5 && T_ <= 0.5 )
                    nu[3]++;
            else if ( T_ > 0.5 && T_ <= 1.5 )
                    nu[4]++;
            else if ( T_ > 1.5 && T_ <= 2.5 )
                    nu[5]++;
            else
                    nu[6]++;
    }
    chi2 = 0.00;
    for ( i=0; i<K+1; i++ )
            chi2 += pow(nu[i]-N*pi[i], 2) / (N*pi[i]);
    p_value = Cephes::cephes_igamc(K/2.0, chi2/2.0);

    free(B_);
    free(P);
    free(C);
    free(T);

    return p_value;
}

