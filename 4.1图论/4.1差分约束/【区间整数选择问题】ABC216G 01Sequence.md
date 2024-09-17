# [ABC 216 G] 01 Sequence

## 题面翻译

你需要构造出一个长度为 $n$ 的 $01$ 序列，满足 $m$ 个限制 $(l_i,r_i,x_i)$：在 $[l_i,r_i]$ 这段区间内，序列上 $1$ 的个数不小于 $x_i$。**你需要保证你的方案中包含 $1$ 的个数最小。**

数据保证有解。

$1 \le n,m \le 2 \times 10^5$

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc216/tasks/abc216_g

`0` と `1` のみからなる長さ $ N $ の数列 $ A=(A_1, A_2,\dots, A_N) $ であって、以下の条件を満たすものを考えます。

> すべての $ i=1,2,\dots, M $ について、$ A_{L_i}, A_{L_i+1},\dots\ ,A_{R_i} $ に `1` が $ X_i $ 個以上含まれる

条件を満たす数列 $ A $ のうち、含まれる `1` の数が**最も少ない**例を $ 1 $ つ出力してください。

なお、制約のもとで条件を満たす数列 $ A $ は必ず存在します。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ M $ $ L_1 $ $ R_1 $ $ X_1 $ $ L_2 $ $ R_2 $ $ X_2 $ $ \vdots $ $ L_M $ $ R_M $ $ X_M $

## 输出格式

`0` と `1` のみからなる数列 $ A $ を空白区切りで出力せよ。

> $ A_1 $ $ A_2 $ $ \dots $ $ A_N $

数列 $ A $ は上記の条件を全て満たさなければならない。

## 样例 #1

### 样例输入 #1

```
6 3
1 4 3
2 2 1
4 6 2
```

### 样例输出 #1

```
0 1 1 1 0 1
```

## 样例 #2

### 样例输入 #2

```
8 2
2 6 1
3 5 3
```

### 样例输出 #2

```
0 0 1 1 1 0 0 0
```

## 提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ \min (2\ \times\ 10^5,\ \frac{N (N+1)}{2}\ ) $
- $ 1\ \leq\ L_i\ \leq\ R_i\ \leq\ N $
- $ 1\ \leq\ X_i\ \leq\ R_i-L_i+1 $
- $ i\ \neq\ j $ ならば $ (L_i, R_i)\ \neq\ (L_j, R_j) $
- 入力は全て整数

### Sample Explanation 1

`1 1 0 1 1 0` などの答えも正解です。 `0 1 1 1 1 1` などの答えは含まれる `1` の数が最小化されていないので、不正解です。

## 题解
我们本题注意到，我们要求我们的区间内 1的数量**大于等于 m**，就等价于我们的一个**差分约束方程**$s[r]-s[l-1]\geq m$。但是这样**还是不够的**，我们考虑建立尽可能多的方程，我们还有一个约束条件是，我们的**某一个位置只能取 0 或 1**，因此，我们就可以有：$0\leq s[i]-s[i-1]\leq 1$,这个时候，我们就可以有下面的连边方式：$l-1\to -r$ (m), $i\to i-1(1)$, $i-1\to i(0)$,显然，我们对于**带有负权边**只能采用我们的 bellman-ford 算法，但是我们一定超市，所以我们考虑优化，例如：我们可以考虑**更换我们的渐变方式**。我们考虑计算我们的**0 的个数**。这个时候，我们的约束条件变为：$//sum[r]<=sum[l-1]+r-l+1-x //sum[l]<=sum[l-1]+1 //sum[l-1]<=sum[l]+0$
我们重新建边跑最短路即可：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
typedef pair<int,int> PII;
int e[N],w[N],ne[N],h[N],idx;
bool vis[N];
void add(int a,int b,int c){
	e[idx]=b;
	w[idx]=c;
	ne[idx]=h[a];
	h[a]=idx++; 
}
int dist[N];
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int n,m;
	cin>>n>>m;
	memset(dist,0x3f3f3f,sizeof dist);
	memset(h,-1,sizeof h);
	for(int i=0;i<m;i++){
		int l,r,x;
		cin>>l>>r>>x; 
		add(l-1,r,r-l+1-x);
	}
	for(int i=1;i<=n;i++){
		add(i-1,i,1);
		add(i,i-1,0);
	}
	dist[0]=0;//为什么要0 
	vis[0]=0;
	priority_queue<PII,vector<PII>,greater<PII>> heap;
	heap.push({dist[0],0});
	while(heap.size()){
		int u=heap.top().second;
		heap.pop();
		if(vis[u]) continue;
		vis[u]=true;
		for(int i=h[u];i!=-1;i=ne[i]){
			int v=e[i];
			int val=w[i];
			if(dist[v]>dist[u]+val){
				dist[v]=dist[u]+val;
				heap.push({dist[v],v});
			}
		} 
	}
	for(int i=1;i<=n;i++){
		cout<<(dist[i]==dist[i-1])<<" ";
	}
}
```