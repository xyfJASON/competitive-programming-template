void toposort(){
	queue<int> q;
	for(int i = 1; i <= scc; i++)
		if(!ind[i])
			q.push(i);
	while(!q.empty()){
		int cur = q.front();
		q.pop();
		for(int i = head[cur]; i; i = edge[i].nxt){
            // do something...
			ind[edge[i].to]--;
			if(!ind[edge[i].to])
				q.push(edge[i].to);
		}
	}
}