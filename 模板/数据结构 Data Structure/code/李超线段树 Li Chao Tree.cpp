#include<algorithm>
#include<cstdio>

using namespace std;

const int N = 50005;

int T;
char opt[10];

inline double getVal(int x, double k, double b){ return k * x + b; }

struct segTree{
	int l, r;
	double k, b;
}tr[N<<2];
#define lid id<<1
#define rid id<<1|1
#define mid ((tr[id].l + tr[id].r) >> 1)
void build(int id, int l, int r){
	tr[id].l = l, tr[id].r = r;
	tr[id].k = 0, tr[id].b = 0; // in this code, there's a default line y=0
	if(tr[id].l == tr[id].r)    return;
	build(lid, l, mid);
	build(rid, mid+1, r);
}
void insert(int id, double k, double b){
	if(tr[id].l == tr[id].r){
		if(getVal(mid, k, b) > getVal(mid, tr[id].k, tr[id].b))
			tr[id].k = k, tr[id].b = b;
		return;
	}
	if(k > tr[id].k){
		if(getVal(mid, k, b) > getVal(mid, tr[id].k, tr[id].b))
			insert(lid, tr[id].k, tr[id].b), tr[id].k = k, tr[id].b = b;
		else  insert(rid, k, b);
	}
	else{
		if(getVal(mid, k, b) > getVal(mid, tr[id].k, tr[id].b))
			insert(rid, tr[id].k, tr[id].b), tr[id].k = k, tr[id].b = b;
		else    insert(lid, k, b);
	}
}
double query(int id, int x){
	if(tr[id].l == tr[id].r)    return getVal(x, tr[id].k, tr[id].b);
	if(x <= mid)    return max(getVal(x, tr[id].k, tr[id].b), query(lid, x));
	else    return max(getVal(x, tr[id].k, tr[id].b), query(rid, x));
}

int main(){
	scanf("%d", &T);
	build(1, 1, 50000);
	while(T--){
		scanf("%s", opt);
		if(opt[0] == 'Q'){
			int x; scanf("%d", &x);
//            printf("%.10f\n", query(1, x));
			printf("%d\n", (int)query(1, x) / 100);
		}
		else{
			double s, p;
			scanf("%lf%lf", &s, &p);
			insert(1, p, s - p);
		}
	}
	return 0;
}
