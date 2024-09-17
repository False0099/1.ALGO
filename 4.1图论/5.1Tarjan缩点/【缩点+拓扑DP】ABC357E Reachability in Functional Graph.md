# [ABC 357 E] Reachability in Functional Graph

## 题面翻译

有一个 $N$ 个点 $N$ 条边的有向图。每个点的出度为 $1$，第 $i$ 个点有一条指向 $a_i$ 的有向边。若从节点 $u$ 能走到节点 $v$，则称 $(u, v)$ 为可达点对。注意 $(u, u)$ 也是可达点对。求给定的有向图中可达点对的个数。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc357/tasks/abc357_e

頂点に $ 1 $ から $ N $ の番号がついた $ N $ 頂点 $ N $ 辺の有向グラフがあります。  
 全ての頂点の出次数は $ 1 $ で、頂点 $ i $ から出ている辺は頂点 $ a_i $ へ伸びています。  
 頂点の組 $ (u,\ v) $ であって、頂点 $ u $ から頂点 $ v $ へ到達可能であるものの個数を求めてください。

ここで、頂点 $ u $ から頂点 $ v $ へ到達可能であるとは、ある長さ $ K+1 $ の頂点の列 $ w_0,\ w_1,\ \dots,\ w_K $ であって次の条件を全て満たすものが存在することをいいます。特に、$ u\ =\ v $ の時は常に到達可能です。

- $ w_0\ =\ u $
- $ w_K\ =\ v $
- $ 0\ \leq\ i\ \lt\ K $ を満たす全ての $ i $ について、頂点 $ w_i $ から頂点 $ w_{i+1} $ へ伸びる辺が存在する。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ a_1 $ $ a_2 $ $ \dots $ $ a_N $

## 输出格式

頂点の組 $ (u,\ v) $ であって、頂点 $ u $ から頂点 $ v $ へ到達可能であるものの個数を出力せよ。

## 样例 #1

### 样例输入 #1

```
4
2 1 1 4
```

### 样例输出 #1

```
8
```

## 样例 #2

### 样例输入 #2

```
5
2 4 3 1 2
```

### 样例输出 #2

```
14
```

## 样例 #3

### 样例输入 #3

```
10
6 10 4 1 5 9 8 6 5 1
```

### 样例输出 #3

```
41
```

## 提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ a_i\ \leq\ N $
- 入力される値は全て整数
 
### Sample Explanation 1

頂点 $ 1 $ から到達可能である頂点は頂点 $ 1,\ 2 $ です。頂点 $ 2 $ から到達可能である頂点は頂点 $ 1,\ 2 $ です。頂点 $ 3 $ から到達可能である頂点は頂点 $ 1,\ 2,\ 3 $ です。頂点 $ 4 $ から到達可能である頂点は頂点 $ 4 $ のみです。 よって、頂点の組 $ (u,\ v) $ であって頂点 $ u $ から頂点 $ v $ へ到達可能であるものの個数は $ 8 $ 個です。頂点 $ 4 $ から出ている辺は自己ループ、すなわち頂点 $ 4 $ 自身へ伸びている辺である点に注意してください。

## 题解
本题我们首先考虑我们从某一个点可以到达的所有点是多少，我们发现，我们如果在一个环内，我们环上的所有点能够到达这个外拓扑序相连的所有点的总和，于是我们在进行我们的维护的时候，需要维护两个东西：一个是我们的**拓扑序前缀和**，一个是我们的答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e6+10, M =1e6+10;

int n, m, mod;
int h[N],e[M<<1],ne[M<<1],idx,val[N];//原图参数 
/*tarjan中间量*/
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
/*tarjan中间量*/
int id[N], scc_size[N];//新旧关系 
int scc_cnt;  //新图的n 
int hs[N],sum[N],dp[N],in[N];//新图的参数 
int f[N],g[N];
int ans; 
void add(int h[],int a,int b)
{
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
int res=0;
void tarjan(int u)
{
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u,in_stk[u] = true;
    for(int i =h[u];~i;i=ne[i])
    {
        int j = e[i];
        if(!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u],low[j]);
        }
        else if(in_stk[j])low[u] = min(low[u],dfn[j]);
    }
    if(dfn[u]==low[u])
    {
        ++scc_cnt;
        int y;
        do{
            y=stk[top--];
            in_stk[y] = false;
            id[y] = scc_cnt;
            //sum[scc_cnt]+=val[y];//处理我们的合并点 
            scc_size[scc_cnt]++;
        }while(y!=u);
    }
}
void topsort(){
	queue<int> q;
	int tot=0;
	for(int i=1;i<=scc_cnt;i++){
		if(in[i]==0){
			q.push(i);
		}
		f[i]=scc_size[i];
        g[i]=scc_size[i]*scc_size[i];
	}
	while(q.size()){
		int now=q.front();
		q.pop();
//        cerr<<now<<" "<<scc_size[now]<<endl;
		for(int i=hs[now];i!=-1;i=ne[i]){
			int v=e[i];
			in[v]--;
            f[v]+=f[now];
            g[v]+=f[now]*scc_size[v];
			if(in[v]==0){
				q.push(v);
			}
		}
        //cerr<<now<<" ";
	}
	for(int i=1;i<=scc_cnt;i++){
		res+=g[i];
	}
}
signed main()
{
    memset(h,-1,sizeof h);
    memset(hs,-1,sizeof hs);
    cin >> n;
    for(int i=1;i<=n;i++){
    	int b;
        cin>>b;
        add(h,i,b);
	}
    for(int i = 1;i<=n;i++)
    {
        if(!dfn[i])
        {
            tarjan(i);
        }
    }
    //set<pair<int,int>> st;
    //st.clear();
    for(int i=1;i<=n;i++)
    {
        for(int j = h[i];~j;j=ne[j])
        {
            int k = e[j];
            int a = id[i],b= id[k];            
            if(a!=b)
            {
            		add(hs,a,b);
            		in[b]++;
            }
        }
    }
    // for(int i=1;i<=n;i++){
    //     cerr<<id[i]<<" ";
    // }
    // cerr<<endl;
    // cerr<<scc_cnt<<endl;
//	puts("");
	topsort();
    cout<<res<<endl;
	//cout<<ans<<endl;
}
```
