现有一个有向图，其中包含 `n` 个节点，节点编号从 `0` 到 `n - 1` 。此外，该图还包含了 `n` 条有向边。

给你一个下标从 **0** 开始的数组 `edges` ，其中 `edges[i]` 表示存在一条从节点 `i` 到节点 `edges[i]` 的边。

想象在图上发生以下过程：

- 你从节点 `x` 开始，通过边访问其他节点，直到你在 **此过程** 中再次访问到之前已经访问过的节点。

返回数组 `answer` 作为答案，其中 `answer[i]` 表示如果从节点 `i` 开始执行该过程，你可以访问到的不同节点数。

**示例 1：**

![](https://assets.leetcode.com/uploads/2023/08/31/graaphdrawio-1.png)

**输入：**edges = [1,2,0,0]
**输出：**[3,3,3,4]
**解释：**从每个节点开始执行该过程，记录如下：
- 从节点 0 开始，访问节点 0 -> 1 -> 2 -> 0 。访问的不同节点数是 3 。
- 从节点 1 开始，访问节点 1 -> 2 -> 0 -> 1 。访问的不同节点数是 3 。
- 从节点 2 开始，访问节点 2 -> 0 -> 1 -> 2 。访问的不同节点数是 3 。
- 从节点 3 开始，访问节点 3 -> 0 -> 1 -> 2 -> 0 。访问的不同节点数是 4 。

**示例 2：**

![](https://assets.leetcode.com/uploads/2023/08/31/graaph2drawio.png)

**输入：**edges = [1,2,3,4,0]
**输出：**[5,5,5,5,5]
**解释：**无论从哪个节点开始，在这个过程中，都可以访问到图中的每一个节点。

## 题解
我们本题因为有 n 个点，n 个边，所以我们这个图一定是一颗基环树，我们只需要缩点后转换为我们的树上问题即可。
```cpp
class Solution {
public:
    vector<int> countVisitedNodes(vector<int> &g) {
        int n = g.size();
        vector<vector<int>> rg(n); // 反图
        vector<int> deg(n);
        for (int x = 0; x < n; x++) {
            int y = g[x];
            rg[y].push_back(x);
            deg[y]++;
        }

        // 拓扑排序，剪掉 g 上的所有树枝
        // 拓扑排序后，deg 值为 1 的点必定在基环上，为 0 的点必定在树枝上
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (deg[i] == 0) {
                q.push(i);
            }
        }
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            int y = g[x];
            if (--deg[y] == 0) {
                q.push(y);
            }
        }

        vector<int> ans(n, 0);
        // 在反图上遍历树枝
        function<void(int, int)> rdfs = [&](int x, int depth) {
            ans[x] = depth;
            for (int y: rg[x]) {
                if (deg[y] == 0) { // 树枝上的点在拓扑排序后，入度均为 0
                    rdfs(y, depth + 1);
                }
            }
        };
        for (int i = 0; i < n; i++) {
            if (deg[i] <= 0) {
                continue;
            }
            vector<int> ring;
            for (int x = i;; x = g[x]) {
                deg[x] = -1; // 将基环上的点的入度标记为 -1，避免重复访问
                ring.push_back(x); // 收集在基环上的点
                if (g[x] == i) {
                    break;
                }
            }
            for (int x: ring) {
                rdfs(x, ring.size()); // 为方便计算，以 ring.size() 作为初始深度
            }
        }
        return ans;
    }
};

作者：灵茶山艾府
链接：https://leetcode.cn/problems/count-visited-nodes-in-a-directed-graph/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```