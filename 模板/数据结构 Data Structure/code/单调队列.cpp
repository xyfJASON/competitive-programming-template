#include<bits/stdc++.h>

using namespace std;

#define mp(x, y) make_pair(x, y)

const int N = 1000005;

int n, k, a[N];

int main(){
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)	scanf("%d", &a[i]);
	deque< pair<int, int> > dq;
	for(int i = 1; i <= n; i++){
		while(!dq.empty() && dq.front().second <= i - k)	dq.pop_front();
		while(!dq.empty() && dq.back().first >= a[i])	dq.pop_back();
		dq.push_back(mp(a[i], i));
		if(i >= k)	printf("%d ", dq.front().first);
	}
	puts("");
	while(!dq.empty())	dq.pop_back();
	for(int i = 1; i <= n; i++){
		while(!dq.empty() && dq.front().second <= i - k)	dq.pop_front();
		while(!dq.empty() && dq.back().first <= a[i])	dq.pop_back();
		dq.push_back(mp(a[i], i));
		if(i >= k)	printf("%d ", dq.front().first);
	}
	puts("");
	return 0;
}