inline int search(int val){
	int pos = 0, sum = 0;
	for(int i = 20; i >= 0; i--)
		if(pos + (1<<i) <= n && sum + c[pos+(1<<i)] < val)
			pos += (1<<i), sum += c[pos];
	return pos + 1;
}