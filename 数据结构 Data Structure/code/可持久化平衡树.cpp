#include<cstdio>
#include<algorithm>

using namespace std;

const int INF = 2147483647;
const int N = 500005;

int n, opt, qx, qv;

struct Treap{
	int son[2], size, val, hp;
}tr[N*50];

int cnt, root[N];
inline int newNode(int val = 0){
	cnt++;
	tr[cnt].son[0] = tr[cnt].son[1] = 0;
	tr[cnt].size = 1;
	tr[cnt].val = val;
	tr[cnt].hp = rand();
	return cnt;
}
inline void pushup(int id){
	if(!id)	return;
	tr[id].size = 1;
	if(tr[id].son[0])	tr[id].size += tr[tr[id].son[0]].size;
	if(tr[id].son[1])	tr[id].size += tr[tr[id].son[1]].size;
}
inline void pushdown(int id){
	return;
}
int merge(int a, int b){
	if(!a ||!b) return a + b;
	if(tr[a].hp <= tr[b].hp){
		pushdown(a);
		int cur = newNode();
		tr[cur] = tr[a];
		tr[cur].son[1] = merge(tr[cur].son[1], b);
		pushup(cur);
		return cur;
	}
	else{
		pushdown(b);
		int cur = newNode();
		tr[cur] = tr[b];
		tr[cur].son[0] = merge(a, tr[cur].son[0]);
		pushup(cur);
		return cur;
	}
}
void split(int id, int k, int &x, int &y){ // split treap into 2 parts according to values: <= k and > k, and store them in x and y
	if(!id){
		x = 0; y = 0;
		return;
	}
	pushdown(id);
	if(k < tr[id].val){
		tr[y = newNode()] = tr[id];
		split(tr[y].son[0], k, x, tr[y].son[0]);
		pushup(y);
	}
	else{
		tr[x = newNode()] = tr[id];
		split(tr[x].son[1], k, tr[x].son[1], y);
		pushup(x);
	}
}
inline void insert(int &cur, int val){ // insert val into treap
	int l = 0, r = 0;
	split(cur, val, l, r);
	int t = newNode(val);
	cur = merge(merge(l, t), r);
}
inline void del(int &cur, int val){ // delete one val from treap
	int l = 0, t = 0, r = 0;
	split(cur, val-1, l, t);
	split(t, val, t, r);
	t = merge(tr[t].son[0], tr[t].son[1]);
	cur = merge(merge(l, t), r);
}
inline int getRank(int cur, int val){ // get the rank of val x
	int l = 0, r = 0;
	split(cur, val-1, l, r);
	int res = tr[l].size + 1;
	merge(l, r);
	return res;
}
inline int findRank(int cur, int x){ // find the val whose rank is x
	int now = cur;
	while(now){
		if(tr[tr[now].son[0]].size + 1 == x)	return tr[now].val;
		else if(tr[tr[now].son[0]].size >= x)	now = tr[now].son[0];
		else{
			x -= tr[tr[now].son[0]].size + 1;
			now = tr[now].son[1];
		}
	}
	return -INF;
}
inline int getPre(int cur, int val){ // find the predecessor of val x (the greatest value less than x)
	int now = cur, res = -INF;
	while(now){
		if(tr[now].val < val){
			res = max(res, tr[now].val);
			now = tr[now].son[1];
		}
		else	now = tr[now].son[0];
	}
	return res;
}
inline int getSuc(int cur, int val){ // find the successor of val x (the least value greater than x)
	int now = cur, res = INF;
	while(now){
		if(tr[now].val > val){
			res = min(res, tr[now].val);
			now = tr[now].son[0];
		}
		else	now = tr[now].son[1];
	}
	return res;
}

int main(){
	srand(20010130);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d%d%d", &qv, &opt, &qx);
		root[i] = root[qv];
		switch(opt){
			case 1: insert(root[i], qx); break;
			case 2: del(root[i], qx); break;
			case 3: printf("%d\n", getRank(root[i], qx)); break;
			case 4: printf("%d\n", findRank(root[i], qx)); break;
			case 5: printf("%d\n", getPre(root[i], qx)); break;
			case 6: printf("%d\n", getSuc(root[i], qx)); break;
			default: ;
		}
	}
	return 0;
}
