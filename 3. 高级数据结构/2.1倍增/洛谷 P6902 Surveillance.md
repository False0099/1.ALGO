# [ICPC 2014 WF] Surveillance

## 题面翻译

### 题目描述
给定一个长度为 $n$ 的环，有 $k$ 个区域被覆盖，求最小的满足环被完全覆盖的区域数量。
### 输入格式
第一行两个整数 $n$，$k$。
接下来 $k$ 行，每行两个整数表示一个区域。
### 输出格式
若环不可能被完全覆盖，输出 `impossible`；否则输出一个整数，表示最少的区域数量。

## 题目描述

The International Corporation for Protection and Control (ICPC) develops efficient technology for, well, protection and control. Naturally, they are keen to have their own headquarters protected and controlled. Viewed from above, the headquarters building has the shape of a convex polygon. There are several suitable places around it where cameras can be installed to monitor the building. Each camera covers a certain range of the polygon sides (building walls), depending on its position. ICPC wants to minimize the number of cameras needed to cover the whole building.

## 输入格式

The input consists of a single test case. Its first line contains two integers $n$ and $k$ ($3 \le n \le 10^6$ and $1 \le k \le 10^6$), where $n$ is the number of walls and $k$ is the number of possible places for installing cameras. Each of the remaining $k$ lines contains two integers $a_ i$ and $b_ i$ ($1 \le a_ i, b_ i \le n$). These integers specify which walls a camera at the $i^{th}$ place would cover. If $a_ i \le b_ i$ then the camera covers each wall $j$ such that $a_ i \le j \le b_ i$. If $a_ i > b_ i$ then the camera covers each wall $j$ such that $a_ i \le j \le n$ or $1 \le j \le b_ i$.

## 输出格式

Display the minimal number of cameras that suffice to cover each wall of the building. The ranges covered by two cameras may overlap. If the building cannot be covered, display impossible instead.

## 样例 #1

### 样例输入 #1

```
100 7
1 50
50 70
70 90
90 40
20 60
60 80
80 20
```

### 样例输出 #1

```
3
```

## 样例 #2

### 样例输入 #2

```
8 2
8 3
5 7
```

### 样例输出 #2

```
impossible
```

## 样例 #3

### 样例输入 #3

```
8 2
8 4
5 7
```

### 样例输出 #3

```
2
```

## 提示

Time limit: 4000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2014

## 题解
我们这一题如果我们把我们的环改成了链，那么我们就可以用我们的贪心算法，假设我们已经覆盖了前面的 x 个点，为了覆盖第 $x+1$ 个点，我们就要去找在 $x$ 之前的，最远的能扩展的点，

现在我们已经变成了一个环，我们就需要用我们的倍增法+贪心来解决我们的这一个问题。这一下我们**就变成了我们的国旗计划**惹！我们用 $f[i][k]$ 表示我们在 i 结点，向后跳 k 次，我们能够到达的最远点是哪里，我们可以 $o(n\log n)$ 预处理，然后再单词简单查询即可。

```c++
#include<bits/stdc++.h>
#define N 1000005
using namespace std;

inline int read(){
    int x = 0; char ch = getchar(); bool positive = 1;
    for (; !isdigit(ch); ch = getchar())	if (ch == '-')	positive = 0;
    for (; isdigit(ch); ch = getchar())	x = x * 10 + ch - '0';
    return positive ? x : -x;
}
inline void write(int a){
    if(a>=10)write(a/10);
    putchar('0'+a%10);
}
inline void writesp(int a){
    if(a>=10)write(a/10);
    putchar('0'+a%10);
    printf(" ");
}
inline void writeln(int a){
    if(a<0){
    	a=-a; putchar('-');
    }
    write(a); puts("");
}

int n,m,x,y,now,f[N<<1][22],Left,ans,nowans,tot;
struct sxy
{
	int first,second;
	bool operator < (const sxy b)const
	{
        return first<b.first;
    }
}a[N<<1];
multiset<pair<int,int> >S;

signed main()
{
	n=read(),m=read();
	for (int i=1;i<=m;i++)
	{
		x=read(),y=read();
		if (x<=y) a[++tot]={x,y},a[++tot]={x+n,y+n}; else a[++tot]={x,y+n};
	}
	sort(a+1,a+tot+1);
	now=0;
	for (int i=1;i<=tot;i++)
	{
		f[i][0]=i;
		S.insert({a[i].second,i});
		while (S.begin()->first<a[i].first-1)
		{
			f[S.begin()->second][0]=now;
			S.erase(S.begin());
		}
		if (a[i].second>a[now].second) now=i;
	}
//	for (int i=1;i<=tot;i++) cout<<f[i][0]<<endl;
	while (!S.empty())
	{
		f[S.begin()->second][0]=now;
		S.erase(S.begin());
	}
	for (int i=1;i<=21;i++)
	  for (int j=1;j<=tot;j++)
	    f[j][i]=f[f[j][i-1]][i-1];
	ans=INT_MAX;
	for (int i=1;i<=tot;i++)
	{
		Left=a[i].first;nowans=0;
		if (a[i].second-a[i].first+1>=n) ans=min(ans,1);
		x=i;
		for(int i=21;i>=0;i--)
        	if(a[f[x][i]].second-Left+1<n)
           		x=f[x][i],nowans+=1<<i;
        x=f[x][0];
        if (a[x].second-Left+1>=n) ans=min(ans,nowans+2);
    }
	if (ans==INT_MAX) puts("impossible"); else writeln(ans);
}
/*
100 7
1 50
20 60
50 70
60 80
70 90
80 20
90 40
*/
```