#include<algorithm>
#include<cstdio>

using namespace std;

const int N = 100005;

int n, a[N], t[N];

inline void disc(){
	for(int i = 1; i <= n; i++)
		t[i] = a[i];
	sort(t+1, t+n+1);
	int len = unique(t+1, t+n+1) - (t+1);
	for(int i = 1; i <= n; i++)
		a[i] = lower_bound(t+1, t+len+1, a[i]) - t;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	disc();
	for(int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	return 0;
}
