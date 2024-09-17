一个整数 $\times$ 的强数组指的是满足和为 $\times$ 的二的幂的最短有序数组。比方说，11 的强数组为 $[1,2,8]$ 。
我们将每一个正整数 i (即 1，2,3 等等)的强数组连接得到数组 big_nums, big_nums 开始部分为 $[1,2,\underline{1},\underline{2},\underline{4},\underline{1},\underline{4},\underline{2},\underline{4},\underline{1},\underline{2},\underline{4},\underline{8},\ldots]$。
给你一个二维整数数组 queries ,其中 
$queries[i] = [from _{\mathrm{i}},\mathrm{to}_{\mathrm{i}},\mathrm{mod}_{\mathrm{i}}]$ ,你需要计算 $(big\_nums[from _{\mathrm{i}}]$
$big\_nums[from_i+1]*...*big\_nums[to_i])\%modi$
请你返回一个整数数组 answer,其中 $answer[i]$ 是第 i 个查询的答案。

## 题解
我们本题是一个比较复杂的问题转换，首先我们因为我们的每一个元素都一定是我们的二的倍数，那么我们就可以把我们的原来的问题转换为我们的**区间幂次和**是多少。

现在，我们要求我们的 $[l,r]$ 的区间幂次和是多少，我们可以通过我们的前缀和来计算，我们可以通过计算 $[1,r]$ 的答案是多少，然后再去依次减掉我们的每一个元素的。

之后，我们考虑怎么计算强数组中 $[1,r]$ 的幂次和是多少。我们考虑把我们的 $[1,r]$ 按照我们的分块方法，先把他分成两个部分，首先是 $[1,k]$，其中 $k$ 是某一个整数的最后一个元素，然后是 $[k+1,r]$，这里是我们的第 $k+1$ 个数字的某一些子数字。

这里，我们的 $k$ 可以通过类似于二分枚举的方法来计算，我们首先由：$f(2^k)=k\times(2^{k-1})$，也就是说，我们每一次可以先美剧我们的最高位找到我们的对应的元素是多少。

确定完我们的最高位之后，我们计算**新填一个小数字**，对于我们的原本的答案的贡献是多少，假设我们在某一个更低位添上了 1，在 $n=4$ 的基础上，假设 $n$ 二进制从低到高第 $i=1$ 位填 1, 即 $n=6$,我们来计算相比 $n=4$,1 的个数增加了多少，即 $[4,6-1]$ 中的 1 的个数。由于第 2 位都是 1, 所以增加量是之前填的 1 的个数 (1 个) 乘以 $[4,6-1]$ 中的元素个数 (2 个), 加上低两位，即 $[0,2-1]$ 中的 1 的个数 (1 个) 。现在 1 的个数为 4 $+1\cdot2+1=7\leq k$ ,可以填 1, 现在 $n=6$ 。也就是说，我们在一个新的二进制位上填 1，我们的个数就是：
$f[2^t+2^k]=f[2^t]+2^k\times1+f[2^k]$。

于是，我们就可以通过我们的枚举每一个二进制位填还是不填来找到我们的对应的答案。这个时候，我们假设我们已经知道了我们已经可以分成 $k$ 块，那么我们这个前 $k$ 块的幂次和是多少呢？

这里，我们给出我们的公式，我们的前 $k$ 块的幂次和是我们的 $$\mathrm{sumE}(2^i)=\frac{i(i-1)}2\cdot2^{i-1}$$
```
class Solution {
    int pow(long long x, long long n, long long mod) {
        long long res = 1 % mod;
        for (; n; n /= 2) {
            if (n % 2) {
                res = res * x % mod;
            }
            x = x * x % mod;
        }
        return res;
    }

    long long sum_e(long long k) {
        long long res = 0, n = 0, cnt1 = 0, sumI = 0;
        for (long long i = 63 - __builtin_clzll(k + 1); i; i--) {
            long long c = (cnt1 << i) + (i << (i - 1)); // 新增的幂次个数
            if (c <= k) {
                k -= c;
                res += (sumI << i) + ((i * (i - 1) / 2) << (i - 1));
                sumI += i; // 之前填的 1 的幂次之和
                cnt1++; // 之前填的 1 的个数
                n |= 1LL << i; // 填 1
            }
        }
        // 最低位单独计算
        if (cnt1 <= k) {
            k -= cnt1;
            res += sumI;
            n++; // 填 1
        }
        // 剩余的 k 个幂次，由 n 的低 k 个 1 补充
        while (k--) {
            res += __builtin_ctzll(n);
            n &= n - 1;
        }
        return res;
    }

public:
    vector<int> findProductsOfElements(vector<vector<long long>>& queries) {
        vector<int> ans;
        for (auto& q : queries) {
            auto er = sum_e(q[1] + 1);
            auto el = sum_e(q[0]);
            ans.push_back(pow(2, er - el, q[2]));
        }
        return ans;
    }
};
```