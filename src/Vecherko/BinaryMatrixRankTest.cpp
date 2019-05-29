#include <iostream>
#include <complex>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <assert.h>
#include <algorithm>
#include <math.h>

using namespace std;

class BinaryMatrixRankTest{
    int getMatrixRank(std::vector<vector<int> > matrix, bool inv = false)
    {
        int n = matrix.size();
        int m = matrix[0].size();


        for(int i = 0; i < n; ++i)
        {
            if(matrix[i][i] == 0)
                for(int j = i + 1; j < n; ++j)
                {
                    if(matrix[j][i]){
                        for(int k = i; k < m; ++k)
                            swap(matrix[i][k], matrix[j][k]);
                        break;
                    }
                }
            if(matrix[i][i] == 0)
            {
                continue;
            }
            else{
                for(int j = i + 1; j < n; ++j)
                {
                    if(matrix[j][i]){
                        for(int k = i; k < m; ++k)
                            matrix[j][k]^=matrix[i][k];
                    }
                }
            }
        }

        int rnk = 0;
        if(inv == true)
        {
            for(int i = 0; i < n; ++i)
                if(vector<int>(m, 0) != matrix[i])
                    ++rnk;
        }
        else
        {
            vector<vector<int> > tmp = matrix;
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < m; ++j)
                    tmp[i][j] = matrix[n-i-1][m-j-1];
            return getMatrixRank(tmp, true);
        }
        return rnk;
    }

    double hiSqCompute(int f_m, int f_m_1, int N)
    {
        double ans = (f_m  - 0.2888*N)*(f_m  - 0.2888*N)/(0.2888*N);
        ans += (f_m_1  - 0.5776*N)*(f_m_1  - 0.5776*N)/(0.5776*N);
        ans += (N - f_m - f_m_1 - 0.1336*N)*
            (N - f_m - f_m_1 - 0.1336*N)/(0.1336*N);
        return ans;
    }

    public: void run(std::vector<int> data, int M = 32, int Q = 32)
    {
        cerr << "Test Rank\n";
        cerr << data.size() << endl;
        vector<vector<int> > bin_matrix(M, vector<int> (Q, 0));
        int cur = 0;
        int f_m = 0, f_m_1 = 0,  f_other = 0;
        while(data.size() >= cur + M * Q)
        {
            for(int i = 0; i < M; ++i)
            {
                for(int j = 0; j < Q; ++j)
                    bin_matrix[i][j] = data[cur++];
            }
            int rnq = getMatrixRank(bin_matrix);
            if(rnq == M)
                f_m++;
            else if(rnq == M-1)
                f_m_1++;
            else
                f_other++;
        }

        double hi_sq = hiSqCompute(f_m, f_m_1, f_m+f_m_1+f_other);
        cerr << "Hi square = "<<hi_sq << endl;
        double p_value = exp(-hi_sq/2.0);
        cerr << "P-value = " << p_value << endl;
        freopen("out.txt", "w", stdout);
        printf("%.8f", (float) p_value);

    }
};

const char* file_name;

vector<int> readBinaryData()
{
    vector<int> ans;
    ifstream in(file_name, std::ios::binary);
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
    //vector<int> nn(ans.begin() , ans.begin()+ 8000);
    in.close();
    return ans;
}


void testRank()
{
    //int arr[] = {0,1,0,1,1,0,0,1,0,0,1,0,1,0,1,0,1,1,1,1,0,0,1,1,1,0,1};
    //vector<int> v(arr, arr+27);
    vector<int> v = readBinaryData();
    BinaryMatrixRankTest brt;
    brt.run(v);
}

int main(int argc, const char* argv[])
{
	if(argc > 1)
    	file_name = argv[1];
    else
    	file_name = "data.in";
    testRank();
    return 0;
}
