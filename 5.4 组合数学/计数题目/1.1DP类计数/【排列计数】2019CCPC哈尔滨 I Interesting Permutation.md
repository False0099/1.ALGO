DreamGrid has an interesting permutation of $1, 2, \dots, n$ denoted by $a_1, a_2, \dots, a_n$. He generates three sequences $f$, $g$ and $h$, all of length $n$, according to the permutation $a$ in the way described below:

-   For each $1 \le i \le n$, $f_i = \max\{a_1, a_2, \dots, a_i \}$;
-   For each $1 \le i \le n$, $g_i = \min\{a_1, a_2, \dots, a_i \}$;
-   For each $1 \le i \le n$, $h_i = f_i - g_i$.

BaoBao has just found the sequence $h$ DreamGrid generates and decides to restore the original permutation. Given the sequence $h$, please help BaoBao calculate the number of different permutations that can generate the sequence $h$. As the answer may be quite large, print the answer modulo $10^9+7$.

**Input**

The input contains multiple cases. The first line of the input contains a single integer $T$ ($1\leq T\leq 20\,000$), the number of cases.

For each case, the first line of the input contains a single integer $n$ ($1 \le n \le 10^5$), the length of the permutation as well as the sequences. The second line contains $n$ integers $h_1, h_2, \dots, h_n$ ($1 \le i \le n, 0 \le h_i \le 10^9$).

It's guaranteed that the sum of $n$ over all cases does not exceed $2\cdot 10^6$.

**Output**

For each case, print a single line containing a single integer, the number of different permutations that can generate the given sequence $h$. Don't forget to print the answer modulo $10^9+7$.

## 题解
我们本题需要一个关键结论：我们可以吧我们的构造数组转换为构造放球方案。

一开始，我们有两个限制，第一个极差一定是 0，第 n 个极差一定是 $n-1$。

其实，我们并不关系最大值和最小值具体是多少，我们**只关心我们的最大值和最小值之前有多少个可用的数**

在我们的第 $i$ 个球之前，如果我们的极差没有改变，那么我们只能放到已经存在的最小球和最大球之间，能放的位置数，就是上一次的极差+1-上一次的球数。

如果极差变大，我们就要放到已经存在的所有球的左边或者右边，我们的答案乘 2.

对于排列计数的问题，可以考虑从第 $i$ 个位置的关于 1 $-i$ 的排列方案转移到第 $i+1$ 个位置关于 $1-i+1$ 的
排列方案。

比如这道 2019 ccpc 哈尔滨的 I 题，假定初始 $a_1=1$,如果 $i->i+1,h_{i+1}>h_i$ ,那么当前第 $i+1$ 个数就只能是最大或最小值，放置最大值就直接基于之前 $1-i$ 放置一个 $Max+d,d$ 为 $h_{i+1}-h_i$ ,或者放置最小值 $Min-d$,, 然后将排列整体向右或向左平移，平移是一对一的映射，平移后方案数不变 (如果一个排列放置 $Max+d$ 或 $Min-d$ 越界，那么他的对称在放置 $Min-d$ 或 $Max+d$ 时也会越界),因此不会影响计数。

首先判断一下 h 数组的合法性，若已判定 h 数组合法：

对于 $h_i>h_{i-1}$,那么第 $i$ 个位置只能作为当前的最大值或者最小值，答案乘以 2，否则，第 $i$ 个位置可以选择放置最大值和最小值之间的可选择的数字，可以理解成插空，假设有 cnt 个可选择的数字，答案乘以 cnt，放置之后 cnt-=1;

同时对于 $h_i>h_{i-1}$ 来说，会新产生 $h_i-h_{i-1}-1$ 的空位，将至加到 cnt 中即可。

```cpp
int sol() {

    cin >> n;

    for(int i = 1; i <= n; i++) cin >> h[i];

    if(h[1] != 0 || h[n] != n-1) return 0;

    ll ans = 1;

    for(int i = 2; i <= n; i++) {

        if(h[i] < h[i-1]) return 0;

        else if(h[i] == h[i-1]) (ans *= h[i-1] + 2 - i) %= mod;

        else (ans *= 2) %= mod;

    }

    return ans;

}
```