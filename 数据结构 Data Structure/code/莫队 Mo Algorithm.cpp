#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline LL gcd(LL a, LL b){ return b == 0 ? a : gcd(b, a % b); }

const int N = 50005;

int n, m, a[N];

int sq, belong[N];
struct Query{
	int id, l, r;
	pair<LL, LL> ans;
	bool operator < (const Query &A) const{
		return belong[l] == belong[A.l] ? r < A.r : belong[l] < belong[A.l];
	}
}q[N];

LL sum2, cnt[N];
inline void update(int pos, int val){
	sum2 -= 1ll * cnt[a[pos]] * cnt[a[pos]];
	cnt[a[pos]] += val;
	sum2 += 1ll * cnt[a[pos]] * cnt[a[pos]];
}

int main(){
	scanf("%d%d", &n, &m);
	sq = n / sqrt(m);
	for(int i = 1; i <= n; i++)	belong[i] = (i - 1) / sq + 1;
	for(int i = 1; i <= n; i++)	scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++)	scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
	sort(q+1, q+m+1);
	for(int i = 1, l = 1, r = 0; i <= m; i++){
		for(; l > q[i].l; l--)	update(l-1, 1);
		for(; r < q[i].r; r++)	update(r+1, 1);
		for(; l < q[i].l; l++)	update(l, -1);
		for(; r > q[i].r; r--)	update(r, -1);

		if(l == r){ q[i].ans.first = 0, q[i].ans.second = 1; continue; }
		LL up = (sum2 - (r - l + 1)), dn = 1ll * (r - l + 1) * (r - l);
		LL g = gcd(up, dn);
		up /= g, dn /= g;
		q[i].ans.first = up, q[i].ans.second = dn;
	}
	sort(q+1, q+m+1, [&](const Query &A, const Query &B){ return A.id < B.id;} );
	for(int i = 1; i <= m; i++)	printf("%lld/%lld\n", q[i].ans.first, q[i].ans.second);
	return 0;
}