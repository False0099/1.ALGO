#mex 
You are given an **unsorted** permutation $p_1, p_2, \ldots, p_n$. To sort the permutation, you choose a constant $k$ ($k \ge 1$) and do some operations on the permutation. In one operation, you can choose two integers $i$, $j$ ($1 \le j &lt; i \le n$) such that $i - j = k$, then swap $p_i$ and $p_j$.

What is the **maximum** value of $k$ that you can choose to sort the given permutation?

A permutation is an array consisting of $n$ distinct integers from $1$ to $n$ in arbitrary order. For example, $[2, 3, 1, 5, 4]$ is a permutation, but $[1, 2, 2]$ is not a permutation ($2$ appears twice in the array) and $[1, 3, 4]$ is also not a permutation ($n = 3$ but there is $4$ in the array).

An unsorted permutation $p$ is a permutation such that there is at least one position $i$ that satisfies $p_i \ne i$.

**Input**

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.

The first line of each test case contains a single integer $n$ ($2 \le n \le 10^{5}$) — the length of the permutation $p$.

The second line of each test case contains $n$ distinct integers $p_1, p_2, \ldots, p_n$ ($1 \le p_i \le n$) — the permutation $p$. It is guaranteed that the given numbers form a permutation of length $n$ and the given permutation is **unsorted**.

It is guaranteed that the sum of $n$ over all test cases does not exceed $2 \cdot 10^{5}$.

**Output**

For each test case, output the maximum value of $k$ that you can choose to sort the given permutation.

We can show that an answer always exists.

## 题解
我们本题首先要求出我们每一个书的真是位置和他的实际位置之前的差 delta，之后，我们对所有的 delta 求一个 gcd 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define max_n 201010
void read(int &p)
{
    p = 0;
    int k = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
        {
            k = -1;
        }
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        p = p * 10 + c - '0';
        c = getchar();
    }
    p *= k;
    return;
}
void write_(int x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 9)
    {
        write_(x / 10);
    }
    putchar(x % 10 + '0');
}
void writesp(int x)
{
    write_(x);
    putchar(' ');
}
void writeln(int x)
{
    write_(x);
    putchar('\n');
}
int T, n, nums[max_n];
signed main()
{
#if _clang_
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    read(T);
    while (T--)
    {
        read(n);
        for (int i = 1, val; i <= n; i++)
        {
            read(val);
            nums[i] = abs(val - i);
        }
        int ans = __gcd(nums[1], nums[2]);
        for (int i = 3; i <= n; i++)
        {
            ans = __gcd(ans, nums[i]);
        }
        writeln(ans);
    }
    return 0;
}
```