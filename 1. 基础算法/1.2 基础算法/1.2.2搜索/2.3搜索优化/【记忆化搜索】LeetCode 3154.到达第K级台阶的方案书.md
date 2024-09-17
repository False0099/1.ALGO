![[Pasted image 20240521140446.png]]

## 题解
我们注意到，我们本体中显然，类似于我们的走台阶，我们的状态转移相对来说比较单一，从一个状态，最多最多也就转移到我们的另一个新的状态。那么这个时候，我们注意到，我们的各个状态之间就形成了一个**图**。

我们**需要找到这个图中出度为 0**的点，我们显然，可以知道，如果我们的一个点的大小是大于我们的 $k+1$ 的，那么我们是不可能回到我们的对应的状态的。

**于是，我们可以考虑我们从我们的出度为 0 的点**，也就是我们的对应的 $i>k+1$ 的这些点来进行我们的 dp 终点。这个时候，我们只需要在去进行我们的简单计算即可。

```cpp
class Solution {

    unordered_map<long long, int> memo;

    //为什么入口是0，而不是k，这是因为我们的入口是不确定的，我们再k不定的情况下，可能有多个能够走到1的方案

    int dfs(int i, int j, bool preDown, int k) {

        if (i > k + 1) {

            return 0;

        }

        long long p = (long long) i << 32 | j << 1 | preDown; // 用一个 long long 表示状态

        if (memo.contains(p)) { // 之前算过了

            return memo[p];

        }

        int res = i == k;

        res += dfs(i + (1 << j), j + 1, false, k); // 操作二

        if (i && !preDown) {

            res += dfs(i - 1, j, true, k); // 操作一

        }

        return memo[p] = res; // 记忆化

    };

  

public:

    int waysToReachStair(int k) {

        return dfs(1, 0, false, k);

    }

};
```