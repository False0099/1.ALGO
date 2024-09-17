#LIS 
# [POI 2013] BAJ-Bytecomputer

## 题面翻译

给定一个长度为 $n$ 的只包含 $-1,0,1$ 的数列 $a$，每次操作可以使 $a_i\gets a_i+a_{i-1}$，求最少操作次数使得序列单调不降。如果不可能通过该操作使得序列单调不降，请输出 `BRAK`。

数据范围：$1\le n\le 10^6$。

## 题目描述

A sequence of ![](http://main.edu.pl/images/OI20/baj-en-tex.1.png) integers ![](http://main.edu.pl/images/OI20/baj-en-tex.2.png) from the set ![](http://main.edu.pl/images/OI20/baj-en-tex.3.png) is given.

The bytecomputer is a device that allows the following operation on the sequence:

incrementing ![](http://main.edu.pl/images/OI20/baj-en-tex.4.png) by ![](http://main.edu.pl/images/OI20/baj-en-tex.5.png) for any ![](http://main.edu.pl/images/OI20/baj-en-tex.6.png).

There is no limit on the range of integers the bytecomputer can store, i.e.,    each ![](http://main.edu.pl/images/OI20/baj-en-tex.7.png) can (in principle) have arbitrarily small or large value.

Program the bytecomputer so that it transforms the input sequence into a non-decreasing sequence    (i.e., such that ![](http://main.edu.pl/images/OI20/baj-en-tex.8.png)) with the minimum number of operations.

## 输入格式

The first line of the standard input holds a single integer ![](http://main.edu.pl/images/OI20/baj-en-tex.9.png) (![](http://main.edu.pl/images/OI20/baj-en-tex.10.png)),      the number of elements in the (bytecomputer's) input sequence.

The second line contains ![](http://main.edu.pl/images/OI20/baj-en-tex.11.png) integers ![](http://main.edu.pl/images/OI20/baj-en-tex.12.png) (![](http://main.edu.pl/images/OI20/baj-en-tex.13.png))      that are the successive elements of the (bytecomputer's) input sequence, separated by single spaces.

In tests worth 24% of the total points it holds that ![](http://main.edu.pl/images/OI20/baj-en-tex.14.png),      and in tests worth 48% of the total points it holds that ![](http://main.edu.pl/images/OI20/baj-en-tex.15.png).

## 输出格式

The first and only line of the standard output should give one integer,      the minimum number of operations the bytecomputer has to perform to make its input sequence non-decreasing,      of the single word BRAK (Polish for none) if obtaining such a sequence is impossible.

## 样例 #1

### 样例输入 #1

```
6
-1 1 0 -1 0 1
```

### 样例输出 #1

```
3
```


## 题解
我们本题的思路就是构造 $f[j][i]$ 表示前 j 个数以 i 结尾的最少改变次数。我们显然可以发现，我们**末尾的只可能是我们的 $0,-1,1$** 如果出现比 1 更大的，那么肯定是不优的。

于是我们就可以考虑我们的转移：
我们以 0 表示我们的末尾为 -1，1 表示我们的末尾为 0，2 表示我们的末尾为 1。那么我们的 $f[i][state]$ 就可以转移为：

$f[i][0]=f[i-1][0]+cnt(a[i]\to-1)(if \ a[i-1]=-1)$
$f[i][0]=f[i-1][1]+cnt(a[i]==-1?0:-1)$

```cpp
#include<bits/stdc++.h>
#define ll long long
#define re register
#define pf putchar(' ')
#define pfn putchar('\n')
using namespace std;
char ch1;
template<class T>
inline void rd(T& x) {
	x = 0; bool w = 0;
	ch1 = getchar();
	while (!isdigit(ch1)) { ch1 == '-' && (w = 1), ch1 = getchar(); }
	while (isdigit(ch1)) { x = (x << 1) + (x << 3) + (ch1 & 15), ch1 = getchar(); }
	w && (x = (~x) + 1);
}
template<class T>
inline void wr(T x)
{
	if (x < 0) x = -x, putchar('-');
	if (x < 10) {
		putchar(x + 48);
		return;
	}
	T L = x / 10;
	wr(L);
	putchar(x - ((L << 1) + (L << 3)) + 48);
}
int n,x,f[3]; 
int inf = 1 << 27;
int main()
{
	rd(n); rd(x);
	memset(f, 63, sizeof(f));
	f[x + 1] = 0;
	for (re int i = 2; i <= n; i++)
	{
		rd(x);
		if (x == -1)
		{
			f[1] = inf;
			f[2] += 2;
		}
		else if (x == 0)
		{
			f[1] = min(f[0], f[1]);
			f[0]++;
			f[2]++;
		}
		else
		{
			f[2] = min(f[0], min(f[1], f[2]));
			f[1] = f[0] + 1;
			f[0] += 2;
		}
	}
	int temp = min(f[0], min(f[1], f[2]));
	if (temp >= inf)printf("BRAK");
	else wr(temp);
	return 0;
}
```

