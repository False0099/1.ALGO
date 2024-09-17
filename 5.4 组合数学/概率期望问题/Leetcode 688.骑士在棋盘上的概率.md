在一个 `n x n` 的国际象棋棋盘上，一个骑士从单元格 `(row, column)` 开始，并尝试进行 `k` 次移动。行和列是 **从 0 开始** 的，所以左上单元格是 `(0,0)` ，右下单元格是 `(n - 1, n - 1)` 。

象棋骑士有8种可能的走法，如下图所示。每次移动在基本方向上是两个单元格，然后在正交方向上是一个单元格。

![](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/10/12/knight.png)

每次骑士要移动时，它都会随机从8种可能的移动中选择一种(即使棋子会离开棋盘)，然后移动到那里。

骑士继续移动，直到它走了 `k` 步或离开了棋盘。

返回 _骑士在棋盘停止移动后仍留在棋盘上的概率_ 。

**示例 1：**

**输入:** n = 3, k = 2, row = 0, column = 0
**输出:** 0.0625
**解释:** 有两步(到(1,2)，(2,1))可以让骑士留在棋盘上。
在每一个位置上，也有两种移动可以让骑士留在棋盘上。
骑士留在棋盘上的总概率是0.0625。

**示例 2：**

**输入:** n = 1, k = 0, row = 0, column = 0
**输出:** 1.00000

**提示:**

- `1 <= n <= 25`
- `0 <= k <= 100`
- `0 <= row, column <= n - 1`

## 题解
我们定义我们的 $f[i][j][p]$ 为从位置 $(i,j)$ 出发，使用步数不超过 p 步，最后仍然在棋盘内的概率，我们如果下一步落点 $(nx,ny)$ 仍然在期盼内，那么我们的概率就是我们的 $f[nx][ny][p-1]$,我们的概率之和就是我们的 $f[i][j][p]=\sum f[nx][ny][p-1]\times \frac{1}{8}$
```cpp
class Solution {
public:
    vector<vector<int>> dirs = {{-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}};

    double knightProbability(int n, int k, int row, int column) {
        vector<vector<vector<double>>> dp(k + 1, vector<vector<double>>(n, vector<double>(n)));
        for (int step = 0; step <= k; step++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (step == 0) {
                        dp[step][i][j] = 1;
                    } else {
                        for (auto & dir : dirs) {
                            int ni = i + dir[0], nj = j + dir[1];
                            if (ni >= 0 && ni < n && nj >= 0 && nj < n) {
                                dp[step][i][j] += dp[step - 1][ni][nj] / 8;
                            }
                        }
                    }
                }
            }
        }
        return dp[k][row][column];
    }
};

作者：力扣官方题解
链接：https://leetcode.cn/problems/knight-probability-in-chessboard/solutions/1271325/gong-shui-san-xie-jian-dan-qu-jian-dp-yu-st8l/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```