#include<bits/stdc++.h>

using namespace std;

const int N = 50005;
const int SQRN = 305;

int n, a[N], add[SQRN];
vector<int> vec[SQRN];

int belong[N], sq;
int L[SQRN], R[SQRN];
inline void init(){
	sq = sqrt(n);
	for(int i = 1; i <= n; i++)
		belong[i] = (i - 1) / sq + 1;
	for(int i = 1; i <= belong[n]; i++){
		L[i] = (i - 1) * sq + 1;
		R[i] = i * sq;
	} R[belong[n]] = n;
}
inline void maintain(int x){
	vec[x].clear();
	for(int i = L[x]; i <= R[x]; i++)
		vec[x].emplace_back(a[i]);
	sort(vec[x].begin(), vec[x].end());
}
inline void modify(int l, int r, int val){
	for(int i = l; i <= min(R[belong[l]], r); i++)
		a[i] += val;
	maintain(belong[l]);
	if(belong[l] != belong[r]){
		for(int i = L[belong[r]]; i <= r; i++)
			a[i] += val;
		maintain(belong[r]);
	}
	for(int i = belong[l] + 1; i < belong[r]; i++){
		add[i] += val;
	}
}
inline int query(int l, int r, int x){
	int res = 0;
	for(int i = l; i <= min(R[belong[l]], r); i++){
		if(a[i] + add[belong[l]] < x)	res++;
	}
	if(belong[l] != belong[r]){
		for(int i = L[belong[r]]; i <= r; i++){
			if(a[i] + add[belong[r]] < x)	res++;
		}
	}
	for(int i = belong[l] + 1; i < belong[r]; i++){
		res += lower_bound(vec[i].begin(), vec[i].end(), x - add[i]) - vec[i].begin();
	}
	return res;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)	scanf("%d", &a[i]);
	init();
	for(int i = 1; i <= belong[n]; i++)	maintain(i);
	for(int i = 1; i <= n; i++){
		int opt, l, r, c; scanf("%d%d%d%d", &opt, &l, &r, &c);
		if(opt == 0)	modify(l, r, c);
		else	printf("%d\n", query(l, r, c * c));
	}
	return 0;
}