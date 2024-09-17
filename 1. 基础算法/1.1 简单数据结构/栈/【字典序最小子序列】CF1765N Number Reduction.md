# Number Reduction

## 题面翻译

给定一个正整数 $x$，你可以移除 $x$ 的任意一位，前提是移除后的 $x$ 不含前导 0，且仍是一个正整数。求 $k$ 次操作后 $x$ 的最小值。

一共 $ t $ ( $ 1 \le t \le 10^5 $ )  组数据。

对于每组数据，给出 $ x $ ( $ 1 \le x < 10^{500000} $ ) 和 $ k $ ( $ 0 \le k < |x| $ )。其中 $|x|$ 表示 $x$ 的位数。

对于每组数据，输出 $k$ 次操作后 $x$ 的最小值。

对于 $100\%$ 的数据满足： $\sum_{i=1}^t|x_i| \le 5 \cdot 10^5 $

**有多测**。

## 题目描述

You are given a positive integer $ x $ .

You can apply the following operation to the number: remove one occurrence of any digit in such a way that the resulting number does not contain any leading zeroes and is still a positive integer. For example, $ 10142 $ can be converted to $ 1142 $ , $ 1042 $ , $ 1012 $ or $ 1014 $ (note that $ 0142 $ is not a valid outcome); $ 10 $ can be converted to $ 1 $ (but not to $ 0 $ since it is not positive).

Your task is to find the minimum positive integer that you can obtain from $ x $ if you can apply the aforementioned operation exactly $ k $ times.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^5 $ ) — the number of test cases.

The first line of each test case contains a single integer $ x $ ( $ 1 \le x < 10^{500000} $ ).

The second line contains a single integer $ k $ ( $ 0 \le k < |x| $ ), where $ |x| $ is the length of the number $ x $ .

The sum of $ |x| $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, print one integer — the minimum positive number that you can obtain from $ x $ if you can apply the operation exactly $ k $ times.

## 样例 #1

### 样例输入 #1

```
5
10000
4
1337
0
987654321
6
66837494128
5
7808652
3
```

### 样例输出 #1

```
1
1337
321
344128
7052
```

## 题解
本题显然属于一个字典序最小子序列问题，我们的方法也很简单，
先看看**允许有前导零**要怎么做：直接遍历字符串，用单调栈维护，只要当前字符小于栈顶，就弹出栈顶同时把 $k$ 减一。最后栈底到栈顶是单调非降的，把栈顶的 $k$ 个元素弹出。

回到原题，不允许有前导零，我们可以在前 $k+1$ 个字符中找到**第一个最小的非 0 字符**，设其为下标为 $j$,那么肯定要把下标小于 $j$ 的字符都删掉。然后从 $j+1$ 开始按照上面的做法跑单调栈即可。

也就是说，我们采用**PK**的思路，我们对于我们一个字符串，我们**先保证我们的长度**，在满足我们的**长度条件的前提下**，再去进行我们的贪心。也因此我们可以用一个单调栈来维护我们的答案。

```c++
#include <iostream>

#include <vector>

#include <string>

#include <cstdio>

#include <algorithm>

  

int main() {

    int T, k;

    std::string s;

  

    std::cin >> T;

    while (T--) {

        std::cin >> s >> k;

        int j = 0;

  

        // 找到前 k+1 个字符中最小的非 0 字符（且下标最小）

        for (int i = 0; i <= k; ++i) {

            if (s[i] > '0' && s[i] < s[j]) {

                j = i;

            }

        }

  

        k -= j;  // 把 j 左边的都删掉

        std::string st(1, s[j]);  // 保留 s[j]

  

        // j 右边的正常跑单调栈即可

        for (size_t i = j + 1; i < s.size(); ++i) {

            while (st.size() > 1 && k > 0 && s[i] < st.back()) {

                st.pop_back();

                --k;

            }

            st.push_back(s[i]);

        }

  

        // 还剩下操作次数，就去掉后面的（因为栈顶元素大）

        st.resize(st.size() - k);

  

        std::cout << st << std::endl;

    }

  

    return 0;

}

```