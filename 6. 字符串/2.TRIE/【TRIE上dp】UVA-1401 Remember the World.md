Neal is very curious about combinatorial problems, and now here comes a problem about words. Knowing that Ray has a photographic memory and this may not trouble him, Neal gives it to Jiejie. Since Jiejie can’t remember numbers clearly, he just uses sticks to help himself. Allowing for Jiejie’s only 20071027 sticks, he can only record the remainders of the numbers divided by total amount of sticks. The problem is as follows: a word needs to be divided into small pieces in such a way that each piece is from some given set of words. Given a word and the set of words, Jiejie should calculate the number of ways the given word can be divided, using the words in the set.

## 输入：
The input file contains multiple test cases. For each test case: the first line contains the given word whose length is no more than 300 000. The second line contains an integer S, 1 ≤ S ≤ 4000. Each of the following S lines contains one word from the set. Each word will be at most 100 characters long. There will be no two identical words and all letters in the words will be lowercase. There is a blank line between consecutive test cases. You should proceed to the end of file.

## 输出：
For each test case, output the number, as described above, from the task description modulo 20071027.

## 样例：
abcd
4
a
b
cd
ab

Case 1: 2

## 一句话题意
本题给出一个由 S 个不同单词组成的一个字典和一个长字符串，问把这个串拆解成若干个单词的链接，有多少种方法。

## 题解
我们看到这一题，不难想到我们之前在 [[长期项目/1.算法题目/6. 字符串/2.TRIE/【TRIE上dp】洛谷P2292 语言]]中看到的一种 dp 设计状态，于是我们也可以：
设 $dp[i]$ 表示以 i 结尾的字符串的分解方案数有多少种。

于是，我们转移方程就有：
$dp[i]+=dp[j](j<i\land(i,j)合法)$ 

期望的时间复杂度为 $o(m^2)$

考虑优化，我们可以考虑不是枚举我们的 j，而是枚举在这个位置对应匹配的字符串是什么。我们于是可以用：$dp[i]+=dp[i-len[s]]$,其中 s 是我们的字符串。

期望的时间复杂度为 $o(mn)$,还是不能够通过改题目。

于是，我们考虑**一边做 trie 查询，一边去更新我们的 dp 数组**。具体来说，我们对于每一个位置，都把他作为我们 trie 树的起点，然后我们再去根据下一个字母判断我们的转移是否可行。

```cpp
#include <iostream>
#include <cstring>
#define MAXN 300010
#define MAXNODE 400010
#define MOD 20071027
using namespace std;
int N, sum[MAXN];
char str[MAXN];
int ch[MAXNODE][26];
struct Trie{
    bool flag[MAXNODE];
    int sz;
    Trie() {
        memset(ch, 0, sizeof(ch));
        memset(flag, false, sizeof(flag));
        sz = 1;
    }
    void Insert(char * s) {
        int u = 0;
        for (int i = 0; s[i]; i++) {
            if (!ch[u][s[i]-'a']) ch[u][s[i]-'a'] = sz++;
            u = ch[u][s[i]-'a'];
        }
        flag[u] = true;
    }
    void query(char * s) {
        memset(sum, 0, sizeof(sum)); sum[0] = 1;  // 注意将sum[0]初始化为1
        for (int i = 1; s[i]; i++) {  // 已经确定分解种数的长度为i-1
            int u = 0;
            for (int j = i; s[j]; j++) {  // 一边查询一边更新
                if (!ch[u][s[j]-'a']) break;
                u = ch[u][s[j]-'a'];
                if (flag[u]) sum[j] = (sum[j] + sum[i-1]) % MOD;
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int cnt = 0;
    while (cin >> str + 1) {
        cin >> N;
        Trie trie;
        char s[110];
        for (int i = 0; i < N; i++) {
            cin >> s;
            trie.Insert(s);
        }
        trie.query(str);
        cout << "Case " << ++cnt << ": " << sum[strlen(str+1)] << endl;
    }
    return 0;
}
```