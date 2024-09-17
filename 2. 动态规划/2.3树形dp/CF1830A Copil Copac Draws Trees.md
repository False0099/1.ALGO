# Copil Copac Draws Trees

## 题面翻译

Copil Copac 得到一个由 $n-1$ 条边，$n$ 个点组成的树，他决定用下面的算法来绘制它：

- 步骤 $0$：绘制第一个顶点（顶点 $1$）。进入步骤 $1$。
- 步骤 $1$：对于输入中的每一条边，依次绘制：如果这条边连接了一个已绘制的顶点 $u$ 和一个未绘制的顶点 $v$，则绘制未绘制的顶点 $v$ 和这条边。检查完每一条边后，进入步骤 $2$。
- 步骤 $2$：如果所有顶点都绘制完毕，则终止算法。否则，转到步骤 $1$。

**执行次数** 定义为 Copil Copac 执行步骤 $1$ 的次数。

请计算 Copil Copac 绘制这棵树所需的 **执行次数**。

## 题目描述

Copil Copac is given a list of $ n-1 $ edges describing a tree of $ n $ vertices. He decides to draw it using the following algorithm:

- Step $ 0 $ : Draws the first vertex (vertex $ 1 $ ). Go to step $ 1 $ .
- Step $ 1 $ : For every edge in the input, in order: if the edge connects an already drawn vertex $ u $ to an undrawn vertex $ v $ , he will draw the undrawn vertex $ v $ and the edge. After checking every edge, go to step $ 2 $ .
- Step $ 2 $ : If all the vertices are drawn, terminate the algorithm. Else, go to step $ 1 $ .

The number of readings is defined as the number of times Copil Copac performs step $ 1 $ .

Find the number of readings needed by Copil Copac to draw the tree.

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of vertices of the tree.

The following $ n - 1 $ lines of each test case contain two integers $ u_i $ and $ v_i $ ( $ 1 \le u_i, v_i \le n $ , $ u_i \neq v_i $ ) — indicating that $ (u_i, v_i) $ is the $ i $ -th edge in the list. It is guaranteed that the given edges form a tree.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the number of readings Copil Copac needs to draw the tree.

## 样例 #1

### 样例输入 #1

```
2
6
4 5
1 3
1 2
3 4
1 6
7
5 6
2 4
2 7
1 3
1 2
4 5
```

### 样例输出 #1

```
2
3
```

## 提示

In the first test case:

After the first reading, the tree will look like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1830A/96592d8d6a7376d06a499045a206685f9a68df31.png)After the second reading:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1830A/7b7bd2d2b1a9ad0d44021bb292052bd1a2395dfd.png)Therefore, Copil Copac needs $ 2 $ readings to draw the tree.

## 题解
我们在本题中，重要的是使用我们的并查集来协助我们进行模拟操作，之后我们每一次建边就正常的合并即可。最坏情况我们的时间复杂度 $o(n^2)$,一定会超时。

我们这一题考虑 dp，我们设 $dp[i]$ 为激活 i 结点所需要的扫描次数，$id[i]$  i 的边的下表

一开始，因为只有 1 处于激活状态，所以 $dp[1]=1$ , $id[1]=0$,如果我们从结点 1 开始执行我们的 dfs，当我们处理边时，可能会有下面两种情况：
1. 如果我们这一条边的下表在我们的 id 之后即 $index((u,v))\geq id[u]$，那么我们可以在与 u 相同的扫描中访问 v
$dp[v]=dp[u],id[v]=index[(u,v)]$

2. 如果我们有相反的，那么我们就有 $dp[v]=dp[u]+1,id[v]=index(u,v)$

我们最后的答案就是我们的 $max(dp[i])$


```cpp
    #include<bits/stdc++.h>
    
    using namespace std;
    const int NMAX = 2e5+5;
    int dp[NMAX], id[NMAX];
    vector<pair<int,int>> edg[NMAX];
    void dfs(int u){
        for(auto it : edg[u]){
            if(dp[it.first] == 0){
                dp[it.first] = dp[u] + (it.second <= id[u]);
                id[it.first] = it.second;
                dfs(it.first);
            }
        }
    }
    void tc(){
        int n;
        cin>>n;
        for(int i=1; i<=n; i++) dp[i] = id[i] = 0, edg[i].clear();
        for(int i=1; i<n; i++){
            int u,v;
            cin>>u>>v;
            edg[u].push_back({v,i});
            edg[v].push_back({u,i});
        }
        dp[1] = 1;
        dfs(1);
        int ans = 0;
        for(int i=1; i<=n; i++) ans=max(ans,dp[i]);
        cout<<ans<<'\n';
    }
    int main()
    {
        ios_base::sync_with_stdio(false);
        int t;
        cin>>t;
        while(t--)
            tc();
        return 0;
    }
```