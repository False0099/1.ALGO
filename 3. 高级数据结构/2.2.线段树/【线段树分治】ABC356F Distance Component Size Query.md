# [ABC 356 F] Distance Component Size Query

## 题面翻译

给你一个整数 $K$。对于初始为空的集合 $S$，依次处理 $Q$ 个操作：

- `1 x`: 给出一个整数 $x$ 。如果 $x$ 在 $S$ 中，则从 $S$ 中删除 $x$ 。否则，将 $x$ 加到 $S$ 中。
- `2 x`: 给出位于 $S$ 中的整数 $x$ 。考虑一个图，其中顶点是 $S$ 中的数字，并且当且仅当两个数字之间的绝对差最多为 $K$ 时，两个数字之间有一条边。求 $x$ 所在联通块中的顶点数。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc356/tasks/abc356_f

整数 $ K $ が与えられます。はじめ空である集合 $ S $ に対して、次の $ 2 $ 種類のクエリを順に $ Q $ 個処理してください。

- `1 x`：整数 $ x $ が与えられる。$ S $ に $ x $ が含まれているならば、$ S $ から $ x $ を取り除く。そうでないならば、$ S $ に $ x $ を追加する。
- `2 x`：$ S $ に含まれる整数 $ x $ が与えられる。$ S $ に含まれる数を頂点とし、差の絶対値が $ K $ 以下であるような数の間に辺を張ったグラフにおいて、$ x $ が属する連結成分の頂点数を出力する。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ Q $ $ K $ $ \mathrm{query}_1 $ $ \vdots $ $ \mathrm{query}_Q $

各クエリはそれぞれ次の形式で与えられる。

> $ 1 $ $ x $

> $ 2 $ $ x $

## 输出格式

クエリを処理せよ。

## 样例 #1

### 样例输入 #1

```
7 5
1 3
1 10
2 3
1 7
2 3
1 10
2 3
```

### 样例输出 #1

```
1
3
2
```

## 样例 #2

### 样例输入 #2

```
11 1000000000000000000
1 1
1 100
1 10000
1 1000000
1 100000000
1 10000000000
1 1000000000000
1 100000000000000
1 10000000000000000
1 1000000000000000000
2 1
```

### 样例输出 #2

```
10
```

## 样例 #3

### 样例输入 #3

```
8 0
1 1
1 2
2 1
1 1
1 2
1 1
1 2
2 1
```

### 样例输出 #3

```
1
1
```

## 提示

### 制約

- $ 1\ \leq\ Q\ \leq\ 2\times\ 10^5 $
- $ 0\ \leq\ K\ \leq\ 10^{18} $
- 各クエリにおいて、$ 1\leq\ x\ \leq\ 10^{18} $
- $ 2 $ 種類目のクエリにおいて与えられる $ x $ はその時点で $ S $ に含まれる。
- 入力は全て整数である。
 
### Sample Explanation 1

クエリの処理は次のように進行します。 - $ 1 $ 番目のクエリでは、$ S $ に $ 3 $ が追加され、$ S=\{3\} $ となります。 - $ 2 $ 番目のクエリでは、$ S $ に $ 10 $ が追加され、$ S=\{3,10\} $ となります。 - $ 3 $ 番目のクエリでは、$ 3,10 $ の $ 2 $ 頂点からなる辺のないグラフを考え、$ 3 $ が属する連結成分のサイズである $ 1 $ を出力します。 - $ 4 $ 番目のクエリでは、$ S $ に $ 7 $ が追加され、$ S=\{3,7,10\} $ となります。 - $ 5 $ 番目のクエリでは、$ 3,7,10 $ の $ 3 $ 頂点からなり、$ 3 $ と $ 7 $、$ 7 $ と $ 10 $ の間に辺のあるグラフを考え、$ 3 $ が属する連結成分のサイズである $ 3 $ を出力します。 - $ 6 $ 番目のクエリでは、$ S $ から $ 10 $ が削除され、$ S=\{3,7\} $ となります。 - $ 7 $ 番目のクエリでは、$ 3,7 $ の $ 2 $ 頂点からなり、$ 3 $ と $ 7 $ の間に辺のあるグラフを考え、$ 3 $ が属する連結成分のサイズである $ 2 $ を出力します。

## 题解
我们本题要**维护我们的图的连通性，和我们的连通块的大小**，我们之后，我们就可以通过我们的一个 set 维护我们的**一个点在那些时间上是存在的**，我们每一次删除的时候，我们就去进行我们的撤销，表示我们的这一段时间不存在这一个边。

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
int n,k;
const int N=3e5+10;
struct Q{
    int x,id;
};vector<Q> q[N];

int qtot;
map<int,int> occ;
struct Msg
{
    int x;
    int y;
    int sz;
}stk[N];
int top=0;

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
		stk[++top]={x, y, sz[x]};
		//if(rk[x]==rk[y]) rk[y]++;
	}	
	void resume(){
        Msg t=stk[top--];
		int y=fa[t.x];
        int x=t.x;
        sz[y]-=sz[x];
        fa[x]=x;
//        fa[t.y]-=t.sz;
//		fa[t.x]=t.x;
	}
}dsu;
struct skaljf
{
    vector<int> lsh;
    void push(int x){
        lsh.push_back(x);
    }
    void init(){
        sort(begin(lsh),end(lsh));
        lsh.erase(unique(begin(lsh),end(lsh)),end(lsh));
    }
    int get_rank(int x){
        return lower_bound(begin(lsh),end(lsh),x)-begin(lsh)+1;
    }
    int get_num(int k){
        return lsh[k];
    }
}discret;
struct node{
    int l;
    int r;
    vector<int> nums;
}tr[N<<2];
void build(int u,int l,int r){
    tr[u].l=l;
    tr[u].r=r;
    tr[u].nums.clear();
    if(l==r){
        return;
    }
    int mid=l+r>>1;
    build(u<<1,l,mid);
    build(u<<1|1,mid+1,r);
}

void assign(int u,int l,int r,int x){
    if(l<=tr[u].l&&tr[u].r<=r){
        //cerr<<"changed"<<tr[u].l<<" "<<tr[u].r<<" "<<x<<endl;
        tr[u].nums.push_back(x);
        return;
    }
    if(tr[u].l==tr[u].r){
        return;
    }
    int mid=tr[u].l+tr[u].r>>1;
    if(l<=mid){
        assign(u<<1,l,r,x);
    }
    if(r>mid){
        assign(u<<1|1,l,r,x);
    }
}
set<int> st;
void calc(int u){
//    cerr<<"tree="<<tr[u].l<<" "<<tr[u].r<<" "<<tr[u].nums.size()<<endl;
    int pref=top;
    for(auto i:tr[u].nums){
        auto it=st.insert(i).first;
        if(it!=st.begin()){
            auto pre=it;
            --pre;
            if(abs(*pre-*it)<=k){
                int x=discret.get_rank(*pre);
                int y=discret.get_rank(*it);
                //cerr<<"tree="<<tr[u].l<<" "<<tr[u].r<<endl;
                //cerr<<"merge: "<<x<<" "<<y<<endl;
                dsu.merge(x,y);
            }
        }
        auto suf=it;++suf;
        if(suf!=st.end()){
            if(abs(*suf-*it)<=k){
                int x=discret.get_rank(*suf);
                int y=discret.get_rank(*it);
                //cerr<<"tree="<<tr[u].l<<" "<<tr[u].r<<endl;
                //cerr<<"merge: "<<x<<" "<<y<<endl;
                dsu.merge(x,y);
            }
        }
    }
    if(tr[u].l==tr[u].r){
        for(auto [x,id]:q[tr[u].l]){
            x=discret.get_rank(x);
            x=dsu.find(x);
            cout<<dsu.sz[x]<<endl;
        }
        for(auto i:tr[u].nums){
            st.erase(i);
        }
        while(top>pref){
            dsu.resume();
        }
        return;
    }
    calc(u<<1);
    calc(u<<1|1);
    for(auto i:tr[u].nums){
        st.erase(i);
    }
    while(top>pref){
        dsu.resume();
    }
}
void solve(){
    cin>>n>>k;
    build(1,1,n);
    //cerr<<"ok"<<endl;
    for(int i=1;i<=n;i++){
        int op,x;
        cin>>op;
        cin>>x;
        if(op==1){
            discret.push(x);
            if(occ[x]){
                //cerr<<"change:"<<occ[x]<<" "<<i-1<<" "<<x<<endl;
                assign(1,occ[x],i-1,x);
                occ[x]=0;
            }else{
                occ[x]=i;
            }
        }else{
            q[i].push_back({x,++qtot});
        }
    }  
    discret.init();
    for(auto [x,t]:occ){
        if(t){
//            cerr<<"change:"<<occ[x]<<" "<<n<<" "<<x<<endl;
            assign(1,occ[x],n,x);
        }
    }
    dsu.init(n);
    calc(1);
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
    //cin>>t;
    init();
    while(t--){
        solve();
    }
}
```