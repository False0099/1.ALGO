#动态规划 #状态设计 #单调队列 
你在一个水果超市里，货架上摆满了玲琅满目的奇珍异果。

给你一个下标从 **1** 开始的数组 `prices` ，其中 `prices[i]` 表示你购买第 `i` 个水果需要花费的金币数目。

水果超市有如下促销活动：

- 如果你花费 `price[i]` 购买了水果 `i` ，那么接下来的 `i` 个水果你都可以免费获得。

**注意** ，即使你 **可以** 免费获得水果 `j` ，你仍然可以花费 `prices[j]` 个金币去购买它以便能免费获得接下来的 `j` 个水果。

请你返回获得所有水果所需要的 **最少** 金币数。

**示例 1：**

**输入：**prices = [3,1,2]
**输出：**4
**解释****：**你可以按如下方法获得所有水果：
- 花 3 个金币购买水果 1 ，然后免费获得水果 2 。
- 花 1 个金币购买水果 2 ，然后免费获得水果 3 。
- 免费获得水果 3 。
注意，虽然你可以免费获得水果 2 ，但你还是花 1 个金币去购买它，因为这样的总花费最少。
购买所有水果需要最少花费 4 个金币。

**示例 2：**

**输入：**prices = [1,10,1,1]
**输出：**2
**解释：**你可以按如下方法获得所有水果：
- 花 1 个金币购买水果 1 ，然后免费获得水果 2 。
- 免费获得水果 2 。
- 花 1 个金币购买水果 3 ，然后免费获得水果 4 。
- 免费获得水果 4 。
购买所有水果需要最少花费 2 个金币。

**提示：**

- `1 <= prices.length <= 1000`
- `1 <= prices[i] <= 105`

## 题解
本题关键在于我们的状态设计，如果我们还是设 $f[i]$ 表示我们从 0-i，那么我们的后效性就无法解决，但如果我们采用我们的 $f[i]$ 表示我们从 $i$ 买到 n 所花费的价格，那么我们就可以相对简单的转移了。
我们的转移方程就有：
$$
dp[i]=price{ [i] }+min_{j=i+1}^{2i+1}dp[j] 
$$

我们的代码就可以有下面的方式：
```cpp
class Solution {
public:
    int minimumCoins(vector<int> &prices) {
        int n = prices.size();
        vector<int> memo((n + 1) / 2);
        function<int(int)> dfs = [&](int i) -> int {
            if (i * 2 >= n) {
                return prices[i - 1]; // i 从 1 开始
            }
            int &res = memo[i]; // 注意这里是引用
            if (res) { // 之前算过
                return res;
            }
            res = INT_MAX;
            for (int j = i + 1; j <= i * 2 + 1; j++) {
                res = min(res, dfs(j));
            }
            res += prices[i - 1];
            return res;
        };
        return dfs(1);
    }
};

作者：灵茶山艾府
链接：https://leetcode.cn/problems/minimum-number-of-coins-for-fruits/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

当然，因为我们的式子很有特点，我们可以考虑用我们的单调队列进行优化：
```cpp
class Solution {
public:
    int minimumCoins(vector<int> &prices) {
        int n = prices.size();
        deque<pair<int, int>> q;
        q.emplace_front(n + 1, 0); // 哨兵
        for (int i = n; i ; i--) {
            while (q.back().first > i * 2 + 1) { // 右边离开窗口
                q.pop_back();
            }
            int f = prices[i - 1] + q.back().second;
            while (f <= q.front().second) {
                q.pop_front();
            }
            q.emplace_front(i, f); // 左边进入窗口
        }
        return q.front().second;
    }
};

作者：灵茶山艾府
链接：https://leetcode.cn/problems/minimum-number-of-coins-for-fruits/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```