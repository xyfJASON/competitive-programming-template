#include<cstdio>

using namespace std;

const int N = 100005;

int n;

int sigma[N], g[N], pList[N], pID;
bool notP[N];
void Euler(int n){
	notP[0] = notP[1] = 1;
	sigma[1] = 1, g[1] = 1;
	for(int i = 1; i <= n; i++){
		if(notP[i] == 0){
			pList[++pID] = i;
			sigma[i] = 1 + i, g[i] = 1 + i;
		}
		for(int j = 1; j <= pID; j++){
			if(1ll * i * pList[j] > n)	break;
			notP[i * pList[j]] = 1;
			if(i % pList[j] == 0){
				sigma[i * pList[j]] = sigma[i] / g[i] * (g[i] * pList[j] + 1);
				g[i * pList[j]] = g[i] * pList[j] + 1;
				break;
			}
			else	sigma[i * pList[j]] = sigma[i] * (1 + pList[j]), g[i * pList[j]] = 1 + pList[j];
		}
	}
}

int main(){
	scanf("%d", &n);
	Euler(n);
	for(int i = 1; i <= n; i++)
		printf("%d: %d\n", i, sigma[i]);
	return 0;
}
