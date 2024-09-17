# [ABC 170 E] Smart Infants

## 题面翻译

有 $N$ 婴儿注册了 AtCoder，编号为 $1\sim N$，另有 $2\times10^5$ 个幼儿园，编号为 $1\sim 2\times10^5$。编号为 $i$ 的婴儿 Rating 为 $A_i$，最初位于 $B_i$ 号幼儿园。  

进行 $Q$ 次操作，第 $j$ 次操作后 $C_j$ 号婴儿会转到 $D_j$ 号幼儿园。

定义“均衡值”为：找出每个幼儿园中 Rating 最高的婴儿，他们中最低的 Rating 为“均衡值”。  

对于每次操作，求出操作后的“均衡值”。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc170/tasks/abc170_e

AtCoder に参加している幼児が $ N $ 人おり、$ 1 $ から $ N $ の番号が付けられています。また、幼稚園が $ 2\times\ 10^5 $ 校あり、$ 1 $ から $ 2\times\ 10^5 $ の番号が付けられています。幼児 $ i $ のレートは $ A_i $ であり、はじめ幼稚園 $ B_i $ に所属しています。

これから $ Q $ 回にわたって、転園が行われます。 $ j $ 回目の転園では、幼児 $ C_j $ の所属を幼稚園 $ D_j $ に変更します。

ここで、「平等さ」を、AtCoderに参加している幼児が一人以上いるような幼稚園それぞれについて園内で最もレートの高い幼児のレートを求め、その最小値として得られる値とします。

$ Q $ 回それぞれの転園後の平等さを求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ Q $ $ A_1 $ $ B_1 $ $ A_2 $ $ B_2 $ $ : $ $ A_N $ $ B_N $ $ C_1 $ $ D_1 $ $ C_2 $ $ D_2 $ $ : $ $ C_Q $ $ D_Q $

## 输出格式

$ Q $ 行出力せよ。 $ j $ 行目には、$ j $ 回目の転園の後の平等さを出力せよ。

## 样例 #1

### 样例输入 #1

```
6 3
8 1
6 2
9 3
1 1
2 2
1 3
4 3
2 1
1 2
```

### 样例输出 #1

```
6
2
6
```

## 样例 #2

### 样例输入 #2

```
2 2
4208 1234
3056 5678
1 2020
2 2020
```

### 样例输出 #2

```
3056
4208
```

## 提示

### 制約

- $ 1\ \leq\ N, Q\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- $ 1\ \leq\ C_j\ \leq\ N $
- $ 1\ \leq\ B_i, D_j\ \leq\ 2\ \times\ 10^5 $
- 入力はすべて整数である。
- $ j $ 回目の転園の前後で幼児 $ C_j $ の所属は異なる。

### Sample Explanation 1

はじめ、幼稚園 $ 1 $ には幼児 $ 1,\ 4 $、幼稚園 $ 2 $ には幼児 $ 2,\ 5 $、幼稚園 $ 3 $ には幼児 $ 3,\ 6 $ が所属しています。 $ 1 $ 回目の転園で幼児 $ 4 $ の所属を幼稚園 $ 3 $ に変更すると、幼稚園 $ 1 $ には幼児 $ 1 $、幼稚園 $ 2 $ には幼児 $ 2,\ 5 $、幼稚園 $ 3 $ には幼児 $ 3,\ 4,\ 6 $ が所属している状態になります。幼稚園 $ 1 $ で最もレートの高い幼児のレートは $ 8 $、幼稚園 $ 2 $ では $ 6 $、幼稚園 $ 3 $ では $ 9 $ です。これらの最小値は $ 6 $ であるので、$ 1 $ 行目には $ 6 $ を出力します。 $ 2 $ 回目の転園で $ 2 $ 番目の幼児の所属を幼稚園 $ 1 $ に変更すると、幼稚園 $ 1 $ には幼児 $ 1,\ 2 $、幼稚園 $ 2 $ には幼児 $ 5 $、幼稚園 $ 3 $ には幼児 $ 3,\ 4,\ 6 $ が所属している状態になります。幼稚園 $ 1 $ で最もレートの高い幼児のレートは $ 8 $、幼稚園 $ 2 $ では $ 2 $、幼稚園 $ 3 $ では $ 9 $ です。これらの最小値は $ 2 $ であるので、$ 2 $ 行目には $ 2 $ を出力します。 $ 3 $ 回目の転園で $ 1 $ 番目の幼児の所属を幼稚園 $ 2 $ に変更すると、幼稚園 $ 1 $ には幼児 $ 2 $、幼稚園 $ 2 $ には幼児 $ 1,\ 5 $、幼稚園 $ 3 $ には幼児 $ 3,\ 4,\ 6 $ が所属している状態になります。幼稚園 $ 1 $ で最もレートの高い幼児のレートは $ 6 $、幼稚園 $ 2 $ では $ 8 $、幼稚園 $ 3 $ では $ 9 $ です。これらの最小値は $ 6 $ であるので、$ 3 $ 行目には $ 6 $ を出力します。

## 题解
本题，我们可以通过我们的 multiset 来维护下面的几个内容：
1. 我们的每一个幼儿园内有哪些东西
2. 我们的最终的每一个幼儿园的最大值是多少，
之后，我们就是简单的维护即可，我们的代码如下所示：
```
```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;

void init() {
    // 任何初始化操作可以在这里添加
}

const int N = 2e5 + 10;
multiset<int> numbers_of_all[N];
multiset<int> best_of_all;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<PII> kids(n + 1);
    
    // 初始化孩子信息和对应幼儿园的集合
    for (int i = 1; i <= n; i++) {
        cin >> kids[i].first >> kids[i].second;
        numbers_of_all[kids[i].second].insert(kids[i].first);
    }
    
    // 记录每个幼儿园中最大的元素
    for (int i = 1; i < N; i++) {
        if (!numbers_of_all[i].empty()) {
            best_of_all.insert(*numbers_of_all[i].rbegin());
        }
    }
    
    while (q--) {
        int id, target;
        cin >> id >> target;
        int id_of_kinder = kids[id].second;

        // 删除原本的幼儿园最大值的贡献
        if (!numbers_of_all[id_of_kinder].empty()) {
            best_of_all.erase(best_of_all.find(*numbers_of_all[id_of_kinder].rbegin()));
        }
        
        // 如果目标幼儿园非空，删除目标幼儿园当前最大值的贡献
        if (!numbers_of_all[target].empty()) {
            best_of_all.erase(best_of_all.find(*numbers_of_all[target].rbegin()));
        }

        // 修改孩子的幼儿园
        numbers_of_all[id_of_kinder].erase(numbers_of_all[id_of_kinder].find(kids[id].first));
        numbers_of_all[target].insert(kids[id].first);
        kids[id].second = target;
        
        // 重新插入原幼儿园和目标幼儿园的最大值
        if (!numbers_of_all[id_of_kinder].empty()) {
            best_of_all.insert(*numbers_of_all[id_of_kinder].rbegin());
        }
        best_of_all.insert(*numbers_of_all[target].rbegin());
        
        // 输出当前的最小的最大值
        cout << *best_of_all.begin() << endl;
    }
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int t = 1;
    //cin >> t;
    init();
    while (t--) {
        solve();
    }
}
```
```