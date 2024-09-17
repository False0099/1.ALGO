#贪心 #重排
# Shocking Arrangement

## 题面翻译

给出一个长度为 $n$ 的数列 $a$，满足 $\sum_{i = 1}^n a_i = 0$。

你需要重排这个数列，使得重排后满足

$$\max\limits_{1 \le l \le r \le n} \lvert a_l + a_{l+1} + \ldots + a_r \rvert < \max(a_1, a_2, \ldots, a_n) - \min(a_1, a_2, \ldots, a_n)$$

多组数据，$n$ 之和不超过 $3 \times 10^5$，$|a_i| \leq 10^9$。


Provider：一扶苏一

## 题目描述

You are given an array $ a_1, a_2, \ldots, a_n $ consisting of integers such that $ a_1 + a_2 + \ldots + a_n = 0 $ .

You have to rearrange the elements of the array $ a $ so that the following condition is satisfied:

$$\max\limits_{1 \le l \le r \le n} \lvert a_l + a_{l+1} + \ldots + a_r \rvert < \max(a_1, a_2, \ldots, a_n) - \min(a_1, a_2, \ldots, a_n)$$ 

Where  $|x|$  denotes the absolute value of  $ x $ .More formally, determine if there exists a permutation  $ p_1, p_2, \ldots, p_n $  that for the array  $ a_{p_1}, a_{p_2}, \ldots, a_{p_n} $ , the condition above is satisfied, and find the corresponding array. Recall that the array  $ p_1, p_2, \ldots, p_n $  is called a permutation if for each integer  $ x $  from  $ 1 $  to  $ n $  there is exactly one  $ i $  from  $ 1 $  to  $ n $  such that  $ p_i = x$.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 50\, 000 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 300\, 000 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ -10^9 \le a_i \le 10^9 $ ) — elements of the array $ a $ . It is guaranteed that the sum of the array $ a $ is zero, in other words: $ a_1 + a_2 + \ldots + a_n = 0 $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 300\, 000 $ .

## 输出格式

For each test case, if it is impossible to rearrange the elements of the array $ a $ in the required way, print "No" in a single line.

If possible, print "Yes" in the first line, and then in a separate line $ n $ numbers — elements $ a_1, a_2, \ldots, a_n $ rearranged in a valid order ( $ a_{p_1}, a_{p_2}, \ldots, a_{p_n} $ ).

If there are several possible answers, you can output any of them.

## 样例 #1

### 样例输入 #1

```
7
4
3 4 -2 -5
5
2 2 2 -3 -3
8
-3 -3 1 1 1 1 1 1
3
0 1 -1
7
-3 4 3 4 -4 -4 0
1
0
7
-18 13 -18 -17 12 15 13
```

### 样例输出 #1

```
Yes
-5 -2 3 4
Yes
-3 2 -3 2 2
Yes
1 1 1 -3 1 1 1 -3
Yes
-1 0 1
Yes
4 -4 4 -4 0 3 -3
No
Yes
13 12 -18 15 -18 13 -17
```

## 提示

In the first test case $ \max (a_1, \ldots, a_n) - \min (a_1, \ldots, a_n) = 9 $ . Therefore, the elements can be rearranged as $ [-5, -2, 3, 4] $ . It is easy to see that for such an arrangement $ \lvert a_l + \ldots + a_r \rvert $ is always not greater than $ 7 $ , and therefore less than $ 9 $ .

In the second test case you can rearrange the elements of the array as $ [-3, 2, -3, 2, 2] $ . Then the maximum modulus of the sum will be reached on the subarray $ [-3, 2, -3] $ , and will be equal to $ \lvert -3 + 2 + -3 \rvert = \lvert -4 \rvert = 4 $ , which is less than $ 5 $ .

In the fourth test example, any rearrangement of the array $ a $ will be suitable as an answer, including $ [-1, 0, 1] $ .

## 题解
我们这一题只需要采取我们的交错来构造就能构成我们的答案，只要我们分别按照我们的正负数排序，然后再依次添加即可，另外，**无解只有可能是全为 0**.

```cpp
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

int T;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  for (std::cin >> T; T; --T) {
    int n;
    std::cin >> n;
    std::vector<int> a(n), b, c;
    std::generate(a.begin(), a.end(), []() { int x; std::cin >> x; return x; });
    if (*std::max_element(a.begin(), a.end()) == 0) {
      std::cout << "No\n";
      continue;
    }
    std::cout << "Yes\n";
    for (auto i : a) 
      if (i < 0) b.push_back(i);
      else c.push_back(i);
    std::sort(b.begin(), b.end());
    std::sort(c.begin(), c.end(), std::greater<int>());
    int sum = 0;
    for (int i = 1, j = 0, k = 0; i <= n; ++i) {
      if (sum >= 0 && j < b.size()) {
        std::cout << b[j] << ' ';
        sum += b[j++];
      } else {
        std::cout << c[k] << ' ';
        sum += c[k++];
      }
    }
    std::cout << '\n';
  }
}
```