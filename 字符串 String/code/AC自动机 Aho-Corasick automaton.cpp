#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

const int N = 1000005;

int n, ans;
char s[N];

struct Trie{
    int ch[26], cntEnd;
}tr[N];
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

int fail[N];
void getFail(){
    queue<int> q;
    for(int i = 0; i < 26; i++){
        if(tr[root].ch[i]){
            fail[tr[root].ch[i]] = root;
            q.push(tr[root].ch[i]);
        }
    }
    while(!q.empty()){
        int cur = q.front(); q.pop();
        for(int i = 0; i < 26; i++){
            if(!tr[cur].ch[i])
                tr[cur].ch[i] = tr[fail[cur]].ch[i];
            else{
                fail[tr[cur].ch[i]] = tr[fail[cur]].ch[i];
                q.push(tr[cur].ch[i]);
            }
        }
    }
}

void ACauto(char s[]){
    int len = (int)strlen(s);
    int now = root;
    for(int i = 0; i < len; i++){
        now = tr[now].ch[s[i]-'a'];
        for(int t = now; t && tr[t].cntEnd != -1; t = fail[t]){
            ans += tr[t].cntEnd;
            tr[t].cntEnd = -1; // in this problem, if a sting appears many times, we only count it once
        }
    }
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%s", s);
        insertTrie(s);
    }
    getFail();
    scanf("%s", s);
    ACauto(s);
    printf("%d\n", ans);
    return 0;
}
