#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<vector>

using namespace std;

const int N = 100005;

void mergesort(int a[], int l, int r){
	if(l >= r)	return;
	int mid = (l + r) >> 1;
	mergesort(a, l, mid);
	mergesort(a, mid+1, r);
	vector<int> t;
	int lpt = l, rpt = mid+1;
	while(lpt <= mid && rpt <= r){
		if(a[lpt] < a[rpt])
			t.emplace_back(a[lpt++]);
		else
			t.emplace_back(a[rpt++]);
	}
	while(lpt <= mid)
		t.emplace_back(a[lpt++]);
	while(rpt <= r)
		t.emplace_back(a[rpt++]);
	for(int i = l; i <= r; i++)
		a[i] = t[i - l];
}

int n, a[N];

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	mergesort(a, 1, n);
	for(int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	return 0;
}