# [USACO 06 FEB] Stall Reservations S

## 题目描述

Oh those picky $N$ ($1 \leq N \leq 50,000$) cows! They are so picky that each one will only be milked over some precise time interval $A..B$ ($1 \leq A \leq B \leq 1,000,000$), which includes both times $A$ and $B$. Obviously, FJ must create a reservation system to determine which stall each cow can be assigned for her milking time. Of course, no cow will share such a private moment with other cows.

Help FJ by determining: The minimum number of stalls required in the barn so that each cow can have her private milking period. An assignment of cows to these stalls over time. Many answers are correct for each test dataset; a program will grade your answer.

约翰的 $N$（$1\leq N\leq 50000$）头奶牛实在是太难伺候了，她们甚至有自己独特的产奶时段。对于某一头奶牛，她每天的产奶时段是固定的时间段 $[A,B]$（即 $A$ 到 $B$，包括 $A$ 和 $B$）。这使得约翰必须开发一个调控系统来决定每头奶牛应该被安排到哪个牛棚去挤奶，因为奶牛们并不希望在挤奶时被其它奶牛看见。

请帮约翰计算：如果要满足奶牛们的要求，并且每天每头奶牛都要被挤过奶，至少需要多少牛棚和每头牛应该在哪个牛棚被挤奶。如果有多种答案，输出任意一种均可。

## 输入格式

Line $1$: A single integer, $N$

Lines $2..N+1$: Line $i+1$ describes cow $i$ 's milking interval with two space-separated integers.

第 $1$ 行为一个整数 $N$。

第 $2\sim (N+1)$ 行，每行两个数字，第 $(i+1)$ 行的数字代表第 $i$ 头奶牛的产奶时段。

## 输出格式

Line $1$: The minimum number of stalls the barn must have.

Lines $2..N+1$: Line $i+1$ describes the stall to which cow i will be assigned for her milking period.

第 $1$ 行输出一个整数，代表需要牛棚的最少数量。

第 $2\sim (N+1)$ 行，每行一个数字，第 $(i+1)$ 行的数字代表第 $i$ 头奶牛将会被安排到哪个牛棚挤奶。

## 样例 #1

### 样例输入 #1

```
5
1 10
2 4
3 6
5 8
4 7
```

### 样例输出 #1

```
4
1
2
3
2
4
```

## 提示

Explanation of the sample:







Here's a graphical schedule for this output:

Time     1  2  3  4  5  6  7  8  9 10


Stall 1 c 1>>>>>>>>>>>>>>>>>>>>>>>>>>>


Stall 2 .. C 2>>>>>> c 4>>>>>>>>> .. ..


Stall 3 .. .. C 3>>>>>>>>> .. .. .. ..


Stall 4 .. .. .. C 5>>>>>>>>> .. .. .. Other outputs using the same number of stalls are possible.

由@FlierKing 提供 spj

## 题解
这题运用的算法是贪心算法。

首先我们这一题相当于：给定我们的 $n$ 个线段，然后我们再去求，我们这 $n$ 个线段最少可以分成多少组不重复的“不相交”序列。其中，我们的不相交序列就是要求我们这一个序列中的任意两个元素之间，不存在公共部分。

而对于本题，我们如果按照右端点来进行排序，可能会遇见下面的问题：
![[Pasted image 20240410204556.png]]
在我们的着一种情况下，我们的线段 $3$ 如果贪心的来说，应该是连接到和他时间最相近，也就是世间最大的那一个当中去，也就是连接到我们的 1 之后。但是，如果我们用堆来操作的话，我们就只能接到我们的 2 之后，显然是不符合我们的要求的。

于是，我们考虑按照我们的左端点来进行排序，这样排序，我们相当于按照我们的时间来进行模拟。

对于每头牛，我们找出一下之前的牛用过的调控系统中最早结束使用的，如果结束时间小于当前奶牛开始挤奶时间，我们就将当前奶牛加入这个调控系统。否则，新建一个调控系统。

实现过程中我们用优先队列存一下当前最早结束挤奶的调控系统。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
typedef pair<int,int> PII;
struct line{
	int l;
	int r;
	int id;
	bool operator <(line&b){
		return l<b.l;
	}
}Line[N];
int ans[N];
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>Line[i].l>>Line[i].r;
		Line[i].id=i;
	}
	sort(Line,Line+n);
	priority_queue<pair<int,int>,vector<PII>,greater<PII>> heap;
	int id=0;
	ans[Line[0].id]=1;
	heap.push({Line[0].r,++id});
	for(int i=1;i<n;i++){
		auto u=heap.top();
		heap.pop();
		if(Line[i].l>u.first){
			u.first=Line[i].r;
			ans[Line[i].id]=u.second;
			heap.push(u);
			continue;
		}else{
			heap.push(u);
			++id;
			heap.push({Line[i].r,id});
			ans[Line[i].id]=id;
		}
	}
	cout<<id<<endl;
	for(int i=0;i<n;i++){
		cout<<ans[i]<<endl;
	} 
}
```