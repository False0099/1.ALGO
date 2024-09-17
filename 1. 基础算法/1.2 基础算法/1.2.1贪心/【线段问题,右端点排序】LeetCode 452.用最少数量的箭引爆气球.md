有一些球形气球贴在一堵用 XY 平面表示的墙面上。墙面上的气球记录在整数数组 `points` ，其中 `points[i] = [xstart, xend]` 表示水平直径在 `xstart` 和 `xend` 之间的气球。你不知道气球的确切 y 坐标。

一支弓箭可以沿着 x 轴从不同点 **完全垂直** 地射出。在坐标 `x` 处射出一支箭，若有一个气球的直径的开始和结束坐标为 `x` `start`，`x` `end`，且满足  `xstart ≤ x ≤ xend` ，则该气球会被 **引爆** 。可以射出的弓箭的数量 **没有限制** 。弓箭一旦被射出之后，可以无限地前进。

给你一个数组 `points` ，_返回引爆所有气球所必须射出的 **最小** 弓箭数_ 。

 

**示例 1：**

**输入：**points = [[10,16],[2,8],[1,6],[7,12]]
**输出：**2
**解释：**气球可以用2支箭来爆破:
-在x = 6处射出箭，击破气球[2,8]和[1,6]。
-在x = 11处发射箭，击破气球[10,16]和[7,12]。

**示例 2：**

**输入：**points = [[1,2],[3,4],[5,6],[7,8]]
**输出：**4
**解释：**每个气球需要射出一支箭，总共需要4支箭。

**示例 3：**

**输入：**points = [[1,2],[2,3],[3,4],[4,5]]
**输出：**2
解释：气球可以用2支箭来爆破:
- 在x = 2处发射箭，击破气球[1,2]和[2,3]。
- 在x = 4处射出箭，击破气球[3,4]和[4,5]。

**提示:**

- `1 <= points.length <= 105`
- `points[i].length == 2`
- `-231 <= xstart < xend <= 231 - 1`

## 题解
我们这一题的思路就是我们的调度问题相类似，先将我们的区间按照我们的右端点排序，然后我们就在第一个区间的最右端放上一个，这么安排，我们能够覆盖尽可能多的点，尽可能的去覆盖尽可能多的区间。

然后我们再去考虑我们下一个区间和我们规定的上下界是否有∩，如果有，我们就合并并更新我们的∩。反之，我们就新开一个区间。
有点类似于我们的拦截导弹？
```cpp
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.empty()) {
            return 0;
        }
        sort(points.begin(), points.end(), [](const vector<int>& u, const vector<int>& v) {
            return u[1] < v[1];
        });
        int pos = points[0][1];
        int ans = 1;
        for (const vector<int>& balloon: points) {
            if (balloon[0] > pos) {
                pos = balloon[1];
                ++ans;
            }
        }
        return ans;
    }
};

作者：力扣官方题解
链接：https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/solutions/494515/yong-zui-shao-shu-liang-de-jian-yin-bao-qi-qiu-1-2/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```