#include<bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef long double LD;
typedef pair<int, int> pii;
#define mp(x, y) make_pair(x, y)

inline LD fpow(LD bs, LL idx){
	LD res = 1;
	while(idx){
		if(idx & 1)	res *= bs;
		bs *= bs;
		idx >>= 1;
	}
	return res;
}

const LD INF = 1e18+1;
const int N = 100005;

int n;
string ch[N];
LL s[N], L, P;

LD dp[N];
int decision[N];
deque<pair<int, pii>> deq;
inline LD calc(int l, int r){
	// calculate fr decided on l
	if(l >= r)	return INF;
	return dp[l] + fpow(abs(s[r] - s[l] - 1 - L), P);
}
void DP(){
	while(!deq.empty())	deq.pop_back();
	for(int i = 1; i <= n; i++)	dp[i] = INF, decision[i] = 0;
	deq.push_back(mp(0, mp(0, n)));

	for(int i = 1; i <= n; i++){
		while(!deq.empty() && deq.front().second.second < i)	deq.pop_front();
		dp[i] = calc(deq.front().first, i);
		decision[i] = deq.front().first;
		while(!deq.empty() && 
			calc(i, deq.back().second.first) < calc(deq.back().first, deq.back().second.first))
			deq.pop_back();
		int l = deq.back().second.first + 1, r = n + 1;
		while(l < r){
			int mid = (l + r) >> 1;
			if(calc(i, mid) < calc(deq.back().first, mid))	r = mid;
			else	l = mid + 1;
		}
		if(l > n)	continue;
		deq.back().second.second = l - 1;
		deq.push_back(mp(i, mp(l, n)));
	}
}

int main(){
	int T; for(scanf("%d", &T); T; T--){
		scanf("%d%lld%lld", &n, &L, &P);
		for(int i = 1; i <= n; i++){
			cin >> ch[i];
			s[i] = s[i-1] + ch[i].size() + 1;
		}
		DP();
		if(dp[n] > 1e18)	puts("Too hard to arrange");
		else{
			vector<string> ans;
			printf("%.0Lf\n", dp[n]);
			int now = n;
			while(now){
				string res;
				for(int i = decision[now] + 1; i <= now; i++)
					res += ch[i] + " \n"[i == now];
				ans.emplace_back(res);
				now = decision[now];
			}
			reverse(ans.begin(), ans.end());
			for(auto &s : ans)	cout << s;
		}
		puts("--------------------");
	}
	return 0;
}