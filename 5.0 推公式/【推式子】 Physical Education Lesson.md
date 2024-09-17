# Physical Education Lesson

## 题目描述

In a well-known school, a physical education lesson took place. As usual, everyone was lined up and asked to settle in "the first– $ k $ -th" position.

As is known, settling in "the first– $ k $ -th" position occurs as follows: the first $ k $ people have numbers $ 1, 2, 3, \ldots, k $ , the next $ k - 2 $ people have numbers $ k - 1, k - 2, \ldots, 2 $ , the next $ k $ people have numbers $ 1, 2, 3, \ldots, k $ , and so on. Thus, the settling repeats every $ 2 k - 2 $ positions. Examples of settling are given in the "Note" section.

The boy Vasya constantly forgets everything. For example, he forgot the number $ k $ described above. But he remembers the position he occupied in the line, as well as the number he received during the settling. Help Vasya understand how many natural numbers $ k $ fit under the given constraints.

Note that the settling exists if and only if $ k > 1 $ . In particular, this means that the settling does not exist for $ k = 1 $ .

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases. This is followed by the description of the test cases.

The only line of each test case contains two integers $ n $ and $ x $ ( $ 1 \le x < n \le 10^9 $ ) — Vasya's position in the line and the number Vasya received during the settling.

## 输出格式

For each test case, output a single integer — the number of different $ k $ that fit under the given constraints.

It can be proven that under the given constraints, the answer is finite.

## 样例 #1

### 样例输入 #1

```
5
10 2
3 1
76 4
100 99
1000000000 500000000
```

### 样例输出 #1

```
4
1
9
0
1
```

## 提示

In the first test case, $ k $ equals $ 2, 3, 5, 6 $ are suitable.

An example of settling for these $ k $ :

  $ k $ / № $ 1 $  $ 2 $  $ 3 $  $ 4 $  $ 5 $  $ 6 $  $ 7 $  $ 8 $  $ 9 $  $ 10 $  $ 2 $  $ 1 $  $ 2 $  $ 1 $  $ 2 $  $ 1 $  $ 2 $  $ 1 $  $ 2 $  $ 1 $  $ 2 $  $ 3 $  $ 1 $  $ 2 $  $ 3 $  $ 2 $  $ 1 $  $ 2 $  $ 3 $  $ 2 $  $ 1 $  $ 2 $  $ 5 $  $ 1 $  $ 2 $  $ 3 $  $ 4 $  $ 5 $  $ 4 $  $ 3 $  $ 2 $  $ 1 $  $ 2 $  $ 6 $  $ 1 $  $ 2 $  $ 3 $  $ 4 $  $ 5 $  $ 6 $  $ 5 $  $ 4 $  $ 3 $  $ 2 $  In the second test case, $ k = 2 $ is suitable.

## 题解
我们这一题的一个方法是：通过我们的公式推导得到我们的答案。

所有数字每隔 $2k - 2$ 个位置重复一次。如果计算出男孩瓦夏的数字是 $x$ ，那么它可以出现在 $(2k - 2) \cdot t + x$ 或 $(2k - 2) \cdot t + k + k - x$ 的位置上，对于某个非负数 $t$ 。除了 $x = 1$ 和 $x = k$ 之外，所有的 $x$ 都是如此。 对于这些值，只剩下一个选项。

我们先确定其中一个选项，第二个选项的情况类似。我们需要找出对于某个非负的 $t$ ， $k$ 有多少个不同的值满足等式 $(2k - 2) \cdot t + x = n$ 。不难发现，只有**当且仅当 $n - x$ 能被 $2k - 2$ 整除**时，方程 $(2k - 2) \cdot t + x = n$ 才成立。因此，我们有必要找出数字 $n - x$ 的除数（并且是偶数）。要考虑第二种情况，就必须对数字 $n + x - 2$ 进行类似的处理。解法的复杂性： $O(\sqrt{n})$ 

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int calc(ll n,int l)
{
	l = max(l, 2);
	int res = 0;
	for(int i=1; (ll)i*i<=n; ++i) if(n % i == 0)
	{
		int j = n / i;
		if(i >= 2 * l - 2 && i % 2 == 0)
			++res;
		if(j != i && j >= 2 * l - 2 && j % 2 == 0)
			++res;
	}
	return res;
}

void solve(void)
{
	ll n,x;
	scanf("%lld%lld",&n,&x);
	
	ll ans = 0;
	ans += calc(n - x, x);
	if(x >= 2)
		ans += calc(n + x - 2, x + 1);
	
	printf("%lld\n",ans);
}

int main(void)
{
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}

```