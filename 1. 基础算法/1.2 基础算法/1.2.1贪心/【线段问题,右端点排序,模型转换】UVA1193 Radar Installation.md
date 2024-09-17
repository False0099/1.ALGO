# Radar Installation

## 题面翻译

## 描述：

假设海岸线是一条无限长的直线，陆地位于海岸线的一边，大海位于海岸线的另一边。大海中有许多小岛。某安全部门为了监视这些岛上是否有敌人入侵，打算在海岸线上安装若干个雷达来检测岛屿的情况。每个雷达的覆盖范围是以雷达中心为圆心，半径为 $d$ 的圆形区域。

我们用平面之间坐标系来表示整个区域，海岸线为 $x$ 轴，大海位于 $x$ 轴上方，陆地位于 $x$ 轴下方。为了节约成本，安全部门想使用最少的雷达覆盖所有的岛屿。现在已知每个岛屿的坐标 $(x,y)$ 和雷达的覆盖半径 $d$，你的任务就是计算出能够覆盖所有岛屿的最少雷达数量。

## 输入：

**输入包含若干组数据。**

每组数据的第一行有两个整数 $n(1 \le n \le 1000)$ 和 $d$，分别表示岛屿的数量和雷达的覆盖半径，之后的 $n$ 行，每行有两个整数，表示第 $i$ 个岛屿的坐标 $(x_i,y_i)$。

相邻的两组数据使用一个空行隔开。输入 $\texttt{0 0}$ 表示输入结束。

## 输出：

对于每一组数据的输出格式为 $\texttt{Case i: x}$，表示第 $i$ 组数据中最少需要 $x$ 个雷达来覆盖所有的岛屿；$x=-1$ 表示这组数据无解（无法覆盖所有的岛屿）。

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3634

[PDF](https://uva.onlinejudge.org/external/11/p1193.pdf)

## 输入格式

## 输出格式

## 样例 #1

### 样例输入 #1

```
3 2
1 2
-3 1
2 1

1 2
0 2

0 0
```

### 样例输出 #1

```
Case 1: 2
Case 2: 1
```

## 题解
本题我们的难点之一在于我们的维度是一个二位上的问题，而我们一般的问题都是我们的一维的问题。我们考虑怎么把我们的原来的问题转换为我们的一维问题。

我们对于每一个点，我们计算覆盖这一个岛的雷达应该在的可能的位置在哪里，首先，我们的位置应该满足：这个位置到我们的岛的距离应该小于我们的 d。也就是我们的对应区间是一个圆。

我们对于每一个岛屿都做出这样的圆，最后能够得到如下所示的图形：
![[Pasted image 20240410211610.png]]
然后，我们就需要找到最少的点，使得我们找到的这些点能够覆盖我们的所有圆。因此，我们现在的问题就变成了我们的线段上的经典问题。

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
struct point{
	double l,r;
}a[1005];
int d,bj=0;
bool cmp(const point &x,const point &y){return x.l<y.l;}
void jisuan(int i,double x,double y)
{
	double t=d*d-y*y;
	if(t<0){bj=1;return;}
	a[i].l=x-sqrt(t);
	a[i].r=x+sqrt(t);
}
int main()
{
	int n,t=0;
	while(scanf("%d%d",&n,&d))
	{
		if(n==0&&d==0)break;
		t++;bj=0;
		for(int i=1;i<=n;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			jisuan(i,x,y);
		}
		if(bj==1||d<0)
		{
			printf("Case %d: -1\n",t);
			continue;
		}
		sort(a+1,a+n+1,cmp);
		double pos=-0x7fffffff/2;
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i].l>pos)
			{
				ans++;
				pos=a[i].r;
			}
			else pos=min(pos,a[i].r);
		}
		printf("Case %d: %d\n",t,ans);
	}
	return 0;
}

```