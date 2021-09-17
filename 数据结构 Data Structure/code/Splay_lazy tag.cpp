#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 100005;
const int INF = 1e9;

int n, m, ql, qr;

struct Splay{
	int fa, son[2], val, size;
	bool rev;
}tr[N];
#define which(x,y) (tr[y].son[1] == x)
int id = 0, root = 0;
inline void pushup(int x){
	if(x){
		tr[x].size = 1;
		if(tr[x].son[0])	tr[x].size += tr[tr[x].son[0]].size;
		if(tr[x].son[1])	tr[x].size += tr[tr[x].son[1]].size;
	}
}
inline void pushdown(int x){
	if(tr[x].rev){
		if(tr[x].son[0]){
			tr[tr[x].son[0]].rev ^= 1;
			swap(tr[tr[x].son[0]].son[0], tr[tr[x].son[0]].son[1]);
		}
		if(tr[x].son[1]){
			tr[tr[x].son[1]].rev ^= 1;
			swap(tr[tr[x].son[1]].son[0], tr[tr[x].son[1]].son[1]);
		}
		tr[x].rev ^= 1;
	}
}
inline void rotate(int x, int dir){ // dir == 0: left; dir == 1: right
	int y = tr[x].fa, z = tr[y].fa, B = tr[x].son[dir];
	tr[x].fa = z; tr[z].son[which(y,z)] = x;
	tr[y].fa = x; tr[x].son[dir] = y;
	tr[B].fa = y; tr[y].son[dir^1] = B;
	pushup(y); pushup(x);
}
inline void splay(int x, int goal){
	if(x == goal)	return;
	while(tr[x].fa != goal){
		int y = tr[x].fa, z = tr[y].fa, dir1 = which(x,y)^1, dir2 = which(y,z)^1;
		pushdown(z); pushdown(y); pushdown(x);
		if(z == goal)	rotate(x, dir1);
		else{
			if(dir1 == dir2)	rotate(y, dir2);
			else	rotate(x, dir1);
			rotate(x, dir2);
		}
	}
	if(goal == 0)	root = x;
}
inline int getPreNode(int val){ // return nodeID
	int now = root, res = 0, preval = -INF;
	while(now){
		pushdown(now);
		if(tr[now].val < val){
			preval = max(preval, tr[now].val);
			res = now;
			now = tr[now].son[1];
		}
		else	now = tr[now].son[0];
	}
	return res;
}
inline int getSucNode(int val){ // return nodeID
	int now = root, res = 0, sucval = INF;
	while(now){
		pushdown(now);
		if(tr[now].val > val){
			sucval = min(sucval, tr[now].val);
			res = now;
			now = tr[now].son[0];
		}
		else	now = tr[now].son[1];
	}
	return res;
}
inline int newNode(int val, int fa){
	id++;
	tr[id].val = val;
	tr[id].fa = fa;
	tr[id].son[0] = tr[id].son[1] = 0;
	tr[id].size = 1;
	tr[id].rev = 0;
	return id;
}
inline int selectNode(int x){ // return the xth node's id
	int now = root;
	pushdown(now);
	while(tr[tr[now].son[0]].size + 1 != x){
		if(tr[tr[now].son[0]].size + 1 > x)
			now = tr[now].son[0];
		else{
			x -= tr[tr[now].son[0]].size + 1;
			now = tr[now].son[1];
		}
		pushdown(now);
	}
	return now;
}
inline void reverse(int l, int r){
	splay(selectNode(l-1), 0);
	splay(selectNode(r+1), root);
	int &x = tr[tr[root].son[1]].son[0];
	tr[x].rev ^= 1;
	swap(tr[x].son[0], tr[x].son[1]);
}
void print(int x){
	pushdown(x);
	if(tr[x].son[0])	print(tr[x].son[0]);
	if(tr[x].val != INF && tr[x].val != -INF)
		printf("%d ", tr[x].val);
	if(tr[x].son[1])	print(tr[x].son[1]);
}

int main(){
	scanf("%d%d", &n, &m);
	root = newNode(-INF, 0);
	int now = root;
	for(int i = 1; i <= n; i++){
		tr[now].son[1] = newNode(i, now);
		now = tr[now].son[1];
	}
	tr[now].son[1] = newNode(INF, now);
	while(m--){
		scanf("%d%d", &ql, &qr);
		reverse(ql+1, qr+1);
	}
	print(root);
	return 0;
}
