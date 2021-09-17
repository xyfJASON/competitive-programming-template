#include<bits/stdc++.h>

using namespace std;

const double PI = acos(-1);

struct Complex{
	double real, imag;
	Complex(){ real = imag = 0; }
	Complex(double r, double i){ real = r, imag = i; }
	Complex operator + (Complex &A){ return Complex(real+A.real, imag+A.imag); }
	Complex operator - (Complex &A){ return Complex(real-A.real, imag-A.imag); }
	Complex operator * (Complex &A){ return Complex(real*A.real-imag*A.imag, real*A.imag+imag*A.real); }
};

namespace FFT{
	int n;
	vector<int> rev;
	inline void preprocess(int _n, int _m){
		int cntBit = 0;
		for(n = 1; n <= _n + _m; n <<= 1, cntBit++);
		// n == 2^cntBit is a upper bound of _n+_m
		rev.resize(n);
		for(int i = 0; i < n; i++)
			rev[i] = (rev[i>>1]>>1) | ((i&1) << (cntBit-1));
			// rev[k] is bit-reversal permutation of k
	}
	inline void fft(vector<Complex> &A, int flag){
		// flag == 1: DFT; flag == -1: IDFT
		A.resize(n);
		for(int i = 0; i < n; i++) if(i < rev[i]) swap(A[i], A[rev[i]]);
		for(int m = 2; m <= n; m <<= 1){
			Complex wm(cos(2*PI/m), flag * sin(2*PI/m));
			for(int k = 0; k < n; k += m){
				Complex w(1, 0);
				for(int j = 0; j < m / 2; j++){
					Complex t = w * A[k+j+m/2], u = A[k+j];
					A[k+j] = u + t, A[k+j+m/2] = u - t;
					w = w * wm;
				}
			}
		}
		if(flag == -1)
			for(int i = 0; i < n; i++)
				A[i].real /= n;
	}
}

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	vector<Complex> f(n+1), g(m+1);
	for(int i = 0; i <= n; i++)	scanf("%lf", &f[i].real);
	for(int i = 0; i <= m; i++)	scanf("%lf", &g[i].real);
	FFT::preprocess(n, m);
	FFT::fft(f, 1); // f used to be coefficients, now they're point-values
	FFT::fft(g, 1); // g used to be coefficients, now they're point-values
	for(int i = 0; i < FFT::n; i++)	f[i] = f[i] * g[i];
	FFT::fft(f, -1); // f used to be point-values, now they're coefficients
	for(int i = 0; i < n + m + 1; i++)
		printf("%d ", (int)(f[i].real+0.5));
	return 0;
}