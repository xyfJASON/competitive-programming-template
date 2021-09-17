#include<cstdio>
#include<algorithm>

using namespace std;

const int INF = 1e9;
const int N = 100005;

int n, opt, qx;

struct Treap{
	int son[2], size, val, hp;
}tr[N];

int cnt, root;
inline int newNode(int val){
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
	if(a == 0)	return b;
	if(b == 0)	return a;
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
void split(int id, int k, int &x, int &y){ // split treap into 2 parts according to values: <= k and > k, and store them in x and y
	if(!id){
		x = 0; y = 0;
		return;
	}
	pushdown(id);
	if(k < tr[id].val){
		y = id;
		split(tr[id].son[0], k, x, tr[id].son[0]);
	}
	else{
		x = id;
		split(tr[id].son[1], k, tr[id].son[1], y);
	}
	pushup(id);
}
inline void insert(int val){ // insert val into treap
	int l = 0, r = 0;
	split(root, val, l, r);
	int t = newNode(val);
	root = merge(merge(l, t), r);
}
inline void del(int val){ // delete one val from treap
	int l = 0, t = 0, r = 0;
	split(root, val-1, l, t);
	split(t, val, t, r);
	t = merge(tr[t].son[0], tr[t].son[1]);
	root = merge(merge(l, t), r);
}
inline int getRank(int val){ // get the rank of val x
	int l = 0, r = 0;
	split(root, val-1, l, r);
	int res = tr[l].size + 1;
	merge(l, r);
	return res;
}
inline int findRank(int x){ // find the val whose rank is x
	int now = root;
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
inline int getPre(int val){ // find the predecessor of val x (the greatest value less than x)
	int now = root, res = -INF;
	while(now){
		if(tr[now].val < val){
			res = max(res, tr[now].val);
			now = tr[now].son[1];
		}
		else	now = tr[now].son[0];
	}
	return res;
}
inline int getSuc(int val){ // find the successor of val x (the least value greater than x)
	int now = root, res = INF;
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
	while(n--){
		scanf("%d%d", &opt, &qx);
		switch(opt){
			case 1: insert(qx); break;
			case 2: del(qx); break;
			case 3: printf("%d\n", getRank(qx)); break;
			case 4: printf("%d\n", findRank(qx)); break;
			case 5: printf("%d\n", getPre(qx)); break;
			case 6: printf("%d\n", getSuc(qx)); break;
			default: ;
		}
	}
	return 0;
}
