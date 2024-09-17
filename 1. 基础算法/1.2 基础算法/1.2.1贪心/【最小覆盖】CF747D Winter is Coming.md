# Winter Is Coming

## 题面翻译

你有两种轮胎，雪地胎和普通轮胎。雪地胎可以在任何路况行驶，而普通轮胎只能在不下雪的时候行驶。你现在知道你的雪地胎最多能用 $k$ 天。

现在告诉你总天数 $n$，和每天是否下雪。问你，最少要换几次轮胎，才能保证下雪天都在用雪地胎，并且雪地胎使用天数不超过 $k$ 天。你初始状态是普通轮胎，结束状态无所谓。

翻译贡献者 UID：54900。

## 题目描述

The winter in Berland lasts $ n $ days. For each day we know the forecast for the average air temperature that day.

Vasya has a new set of winter tires which allows him to drive safely no more than $ k $ days at any average air temperature. After $ k $ days of using it (regardless of the temperature of these days) the set of winter tires wears down and cannot be used more. It is not necessary that these $ k $ days form a continuous segment of days.

Before the first winter day Vasya still uses summer tires. It is possible to drive safely on summer tires any number of days when the average air temperature is non-negative. It is impossible to drive on summer tires at days when the average air temperature is negative.

Vasya can change summer tires to winter tires and vice versa at the beginning of any day.

Find the minimum number of times Vasya needs to change summer tires to winter tires and vice versa to drive safely during the winter. At the end of the winter the car can be with any set of tires.

## 输入格式

The first line contains two positive integers $ n $ and $ k $ ( $ 1<=n<=2·10^{5} $ , $ 0<=k<=n $ ) — the number of winter days and the number of days winter tires can be used. It is allowed to drive on winter tires at any temperature, but no more than $ k $ days in total.

The second line contains a sequence of $ n $ integers $ t_{1}, t_{2},..., t_{n} $ ( $ -20<=t_{i}<=20 $ ) — the average air temperature in the $ i $ -th winter day.

## 输出格式

Print the minimum number of times Vasya has to change summer tires to winter tires and vice versa to drive safely during all winter. If it is impossible, print -1.

## 样例 #1

### 样例输入 #1

```
4 3
-5 20 -3 0
```

### 样例输出 #1

```
2
```

## 样例 #2

### 样例输入 #2

```
4 2
-5 20 -3 0
```

### 样例输出 #2

```
4
```

## 样例 #3

### 样例输入 #3

```
10 6
2 -5 1 3 0 0 -4 -3 1 0
```

### 样例输出 #3

```
3
```

## 提示

In the first example before the first winter day Vasya should change summer tires to winter tires, use it for three days, and then change winter tires to summer tires because he can drive safely with the winter tires for just three days. Thus, the total number of tires' changes equals two.

In the second example before the first winter day Vasya should change summer tires to winter tires, and then after the first winter day change winter tires to summer tires. After the second day it is necessary to change summer tires to winter tires again, and after the third day it is necessary to change winter tires to summer tires. Thus, the total number of tires' changes equals four.

## 题解
本题思路为贪心：并且我们本题符合我们额的合并果子模型，我们每一次可以考虑先把我们的每一个需要走雪地的地方都覆盖起来，然后我们每一次就去计算出我们合并两个雪地的最小代价是多少，然后我们再去按照我们的对应方法计算即可。

```cpp
#include<bits/stdc++.h>
#define mn 1111111
using namespace std;
int n,k,i=1,x,l=-1,s,p,q,a[mn];
int main()
{
	for (scanf("%d%d",&n,&k);i<=n;i++) 
	{
		scanf("%d",&x); 
		if (x<0) {if (p) a[++q]=i-p-1; l=p=i; s+=2; k--;}
	}
    //a数组记录两段雪天之间的天数,l记录最后一次雪天
	if (k<0) return puts("-1"),0; sort(a+1,a+1+q);
    //k不足下雪天数直接输出-1		顺便排个序
	for (i=1;i<=q;i++) if (k>=a[i]) k-=a[i],s-=2; else break;
    //贪心
	printf("%d",n-l<=k?s-1:s);
    //如果最后可以一直用雪地胎就保留
}
```