# [ABC 070 D] Transit Tree Path

## 题面翻译

给出一棵有 N 个结点的树，给出 Q 个询问，求结点 xj 过结点 K 到节点 yj 的最短距离

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc070/tasks/abc070_d

$ N $ 頂点の木が与えられます。   
 木とはグラフの一種であり、頂点の数を $ N $ とすると、辺の数が $ N-1 $ 本である閉路のない連結グラフです。   
 $ i (1≦i≦N-1) $ 番目の辺は 頂点 $ a_i $ と 頂点 $ b_i $ を距離 $ c_i $ で結びます。

また、$ Q $ 個の質問クエリと整数 $ K $ が与えられます。

- $ j (1≦j≦Q) $ 番目の質問クエリでは、頂点 $ x_j $ から 頂点 $ K $ を経由しつつ、頂点 $ y_j $ まで移動する場合の最短経路の距離を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ a_1 $ $ b_1 $ $ c_1 $ $ : $ $ a_{N-1} $ $ b_{N-1} $ $ c_{N-1} $ $ Q $ $ K $ $ x_1 $ $ y_1 $ $ : $ $ x_{Q} $ $ y_{Q} $

## 输出格式

質問クエリの解答を $ Q $ 行出力せよ。   
 $ j (1≦j≦Q) $ 行目には、$ j $ 番目のクエリの答えを出力せよ。

## 样例 #1

### 样例输入 #1

```
5
1 2 1
1 3 1
2 4 1
3 5 1
3 1
2 4
2 3
4 5
```

### 样例输出 #1

```
3
2
4
```

## 样例 #2

### 样例输入 #2

```
7
1 2 1
1 3 3
1 4 5
1 5 7
1 6 9
1 7 11
3 2
1 3
4 5
6 7
```

### 样例输出 #2

```
5
14
22
```

## 样例 #3

### 样例输入 #3

```
10
1 2 1000000000
2 3 1000000000
3 4 1000000000
4 5 1000000000
5 6 1000000000
6 7 1000000000
7 8 1000000000
8 9 1000000000
9 10 1000000000
1 1
9 10
```

### 样例输出 #3

```
17000000000
```

## 提示

### 制約

- $ 3≦N≦10^5 $
- $ 1≦a_i, b_i≦N\ (1≦i≦N-1) $
- $ 1≦c_i≦10^9\ (1≦i≦N-1) $
- 与えられるグラフは木である。
- $ 1≦Q≦10^5 $
- $ 1≦K≦N $
- $ 1≦x_j, y_j≦N\ (1≦j≦Q) $
- $ x_j≠y_j\ (1≦j≦Q) $
- $ x_j≠K, y_j≠K\ (1≦j≦Q) $

### Sample Explanation 1

与えられた $ 3 $ つの質問クエリに対する最短経路は以下の通りです。 - $ 1 $ つ目の質問クエリ: 頂点 $ 2 $ → 頂点 $ 1 $ → 頂点 $ 2 $ → 頂点 $ 4 $ : 距離 $ 1+1+1=3 $ - $ 2 $ つ目の質問クエリ: 頂点 $ 2 $ → 頂点 $ 1 $ → 頂点 $ 3 $ : 距離 $ 1+1=2 $ - $ 3 $ つ目の質問クエリ: 頂点 $ 4 $ → 頂点 $ 2 $ → 頂点 $ 1 $ → 頂点 $ 3 $ → 頂点 $ 5 $ : 距離 $ 1+1+1+1=4 $

### Sample Explanation 2

質問クエリに対する最短経路は、必ず頂点 $ K=2 $ を通過する必要があります。

## 题解
本题我们虽然题目中给的是一个树，但是因为我们的**各个节点的边权不固定**，所以我们如果直接套用模板的话不太方便使用，于是我们我们能否**描述我们的这一个路径形态**，我们发现，我们的这一个路径，因为要求**必须经过某一个点的**路径的最小值之和，并且我们的这一个图还是一个**无向图**，于是我们就可以转换为求我们的**无向图上**我们从我们的中间点，到两个点的最小距离的和是多少即可。
```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
typedef pair<int,int> PII;
int h[N],ne[N<<1],e[N<<1],w[N<<1],idx;
void add(int a,int b,int c){
	e[idx]=b;
	ne[idx]=h[a];
	w[idx]=c;
	h[a]=idx++;
}
int dist[N];
signed main(){
	int n;
	cin>>n;
	memset(h,-1,sizeof h);
	memset(dist,0x3f3f3f3f3f,sizeof dist);
	for(int i=1;i<n;i++){
		int a,b,c;
		cin>>a>>b>>c;
		add(a,b,c);
		add(b,a,c);
	}
	int q,k;
	cin>>q>>k;
	dist[k]=0;
	priority_queue<PII,vector<PII>,greater<PII>> heap;
	heap.push({0,k});
	while(heap.size()){
		int dist_prev=heap.top().first;
		int u=heap.top().second;
		heap.pop();
		for(int i=h[u];i!=-1;i=ne[i]){
			int v=e[i];
			int val=w[i];
			if(dist[v]>dist[u]+val){
				dist[v]=dist[u]+val;
				heap.push({dist[v],v});
			}
		}
	}
	while(q--){
		int a,b;
		cin>>a>>b;
		cout<<dist[a]+dist[b]<<endl;
	}
}
```