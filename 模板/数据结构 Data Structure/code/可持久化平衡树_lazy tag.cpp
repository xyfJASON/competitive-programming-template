#include<cstdio>
#include<algorithm>

using namespace std;

typedef long long LL;

const int N = 200005;

int m, qv, opt, qx, qy;
LL lastans = 0ll;

struct Treap{
	int son[2], size, hp;
	LL val, sum;
	bool rev;
}tr[N*100];

int root[N], cnt;
inline int newNode(LL val = 0){
	++cnt;
	tr[cnt].son[0] = tr[cnt].son[1] = 0;
	tr[cnt].size = 1;
	tr[cnt].hp = rand();
	tr[cnt].val = tr[cnt].sum = val;
	tr[cnt].rev = 0;
	return cnt;
}
inline void pushup(int id){
	if(!id)	return;
	tr[id].sum = tr[id].val;
	tr[id].size = 1;
	if(tr[id].son[0]){
		tr[id].sum += tr[tr[id].son[0]].sum;
		tr[id].size += tr[tr[id].son[0]].size;
	}
	if(tr[id].son[1]){
		tr[id].sum += tr[tr[id].son[1]].sum;
		tr[id].size += tr[tr[id].son[1]].size;
	}
}
inline void pushdown(int id){
	if(tr[id].rev){
		if(tr[id].son[0]){
			Treap tmp = tr[tr[id].son[0]];
			tr[id].son[0] = newNode();
			tr[tr[id].son[0]] = tmp;
			tr[tr[id].son[0]].rev ^= 1;
			swap(tr[tr[id].son[0]].son[0], tr[tr[id].son[0]].son[1]);
		}
		if(tr[id].son[1]){
			Treap tmp = tr[tr[id].son[1]];
			tr[id].son[1] = newNode();
			tr[tr[id].son[1]] = tmp;
			tr[tr[id].son[1]].rev ^= 1;
			swap(tr[tr[id].son[1]].son[0], tr[tr[id].son[1]].son[1]);
		}
		tr[id].rev ^= 1;
	}
}
inline void splitSize(int id, int k, int &x, int &y){
	if(!id){
		x = y = 0;
		return;
	}
	pushdown(id);
	if(tr[tr[id].son[0]].size >= k){
		tr[y = newNode()] = tr[id];
		splitSize(tr[y].son[0], k, x, tr[y].son[0]);
		pushup(y);
	}
	else{
		tr[x = newNode()] = tr[id];
		splitSize(tr[x].son[1], k - tr[tr[id].son[0]].size - 1, tr[x].son[1], y);
		pushup(x);
	}
}
inline int merge(int a, int b){
	if(a == 0 || b == 0)	return a + b;
	if(tr[a].hp <= tr[b].hp){
		pushdown(a);
		tr[a].son[1] = merge(tr[a].son[1], b);
		pushup(a);
		return a;
	}
	else{
		pushdown(b);
		tr[b].son[0] = merge(a, tr[b].son[0]);
		pushup(b);
		return b;
	}
}
inline void insert(int &cur, int pos, LL val){
	int L = 0, R = 0;
	splitSize(cur, pos, L, R);
	cur = merge(merge(L, newNode(val)), R);
}
inline void del(int &cur, int pos){
	int L = 0, T = 0, R = 0;
	splitSize(cur, pos, L, R);
	splitSize(L, pos-1, L, T);
	cur = merge(L, R);
}
inline void reverse(int &cur, int l, int r){
	int L = 0, T = 0, R = 0;
	splitSize(cur, r, L, R);
	splitSize(L, l-1, L, T);
	tr[T].rev ^= 1;
	swap(tr[T].son[0], tr[T].son[1]);
	cur = merge(merge(L, T), R);
}
inline LL querySum(int &cur, int l, int r){
	int L = 0, T = 0, R = 0;
	splitSize(cur, r, L, R);
	splitSize(L, l-1, L, T);
	LL res = tr[T].sum;
	cur = merge(merge(L, T), R);
	return res;
}

int main(){
	srand(20010130);
	scanf("%d", &m);
	for(int k = 1; k <= m; k++){
		scanf("%d%d", &qv, &opt);
		root[k] = root[qv];
		if(opt == 1){
			scanf("%d%d", &qx, &qy);
			qx ^= lastans; qy ^= lastans;
			insert(root[k], qx, qy);
		}
		else if(opt == 2){
			scanf("%d", &qx);
			qx ^= lastans;
			del(root[k], qx);
		}
		else if(opt == 3){
			scanf("%d%d", &qx, &qy);
			qx ^= lastans; qy ^= lastans;
			reverse(root[k], qx, qy);
		}
		else if(opt == 4){
			scanf("%d%d", &qx, &qy);
			qx ^= lastans; qy ^= lastans;
			printf("%lld\n", lastans = querySum(root[k], qx, qy));
		}
	}
	return 0;
}
