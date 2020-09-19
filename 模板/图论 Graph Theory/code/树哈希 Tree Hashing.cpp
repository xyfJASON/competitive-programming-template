#include<bits/stdc++.h>

using namespace std;

typedef unsigned long long ULL;

const int N = 105;

int n, m;

bool notP[N];
int pList[N], pID;
void Euler(int n){
	notP[0] = notP[1] = 1;
	for(int i = 1; i <= n; i++){
		if(!notP[i])	pList[++pID] = i;
		for(int j = 1; j <= pID; j++){
			if(1ll * i * pList[j] > n)	break;
			notP[i * pList[j]] = 1;
			if(i % pList[j] == 0)	break;
		}
	}
}

vector<int> edge[N];

int size[N], mxson[N];
void getCentroid(int x, int f, int &rt){ // rt is the id of centroid
	mxson[x] = 0, size[x] = 1;
	for(auto &to : edge[x]){
		if(to == f)	continue;
		getCentroid(to, x, rt);
		size[x] += size[to];
		mxson[x] = max(mxson[x], size[to]);
	}
	mxson[x] = max(mxson[x], n - size[x]);
	if(rt == 0 || mxson[rt] > mxson[x])	rt = x;
}

ULL Hash[N];
int sz[N]; // pay attention that sz[] is different from size[]
void getHash(int x, int f){ // tree rooted at x
	sz[x] = 1; Hash[x] = 1;
	for(auto &to : edge[x]){
		if(to == f)	continue;
		getHash(to, x);
		sz[x] += sz[to];
		Hash[x] += pList[sz[to]] * Hash[to];
	}
}

int v[2][N];

int main(){
	Euler(100);
	scanf("%d", &m);
	for(int j = 1; j <= m; j++){
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)	edge[i].clear();
		for(int i = 1; i <= n; i++){
			int f; scanf("%d", &f);
			if(f)	edge[f].push_back(i), edge[i].push_back(f);
		}
		int rt1 = 0;
		getCentroid(1, 0, rt1);
		getHash(rt1, 0);
		v[0][j] = Hash[rt1];
		bool b = false;
		for(auto &rt2 : edge[rt1]){
			if(rt2 != rt1 && mxson[rt1] == mxson[rt2]){
				getHash(rt2, 0);
				v[1][j] = Hash[rt2];
				b = true;
				break;
			}
		}
		if(!b)	v[1][j] = v[0][j];
		if(v[0][j] > v[1][j])	swap(v[0][j], v[1][j]);
	}
	for(int i = 1; i <= m; i++){
		for(int j = 1; j <= i; j++){
			if(v[0][i] == v[0][j] && v[1][i] == v[1][j]){
				printf("%d\n", j);
				break;
			}
		}
	}
	return 0;
}