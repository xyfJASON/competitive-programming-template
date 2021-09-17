#include<cstdio>

using namespace std;

const int N = 10000005;

int n, m, a;

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

int main(){
	scanf("%d%d", &n, &m);
	Euler(n);
	while(m--){
		scanf("%d", &a);
		printf(notP[a] ? "No\n" : "Yes\n");
	}
	return 0;
}
