# Rock and Lever

## 题面翻译

定义 $\&$ 为按位与操作，$\oplus$ 为按位异或操作。

求出序列 $a$ 中满足 $a_i\&a_j\ge a_i\oplus a_j$ 的二元组 $(i,j)$ 的个数。

多组数据。

## 题目描述

"You must lift the dam. With a lever. I will give it to you. You must block the canal. With a rock. I will not give the rock to you."





Danik urgently needs rock and lever! Obviously, the easiest way to get these things is to ask Hermit Lizard for them.

Hermit Lizard agreed to give Danik the lever. But to get a stone, Danik needs to solve the following task.

You are given a positive integer $ n $ , and an array $ a $ of positive integers. The task is to calculate the number of such pairs $ (i, j) $ that $ i<j $ and $ a_i $ $ \& $ $ a_j \ge a_i \oplus a_j $ , where $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND), and $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Danik has solved this task. But can you solve it?

## 输入格式

Each test contains multiple test cases.

The first line contains one positive integer $ t $ ( $ 1 \le t \le 10 $ ) denoting the number of test cases. Description of the test cases follows.

The first line of each test case contains one positive integer $ n $ ( $ 1 \le n \le 10^5 $ ) — length of the array.

The second line contains $ n $ positive integers $ a_i $ ( $ 1 \le a_i \le 10^9 $ ) — elements of the array.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For every test case print one non-negative integer — the answer to the problem.

## 样例 #1

### 样例输入 #1

```
5
5
1 4 3 7 10
3
1 1 1
4
6 2 5 3
2
2 4
1
1
```

### 样例输出 #1

```
1
3
2
0
0
```

## 提示

In the first test case there is only one pair: $ (4,7) $ : for it $ 4 $ $ \& $ $ 7 = 4 $ , and $ 4 \oplus 7 = 3 $ .

In the second test case all pairs are good.

In the third test case there are two pairs: $ (6,5) $ and $ (2,3) $ .

In the fourth test case there are no good pairs.

## 题解
我们遇见**比大小+位运算**，可以考虑从我们的**比大小的**最原始的方法，从高到低判断每一位的大小，相同再去比较下一位的方式来进行计算。

我们对 $(a_i, a_j)$ 这个二元组进行分类讨论：

从高往低枚举每一对$(a_i[k], a_j[k])$：
* $(0, 0)$无法判断。
* $(0, 1)$不满足条件。
* $(1, 0)$不满足条件。
* $(1, 1)$满足条件。
一旦能够判断结果就直接跳出。
也就是说我们需要着重观察的是数字的最高位的$1$，也只有它是有用的，例如对于两个二进制数：
$a_i = 00011111$
$a_j = 00100010$
我们只需要比较从高往低第三位的$(0, 1)$即可判断出不满足条件，于是这一对$(a_i, a_j)$是不会被计数的。
于是我们可以处理出每一个数字的最高位$1$所在的位置，例如$pos[0011001]=4$（最右端是最低位，即第$0$位），这有利于后续做处理。

我们现在开始枚举$j$，那么对于枚举出的这个$j$，有多少个$i$满足条件呢，也很简单了，那就是：左侧最高位和$a_j$相同的数字的个数。直接用桶计算即可。

### 代码

  

```cpp

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e6 + 9;

int a[N], cnt[50];

  

int getpos(int x)

{
    int res(0);
    while(x)res ++, x >>= 1;
    return res;
}
void solve()

{
    int n;cin >> n;
    for(int i = 1;i <= n; ++ i)cin >>a[i];
    memset(cnt, 0, sizeof cnt);
    ll ans = 0;
    for(int i = 1;i <= n; ++ i)
    {
        int pos = getpos(a[i]);
        ans += cnt[pos];
        cnt[pos] ++;
    }
    cout << ans << '\n';
}
int main()

{

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    int _;cin >> _;

    while(_ --)solve();

    return 0;

}

```