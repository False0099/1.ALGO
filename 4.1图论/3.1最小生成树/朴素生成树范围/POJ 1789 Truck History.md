Advanced Cargo Movement, Ltd. uses trucks of different types. Some trucks are used for vegetable delivery, other for furniture, or for bricks. The company has its own code describing each type of a truck. The code is simply a string of exactly seven lowercase letters (each letter on each position has a very special meaning but that is unimportant for this task). At the beginning of company's history, just a single truck type was used but later other types were derived from it, then from the new types another types were derived, and so on.  
  
Today, ACM is rich enough to pay historians to study its history. One thing historians tried to find out is so called derivation plan -- i.e. how the truck types were derived. They defined the distance of truck types as the number of positions with different letters in truck type codes. They also assumed that each truck type was derived from exactly one other truck type (except for the first truck type which was not derived from any other type). The quality of a derivation plan was then defined as  

**1/Σ(to,td)d(to,td)**

  
where the sum goes over all pairs of types in the derivation plan such that to is the original type and td the type derived from it and d(to,td) is the distance of the types.  
Since historians failed, you are to write a program to help them. Given the codes of truck types, your program should find the highest possible quality of a derivation plan.  

Input

The input consists of several test cases. Each test case begins with a line containing the number of truck types, N, 2 <= N <= 2 000. Each of the following N lines of input contains one truck type code (a string of seven lowercase letters). You may assume that the codes uniquely describe the trucks, i.e., no two of these N lines are the same. The input is terminated with zero at the place of number of truck types.

Output

For each test case, your program should output the text "The highest possible quality is 1/Q.", where 1/Q is the quality of the best derivation plan.

Sample

|Inputcopy|Outputcopy|
|---|---|
|4<br>aaaaaaa<br>baaaaaa<br>abaaaaa<br>aabaaaa<br>0|The highest possible quality is 1/3.|


题意：给出 n 个卡车，每个卡车的类型是七个字符组成的，一种卡车可以从另一种卡车派生来的，代价是两种卡车间类型不同字符的个数，求出这 n 中卡车派生的最小代价，n 种车有一种是开始就有的，n-1种是派生出来的。

```CPP
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
const int N=2010;
char str[N][10];
int num,f[N];
struct edge
{
	int st,ed,w;
}e[N*N];
void addedge(int x,int y,int w)
{
	e[num].st=x;e[num].ed=y;e[num].w=w;num++;
}
int cmp(void const *a,void const *b)
{
	edge *c,*d;
	c=(edge *)a;
	d=(edge *)b;
	return c->w-d->w;
}
int dis(int i,int j)
{
	int k,sum=0;
	for(k=0;k<7;k++)
	{
		if(str[i][k]!=str[j][k])
			sum++;
	}
	return sum;
}
int find(int a)
{
	if(a!=f[a])
		f[a]=find(f[a]);
	return f[a];
}
int main()
{
	int i,j,n,x,y,sum;
	while(scanf("%d",&n)!=-1&&n)
	{
		num=0;
		for(i=1;i<=n;i++)
		{
			scanf("%s",str[i]);
			for(j=1;j<i;j++)
			{
				addedge(i,j,dis(i,j));
			}
			f[i]=i;
		}
		qsort(e,num,sizeof(e[0]),cmp);
		j=1;sum=0;
		for(i=0;i<num&&j<n;i++)
		{
			x=find(e[i].st);
			y=find(e[i].ed);
			if(x==y)continue;
			f[x]=find(y);
			sum+=e[i].w;
			j++;
		}
		printf("The highest possible quality is 1/%d.\n",sum);
	}
	return 0;
}
```