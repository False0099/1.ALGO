## Description

给定一个 n 个点 n 条边的无向图，你需要求有多少种选择图上的一个点 p 和一条边 (x, y) 的方案，使得删去 (x, y) 后图变成一棵树，且这棵树以 p 为根时每个节点的儿子个数均不超过 3。**保证至少存在一种这样的方案。**

## Input

输入的第一行一个整数 n（2≤n≤105） 表示节点数，接下来 n 行每行两个整数 a, b（1≤a, b≤n） 描述图上的一条边。保证图中没有重边自环。

## Output

输出一行一个正整数表示答案。

## Sample

#### #0

#### **Input**

Copy

6
1 2
1 3
1 4
1 5
1 6
2 3

#### **Output**

Copy

10

## Hint

**【样例解释 # 0】**

删除 (1,2) 或者 (1,3)，并在 2,3,4,5,6 中选择一个节点作为根，可以得到所有的合法方案。因此输出为 2×5=10。

## Source

[第九届中国大学生程序设计竞赛（深圳）-（CCPC2023-Shenzhen）](https://cpc.csgrandeur.cn/csgoj/problemset#search=%E7%AC%AC%E4%B9%9D%E5%B1%8A%E4%B8%AD%E5%9B%BD%E5%A4%A7%E5%AD%A6%E7%94%9F%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%E7%AB%9E%E8%B5%9B%EF%BC%88%E6%B7%B1%E5%9C%B3%EF%BC%89-%EF%BC%88CCPC2023-Shenzhen%EF%BC%89)

## Author

THU

## 题解
我们这一题需要我们先推导出我们的结论：我们先找到我们的环，然后把环上的边删除，删除之后我们再枚举我们度小于 4 的点是哪些，这些点一定可以做我们的根，那么我们只需要统计我们的满足我们的环上度小于 4 的点有哪些，然后对应的边都可以删。
```cpp
#include "bits/stdc++.h"

using namespace std;
using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<pair<int, int>>> g(n);
    vector<pair<int, int>> e(n);
    vector<int> deg(n);

    for (int i = 0; i < n; i++) {
        auto &[u, v] = e[i];
        cin >> u >> v;

        u--, v--;
        g[u].push_back({v, i});
        g[v].push_back({u, i});
        deg[u]++, deg[v]++;
    }

    vector<int> dfn(n, -1), low(n, -1), ban(n);

    int tot = 0;
    function<void(int, int)> tarjan = [&](int cur, int pre) {
        dfn[cur] = low[cur] = tot++;
        for (auto &[nex, j] : g[cur]) {
            if (nex != pre) {
                if (dfn[nex] == -1) {
                    tarjan(nex, cur);
                    low[cur] = min(low[cur], low[nex]);
                    if (low[nex] > dfn[cur]) {
                        ban[j] = 1;//找到环
                    }
                } else {
                    low[cur] = min(low[cur], dfn[nex]);
                }
            }
        }
    };

    for (int i = 0; i < n; i++) {
        if (dfn[i] == -1) {
            tarjan(i, -1);
        }
    }

    int cnt0 = 0, cnt1 = 0;
    for (int i = 0; i < n; i++) {
        cnt0 += (deg[i] > 3);//
        cnt1 += (deg[i] > 4);//一定不能做根节点的点
    }

    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        if (!ban[i]) {//我们这个边是否在环上
            auto &[u, v] = e[i];
            cnt0 -= (deg[u] == 4) + (deg[v] == 4);//更新我们度数大于4的点
            cnt1 -= (deg[u] == 5) + (deg[v] == 5);//统计我们度数大于5的点
            if (cnt1 == 0) {//找是否存在度数大于5的，如果存在，那么我们一定不可行，否则，其他度数不为4的都可以做叶子节点。
                ans += n - cnt0;
            }
            cnt0 += (deg[u] == 4) + (deg[v] == 4);//保护现场
            cnt1 += (deg[u] == 5) + (deg[v] == 5);//保护现场
        }
    }
    cout << ans << '\n';
    
    return 0;
}
```