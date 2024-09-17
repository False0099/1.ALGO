# 题目
给你一个下标从 0 开始的整数数组 nums 和一个整数 p 。请你从 nums 中找到 p 个下标对，每个下标对对应数值取差值，你需要使得这 p 个差值的最大值最小。同时，你需要确保每个下标在这 p 个下标对中最多出现一次。

对于一个下标对 i 和 j ，这一对的差值为  $$ |nums[i] - nums[j]|$$ ，其中 |x| 表示 x 的绝对值。

请你返回 p 个下标对对应数值最大差值的最小值。


# 思路
·遇到最大的最小或者最小的最大的时候，我们一般都要去考虑二分法去作答，
·我们要求给定 p 下的最大差 x 的关系，我们当然也可以反过来求给定 x 的的情况下 p 的数值。又因为随着 p 的增长 X 只会升不会降，所以我们也完全可以用反函数的方法来解决这一个问题。并且给定 x 再去求 p 是是更加方便的，所以我们就直接求 p 去吧。
·求 p 时，就是在计算是否至少有 $p$ 个数对，它们的最大差值为 $X$ 。因为数对的差值和数所在的位置无关，为了方便下面的说明，我们首先将序列从小到大排个序。为了解决这个转换后的问题，首先注意到一个贪心的结论：一定存在一种选择最多数对的方法，使得每个数对里的两个元素（在排序后的序列里）是相邻的。
有了以上贪心结论，我们只需要考虑相邻的数对即可。在下图中，我们用一条红色的横线表示差值小于等于 X 的相邻数对。
![[Pasted image 20230409143557.png]]
因为数对里每个数至多出现一次，因此重叠的红线会互相影响。重叠的红线形成了一个个区间，不同区间用蓝色竖线进行分隔。可以看到，不同区间的红线不会相互影响，而如果一个区间里有 T 条红线，则最多只能选择 $\frac{t}{2}$
条。

因此，我们只需要求出每个连续的红线区间，并把每个区间的答案加起来，看看总和是否大于等于 P 即可。
# AC 代码
```cpp
class Solution {
public:
    int minimizeMax(vector<int>& nums, int p) {
        // 特殊情况：p == 0
        if (p == 0) return 0;

        int n = nums.size();
        sort(nums.begin(), nums.end());

        // 检验二分出来的答案 LIM
        auto check = [&](int LIM) {
            // cnt 表示当前区间中有几条红线
            // total 表示所有区间一共最多能选几条红线
            int cnt = 0, total = 0;
            for (int i = 0; i + 1 < n; i++) {
                // 相邻数之差符合要求，区间红线数 +1
                if (nums[i + 1] - nums[i] <= LIM) cnt++;
                else {
                    // 相邻数之差不符合要求，计算答案并开启新区间
                    total += (cnt + 1) / 2;
                    cnt = 0;
                }
            }
            // 最后一个区间的答案还没算
            total += (cnt + 1) / 2;
            return total >= p;
        };

        // 二分答案
        int head = 0, tail = nums[n - 1] - nums[0];
        while (head < tail) {
            int mid = (head + tail) >> 1;
            if (check(mid)) tail = mid;
            else head = mid + 1;
        }
        return head;
    }
};

作者：tsreaper
链接：https://leetcode.cn/problems/minimize-the-maximum-difference-of-pairs/solution/er-fen-tan-xin-han-xiang-xi-zheng-ming-b-21b5/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
# 备注
