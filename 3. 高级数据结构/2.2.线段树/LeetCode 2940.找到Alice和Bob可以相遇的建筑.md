给你一个下标从 **0** 开始的正整数数组 `heights` ，其中 `heights[i]` 表示第 `i` 栋建筑的高度。

如果一个人在建筑 `i` ，且存在 `i < j` 的建筑 `j` 满足 `heights[i] < heights[j]` ，那么这个人可以移动到建筑 `j` 。

给你另外一个数组 `queries` ，其中 `queries[i] = [ai, bi]` 。第 `i` 个查询中，Alice 在建筑 `ai` ，Bob 在建筑 `bi` 。

请你能返回一个数组 `ans` ，其中 `ans[i]` 是第 `i` 个查询中，Alice 和 Bob 可以相遇的 **最左边的建筑** 。如果对于查询 `i` ，Alice 和 Bob 不能相遇，令 `ans[i]` 为 `-1` 。

**示例 1：**

**输入：**heights = [6,4,8,5,2,7], queries = [[0,1],[0,3],[2,4],[3,4],[2,2]]
**输出：**[2,5,-1,5,2]
**解释：**第一个查询中，Alice 和 Bob 可以移动到建筑 2 ，因为 heights[0] < heights[2] 且 heights[1] < heights[2] 。
第二个查询中，Alice 和 Bob 可以移动到建筑 5 ，因为 heights[0] < heights[5] 且 heights[3] < heights[5] 。
第三个查询中，Alice 无法与 Bob 相遇，因为 Alice 不能移动到任何其他建筑。
第四个查询中，Alice 和 Bob 可以移动到建筑 5 ，因为 heights[3] < heights[5] 且 heights[4] < heights[5] 。
第五个查询中，Alice 和 Bob 已经在同一栋建筑中。
对于 ans[i] != -1 ，ans[i] 是 Alice 和 Bob 可以相遇的建筑中最左边建筑的下标。
对于 ans[i] == -1 ，不存在 Alice 和 Bob 可以相遇的建筑。

**示例 2：**

**输入：**heights = [5,3,8,2,6,1,4,6], queries = [[0,7],[3,5],[5,2],[3,0],[1,6]]
**输出：**[7,6,-1,4,6]
**解释：**第一个查询中，Alice 可以直接移动到 Bob 的建筑，因为 heights[0] < heights[7] 。
第二个查询中，Alice 和 Bob 可以移动到建筑 6 ，因为 heights[3] < heights[6] 且 heights[5] < heights[6] 。
第三个查询中，Alice 无法与 Bob 相遇，因为 Bob 不能移动到任何其他建筑。
第四个查询中，Alice 和 Bob 可以移动到建筑 4 ，因为 heights[3] < heights[4] 且 heights[0] < heights[4] 。
第五个查询中，Alice 可以直接移动到 Bob 的建筑，因为 heights[1] < heights[6] 。
对于 ans[i] != -1 ，ans[i] 是 Alice 和 Bob 可以相遇的建筑中最左边建筑的下标。
对于 ans[i] == -1 ，不存在 Alice 和 Bob 可以相遇的建筑。

**提示：**

- `1 <= heights.length <= 5 * 104`
- `1 <= heights[i] <= 109`
- `1 <= queries.length <= 5 * 104`
- `queries[i] = [ai, bi]`
- `0 <= ai, bi <= heights.length - 1`

## 题解
我们每次一需要的是查询大于 $max(h[a],h[b])$ 的**最靠左**的下标，我们正面去计算不太方便，我们考虑**枚举答案**。如果我们的答案是一个合法状态，我们一定满足从我们的 $max(pos[a],pos[b])$,到我们这个位置这一段**区间中，我们的最大值**大于我们的 $max(h[a],h[b])$，这就变成了求一个区间最大值的问题，我们显然可以用我们的树状数组来维护（线段树太难写了），然后我们就可以解决我们的问题了。

```cpp
class Solution {
private:
    vector<int> mx;

    void build(int o, int l, int r, vector<int> &heights) {
        if (l == r) {
            mx[o] = heights[l - 1];
            return;
        }
        int m = (l + r) / 2;
        build(o * 2, l, m, heights);
        build(o * 2 + 1, m + 1, r, heights);
        mx[o] = max(mx[o * 2], mx[o * 2 + 1]);
    }

    // 返回 [L,n] 中 > v 的最小下标（前三个参数表示线段树的节点信息）
    int query(int o, int l, int r, int L, int v) {
        if (v >= mx[o]) { // 最大值 <= v，没法找到 > v 的数
            return 0;
        }
        if (l == r) { // 找到了
            return l;
        }
        int m = (l + r) / 2;
        if (L <= m) {
            int pos = query(o * 2, l, m, L, v); // 递归左子树
            if (pos > 0) { // 找到了
                return pos;
            }
        }
        return query(o * 2 + 1, m + 1, r, L, v); // 递归右子树
    }

public:
    vector<int> leftmostBuildingQueries(vector<int> &heights, vector<vector<int>> &queries) {
        int n = heights.size();
        mx.resize(n * 4);
        build(1, 1, n, heights);

        vector<int> ans;
        for (auto &q : queries) {
            int i = q[0], j = q[1];
            if (i > j) {
                swap(i, j);
            }
            if (i == j || heights[i] < heights[j]) {
                ans.push_back(j);
            } else {
                int pos = query(1, 1, n, j + 1, heights[i]);
                ans.push_back(pos - 1); // 不存在时刚好得到 -1
            }
        }
        return ans;
    }
};

作者：灵茶山艾府
链接：https://leetcode.cn/problems/find-building-where-alice-and-bob-can-meet/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。