# [USACO 23 DEC] Minimum Longest Trip G

## 题目描述

Bessie 正在奶牛大陆上旅行。奶牛大陆由从 $1$ 到 $N$ 编号的 $N$（$2 \le N \le 2\cdot 10^5$）座城市和 $M$（$1 \le M \le 4\cdot 10^5$）条单向道路组成。第 $i$ 条路从城市 $a_i$ 通向城市 $b_i$，标签为 $l_i$。

由城市 $x_0$ 开始的长度为 $k$ 的旅程被定义为一个城市序列 $x_0,x_1,\ldots,x_k$，对于所有的 $0 \le i < k$，存在由城市 $x_i$ 到 $x_{i+1}$ 的路。保证在奶牛大路上不存在长度无限的旅程，不存在两条路连接一对相同的城市。

对于每座城市，Bessie 想知道从它开始的最长旅程。对于一些城市，从它们开始的最长旅程不唯一，Bessie 将选择其中道路标签序列字典序更小的旅程。一个序列比等长的另一个序列字典序更小，当且仅当在它们不同的第一个位置，前者比后者的元素更小。

输出 Bessie 在每座城市选择的旅途的长度和道路标签之和。

## 输入格式

第一行包含 $N$ 和 $M$。

接下来 $M$ 行，每行三个整数 $a_i,b_i,l_i$，代表一条由 $a_i$ 到 $b_i$，标签为 $l_i$ 的单向道路。

## 输出格式

输出 $N$ 行，第 $i$ 行包含由空格分隔的两个整数，表示 Bessie 选择的从城市 $i$ 开始的旅程的长度和道路标签之和。

## 样例 #1

### 样例输入 #1

```
4 5
4 3 10
4 2 10
3 1 10
2 1 10
4 1 10
```

### 样例输出 #1

```
0 0
1 10
1 10
2 20
```

## 样例 #2

### 样例输入 #2

```
4 5
4 3 4
4 2 2
3 1 5
2 1 10
4 1 1
```

### 样例输出 #2

```
0 0
1 10
1 5
2 12
```

## 样例 #3

### 样例输入 #3

```
4 5
4 3 2
4 2 2
3 1 5
2 1 10
4 1 1
```

### 样例输出 #3

```
0 0
1 10
1 5
2 7
```

## 样例 #4

### 样例输入 #4

```
4 5
4 3 2
4 2 2
3 1 10
2 1 5
4 1 1
```

### 样例输出 #4

```
0 0
1 5
1 10
2 7
```

## 提示

### 样例解释 2

在下面的解释中，我们用 $a_i\xrightarrow{l_i} b_i$ 表示由城市 $a_i$ 通往 $b_i$，标签为 $l_i$ 的单向道路。

从城市 $4$ 出发有多条旅程，包含 $4\xrightarrow{4} 3\xrightarrow 5 1$，$4\xrightarrow 1 1$ 和 $4\xrightarrow 2 2\xrightarrow{10} 1$。在这些旅程中，$4\xrightarrow{4} 3\xrightarrow 5 1$ 和 $4\xrightarrow 2 2\xrightarrow{10} 1$ 是最长的。它们的长度均为 $2$，道路标签序列分别为 $[4,5]$ 和 $[2,10]$。$[2,10]$ 是字典序更小的那一个，它的和为 $12$。

### 测试点性质

- 测试点 $5-6$ 满足所有道路的标签相同。
- 测试点 $7-8$ 满足所有道路的标签不相同。
- 测试点 $9-10$ 满足 $N,M \le 5000$。
- 测试点 $11-20$ 没有额外限制。

## 题解
我们本题就是给定你一个有向无环图，要你求出它的最长路径是多少。并要求求出我们路径上的所有边标签的和是多少。
很显然，我们这一题可以通过我们的拓扑排序来进行我们的路径选择。对于每一个结点，我们只需要维护：
1. 我们从哪一个边转移过来
2. 我们从转移到这个点的道路标签是多少
3. 我们的字典序怎么样。

在这里，我们的一大困难是求出我们的字典序最小的路是多少。这里，我们有两种方法，一种是字典序比较的常见思路：lcp+哈希，这种思路的原因是，我们的原来的序列中不能存储我们的字符串，因为我们的字符串比较的时间复杂度是 $o(n)$ 的, 我们考虑采用我们的哈希+lcp 来优化我们字符串比较的时间复杂度

第二种方法比较巧妙：
考虑对出度为 0 的点优先做拓扑排序。对一个点 $u$ 考虑其后继 $v_i$, 若 $v_i$ 深度大于 $v_j$ 则显然前者更优，若深度一致，则所连边的权重较小者更优。若权重一样，则需考虑 $v_i$ 和 $v_j$ 分别的后继为多少。
 这种情况下不可按照后继依次比较，否则会超时。考虑对那些深度为 $k$ 的点进行排名。排名依据依次为

(最优后继边权重，最优后继边排名)(也就是说，深度为 $k$ 的所有点的排名依赖于深度为 $k-1$ 的点的排名)。那么深度一致的后继点，可以直接选择排名靠前的点。
![[Pasted image 20240320122333.png]]

因此，我们本题的关键就在于，怎么对于我们每一个深度为 $dep$ 的元素，快速的求出它所对应的排名是多少。这里，沃恩的方法是，直接采用暴力 sort，

```cpp
#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

typedef long long ll;
const int N = 2e5 + 10;
const int M = 4e5 + 10;
vector<int> e[N];
vector<int> own[N];
vector<int> w[N];

int dep[N];
int out[N];
int nxt[N], ansl[N], rnk[N];
ll sum[N];
int ids[N];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v, l;
        scanf("%d%d%d", &u, &v, &l);
        e[u].push_back(v);
        w[u].push_back(l);
        own[v].push_back(u);
        out[u]++;
    }
    vector<int> cur_len_nodes;
    vector<int> nxt_len_nodes;
    for (int i = 1; i <= n; i++) {
        if (!out[i]) {
            dep[i] = 1;
            cur_len_nodes.push_back(i);
            sum[i] = 0;
        }
    }
    int cur_len = 1;
    while (!cur_len_nodes.empty()) {
        // 获取长度为 1 的路径...
        ++cur_len;
        for (int v: cur_len_nodes) {
            for (int u: own[v]) {
                if (--out[u] == 0) {
                    nxt_len_nodes.push_back(u);
                    dep[u] = cur_len;
                    ansl[u] = 1e9 + 7;
                }
            }
        }
        for (int u: nxt_len_nodes) {
            for (int i = 0; i < e[u].size(); i++) {
                int v = e[u][i];
                int l = w[u][i];
                if (dep[v] == cur_len - 1) {
                    if (l < ansl[u]) {
                        ansl[u] = l;
                        nxt[u] = v;
                        sum[u] = sum[v] + l;
                    } else if (l == ansl[u] && rnk[v] < rnk[nxt[u]]) {
                        // rnk 针对同级
                        nxt[u] = v;
                        sum[u] = sum[v] + l;
                    }
                }
            }
        }
        int cnt = 0;
        for (int u: nxt_len_nodes) {
            ids[++cnt] = u;
        }
        sort(ids + 1, ids + cnt + 1, [&](const int& a, const int& b) {
            if (ansl[a] != ansl[b])
                return ansl[a] < ansl[b];
            return rnk[nxt[a]] < rnk[nxt[b]];
        });
        for (int i = 1; i <= cnt; i++) {
            rnk[ids[i]] = i;
        }
        swap(cur_len_nodes, nxt_len_nodes);
        nxt_len_nodes.clear();
        // 稍后计算 rnk
    }
    for (int i = 1; i <= n; i++) {
        printf("%d %lld\n", dep[i] - 1, sum[i]);
    }
    return 0;
}

```



