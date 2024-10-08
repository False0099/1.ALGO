你将会获得一系列视频片段，这些片段来自于一项持续时长为 `time` 秒的体育赛事。这些片段可能有所重叠，也可能长度不一。

使用数组 `clips` 描述所有的视频片段，其中 `clips[i] = [starti, endi]` 表示：某个视频片段开始于 `starti` 并于 `endi` 结束。

甚至可以对这些片段自由地再剪辑：

- 例如，片段 `[0, 7]` 可以剪切成 `[0, 1] + [1, 3] + [3, 7]` 三部分。

我们需要将这些片段进行再剪辑，并将剪辑后的内容拼接成覆盖整个运动过程的片段（`[0, time]`）。返回所需片段的最小数目，如果无法完成该任务，则返回 `-1` 。

**示例 1：**

**输入：**clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], time = 10
**输出：**3
**解释：**
选中 [0,2], [8,10], [1,9] 这三个片段。
然后，按下面的方案重制比赛片段：
将 [1,9] 再剪辑为 [1,2] + [2,8] + [8,9] 。
现在手上的片段为 [0,2] + [2,8] + [8,10]，而这些覆盖了整场比赛 [0, 10]。

**示例 2：**

**输入：**clips = [[0,1],[1,2]], time = 5
**输出：**-1
**解释：**
无法只用 [0,1] 和 [1,2] 覆盖 [0,5] 的整个过程。

**示例 3：**

**输入：**clips = [[0,1],[6,8],[0,2],[5,6],[0,4],[0,3],[6,7],[1,3],[4,7],[1,4],[2,5],[2,6],[3,4],[4,5],[5,7],[6,9]], time = 9
**输出：**3
**解释：** 
选取片段 [0,4], [4,7] 和 [6,9] 。

**提示：**

- `1 <= clips.length <= 100`
- `0 <= starti <= endi <= 100`
- `1 <= time <= 100`

## 题解
我们这一类题，和其他的区间调度类问题不同，我们这一类问题要解决的是我们选择最少多少能完全覆盖我们的整个区间。而这一题，我们就可以用我们的贪心思想，先按我们的左端点排序，然后再按我们的右端点排序，然后下一段，我们选择的范围就是尽可能的让我们右端点靠后。
我们对于上面的问题有两种解决方案：
对于每一段选择，我们有 $dp[i]=min(dp[a_{j}])+1,(a_{j}<i\leq b_{j})$,最终我们的答案就是我们的 $dp[time]$

```cpp
class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int time) {
        vector<int> dp(time + 1, INT_MAX - 1);
        dp[0] = 0;
        for (int i = 1; i <= time; i++) {
            for (auto& it : clips) {
                if (it[0] < i && i <= it[1]) {
                    dp[i] = min(dp[i], dp[it[0]] + 1);
                }
            }
        }
        return dp[time] == INT_MAX - 1 ? -1 : dp[time];
    }
};

作者：力扣官方题解
链接：https://leetcode.cn/problems/video-stitching/solutions/458461/shi-pin-pin-jie-by-leetcode-solution/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

第二种：我们可以采用我们的贪心方法：
```cpp
class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int time) {
        vector<int> maxn(time);
        int last = 0, ret = 0, pre = 0;
        for (vector<int>& it : clips) {
            if (it[0] < time) {
                maxn[it[0]] = max(maxn[it[0]], it[1]);
            }
        }
        for (int i = 0; i < time; i++) {
            last = max(last, maxn[i]);
            if (i == last) {
                return -1;
            }
            if (i == pre) {
                ret++;
                pre = last;
            }
        }
        return ret;
    }
};

作者：力扣官方题解
链接：https://leetcode.cn/problems/video-stitching/solutions/458461/shi-pin-pin-jie-by-leetcode-solution/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```