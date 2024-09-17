# Candy Store

## 题面翻译

有 $n$ 种糖，第 $i$ 种糖有 $a_i$ 块，每块 $b_i$ 元。对每种糖，你要选择一个 $d_i | a_i$，然后每 $d_i$ 块糖装进一个袋子。

现在把糖摆上货架，第 $i$ 类糖的价签上的价格 $c_i$ 是一袋子 $i$ 类糖的价值，即 $c_i = d_i \times b_i$。

对于货架上一个区间 $[l, r]$，如果他们的价签相同，即 $c_l = c_{l + 1} = \dots = c_r$，则他们可以共用一个价签。

请问最少需要多少价签？

多组数据，保证 $n$ 之和不超过 $2 \times 10^5$，$1 \leq a_i \leq 10^9$，$1 \leq b_i \leq 10^4$。

Provider：一扶苏一

## 题目描述

The store sells $ n $ types of candies with numbers from $ 1 $ to $ n $ . One candy of type $ i $ costs $ b_i $ coins. In total, there are $ a_i $ candies of type $ i $ in the store.

You need to pack all available candies in packs, each pack should contain only one type of candies. Formally, for each type of candy $ i $ you need to choose the integer $ d_i $ , denoting the number of type $ i $ candies in one pack, so that $ a_i $ is divided without remainder by $ d_i $ .

Then the cost of one pack of candies of type $ i $ will be equal to $ b_i \cdot d_i $ . Let's denote this cost by $ c_i $ , that is, $ c_i = b_i \cdot d_i $ .

After packaging, packs will be placed on the shelf. Consider the cost of the packs placed on the shelf, in order $ c_1, c_2, \ldots, c_n $ . Price tags will be used to describe costs of the packs. One price tag can describe the cost of all packs from $ l $ to $ r $ inclusive if $ c_l = c_{l+1} = \ldots = c_r $ . Each of the packs from $ 1 $ to $ n $ must be described by at least one price tag. For example, if $ c_1, \ldots, c_n = [4, 4, 2, 4, 4] $ , to describe all the packs, a $ 3 $ price tags will be enough, the first price tag describes the packs $ 1, 2 $ , the second: $ 3 $ , the third: $ 4, 5 $ .

You are given the integers $ a_1, b_1, a_2, b_2, \ldots, a_n, b_n $ . Your task is to choose integers $ d_i $ so that $ a_i $ is divisible by $ d_i $ for all $ i $ , and the required number of price tags to describe the values of $ c_1, c_2, \ldots, c_n $ is the minimum possible.

For a better understanding of the statement, look at the illustration of the first test case of the first test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1798C/1160d0ae9da0a28139cfb8794bbbd0911d44c66f.png)Let's repeat the meaning of the notation used in the problem:

 $ a_i $ — the number of candies of type $ i $ available in the store.

 $ b_i $ — the cost of one candy of type $ i $ .

 $ d_i $ — the number of candies of type $ i $ in one pack.

 $ c_i $ — the cost of one pack of candies of type $ i $ is expressed by the formula $ c_i = b_i \cdot d_i $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 100\, 000 $ ). Description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 200\, 000 $ ) — the number of types of candies.

Each of the next $ n $ lines of each test case contains two integers $ a_i $ and $ b_i $ ( $ 1 \le a_i \le 10^9 $ , $ 1 \le b_i \le 10\, 000 $ ) — the number of candies and the cost of one candy of type $ i $ , respectively.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 200\, 000 $ .

## 输出格式

For each test case, output the minimum number of price tags required to describe the costs of all packs of candies in the store.

## 样例 #1

### 样例输入 #1

```
5
4
20 3
6 2
14 5
20 7
3
444 5
2002 10
2020 2
5
7 7
6 5
15 2
10 3
7 7
5
10 1
11 5
5 1
2 2
8 2
6
7 12
12 3
5 3
9 12
9 3
1000000000 10000
```

### 样例输出 #1

```
2
1
3
2
5
```

## 提示

In the first test case, you can choose $ d_1 = 4 $ , $ d_2 = 6 $ , $ d_3 = 7 $ , $ d_4 = 5 $ . Then the cost of packs will be equal to $ [12, 12, 35, 35] $ . $ 2 $ price tags are enough to describe them, the first price tag for $ c_1, c_2 $ and the second price tag for $ c_3, c_4 $ . It can be shown that with any correct choice of $ d_i $ , at least $ 2 $ of the price tag will be needed to describe all the packs. Also note that this example is illustrated by a picture in the statement.

In the second test case, with $ d_1 = 4 $ , $ d_2 = 2 $ , $ d_3 = 10 $ , the costs of all packs will be equal to $ 20 $ . Thus, $ 1 $ price tag is enough to describe all the packs. Note that $ a_i $ is divisible by $ d_i $ for all $ i $ , which is necessary condition.

In the third test case, it is not difficult to understand that one price tag can be used to describe $ 2 $ nd, $ 3 $ rd and $ 4 $ th packs. And additionally a price tag for pack $ 1 $ and pack $ 5 $ . Total: $ 3 $ price tags.

## 题解
注意：我们的标签必须是连续的！所以我们可以 $o(n)$ 的解决我们的问题！

我们本题的思路在于，我们判断有哪些可以共用一个糖，于是我们就可以通过我们的一个简单的贪心去进行，考虑一段能够公用一个价格标签 c 的区间 $[l,r]$,我们有 $x=bldl=b_{l+1}d_{l+1}=\dots b_{r}d_{r}$,我们显然有：$lcm_{i=1}^r b_{i}|c$,
于是一个区间能够共用一个价签的条件就是 $lcm(b_{l},b_{l+1},\dots b_{r})|gcd(a_{l}b_{l},a_{l+1}b_{l+1}\dots,a_{r}b_{r})$

下一个问题是怎么安排我们的价签。这里是一个贪心，尽可能多的把价签安排在一个集合即可。

```cpp
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

int T;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  for (std::cin >> T; T; --T) {
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> a[i] >> b[i];
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
      ++ans;
      long long x = b[i], y = 1ll * a[i] * b[i];
      for (int j = i + 1; j <= n; ++j) {
        x = std::lcm(1ll * b[j], x);
        y = std::gcd(y, 1ll * a[j] * b[j]);
        if (y % x != 0) {
          i = j - 1; break;
        }
        if (j == n) {
          i = j; break;
        }
      }
    }
    std::cout << ans << '\n';
  }
}
```