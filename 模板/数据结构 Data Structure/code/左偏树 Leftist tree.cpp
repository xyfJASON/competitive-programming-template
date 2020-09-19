#include<algorithm>
#include<iostream>
#include<cstdio>

using namespace std;

const int N = 100005;

int n, m;

struct LeftistTree{
	int l, r, fa, key, dis;
	LeftistTree(){ dis = -1; }
}tr[N];
int findfa(int x){ return x == tr[x].fa ? x : tr[x].fa = findfa(tr[x].fa); }
int Merge(int x, int y){
	// merge two heaps whose roots are x and y
	// if x,y are not roots, apply x = findfa(x), y = findfa(y) beforehand
	if(!x || !y)	return x + y;
	if(x == y)	return x;
	if(tr[x].key > tr[y].key || (tr[x].key == tr[y].key && x > y))	swap(x, y);
	tr[x].r = Merge(tr[x].r, y);
	if(tr[tr[x].l].dis < tr[tr[x].r].dis)	swap(tr[x].l, tr[x].r);
	tr[tr[x].l].fa = tr[tr[x].r].fa = tr[x].fa = x;
	tr[x].dis = tr[tr[x].r].dis + 1;
	return x;
}
int Pop(int x){
	// pop the first element in the heap rooted at x
	// if x is not root, apply x = findfa(x) beforehand
	tr[tr[x].l].fa = tr[x].l, tr[tr[x].r].fa = tr[x].r;
	tr[x].dis = -1;
	tr[x].fa = Merge(tr[x].l, tr[x].r);
	tr[x].l = tr[x].r = 0;
	return tr[x].fa;
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++){
		tr[i].l = tr[i].r = 0;
		tr[i].fa = i;
		scanf("%d", &tr[i].key);
		tr[i].dis = 0;
	}
	while(m--){
		int opt, x, y;
		scanf("%d", &opt);
		if(opt == 1){
			scanf("%d%d", &x, &y);
			if(tr[x].dis == -1 || tr[y].dis == -1)	continue;
			x = findfa(x), y = findfa(y);
			if(x != y)	tr[x].fa = tr[y].fa = Merge(x, y);
		}
		else{
			scanf("%d", &x);
			if(tr[x].dis == -1){ puts("-1"); continue; }
			x = findfa(x);
			printf("%d\n", tr[x].key);
			Pop(x);
		}
	}
	return 0;
}