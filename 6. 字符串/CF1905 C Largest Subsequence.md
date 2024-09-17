# Largest Subsequence

#后缀 #字符串 
## 题面翻译

对于一个长为 $n$ 的字符串，一次操作定义为将 $n$ 的字典序最大的子序列 $t$ 拉出来进行一次右 shift 操作，再原位放进去。

shift 操作是指对于 $t[1\sim m]$ 转化为 $t_m+t[1\sim m-1]$，$+$ 是指拼接操作。

求使 $s$ 有序的最少操作次数，或报告不可能。

## 题目描述

Given is a string $ s $ of length $ n $ . In one operation you can select the lexicographically largest $ ^\dagger $ subsequence of string $ s $ and cyclic shift it to the right $ ^\ddagger $ .

Your task is to calculate the minimum number of operations it would take for $ s $ to become sorted, or report that it never reaches a sorted state.

 $ ^\dagger $ A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- In the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

 $ ^\ddagger $ By cyclic shifting the string $ t_1 t_2\ldots t_m $ to the right, we get the string $ t_mt_1\ldots t_{m-1} $ .

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the string $ s $ .

The second line of each test case contains a single string $ s $ of length $ n $ , consisting of lowercase English letters.

It is guaranteed that sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the minimum number of operations required to make $ s $ sorted, or $ -1 $ if it's impossible.

## 样例 #1

### 样例输入 #1

```
6
5
aaabc
3
acb
3
bac
4
zbca
15
czddeneeeemigec
13
cdefmopqsvxzz
```

### 样例输出 #1

```
0
1
-1
2
6
0
```

## 提示

In the first test case, the string $ s $ is already sorted, so we need no operations.

In the second test case, doing one operation, we will select cb and cyclic shift it. The string $ s $ is now abc which is sorted.

In the third test case, $ s $ cannot be sorted.

In the fourth test case we will perform the following operations:

- The lexicographically largest subsequence is zca. Then $ s $ becomes abzc.
- The lexicographically largest subsequence is zc. Then $ s $ becomes abcz. The string becomes sorted.

Thus, we need $ 2 $ operations.

## 题解
假如第一次找到的最大字典序子序列是 t, 那么如果我们最后有答案，那么我们最后的操作，就是把我们的这一个子序列给完全翻转过来。

由于最大字典序的性质，t 明显是单调递减的

记录字母的位置，按字母从大到小，再记录当前 t 的最大位置，即可求 t

假如执行了一次操作，第二次的最大字典序子序列是 t2

由于t是最大字典序子序列，t2一定是 t删去最后一个字母

后面的操作同理

最后只是把t倒转

先判把t倒转后答案是否合法，再计算答案

**注意当 t 的字母都是相同的字母时，执行操作是没有意义的
这个情况只会是t操作到只剩最大的字母记录一下最大的字母的个数，初始 t 长度减去最大的字母就是答案.
```
#include <bits/stdc++.h>
using namespace std;
int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    int q;
    cin >> q;
    while (q--)
    {
        int n;
        string s;
        cin >> n >> s;
        s = '$' + s;
        vector<int> subset;
        for (int i = 1; i <= n; ++i)
        {
            while (!subset.empty() && s[subset.back()] < s[i])
            {
                subset.pop_back();
            }
            subset.push_back(i);
        }
        int ans = 0;
        int m = (int)subset.size() - 1;
        while (ans <= m && s[subset[ans]] == s[subset[0]])
        {
            ans++;
        }
        ans = m - ans + 1;

        for (int i = 0; i <= m; ++i)
        {
            if (i < m - i)
            {
                swap(s[subset[i]], s[subset[m - i]]);
            }
        }
        for (int i = 2; i <= n; ++i)
        {
            if (s[i] < s[i - 1])
            {
                ans = -1;
                break;
            }
        }
        cout << ans << '\n';
    }
}
```