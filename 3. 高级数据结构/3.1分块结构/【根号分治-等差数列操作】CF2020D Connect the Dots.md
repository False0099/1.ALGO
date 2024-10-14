# Connect the Dots

## 题面翻译

### 题意描述
爱丽丝画了一条直线，并在上面标记了 n 个点，从 1 到 n 进行索引。最初，点之间没有弧，所以它们都是不相交的。之后，Alice 执行以下类型的 m 个操作：

1.   她选了三个整数 ai bi 和 ki
2.   她选择点 ai，ai+di, ai+2 di...... Ai+ki*di，并用弧线连接每对点。

在完成所有 m 操作后，她想知道这些点形成的连接组件的数量。

如果两个点之间通过几个（**可能为零**）弧和其他点存在路径，则称这两个点位于一个连接的组件中。
### 输入格式
每个测试包含多个测试用例。第一行包含测试用例的数量 t。每个测试用例的描述如下:


每个测试用例的第一行包含两个整数 n 和 m。
以下 m 行中的第 i 行包含三个整数。

保证所有测试用例中的 n 和 m 之和不超过 2*1e5。

### 输出格式
对于每个测试用例，输出连接的组件数量。

## 题目描述

One fine evening, Alice sat down to play the classic game "Connect the Dots", but with a twist.

To play the game, Alice draws a straight line and marks $ n $ points on it, indexed from $ 1 $ to $ n $ . Initially, there are no arcs between the points, so they are all disjoint. After that, Alice performs $ m $ operations of the following type:

- She picks three integers $ a_i $ , $ d_i $ ( $ 1 \le d_i \le 10 $ ), and $ k_i $ .
- She selects points $ a_i, a_i+d_i, a_i+2 d_i, a_i+3 d_i, \ldots, a_i+k_i\cdot d_i $ and connects each pair of these points with arcs.

After performing all $ m $ operations, she wants to know the number of connected components $ ^\dagger $ these points form. Please help her find this number.

 $ ^\dagger $ Two points are said to be in one connected component if there is a path between them via several (possibly zero) arcs and other points.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 1 \le m \le 2 \cdot 10^5 $ ).

The $ i $ -th of the following $ m $ lines contains three integers $ a_i $ , $ d_i $ , and $ k_i $ ( $ 1 \le a_i \le a_i + k_i\cdot d_i \le n $ , $ 1 \le d_i \le 10 $ , $ 0 \le k_i \le n $ ).

It is guaranteed that both the sum of $ n $ and the sum of $ m $ over all test cases do not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the number of connected components.

## 样例 #1

### 样例输入 #1

```
3
10 2
1 2 4
2 2 4
100 1
19 2 4
100 3
1 2 5
7 2 6
17 2 31
```

### 样例输出 #1

```
2
96
61
```

## 提示

In the first test case, there are $ n = 10 $ points. The first operation joins the points $ 1 $ , $ 3 $ , $ 5 $ , $ 7 $ , and $ 9 $ . The second operation joins the points $ 2 $ , $ 4 $ , $ 6 $ , $ 8 $ , and $ 10 $ . There are thus two connected components: $ \{1, 3, 5, 7, 9\} $ and $ \{2, 4, 6, 8, 10\} $ .

In the second test case, there are $ n = 100 $ points. The only operation joins the points $ 19 $ , $ 21 $ , $ 23 $ , $ 25 $ , and $ 27 $ . Now all of them form a single connected component of size $ 5 $ . The other $ 95 $ points form single-point connected components. Thus, the answer is $ 1 + 95 = 96 $ .

In the third test case, there are $ n = 100 $ points. After the operations, all odd points from $ 1 $ to $ 79 $ will be in one connected component of size $ 40 $ . The other $ 60 $ points form single-point connected components. Thus, the answer is $ 1 + 60 = 61 $ .

## 题解
本题我们看到等差数列操作，显然的思路是，通过根号分治方法，我们不妨考虑两种方法，一种是 $d_{i}$ 很大时候，我们直接暴力操作即可，另一种是 $d_{i}$ 很小的时候，我们直接使用我们的暴力 dp，我们设 $dp[i][d_{i}]$ 表示我们在 $i$ 这一个点，我们的贡茶为 $d_{i}$ 时，我们能够走到的最大的 $k_{i}$ 在哪里。

对于我们的 $dp[i][d_{i}]$,一开始，我们的意义也许并不明确，但是我们可以考虑使用我们的特殊样例，就比如我们的 $d_{i}=1$ 的时候来考虑。

显然，这个时候，我们的一个想法是，维护我们的最远何必 ing 的点咋哪里，这就需要我们倒序枚举并且根据我们的这一个来更新。这一步的时间复杂度是 $o(nd_{i})$ 的，

于是，我们也就完成了本题。当然，因为本题我们的 $d$ 很小，所以我们其实大部分情况都是属于我们的第二种情况。
```
#include <bits/stdc++.h>
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
const int N=2e5+10;

int top=0;

mt19937 rnd(time(0));
int fa[N];
int find(int u){
    if(u==fa[u]){
        return u;
    }else{
        return fa[u]=find(fa[u]);
    }
}
void merge(int a,int b){
    int aa=find(a);
    int bb=find(b);
    if(a==b){
        return;
    }else{
        fa[aa]=bb;
    }
}
const int M=sqrt(N)+10;
int f[M][N];
void solve(){
    int n,m;
    cin>>n>>m;
    //int V=sqrt(n); 
    int V=sqrt(n);
    for (int i=1;i<=V;i++)
        for (int j=1;j<=n;j++)
            f[i][j]=0;
    for (int i=1;i<=n;i++)
        fa[i]=i;
    for (int i=1;i<=m;i++){
        int a,b,k;
        cin>>a>>b>>k;
        if (b>V)
            for (int j=1;j<=k;j++)
                merge(a+b*j-b,a+b*j);
        else f[b][a]=max(f[b][a],a+b*k);
    }
    for (int i=1;i<=V;i++){
        for (int j=1;j<=i;j++){
            int t=0;
            for (int x=j;x<=n;x+=i){
                if (t>=x) merge(x-i,x);
                t=max(t,f[i][x]);
            }
        }
    }
    int c=0;
    for (int i=1;i<=n;i++)
        if (find(i)==i) c++;
    printf("%d\n",c);
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
    cin>>t;
    init();
    while(t--){
        solve();
    }
}
```