给你一个整数数组 `nums`，和一个整数 `k` 。

对于每个下标 `i`（`0 <= i < nums.length`），将 `nums[i]` 变成 `nums[i] + k` 或 `nums[i] - k` 。

`nums` 的 **分数** 是 `nums` 中最大元素和最小元素的差值。

在更改每个下标对应的值之后，返回 `nums` 的最小 **分数** 。

## 题解
我们本题要求我们的极差最小，我们的一个显然的方法是，贪心的，让我们的一部分变大，再让另一部分变小，这样，我们最后就能够求出来一个合适的极差了。我们枚举我们的分界点是哪里，然后再去进行若干次操作，即可得到我们的答案。
![[Pasted image 20240927141003.png]]

![[Pasted image 20240927141015.png]]

![[Pasted image 20240927141026.png]]

![[Pasted image 20240927141156.png]]

```
class Solution {

public:

    int smallestRangeII(vector<int>& nums, int k) {

        ranges::sort(nums);

        int ans = nums.back() - nums[0];

        for (int i = 1; i < nums.size(); i++) {

            int mx = max(nums[i - 1] + k, nums.back() - k);

            int mn = min(nums[0] + k, nums[i] - k);

            ans = min(ans, mx - mn);

        }

        return ans;

    }

};

  

作者：灵茶山艾府

链接：https://leetcode.cn/problems/smallest-range-ii/solutions/2928780/xiao-de-bian-da-da-de-bian-xiao-pythonja-8fnp/

来源：力扣（LeetCode）

著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```