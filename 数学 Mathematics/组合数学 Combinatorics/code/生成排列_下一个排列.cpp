#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 1005;

int a[N], n;

inline bool nextPermutation(int a[], int n){
	int j = n - 1, k = n;
	while(a[j] >= a[j+1])	j--;
	if(!j)	return false;
	while(a[j] >= a[k])	k--;
	swap(a[k], a[j]);
	int l = j + 1, r = n;
	while(r > l)	swap(a[l++], a[r--]);
	return true;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		a[i] = i;
	do{
		for(int j = 1; j <= n; j++)
			printf("%d ", a[j]);
		putchar(10);
	}while(nextPermutation(a, n));
	return 0;
}
