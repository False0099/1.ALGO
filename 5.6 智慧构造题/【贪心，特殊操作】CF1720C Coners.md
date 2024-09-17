# Corners

## 题面翻译

有一个由 0 和 1 组成的矩阵。

每次操作可以选择一个 $2\times 2$ 的子矩阵，在这个子矩阵中选择一个 L 形，将这个 L 形里的 3 个数变成 $0$，注意，这个 L 形至少含有一个 1，你想最大化操作个数，问最多操作多少次。

## 题目描述

You are given a matrix consisting of $ n $ rows and $ m $ columns. Each cell of this matrix contains $ 0 $ or $ 1 $ .

Let's call a square of size $ 2 \times 2 $ without one corner cell an L-shape figure. In one operation you can take one L-shape figure, with at least one cell containing $ 1 $ and replace all numbers in it with zeroes.

Find the maximum number of operations that you can do with the given matrix.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \leq t \leq 500 $ ) — the number of test cases. Then follow the descriptions of each test case.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 2 \leq n, m \leq 500 $ ) — the size of the matrix.

Each of the following $ n $ lines contains a binary string of length $ m $ — the description of the matrix.

It is guaranteed that the sum of $ n $ and the sum of $ m $ over all test cases does not exceed $ 1000 $ .

## 输出格式

For each test case output the maximum number of operations you can do with the given matrix.

## 样例 #1

### 样例输入 #1

```
4
4 3
101
111
011
110
3 4
1110
0111
0111
2 2
00
00
2 2
11
11
```

### 样例输出 #1

```
8
9
0
2
```

## 提示

In the first testcase one of the optimal sequences of operations is the following (bold font shows l-shape figure on which operation was performed):

- Matrix before any operation was performed:  101111011110
- Matrix after $ 1 $ operation was performed:  100101011110
- Matrix after $ 2 $ operations were performed:  100100011110
- Matrix after $ 3 $ operations were performed:  100100010110
- Matrix after $ 4 $ operations were performed:  100000010110
- Matrix after $ 5 $ operations were performed:  100000010100
- Matrix after $ 6 $ operations were performed:  100000000100
- Matrix after $ 7 $ operations were performed:  000000000100
- Matrix after $ 8 $ operations were performed:  000000000000

In the third testcase from the sample we can not perform any operation because the matrix doesn't contain any ones.

In the fourth testcase it does not matter which L-shape figure we pick in our first operation. We will always be left with single one. So we will perform $ 2 $ operations.

## 题解
我们这一题关键在于找到我们的贪心构造思路。我们除了第一次以外，希望尽可能的少去减我们的数，因此，我们的关键就是我们的第一次操作会消除掉多少个 1，如果第一次我们会消除掉 2 个 1，那么我们最后的次数就是 1 的总个数减去我们的操作数。
```cpp
#include <iostream>
#include <cstdio>
#define endl putchar('\n')
using namespace std;
void fastio()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
}
const int N = 505;
int a[N][N];
void solve()
{
	int n, m, sum = 0, minn = 114514;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			char x;
			cin >> x;
			a[i][j] = (x == '1'), sum += a[i][j]; //sum 统计 1 的个数
		}
	for (int i = 2; i <= n; i++)
		for (int j = 2; j <= m; j++)
		{
            //cnt 表示 2*2 方格内有多少个 1
			int cnt = a[i-1][j-1] + a[i-1][j] + a[i][j-1] + a[i][j];
			if (cnt == 0) continue;             //没有 1 说明无法构成 L 型
			if (cnt == 1) minn = min(minn, 1);  //一个 1 最少也要包含这个 1 否则不合法
			if (cnt == 2) minn = min(minn, 1);  //两个 1 仍然可以使 L 只覆盖一个 1
			if (cnt == 3) minn = min(minn, 2);  //三个 1 显然必须覆盖两个
			if (cnt == 4) minn = min(minn, 3);  //四个 1 明显覆盖 3 个
		}
	if (minn == 114514) {cout << 0 << '\n'; return;} //如果一个 L 都没法覆盖，就是 0
	cout << sum - minn + 1 << '\n';	 //否则，第一次用 1 个 L，之后每次消耗 (sum - minn) 个 1，共 (sum - minn + 1) 个 L
}
int main()
{
	fastio();
	int T;
	cin >> T;
	while (T--) solve();
	return 0;
}
```