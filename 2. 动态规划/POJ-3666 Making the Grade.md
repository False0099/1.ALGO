一条笔直的土路连接着 FJ 农场上的两个田地，但它改变的海拔比 FJ 想要的要多。他的牛不介意爬上或下一个斜坡，但他们不喜欢交替的山丘和山谷。FJ 想要增加和清除道路上的泥土，这样它就变成了一个单调的斜坡(无论是向上倾斜还是向下倾斜)。给你 N 个整数 A1, ... , AN (1 ≤ N ≤ 2,000) 描述海拔(0 ≤ Ai ≤ 1,000,000,000) 在路上 N 个等距的位置，从第一个字段开始，到另一个字段结束。FJ 想把这些高度调整成一个新的序列 B1, . ... , BN 这要么是不增加的，要么是不减少的。由于增加或清除沿路任何位置的污物所需的费用相同，因此修路的总费用为 $| A 1 - B 1| + | A 2 - B 2| + ... + | AN - BN |$ 请计算他的道路分级的最低费用，使它成为一个连续的斜坡。FJ 高兴地告诉你，有符号的32位整数肯定可以用来计算答案。

Input

* Line 1: A single integer: _N_  
* Lines 2.._N_+1: Line _i_+1 contains a single integer elevation: _Ai_

Output

* 第1行：一个整数，它是FJ对其土路进行分级的最小成本，因此它在高程上不会增加或减少。

Sample Input

7
1
3
2
4
5
3
9

Sample Output

3

## 题解
我们这一题中可以知道，我们的可以用我们的 $f[i][0]$ 表示我们从 0-1 变得单调递增的花费是多少，以及我们 $f[i][1]$ 表示我们变得单调递减的最低花费是多少，我们的状态转移就可以转换为

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <limits>
 
using namespace std;
const int maxn = 2005;
 
int N;
int A[maxn], B[maxn];
int dp[maxn];
 
void solve() {
	memcpy(B, A, sizeof(A));
	sort(B, B + N);
	for (int i = 0; i < N; i++) dp[i] = abs(A[0] - B[i]);
	for (int i = 1; i < N; i++) {
		int temp = dp[0];
		for (int j = 0; j < N; j++) {
			dp[j] = (temp = min(temp, dp[j])) + abs(A[i] - B[j]);
		}
	}
	int ans = numeric_limits<int>::max();
	for (int i = 0; i < N; i++) ans = min(dp[i], ans);
	printf("%d\n", ans);
}
 
int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%d", &A[i]);
	solve();
	return 0;
}
```