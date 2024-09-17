# Equal Frequencies

## 题面翻译

给出长度为 $n$ 的只包含小写字母的字符串 $s$，请修改尽量少的字符，使得每种出现过的字符出现次数相同。给出最优的修改次数和一种方案。**（一定有解，多组数据）**

## 题目描述

Let's call a string balanced if all characters that are present in it appear the same number of times. For example, "coder", "appall", and "ttttttt" are balanced, while "wowwow" and "codeforces" are not.

You are given a string $ s $ of length $ n $ consisting of lowercase English letters. Find a balanced string $ t $ of the same length $ n $ consisting of lowercase English letters that is different from the string $ s $ in as few positions as possible. In other words, the number of indices $ i $ such that $ s_i \ne t_i $ should be as small as possible.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

Each test case consists of two lines. The first line contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the length of the string $ s $ .

The second line contains the string $ s $ of length $ n $ consisting of lowercase English letters.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, print the smallest number of positions where string $ s $ and a balanced string $ t $ can differ, followed by such a string $ t $ .

If there are multiple solutions, print any. It can be shown that at least one balanced string always exists.

## 样例 #1

### 样例输入 #1

```
4
5
hello
10
codeforces
5
eevee
6
appall
```

### 样例输出 #1

```
1
helno
2
codefofced
1
eeeee
0
appall
```

## 提示

In the first test case, the given string "hello" is not balanced: letters 'h', 'e', and 'o' appear in it once, while letter 'l' appears twice. On the other hand, string "helno" is balanced: five distinct letters are present in it, and each of them appears exactly once. Strings "hello" and "helno" differ in just one position: the fourth character. Other solutions are possible too.

In the second test case, string "codefofced" is balanced since only letters 'c', 'o', 'd', 'e', and 'f' are present in it, and each of them appears exactly twice.

In the third test case, string "eeeee" is balanced since only letter 'e' is present in it.

In the fourth test case, the given string "appall" is already balanced.

## 题解
我们这一题前半部分比较好想，统计每一个字母出现的次数，然后枚举结果里有 k 个因子。
最后，我们现在问题在于怎么在直到分为 k 份，每份的值固定的情况下，我们的答案是多少。
我们的思路是：把我们的比原来的要多的部分，分配给我们的较小的部分，这里，我们可以用我们的双指针来实现。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
string s;
int cnt[26];
struct Node
{
    int id, cnt;
} v[26];
bool cmp(Node a, Node b)
{
    return a.cnt > b.cnt;
}
signed main()
{
    int t;
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while (t--)
    {
        cin >> n >> s;
        fill(cnt, cnt + 26, 0);
        for (int i = 0; i < s.length(); ++i)
            ++cnt[s[i] - 'a'];
        int ans = 0x3f3f3f3f3f3f3f3fll, ansid = 0;
        for (int i = 0; i < 26; ++i)
            v[i] = {i, cnt[i]}; // 记录出现次数
        sort(v, v + 26, cmp); // 排序
        for (int used = 1; used <= 26; ++used)
        { // 枚举使用的字母个数 k
            if (n % used != 0)
                continue;
            int m = n / used; // n / k
            int now = 0;
            for (int i = 0; i < used; ++i)
                now += abs(v[i].cnt - m); // 前 k 个字母的目标为 n / k
            for (int i = used; i < 26; ++i)
                now += v[i].cnt; // 剩余字母的目标为 0
            now /= 2; // 每次修改可以改变 2 个出现次数
            ans = min(ans, now);
            if (ans == now)
                ansid = used;
        }
        cout << ans << '\n'; // 先输出修改次数，下面进行构造
        for (int i = 0; i < ansid; ++i)
            cnt[v[i].id] = n / ansid;
        for (int i = ansid; i < 26; ++i)
            cnt[v[i].id] = 0; // 保存目标出现次数
        for (int i = 0; i < s.length(); ++i)
        {
            bool vis = false;
            for (int j = 0; j < ansid; ++j)
                if (v[j].id == s[i] - 'a')
                {
                    vis = true;
                    break;
                } // 判断当前字母可不可以保留
            if (!vis)
                s[i] = '\0'; // 因为当前字母不在前 k 种里，所以不能保留
            else if (cnt[s[i] - 'a'])
                --cnt[s[i] - 'a'];
            else
                s[i] = '\0'; // 因为当前字母出现次数过多，所以不能保留
        }
        for (int i = 0; i < s.length(); ++i)
        {
            if (s[i] != '\0')
                continue; // 对不能保留的字母重新分配
            int vis = -1;
            for (int j = 0; j < ansid; ++j)
                if (cnt[v[j].id])
                {
                    vis = v[j].id; // 找到还有空余的字母
                    break;
                }
            s[i] = vis + 'a'; // 进行分配
            --cnt[vis];
        }
        cout << s << '\n';
    }
    cout.flush();
    return 0;
}
```