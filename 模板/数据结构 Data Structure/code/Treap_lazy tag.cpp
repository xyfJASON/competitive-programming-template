#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 100005;

int n, m, qv, ql, qr, lastans;

struct Treap{
	int son[2], size, val, hp;
	bool rev;
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
	if(tr[id].rev){
		if(tr[id].son[0]){
			tr[tr[id].son[0]].rev ^= 1;
			swap(tr[tr[id].son[0]].son[0], tr[tr[id].son[0]].son[1]);
		}
		if(tr[id].son[1]){
			tr[tr[id].son[1]].rev ^= 1;
			swap(tr[tr[id].son[1]].son[0], tr[tr[id].son[1]].son[1]);
		}
		tr[id].rev ^= 1;
	}
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
void splitSize(int id, int k, int &x, int &y){ // split treap into 2 parts according to ranking: <= k and > k, and store them in x and y
	if(!id){
		x = 0; y = 0;
		return;
	}
	pushdown(id);
	if(k <= tr[tr[id].son[0]].size){
		y = id;
		splitSize(tr[id].son[0], k, x, tr[id].son[0]);
	}
	else{
		x = id;
		splitSize(tr[id].son[1], k - tr[tr[id].son[0]].size - 1, tr[id].son[1], y);
	}
	pushup(id);
}
inline void insert(int val){ // insert val into treap
	int l = 0, r = 0;
	splitSize(root, val, l, r);
	int t = newNode(val);
	root = merge(merge(l, t), r);
}
inline void reverse(int l, int r){
	int L = 0, T = 0, R = 0;
	splitSize(root, l - 1, L, T);
	splitSize(T, r - l + 1, T, R);
	tr[T].rev ^= 1;
	swap(tr[T].son[0], tr[T].son[1]);
	root = merge(merge(L, T), R);
}
void print(int x){
	pushdown(x);
	if(tr[x].son[0])	print(tr[x].son[0]);
	printf("%d ", tr[x].val);
	if(tr[x].son[1])	print(tr[x].son[1]);
}

int main(){
	srand(20010130);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		insert(i);
	while(m--){
		scanf("%d%d", &ql, &qr);
		reverse(ql, qr);
	}
	print(root);
	return 0;
}
