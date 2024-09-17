# Packets

## 题面翻译

你有 $n$ 个硬币，每个硬币价值都为 $1$。

你要把它们分成若干个小包裹，使得在 $1$ 与 $n$ 之间的所有面额都能用这其中某几个小包裹凑出。

每个小包裹只能作为一个整体使用。

请求出最少要分几个包裹。

### 输入格式：

一个数 $n$ ($1\le n\le 10^9$)。

### 输出格式：

输出最少要分几个包裹。

### 样例解释 1：

分成 $3$ 个包裹：$[1,2,3]$，可以凑出 $1$ 到 $6$ 中所有的面额。

## 题目描述

You have $ n $ coins, each of the same value of $ 1 $ .

Distribute them into packets such that any amount $ x $ ( $ 1 \leq x \leq n $ ) can be formed using some (possibly one or all) number of these packets.

Each packet may only be used entirely or not used at all. No packet may be used more than once in the formation of the single $ x $ , however it may be reused for the formation of other $ x $ 's.

Find the minimum number of packets in such a distribution.

## 输入格式

The only line contains a single integer $ n $ ( $ 1 \leq n \leq 10^9 $ ) — the number of coins you have.

## 输出格式

Output a single integer — the minimum possible number of packets, satisfying the condition above.

## 样例 #1

### 样例输入 #1

```
6
```

### 样例输出 #1

```
3
```

## 样例 #2

### 样例输入 #2

```
2
```

### 样例输出 #2

```
2
```

## 提示

In the first example, three packets with $ 1 $ , $ 2 $ and $ 3 $ coins can be made to get any amount $ x $ ( $ 1\leq x\leq 6 $ ).

- To get $ 1 $ use the packet with $ 1 $ coin.
- To get $ 2 $ use the packet with $ 2 $ coins.
- To get $ 3 $ use the packet with $ 3 $ coins.
- To get $ 4 $ use packets with $ 1 $ and $ 3 $ coins.
- To get $ 5 $ use packets with $ 2 $ and $ 3 $ coins
- To get $ 6 $ use all packets.

In the second example, two packets with $ 1 $ and $ 1 $ coins can be made to get any amount $ x $ ( $ 1\leq x\leq 2 $ ).

## 题解
我们这一题转换成人话就是问：至少用多少个发吗才能量出我们的 $n$ 重量。
这里，我们可以通过我们的一个二进制来进行计算。我们可以通过计算我们的 log 是多少来得出我们的答案。

```cpp
#include<bits/stdc++.h>//万能脑袋
using namespace std;
int n,s;//n就是题中的，s表示到1~2ⁿ的和
int main()
{
	cin>>n;
	for(int i=0;;i++)
	{
		s+=pow(2,i);//每次都加
		if(s>=n)//直到大于n为止
		{
			cout<<i+1;
			break;
		}
		
	}
	return 0;
} 
```