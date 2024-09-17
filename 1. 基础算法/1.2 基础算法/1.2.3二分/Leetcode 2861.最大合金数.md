假设你是一家合金制造公司的老板，你的公司使用多种金属来制造合金。现在共有 `n` 种不同类型的金属可以使用，并且你可以使用 `k` 台机器来制造合金。每台机器都需要特定数量的每种金属来创建合金。

对于第 `i` 台机器而言，创建合金需要 `composition[i][j]` 份 `j` 类型金属。最初，你拥有 `stock[i]` 份 `i` 类型金属，而每购入一份 `i` 类型金属需要花费 `cost[i]` 的金钱。

给你整数 `n`、`k`、`budget`，下标从 **1** 开始的二维数组 `composition`，两个下标从 **1** 开始的数组 `stock` 和 `cost`，请你在预算不超过 `budget` 金钱的前提下，**最大化** 公司制造合金的数量。

**所有合金都需要由同一台机器制造。**

返回公司可以制造的最大合金数。

**示例 1：**

**输入：**n = 3, k = 2, budget = 15, composition = [[1,1,1],[1,1,10]], stock = [0,0,0], cost = [1,2,3]
**输出：**2
**解释：**最优的方法是使用第 1 台机器来制造合金。
要想制造 2 份合金，我们需要购买：
- 2 份第 1 类金属。
- 2 份第 2 类金属。
- 2 份第 3 类金属。
总共需要 2 * 1 + 2 * 2 + 2 * 3 = 12 的金钱，小于等于预算 15 。
注意，我们最开始时候没有任何一类金属，所以必须买齐所有需要的金属。
可以证明在示例条件下最多可以制造 2 份合金。

**示例 2：**

**输入：**n = 3, k = 2, budget = 15, composition = [[1,1,1],[1,1,10]], stock = [0,0,100], cost = [1,2,3]
**输出：**5
**解释：**最优的方法是使用第 2 台机器来制造合金。 
要想制造 5 份合金，我们需要购买： 
- 5 份第 1 类金属。
- 5 份第 2 类金属。 
- 0 份第 3 类金属。 
总共需要 5 * 1 + 5 * 2 + 0 * 3 = 15 的金钱，小于等于预算 15 。 
可以证明在示例条件下最多可以制造 5 份合金。

**示例 3：**

**输入：**n = 2, k = 3, budget = 10, composition = [[2,1],[1,2],[1,1]], stock = [1,1], cost = [5,5]
**输出：**2
**解释：**最优的方法是使用第 3 台机器来制造合金。
要想制造 2 份合金，我们需要购买：
- 1 份第 1 类金属。
- 1 份第 2 类金属。
总共需要 1 * 5 + 1 * 5 = 10 的金钱，小于等于预算 10 。
可以证明在示例条件下最多可以制造 2 份合金。

## 题解
我们假设要制造 m 个合金，由于 num 越小，花的钱越少，num 越多，花的越多，所以我们的 num 满足单调性。可以二分。

对于第 j 类金属：如果 $composition[i][j]\times num\leq stock[j]$,那么我们无需购买额外的，反之，则需要额外花费。如果超过 budget，那么我们就无法制造 num 份，否则可以制造。

```cpp
class Solution {
public:
    int maxNumberOfAlloys(int n, int k, int budget, vector<vector<int>> &composition, vector<int> &stock, vector<int> &cost) {
        int ans = 0;
        int mx = *min_element(stock.begin(), stock.end()) + budget;
        for (auto &com: composition) {
            auto check = [&](long long num) -> bool {
                long long money = 0;
                for (int i = 0; i < n; i++) {
                    if (stock[i] < com[i] * num) {
                        money += (com[i] * num - stock[i]) * cost[i];
                        if (money > budget) {
                            return false;
                        }
                    }
                }
                return true;
            };
            int left = 0, right = mx + 1;
            while (left + 1 < right) { // 开区间写法
                int mid = (left + right) / 2;
                (check(mid) ? left : right) = mid;
            }
            ans = max(ans, left);
        }
        return ans;
    }
};

作者：灵茶山艾府
链接：https://leetcode.cn/problems/maximum-number-of-alloys/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```