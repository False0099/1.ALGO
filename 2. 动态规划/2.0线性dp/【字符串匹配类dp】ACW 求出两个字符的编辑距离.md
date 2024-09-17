# 知识点
  ## [[动态规划]]
# 题目
给定 n 个长度不超过 10的字符串以及 m 次询问，每次询问给出一个字符串和一个操作次数上限。
对于每次询问，请你求出给定的 n 个字符串中有多少个字符串可以在上限操作次数内经过操作变成询问给出的字符串。
每个对字符串进行的单个字符的插入、删除或替换算作一次操作。

# 思路
我们采用类似于 LIS 的状态表达，即 $f[i][j]$ 表示我们第一个串的 $1-i$ **所有位置**与第二个串的 $1-j$ **所有位置**相等的总共方案数。于是我们的转移就可以根据我们的操作分为三类：
1. **增加**，那么我们就可以拿我们第一个串的 i-1 位和我们的 j 位匹配的最小操作次数+1
2. **删除**，那么我们就可以那我们的第一个串的 i 位和我们的 j-1 位匹配的最小操作次数+1
3. **修改**，根据当前位置是否匹配，如果匹配，我们就直接用 $(i-1,j-1)$ 转移即可。如果不匹配，我们还要再原来的答案的基础上再+1。

![[Pasted image 20230416174716.png]]
·![[Pasted image 20230416174739.png]]
·
# AC 代码
```cpp
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1e1 + 5, M = 1e3 + 10;

int n, m;
char str[M][N];
int dp[N][N];

int edit_distance(char a[], char b[])
{
    int la = strlen(a + 1), lb = strlen(b + 1);
    for (int i = 0; i <= lb; i++) {
        dp[0][i] = i;
    }
    for (int i = 0; i <= la; i++) {
        dp[i][0] = i;
    }
    for (int i = 1; i <= la; i++) {
        for (int j = 1; j <= lb; j++) {
            dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);
            dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + (a[i] != b[j]));
        }
    }
    return dp[la][lb];
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> (str[i] + 1);
    }

    while (m--) {
        int res = 0;
        char s[N];
        int limit;
        cin >> (s + 1) >> limit;
        for (int i = 0; i < n; i++) {
            if (edit_distance(str[i], s) <= limit) {
                res++;
            }
        }
        cout << res << endl;
    }

    return 0;
}

作者：Bug-Free
链接：https://www.acwing.com/solution/content/46098/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
# 备注
