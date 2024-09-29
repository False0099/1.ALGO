# Naughty Stone Piles

## 题面翻译

在你的面前有 $n$ 堆石子从左往右排成一排，初始时每堆石子的大小（石子个数）依次为 $a_1, a_2, \ldots, a_n$。  

你需要将这些石子进行合并。  

每一步操作，你可以选择一堆石子并将这堆石子加入到另一堆石子中。如果你将第 $i$ 堆石子加入到第 $j$ 堆石子中，则第 $j$ 堆石子的大小将会增加第 $i$ 堆石子的大小，同时第 $i$ 堆石子将会消失 $\Rightarrow$ 我们将这样一步操作称为：将第 $i$ 堆石子合并到第 $j$ 堆石子中，其对应的代价为合并前第 $i$ 堆石子的大小。  

你的任务是确定将所有石子合并成一堆所需的最小代价。  

但是本题中有一个限制：对于任意一堆石子，你将其它石子合并到这堆石子的次数不能超过 $k$ 次。  

有 $q$ 次询问，每次询问都会给出一个整数 $k$，你需要根据 $k$ 的值确定将 $n$ 堆石子合并成一堆的最小总代价（**注：可能存在几次询问的 $k$ 相同**）。

## 题目描述

There are $ n $ piles of stones of sizes $ a_{1}, a_{2},..., a_{n} $ lying on the table in front of you.

During one move you can take one pile and add it to the other. As you add pile $ i $ to pile $ j $ , the size of pile $ j $ increases by the current size of pile $ i $ , and pile $ i $ stops existing. The cost of the adding operation equals the size of the added pile.

Your task is to determine the minimum cost at which you can gather all stones in one pile.

To add some challenge, the stone piles built up conspiracy and decided that each pile will let you add to it not more than $ k $ times (after that it can only be added to another pile).

Moreover, the piles decided to puzzle you completely and told you $ q $ variants (not necessarily distinct) of what $ k $ might equal.

Your task is to find the minimum cost for each of $ q $ variants.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=10^{5}) $ — the number of stone piles. The second line contains $ n $ space-separated integers: $ a_{1}, a_{2},..., a_{n} $ $ (1<=a_{i}<=10^{9}) $ — the initial sizes of the stone piles.

The third line contains integer $ q $ $ (1<=q<=10^{5}) $ — the number of queries. The last line contains $ q $ space-separated integers $ k_{1}, k_{2},..., k_{q} $ $ (1<=k_{i}<=10^{5}) $ — the values of number $ k $ for distinct queries. Note that numbers $ k_{i} $ can repeat.

## 输出格式

Print $ q $ whitespace-separated integers — the answers to the queries in the order, in which the queries are given in the input.

Please, do not use the %lld specifier to read or write 64-bit integers in C++. It is preferred to use the cin, cout streams or the %I 64 d specifier.

## 样例 #1

### 样例输入 #1

```
5
2 3 4 1 1
2
2 3
```

### 样例输出 #1

```
9 8
```

## 提示

In the first sample one way to get the optimal answer goes like this: we add in turns the $ 4 $ -th and the $ 5 $ -th piles to the $ 2 $ -nd one; then we add the $ 1 $ -st pile to the $ 3 $ -rd one; we add the $ 2 $ -nd pile to the $ 3 $ -rd one. The first two operations cost $ 1 $ each; the third one costs $ 2 $ , the fourth one costs $ 5 $ (the size of the $ 2 $ -nd pile after the first two operations is not $ 3 $ , it already is $ 5 $ ).

In the second sample you can add the $ 2 $ -nd pile to the $ 3 $ -rd one (the operations costs $ 3 $ ); then the $ 1 $ -st one to the $ 3 $ -th one (the cost is $ 2 $ ); then the $ 5 $ -th one to the $ 4 $ -th one (the costs is $ 1 $ ); and at last, the $ 4 $ -th one to the $ 3 $ -rd one (the cost is $ 2 $ ).

## 题解
本题，我们显然可以看出来，我们是一个石子合并问题。而对于我们的狮子合并，我们的一种思路是：**通过将我们的石子合并问题等价于我们的最优二叉树搜索**。也就是找到我们的一个最佳的哈夫曼树。

我们于是考虑将我们的**合并限制等价转换到我们的树的限制**，我们发现，我们一个石子合并不超过 K 次，就可以等价于我们的一个**树上的儿子数不超过 K**。

假如不限制每个点的合并次数，显然最优解应该是把所有点往最大点上合并。于是我们找到了这道题的一个结论，即**一个点对答案的贡献次数是它以及它所在集合被合并的次数**。而合并的过程又非常像一个树形结构（儿子们向父亲合并，然后被父亲带着去合并祖先），于是我们可以转化一下题意：有一些点，希望用这些点组成一棵树，限制每个点儿子数量的最大值，希望最小化所有点的点权乘深度之和（毕竟深度就是它被合并，也就是贡献的次数）。

这棵树是完全（套用完全二叉树的概念）的时候显然是最优的，然后考虑如何安排点权，由于每个点的贡献只和深度有关，而且一个点往上走只会单纯的导致一个点落下来，所以问题就可以贪心的来做了，即把权值大的点尽量往上安排即可。

```
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
void solve(){
    int n;
    cin>>n;
    vector<int> a(n+1);
    vector<int> sum(n+1);
    vector<int> ans(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];
    } 
    sort(begin(a)+1,end(a),[&](int a,int b){
        return a>b;
    });
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+a[i];
    }
    auto calc=[&](int i){
        int l_range=1;
        ans[i]=0;
        for(int depth=1;;depth++){
            int r_range=pow(i,depth)+l_range;
            cerr<<l_range<<" "<<r_range<<" "<<(sum[min(r_range,n)]-sum[l_range])*depth<<endl;
            ans[i]+=(sum[min(r_range,n)]-sum[l_range])*depth;
            if(r_range>=n){
                break;
            }
            l_range=r_range;
        }
        cerr<<endl;
    };
    for(int i=1;i<=n;i++){
        calc(i);
    }
    int q;
    cin>>q;
    while(q--){
        int a;
        cin>>a;
        a=min(a,n);
        cout<<ans[a]<<" ";
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
