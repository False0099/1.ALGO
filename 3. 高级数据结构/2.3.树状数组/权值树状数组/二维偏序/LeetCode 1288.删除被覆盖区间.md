给你一个区间列表，请你删除列表中被其他区间所覆盖的区间。

只有当 `c <= a` 且 `b <= d` 时，我们才认为区间 `[a,b)` 被区间 `[c,d)` 覆盖。

在完成所有删除操作后，请你返回列表中剩余区间的数目。

**示例：**

**输入：**intervals = [[1,4],[3,6],[2,8]]
**输出：**2
**解释：**区间 [3,6] 被区间 [2,8] 覆盖，所以它被删除了。

**提示：**​​​​​​

- `1 <= intervals.length <= 1000`
- `0 <= intervals[i][0] < intervals[i][1] <= 10^5`
- 对于所有的 `i != j`：`intervals[i] != intervals[j]`

## 题解
我们这一题本质上就是求我们的一个二维偏序，然后问我们逆序对数量有多少个，而我们甚至不需要用到我们的逆序对，我们只需要判断我们新一条线段的右端点是否已经超过了哦我们的最大的右端点，如果有，我们就认为没有重合，否则，我们认为有重合
```cpp
class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();
        sort(intervals.begin(), intervals.end(), [](const vector<int>& u, const vector<int>& v) {
            return u[0] < v[0] || (u[0] == v[0] && u[1] > v[1]);
        });
        int ans = n;
        int rmax = intervals[0][1];
        for (int i = 1; i < n; ++i) {
            if (intervals[i][1] <= rmax) {
                --ans;
            }
            else {
                rmax = max(rmax, intervals[i][1]);
            }
        }
        return ans;
    }
};

作者：力扣官方题解
链接：https://leetcode.cn/problems/remove-covered-intervals/solutions/101727/shan-chu-bei-fu-gai-qu-jian-by-leetcode-solution/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```