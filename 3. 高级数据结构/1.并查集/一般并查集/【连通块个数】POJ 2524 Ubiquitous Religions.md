## 描述

当今世界上有许多不同的明星，你想知道你们学校的学生总共喜欢多少个不同的明星。
你知道你的大学里有n个学生(0 < n ≤ 50000)，你问每个学生他们喜欢的明星是不可能的。此外，许多学生不好意思说出他们喜欢哪个明星。避免这些问题的一种方法是问m (0≤ m ≤ n(n-1)/2)对学生，问他们是否喜欢相同的明星(例如，他们可能知道他们是否观看同一场演出)。从这些数据中，你可能不知道每个人具体喜欢哪个明星，但你可以知道校园里最多有多少个不同的被喜欢的明星。你可以假设每个学生最喜欢的只有一个明星。

## 输入

输入由多组用例组成。每一种情况都以整数n和m作为的一行开始，接下来的m行分别由两个整数i和j组成，表示学生i和j喜欢相同的明星。学生被编号为1到n。输入的结束由一行指定，其中n = m = 0。

## 输出

对于每个测试用例，在单行上打印案例号(以1开头)，后面跟着该大学学生所喜欢的不同明星的最大数量。

## 样例输入

10 9
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10
10 4
2 3
4 5
4 8
5 8
0 0

## 样例输出

Case 1: 1
Case 2: 7

## 题解
我们这一题只需要我们用一个并查集即可，我们即判断 $fa[i]$ 是否曾经出现过，如果是，那么我们就继续，没有，我们就次数++，最后我们来统计我们的次数即可。

```cpp
#include <stdio.h>

int main()
{
	int cases=0;
	int n,m;
	while(~scanf("%d %d",&n,&m)&&n!=0&&m!=0)
	{
		int students[55000]={0};
		for(int i=1;i<=n;i++) students[i]=i;
		for(int k=0;k<m;k++)
		{
			int i,j;
			scanf("%d %d",&i,&j);
			int r1=i;
			int r2=j;
			while(students[r1]!=r1) r1=students[r1];
			while(students[r2]!=r2) r2=students[r2];
			if(r1==r2) continue;
			students[r1]=r2;
			for(int l=1;l<=n;l++)
			{
				if(students[l]==r1) students[l]=r2;
			}
		}
		int counter=0;
		for(int i=1;i<=n;i++) if(students[i]==i) counter++;
		printf("Case %d: %d\n",++cases,counter);
	}
	return 0;
}

```