以数组 `intervals` 表示若干个区间的集合，其中单个区间为 `intervals[i] = [starti, endi]` 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。

**示例 1：**

**输入：**intervals = [[1,3],[2,6],[8,10],[15,18]]
**输出：**[[1,6],[8,10],[15,18]]
**解释：**区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].

**示例 2：**

**输入：**intervals = [[1,4],[4,5]]
**输出：**[[1,5]]
**解释：**区间 [1,4] 和 [4,5] 可被视为重叠区间。

**提示：**

- `1 <= intervals.length <= 104`
- `intervals[i].length == 2`
- `0 <= starti <= endi <= 104`

## 题解
我们区间合并其实和我们的之前的所谓区间调度思路都是一样的，都是先按照我们的末尾节点, 也就是我们的右端点排序后，然后再从小到大的更新我们的新节点，然后每次我们一有新节点，我们直接合并即可。这题和我们的扎气球一样的。

```cpp
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.size() == 0) {
            return {};
        }
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> merged;
        for (int i = 0; i < intervals.size(); ++i) {
            int L = intervals[i][0], R = intervals[i][1];
            if (!merged.size() || merged.back()[1] < L) {
                merged.push_back({L, R});
            }
            else {
                merged.back()[1] = max(merged.back()[1], R);
            }
        }
        return merged;
    }
};

作者：力扣官方题解
链接：https://leetcode.cn/problems/merge-intervals/solutions/203562/he-bing-qu-jian-by-leetcode-solution/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```