#枚举答案 #中位数 

$n$ cards are placed in a row, where $n$ is an odd number. Each card has numbers written on both sides. On the $i$ -th card, $a_i$ is facing up and $b_i$ is facing down.

Grammy wants to maximize the median of all the numbers that are facing up. In order to achieve this, she can do the following operation **at most once**.

-   Choose an interval $[l,r]$ and flip all the cards in the interval. After flipping the cards, $b_i$ will be facing up and $a_i$ will be facing down for $i \in [l,r]$.

Please help Grammy to calculate the median of all the numbers that are facing up under her optimal strategy.

Recall that the median of a sequence of numbers is the $\frac{n+1}{2}$ \-th largest number in the sequence.

## 输入
**Input**

The first line contains two integers $n$ ($1 \leq n \leq; 3 \cdot 10^5, n \bmod 2 = 1$), denoting the number of cards.

Each of the next $n$ lines contains $2$ integers $a_i,b_i$ ($1 \leq a_i,b_i \leq 10^9$), denoting the initial number that is facing up and the initial number that is facing down for each card.

## 输出
**Output**

Output one integer, denoting the median of all the numbers that are facing up under Grammy's optimal strategy.

## 题解
我们这一题要让我们求我们反转后我们的中位数最大是多少，我们考虑到用我们的二分答案，然后求我们的 $|b_{i}\geq w|-|a_{i}\geq w|$ 的最大子段和，我们的复杂度就是 $n\log a$

```cpp
const int maxn = 300010;
const int mod = 998244353;
int n, m, q;
int a[maxn], b[maxn];
int x, y;
int suf[maxn];
bool check(int x) {
    suf[n-1] = a[n-1] >= x;
    for (int i = n - 2; i >= 0; --i) {
        suf[i] = suf[i+1] + (a[i] >= x);//求$a[i]中大于x的后缀和$
    }
    // pre 维护 当前只取ai, >=x的个数
    // cur 维护 当前元素取bi,前面任意取，>=x的最大个数
    // lst 维护 前一个元素取bi, >=x的最大个数 
    int pre = 0, cur = 0, lst = 0;
    int res = suf[0]; // res 维护>=x最大个数；初始值 取不翻转的情况 
    for (int i = 0; i < n; ++i) {
        // cur的更新有2种情况：
        // 1) 前一个元素做了翻转,用b 
        // 2) 前一个元素用a
        cur = max(lst, pre) + (b[i] >= x);//求一个两种情况的最大值
        pre += (a[i] >= x);
        lst = cur;
        // 更新最大值
        // cur + suf[i+1] 表示  翻转区间右边界为i时的最大值 
        res = max(res, cur + suf[i+1]);
    }
    // >=x的个数有 一半以上，说明中间值可以取到x 
    return res >= (n + 1) / 2; 

}
void solve() { 
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &a[i], &b[i]);
    }
    int l = 1, r = 1e9, res = -1, mid;
    while (l <= r) {
        mid = (l + r) / 2;
        if (check(mid)) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    printf("%d\n", res);
}
```