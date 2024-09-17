给你一个输入字符串 (`s`) 和一个字符模式 (`p`) ，请你实现一个支持 `'?'` 和 `'*'` 匹配规则的通配符匹配：

- `'?'` 可以匹配任何单个字符。
- `'*'` 可以匹配任意字符序列（包括空字符序列）。

判定匹配成功的充要条件是：字符模式必须能够 **完全匹配** 输入字符串（而不是部分匹配）。

 

**示例 1：**

**输入：**s = "aa", p = "a"
**输出：**false
**解释：**"a" 无法匹配 "aa" 整个字符串。

**示例 2：**

**输入：**s = "aa", p = "*"
**输出：**true
**解释：**'*' 可以匹配任意字符串。

**示例 3：**

**输入：**s = "cb", p = "?a"
**输出：**false
**解释：**'?' 可以匹配 'c', 但第二个 'a' 无法匹配 'b'。

**提示：**

- `0 <= s.length, p.length <= 2000`
- `s` 仅由小写英文字母组成
- `p` 仅由小写英文字母、`'?'` 或 `'*'` 组成

## 题解
对于我们的匹配问题，我们的想法就是用我们的动态规划，这也许已经可以作为我们的一个套路来进行了。我们设我们的 $dp[i][j]$ 表示我们第一个字符串的前 i 个和我们第二个字符串的前 j 个能否匹配，于是我们的就可以有下面的方法：
1. $a[i]=?$, $dp[i][j]=dp[i-1][j-1]$
2. $a[i]=具体字母$，$dp[i][j]=(a[i]==a[j])\land dp[i-1][j-1]$
3. $a[i]=*$   $dp[i][j]=dp[i][j-1] \lor dp[i-1][j]$

```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        dp[0][0] = true;
        for (int i = 1; i <= n; ++i) {
            if (p[i - 1] == '*') {
                dp[0][i] = true;
            }
            else {
                break;
            }
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == '*') {
                    dp[i][j] = dp[i][j - 1] | dp[i - 1][j];
                }
                else if (p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }
        return dp[m][n];
    }
};

作者：力扣官方题解
链接：https://leetcode.cn/problems/wildcard-matching/solutions/315802/tong-pei-fu-pi-pei-by-leetcode-solution/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```