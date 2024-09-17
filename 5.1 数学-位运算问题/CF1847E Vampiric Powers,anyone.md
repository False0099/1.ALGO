[DIO](https://jojowiki.com/Dio_Brando) knows that the Stardust Crusaders have determined his location and will be coming to fight him. To foil their plans he decides to send out some [Stand](https://jojo.fandom.com/wiki/Stand) users to fight them. Initially, he summoned $n$ Stand users with him, the $i$ \-th one having a strength of $a_i$. Using his vampiric powers, he can do the following as many times as he wishes:

-   Let the **current** number of Stand users be $m$.
-   DIO chooses an index $i$ ($1 \le i \le m$).
-   Then he summons a new Stand user, with index $m+1$ and strength given by:
    $$
    a_{m+1} = a_i \oplus a_{i+1} \oplus \ldots \oplus a_m,
    $$
    
    where the operator $\oplus$ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).
    
-   Now, the number of Stand users becomes $m+1$.

Unfortunately for DIO, by using Hermit Purple's divination powers, the Crusaders know that he is plotting this, and they also know the strengths of the original Stand users. Help the Crusaders find the maximum possible strength of a Stand user among all possible ways that DIO can summon.

## 题解
我们这一题首先要知道，所谓的替身最大值，其实就是求我们的**连续区间异或最大值**，这个显然可以用我们的 01 字典树来解决。我们先把我们的整个区间求一个前缀和，然后对我们的这一个前缀和构造一个 0-1 TRIE，然后我们能够求出来的**区间最大值**就是我们当中任意**两点的异或的最大值。**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
 
int n, m;
int s[N], son[N][2], cnt[N], idx;
 
void insert(int x, int v) 
{
    int p = 0;
    for (int i = 30; i >= 0; i --)
    {
        int u = x >> i & 1;
        if (!son[p][u]) son[p][u] = ++ idx;
        p = son[p][u];
        cnt[p] += v;
    }
}
 
int query(int x)
{
    int p = 0, res = 0;
    for (int i = 30; i >= 0; i --)
    {
        int u = x >> i & 1;
        if (cnt[son[p][!u]]) 
        {
            res += 1 << i;
            p = son[p][!u];
        }
        else p = son[p][u];
    }
    return res;
}
 
int main()
{
	int t;
	scanf("%d",&t);
	while(t--){
		idx=0,s[0]=0;
    	scanf("%d", &n);
    	m=n;
    	for(int i=0;i<=n+500;i++)
    		son[i][1]=0,son[i][0]=0,cnt[i]=0;
    	for (int i = 1; i <= n; i ++) 
    	{
    	    int x;
    	    scanf("%d", &x);
    	    s[i] = s[i - 1] ^ x;
    	}
    	int res = 0;
    	insert(s[0], 1);
    	for (int i = 1; i <= n; i ++)
    	{
    	    if (i > m) insert(s[i - m - 1], -1);
    	    insert(s[i], 1);
    	    res = max(res, query(s[i]));
    	}
    	printf("%d\n", res);
	}
}
```