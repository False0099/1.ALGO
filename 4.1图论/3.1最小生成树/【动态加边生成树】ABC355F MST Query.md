# [ABC 355 F] MST Query

## 题面翻译

给你一棵 $n$ 个点的带边权的树，有 $q$ 次询问，每次询问加一条带边权的边，输出当前的最小生成树的边权和。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc355/tasks/abc355_f

頂点に $ 1 $ から $ N $ の番号が、辺に $ 1 $ から $ N-1 $ の番号が付いた $ N $ 頂点 $ N-1 $ 辺の重み付き無向連結グラフ $ G $ が与えられます。辺 $ i $ は頂点 $ a_i $ と頂点 $ b_i $ を結んでおり、その重みは $ c_i $ です。

$ Q $ 個のクエリが与えられるので順に処理してください。$ i $ 番目のクエリは以下で説明されます。

- 整数 $ u_i, v_i, w_i $ が与えられる。$ G $ の頂点 $ u_i, v_i $ の間に重み $ w_i $ の辺を追加する。その後、$ G $ の最小全域木に含まれる辺の重みの和を出力する。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ Q $ $ a_1 $ $ b_1 $ $ c_1 $ $ \vdots $ $ a_{N-1} $ $ b_{N-1} $ $ c_{N-1} $ $ u_1 $ $ v_1 $ $ w_1 $ $ \vdots $ $ u_Q $ $ v_Q $ $ w_Q $

## 输出格式

$ Q $ 行出力せよ。$ i $ 行目には $ i $ 番目のクエリに対する答えを出力せよ。

## 样例 #1

### 样例输入 #1

```
4 4
1 2 6
2 3 5
2 4 4
1 3 3
1 2 3
1 4 10
3 4 1
```

### 样例输出 #1

```
12
10
10
7
```

## 样例 #2

### 样例输入 #2

```
8 6
1 8 8
1 6 10
1 5 8
2 6 6
6 7 6
1 3 9
2 4 7
1 3 4
1 6 7
3 4 6
1 5 1
7 8 4
3 5 3
```

### 样例输出 #2

```
49
46
45
38
34
33
```

## 提示

### 制約

- $ 2\leq\ N\leq\ 2\ \times\ 10^5 $
- $ 1\leq\ Q\leq\ 2\ \times\ 10^5 $
- $ 1\leq\ a_i\lt\ b_i\leq\ N $
- $ 1\leq\ u_i\lt\ v_i\leq\ N $
- $ 1\leq\ c_i, w_i\leq\ 10 $
- クエリを処理する前のグラフは連結
- 入力はすべて整数
 
### Sample Explanation 1

各クエリで辺を追加した後のグラフを示しています。最小全域木に含まれる辺は赤色で塗られています。 !\ [\](https://img.atcoder.jp/abc355/4e83a6e54750f138ecada66dd93b2b67.png)

## 题解
本题，我们理论上可以通过我们的 LCT 来解决，但是因为我们有一个哥哥宾得权值都是小于 10 的，我们于是可以通过维护我们的一个**并查集**，维护我们所有满足**权值<x**的边所构成的连通性是什么样的。

这样，我们每一次加边的时候，就可以检测，如果我们在权值为 x 的时候，对应的边的两个断点已经联通，那么我们直接忽视这一条边，否则，我们取找到**第一个联通这两个边**的权值，然后替换这一个权值。

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
struct node
{
    int a;
    int b;
    int c;
    /* data */
};
const int V=15;
const int N=2e5+10;
mt19937 rnd(time(0));
struct Dsu{
	int fa[N], rk[N],sz[N];
	void init(int n){
        for(int i=1;i<=n;i++){
            fa[i]=i;
            sz[i]=1;
            rk[i]=rnd();
        }
	}
	int find(int x){
		return x==fa[x]? x: find(fa[x]);
	}
	bool same(int x, int y){
		return find(x)==find(y);
	}
	void merge(int x, int y){
		x=find(x), y=find(y);
		if(x==y) return;
		if(rk[x]>rk[y]) swap(x, y);
		fa[x]=y;
        sz[y]+=sz[x];
		//stk[++top]={x, y, sz[x]};
		//if(rk[x]==rk[y]) rk[y]++;
	}	
}dsu[V];
void solve(){
    int n,q;
    cin>>n>>q;    
    int res=0;
    for(int i=1;i<=10;i++){
        dsu[i].init(n);
    }
    for(int i=0;i<n-1;i++){
        int a,b,c;
        cin>>a>>b>>c;
        for(int j=c;j<=10;j++){
            dsu[j].merge(a,b);
        }  
        res+=c;
    }
    while(q--){
        int a,b,c;
        cin>>a>>b>>c;
        bool flg=1;
        if(flg==0){
            cout<<res<<endl;
            continue;
        }
        for(int j=c;j<=10;j++){
            if(dsu[j].same(a,b)){
                res-=j;
                res+=c;
                break;
            }
        }
        for(int j=c;j<=10;j++){
            dsu[j].merge(a,b);
        }
        cout<<res<<endl;
    }
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
 //   cin>>t;
    init();
    while(t--){
        solve();
    }
}
```