# 知识点
  ## [[动态规划]]
# 题目
 # [USACO 12 MAR]Landscaping S

## 题目背景

*本题与 [2016 年公开赛白金组同名题目](/problem/P2748) 在题意上一致，唯一的差别是数据范围。*

## 题目描述

Farmer John 打算修建一座花园，他需要移动不少泥土。

花园由 $N$ 个花坛组成（$1 \leq N \leq 100$），其中花坛 $i$ 包含 $A_i$ 单位的泥土。FJ 希望花坛 $i$ 包含 $B_i$ 单位的泥土，保证 $0 \leq A_i,B_i \leq 10$。

为了达到这个目标，他可以做这几件事情：

- 购买一单位的泥土，放在指定的花坛中，费用为 $X$。
- 从任意一个花坛中移走一单位泥土，费用为 $Y$。
- 从花坛 $i$ 运送一单位泥土到花坛 $j$，费用为 $Z|i-j|$。

请你帮 FJ 计算移动泥土的最小开销。

## 输入格式

第一行四个整数 $N,X,Y,Z$（$0 \leq X,Y,Z \leq 1000$）。

接下来 $N$ 行，第 $i$ 行两个整数 $A_i,B_i$。

## 输出格式

输出移动泥土的最小开销。

## 样例 #1

### 样例输入 #1

```
4 100 200 1 
1 4 
2 3 
3 2 
4 0
```

### 样例输出 #1

```
210
```

## 提示

按下面的方案，最小花费为 $210$，可以证明不存在开销更小的方案。

- 移除 $4$ 号花坛的一单位泥土，花费 $200$。
- 将 $4$ 号花坛的三单位泥土移到 $1$ 号花坛，花费 $3 \times 3=9$。
- 将 $3$ 号花坛的一单位泥土移到 $2$ 号花坛，花费 $1 \times 1=1$。

# 思路
·对于这一道题，我们首先能观察到，使用一维 dp 是是不可取的，因为你每一次更改前面的状态会使后面的状态也会改变。这违背了 dp 的的基本原则
·其次，我们注意到数据范围是较小的，所以我们可以采用“离散化” 的方法来将原本的泥土离散化，比如原本的泥土数位 1，2，3，4. 我们我们就可以创建一个新数组 a 其中的元素为 1 2 2 3 3 3 4 4 4 4 .
目标数组 1 1 4 5 也可以表示为 b'  1 2 3 3 3 3 4 4 4 4 4 现在我们我们要计算的就是把 a 变为 b 所需要的最小代价，我们就可以在这个基础上设置 $f[i][j]$,表示使得 a 的前 i 项和 b 的前 j 项相同所需要的代价。
·转移方程就可以写成 $f[i][j]=min(f[i][j],f[i][j-1]+X,f[i-1][j]+Y,Z∗abs(ai​−bj​))$,其中 X 表示在前面的 i-1 都相同的前提下，不进行其他操作，只购买一摊匹配的土，Y 表示在前面 j 个都相同的前提下，直接移去不匹配的那一摊土，Z 表示直接将上面的变成和下面匹配，即运输
# AC 代码
```cpp
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[1005],b[1005],an,bn;
int c[1005][1005],X,Y,Z;
signed main(){
	int n;
	cin>>n>>X>>Y>>Z;
	for(int i=1;i<=n;i++){
		int j;
		cin>>j;
		while(j>0){
			a[++an]=i;
			j--;
		}
		cin>>j;
		while(j>0){
			b[++bn]=i;
			j--;
		}
	}
	for(int j=0;j<=bn;j++){
		c[0][j]=j*X;
	}
	for(int i=0;i<=an;i++){
		c[i][0]=i*Y;
	}
	for(int i=1;i<=an;i++){
		for(int j=1;j<=bn;j++){
			c[i][j]=i*Y+j*X;
			c[i][j]=min(c[i][j],c[i][j-1]+X);
			c[i][j]=min(c[i][j],c[i-1][j]+Y);
			c[i][j]=min(c[i][j],c[i-1][j-1]+Z*llabs(a[i]-b[j]));
		}
	}
	cout<<c[an][bn];
	return 0;
}
```
```
# 备注
