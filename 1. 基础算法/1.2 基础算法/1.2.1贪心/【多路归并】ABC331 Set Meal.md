# [ABC 331 E] Set Meal

## 题面翻译

AtCoder 餐厅里有 $N$ 种主食和 $M$ 种配菜。\
第 $i$ 种主食卖 $A_i$ 元，第 $i$ 种配菜卖 $B_i$ 元。\
你想买一种主食和一种配菜，但是有 $L$ 种搭配 $(c_i,d_i)$ 你不喜欢，请问你喜欢的搭配中最贵的要花多少钱。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc331/tasks/abc331_e

AtCoder 食堂では主菜と副菜からなる定食が販売されています。  
 主菜は $ N $ 種類あり、順に主菜 $ 1 $, 主菜 $ 2 $, $ \dots $, 主菜 $ N $ と呼びます。主菜 $ i $ の価格は $ a_i $ 円です。  
 副菜は $ M $ 種類あり、順に副菜 $ 1 $, 副菜 $ 2 $, $ \dots $, 副菜 $ M $ と呼びます。副菜 $ i $ の価格は $ b_i $ 円です。

定食は主菜と副菜を $ 1 $ 種類ずつ選んで構成されます。定食の価格は選んだ主菜の価格と副菜の価格の和です。   
 ただし、$ L $ 個の相異なる組 $ (c_1,\ d_1),\ \dots,\ (c_L,\ d_L) $ について、主菜 $ c_i $ と副菜 $ d_i $ からなる定食は食べ合わせが悪いため提供されていません。  
 つまり、提供されている定食は $ NM\ -\ L $ 種類あることになります。(提供されている定食が少なくとも $ 1 $ 種類存在することが制約によって保証されています。)

提供されている定食のうち、最も価格の高い定食の価格を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ M $ $ L $ $ a_1 $ $ a_2 $ $ \dots $ $ a_N $ $ b_1 $ $ b_2 $ $ \dots $ $ b_M $ $ c_1 $ $ d_1 $ $ c_2 $ $ d_2 $ $ \vdots $ $ c_L $ $ d_L $

## 输出格式

提供されている定食のうち、最も価格の高い定食が何円であるかを出力せよ。

## 样例 #1

### 样例输入 #1

```
2 3 3
2 1
10 30 20
1 2
2 1
2 3
```

### 样例输出 #1

```
31
```

## 样例 #2

### 样例输入 #2

```
2 1 0
1000000000 1
1000000000
```

### 样例输出 #2

```
2000000000
```

## 样例 #3

### 样例输入 #3

```
10 10 10
47718 21994 74148 76721 98917 73766 29598 59035 69293 29127
7017 46004 16086 62644 74928 57404 32168 45794 19493 71590
1 3
2 6
4 5
5 4
5 5
5 6
5 7
5 8
5 10
7 3
```

### 样例输出 #3

```
149076
```

## 提示

### 制約

- $1\ \leq\ N,\ M\ \leq\ 10^5$
- $0\ \leq\ L\ \leq\ \min (10^5,\ N\ M\ -\ 1)$
- $1\ \leq\ a_i,\ b_i\ \leq\ 10^9$
- $1\ \leq\ c_i\ \leq\ N$
- $1\ \leq\ d_j\ \leq\ M$
- $i\ \neq\ j$ ならば $(c_i,\ d_i)\ \neq\ (c_j,\ d_j)$
- 入力される値は全て整数
 
### Sample Explanation 1

提供されている定食、及びその価格は次の $ 3 $ 種類です。 - 主菜 $ 1 $ と副菜 $ 1 $ からなる定食。価格は $ 2\ +\ 10\ =\ 12 $ 円である。 - 主菜 $ 1 $ と副菜 $ 3 $ からなる定食。価格は $ 2\ +\ 20\ =\ 22 $ 円である。 - 主菜 $ 2 $ と副菜 $ 2 $ からなる定食。価格は $ 1\ +\ 30\ =\ 31 $ 円である。 この中で最も高い定食は $ 3 $ 番目の定食です。よって $ 31 $ を出力してください。

## 题解
我们考虑使用一个 $o(L)$ 的算法，我们考虑求出我们配对的前 $L$ 大元素，那么我们当中一定有一个是满足我们条件的元素。于是我们就可以考虑我们的多路归并问题。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>
using namespace std;
int main() {
  int N, M, L;
  cin >> N >> M >> L;
  vector<int> a(N), b(M);
  for (auto& x : a) cin >> x;
  for (auto& x : b) cin >> x;
  set<pair<int, int>> bad;
  for (int i = 0; i < L; i++) {
    int c, d;
    cin >> c >> d;
    bad.emplace(c - 1, d - 1);
  }

  vector<int> ord_b(M);
  for (int i = 0; i < M; i++) ord_b[i] = i;
  sort(begin(ord_b), end(ord_b), [&](int i, int j) { return b[i] > b[j]; });

  vector<int> cur(N);
  priority_queue<pair<int, int>> Q;
  for (int i = 0; i < N; i++) Q.emplace(a[i] + b[ord_b[cur[i]]], i);
  while (true) {
    auto [cost, i] = Q.top();
    int j = cur[i];
    Q.pop();
    if (bad.count({i, ord_b[j]}) == 0) {
      cout << cost << "\n";
      break;
    }
    cur[i]++;
    if (cur[i] != M) Q.emplace(a[i] + b[ord_b[cur[i]]], i);
  }
}

```