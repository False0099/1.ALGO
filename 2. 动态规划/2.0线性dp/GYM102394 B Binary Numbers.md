ZYB 是个聪明人。他正在解决一个关于二进制数的问题。

假设 $a_i$ 是 $a$ 的二进制表示中的 $i$ -th （基于 0 的索引）最小有效位。例如，如果 $a = 2$  则 $a_0=0, a_1=1$ ， $a_i=0$ 为 $i\ge 2$ 。， $a_i=0$ 为 $i\ge 2$ 。定义 $F_k(a,b)$ 为

$$
F_k(a,b)= \begin{cases} F_{k-1}(a,b) + 1 & (a_k = b_k) \\ 0 & (a_k \neq b_k) \end{cases}
$$
 具体地说， $F_{-1}(a, b)=0$ 。

ZYB 有 $N$ 个区间 $[L_1, R_1],\ [L_2, R_2],\ \dots,\ [L_n, R_n]$ ，其中 $L_1=0,\ R_n=2^m-1$ .  和 $\forall i \in [1, n-1]: \: R_i +1 =L_{i+1}$ 。他希望选择 $N$ 个整数 $A_1, A_2, \dots, A_n$ ，以便 $A_i \in [L_i,R_i]$ ，且每个 $i \in [1, n]$ 都，以下条件成立：

$$
\forall k \in [L_i,R_i]: \: F_{m-1}(A_i,k) \geq \max \limits_{1 \le j \le N}\{F_{m-1}(A_j,k)\} 
$$
 序列 $A$ 的值定义为 $V (A)=\prod \limits_{i=1}^n A_i$ 。  .

当然，有多种方法可以选择序列 $A$ 。现在 ZYB 想知道，在他可以选择的所有不同序列中， $V (A)$ 的和是多少。当且仅当 $\exists i \in[1, n]: \: P_i \ne Q_i$ 时，两个序列 $P$ 和 $Q$ 是不同的。由于答案可能很大，他只想知道取模 $100\,000\,007$ 的答案。

## 输入：
**Input**

The input contains multiple cases. The first line of the input contains a single integer $T\ (1 \leq T \leq 100)$, the number of cases.

For each case, the first line of the input contains two integers $m$ ($0 \leq m \leq 17$) and $N$ ($1 \leq N \leq 2^m$). The following $N$ lines each contains two integers $L_i$ and $R_i \ (0 \le L_i \le R_i &lt; 2^m)$.

It's guaranteed that the sum of $2^m$ over all cases doesn't exceed $2^{18}$.

## 输出：
**Output**

For each case, print a single integer in a single line, the sum of $V(A)$ modulo $100\,000\,007$.

## 题解
我们本题的第一个关键步骤是读懂我们的题意，我们的 $F(a,b)$ 就表示我们的前 $m-1$ 位中，我们的相同的位数有多少。

而我们的题目要求是：给你 N 个区间，每个区间选一个数，要求这个是和区间内的数相同位数是所有数字中最多的。问有多少种方案。

首先，我们需要发现一个性质：如果 $i\geq j\geq k$，那么我们一定有 $f(i,k)\leq f(j,k)$。

然后对于第组，在 1~i-1 组的方向上，在第 1 组的数中，L[i]显然是与 A[i]的值最小的，而且是与 A[i-1]的 f 值最大的。因此如果满足了 f (A[i], L[i])>=f (A[i-1], L[i]),\quad B 么 A[1]到 A[i-1]都满足了题目的限制。I+1~n 组的方向上同理。
 然后就可以发现，第 1 到 i-1 组和第 i+1 到 n 组互不影响，于是就有 dp 性质，考虑用 dp 求解。
 假设 j 所在组为 i。设 dp[i]为选择 j 为 A[i]时，第 1 到 i 组时的答案。
 我们需要找到所有第 i-1 组中能够满足 $f(j,L[i])>=f(A[-1],L[i])$ 且 $f(A[i-1],R[i-1])>=f(j,R[i-1])$ 的 A[i-1], 把这些方案的加起来乘上 j 就是 dp[i]的值了。由于 f 具有单调性，可以用
 双指针维护出这个 A[i-1]的可选区间。


```cpp
#include <cstdio>  
  
using namespace std;  
  
#define  
  
#define  
  
typedef long long LL;  
  
const int p = 100000007;  
  
template <typename T>  
void AddMod(T& x) {  
if (x >= p)  
x -= p;  
}  
template <typename T>  
void SubMod(T& x) {  
if (x < 0)  
x += p;  
}  
  
int m;  
int f(int x, int y) {  
int i;  
for (i = m - 1; i >= 0 && ((x & (1 << i)) == (y & (1 << i))); --i);  
return m - i - 1;  
}  
  
int main() {  
int T;  
static int le[MAXN], ri[MAXN], dp[MAXN];  
  
scanf("%d", &T);  
while (T--) {  
int n;  
scanf("%d%d", &m, &n);  
for (int i = 0; i < n; ++i) {  
scanf("%d%d", le + i, ri + i);  
}  
for (int j = le[0]; j <= ri[0]; ++j) {  
dp[j] = j % p;  
}  
for (int i = 1; i < n; ++i) {  
int sum = 0;  
int up = le[i-1], down = le[i-1];  
int sp = le[i];  
for (int j = ri[i]; j >= le[i]; --j) {  
while (up <= ri[i-1] && f(up, sp) <= f(j, sp)) {  
AddMod(sum += dp[up]);  
++up;  
}  
while (down <= up && f(down, sp-1) < f(j, sp-1)) {  
SubMod(sum -= dp[down]);  
++down;  
}  
dp[j] = (LL)sum * j % p;  
}  
#if  
for (int i = 0; i <= ri[n-1]; ++i) {  
printf("%d ", dp[i]);  
}  
putchar('\n');  
#endif  
}  
int ans = 0;  
for (int i = le[n-1]; i <= ri[n-1]; ++i) {  
AddMod(ans += dp[i]);  
}  
printf("%d\n", ans);  
}  
return 0;  
}
```

