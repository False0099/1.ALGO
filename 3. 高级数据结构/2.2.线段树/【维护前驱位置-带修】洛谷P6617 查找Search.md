# 查找 Search

## 题目背景

>   也许，同学间最好的结局就是朋友吧。

$\mu ry$ 是一个可爱的女孩子。

在她所住的小区里有排成一排的 $n$ 个垃圾桶，从左至右第 $i$ 个垃圾桶里都装着编号为 $a_i$ 的垃圾。

$\mu ry$ 不喜欢无序，于是就想把社区里编号和为 $w$ 的垃圾都清在一起。

但是调皮的 $\text{LeverImmy}$ 可能会把某个垃圾桶里的垃圾偷换成另一种。

生气的 $\mu ry$ 想考考 $\text{LeverImmy}$ 一个区间 $[l, r]$ 内是否存在编号和为 $w$ 的垃圾。

但 $\text{LeverImmy}$ 也不会解决这个问题，于是他找到了聪明的你。

## 题目描述

给定 $n$ 个垃圾桶，你需要维护一个数据结构，支持以下操作：

-   `1 pos val` 表示将第 $pos$ 个垃圾桶里的垃圾的编号换成 $val$；

-   `2 l r` 询问在 $[l\oplus cnt, r\oplus cnt]$ 内是否存在垃圾编号和为 $w$ 的 **两个** 垃圾桶。

其中 $\oplus$ 表示异或运算，$cnt$ 表示在 **此次询问之前**，答案为 `Yes` 的个数。

对于每个操作 2，若存在请输出 `Yes`，不存在请输出 `No`。

值得注意的是，对于所有询问， $w$ 为 **同一个数**。

## 输入格式

第一行共三个整数 $n, m, w$，表示序列长度、接下来的操作个数与 $w$。

第二行共 $n$ 个整数 $a_1, a_2, \cdots, a_n$ 描述了这个每个垃圾桶内垃圾的编号 $a$。

接下来的 $m$ 行，每行三个整数，格式为 `opt x y`。

## 输出格式

令操作 2 的次数为 $t$，输出数据共 $t$ 行。

第 $i$ 行表示第 $i$ 个操作 2 的结果，即 `Yes` 或 `No`。

## 样例 #1

### 样例输入 #1

```
6 4 6
1 3 2 5 5 6
2 1 4
1 4 1
2 0 5
2 3 7
```

### 样例输出 #1

```
Yes
No
Yes
```

## 样例 #2

### 样例输入 #2

```
10 20 10
9 3 6 3 3 3 3 1 4 9
1 3 9
1 6 9
2 3 10
1 3 9
2 4 4
1 1 7
1 1 3
1 5 6
1 3 9
2 4 7
1 2 7
2 6 8
1 6 10
2 2 9
1 7 9
2 3 1
1 3 5
1 5 6
1 9 10
1 3 6
```

### 样例输出 #2

```
Yes
No
No
No
Yes
Yes
```

## 提示

本题采用 **捆绑测试**，开启 **O 2 优化**。

$\text{Subtask 1 (7 pts)}:$ 保证 $1 \le n, m, w \le 2\cdot10^3$，**时限 $1\text{s}$**；

$\text{Subtask 2 (20 pts)}:$ 保证 $1 \le n, m, w \le 1\cdot10^5$，$opt = 2$，**时限 $2\text{s}$**；

$\text{Subtask 3 (30 pts)}:$ 保证 $1 \le n, m, w \le 1\cdot10^5$，**时限 $2\text{s}$**；

$\text{Subtask 4 (43 pts)}:$ 没有特殊限制，**时限 $4\text{s}$**；

对于所有数据， $1 \le n, m, w \le 5\cdot10^5$，$0 \le a_i \le w$。

数据保证对于每个操作，$1 \le pos \le n$，$0 \le val \le w$，$1 \le l \le r \le n$。

由于输入输出量较大，建议使用更快的输入输出方式。

---

#### 输入 #1 解释

第一次操作，询问区间 $[1, 4]$ 中是否有两个数加起来为 $6$，显然有 $a_1 + a_4 = 6$，因此输出 `Yes`；

第二次操作，修改 $a_4$ 为 $1$，则序列变为 $[1, 3, 2, 1, 5, 6]$；

第三次操作，询问区间 $[1, 4]$ 中是否有 **两个** 数加起来为 $6$，无，因此输出 `No`。

第四次操作，询问区间 $[2, 6]$ 中是否有两个数加起来为 $6$，显然有 $a_4 + a_5 = 6$，因此输出 `Yes`。

## 题解
本题，我们首先有一个经典的 trick 是，求出我们的每一个元素的前一个位置在哪里，然后我们就可以对于我们的所有的元素，找到一个对应的答案。

但是，我们本体是一个带有修改的，那么我们应该怎么处理呢？我们的想法是：考虑每一次修改对于我们的所有的答案的影响是什么。我们发现，如果我们暴力的修改，我们的答案显然是 $o(qn)$ 的。

我们这个时候考虑一个优化，有一个比较巧妙的转化，就是如果一个数的前驱比它前面第一个与他相同的位置要小，则我们直接把这个位置的前驱设为零。可以发现这样是对的。

发现新定义的前驱会改变的位置最多只有五个：这个位置，这个位置原来后面第一个与他相同的位置，这个位置原来后面第一个与他相加得 w 的位置，这个位置后来后面第一个与他相同的位置，这个位置后来后面第一个与他相加得 w 的位置。

直接用 `set` 维护每个值出现的位置，然后在线段树上修改即可。

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
const int N=5e5+10;
int a[N];
class SegmentTree
{
public:
    struct Node
    {
        int l, r;
        int maxx;
    }tr[N << 2];
    Node merge(Node x, Node y)
    {
        if (x.l == -1) return y;
        if (y.l == -1) return x;
        Node z;
        z.l=min(x.l,y.l);
        z.r=max(x.r,y.r);
        z.maxx=max(x.maxx,y.maxx);
        return z;
    }//这里需要改 
    void pushup(int u)
    {
        tr[u] = merge(tr[u << 1], tr[u << 1 | 1]);
    }
    void build(int u, int l, int r)
    {
        tr[u] = {l, r, 0};
        if (l == r) return;
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
    void update(int u, int p, int x)
    {
        if (tr[u].l == tr[u].r)
        {
            //这里需要改 
            tr[u].maxx=x;
            return;
        }
        int mid = tr[u].l + tr[u].r >> 1;
        if (p <= mid) update(u << 1, p, x);
        else update(u << 1 | 1, p, x);
        pushup(u);
    }
    Node query(int u, int l, int r)
    {
        if (tr[u].l >= l and tr[u].r <= r) 
        {
            return tr[u];
        }
        int mid = tr[u].l + tr[u].r >> 1;
        Node ret;
        ret.l = -1;
        if (l <= mid) ret = query(u << 1, l, r);
        if (r > mid) ret = merge(ret, query(u << 1 | 1, l, r));
        return ret;
    }
}t;
set<int> st[N];
//set<int> cnt_[N];
void init(){
    
}
void solve(){
    int n,m,w;
    cin>>n>>m>>w;
    t.build(1,1,n);
    auto calc=[&](int x){
            auto it1=st[a[x]].lower_bound(x);
            auto it2=st[w-a[x]].lower_bound(x);
            if(it2==st[w-a[x]].begin()){
                return 0ll;
            }  
            if(it1==st[a[x]].begin()){
                return *(--it2);
            }
            --it1;
            --it2;
            if(*it1>*it2){
                return 0ll;
            }
            return *it2;
    };
    for(int i=1;i<=n;i++){
        cin>>a[i];
        t.update(1,i,calc(i));
        st[a[i]].insert(i);
    }
    int cnt=0;
    for(int i=1;i<=m;i++){
        int op;
        cin>>op;
        if(op==1){
            vector<int> upd;
            int x,y;
            cin>>x>>y;

            auto it=st[a[x]].upper_bound(x);
            if(it!=st[a[x]].end()){
                upd.push_back(*it);
            }    
            it=st[w-a[x]].upper_bound(x);
            if(it!=st[w-a[x]].end()){
                upd.push_back(*it);
            }

            st[a[x]].erase(x);
            a[x]=y;
            st[a[x]].insert(x);
            upd.push_back(x);//调试注意？

            it=st[a[x]].upper_bound(x);
            if(it!=st[a[x]].end()){
                upd.push_back(*it);
            }
            it=st[w-a[x]].upper_bound(x);
            if(it!=st[w-a[x]].end()){
                upd.push_back(*it);
            }
            for(auto p:upd){
                t.update(1,p,calc(p));
            }
        }else{
            int x,y;
            cin>>x>>y;
            x^=cnt;
            y^=cnt;
            cerr<<x<<" "<<y<<endl;
            cerr<<t.query(1,x,y).maxx<<endl;
            if(t.query(1,x,y).maxx>=x){
                cnt++;
                cout<<"Yes"<<endl;
            }else{
                cout<<"No"<<endl;
            }
        }
    }
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
//    cin>>t;
    init();
    while(t--){
        solve();
    }
}
```