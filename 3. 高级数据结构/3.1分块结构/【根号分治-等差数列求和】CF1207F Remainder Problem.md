# Remainder Problem

## 题面翻译

## 题目描述
给你一个长度为 $500000$ 的序列，初值为 $0$ ，你要完成 $q$ 次操作，操作有如下两种：
1. `1 x y` : 将下标为 $x$ 的位置的值加上 $y$
2. `2 x y` : 询问所有下标模 $x$ 的结果为 $y$ 的位置的值之和

## 输入格式
第一行一个整数 $q$ ，表示操作数。($q\leqslant500000$)  
接下来 $q$ 行，每行三个整数 $t,x,y$ 表示一次操作。($t\in\{1,2\}$)  
若 $t=1$ 则为第一种操作，保证：  
$1\leqslant x\leqslant500000,-1000\leqslant y\leqslant1000$  
若 $t=2$ 则为第二种操作，保证：  
$1\leqslant x\leqslant500000,0\leqslant y<x$  
数据保证至少有一个操作 $2$ 。

## 输出格式
每行对于每个操作 $2$ 输出一个整数表示答案。

## 题目描述

You are given an array $ a $ consisting of $ 500000 $ integers (numbered from $ 1 $ to $ 500000 $ ). Initially all elements of $ a $ are zero.

You have to process two types of queries to this array:

- $ 1 $ $ x $ $ y $ — increase $ a_x $ by $ y $ ;
- $ 2 $ $ x $ $ y $ — compute $ \sum\limits_{i \in R (x, y)} a_i $ , where $ R (x, y) $ is the set of all integers from $ 1 $ to $ 500000 $ which have remainder $ y $ modulo $ x $ .

Can you process all the queries?

## 输入格式

The first line contains one integer $ q $ ( $ 1 \le q \le 500000 $ ) — the number of queries.

Then $ q $ lines follow, each describing a query. The $ i $ -th line contains three integers $ t_i $ , $ x_i $ and $ y_i $ ( $ 1 \le t_i \le 2 $ ). If $ t_i = 1 $ , then it is a query of the first type, $ 1 \le x_i \le 500000 $ , and $ -1000 \le y_i \le 1000 $ . If $ t_i = 2 $ , then it it a query of the second type, $ 1 \le x_i \le 500000 $ , and $ 0 \le y_i < x_i $ .

It is guaranteed that there will be at least one query of type $ 2 $ .

## 输出格式

For each query of type $ 2 $ print one integer — the answer to it.

## 样例 #1

### 样例输入 #1

```
5
1 3 4
2 3 0
2 4 3
1 4 -4
2 1 0
```

### 样例输出 #1

```
4
4
0
```

## 题解
本题是我们关于我们的分块模板题的双倍经验，我们不讨论本题的对应的内容。

```
#include <bits/stdc++.h>
//#define int long long
#define endl '\n'
int INF = 0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int, int> PII;

void init() {
    // 初始化代码
}

const int N = 5000;
int f[N][N];
const int M = 500000 + 10;
int a[M];

void solve() {
    int m;
    cin >> m;
    int n = 500000;
    int S = (int)sqrt(n);

    for (int i = 1; i <= m; i++) {
        int c;
        cin >> c;
        if (c == 2) {
            int x, y;
            cin >> x >> y;
            if (x > S) {
                int sum = 0;
                for (int k = 0; k * x + y <= n; k++) {
                    sum += a[k * x + y];
                }
                cout << sum << endl;
            } else {
                cout << f[x][y] << endl;
            }
        } else {
            int x, y;
            cin >> x >> y;
            for (int i = 1; i <= S; i++) {
                f[i][x % i] += y;
            }
            a[x] += y;
        }
    }
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int t = 1;
    // cin >> t;
    init();
    while (t--) {
        solve();
    }
}
```