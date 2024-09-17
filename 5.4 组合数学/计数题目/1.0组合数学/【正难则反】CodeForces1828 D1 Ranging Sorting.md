**The only difference between this problem and the hard version is the constraints on $t$ and $n$.**

You are given an array $a$, consisting of $n$ distinct integers $a_1, a_2, \ldots, a_n$.

Define the beauty of an array $p_1, p_2, \ldots p_k$ as the minimum amount of time needed to sort this array using an arbitrary number of range-sort operations. In each range-sort operation, you will do the following:

-   Choose two integers $l$ and $r$ ($1 \le l &lt; r \le k$).
-   Sort the subarray $p_l, p_{l + 1}, \ldots, p_r$ in $r - l$ seconds.

Please calculate the sum of beauty over all subarrays of array $a$.

A subarray of an array is defined as a sequence of consecutive elements of the array.

	**Input**

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 5 \cdot 10^3$). The description of the test cases follows.

The first line of each test case contains a single integer $n$ ($1 \le n \le 5 \cdot 10^3$) — the length of the array $a$.

The second line of each test case consists of $n$ integers $a_1,a_2,\ldots, a_n$ ($1\le a_i\le 10^9$). It is guaranteed that all elements of $a$ are pairwise distinct.

It is guaranteed that the sum of $n$ over all test cases does not exceed $5 \cdot 10^3$.

**Output**

For each test case, output the sum of beauty over all subarrays of array $a$.


## 题解
我们这一题采用正男则反，我们先统计所有区间的总长度是多少，然后我们再用我们的总长度减去不需要调整的区间的总长度即可。这里我们可以用我们的双指针，如果一个区间不需要调整，那么等价于我们存在一个 k，对于 l，r，有 $max_{l\leq i\leq k}a_{i}<min_{k<j\leq r}a_{j}$，那么我们一个区间的答案就等于 $r-l$ 再减去我们位置 $k$ 的个数。k 的个数，我们可以通过我们的一个前后缀最大、最小值来计算。

思路：
我们首先考虑每一段对于我们答案的贡献，这个贡献我们可以通过我们 $o(1)$ 的枚举得出