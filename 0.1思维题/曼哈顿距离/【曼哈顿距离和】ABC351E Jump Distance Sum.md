# [ABC 351 E] Jump Distance Sum

## 题面翻译

>位置 $(x, y)$ 可以一步跳到 $(x+1, y+1)$ 、 $(x+1, y-1)$ 、 $(x-1, y+1)$ 或 $(x-1, y-1)$ 。

$\text{dist}(A, B)$ 定义为从点 $A$ 跳到点 $B$ 所需的最少跳跃次数。

如果经过任意次数的跳跃都无法从点 $A$ 到达点 $B$ ，则设为 $\text{dist}(A, B) = 0$ 。

给定 $N$ 个二维点 $P_1 , P_2, P_3,\dots,P_N$

计算

$$\sum_{i=1}^{N-1}{\sum_{j=i+1}^{N}{\text{dist}(P_i,P_j)}}$$

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc351/tasks/abc351_e

座標平面上に $ N $ 個の点 $ P_1, P_2,\ldots, P_N $ があり、点 $ P_i $ の座標は $ (X_i, Y_i) $ です。  
$ 2 $ つの点 $ A, B $ の距離 $ \text{dist}(A, B) $ を次のように定義します。

> 最初、ウサギが点 $ A $ にいる。  
> $ (x, y) $ にいるウサギは $ (x+1, y+1) $, $ (x+1, y-1) $, $ (x-1, y+1) $, $ (x-1, y-1) $ のいずれかに $ 1 $ 回のジャンプで移動することができる。  
> 点 $ A $ から点 $ B $ まで移動するために必要なジャンプの回数の最小値を $ \text{dist}(A, B) $ として定義する。  
> ただし、何度ジャンプを繰り返しても点 $ A $ から点 $ B $ まで移動できないとき、$ \text{dist}(A, B)=0 $ とする。

$ \displaystyle\sum_{i=1}^{N-1}\displaystyle\sum_{j=i+1}^N\ \text{dist}(P_i, P_j) $ を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ X_1 $ $ Y_1 $ $ X_2 $ $ Y_2 $ $ \vdots $ $ X_N $ $ Y_N $

## 输出格式

$ \displaystyle\sum_{i=1}^{N-1}\displaystyle\sum_{j=i+1}^N\ \text{dist}(P_i, P_j) $ の値を整数で出力せよ。

## 样例 #1

### 样例输入 #1

```
3
0 0
1 3
5 6
```

### 样例输出 #1

```
3
```

## 样例 #2

### 样例输入 #2

```
5
0 5
1 7
2 9
3 8
4 6
```

### 样例输出 #2

```
11
```

## 提示

### 制約

- $ 2\leq\ N\leq\ 2\times\ 10^5 $
- $ 0\leq\ X_i, Y_i\leq\ 10^8 $
- $ i\neq\ j $ ならば $ (X_i, Y_i)\neq\ (X_j, Y_j) $
- 入力はすべて整数

### Sample Explanation 1

$ P_1, P_2, P_3 $ の座標はそれぞれ $ (0,0) $, $ (1,3) $, $ (5,6) $ です。 $ P_1 $ から $ P_2 $ へはウサギは $ (0,0)\to\ (1,1)\to\ (0,2)\to\ (1,3) $ と $ 3 $ 回で移動でき、$ 2 $ 回以下では $ P_1 $ から $ P_2 $ まで移動できないため、 $ \text{dist}(P_1, P_2)=3 $ です。 $ P_1 $ から $ P_3 $ および $ P_2 $ から $ P_3 $ へはウサギは移動できないため、$ \text{dist}(P_1, P_3)=\text{dist}(P_2, P_3)＝0 $ となります。 よって、答えは $ \displaystyle\sum_{i=1}^{2}\displaystyle\sum_{j=i+1}^3\text{dist}(P_i, P_j)=\text{dist}(P_1, P_2)+\text{dist}(P_1, P_3)+\text{dist}(P_2, P_3)=3+0+0=3 $ となります。

## 题解
我们本体考虑到我们**哪些点之间是可达的**，我们不难发现，我们如果两个点是可达的，一定满足**x+y**的奇偶性相同。我们很容易分析出 $\operatorname{dist}((x_i,y_i),(x_j,y_j))=\max(x_i-x_j,y_i-y_j)$,在 $(x_i+y_i)\operatorname{mod}2\neq(x_j+$$y_j)\bmod2$ 时，$\det((x_i,y_i)(x_j,y_j))=0$。

因此，我们就可以把我们的原图先分成两个不相关联的子图，然后再对每一个子图，我们去求我们的一个曼哈顿距离之和是多少。即可完成本题

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, dx[200005], dy[200005];
vector<pair<int, int> > v1, v2;
int solve(vector<pair<int, int> > v) {
	int i;
	vector<int> allx, ally;
	for (i = 0; i < v.size(); i++) {
		allx.push_back(v[i].first);
		ally.push_back(v[i].second);
	}
	sort(allx.begin(), allx.end());
	sort(ally.begin(), ally.end());
	int sum = 0, ret = 0;
	for (i = 0; i < allx.size(); i++) {
		ret += i * allx[i] - sum;
		sum += allx[i];
	}
	sum = 0;
	for (i = 0; i < ally.size(); i++) {
		ret += i * ally[i] - sum;
		sum += ally[i];
	}
	return ret;
}
signed main() {
	int i;
	cin >> n;
	for (i = 0; i < n; i++) {
		cin >> dx[i] >> dy[i];
		if ((dx[i] + dy[i]) & 1) {
			v1.push_back(make_pair(dx[i] + dy[i], dx[i] - dy[i]));
		} else {
			v2.push_back(make_pair(dx[i] + dy[i], dx[i] - dy[i]));
		}
	}
	cout << (solve(v1) + solve(v2)) / 2 << '\n';//应为题目要求i<j所以要除以2
	return 0;
}

```