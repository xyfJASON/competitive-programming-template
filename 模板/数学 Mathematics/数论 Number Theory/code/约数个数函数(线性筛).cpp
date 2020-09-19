#include<cstdio>

using namespace std;

const int N = 100005;

int n;

int d[N], num[N], pList[N], pID;
bool notP[N];
void Euler(int n){
	notP[0] = notP[1] = 1;
	d[1] = 1;
	for(int i = 1; i <= n; i++){
		if(notP[i] == 0){
			pList[++pID] = i;
			d[i] = 2, num[i] = 1;
		}
		for(int j = 1; j <= pID; j++){
			if(1ll * i * pList[j] > n)	break;
			notP[i * pList[j]] = 1;
			if(i % pList[j] == 0){
				d[i * pList[j]] = d[i] / (num[i] + 1) * (num[i] + 2);
				num[i * pList[j]] = num[i] + 1;
				break;
			}
			else	d[i * pList[j]] = d[i] * 2, num[i * pList[j]] = 1;
		}
	}
}

int main(){
	scanf("%d", &n);
	Euler(n);
	for(int i = 1; i <= n; i++)
		printf("%d ", d[i]);
	return 0;
}
