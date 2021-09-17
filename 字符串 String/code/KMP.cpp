#include<cstdio>
#include<cstring>

using namespace std;

const int N = 1000005;

char s[N], t[N];
int fail[N];

void getFail(char t[], int lent){
    int i = 1, j = 0;
    fail[1] = 0;
    while(i <= lent){
        if(!j || t[i] == t[j])  fail[++i] = ++j;
        else    j = fail[j];
    }
}
void KMP(char s[], int lens, char t[], int lent){
    int i = 1, j = 1;
    while(i <= lens){
        if(!j || s[i] == t[j]){
            i++, j++;
            if(j == lent + 1){
                printf("%d\n", i - lent);
                j = fail[j];
            }
        }
        else    j = fail[j];
    }
}

int main(){
    scanf("%s", s+1);
    scanf("%s", t+1);
    int lens = strlen(s+1);
    int lent = strlen(t+1);
    getFail(t, lent);
    KMP(s, lens, t, lent);
    for(int i = 2; i <= lent + 1; i++)
        printf("%d ", fail[i] - 1);
    return 0;
}