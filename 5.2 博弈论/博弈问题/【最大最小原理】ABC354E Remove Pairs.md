# [ABC 354 E] Remove Pairs

## 题面翻译

- Takahashi 和 Aoki 在玩公平组合游戏，Takahashi 先手。有 $n$ 张牌在桌面上，正面写 $a_i$ 反面写 $b_i$。每次玩家可以选择两张正面相同或反面相同的牌并拿走。输出最后的赢家。
- $1 \le n \le 18$，$1 \le a_i, b_i \le 10^9$。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc354/tasks/abc354_e

高橋君と青木君は $ N $ 枚のカードを使ってとあるゲームをします。$ i $ 枚目のカードの表面には $ A_i $ が、裏面には $ B_i $ が書かれています。初めに場には $ N $ 枚のカードが並べられており、高橋君を先手として、$ 2 $ 人は以下の操作を交互に繰り返します。

- 場にあるカードの中から表面同士に同じ数が書かれている、または裏面同士に同じ数が書かれている $ 2 $ 枚のカードの組を選び、そのカードを場から取り除く。このようなカードの組が存在しない場合、操作を行えない。
 
先に操作を行えなくなった方が負けとなり、もう一方が勝ちとなります。両者がそれぞれ勝つために最適な操作を選ぶ時、どちらが勝つか求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_1 $ $ B_1 $ $ A_2 $ $ B_2 $ $ \vdots $ $ A_N $ $ B_N $

## 输出格式

$ 2 $ 人とも最適に操作を行なったとき、高橋君が勝つ場合は `Takahashi` と、青木君が勝つ場合は `Aoki` と出力せよ。

## 样例 #1

### 样例输入 #1

```
5
1 9
2 5
4 9
1 4
2 5
```

### 样例输出 #1

```
Aoki
```

## 样例 #2

### 样例输入 #2

```
9
3 2
1 7
4 1
1 8
5 2
9 8
2 1
6 8
5 2
```

### 样例输出 #2

```
Takahashi
```

## 提示

### 制約

- $ 1\ \leq\ N\ \leq\ 18 $
- $ 1\ \leq\ A_i, B_i\ \leq\ 10^9 $
- 入力は全て整数である。
 
### Sample Explanation 1

髙橋君が最初に取り除いた $ 2 $ 枚が - $ 1 $ 枚目と $ 3 $ 枚目のカードだった場合: 青木君は $ 2 $ 枚目と $ 5 $ 枚目のカードを取り除くことで勝つことができる。 - $ 1 $ 枚目と $ 4 $ 枚目のカードだった場合: 青木君は $ 2 $ 枚目と $ 5 $ 枚目のカードを取り除くことで勝つことができる。 - $ 2 $ 枚目と $ 5 $ 枚目のカードだった場合: 青木君は $ 1 $ 枚目と $ 3 $ 枚目のカードを取り除くことで勝つことができる。髙橋君が最初の操作で取り除くことができるカードの組み合わせは以上の $ 3 $ 通りのみで、髙橋君がどのような操作を行っても青木君が勝つことができるため、青木君が答えとなります。

## 题解
本题，我们因为我们的数据范围很小很小，我们完全可以利用我们的最大最小原理加上我们的暴力 dfs 来进行处理，我们最后就能得到下面的答案：
```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF = 0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int, int> PII;

void init() {}

bool dfs(vector<PII>& cards_now, map<vector<PII>, bool>& memo) {
    if (memo.count(cards_now)) return memo[cards_now];
    memo[cards_now]=false;
    vector<pair<int, int>> match_indices;
    for (int i = 0; i < cards_now.size(); i++) {
        for (int j = i + 1; j < cards_now.size(); j++) {
            if (cards_now[i].first == cards_now[j].first||cards_now[i].second==cards_now[j].second) {
                match_indices.push_back({i, j});
            }
        }
    }
    
    if (match_indices.empty()) {
        return memo[cards_now] = false;
    }

    for (auto [id1, id2] : match_indices) {
        vector<PII> next_state;
        for (int i = 0; i < cards_now.size(); i++) {
            if (i != id1 && i != id2) {
                next_state.push_back(cards_now[i]);
            }
        }
        if (!dfs(next_state, memo)) {
            return memo[cards_now] = true;
        }
    }
    
    return memo[cards_now];
}

void solve() {
    int n;
    cin >> n;
    vector<PII> cards(n);
    for (int i = 0; i < n; i++) {
        cin >> cards[i].first >> cards[i].second;
    }
    
    map<vector<PII>, bool> memo;
    bool result = dfs(cards, memo);
    cout << (result ? "Takahashi" : "Aoki") << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    init();
    while (t--) {
        solve();
    }
}
```