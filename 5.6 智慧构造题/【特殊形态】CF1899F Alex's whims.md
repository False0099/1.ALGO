# Alex's whims

## 题目描述

Tree is a connected graph without cycles. It can be shown that any tree of $ n $ vertices has exactly $ n - 1 $ edges.

Leaf is a vertex in the tree with exactly one edge connected to it.

Distance between two vertices $u$ and $v$ in a tree is the minimum number of edges that must be passed to come from vertex $ u $ to vertex $ v $ .

Alex's birthday is coming up, and Timofey would like to gift him a tree of $n$ vertices. However, Alex is a very moody boy. Every day for $q$ days, he will choose an integer, denoted by the integer chosen on the $i$ -th day by $d_i$ . If on the $i$ -th day there are not two leaves in the tree at a distance exactly $d_i$ , Alex will be disappointed.

Timofey decides to gift Alex a designer so that he can change his tree as he wants. Timofey knows that Alex is also lazy (a disaster, not a human being), so at the beginning of every day, he can perform no more than one operation of the following kind:

- Choose vertices $u$ , $v_1$ , and $v_2$ such that there is an edge between $u$ and $v_1$ and no edge between $u$ and $v_2$ . Then remove the edge between $u$ and $v_1$ and add an edge between $u$ and $v_2$ . This operation cannot be performed if the graph is no longer a tree after it.

Somehow Timofey managed to find out all the $d_i$ . After that, he had another brilliant idea — just in case, make an instruction manual for the set, one that Alex wouldn't be disappointed.

Timofey is not as lazy as Alex, but when he saw the integer $n$ , he quickly lost the desire to develop the instruction and the original tree, so he assigned this task to you. It can be shown that a tree and a sequence of operations satisfying the described conditions always exist.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1899F/35aefc75de29a9e6379531b047a78067538fbc66.png)

Here is an example of an operation where vertices were selected: $ u $ — $ 6 $ , $ v_1 $ — $ 1 $ , $ v_2 $ — $ 4 $ .

## 输入格式

The first line contains the integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ ( $ 3 \leq n \leq 500 $ ) and $ q $ ( $ 1 \leq q \leq 500 $ ) — the number of nodes in the tree and the number of days, respectively.

The $ i $ th of the following $ q $ lines contains the integer $ d_i $ ( $ 2 \leq d_i \leq n - 1 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 500 $ . The same is guaranteed for $ q $ .

It can be shown that a tree and a sequence of operations satisfying the described conditions always exist.

## 输出格式

For each test case, first print an $ n - 1 $ string describing the edges of the tree. If you want the tree to have an edge between nodes $ u $ and $ v $ , there must be a string $ v $ $ u $ or $ u $ $ v $ among these $ n - 1 $ lines.

In the next $ q $ lines, print three integers each $ u $ $ v_1 $ $ v_2 $ — a description of the operations. If Alex doesn't need to perform an operation the following day, print $ -1 $ $ -1 $ $ -1 $ .

## 样例 #1

### 样例输入 #1

```
3
3 3
2
2
2
5 6
4
2
3
4
3
2
4 9
2
3
3
2
2
2
3
2
2
```

### 样例输出 #1

```
1 2
2 3
-1 -1 -1
-1 -1 -1
-1 -1 -1
1 2
2 3
3 4
4 5
-1 -1 -1
4 3 2
5 4 3
4 2 5
4 5 2
5 3 4
1 2
2 3
3 4
4 3 2
4 2 3
-1 -1 -1
4 3 2
-1 -1 -1
-1 -1 -1
4 2 3
4 3 2
-1 -1 -1
```

## 题解
我们本题的题意为：要求你构造一棵树，并且要求我们指定的两个结点之间的距离是一个给定的值 $d_{i}$,这里我们可以通过我们的特殊构造：即构造我们的树退化为一条链，然后我们每一次到原始点的距离为 d，就直接把这个点和我们的 d 号点相连，距离就一定是 d 了，注意，如果我们已经在那个点了，我们就输出-1，-1，-1 即可

而我们本题的构造思路也很简单，我们把我们的 $n$ 看作是一个插件，我们每一次需要嗯行我们距离为多少的点，我们就放到哪一个对应的结点后面，这样构造一定可以满足我们的条件。而我们找到的对应的组合也一定就是我们的 $(1,n)$ 这一个点对满足我们的条件。

而我们怎么样想到这个条件，

```cpp
#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <vector>
typedef long long ll;
typedef long double ld;
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n, q;
        cin >> n >> q;
        vector<int> d(q);
        for (int i = 0; i < q; i++) cin >> d[i];
        set<pair<int, int> > tr;
        for (int i = 0; i < n - 1; i++) tr.insert({ i, i + 1 });

        for (pair<int, int> p : tr) cout << p.first + 1 << " " << p.second + 1 << "\n";

        for (int i = 0; i < q; i++)
        {
            int u = n - 1;
            int v1 = -1;
            for (pair<int, int> p : tr) if (p.second == u)
            {
                v1 = p.first;
            }
            int v2 = d[i] - 1;
            if (v1 == v2) cout << "-1 -1 -1\n";
            else
            {
                cout << u + 1 << " " << v1 + 1 << " " << v2 + 1 << "\n";
                tr.erase({ v1, u });
                tr.insert({ v2, u });
            }
        }
    }
    return 0;
}
```