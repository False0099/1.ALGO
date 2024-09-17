Chaneka, a gamer kid, invented a new gaming controller called joyboard. Interestingly, the joyboard she invented can only be used to play one game. The joyboard has a screen containing $n+1$ slots numbered from $1$ to $n+1$ from left to right. The $n+1$ slots are going to be filled with an array of non-negative integers $[a_1,a_2,a_3,\ldots,a_{n+1}]$. Chaneka, as the player, must assign $a_{n+1}$ with an integer between $0$ and $m$ inclusive. Then, for each $i$ from $n$ to $1$, the value of $a_i$ will be equal to the **remainder** of dividing $a_{i+1}$ (the adjacent value to the right) by $i$. In other words, $a_i = a_{i + 1} \bmod i$. Chaneka wants it such that after every slot is assigned with an integer, there are exactly $k$ distinct values in the entire screen (among all $n+1$ slots). How many valid ways are there for assigning a non-negative integer into slot $n+1$?

**Input**

Each test contains multiple test cases. The first line contains an integer $t$ ($1 \leq t \leq 2\cdot10^4$) — the number of test cases. The following lines contain the description of each test case.

The only line of each test case contains three integers $n$, $m$, and $k$ ($1 \leq n \leq 10^9$; $0 \leq m \leq 10^9$; $1 \leq k \leq n+1$) — there are $n+1$ slots, the integer assigned in slot $n+1$ must not be bigger than $m$, and there should be exactly $k$ distinct values.

**Output**

For each test case, output a line containing an integer representing the number of valid ways for assigning a non-negative integer into slot $n+1$.

4
4 6 3
2 0 1
265 265 265
3 10 2

2
1
0
5

## 题解
我们本题因为只有两个参数，所以我们可以采用我们的打表方法，我们打表后找规律即可。
```cpp
```cpp
#include <bits/stdc++.h>
#define int long long
int n, m, k;
void solve() {
  std::cin >> n >> m >> k;
  std::vector<int> ans(n + 15);
  std::map<int, int> mp;
  for (int val = 0; val <= m; val++) {
    std::set<int> S;
    ans[n + 1] = val;
    for (int i = n; i >= 1; i--) {
      ans[i] = ans[i + 1] % i;
    }
    for (int i = 1; i <= n + 1; i++) {
      std::cerr << ans[i] << " ";
      S.insert(ans[i]);
    }
    mp[S.size()]++;
    std::cerr << "\n";
  }
  std::cout << mp[k] << "\n";
}

signed main() {
  int __;
  std::cin >> __;
  while (__--) solve();
  return 0;
}
```


我们的答案函数
```cpp
#include <bits/stdc++.h>
#define int long long
int n, m, k;
void solve() {
  std::cin >> n >> m >> k;
  if (n == m) {
    if (k == 1) {
      std::cout << "1\n";
    } else if (k == 2) {
      std::cout << n << "\n";
    } else if (k == 3) {
      std::cout << 0 << "\n";
    } else {
      std::cout << 0 << "\n";
    }
  } else if (n < m) {
    if (k == 1) {
      std::cout << "1\n";
    } else if (k == 2) {
      std::cout << n - 1 + m / n << "\n";
    } else if (k == 3) {
      std::cout << m - (n - 1 + m / n) << "\n";
    } else {
      std::cout << 0 << "\n";
    }
  } else {
    if (k == 1) {
      std::cout << "1\n";
    } else if (k == 2) {
      std::cout << m << "\n";
    } else if (k == 3) {
      std::cout << 0 << "\n";
    } else {
      std::cout << 0 << "\n";
    }
  }
}

signed main() {
  int __;
  std::cin >> __;
  while (__--) solve();
  return 0;
}
```