#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 1005;

int n;
char s[N];

inline void nextBitString(char s[], int n){ //s[n-1]s[n-2]...s[0] is a bit string which is not 11...1
	int k = 0;
	while(s[k] == '1'){
		s[k] = '0';
		k++;
	}
	s[k] = '1';
}

int main(){
	scanf("%d", &n);
	scanf("%s", s);
	for(int i = 0; i < n; i++)
		if(i < n - i - 1)
			swap(s[i], s[n-i-1]);
	nextBitString(s, n);
	for(int i = n-1; i >= 0; i--)
		putchar(s[i]);
	putchar(10);
	return 0;
}
