#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 200005;
const LL INF = 1e16;

int n;
LL b[N];

struct Splay{
	int fa, son[2], size;
	LL val, sum, mn;
	void init(){
		fa = son[0] = son[1] = size = 0;
		val = sum = mn = 0;
	}
}tr[N];
#define which(x,fa) (tr[fa].son[1] == x)
int tot = 0, root = 0;
inline void pushup(int x){
	if(x){
		tr[x].size = 1, tr[x].sum = tr[x].mn = tr[x].val;
		if(tr[x].son[0]){
			tr[x].size += tr[tr[x].son[0]].size;
			tr[x].sum += tr[tr[x].son[0]].sum;
			tr[x].mn = min(tr[tr[x].son[0]].mn, tr[x].mn);
		}
		if(tr[x].son[1]){
			tr[x].size += tr[tr[x].son[1]].size;
			tr[x].sum += tr[tr[x].son[1]].sum;
			tr[x].mn = min(tr[tr[x].son[1]].mn, tr[x].mn);
		}
	}
}
inline void rotate(int x, int dir){
	// dir == 0: left, dir == 1: right
	int y = tr[x].fa, z = tr[y].fa, B = tr[x].son[dir];
	tr[z].son[which(y,z)] = x; tr[x].fa = z;
	tr[x].son[dir] = y; tr[y].fa = x;
	tr[y].son[dir^1] = B; tr[B].fa = y;
	pushup(y); pushup(x);
}
inline void splay(int x, int goal){
	// rotate x to the son of goal
	if(x == goal)    return;
	while(tr[x].fa != goal){
		int y = tr[x].fa, z = tr[y].fa, dir1 = which(x,y)^1, dir2 = which(y,z)^1;
		if(z == goal)	rotate(x, dir1);
		else{
			if(dir1 == dir2)	rotate(y, dir2);
			else	rotate(x, dir1);
			rotate(x, dir2);
		}
	}
	if(goal == 0)	root = x;
}
inline int selectNode(int x){
	// return id of x'th node on the tree
	int now = root;
	while(tr[tr[now].son[0]].size + 1 != x){
		if(tr[tr[now].son[0]].size + 1 > x)
			now = tr[now].son[0];
		else{
			x -= tr[tr[now].son[0]].size + 1;
			now = tr[now].son[1];
		}
	}
	return now;
}

inline int findlast(int x, LL k){
	// find the last node whose val < k in 2nd ~ xth node on the tree
	splay(selectNode(1), 0);
	splay(selectNode(x+1), root);
	int now = tr[tr[root].son[1]].son[0];
	int rk = 1;
	if(tr[now].mn >= k)    return -1;
	while(now && tr[now].mn < k){
		if(tr[now].son[1] && tr[tr[now].son[1]].mn < k)
			rk += tr[tr[now].son[0]].size + 1, now = tr[now].son[1];
		else if(tr[now].val < k){ rk += tr[tr[now].son[0]].size + 1; break; }
		else if(tr[now].son[0] && tr[tr[now].son[0]].mn < k)
			now = tr[now].son[0];
	}
	return rk; // rk: this node is rk'th node on the tree
}
inline LL getSum(int l, int r){
	// return the sum of nodes from l'th to r'th node on the tree
	splay(selectNode(l-1), 0);
	splay(selectNode(r+1), root);
	int now = tr[tr[root].son[1]].son[0];
	return tr[now].sum;
}
inline int del(int x){ // delete the x'th node on the tree
	splay(selectNode(x-1), 0);
	splay(selectNode(x+1), root);
	int now = tr[tr[root].son[1]].son[0];
	tr[tr[root].son[1]].son[0] = 0;
	tr[now].fa = tr[now].size = 0;
	tr[now].son[0] = tr[now].son[1] = 0;
	tr[now].val = tr[now].sum = tr[now].mn = 0;
	pushup(tr[root].son[1]), pushup(root);
	return now;
}
inline void insert(int x, LL val, int id){
	// insert val as the x'th node on the tree, using id as its id
	splay(selectNode(x-1), 0);
	splay(selectNode(x), root);
	tr[tr[root].son[1]].son[0] = id;
	tr[id].fa = tr[root].son[1];
	tr[id].son[0] = tr[id].son[1] = 0;
	tr[id].size = 1;
	tr[id].val = tr[id].sum = tr[id].mn = val;
	pushup(tr[root].son[1]), pushup(root);
}

int build(int l, int r, int fa){
	if(l > r)	return 0;
	int id = ++tot;
	tr[id].fa = fa, tr[id].size = 1;
	int mid = (l + r) >> 1;
	tr[id].val = tr[id].sum = tr[id].mn = b[mid];
	tr[id].son[0] = build(l, mid - 1, id);
	tr[id].son[1] = build(mid + 1, r, id);
	pushup(id);
	return id;
}
bool first = false;
void print(int x){
	if(tr[x].son[0])	print(tr[x].son[0]);
	if(tr[x].val != -INF && tr[x].val != INF){
		if(!first)	printf("%lld", tr[x].val), first = true;
		else	printf(" %lld", tr[x].val);
	}
	if(tr[x].son[1])	print(tr[x].son[1]);
}

inline void init(){
	tot = root = 0;
	for(int i = 1; i <= n + 2; i++)	tr[i].init();
	first = false;
}

int main(){
	int T; for(scanf("%d", &T); T; T--){
		int q; scanf("%d%d", &n, &q);
		init();
		b[0] = -INF, b[n+1] = INF;
		for(int i = 1; i <= n; i++)	scanf("%lld", &b[i]);
		root = build(0, n + 1, 0);
		while(q--){
			int opt, x; LL y;
			scanf("%d", &opt);
			if(opt == 1){
				scanf("%d%lld", &x, &y); x++;
				if(y > tr[selectNode(x)].val){ puts("0"); continue; }
				int pos = findlast(x, y);
				if(pos == -1){ puts("0"); continue; }
				printf("%lld\n", getSum(pos+1, x) - 1ll*(y-1)*(x-pos));
				LL newVal = tr[selectNode(pos+1)].val - y + 1 + tr[selectNode(pos)].val;
				int id = del(pos);
				insert(pos, newVal, id);
				id = del(pos+1);
				insert(x, y-1, id);
			}
			else{
				scanf("%d", &x); x++;
				printf("%lld\n", tr[selectNode(x)].val);
			}
		}
		print(root);
		puts("");
	}
	return 0;
}