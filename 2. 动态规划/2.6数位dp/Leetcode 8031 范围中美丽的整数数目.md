# 
## 题目描述

给你正整数 `low` ，`high` 和 `k` 。

如果一个数满足以下两个条件，那么它是 **美丽的** ：

- 偶数数位的数目与奇数数位的数目相同。
- 这个整数可以被 `k` 整除。

请你返回范围 `[low, high]` 中美丽整数的数目。

**输入：**low = 10, high = 20, k = 3
**输出：**2
**解释：**给定范围中有 2 个美丽数字：[12,18]
- 12 是美丽整数，因为它有 1 个奇数数位和 1 个偶数数位，而且可以被 k = 3 整除。
- 18 是美丽整数，因为它有 1 个奇数数位和 1 个偶数数位，而且可以被 k = 3 整除。
以下是一些不是美丽整数的例子：
- 16 不是美丽整数，因为它不能被 k = 3 整除。
- 15 不是美丽整数，因为它的奇数数位和偶数数位的数目不相等。
给定范围内总共有 2 个美丽整数。

## 题解
我们可以按照数位dp的思路来解决这一个题目，统计从0到某个位置时满足条件的所有个数，然后再前后相减即可

## 代码
```cpp
class Solution {
    int calc(int high, int k) {
        auto s = to_string(high);
        int n = s.length(), memo[n][k + 1][n * 2 + 1];
        memset(memo, -1, sizeof(memo)); // -1 表示没有计算过
        function<int(int, int, int, bool, bool)> dfs;
        dfs = [&](int i, int val, int diff, bool is_limit, bool is_num) -> int {
            if (i == n)
                return is_num && val == 0 && diff == n; // 找到了一个合法数字
            if (!is_limit && is_num && memo[i][val][diff] != -1)
                return memo[i][val][diff];
            int res = 0;
            if (!is_num) //枚举前导0 
                res = dfs(i + 1, val, diff, false, false);
            int up = is_limit ? s[i] - '0' : 9; // 如果前面填的数字都和 high 的一样，那么这一位至多填数字 s[i]（否则就超过 high 啦）
            for (int d = 1 - is_num; d <= up; d++) // 枚举要填入的数字 d
                res += dfs(i + 1, (val * 10 + d) % k, diff + d % 2 * 2 - 1, is_limit && d == up, true);
            if (!is_limit && is_num)
                memo[i][val][diff] = res; // 记忆化
            return res;
        };
        return dfs(0, 0, n, true, false);
    }

public:
    int numberOfBeautifulIntegers(int low, int high, int k) {
        return calc(high, k) - calc(low - 1, k);
    }
};

```