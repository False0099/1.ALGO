https://leetcode.cn/problems/minimum-cost-to-equalize-array/description/

给你一个整数数组 nums 和两个整数 cost 1 和 cost 2 。你可以执行以下任一操作任意次：
·从 nums 中选择下标 i 并且将 $nums[i]$ 增加 1, 开销为 costl 。
·选择 nums 中两个不同下标 i 和 j ,并且将 $nums[i]$ 和 $nums[j]$ 都增加 1, 开销为 cost 2 。
你的目标是使数组中所有元素都相等，请你返回需要的最小开销之和。由于答案可能会很大，请你将它对 $10^{9}+7$ 取余后返回。


## 题解
我们本题的思想首先是考虑**枚举我们最后转变为哪一个数字**，也就是我们的枚举值域。我们考虑我们最后都变为 $x$ 后，我们的花费的最小代价。

我们考虑分类讨论：
首先，我们如果有第二类的花费 $c_{2}>2*c_{1}$,那么我们直接全部都用 $c_{1}$ 就可以了，这种情况是最不需要讨论的。

其次，如果我们在不满足第一个条件的情况下，我们考虑尽可能多的使用我们的花费二，在不满足条件的情况下再去使用我们的花费一。

这个时候，我们就可以转化为模型：有 $n$ 个桶，第 $i$ 个桶里有 $(g-a_i)$ 个石头，每次你可以花 cost 1 从一个桶里拿走一个石头，或者花 cost 2 从两个桶里分别拿走一个石头。求把石头拿完的最小代价。

我们的**结论**是：
若 $m>s-m$,则最多可以执行 $(s-m)$ 次第二种操作，之后所有石头都只在最多的那个桶里，必须执行 $(m-(s-m))$ 次第一种操作。

若 $m\leq s-m$,则最多可以执行 $\lfloor\frac s2\rfloor$ 次第二种操作，之后如果 $s$ 是奇数那么还会剩下一个石头，执行一次第一种操作即可。

于是，我们可以分别写出上面两个的方法：
$$f(x)=\left\lfloor\frac s2\right\rfloor\cdot c_2+s\bmod2\cdot c_1$$

$$f(x)=(s-d)\cdot c_2+(2d-s)\cdot c_1$$

最后，如果我们希望能更快的计算出我们的答案，我们只需用三分法三分我们的 $x$ 即可。

```
class Solution {
public:
    int minCostToEqualizeArray(vector<int>& nums, int c1, int c2) {
        const int MOD = 1'000'000'007;
        long long n = nums.size();
        auto [m, M] = ranges::minmax(nums);
        long long base = n * M - reduce(nums.begin(), nums.end(), 0LL);
        if (n <= 2 || c1 * 2 <= c2) {
            return base * c1 % MOD;
        }
        auto f = [&](int x) -> long long {
            long long s = base + (x - M) * n;
            int d = x - m;
            if (d * 2 <= s) {
                return s / 2 * c2 + s % 2 * c1;
            }
            return (s - d) * c2 + (d * 2 - s) * c1;
        };

        int i = (n * M - m * 2 - base + n - 3) / (n - 2);
        return i <= M ? min(f(M), f(M + 1)) % MOD :
               min({f(M), f(i - 1), f(i), f(i + 1)}) % MOD;
    }
};

作者：灵茶山艾府
链接：https://leetcode.cn/problems/minimum-cost-to-equalize-array/solutions/2766600/fen-lei-tao-lun-on-zuo-fa-pythonjavacgo-9bsb4/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
