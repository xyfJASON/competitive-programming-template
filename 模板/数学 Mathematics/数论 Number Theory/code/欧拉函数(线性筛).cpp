#include<cstdio>

using namespace std;

const int N = 100005;

int n;

int phi[N], pList[N], pID;
bool notP[N];
void Euler(int n){
	notP[0] = notP[1] = 1;
	phi[1] = 1;
	for(int i = 1; i <= n; i++){
		if(notP[i] == 0){
			pList[++pID] = i;
			phi[i] = i - 1;
		}
		for(int j = 1; j <= pID; j++){
			if(1ll * i * pList[j] > n)	break;
			notP[i * pList[j]] = 1;
			if(i % pList[j] == 0){
				phi[i * pList[j]] = phi[i] * pList[j];
				break;
			}
			else	phi[i * pList[j]] = phi[i] * (pList[j] - 1);
		}
	}
}

int main(){
	scanf("%d", &n);
	Euler(n);
	for(int i = 1; i <= n; i++)
		printf("%d ", phi[i]);
	return 0;
}
