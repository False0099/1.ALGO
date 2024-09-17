# Wooden Fence

## 题面翻译

给定 $n$ 种木板，每种木板有长度和宽度 $a_i,b_i$。

现在需要从中选一些木板，拼成长度总和为 $l$ 的栅栏，每种木板可以使用无限次。注意你可以将一块木板旋转 $90^\circ$，使其长度和宽度对调，但这不会改变它的种类。

建出的栅栏要求相邻两块木板：

- 种类不能一样
- 前者的长度需等于后者的宽度

请你求出有多少种建栅栏的方案数。答案对 $10^9+7$ 取模。

## 题目描述

Vasya has recently bought some land and decided to surround it with a wooden fence.

He went to a company called "Wooden board" that produces wooden boards for fences. Vasya read in the catalog of products that the company has at its disposal $ n $ different types of wood. The company uses the $ i $ -th type of wood to produce a board of this type that is a rectangular $ a_{i} $ by $ b_{i} $ block.

Vasya decided to order boards in this company and build a fence from them. It turned out that the storehouse of the company is so large that Vasya can order arbitrary number of boards of every type. Note that Vasya is allowed to turn the boards as he builds the fence. However, Vasya cannot turn square boards.

Vasya is required to construct a fence of length $ l $ , however, an arbitrary fence won't do. Vasya wants his fence to look beautiful. We'll say that a fence is beautiful if and only if the following two conditions are fulfilled:

- There are no two successive boards of the same type
- The first board of the fence has an arbitrary length, and the length of each subsequent board equals the width of the previous one

In other words, the fence is considered beautiful, if the type of the $ i $ -th board in the fence is different from the $ i-1 $ -th board's type; besides, the $ i $ -th board's length is equal to the $ i-1 $ -th board's width (for all $ i $ , starting from 2).

Now Vasya wonders, how many variants of arranging a fence for his land exist. Your task is to count the number of different beautiful fences of length $ l $ .

Two fences will be considered the same if the corresponding sequences of fence boards types and rotations are the same, otherwise the fences are different. Since the sought number can be large enough, you need to calculate the answer modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 输入格式

The first line contains two integers $ n $ and $ l $ ( $ 1<=n<=100,1<=l<=3000 $ ) — the number of different board types and the fence length, correspondingly. Next $ n $ lines contain descriptions of board types: the $ i $ -th line contains two integers $ a_{i} $ and $ b_{i} $ ( $ 1<=a_{i}, b_{i}<=100 $ ) — the sizes of the board of the $ i $ -th type. All numbers on the lines are separated by spaces.

## 输出格式

Print a single integer — the sought number of variants modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 样例 #1

### 样例输入 #1

```
2 3
1 2
2 3
```

### 样例输出 #1

```
2
```

## 样例 #2

### 样例输入 #2

```
1 2
2 2
```

### 样例输出 #2

```
1
```

## 样例 #3

### 样例输入 #3

```
6 6
2 1
3 2
2 5
3 3
5 1
2 1
```

### 样例输出 #3

```
20
```

## 提示

In the first sample there are exactly two variants of arranging a beautiful fence of length 3:

- As the first fence board use the board of the first type of length 1 and width 2. As the second board use board of the second type of length 2 and width 3.
- Use one board of the second type after you turn it. That makes its length equal 3, and width — 2.

## 题解
我们本题给定了我们的微观限制：我们的相邻的两个木板的宽度必须是相等的。并且我们的相邻的种类不能相等。

同时还给定了我们的宏观限制：我们的木板的总和必须恰好为 l。


因为我们的微观限制，所以我们就需要记录我们上一块模板是什么类型的。于是我们设 $f[i][j]$ 表示我们现在总长为 i，最后一块木板是 j 的方案数。
我们的转移方程就有：$f[i][j]=f[i-a[j]]\left[ \sum k \right],a_{j}\neq b_{k},c_{j}\neq c_{k}$,

这里我们的转移就要通过枚举我们的上一块的种类来实现。

```cpp
#include<bits/stdc++.h>
#define p 1000000007
#define nb 210
using namespace std;

int ans, n, l, cnt, a[nb], b[nb], c[nb], f[3010][nb];

// f[i][j] = 当前长度为 i, 最后一块木板为 j 的总方案数
// f[i][j] += f[i - a[j]][k] (a[j] = b[k], c[j] != c[k])

int main(){
	cin >> n >> l;
	for(int i = 1; i <= n; i++){
		c[++cnt] = i;
		cin >> a[cnt] >> b[cnt];
		if(a[cnt] != b[cnt]){
			c[++cnt] = i;
			a[cnt] = b[cnt - 1];
			b[cnt] = a[cnt - 1];
			// 如果不是正方形，将其拆成两种木板
			// 但原来的木板种类仍为 i 
		}
	}
	for(int i = 1; i <= l; i++){
		for(int j = 1; j <= cnt; j++){
			for(int k = 0; k <= cnt; k++){
				if(c[j] == c[k]) continue;		// 若种类相同则跳过 
				if(!k && a[j] == i) f[i][j]++;	// k = 0 代表当前已是第一块木板 
				else if(a[j] == b[k] && i > a[j]){
					// 根据限制条件二, a[j] = b[k] 
					f[i][j] = (f[i][j] + f[i - a[j]][k]) % p;
				}
			}
		}
	}
	for(int i = 1; i <= cnt; i++) ans = (ans + f[l][i]) % p;
	cout << ans;
	return 0;
}
```
