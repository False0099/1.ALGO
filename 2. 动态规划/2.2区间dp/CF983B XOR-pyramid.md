# XOR-pyramid

## 题面翻译

在一个长度为 $m$ 的数组 $b$ 中定义函数 $f$：

$$
f(b) = \begin{cases} b[1] & \quad \text{if } m = 1 \\ f(b[1] \oplus b[2],b[2] \oplus b[3],\dots,b[m-1] \oplus b[m]) & \quad \text{otherwise,} \end{cases}
$$

例如：

$$
\begin{aligned}
f(1,2,4,8)& = f(1\oplus2,2\oplus4,4\oplus8) \\ &=f(3,6,12)\\&=f(3\oplus6,6\oplus12)\\&=f(5,10)\\&=f(5\oplus10)\\&=f(15)\\&=15
\end{aligned}
$$

现在，有一个长度为 $n$ 的序列 $a$，给了 $q$ 组询问，请计算 $a_l, a_{l+1}, \ldots, a_r$ 的所有连续子序列 $\{b\}$ 中，$f(b)$ 的最大值为多少。

## 题目描述

For an array $ b $ of length $ m $ we define the function $ f $ as

 $  f (b) = \begin{cases} b[1] & \quad \text{if } m = 1 \\ f (b[1] \oplus b[2], b[2] \oplus b[3],\dots, b[m-1] \oplus b[m]) & \quad \text{otherwise,} \end{cases}  $ where $ \oplus $ is [bitwise exclusive OR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

For example, $ f (1,2,4,8)=f (1\oplus 2,2\oplus 4,4\oplus 8)=f (3,6,12)=f (3\oplus 6,6\oplus 12)=f (5,10)=f (5\oplus 10)=f (15)=15 $

You are given an array $ a $ and a few queries. Each query is represented as two integers $ l $ and $ r $ . The answer is the maximum value of $ f $ on all continuous subsegments of the array $ a_l, a_{l+1}, \ldots, a_r $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 5000 $ ) — the length of $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 2^{30}-1 $ ) — the elements of the array.

The third line contains a single integer $ q $ ( $ 1 \le q \le 100\, 000 $ ) — the number of queries.

Each of the next $ q $ lines contains a query represented as two integers $ l $ , $ r $ ( $ 1 \le l \le r \le n $ ).

## 输出格式

Print $ q $ lines — the answers for the queries.

## 样例 #1

### 样例输入 #1

```
3
8 4 1
2
2 3
1 2
```

### 样例输出 #1

```
5
12
```

## 样例 #2

### 样例输入 #2

```
6
1 2 4 8 16 32
4
1 6
2 5
3 4
1 2
```

### 样例输出 #2

```
60
30
12
3
```

## 提示

In first sample in both queries the maximum value of the function is reached on the subsegment that is equal to the whole segment.

In second sample, optimal segment for first query are $ [3,6] $ , for second query — $ [2,5] $ , for third — $ [3,4] $ , for fourth — $ [1,2] $ .


## 题解
递归思想，令 $\mathrm{dp[ 0] [ i] = a[ i] , 令dp[ i] [ j] }$ 为第 i 层递归的第 j 个连续 (i+1) 个数的 f 值，则再将 $dp[i][j]$更新为 $dp[i][j]$, $dp[i-1][j]$、 $dp[i-1][j-1]$ 的最大值。则查找 I-r 的最大值时，只需要输出 $dp[r-1][1-1]$ 即可。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;
const int N = 5100;

int m,n,a[N];
int xor_sum[N][N];

void work_first() {
	for(int i = 2 ; i <= n ; i++) {
		for(int j = i ; j <= n ; j++) {
			xor_sum[i][j] = xor_sum[i - 1][j - 1] ^ xor_sum[i - 1][j];
		}
	}
	for(int i = 1 ; i <= n ; i++) {
		for(int j = i ; j <= n ; j++) {
			int xor_num = max(xor_sum[i - 1][j - 1] , xor_sum[i - 1][j]);
			xor_sum[i][j] = max(xor_sum[i][j] , xor_num);
		}
	}
}
void check_them() {
	scanf("%d",&m);
	for(int i = 1 ; i <= m ; i++) {
		int l,r;
		scanf("%d%d",&l,&r);
		int ans = xor_sum[r - l + 1][r];
		printf("%d\n",ans);
	}
}

int main() {
	freopen("function.in","r",stdin);
	freopen("function.out","w",stdout);
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++) {
		scanf("%d",&a[i]);
		xor_sum[1][i] = a[i];
	}
	work_first();//预处理
	check_them();//查询
	return 0;
}
```