# Palindrome Basis

## 题面翻译

给你一个正整数。如果某个正整数的数字顺序颠倒后仍保持不变，那么我们将其称为无前导零的回文整数。

找出将 $n$ 表示为正回文整数和的不同方式的数量。如果至少一个回文整数的数量不同，则认为这两种方法不同。

例如：$5=4+1$ 和 $5=3+1+1$ 被认为是不同的，但 $5=3+1+1$ 和 $5=1+3+1$ 被认为是相同的。

你需要输出表示为 $n$ 的正回文整数和的不同方式的数量。

因为答案可能相当大，所以以模 $10^9+7$ 后输出即可

## 题目描述

You are given a positive integer $ n $ . Let's call some positive integer $ a $ without leading zeroes palindromic if it remains the same after reversing the order of its digits. Find the number of distinct ways to express $ n $ as a sum of positive palindromic integers. Two ways are considered different if the frequency of at least one palindromic integer is different in them. For example, $ 5=4+1 $ and $ 5=3+1+1 $ are considered different but $ 5=3+1+1 $ and $ 5=1+3+1 $ are considered the same.

Formally, you need to find the number of distinct multisets of positive palindromic integers the sum of which is equal to $ n $ .

Since the answer can be quite large, print it modulo $ 10^9+7 $ .

## 输入格式

The first line of input contains a single integer $ t $ ( $ 1\leq t\leq 10^4 $ ) denoting the number of testcases.

Each testcase contains a single line of input containing a single integer $ n $ ( $ 1\leq n\leq 4\cdot 10^4 $ ) — the required sum of palindromic integers.

## 输出格式

For each testcase, print a single integer denoting the required answer modulo $ 10^9+7 $ .

## 样例 #1

### 样例输入 #1

```
2
5
12
```

### 样例输出 #1

```
7
74
```

## 提示

For the first testcase, there are $ 7 $ ways to partition $ 5 $ as a sum of positive palindromic integers:

- $ 5=1+1+1+1+1 $
- $ 5=1+1+1+2 $
- $ 5=1+2+2 $
- $ 5=1+1+3 $
- $ 5=2+3 $
- $ 5=1+4 $
- $ 5=5 $

For the second testcase, there are total $ 77 $ ways to partition $ 12 $ as a sum of positive integers but among them, the partitions $ 12=2+10 $ , $ 12=1+1+10 $ and $ 12=12 $ are not valid partitions of $ 12 $ as a sum of positive palindromic integers because $ 10 $ and $ 12 $ are not palindromic. So, there are $ 74 $ ways to partition $ 12 $ as a sum of positive palindromic integers.

## 题解
我们这一题的目的就是把我们的原本的数字拆分成若干个满足条件的，然后问我们一共有多少种可行的方案数。这里，我们就可以用我们的 0-1 背包。
我们可以先预处理出我们的所有返回内的回文数时多少，然后再把这个当作我们的背包容量，之后，我们再去进行我们的状态转移，$f[i+x]+=f[i]$。
```cpp
vector<int>v;
int check(int n) {
    int tmp = n,res = 0;
    while (n) {
        res = res * 10 + n % 10;
        n /= 10;
    }
    return res == tmp;
}
int f[MAXN];
void slove() {
    for (int i = 1; i <= 4e4; i++)
        if (check(i))v.push_back(i);
    f[0] = 1;
    for (int x : v) 
        for (int i = 0; i <= 4e4; i++) 
            (f[i + x] += f[i]) %= mod;
    int T; cin >> T; while (T--) {
        int x; cin >> x;
        cout << f[x] << endl;
    }
}
```