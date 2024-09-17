## 题意
![[Pasted image 20240221000517.png]]

## 题解
本题类似于我们的求最小字典序的题目，我们在这里，通过 TRIE 进行字典序比较时，我们先去找两个字符串之间的最长公共前缀，然后我们的比较次数，就是我们的最长公共前缀+1. 于是我们就可以动态插入 TRIE 函数，动态更新我们的比较次数。

具体来说，再插入的时候，如果一个点已经出现过，我们就更新我们这个点总共的出现次数，我们具体的就是 $ans+=cnt['s']*height$ 作为我们的答案。
![[Pasted image 20240221001114.png]]

```cpp
#include<bits/stdc++.h>
#define _for(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef long long ll;
const int mod =1e6+7;
double esp=1e-6;
int INF =0x3f3f3f3f;
const int inf = 1<<28;
const int MAXN=5e6+10;
int ch[MAXN][70];
int val[MAXN];
int same[MAXN];
struct Trie
{
    ll ans;
    int sz;
    Trie()
    {
        sz=1;
        memset(ch,0,sizeof(ch));
        memset(val,0,sizeof(val));
        memset(same,0,sizeof(same));
        ans=0;
    }
    int idx(char x)
    {
        if(x>='0'&&x<='9')return x-'0';
        else  if(x>='A'&&x<='Z')return x-'A'+10;
        else if(x>='a'&&x<='z')return x-'a'+36;
    }
    void INSERT(char *s)
    {
        int u=0,n=strlen(s);
        for(int i=0;i<n;i++)
        {
            int v=idx(s[i]);
            if(ch[u][v]==0)
            {
                ans+=val[u]*(2*i+1);
                ch[u][v]=sz++;
            }
            else
            {
                ans+=(val[u]-val[ch[u][v]])*(2*i+1);
            }
            val[u]++;
            u=ch[u][v];
        }//比当前串短的
        ans+=(same[u]*2*(n+1));//和当前串相同的
        ans+=(val[u]-same[u])*(2*n+1);//比当前串长的
        val[u]++;
        same[u]++;
    }

};
char s[2000];
int main()
{
    int Case=0,t;
    while(~scanf("%d",&t))
    {
        if(t==0)break;
        Trie tmp;
        for(int i=0;i<t;i++)
        {
            scanf("%s",s);
            tmp.INSERT(s);
        }
        printf("Case %d: %lld\n",++Case,tmp.ans);
    }
}
```