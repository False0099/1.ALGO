给定一个数组 `trees`，其中 `trees[i] = [xi, yi]` 表示树在花园中的位置。

你被要求用最短长度的绳子把整个花园围起来，因为绳子很贵。只有把 **所有的树都围起来**，花园才围得很好。

返回_恰好位于围栏周边的树木的坐标_。

**示例 1:**

![](https://assets.leetcode.com/uploads/2021/04/24/erect2-plane.jpg)

**输入:** points = [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
**输出:** [[1,1],[2,0],[3,3],[2,4],[4,2]]

**示例 2:**

![](https://assets.leetcode.com/uploads/2021/04/24/erect1-plane.jpg)

**输入:** points = [[1,2],[2,2],[4,2]]
**输出:** [[4,2],[2,2],[1,2]]

**注意:**

- `1 <= points.length <= 3000`
- `points[i].length == 2`
- `0 <= xi, yi <= 100`
- 所有给定的点都是 **唯一** 的。

## 题解
我们这一题是求我们二维凸包的标准例题，我们可以用我们的二维凸包的模板来计算我们的这 n 个点的凸包，

```cpp
class Solution {
public:
    int cross(const vector<int> & p, const vector<int> & q, const vector<int> & r) {
        return (q[0] - p[0]) * (r[1] - q[1]) - (q[1] - p[1]) * (r[0] - q[0]);
    }

    int distance(const vector<int> & p, const vector<int> & q) {
        return (p[0] - q[0]) * (p[0] - q[0]) + (p[1] - q[1]) * (p[1] - q[1]);
    }

    vector<vector<int>> outerTrees(vector<vector<int>> &trees) {
        int n = trees.size();
        if (n < 4) {
            return trees;
        }
        int bottom = 0;
        /* 找到 y 最小的点 bottom*/
        for (int i = 0; i < n; i++) {
            if (trees[i][1] < trees[bottom][1]) {
                bottom = i;
            }
        }
        swap(trees[bottom], trees[0]);
        /* 以 bottom 原点，按照极坐标的角度大小进行排序 */
        sort(trees.begin() + 1, trees.end(), [&](const vector<int> & a, const vector<int> & b) {
            int diff = cross(trees[0], a, b);
            if (diff == 0) {
                return distance(trees[0], a) < distance(trees[0], b);
            } else {
                return diff > 0;
            }
        });
        /* 对于凸包最后且在同一条直线的元素按照距离从大到小进行排序 */
        int r = n - 1;
        while (r >= 0 && cross(trees[0], trees[n - 1], trees[r]) == 0) {
            r--;
        }
        for (int l = r + 1, h = n - 1; l < h; l++, h--) {
            swap(trees[l], trees[h]);
        }
        stack<int> st;
        st.emplace(0);
        st.emplace(1);
        for (int i = 2; i < n; i++) {
            int top = st.top();
            st.pop();
            /* 如果当前元素与栈顶的两个元素构成的向量顺时针旋转，则弹出栈顶元素 */
            while (!st.empty() && cross(trees[st.top()], trees[top], trees[i]) < 0) {
                top = st.top();
                st.pop();
            }
            st.emplace(top);
            st.emplace(i);
        }

        vector<vector<int>> res;
        while (!st.empty()) {
            res.emplace_back(trees[st.top()]);
            st.pop();
        }
        return res;
    }
};

作者：力扣官方题解
链接：https://leetcode.cn/problems/erect-the-fence/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```