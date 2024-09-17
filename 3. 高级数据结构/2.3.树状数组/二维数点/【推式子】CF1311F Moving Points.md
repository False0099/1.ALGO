# Moving Points

## 题面翻译

### 题目描述

在数轴 $OX$ 上有 $n$ 个点。第 $i$ 个点最初在坐标 $x_i$，并且有一个速度 $v_i$。没有两个点的坐标是相同的。所有的的都安装不变的速度移动，第 $i$ 个点在 $t$ 时刻的坐标为 $x_i + t \cdot v_i$ （$t$ 可能不是整数）。

对于两个点 $i$ 和 $j$，设 $d(i,j)$ 为 $i$ 和 $j$ 在任意时刻下的可能的最小距离（时刻可能不是整数）。如果 $i$ 和 $j$ 在某一时刻重合，那么 $d(i,j)=0$。

你的任务是计算出下面这个式子的值（对于任意两个点的最小距离之和）：
$$
\sum_{1\leq i < j \leq n}d(i,j)
$$

### 输入格式

第一行是一个整数 $n\ (2\leq n \leq 2\times 10^5)$，表示点的个数。

第二行包含 $n$ 个整数 $x_1,x_2,\dots,x_n\ (1\leq x_i \leq 10^8)$，$x_i$ 表示第 $i$ 个点的初始坐标。数据保证没有重复的 $x_i$。

第三行包含 $n$ 个整数 $v_1,v_2,\dots,v_n\ (-10^8 \leq v_i \leq 10^8)$，$v_i$ 表示第 $i$ 个点的初始速度。

### 输出格式

输出一个整数，表示任意两个点的最小距离之和，即
$$
\sum_{1\leq i < j \leq n}d(i,j)
$$

## 题目描述

There are $ n $ points on a coordinate axis $ OX $ . The $ i $ -th point is located at the integer point $ x_i $ and has a speed $ v_i $ . It is guaranteed that no two points occupy the same coordinate. All $ n $ points move with the constant speed, the coordinate of the $ i $ -th point at the moment $ t $ ( $ t $ can be non-integer) is calculated as $ x_i + t \cdot v_i $ .

Consider two points $ i $ and $ j $ . Let $ d (i, j) $ be the minimum possible distance between these two points over any possible moments of time (even non-integer). It means that if two points $ i $ and $ j $ coincide at some moment, the value $ d (i, j) $ will be $ 0 $ .

Your task is to calculate the value $ \sum\limits_{1 \le i < j \le n} $ $ d (i, j) $ (the sum of minimum distances over all pairs of points).

## 输入格式

The first line of the input contains one integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of points.

The second line of the input contains $ n $ integers $ x_1, x_2, \dots, x_n $ ( $ 1 \le x_i \le 10^8 $ ), where $ x_i $ is the initial coordinate of the $ i $ -th point. It is guaranteed that all $ x_i $ are distinct.

The third line of the input contains $ n $ integers $ v_1, v_2, \dots, v_n $ ( $ -10^8 \le v_i \le 10^8 $ ), where $ v_i $ is the speed of the $ i $ -th point.

## 输出格式

Print one integer — the value $ \sum\limits_{1 \le i < j \le n} $ $ d (i, j) $ (the sum of minimum distances over all pairs of points).

## 样例 #1

### 样例输入 #1

```
3
1 3 2
-100 2 3
```

### 样例输出 #1

```
3
```

## 样例 #2

### 样例输入 #2

```
5
2 1 4 3 5
2 2 2 3 4
```

### 样例输出 #2

```
19
```

## 样例 #3

### 样例输入 #3

```
2
2 1
-3 0
```

### 样例输出 #3

```
0
```

## 题解
我们本题的思路是推式子，我们能够发现，如果我们两个是不会相遇，那么我们的 $d(i,j)=|x_{i}-x_{j}|$,如果我们会相遇，我们的 $d(i,j)=0$。

于是，我们就需要计算我们两个能不能相遇，如果能够相遇一定当前仅当 $x_{i}>x_{j},v_{i}<v_{j}$。这里也就转换为了我们的一个二维偏序问题。也就是只有这样，我们才会有贡献。

于是，我们就可以考虑把我们的全部速度按照我们的 $v$ 来进行排序，这样对于任意一对，如果满足 $x_{i}\geq x_{j}$，那么他对我们的贡献就是我们的 $x_{i}-x_{j}$。否则我们的贡献为 0.

于是，我们就可以采用类似于二维数点的方式来计算，对于每一个点，我们要求：
$x\in[0,x_{i}]$, $v\in(-\infty,v_{i})$ 的点的个数。

```cpp
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
struct Node{
	int x,v;
}e[N];
int n,a[N];
long long ans,c[N],d[N];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
bool cmp(Node xxx,Node yyy){
	return xxx.x<yyy.x;
}
int lowbit(int x){
	return x&-x;
}
void adda(int x,int w){
	for(x;x<=n;x+=lowbit(x))c[x]+=w;
}
void addb(int x,int w){
	for(x;x<=n;x+=lowbit(x))d[x]+=w;
}
long long aska(int x){
	long long aaa=0;
	for(x;x>0;x-=lowbit(x))aaa+=c[x];
	return aaa;
}
long long askb(int x){
	long long aaa=0;
	for(x;x>0;x-=lowbit(x))aaa+=d[x];
	return aaa;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)e[i].x=read();
	for(int i=1;i<=n;i++)e[i].v=read(),a[i]=e[i].v;
	sort(e+1,e+1+n,cmp);
	sort(a+1,a+1+n);
	int s=unique(a+1,a+1+n)-a-1;
	for(int i=1;i<=n;i++){
		e[i].v=lower_bound(a+1,a+1+s,e[i].v)-a;
		//cout<<e[i].v<<endl;
	}
	for(int i=1;i<=n;i++){
		ans=ans+askb(e[i].v)*e[i].x-aska(e[i].v);
		adda(e[i].v,e[i].x);
		addb(e[i].v,1);
	}
	cout<<ans;
	return 0;
}
```
```