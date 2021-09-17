#include<cmath>
#include<cstdio>
#include<cstring>

using namespace std;

typedef unsigned long long ULL;

const int LEN = 100005;

char s[LEN];

ULL h[LEN], base = 233; // hash value of string s[1...i] is stored in h[i]
void Hash(char s[]){
	int len = (int)strlen(s+1);
	h[1] = s[1];
	for(int i = 2; i <= len; i++)
		h[i] = h[i-1] * base + s[i];
}
ULL getSubstring(int l, int r){ // get hash value of s[l...r]
	return h[r] - h[l-1] * pow(base, r - l + 1);
}

int main(){
	scanf("%s", s+1);
	Hash(s);
	int len = (int)strlen(s+1);
	for(int i = 1; i <= len; i++)
		printf("%lld\n", h[i]);
	return 0;
}
