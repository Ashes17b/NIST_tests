#include <iostream>
#include <iterator>
#include <complex>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <assert.h>
#include <algorithm>
#include <math.h>

using namespace std;
typedef complex<double> base;

class DiscreteFourierTransformTest{
    int n;
    void replaceZeros(vector<int> &v)
    {
        for(int i = 0; i < v.size(); ++i)
            if(v[i] == 0)
                v[i] = -1;
    }

    void fft (vector<base> & a, bool invert) {
        int n = (int) a.size();
        if (n <= 1)  return;

        vector<base> a0 ((n+1)/2),  a1 ((n+1)/2);
        for (int i=0, j=0; i<n-1; i+=2, ++j) {
            a0[j] = a[i];
            a1[j] = a[i+1];
        }
        if(n&1)
            a0[n/2] = a[n-1];
        fft (a0, invert);
        fft (a1, invert);

        double ang = 2*M_PI/n * (invert ? -1 : 1);
        base w (1),  wn (cos(ang), sin(ang));
        for (int i=0; i<n/2; ++i) {
            a[i] = a0[i] + w * a1[i];
            a[i+n/2] = a0[i] - w * a1[i];
            if (invert)
                a[i] /= 2,  a[i+n/2] /= 2;
            w *= wn;
        }
        if(n&1)
            a[n-1] = a0[n/2] + w * a1[n/2];;
    }

    vector<base> runFFT(vector<int> a)
    {
        vector<base> fa (a.begin(), a.end());
        fft (fa, false);
        return fa;
    }


    vector<double> getModuls(vector<base> v)
    {
        vector<double> ans(v.size());
        for(int i = 0; i < v.size(); ++i)
            ans[i] = abs(v[i]);
        return ans;
    }

    double getN1(vector<double> v, double T)
    {
        double ans = 0;
        for(int i = 0; i < v.size(); ++i)
            if(v[i] < T)
                ++ans;
        return ans;
    }




public:
    double run(vector<int> v)
    {
        int n = v.size();
        cerr << "Run FFT test\n";
        cerr << "n " << n<< endl;
        replaceZeros(v);


        cerr << "Start FFT\n";
        vector<base> S = runFFT(v);
        cerr << "End FFT\n";

        S.resize(v.size() / 2);
        vector<double> moduls = getModuls(S);

        cerr << endl;
        double T = sqrt(3.0*n);
        cerr <<"T "<< T << endl;
        double N0 = .95 * n / 2;
        cerr <<"N0 "<< N0 << endl;

        double N1 = getN1(moduls, T);
        cerr << moduls.size() << endl;
        cerr <<"N1 "<< N1 << endl;


        double d = (N1 - N0) /
            sqrt(n*0.95*0.05/2);

        cerr <<"d "<< d << endl;

        double p_value = erfc(abs(d)/ sqrt(2));

        cerr <<"P-value "<< p_value << endl;
        freopen("out.txt", "w", stdout);
        printf("%.8f\n", (float) p_value);
        return p_value;
    }
};

const char* file_name;

vector<int> readBinaryData()
{
    
	cerr << "Start reading\n";
    ifstream in(file_name, std::ios::binary);
	vector<char> myData;
	in.unsetf(std::ios::skipws);

	vector<int> ans;
	char c;
    in.get(c);
    while(in)
    {

        for(int i = 0; i < 8; ++i)
            if(c & ((char)(1<<i)))
                ans.push_back(1);
            else
                ans.push_back(0);
         reverse(ans.end()-8,ans.end());
         in.get(c);
    }
    int n = ans.size();
    while(n&(n-1)) --n;
    if(n > (1<<20)) n = (1<<20);
    ans.resize(n);
    cerr << "End reading\n";
	return ans;
}



void testSpect()
{
    vector<int> v;
    v = readBinaryData();
    cerr << v.size() << endl;
    for(int i = 0; i < v.size(); ++i){
        if(v[i]==0)
            v[i] = -1;
        assert(v[i]>=-1 && v[i] < 2);
    }

    //freopen("out.txt", "w", stdout);
    DiscreteFourierTransformTest DFTT;

    DFTT.run(v);
}


int main(int argc, const char* argv[])
{
	if(argc > 1)
    	file_name = argv[1];
    else
    	file_name = "data.in";
    testSpect();
    return 0;
}
