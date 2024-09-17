# 
## 题目描述

给你一个下标从 **0** 开始的整数数组 `nums` 和一个整数 `k` 。

如果子数组中所有元素都相等，则认为子数组是一个 **等值子数组** 。注意，空数组是 **等值子数组** 。

从 `nums` 中删除最多 `k` 个元素后，返回可能的最长等值子数组的长度。

**子数组** 是数组中一个连续且可能为空的元素序列。

## 样例 #1

**输入：**nums = [1,3,2,3,1,3], k = 3
**输出：**3
**解释：**最优的方案是删除下标 2 和下标 4 的元素。
删除后，nums 等于 [1, 3, 3, 3] 。
最长等值子数组从 i = 1 开始到 j = 3 结束，长度等于 3 。
可以证明无法创建更长的等值子数组。

## 题解
我们可以先用一个set来记录每一个数字出现的位置，然后对于每一个数字，我们记相邻两数之间的距离为d，如果我们要让他们两个变得相邻，就要花费$d$个代价。

为了不使用DP，我们考虑这样一种策略，我们枚举结果的右端点，并由右端点推导，这个端点往前最远能达到的位置。

但这样的计算是低效的，为了优化我们可以采用双指针的思路，一个指针指向右端点，另一个指针指向左端点。如果现在我们的花费是比我们的代价要高的，我们就把左指针右移。反之，我们就右指针左移。以此，我们可以记录每个数的代价，然后再对所有的数取max即可。

## 代码
```cpp
class Solution { public: int longestEqualSubarray(vector<int> &nums, int k) { int n = nums.size(), ans = 0; vector<vector<int>> pos(n + 1); for (int i = 0; i < n; i++) pos[nums[i]].push_back(i - pos[nums[i]].size()); for (auto &ps: pos) { int left = 0; for (int right = 0; right < ps.size(); right++) { while (ps[right] - ps[left] > k) // 要删除的数太多了 left++; ans = max(ans, right - left + 1); } } return ans; } }; 作者：灵茶山艾府 链接：https://leetcode.cn/problems/find-the-longest-equal-subarray/solutions/2396401/fen-zu-shuang-zhi-zhen-pythonjavacgo-by-lqqau/ 来源：力扣（LeetCode） 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```