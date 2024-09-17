You are given a tree consisting of $n$ vertices. A number is written on each vertex; the number on vertex $i$ is equal to $a_i$.

You can perform the following operation any number of times (possibly zero):

-   choose a vertex which has **at most $1$** incident edge and remove this vertex from the tree.

Note that you can delete all vertices.

After all operations are done, you're compressing the tree. The compression process is done as follows. While there is a vertex having **exactly $2$** incident edges in the tree, perform the following operation:

-   delete this vertex, connect its neighbors with an edge.

It can be shown that if there are multiple ways to choose a vertex to delete during the compression process, the resulting tree is still the same.

Your task is to calculate the maximum possible sum of numbers written on vertices after applying the aforementioned operation any number of times, and then compressing the tree.

**Input**

The first line contains a single integer $t$ ($1 \le t \le 10^4$) — the number of test cases.

The first line of each test case contains a single integer $n$ ($2 \le n \le 5 \cdot 10^5$) — the number of vertices.

The second line contains $n$ integers $a_1, a_2, \dots, a_n$ ($-10^9 \le a_i \le 10^9$).

Each of the next $n - 1$ lines describes an edge of the tree. Edge $i$ is denoted by two integers $v_i$ and $u_i$, the labels of vertices it connects ($1 \le v_i, u_i \le n$, $v_i \ne u_i$). These edges form a tree.

Additional constraint on the input: the sum of $n$ over all test cases doesn't exceed $5 \cdot 10^5$.

**Output**

For each test case, print a single integer — the maximum possible sum of numbers written on vertices after applying the aforementioned operation any number of times, and then compressing the tree.

## 题解
我们想到，如果我们从一个结点向上延申，实际上只有它和它的子树的最大权值和是有用的，具体怎么延申实际上没什么用。所以，我们可以考虑用我们的树形 dp 来进行计算。

我们这里的 $dp[i]$ 记录的是我们的 $i$ 结点，**能给我们的父节点贡献最多多少的权值**。
第一种贡献法：是只选择这一个结点

第二种贡献法：我们选了这个结点，选了我们若干个子节点，这里，我们此时要把我们的 $a_{i}$ 添加到我们的权值中计算
![[无标题 20.png]]
这里，我们就需要我们的子树最大 dp 值的和来辅助我们进行计算。

第三种贡献法：我们保留了向上的一条链，并且我们的 $i$ 不是最终的端点，此时我们的 $a_{i}$ 不计入我们的 $dp[i]$,我们取 $i$ 子树的最大值
![[无标题 19.png]]

此时，我们还需要记录一个变量叫做 `result`，用于存储我们能够获得的最大结果是多少。那么我们就有下面的几种分类讨论：
1. 我们全为空=0
2. 我们只链接一个子树贡献：我们的答案就是当前权值加上最大子树贡献
3. 我们只保留我们的当前点
4. 我们只链接 2 个子树，并且我们要删除当前的点，我们直接返回我们的最大和次大子树
5. 我们链接多个子树，我们作为中间点加入贡献。
```cpp
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

void solve() {
    const long long int INF = 1e16;
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1;i <= n;++i) {
        cin >> a[i];
    }
    vector<vector<int>> tree(n + 1);
    for(int i = 1;i < n;++i) {
        int u, v;
        cin >> u >> v;
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
    }
    if (n == 1) {
        cout << max(0, a[1]) << "\n";
        return;
    }
    if (n == 2) {
        if (a[1] >= 0 && a[2] >= 0) {
            cout << a[1] + a[2] << "\n";
        } else if (a[1] < 0 && a[2] < 0) {
            cout << "0\n";
        } else {
            cout << max(a[1], a[2]) << "\n";
        }
        return;
    }
    vector<long long int> dp(n + 1, -INF);  // dp[i], i 子树有 >= 1 个节点, 此时 i 为根的子树, 最大的是多少
    long long int result = 0;  // 都不选
    // dp[u] 更新:
    // 1. 只有 u
    // 2. u 在链上, 此时 a[u] 不计入答案
    // 3. u 连两个及以上子树
    // result 更新
    // 1. 没有节点(初始化)
    // 2. 只有 u 节点
    // 3. 删掉 u 之上的, u 是根, 连一个子树
    // 4. u 连两个子树, u 被删掉
    // 5. u 连三个及以上子树, u 留着
    // 需要额外维护
    // 1. 最大值
    // 2. 次大值
    // 3. 第三大值
    // 4. >= 0 的 dp 之和
    function<void(int, int)> DFS = [&](int u, int f)->void {
        int m1 = 0;  // 子节点 dp 最大
        int m2 = 0;  // 子节点 dp 次大
        int m3 = 0;  // 子节点 dp 第三大
        long long int sum = 0;  // 子节点 >= 0 的 dp 之和
        // 只有 a[u] 一个
        dp[u] = max(dp[u], 1LL * a[u]);
        result = max(result, 1LL * a[u]);
        for(auto v : tree[u]) {
            if (v == f) {
                continue;
            }
            DFS(v, u);
            if (dp[v] > 0) {
                sum += dp[v];
            }
            if (m1 == 0 || dp[v] > dp[m1]) {
                m3 = m2;
                m2 = m1;
                m1 = v;
            } else if (m2 == 0 || dp[v] > dp[m2]) {
                m3 = m2;
                m2 = v;
            } else if (m3 == 0 || dp[v] > dp[m3]) {
                m3 = v;
            }
        }
        if (m1 == 0) {
            // 叶子节点
            return;
        }
        dp[u] = max(dp[u], dp[m1]);   // u 连链, 还要往上
        result = max(result, dp[m1] + a[u]);  // 删掉 u 以上的, u 变成了根, 连一个子树
        if (m2 == 0) {
            // 只是在链上
            return;
        }
        dp[u] = max(dp[u], dp[m1] + dp[m2] + a[u]);  // 连两个子树
        result = max(result, dp[m1] + dp[m2]);  // 连两个子树, a[u] 被删掉
        if (m3 == 0) {
            // 只连接了两个子树
            return;
        }
        if (dp[m2] >= 0) {
            // 要走全部 >= 0 的
            dp[u] = max(dp[u], sum + a[u]);
        }
        if (dp[m3] >= 0) {
            // 有三个 >= 0
            result = max(result, sum + a[u]);
        } else {
            // 不足三个 >= 0, 所有越少越好
            result = max(result, dp[m1] + dp[m2] + dp[m3] + a[u]);
        }
    };
    DFS(1, 0);
    cout << result << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
```
