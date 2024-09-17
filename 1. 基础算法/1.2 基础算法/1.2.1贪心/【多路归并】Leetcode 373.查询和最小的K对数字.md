给定两个以 **非递减顺序排列** 的整数数组 `nums1` 和 `nums2` , 以及一个整数 `k` 。

定义一对值 `(u,v)`，其中第一个元素来自 `nums1`，第二个元素来自 `nums2` 。

请找到和最小的 `k` 个数对 `(u1,v1)`,  `(u2,v2)`  ...  `(uk,vk)` 。

**示例 1:**

**输入:** nums1 = [1,7,11], nums2 = [2,4,6], k = 3
**输出:** [1,2],[1,4],[1,6]
**解释:** 返回序列中的前 3 对数：
     [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]

**示例 2:**

**输入:** nums1 = [1,1,2], nums2 = [1,2,3], k = 2
**输出:** [1,1],[1,1]
**解释:** 返回序列中的前 2 对数：
     [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]

**示例 3:**

**输入:** nums1 = [1,2], nums2 = [3], k = 3 
**输出:** [1,3],[2,3]
**解释:** 也可能序列中所有的数对都被返回:[1,3],[2,3]

**提示:**

- `1 <= nums1.length, nums2.length <= 105`
- `-109 <= nums1[i], nums2[i] <= 109`
- `nums1` 和 `nums2` 均为升序排列
- `1 <= k <= 104`

## 题解
我们这一题关键在于怎么转换到我们的多路归并模型，多路归并模型有这么几个性质：在这里，我们可以把一路定义为：以 `nums[i]` 为起点的所有元素的和。
具体地说，起始，我们将这 n 个序列的首位元素以而元素放入我们的小根堆中，然后，我们每一次从优先队列中取出堆顶元素，并把这一个元素的下一位放入到我们的优先队列中。
```cpp
class Solution {
public:
    bool flag = true;
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<vector<int>> ans;
        int n = nums1.size(), m = nums2.size();
        if(n > m) { //始终确保nums1为两数组中长度较少的那个
            swap(nums1, nums2);
            swap(m,n);
            flag = false;
        }
        //定义比较规则
        auto cmp = [&](const auto& a, const auto& b){
            return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];
        };
        priority_queue< pair<int,int>, vector<pair<int,int>>, decltype(cmp) > q(cmp);
        for(int i = 0; i < min(n,k); i++){
            q.push( {i, 0} );
        }
        while(ans.size() < k and q.size()){
            auto [a,b] = q.top();
            q.pop();
            flag ? ans.push_back( {nums1[a], nums2[b]}) : ans.push_back( {nums2[b], nums1[a]});
            if(b + 1 < m) q.push( {a, b + 1} );
        }
        return ans;
    }
};

作者：宫水三叶
链接：https://leetcode.cn/problems/find-k-pairs-with-smallest-sums/description/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
