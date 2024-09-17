**在去掉包含的线段后，我们按照某一个端点排序，我们最后得到的所有线段一定是满足二维偏序的**，但是如果我们还需要处理我们的包含的线段应该怎么选择，选大的还是选小的。

给定一个区间的集合 `intervals` ，其中 `intervals[i] = [starti, endi]` 。返回 _需要移除区间的最小数量，使剩余区间互不重叠_ 。

**示例 1:**

**输入:** intervals = [[1,2],[2,3],[3,4],[1,3]]
**输出:** 1
**解释:** 移除 [1,3] 后，剩下的区间没有重叠。

**示例 2:**

**输入:** intervals = [ [1,2], [1,2], [1,2] ]
**输出:** 2
**解释:** 你需要移除两个 [1,2] 来使剩下的区间没有重叠。

**示例 3:**

**输入:** intervals = [ [1,2], [2,3] ]
**输出:** 0
**解释:** 你不需要移除任何区间，因为它们已经是无重叠的了。

**提示:**

- `1 <= intervals.length <= 105`
- `intervals[i].length == 2`
- `-5 * 104 <= starti < endi <= 5 * 104`


## 题解
我们这一题可以通过我们的贪心算法来进行，我们先按照我们的每一个区间的末端点来排序，然后对于末端点靠前的，我们一定先选上，之后如果有一个末端点靠后，但是被这一区间覆盖，那么我们就把那一个删除了。以此类推，我们就可以求出我们的满足条件的最大区域数量是多少。

```cpp
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) {
            return 0;
        }
        
        sort(intervals.begin(), intervals.end(), [](const auto& u, const auto& v) {
            return u[1] < v[1];
        });

        int n = intervals.size();
        int right = intervals[0][1];
        int ans = 1;
        for (int i = 1; i < n; ++i) {
            if (intervals[i][0] >= right) {
                ++ans;
                right = intervals[i][1];
            }
        }
        return n - ans;
    }
};

作者：力扣官方题解
链接：https://leetcode.cn/problems/non-overlapping-intervals/solutions/541543/wu-zhong-die-qu-jian-by-leetcode-solutio-cpsb/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```