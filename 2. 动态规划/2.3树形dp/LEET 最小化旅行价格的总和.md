# 知识点
  ## [[]]
# 题目
 现有一棵无向、无根的树，树中有 n 个节点，按从 0 到 n - 1 编号。给你一个整数 n 和一个长度为 n - 1 的二维整数数组 edges ，其中 $edges[i] = [ai, bi]$ 表示树中节点 ai 和 bi 之间存在一条边。

每个节点都关联一个价格。给你一个整数数组 price ，其中 $price[i]$ 是第 i 个节点的价格。

给定路径的价格总和是该路径上所有节点的价格之和。

另给你一个二维整数数组 trips ，其中 $trips[i] = [starti, endi]$ 表示您从节点 $start_{i}$ 开始第 i 次旅行，并通过任何你喜欢的路径前往节点 $endi$ 。

在执行第一次旅行之前，你可以选择一些*非相邻节点*并将价格减半。

返回执行所有旅行的最小价格总和。
# 思路
·我们发现因为树上两点之间的路径是唯一的，所以我们可以先统计出走完所有路程需要经过的所有的路程的总和，之后我们在按照走过的次数乘以他那个点的本来的权值，就是我们最后哪一个节点的真正权值，然后我们再用这些权值做一个类似于打家劫舍的 DP 即可
# AC 代码
```cpp
class Solution {
public:
    int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
        // 建图
        vector<int> e[n];
        for (auto &edge : edges) {
            e[edge[0]].push_back(edge[1]);
            e[edge[1]].push_back(edge[0]);
        }

        // cnt[i] 表示节点 i 被几次旅行经过
        int cnt[n];
        memset(cnt, 0, sizeof(cnt));
        // 暴力 DFS 找出从根到 goal 的路径
        // 返回值表示节点 sn 是否在从根到 goal 的路径上
        function<bool(int, int, int)> dfs = [&](int sn, int fa, int goal) {//λ表达式
            if (sn == goal) {
                // 找到了 goal
                cnt[sn]++;//
                return true;
            }

            bool ret = false;
            for (int fn : e[sn]) if (fn != fa) {
                bool t = dfs(fn, sn, goal);
                if (t) {
                    ret = true;
                    break;
                }
            }
            // sn 在从根到 goal 的路径上，因此它会被本次旅行经过
            if (ret) cnt[sn]++;
            return ret;
        };
        for (auto &trip : trips) dfs(trip[0], -1, trip[1]);

        // 打家劫舍 III，套用题解中的 DP 方程即可
        long long f[n][2];
        function<void(int, int)> dp = [&](int sn, int fa) {
            f[sn][0] = 0;
            f[sn][1] = 1LL * cnt[sn] * price[sn] / 2;

            for (int fn : e[sn]) if (fn != fa) {
                dp(fn, sn);
                f[sn][0] += max(f[fn][0], f[fn][1]);
                f[sn][1] += f[fn][0];
            }
        };
        dp(0, -1);

        // 统计答案：总费用减去最大节省费用
        long long ans = 0;
        for (int i = 0; i < n; i++) ans += 1LL * cnt[i] * price[i];
        ans -= max(f[0][0], f[0][1]);
        return ans;
    }
};

作者：tsreaper
链接：https://leetcode.cn/problems/minimize-the-total-price-of-the-trips/solution/da-jia-jie-she-iiidfs-or-tarjan-jie-fa-x-iddx/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
# 备注





 