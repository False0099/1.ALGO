给你一个下标从 **0** 开始的数组 `nums` 和一个整数 `target` 。

下标从 **0** 开始的数组 `infinite_nums` 是通过无限地将 nums 的元素追加到自己之后生成的。

请你从 `infinite_nums` 中找出满足 **元素和** 等于 `target` 的 **最短** 子数组，并返回该子数组的长度。如果不存在满足条件的子数组，返回 `-1` 。

**示例 1：**

**输入：**nums = [1,2,3], target = 5
**输出：**2
**解释：**在这个例子中 infinite_nums = [1,2,3,1,2,3,1,2,...] 。
区间 [1,2] 内的子数组的元素和等于 target = 5 ，且长度 length = 2 。
可以证明，当元素和等于目标值 target = 5 时，2 是子数组的最短长度。

**示例 2：**

**输入：**nums = [1,1,1,2,3], target = 4
**输出：**2
**解释：**在这个例子中 infinite_nums = [1,1,1,2,3,1,1,1,2,3,1,1,...].
区间 [4,5] 内的子数组的元素和等于 target = 4 ，且长度 length = 2 。
可以证明，当元素和等于目标值 target = 4 时，2 是子数组的最短长度。

**示例 3：**

**输入：**nums = [2,4,6,8], target = 3
**输出：**-1
**解释：**在这个例子中 infinite_nums = [2,4,6,8,2,4,6,8,...] 。
可以证明，不存在元素和等于目标值 target = 3 的子数组。

## 题解
我们这一题是思维题，首先，我们能否实现，只与我们的目标值模上我们的数组总和相关，这个不妙之能否实现，我们只需要关注我们的后缀和加前缀和是否存在某一段能够让我们实现即可。这里，因为每一个数字都非负，所以我们可以用我们的滑动窗口来解决。
```cpp
class Solution {
public:
    int minSizeSubarray(vector<int> &nums, int target) {
        long long total = accumulate(nums.begin(), nums.end(), 0LL);
        int n = nums.size();
        int ans = INT_MAX;
        int left = 0;
        long long sum = 0;
        for (int right = 0; right < n * 2; right++) {
            sum += nums[right % n];
            while (sum > target % total) {
                sum -= nums[left++ % n];
            }
            if (sum == target % total) {
                ans = min(ans, right - left + 1);
            }
        }
        return ans == INT_MAX ? -1 : ans + target / total * n;
    }
};
```