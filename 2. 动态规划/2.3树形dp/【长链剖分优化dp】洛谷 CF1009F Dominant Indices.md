# Dominant Indices

## 题面翻译

给定一棵以 $1$ 为根，$n$ 个节点的树。设 $d(u,x)$ 为 $u$ 子树中到 $u$ 距离为 $x$ 的节点数。  

对于每个点，求一个最小的 $k$，使得 $d(u,k)$ 最大。

## 题目描述

You are given a rooted undirected tree consisting of $ n $ vertices. Vertex $ 1 $ is the root.

Let's denote a depth array of vertex $ x $ as an infinite sequence $ [d_{x, 0}, d_{x, 1}, d_{x, 2}, \dots] $ , where $ d_{x, i} $ is the number of vertices $ y $ such that both conditions hold:

- $ x $ is an ancestor of $ y $ ;
- The simple path from $ x $ to $ y $ traverses exactly $ i $ edges.

The dominant index of a depth array of vertex $ x $ (or, shortly, the dominant index of vertex $ x $ ) is an index $ j $ such that:

- For every $ k < j $ , $ d_{x, k} < d_{x, j} $ ;
- For every $ k > j $ , $ d_{x, k} \le d_{x, j} $ .

For every vertex in the tree calculate its dominant index.

## 输入格式

The first line contains one integer $n$ ( $ 1 \le n \le 10^6 $ ) — the number of vertices in a tree.

Then $ n - 1 $ lines follow, each containing two integers $ x $ and $ y $ ( $ 1 \le x, y \le n $ , $ x \ne y $ ). This line denotes an edge of the tree.

It is guaranteed that these edges form a tree.

## 输出格式

Output $ n $ numbers. $ i $ -th number should be equal to the dominant index of vertex $ i $ .

## 样例 #1

### 样例输入 #1

```
4
1 2
2 3
3 4
```

### 样例输出 #1

```
0
0
0
0
```

## 样例 #2

### 样例输入 #2

```
4
1 2
1 3
1 4
```

### 样例输出 #2

```
1
0
0
0
```

## 样例 #3

### 样例输入 #3

```
4
1 2
2 3
2 4
```

### 样例输出 #3

```
2
1
0
0
```


## 题解
我们如果按照正常的思路，设置 $dp[i][j]$ 表示 i 节点到深度为 j 的地方的总共的方案数。那么我们的转移就可以用如下方式来计算
$$
dp[i][j]=\sum dp[v][j-1]
$$
我们的 $ans$ 就等于我们的 $max(dp[i][j])$。

我们在优化时，首先进行一遍长链剖分，之后我们在进行 dp 时，让父节点直接继承我们的长链的结果，然后再对我们的轻链进行暴力的合并, 合并的公式按照我们的转移公式来进行。

我们在实现时抛弃传统的 DP，预先为每个节点**申请每个节点对应 size 大小的空间**，以节省我们的空间而是在 dp 的过程中，动态的为节点申请内存，所以我们要采用指针的写法。然后，我们对每一个长链的顶端节点申请内存，而对于一条长链上的数据，我们可以共用一片空间。



```cpp
#include <bits/stdc++.h>
#define debug printf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
#define in inline
#define re register
using namespace std;
typedef long long ll;
typedef double db;
in int read()
{
    int ans=0,f=1;char c=getchar();
    for (;!isdigit(c);c=getchar()) if (c=='-') f=-1;
    for (;isdigit(c);c=getchar()) ans=(ans<<3)+(ans<<1)+(c^48);
    return ans*f;
}
in int cmin(int &a,int b) {return a=min(a,b);}
in int cmax(int &a,int b) {return a=max(a,b);}
int n;
int buf[1000005];
int *f[1000005],*g[1000005],*now=buf;
int nex[2000005],head[1000005],tail[2000005],tot;
int ans[1000005];
void addedge(int u,int v)
{
    nex[++tot]=head[u];
    head[u]=tot;
    tail[tot]=v;
}
int dep[1000005],son[1000005];
void dfs1(int u,int fa) // 长链剖分
{
    for (int e=head[u];e;e=nex[e])
    {
        int v=tail[e];
        if (v==fa) continue;
        dfs1(v,u);
        if (dep[v]>dep[son[u]]) son[u]=v;
    }
    dep[u]=dep[son[u]]+1;
}
void dfs2(int u,int fa) //做dp
{
    f[u][0]=1;
    if (son[u])
    {
        f[son[u]]=f[u]+1; // 共享内存
        dfs2(son[u],u);
        ans[u]=ans[son[u]]+1; //从长孩子节点继承答案
    }
    for (int e=head[u];e;e=nex[e])
    {
        int v=tail[e];
        if (v==son[u] || v==fa) continue;
        f[v]=now;now+=dep[v]; // 分配内存
        dfs2(v,u);
        for (int i=1;i<=dep[v];i++)
        {
            f[u][i]+=f[v][i-1]; //暴力合并
            if (f[u][i]>f[u][ans[u]] || (f[u][i]==f[u][ans[u]] && i<ans[u])) ans[u]=i; //更新答案
        }
    }
    if (f[u][ans[u]]==1) ans[u]=0;
}
int main()
{
    n=read();
    for (int i=1;i<n;i++)
    {
        int u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0); // 长链剖分
    f[1]=now;now+=dep[1]; // 为根节点的答案分配内存
    dfs2(1,0);
    for (int i=1;i<=n;i++) cout<<ans[i]<<endl;
    return 0;
}
```
