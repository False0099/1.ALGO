# Make It Round

## 题面翻译

## 题目描述
给定 $n$ 和 $m$, 我们可以把 $n$ 变为 $n\cdot k(1\leq k\leq m,k∈N^{*})$, 请输出末尾 $0$ 的个数最多的 $n\cdot k$。  
- 例如, $481000$ 比 $1000010$ 末尾 $0$ 的个数更多。
- 如果有多个末尾 $0$ 个数最多的 $n\cdot k$, 则输出其中最大的一个。  
- 如果不存在末尾 $0$ 个数更多的 $n\cdot k$, 则输出 $n\cdot m$。  
## 输入格式
第一行输入一个整数 $t\ (1\leq t \leq 10^4)$, 表示数据组数。  
之后的 $t$ 行，每行包含两个整数 $n$, $m\ (1\leq n,m \leq 10^9)$。

## 输出格式
对于每组数据，输出末尾 $0$ 的个数最多的 $n\cdot k\ (1\leq k\leq m,k∈N^{*})$。  

如果有多个末尾 $0$ 个数最多的 $n\cdot k$, 则输出其中最大的一个。  

如果不存在末尾 $0$ 个数更多的 $n\cdot k$, 则输出 $n\cdot m$。

## 样例解释
在第一组数据中 $n=6,m=11$, 我们无法得到一个末尾有两个 $0$ 的数，因此我们令 $k=10$, 输出 $6\cdot 10=60$。（它的末尾有 $1$ 个 $0$, 且它比 $30$ 更大）  

在第三组数据中 $n=13,m=5$, 所有可能的 $n\cdot k$ 末尾都没有 $0$, 因此我们输出 $n\cdot m=65$。

## 题目描述

Inflation has occurred in Berlandia, so the store needs to change the price of goods.

The current price of good $ n $ is given. It is allowed to increase the price of the good by $ k $ times, with $ 1 \le k \le m $ , k is an integer. Output the roundest possible new price of the good. That is, the one that has the maximum number of zeros at the end.

For example, the number 481000 is more round than the number 1000010 (three zeros at the end of 481000 and only one at the end of 1000010).

If there are several possible variants, output the one in which the new price is maximal.

If it is impossible to get a rounder price, output $ n \cdot m $ (that is, the maximum possible price).

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) —the number of test cases in the test.

Each test case consists of one line.

This line contains two integers: $ n $ and $ m $ ( $ 1 \le n, m \le 10^9 $ ). Where $ n $ is the old price of the good, and the number $ m $ means that you can increase the price $ n $ no more than $ m $ times.

## 输出格式

For each test case, output on a separate line the roundest integer of the form $ n \cdot k $ ( $ 1 \le k \le m $ , $ k $ — an integer).

If there are several possible variants, output the one in which the new price (value $ n \cdot k $ ) is maximal.

If it is impossible to get a more rounded price, output $ n \cdot m $ (that is, the maximum possible price).

## 样例 #1

### 样例输入 #1

```
10
6 11
5 43
13 5
4 16
10050 12345
2 6
4 30
25 10
2 81
1 7
```

### 样例输出 #1

```
60
200
65
60
120600000
10
100
200
100
7
```

## 提示

In the first case $ n = 6 $ , $ m = 11 $ . We cannot get a number with two zeros or more at the end, because we need to increase the price $ 50 $ times, but $ 50 > m = 11 $ . The maximum price multiple of $ 10 $ would be $ 6 \cdot 10 = 60 $ .

In the second case $ n = 5 $ , $ m = 43 $ . The maximum price multiple of $ 100 $ would be $ 5 \cdot 40 = 200 $ .

In the third case, $ n = 13 $ , $ m = 5 $ . All possible new prices will not end in $ 0 $ , then you should output $ n \cdot m = 65 $ .

In the fourth case, you should increase the price $ 15 $ times.

In the fifth case, increase the price $ 12000 $ times.

## 题解
我们这一题的思路就是对我们的 n 进行我们的因式分解，然后如果我们想让我们的末尾 0 尽可能多，我们就要让我们乘除来后我们的 (2* 5 )尽可能多。

我们于是就可以考虑贪心的分解，问我们原始能分解成几个 2，5 相乘，然后让我们的 k 先去补两者差，之后再去尽可能的扩大我们的结果，于是就去诚实，最后再看我们能有最多多少个即可。最后因为我们还要输出我们的最大值，所以我们就还需要去进行我们的一个乘。

```cpp
```cpp
#include<bits/stdc++.h>
#define N 2000005
#define int long long
using namespace std;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')x=10*x+c-'0',c=getchar();
	return x*f;
}
int n,t,m;
signed main()
{
	t=read();
	for(;t;t--)
	{
		n=read(),m=read();
		int x=n,y=m,c10=0,c5=0,c2=0,bs=1,k=1;
		while(!(x%10))x/=10,c10++;
		while(!(x%2))x/=2,c2++;
		while(!(x%5))x/=5,c5++;//分别拆出10 2 5
		while(bs*2<=m&&c5>0){bs*=2;c5--;}
		while(bs*5<=m&&c2>0){bs*=5;c2--;}
		while(bs*10<=m)bs*=10;//先考虑还能不能补0
	   for(int i=2;;i++)if(bs*i>m){
         bs*=(i-1);break;//还能乘一个常数就继续乘
      }
		cout<<bs*n<<"\n";
	}
	return 0; 
}
```
```