# Vika and Price Tags

## 题面翻译

你有两个长度均为 $n(1 \le n \le 10^5)$ 的序列 $a,b(0 \le a_i,b_i \le 10^9)$，每一次操作令所有 $a_i = b_i,b_i = |a_i - b_i|$。问若干次操作后，是否能让所有的 $a_i$ 值都为 $0$。多测。

## 题目描述

Vika came to her favorite cosmetics store "Golden Pear". She noticed that the prices of $ n $ items have changed since her last visit.

She decided to analyze how much the prices have changed and calculated the difference between the old and new prices for each of the $ n $ items.

Vika enjoyed calculating the price differences and decided to continue this process.

Let the old prices be represented as an array of non-negative integers $ a $ , and the new prices as an array of non-negative integers $ b $ . Both arrays have the same length $ n $ .

In one operation, Vika constructs a new array $ c $ according to the following principle: $ c_i = |a_i - b_i| $ . Then, array $ c $ renamed into array $ b $ , and array $ b $ renamed into array $ a $ at the same time, after which Vika repeats the operation with them.

For example, if $ a = [1, 2, 3, 4, 5, 6, 7] $ ; $ b = [7, 6, 5, 4, 3, 2, 1] $ , then $ c = [6, 4, 2, 0, 2, 4, 6] $ . Then, $ a = [7, 6, 5, 4, 3, 2, 1] $ ; $ b = [6, 4, 2, 0, 2, 4, 6] $ .

Vika decided to call a pair of arrays $ a $ , $ b $ dull if after some number of such operations all elements of array $ a $ become zeros.

Output "YES" if the original pair of arrays is dull, and "NO" otherwise.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the number of items whose prices have changed.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10^9 $ ) — the old prices of the items.

The third line contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 0 \le b_i \le 10^9 $ ) — the new prices of the items.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output "YES" if the pair of price arrays is dull, and "NO" otherwise.

You can output each letter in any case (lowercase or uppercase). For example, the strings "yEs", "yes", "Yes", and "YES" will be accepted as a positive answer.

## 样例 #1

### 样例输入 #1

```
9
4
0 0 0 0
1 2 3 4
3
1 2 3
1 2 3
2
1 2
2 1
6
100 23 53 11 56 32
1245 31 12 6 6 6
7
1 2 3 4 5 6 7
7 6 5 4 3 2 1
3
4 0 2
4 0 2
3
2 5 2
1 3 4
2
6 1
4 2
2
0 0
0 3
```

### 样例输出 #1

```
YES
YES
NO
NO
YES
YES
NO
YES
YES
```

## 提示

In the first test case, the array $ a $ is initially zero.

In the second test case, after the first operation $ a = [1, 2, 3], b = [0, 0, 0] $ . After the second operation $ a = [0, 0, 0], b = [1, 2, 3] $ .

In the third test case, it can be shown that the array $ a $ will never become zero.

## 题解
我们首先对本题进行观察，我们不难发现，我们如果最后的状态是：$(0,b)$,那么我们如果持续进行我们的操作，我们会发生下述变化：$(0,b)\to(b,b)\to(b,0)\to(0,b)$ 也就是说，我们的变换周期为 3，我们如果想要最后的结果相同，我们一定要 $\%3$ 后的结果是相同的。

那么现在，我们考虑怎么计算出每一个位置的操作次数是多少。我们发现，我们上述的操作很像我们的辗转相除法，我们模拟一下上述过程，我们能发现：

$$
\begin{aligned}(a,ka+p)\to(ka+p,(k-1)a+p)\to((k-1)a+p,a)\to(a,(k-2)a+p)\end{aligned}
$$

也就是说，我们经过了三次操作后，我们的 $k$ 就会对应的减二。有因此，我们的只需要关注我们的 $k$ 是否是莫尔为 0 的，如果是，那么我们转换为求 $(a,p)$,并且我们的模仍然为 0，如果不是，我们转换为求 $(a,a+p)$,之后，我们经过一次操作后，会变成我们的 $(a,b)$


```cpp
#include <algorithm>
#include <iostream>

using namespace std;
using LL = long long;

const int kN = 1e5 + 1;

int t, n, a[kN], b[kN], c[3];

int C(int a, int b) {
  if (!a || !b) {
    return !!a;
  }
  if (a < b) {
    int k = b / a, p = b % a;
    return (k & 1) ? 2 + C(p, a) : C(a, p);
  } else {
    int k = a / b, p = a % b;
    return (k & 1) ? 1 + C(b, p) : C(p, b);
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  for (cin >> t; t--;) {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
      cin >> b[i];
    }
    c[0] = c[1] = c[2] = 0;
    for (int i = 1; i <= n; ++i) {
      if (a[i] || b[i]) {
        ++c[C(a[i], b[i]) % 3];
      }
    }
    cout << (count(c, c + 3, 0) >= 2 ? "YES" : "NO") << '\n';
  }
  return 0;
}
```