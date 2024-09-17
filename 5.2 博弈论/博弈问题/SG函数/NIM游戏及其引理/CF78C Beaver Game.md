# Beaver Game

## 题面翻译

两只海狸（Timur and Marsel）做游戏
什么游戏呢？
有 n 条长度为 m 的木棍
从 Timur 开始，每只海狸轮流将一根已有的木棍任意等分
但要保证等分后的每一段长度都是不小于 k 的整数
（m, n，k 为小于等于 1000000000 的正整数）
先无法等分的海狸输
已知 Timur and Marsel, 无比聪明，智商碾压人类（真可怕），这导致他们每一步都最优
那聪明的你，能不能告诉更聪明的评测机，到底谁会获胜呢？
贡献者：HandSome_Colin

## 题目描述

Two beavers, Timur and Marsel, play the following game.

There are $ n $ logs, each of exactly $ m $ meters in length. The beavers move in turns. For each move a beaver chooses a log and gnaws it into some number (more than one) of equal parts, the length of each one is expressed by an integer and is no less than $ k $ meters. Each resulting part is also a log which can be gnawed in future by any beaver. The beaver that can't make a move loses. Thus, the other beaver wins.

Timur makes the first move. The players play in the optimal way. Determine the winner.

## 输入格式

The first line contains three integers $ n $ , $ m $ , $ k $ ( $ 1<=n, m, k<=10^{9} $ ).

## 输出格式

Print "Timur", if Timur wins, or "Marsel", if Marsel wins. You should print everything without the quotes.

## 样例 #1

### 样例输入 #1

```
1 15 4
```

### 样例输出 #1

```
Timur
```

## 样例 #2

### 样例输入 #2

```
4 9 5
```

### 样例输出 #2

```
Marsel
```

## 提示

In the first sample the beavers only have one log, of $ 15 $ meters in length. Timur moves first. The only move he can do is to split the log into $ 3 $ parts each $ 5 $ meters in length. Then Marsel moves but he can't split any of the resulting logs, as $ k=4 $ . Thus, the winner is Timur.

In the second example the beavers have $ 4 $ logs $ 9 $ meters in length. Timur can't split any of them, so that the resulting parts possessed the length of not less than $ 5 $ meters, that's why he loses instantly.

## 题解
我们这一题，有一个常见的就是把我们的长度为 m 的进行等分。

假如我们的棍子有偶数个，那么我们可以进行我们的复读操作，最后，我们的先手玩家一定会输。

假如我们的棍子有奇数个，那么如果我们的先手能一次性把我们的棍子分割成不可再分，那么我们就是先手必胜。

除此之外，我们是后手必胜。

```
#include<bits/stdc++.h>

using namespace std;

inline bool swin(int a,int min)
{
	int k=sqrt(a)+1;
	for(register int i=1;i<k;++i)
	{
		if(a%i!=0)
		{
			continue;
		}
		if(i>=min&&a/i>1)
		{
			return 0;
		}
		else
		{
			if(i>1&&a/i>=min)
			{
				return 0;
			}
		}
	}
	return 1;
}

int main()
{
	ios::sync_with_stdio(0),cin.tie(0);
	int n,m,k;
	cin>>n>>m>>k;
	if(n%2==0)
	{
		cout<<"Marsel";
	}
	else
	{
		if(swin(m,k))
		{
			cout<<"Marsel";
		}
		else
		{
			cout<<"Timur";
		}
	}
}
```