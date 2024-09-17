# Deleting Divisors

## 题面翻译

Alice 和 Bob 正在玩游戏，他们都**绝顶聪明**。

开始时有一个整数 $n$，二者轮流行动，每次行动可以在当前的 $n$ 上减去其一个非 $1$ 非 $n$ 的因子。

若 Alice 先手，某一方无法进行操作则判输，谁会赢呢？

## 题目描述

Alice and Bob are playing a game.

They start with a positive integer $ n $ and take alternating turns doing operations on it. Each turn a player can subtract from $ n $ one of its divisors that isn't $ 1 $ or $ n $ . The player who cannot make a move on his/her turn loses. Alice always moves first.

Note that they subtract a divisor of the current number in each turn.

You are asked to find out who will win the game if both players play optimally.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. Then $ t $ test cases follow.

Each test case contains a single integer $ n $ ( $ 1 \leq n \leq 10^9 $ ) — the initial number.

## 输出格式

For each test case output "Alice" if Alice will win the game or "Bob" if Bob will win, if both players play optimally.

## 样例 #1

### 样例输入 #1

```
4
1
4
12
69
```

### 样例输出 #1

```
Bob
Alice
Alice
Bob
```

## 提示

In the first test case, the game ends immediately because Alice cannot make a move.

In the second test case, Alice can subtract $ 2 $ making $ n = 2 $ , then Bob cannot make a move so Alice wins.

In the third test case, Alice can subtract $ 3 $ so that $ n = 9 $ . Bob's only move is to subtract $ 3 $ and make $ n = 6 $ . Now, Alice can subtract $ 3 $ again and $ n = 3 $ . Then Bob cannot make a move, so Alice wins.

## 题解
我们本题很简单的可以找到我们的最终的结束状态，显然我们有质数和 1 是必败态。那么我们就可以有我们的递推公式暴力递推。
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
bool ans[10000000];
bool solve(int n)
{
	for (int i = 2; i * i <= n; i++)
		if (n % i == 0)
		{
			if (!ans[n - i]) return true;
			if (!ans[n - n / i]) return true;
		}
	return false;
}
int main()
{
	for (int i = 1; i <= 114514; i++)
	{
		ans[i] = solve(i);
		printf("if n = %d : ans = %s\n", i, ans[i] ? "Alice" : "Bob");
		//if (i % 2 == 0 && !ans[i]) printf("ans = %d!\n", i); //这个是题解中"单独打表"的内容
	}
	return 0;
}
```

于是我们就可以通过打表找到我们的规律：我们 $2^{2n+1}$ 次方是必败态，其他都是必胜态。所以我们直接写一个对应的程序即可。
```
#include <iostream>
#include <cstdio>
#include <map>
using namespace std;
map <int, bool> zlt;
bool solve()
{
	int n;
	scanf("%d", &n);
	if (zlt[n]) return false; //可以理解为特判
	return (n % 2 == 0); //奇数就是Bob，偶数就是Alice
}
int main()
{
	zlt[2] = zlt[8] = zlt[32] = zlt[128] = zlt[512] = zlt[2048] = zlt[8192] = zlt[32768] = zlt[131072] = zlt[524288] = zlt[2097152] = zlt[8388608] = zlt[33554432] = zlt[134217728] = zlt[536870912] = true;
	ios::sync_with_stdio(false);
	int T;
	scanf("%d", &T);
	while (T--)
		if (solve()) puts("Alice");
		else puts("Bob");
	return 0;
}
```