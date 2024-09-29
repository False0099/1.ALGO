# Fish

## 题面翻译

题目描述

有 n 条鱼，编号从 1 到 n，住在湖里。每天有一对鱼相遇，

彼此相遇的概率是一样的。如果两条标号为 i 和 j 的鱼见面，第一只吃了第二只的概率为 $a_{i,j}$，第二只会吃了第一只的概率为 $a_{j,i}$ = $1-a_{i,j}$。所描述的过程继续进行，直到湖里只剩下一条鱼。请你算出每只鱼最后存活在湖里的可能性。

输入格式

第一行包含整数 n ( 1<=n<=18)--湖里的鱼数量。接下来 n 行为实数矩阵 a，其中 $a_{i,j}$ 代表相遇时第 i 条鱼吃掉第 j 条的概率。数据保证主对角线上只包含 0，且 $a_{j,i}$ = $1-a_{i,j}$。每个实数小数点后只有6位。

输出格式

输出 n 个六位小数，以空格隔开，其中第 i 个表示第 i 条鱼存活到最后的概率。

## 题目描述

$ n $ fish, numbered from $ 1 $ to $ n $ , live in a lake. Every day right one pair of fish meet, and the probability of each other pair meeting is the same. If two fish with indexes i and j meet, the first will eat up the second with the probability $ a_{ij} $ , and the second will eat up the first with the probability $ a_{ji}=1-a_{ij} $ . The described process goes on until there are at least two fish in the lake. For each fish find out the probability that it will survive to be the last in the lake.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=18 $ ) — the amount of fish in the lake. Then there follow $ n $ lines with $ n $ real numbers each — matrix $ a $ . $ a_{ij} $ ( $ 0<=a_{ij}<=1 $ ) — the probability that fish with index $ i $ eats up fish with index $ j $ . It's guaranteed that the main diagonal contains zeros only, and for other elements the following is true: $ a_{ij}=1-a_{ji} $ . All real numbers are given with not more than 6 characters after the decimal point.

## 输出格式

Output $ n $ space-separated real numbers accurate to not less than 6 decimal places. Number with index $ i $ should be equal to the probability that fish with index $ i $ will survive to be the last in the lake.

## 样例 #1

### 样例输入 #1

```
2
0 0.5
0.5 0
```

### 样例输出 #1

```
0.500000 0.500000
```

## 样例 #2

### 样例输入 #2

```
5
0 1 1 1 1
0 0 0.5 0.5 0.5
0 0.5 0 0.5 0.5
0 0.5 0.5 0 0.5
0 0.5 0.5 0.5 0
```

### 样例输出 #2

```
1.000000 0.000000 0.000000 0.000000 0.000000
```

## 题解
首先，对于 n 条鱼，它们两两相遇（不重复）的方案数显然为 n∗(n−1)/2 。

接着，对于鱼 i 吃掉 鱼 j ，可以分为三个步骤：

1. 鱼 i 与 鱼 j 都在湖里。
    
2. 鱼 i 与 鱼 j 相遇。
    
3. 鱼 i 战胜 鱼 j 。
    

所以鱼 i 吃掉 鱼 j 的概率为P=(P(鱼 i 与 鱼 j 都在湖里)) ∗(P(鱼 i 与 鱼 j 相遇)) ∗(P(鱼 i 战胜 鱼 j ))

设$f[S]$ 为湖中鱼状态为 S 的概率，那么方程就是

$f[S | (1<<j)]$ += $f[S]*$ $a[i][j]$ /(n∗(n−1)/2)$



** 代码**

```cpp
#include<cstdio>

using namespace std;

double f[1<<19];
double a[19][19];
int n,cnt;

int count(int s)
{
	int cnt=0;
	while(s)
	{
		cnt++;s^=s & (-s);
	}
	return cnt;
}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)
	scanf("%lf",&a[i][j]);
	f[(1<<n)-1]=1;
	for(int s=(1<<n)-1;s>0;s--)
	if(f[s])
		for(int i=0;i<n;i++)
		if( (1<<i)&s )
			for(int j=0;j<n;j++)
			if(i!=j && ( (1<<j)&s ))
			{
				cnt=count(s);
				if(cnt>1)
				f[s^(1<<j)]+=f[s]*2*a[i][j]/cnt/(cnt-1);
			}
	for(int i=0;i<n;i++)
	printf("%.6lf ",f[1<<i]);
	return 0;
}
```

---

~~后记（真题面）~~

[![timg.jpg](https://s22.postimg.cc/u39xlhb29/timg.jpg)](https://postimg.cc/image/o2c8oeofx/) [![cc9015ef76c6a7efa56cf50df7faaf51f2de66d0.jpg](https://s22.postimg.cc/jhq29iugx/cc9015ef76c6a7efa56cf50df7faaf51f2de66d0.jpg)](https://postimg.cc/image/vjlg3o3p9/)