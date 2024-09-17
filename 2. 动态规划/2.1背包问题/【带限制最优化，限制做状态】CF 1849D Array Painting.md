# Array Painting

## 题面翻译

有一个长度为 $n$ 的数组 $a$，满足 $\forall a_i\in\{0,1,2\}$，一开始所有元素均为蓝色。

可以有如下操作：

- 用一枚硬币，把一个蓝色元素涂成红色；

- 选择一个不等于 $0$ 的红色元素和一个与其相邻的蓝色元素，将所选的红色元素减少 $1$，并将所选的蓝色元素涂成红色。

要将所有元素涂红，最少需要多少硬币？

## 题目描述

You are given an array of $ n $ integers, where each integer is either $ 0 $ , $ 1 $ , or $ 2 $ . Initially, each element of the array is blue.

Your goal is to paint each element of the array red. In order to do so, you can perform operations of two types:

- Pay one coin to choose a blue element and paint it red;
- Choose a red element which is not equal to $ 0 $ and a blue element adjacent to it, decrease the chosen red element by $ 1 $ , and paint the chosen blue element red.

What is the minimum number of coins you have to spend to achieve your goal?

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 2 $ ).

## 输出格式

Print one integer — the minimum number of coins you have to spend in order to paint all elements red.

## 样例 #1

### 样例输入 #1

```
3
0 2 0
```

### 样例输出 #1

```
1
```

## 样例 #2

### 样例输入 #2

```
4
0 0 1 1
```

### 样例输出 #2

```
2
```

## 样例 #3

### 样例输入 #3

```
7
0 1 0 0 1 0 2
```

### 样例输出 #3

```
4
```

## 提示

In the first example, you can paint all elements red with having to spend only one coin as follows:

1. Paint the $ 2 $ -nd element red by spending one coin;
2. Decrease the $ 2 $ -nd element by $ 1 $ and paint the $ 1 $ -st element red;
3. Decrease the $ 2 $ -nd element by $ 1 $ and paint the $ 3 $ -rd element red.

In the second example, you can paint all elements red spending only two coins as follows:

1. Paint the $ 4 $ -th element red by spending one coin;
2. Decrease the $ 4 $ -th element by $ 1 $ and paint the $ 3 $ -rd element red;
3. Paint the $ 1 $ -st element red by spending one coin;
4. Decrease the $ 3 $ -rd element by $ 1 $ and paint the $ 2 $ -nd element red.

## 题解
这里，我们消除后效性的方法是：**记录我们上一个格子的代价是多少**，因为我们我们通过我们的当前位置的花费，和我们的上一个格子的花费，两者结合能唯一的求出我们的对应的地址。这一种思想在我们的[[长期项目/1.算法题目/3. 高级数据结构/2.3.树状数组/统计种类/洛谷 P4113 采花|洛谷 P4113 采花]]中，也是有着类似的思想。


就一个很显然的 dp。设 $dp_{i,j}$ 为涂完前 $i$ 格，涂完后最后一格为 $j$ 的最小代价。假设前面都涂完了，那么最后一格只有两种方
 法涂上，一种是自己花钱涂，一种是找前面的匀一点。那么有转移：

$$
dp_{i,a_i}\leftarrow\min(dp_{i-1,0}+1,dp_{i-1,1},dp_{i-1,2})
$$

当然还有一种可能，就是先涂完自己这一格，再往前匀一点。在这种情况下，一次涂色最多能影响到的长度为：这个位置往前最长连续正数段的长度 +1 ,你可以理解为一个类似于多米诺骨牌的过程。涂完这一段后，再往前的段与后面都没关系了，因为两边中间隔着一个 0, 想匀也没法匀。预处理出每个位置 $i$ 前最后出现的 0 的位置，设为 $pre_i$,有转移：

$$
dp_{i,a_i-1}\leftarrow\min(dp_{pre_i-1,0},dp_{pre_i-1,1},dp_{pre_i-1,2})+1
$$

那么就做完了。时间复杂度 $O(n)$,写法应该是最简洁的。

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int MAXN = 2e5 + 10;
 
int n, a[MAXN], dp[MAXN][3], pre[MAXN];
 
int main() {
	scanf("%d", &n), memset(dp, 0x3f, sizeof dp), dp[0][0] = dp[0][1] = dp[0][2] = 0;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]); dp[1][a[1]] = 1;
	for (int i = 1; i <= n; i++) pre[i] = a[i] ? pre[i - 1] : i;
	for (int i = 2, j; i <= n; i++) {
		dp[i][a[i]] = min({ dp[i - 1][0] + 1, dp[i - 1][1], dp[i - 1][2] });
		if (a[i]) dp[i][a[i] - 1] = min({ dp[pre[i] - 1][0], dp[pre[i] - 1][1], dp[pre[i] - 1][2] }) + 1;
	}
	printf("%d", min({ dp[n][0], dp[n][1], dp[n][2] }));
}
```