struct Trie{
	int ch[26], cntEnd; // cntEnd can be changed according to different problem
}tr[NODEN];
#define root 0
int id;
void insertTrie(char s[]){
	int len = (int)strlen(s);
	int now = root;
	for(int i = 0; i < len; i++){
		if(!tr[now].ch[s[i]-'a'])
			tr[now].ch[s[i]-'a'] = ++id;
		now = tr[now].ch[s[i]-'a'];
	}
	tr[now].cntEnd++;
}

//-------------------------------------------------------//
struct Trie{
	bool isEnd;
	Trie *ch[26];
	Trie(){
		isEnd = false;
		for(int i = 0; i < 26; i++)
			ch[i] = nullptr;
	}
};
Trie *rt;
void insertTrie(string s){
	int len = s.size();
	Trie *now = rt;
	for(int i = 0; i < len; i++){
		if(now -> ch[s[i]-'a'] == nullptr)
			now -> ch[s[i]-'a'] = new Trie;
		now = now -> ch[s[i]-'a'];
	}
	now -> isEnd = true;
}