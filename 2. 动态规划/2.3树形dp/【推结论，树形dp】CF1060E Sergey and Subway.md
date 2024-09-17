# Sergey and Subway

## 题面翻译

给出一颗 $N$ 个节点的树, 现在我们**在原图中**每个不直接连边但是中间只间隔一个点的两个点之间连一条边.

比如**在原图中**$u$ 与 $v$ 连边, $v$ 与 $w$ 连边, 但是 $u$ 与 $w$ 不连边, 这时候我们就需要连一条 $u$ 与 $w$ 的边.

现在我们需要求出新图中每一个点对 $(i,j)\ (1 \leq i \leq j \leq N)$ 的经过的边数和.

Upd on 2020.6.2 翻译修改。

## 题目描述

Sergey Semyonovich is a mayor of a county city N and he used to spend his days and nights in thoughts of further improvements of Nkers' lives. Unfortunately for him, anything and everything has been done already, and there are no more possible improvements he can think of during the day (he now prefers to sleep at night). However, his assistants have found a solution and they now draw an imaginary city on a paper sheet and suggest the mayor can propose its improvements.

Right now he has a map of some imaginary city with $ n $ subway stations. Some stations are directly connected with tunnels in such a way that the whole map is a tree (assistants were short on time and enthusiasm). It means that there exists exactly one simple path between each pair of station. We call a path simple if it uses each tunnel no more than once.

One of Sergey Semyonovich's favorite quality objectives is the sum of all pairwise distances between every pair of stations. The distance between two stations is the minimum possible number of tunnels on a path between them.

Sergey Semyonovich decided to add new tunnels to the subway map. In particular, he connected any two stations $ u $ and $ v $ that were not connected with a direct tunnel but share a common neighbor, i.e. there exists such a station $ w $ that the original map has a tunnel between $ u $ and $ w $ and a tunnel between $ w $ and $ v $ . You are given a task to compute the sum of pairwise distances between all pairs of stations in the new map.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 2 \leq n \leq 200\, 000 $ ) — the number of subway stations in the imaginary city drawn by mayor's assistants. Each of the following $ n - 1 $ lines contains two integers $ u_i $ and $ v_i $ ( $ 1 \leq u_i, v_i \leq n $ , $ u_i \ne v_i $ ), meaning the station with these indices are connected with a direct tunnel.

It is guaranteed that these $ n $ stations and $ n - 1 $ tunnels form a tree.

## 输出格式

Print one integer that is equal to the sum of distances between all pairs of stations after Sergey Semyonovich draws new tunnels between all pairs of stations that share a common neighbor in the original map.

## 样例 #1

### 样例输入 #1

```
4
1 2
1 3
1 4
```

### 样例输出 #1

```
6
```

## 样例 #2

### 样例输入 #2

```
4
1 2
2 3
3 4
```

### 样例输出 #2

```
7
```

## 提示

In the first sample, in the new map all pairs of stations share a direct connection, so the sum of distances is $ 6 $ .

In the second sample, the new map has a direct tunnel between all pairs of stations except for the pair $ (1, 4) $ . For these two stations the distance is $ 2 $ .

## 题解
我们思考每一次连边对于我们结果的影响，我们每一次连接之后，一定是去链接我们的新边，而不是走我们的旧边。于是，我们的计算就可以变为：$$\operatorname{dist}(i,j)=\lceil\frac{\operatorname{dis}}2\rceil=\frac{\operatorname{dis}+\lfloor\operatorname{dis}\operatorname{mod}2==1\rfloor}2.$$

把上式带入我们答案要求的式子，我们就有：
$$\frac{\sum_{i=1}^n\sum_{j=i}^n(\mathsf{d}(i,j)+[\mathsf{d}(i,j)\mathrm{~mod~}2==1])}2\:,$$

考虑后半部分的意义，我们有：我们最后要统计的结果是我们的原本图中树奇数路径的总数。

于是，我们就可以通过我们的 dfs 计算得到。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+10;
struct Tree
{
    int to,next;
}e[N*2];
int n,head[N],cnt,dep[N],size[N];
long long ans,num;
void add(int x,int y)
{
    e[++cnt].to=y;
    e[cnt].next=head[x];
    head[x]=cnt;
}
void DFS(int x,int last)
{
    size[x]=1;
    for(int i=head[x];i;i=e[i].next)
    {
        int v=e[i].to;
        if(v==last) continue ;
        dep[v]=dep[x]+1;
        DFS(v,x);
        size[x]+=size[v];
    }
}
int main()
{
    cin>>n;
    for(int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y),add(y,x);
    }
    DFS(1,0);
    for(int i=1;i<=n;i++)
    {
        ans+=size[i]*(long long)(n-size[i]);
        if(dep[i]%2==1) num++;
    }
    ans+=num*(long long)(n-num);
    cout<<ans/2;
    return 0;
}
```