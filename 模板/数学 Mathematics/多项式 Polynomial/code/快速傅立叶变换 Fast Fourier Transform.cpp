#include<cmath>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 3000005;
const double PI = acos(-1);

inline int read(){
	int x = 0, fl = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9'){
		if(ch == '-')   fl = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * fl;
}

struct Complex{
	double real, imag;
	Complex():real(0),imag(0){}
	Complex(double r, double i){ real = r; imag = i; }
	Complex operator + (Complex &A){ return Complex(real+A.real,imag+A.imag); }
	Complex operator - (Complex &A){ return Complex(real-A.real,imag-A.imag); }
	Complex operator * (Complex &A){ return Complex(real*A.real-imag*A.imag,real*A.imag+imag*A.real); }
};

int lenf, leng, rev[N];
Complex f[N], g[N];

void fft(Complex A[], int n, int flag){ // flag == 1: fft; flag == -1: ifft (inverse fft)
	for(int i = 0; i < n; i++)
		if(i < rev[i])
			swap(A[i], A[rev[i]]);
	for(int m = 2; m <= n; m <<= 1){
		Complex wm( cos(2*PI/m), flag * sin(2*PI/m) ); // mth unit root
		for(int k = 0; k < n; k += m){
			Complex w(1, 0);
			for(int j = 0; j < m / 2; j++){
				Complex t = w * A[k+j+m/2], u = A[k+j];
				A[k+j] = u + t;
				A[k+j+m/2] = u - t;
				w = w * wm;
			}
		}
	}
	if(flag == -1)
		for(int i = 0; i < n; i++)
			A[i].real /= n;
}

int main(){
	lenf = read(); leng = read();
	for(int i = 0; i <= lenf; i++)
		f[i].real = read();
	for(int i = 0; i <= leng; i++)
		g[i].real = read();
	int n = 1, cntBit = 0;
	while(n <= lenf + leng){
		n <<= 1;
		cntBit++;
	}                           // n == 2^cntBit is a upper bound of lenf+leng
	for(int i = 0; i < n; i++)  // rev[k] is bit-reversal permutation of k
		rev[i] = ( rev[i>>1] >> 1 ) | ( (i&1) << (cntBit-1) );
	fft(f, n, 1);               // f[] used to be coefficients, now they're point-values
	fft(g, n, 1);               // g[] used to be coefficients, now they're point-values
	for(int i = 0; i < n; i++)  f[i] = f[i] * g[i];
	fft(f, n, -1);              // f[] used to be point-values, now they're coefficients
	for(int i = 0; i <= lenf + leng; i++)
		printf("%d ", (int)(f[i].real+0.5));
	return 0;
}
