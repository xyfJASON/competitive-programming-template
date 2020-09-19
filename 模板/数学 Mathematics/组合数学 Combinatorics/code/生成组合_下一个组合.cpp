#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 1005;

int n, a[N], r;

inline bool nextCombination(int a[], int n, int r){ // n elements, r-combination
	int i = r;
	while(a[i] == n - r + i)	i--;
	if(!i)	return false;
	a[i] = a[i] + 1;
	for(int j = i + 1; j <= r; j++)
		a[j] = a[i] + j - i;
	return true;
}

int main(){
	scanf("%d%d", &n, &r);
	for(int i = 1; i <= r; i++)
		scanf("%d", &a[i]);
	nextCombination(a, n, r);
	for(int i = 1; i <= r; i++)
		printf("%d ", a[i]);
	return 0;
}
