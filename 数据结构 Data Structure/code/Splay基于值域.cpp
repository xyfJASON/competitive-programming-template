#include<bits/stdc++.h>

using namespace std;

const int N = 1100005;
const int INF = 2e9;

int n, q, opt, x, lastans;

struct Splay{
	int fa, son[2], size, cnt, val;
}tr[N];
#define which(x,fa) (tr[fa].son[1] == x)
int tot = 0, root = 0;
queue<int> rec; // recycle
inline void pushup(int x){
	if(x){
		tr[x].size = tr[x].cnt;
		if(tr[x].son[0])	tr[x].size += tr[tr[x].son[0]].size;
		if(tr[x].son[1])	tr[x].size += tr[tr[x].son[1]].size;
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
	if(x == goal)	return;
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
inline int select(int val){
	// return tot of node whose val == val
	int now = root;
	while(now){
		if(tr[now].val == val)	return now;
		else if(tr[now].val > val)	now = tr[now].son[0];
		else if(tr[now].val < val)	now = tr[now].son[1];
	}
	if(!now)	return -1;
	return now;
}
inline int getPre(int val){
	// find the predecessor of val x (the greatest value less than x)
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
inline int getSuc(int val){
	// find the successor of val x (the least value greater than x)
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
inline int getRank(int val){
	// get the rank of val
	// i.e. the number of those < val plus 1
	int now = root, rank = 0, t = 0;
	while(now){
		t = now;
		if(tr[now].val == val){
			rank += tr[tr[now].son[0]].size;
			break;
		}
		else if(tr[now].val < val){
			rank += tr[now].size - tr[tr[now].son[1]].size;
			now = tr[now].son[1];
		}
		else	now = tr[now].son[0];
	}
	splay(t, 0);
	return rank;
}
inline int newNode(int val, int fa){
	int id;
	if(!rec.empty())	id = rec.front(), rec.pop();
	else	id = ++tot;
	tr[id].fa = fa;
	tr[id].son[0] = tr[id].son[1] = 0;
	tr[id].size = tr[id].cnt = 1;
	tr[id].val = val;
	return id;
}
inline void insert(int val){
	// insert val into splay tree
	splay(select(getPre(val)), 0);
	splay(select(getSuc(val)), root);
	int &x = tr[tr[root].son[1]].son[0];
	if(x){ tr[x].cnt++; tr[x].size++; }
	else	x = newNode(val, tr[root].son[1]);
	pushup(tr[root].son[1]);
	pushup(root);
}
inline void del(int val){
	// delete one val from splay tree
	splay(select(getPre(val)), 0);
	splay(select(getSuc(val)), root);
	int &x = tr[tr[root].son[1]].son[0];
	if(!x || !tr[x].cnt)	return ;
	tr[x].cnt--; tr[x].size--;
	if(tr[x].cnt == 0)	rec.push(x), x = 0;
	pushup(tr[root].son[1]);
	pushup(root);
}
inline int findRank(int x){
	// find the val of x'th node
	int now = root;
	while(now){
		if(tr[tr[now].son[0]].size + 1 <= x && x <= tr[now].size - tr[tr[now].son[1]].size)
			break;
		else if(tr[tr[now].son[0]].size + 1 > x)
			now = tr[now].son[0];
		else if(x > tr[now].size - tr[tr[now].son[1]].size){
			x -= tr[now].size - tr[tr[now].son[1]].size;
			now = tr[now].son[1];
		}
	}
	splay(now, 0);
	return tr[root].val;
}

int main(){
	scanf("%d%d", &n, &q);
	root = newNode(-INF, 0);
	tr[root].son[1] = newNode(INF, root);
	pushup(root);
	for(int i = 1; i <= n; i++){
		int x; scanf("%d", &x);
		insert(x);
	}
	int ans = 0;
	while(q--){
		scanf("%d%d", &opt, &x);
		x ^= lastans;
		switch(opt){
			case 1: insert(x); break;
			case 2: del(x); break;
			case 3: ans ^= (lastans = getRank(x)); break;
			case 4:	ans ^= (lastans = findRank(x+1)); break;
			case 5:	ans ^= (lastans = getPre(x)); break;
			case 6:	ans ^= (lastans = getSuc(x)); break;
			default: ;
		}
	}
	printf("%d\n", ans);
	return 0;
}