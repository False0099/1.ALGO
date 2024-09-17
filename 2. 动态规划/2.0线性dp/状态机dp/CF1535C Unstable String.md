# Unstable String

## 题面翻译

$t$ 组询问，每次给定一个仅包含字符 `1` 或 `0` 或 `?` 字符串 $s$。定义一个子串是**不稳定的**当且仅当子串中任意相邻两数均不相同，如 $101010\cdots$ 或 $010101\cdots$。

我们称一个子串是**好看的**当且仅当我们可以将其中的 `?` 换为 `1` 或 `0` 其中一种使得这个子串是**不稳定的**。

求字符串中**好看的**子串个数之和。

$1\leq t\leq 10^4$，$1 \leq\left\vert s\right\vert\leq2\times10^5$，$\sum \left\vert s\right\vert\leq2\times10^5$。

Translated by LinkZelda

## 题目描述

You are given a string $ s $ consisting of the characters 0, 1, and ?.

Let's call a string unstable if it consists of the characters 0 and 1 and any two adjacent characters are different (i. e. it has the form 010101... Or 101010...).

Let's call a string beautiful if it consists of the characters 0, 1, and ?, and you can replace the characters ? To 0 or 1 (for each character, the choice is independent), so that the string becomes unstable.

For example, the strings 0?? 10, 0, and ??? Are beautiful, and the strings 00 and ?1?? 1 are not.

Calculate the number of beautiful contiguous substrings of the string $ s $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — number of test cases.

The first and only line of each test case contains the string $ s $ ( $ 1 \le |s| \le 2 \cdot 10^5 $ ) consisting of characters 0, 1, and ?.

It is guaranteed that the sum of the string lengths over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the number of beautiful substrings of the string $ s $ .

## 样例 #1

### 样例输入 #1

```
3
0?10
???
?10??1100
```

### 样例输出 #1

```
8
6
25
```


## 题解
我们本题的思路就是采用我们的线性 dp，我们设 $dp[i][0/1]$ 表示我们以 i 为后缀，且我们的第 i 位是 0/1 的方案总数有哪些，于是我们就可以通过我们的这一种转移来进行我们的计数工作：
```cpp
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int t; ll ans, dp[200010][2]; string s;

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		cin >> s;
        int len = s.length(); ans = 0;
		if (s[0] != '?') dp[0][s[0] - '0'] = 1;
		else dp[0][0] = dp[0][1] = 1; // 边界
		for (int i = 1; i < len; ++i)
			if (s[i] != '?')
				dp[i][s[i] - '0'] = dp[i-1][!(s[i] - '0')] + 1;
			else
				dp[i][0] = dp[i-1][1] + 1, dp[i][1] = dp[i-1][0] + 1;
		for (int i = 0; i < len; ++i) ans += max(dp[i][0], dp[i][1]); // 如题解公式
		printf("%lld\n", ans);
		for (int i = 0; i < len; ++i) dp[i][0] = dp[i][1] = 0; //记得清空
	}
	return 0;
}
```
```