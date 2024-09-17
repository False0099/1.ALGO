# [USACO 05 DEC] Layout G

## 题目背景

14 组数据，前 10 组为原数据，后 4 组为 hack 数据

## 题面翻译

正如其他物种一样，奶牛们也喜欢在排队打饭时与它们的朋友挨在一起。FJ 有编号为 $1\dots N$ 的 $N$ 头奶牛 $(2\le N\le 1000)$。开始时，奶牛们按照编号顺序来排队。奶牛们很笨拙，因此可能有多头奶牛在同一位置上。

有些奶牛是好基友，它们希望彼此之间的距离小于等于某个数。有些奶牛是情敌，它们希望彼此之间的距离大于等于某个数。

给出 $M_L$ 对好基友的编号，以及它们希望彼此之间的距离小于等于多少；又给出 $M_D$ 对情敌的编号，以及它们希望彼此之间的距离大于等于多少 $(1\le M_L,$ $M_D\le 10^4)$。

请计算：如果满足上述所有条件，$1$ 号奶牛和 $N$ 号奶牛之间的距离最大为多少。

## 输入输出格式

### 输入格式

第一行：三个整数 $N, M_L, M_D$，用空格分隔。

第 $2\dots M_L+1$ 行：每行三个整数 $A, B, D$，用空格分隔，表示 $A$ 号奶牛与 $B$ 号奶牛之间的距离须 $\le D$。保证 $1\le A<B\le N,$ $1\le D\le 10^6$. 

第 $M_L+2\dots M_L+M_D+1$ 行：每行三个整数 $A, B, D$，用空格分隔，表示 $A$ 号奶牛与 $B$ 号奶牛之间的距离须 $\ge D$。保证 $1\le A<B\le N,$ $1\le D\le 10^6$. 

### 输出格式

一行，一个整数。如果没有合法方案，输出 `-1`. 如果有合法方案，但 $1$ 号奶牛可以与 $N$ 号奶牛相距无穷远，输出 `-2`. 否则，输出 $1$ 号奶牛与 $N$ 号奶牛间的最大距离。

## 题目描述

Like everyone else, cows like to stand close to their friends when queuing for feed. FJ has N (2 <= N <= 1,000) cows numbered 1.. N standing along a straight line waiting for feed. The cows are standing in the same order as they are numbered, and since they can be rather pushy, it is possible that two or more cows can line up at exactly the same location (that is, if we think of each cow as being located at some coordinate on a number line, then it is possible for two or more cows to share the same coordinate). 

Some cows like each other and want to be within a certain distance of each other in line. Some really dislike each other and want to be separated by at least a certain distance. A list of ML (1 <= ML <= 10,000) constraints describes which cows like each other and the maximum distance by which they may be separated; a subsequent list of MD constraints (1 <= MD <= 10,000) tells which cows dislike each other and the minimum distance by which they must be separated. 

Your job is to compute, if possible, the maximum possible distance between cow 1 and cow N that satisfies the distance constraints.

## 输入格式

Line 1: Three space-separated integers: N, ML, and MD. 

Lines 2.. ML+1: Each line contains three space-separated positive integers: A, B, and D, with 1 <= A < B <= N. Cows A and B must be at most D (1 <= D <= 1,000,000) apart. 

Lines ML+2.. ML+MD+1: Each line contains three space-separated positive integers: A, B, and D, with 1 <= A < B <= N. Cows A and B must be at least D (1 <= D <= 1,000,000) apart.

## 输出格式

Line 1: A single integer. If no line-up is possible, output -1. If cows 1 and N can be arbitrarily far apart, output -2. Otherwise output the greatest possible distance between cows 1 and N.

## 样例 #1

### 样例输入 #1

```
4 2 1
1 3 10
2 4 20
2 3 3
```

### 样例输出 #1

```
27
```

## 提示

Explanation of the sample: 

There are 4 cows. Cows #1 and #3 must be no more than 10 units apart, cows #2 and #4 must be no more than 20 units apart, and cows #2 and #3 dislike each other and must be no fewer than 3 units apart. 

The best layout, in terms of coordinates on a number line, is to put cow #1 at 0, cow #2 at 7, cow #3 at 10, and cow #4 at 27.

## 题解
我们首先确定，我们能通过条件构造一个差分约束系统，之后我们再在这个系统上找 1-N 的最短路，就是我们的最长距离
同时我们由几个坑点：
1. 我们应该从 0 开始跑 spfa 判断图是不是联通的
2. 如果没有冲突，我们也应该连一条边。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ml,md,a,b,c,fst[10100],nex[50010],v[50010],w[50010],cnt,vis[10100],dis[10100],tim[10100];
queue<int> q;
void add(int a,int b,int c)
{
    nex[++cnt]=fst[a];
    fst[a]=cnt;
    v[cnt]=b;
    w[cnt]=c;
    return ;
}
int spfa(int k)
{
    memset(dis,0x7f/3,sizeof(dis));
    memset(vis,0,sizeof(vis));
    memset(tim,0,sizeof(tim));
    q.push(k);
    dis[k]=0;
    vis[k]=1;
    while(!q.empty())
    {
        int u=q.front();
        //cout<<u<<" ";
        q.pop();
        tim[u]++;
        vis[u]=0;
        if(tim[u]>n)
        return -1;
        for(int i=fst[u];i!=-1;i=nex[i])
        {
            if(dis[v[i]]>dis[u]+w[i])
            {
                dis[v[i]]=dis[u]+w[i];
                if(!vis[v[i]])
                {
                    q.push(v[i]);
                    vis[v[i]]=1;
                }
            }
        }
    }
    /*cout<<endl;
    for(int i=1;i<=n;i++)
    {
        cout<<dis[i]<<" ";
    }*/
    if(dis[n]>1e8)
    return -2;
    return dis[n];
}
int main()
{
    memset(fst,-1,sizeof(fst));
    cin>>n>>ml>>md;
    for(int i=1;i<=ml;i++)
    {
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c);
    }
    for(int i=1;i<=md;i++)
    {
        scanf("%d%d%d",&a,&b,&c);
        add(b,a,-c);
    }
    for(int i=1;i<n;i++)
    {
        add(i+1,i,0);
    }
    for(int i=1;i<=n;i++)
    {
        add(0,i,0);
    }
    int sp=spfa(0); 
    if(sp<=-1)
    {
    	cout<<sp;
    	return 0;
    }
    else
    {
    	cout<<spfa(1);
    }
    //cout<<" "<<sp;
    return 0;
}
```