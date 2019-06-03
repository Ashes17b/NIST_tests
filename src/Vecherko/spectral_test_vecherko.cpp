#include "../libraries/spectral_test_vecherko.hpp"

namespace spectral_test {

    void Spectral_test_vecherko::read(std::string filename /* = "" */) {
        if (filename.empty())
            std::cerr << "Filename is undefined" << std::endl;
        else
            std::cout << "Read from(Spectral_test Vecherko) " << filename << std::endl;

        std::ifstream f(filename, std::ios::binary | std::ios::in);

        if (!f.is_open()) {
            std::cerr << "Could NOT find " + filename << std::endl;
            return;
        }

        _buffer.reserve(get_size_file(filename)*8);

        char c;
        while(f.get(c))
        {
            for(int i = 0; i < 8; ++i)
                if(c & ((char)(1<<i)))
                    _buffer.push_back(1);
                else
                    _buffer.push_back(0);
            reverse(_buffer.end()-8, _buffer.end());
        }
        auto n = _buffer.size();

        while(n & (n-1)) 
            --n;

        if(n > (1<<20)) 
            n = (1<<20);
        _buffer.resize(n);

        f.close();
    }

    double Spectral_test_vecherko::run_test() {
        std::cout << "Started performing spectral_test Vecherko" << std::endl;
        assert(!_buffer.empty());

        for(int i = 0; i < _buffer.size(); ++i) {
            if(_buffer[i] == 0)
                _buffer[i] = -1;
            assert(_buffer[i]>=-1 && _buffer[i] < 2);
        }

        replaceZeros(_buffer);

        std::vector<base> S = runFFT();

        S.resize(_buffer.size() / 2);
        std::vector<double> moduls = getModuls(S);

        double T = sqrt(3.0 * _buffer.size());
        double N0 = .95 * _buffer.size() / 2;

        double N1 = getN1(moduls, T);

        double d = (N1 - N0) / sqrt(_buffer.size()*0.95*0.05/2);

        double p_value = erfc(abs(d)/ sqrt(2));

        return p_value;
    }

    std::vector<base> Spectral_test_vecherko::runFFT() {
        std::vector<base> fa(_buffer.begin(), _buffer.end());
        fft(fa, false);
        return fa;
    }

    std::vector<double> Spectral_test_vecherko::getModuls(const std::vector<base> &v) {
        std::vector<double> ans(v.size());
        for(int i = 0; i < v.size(); ++i)
            ans[i] = abs(v[i]);
        return ans;
    }

    double Spectral_test_vecherko::getN1(const std::vector<double> &v, double T) {
        double ans = 0;
        for(int i = 0; i < v.size(); ++i)
            if(v[i] < T)
                ++ans;
        return ans;
    }

    void Spectral_test_vecherko::fft(std::vector<base> & a, bool invert) {
        int n = (int) a.size();
        if (n <= 1)  return;

        std::vector<base> a0 ((n+1)/2),  a1 ((n+1)/2);
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

    void Spectral_test_vecherko::replaceZeros(std::vector<int> &v) {
        for(int i = 0; i < v.size(); ++i)
            if(v[i] == 0)
                v[i] = -1;
    }

    std::size_t Spectral_test_vecherko::get_size_file(std::string filename) const {
        std::ifstream f(filename, std::ios::binary | std::ios::in | std::ifstream::ate);
        return f.tellg();
    }

} //namespace spectral_test