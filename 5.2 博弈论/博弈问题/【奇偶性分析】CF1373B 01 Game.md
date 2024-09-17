# 01 Game

## 题面翻译

**题目大意**

`Alice` 和 `Bob` 在玩游戏。

初始有一个仅由 `01` 构成的字符串。`Alice` 和 `Bob` 轮流进行游戏，`Alice` 先行。轮到某个人的时候，他需要从原串中找到并删除两个相邻且不同的字符（`01` 或 `10`），无法操作者输。

两人都用最优的策略进行，你需要确定谁能够赢得游戏。

**输入格式**

第一行输入一个整数 $t(1\le t \le 1000)$ 表示测试数据的数量。

接下类每组数据输入一个字符串 $s(1\le |s|\le 100),|\sum|=\{'0','1'\}$,表示初始字符串。

**输出格式**

对于每组数据，如果 `Alice` 赢，输出 `DA`,否则输出 `NET`。

## 题目描述

Alica and Bob are playing a game.

Initially they have a binary string $ s $ consisting of only characters 0 and 1.

Alice and Bob make alternating moves: Alice makes the first move, Bob makes the second move, Alice makes the third one, and so on. During each move, the current player must choose two different adjacent characters of string $ s $ and delete them. For example, if $ s =       1011001 $ then the following moves are possible:

1. Delete $ s_1 $ and $ s_2 $ : $ \textbf{10}11001         \rightarrow 11001 $ ;
2. Delete $ s_2 $ and $ s_3 $ : $ 1\textbf{01}1001         \rightarrow 11001 $ ;
3. Delete $ s_4 $ and $ s_5 $ : $ 101\textbf{10}01         \rightarrow 10101 $ ;
4. Delete $ s_6 $ and $ s_7 $ : $ 10110\textbf{01}         \rightarrow 10110 $ .

If a player can't make any move, they lose. Both players play optimally. You have to determine if Alice can win.

## 输入格式

First line contains one integer $ t $ ( $ 1 \le t \le       1000 $ ) — the number of test cases.

Only line of each test case contains one string $ s $ ( $ 1 \le       |s| \le 100 $ ), consisting of only characters 0 and 1.

## 输出格式

For each test case print answer in the single line.

If Alice can win print DA (YES in Russian) in any register. Otherwise print NET (NO in Russian) in any register.

## 样例 #1

### 样例输入 #1

```
3
01
1111
0011
```

### 样例输出 #1

```
DA
NET
NET
```

## 提示

In the first test case after Alice's move string $ s $ become empty and Bob can not make any move.

In the second test case Alice can not make any move initially.

In the third test case after Alice's move string $ s $ turn into $ 01 $ . Then, after Bob's move string $ s $ become empty and Alice can not make any move.

## 题解
我们本体的思路是：发现我们每一步操作的对应的性质。首先，我们每一次操作，都一定是能够让我们的一个 $01$ 变成 $00$.也就是让我们的**交错数列**长度减去 2. 

![[Pasted image 20240508090820.png]]

于是，我们可以统计我们的交错数列的长度是多少，然后除以 2 得到我们可以操作的次数，最后我们就能够得到我们的答案。

```
#include <bits/stdc++.h>

using namespace std;

const int N = 105;

char s[N];
int n, cnt1, cnt0;

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		cnt1 = cnt0 = 0;
		
		scanf("%s", s+1);
		n = strlen(s+1);
		for (int i = 1; i <= n; i++) {
			if (s[i] == '1')
				cnt1++;
			else
				cnt0++;
		}
		
		int cnt = min(cnt1, cnt0);
		if (cnt % 2 == 0) 
			puts("NET");
		else
			puts("DA");
	}
	return 0;
}

```