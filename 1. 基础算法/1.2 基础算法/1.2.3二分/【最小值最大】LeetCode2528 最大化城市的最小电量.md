给你一个下标从 **0** 开始长度为 `n` 的整数数组 `stations` ，其中 `stations[i]` 表示第 `i` 座城市的供电站数目。

每个供电站可以在一定 **范围** 内给所有城市提供电力。换句话说，如果给定的范围是 `r` ，在城市 `i` 处的供电站可以给所有满足 `|i - j| <= r` 且 `0 <= i, j <= n - 1` 的城市 `j` 供电。

- `|x|` 表示 `x` 的 **绝对值** 。比方说，`|7 - 5| = 2` ，`|3 - 10| = 7` 。

一座城市的 **电量** 是所有能给它供电的供电站数目。

政府批准了可以额外建造 `k` 座供电站，你需要决定这些供电站分别应该建在哪里，这些供电站与已经存在的供电站有相同的供电范围。

给你两个整数 `r` 和 `k` ，如果以最优策略建造额外的发电站，返回所有城市中，最小电量的最大值是多少。

这 `k` 座供电站可以建在多个城市。

## 题解
显然，我们可以二分答案，然后看我们如果要满足我们的要求，我们需要建造多少发电站，我们建造发电站的时候，我们需要用到我们的**贪心的思想**，我们每一次**从左向右去进行处理**，然后让我们的发电站建立的尽可能靠右。

```
class Solution {

public:

    long long maxPower(vector<int> &stations, int r, int k) {

        int n = stations.size();

        long sum[n + 1], power[n], diff[n];

        sum[0] = 0;

        for (int i = 0; i < n; ++i)

            sum[i + 1] = sum[i] + stations[i]; // 前缀和

        for (int i = 0; i < n; ++i)

            power[i] = sum[min(i + r + 1, n)] - sum[max(i - r, 0)]; // 电量

  

        auto check = [&](long min_power) -> bool {

            memset(diff, 0, sizeof(diff)); // 重置差分数组

            long sum_d = 0, need = 0;

            for (int i = 0; i < n; ++i) {

                sum_d += diff[i]; // 累加差分值

                long m = min_power - power[i] - sum_d;

                if (m > 0) { // 需要 m 个供电站

                    need += m;

                    if (need > k) return false; // 提前退出这样快一些

                    sum_d += m; // 差分更新

                    if (i + r * 2 + 1 < n) diff[i + r * 2 + 1] -= m; // 差分更新

                }

            }

            return true;

        };

  

        long left = *min_element(power, power + n), right = left + k + 1; // 开区间写法

        while (left + 1 < right) {

            long mid = left + (right - left) / 2;

            check(mid) ? left = mid : right = mid;

        }

        return left;

    }

};

```