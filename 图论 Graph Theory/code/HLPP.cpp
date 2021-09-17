#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 1205;
const int M = 120005;
const LL INF = 1e14;

namespace FLOW{
	
	int n, S, T;
	struct Edge{
		int nxt, to;
		LL flow;
	}edge[M<<1];
	int head[N], edgeNum = 1;
	void addEdge(int from, int to, LL flow){
		edge[++edgeNum] = (Edge){head[from], to, flow};
		head[from] = edgeNum;
	}

	LL extra[N], h[N], gap[N];
	inline bool bfs(){
		for(int i = 1; i <= n; i++)	h[i] = INF;
		h[T] = 0, gap[0] = 1;
		queue<int> q;
		q.push(T);
		while(!q.empty()){
			int cur = q.front(); q.pop();
			for(int i = head[cur]; i; i = edge[i].nxt){
				if(edge[i^1].flow && h[edge[i].to] == INF){
					h[edge[i].to] = h[cur] + 1;
					gap[h[edge[i].to]]++;
					q.push(edge[i].to);
				}
			}
		}
		return h[S] != INF;
	}
	struct cmp{ bool operator ()(int a, int b){ return h[a] < h[b]; } };
	priority_queue<int, vector<int>, cmp> pq;
	bool inq[N];
	inline void Push(int x){
		for(int i = head[x]; i; i = edge[i].nxt){
			if(h[x] == h[edge[i].to] + 1 && edge[i].flow){
				LL mn = min(edge[i].flow, extra[x]);
				edge[i].flow -= mn, edge[i^1].flow += mn;
				extra[x] -= mn, extra[edge[i].to] += mn;
				if(!inq[edge[i].to] && edge[i].to != T && edge[i].to != S)
					pq.push(edge[i].to), inq[edge[i].to] = true;
				if(!extra[x])	break;
			}
		}
	}
	inline void Relabel(int x){
		h[x] = INF;
		for(int i = head[x]; i; i = edge[i].nxt)
			if(edge[i].flow)
				h[x] = min(h[x], h[edge[i].to] + 1);
	}
	inline LL HLPP(){
		if(!bfs())	return 0;
		h[S] = n;
		for(int i = head[S]; i; i = edge[i].nxt){
			if(edge[i].flow){
				extra[S] -= edge[i].flow, extra[edge[i].to] += edge[i].flow;
				edge[i^1].flow += edge[i].flow, edge[i].flow = 0;
				if(!inq[edge[i].to] && edge[i].to != T && edge[i].to != S)
					pq.push(edge[i].to), inq[edge[i].to] = true;
			}
		}
		while(!pq.empty()){
			int cur = pq.top(); pq.pop();
			inq[cur] = false;
			Push(cur);
			if(extra[cur]){
				if(--gap[h[cur]] == 0)
					for(int i = 1; i <= n; i++)
						if(i != S && i != T && h[i] > h[cur] && h[i] < n + 1)
							h[i] = n + 1;
				Relabel(cur);
				gap[h[cur]]++;
				pq.push(cur), inq[cur] = true;
			}
		}
		return extra[T];
	}
}

int main(){
	int n, m, s, t;
	scanf("%d%d%d%d", &n, &m, &s, &t);
	FLOW::n = n, FLOW::S = s, FLOW::T = t;
	for(int i = 1; i <= m; i++){
		int u, v; LL w;
		scanf("%d%d%lld", &u, &v, &w);
		FLOW::addEdge(u, v, w);
		FLOW::addEdge(v, u, 0);
	}
	printf("%lld\n", FLOW::HLPP());
	return 0;
}