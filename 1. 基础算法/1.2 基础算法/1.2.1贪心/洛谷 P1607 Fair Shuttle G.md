# [USACO 09 FEB] Fair Shuttle G

## 题面翻译

逛逛集市，兑兑奖品，看看节目对农夫约翰来说不算什么，可是他的奶牛们非常缺乏锻炼——如果要逛完一整天的集市，他们一定会筋疲力尽的。所以为了让奶牛们也能愉快地逛集市，约翰准备让奶牛们在集市上以车代步。但是，约翰木有钱，他租来的班车只能在集市上沿直线跑一次，而且只能停靠 $N(1 \leq N\leq 20000)$ 个地点（所有地点都以 $1$ 到 $N$ 之间的一个数字来表示）。现在奶牛们分成 $K(1\leq K\leq 50000)$ 个小组，第 i 组有 $M_i(1\leq M_i\leq N)$ 头奶牛，他们希望从 $S_i$ 跑到 $E_i(1\leq S_i< E_i\leq N)$。

由于班车容量有限，可能载不下所有想乘车的奶牛们，此时也允许小组里的一部分奶牛分开乘坐班车。约翰经过调查得知班车的容量是 $C(1\leq C\leq 100)$，请你帮助约翰计划一个尽可能满足更多奶牛愿望的方案。

## 题目描述

Although Farmer John has no problems walking around the fair to collect prizes or see the shows, his cows are not in such good shape; a full day of walking around the fair leaves them exhausted. To help them enjoy the fair, FJ has arranged for a shuttle truck to take the cows from place to place in the fairgrounds.

FJ couldn't afford a really great shuttle, so the shuttle he rented traverses its route only once (!) and makes N (1 <= N <= 20,000) stops (conveniently numbered 1.. N) along its path. A total of K (1 <= K <= 50,000) groups of cows conveniently numbered 1.. K wish to use the shuttle, each of the M\_i (1 <= M\_i <= N) cows in group i wanting to ride from one stop S\_i (1 <= S\_i < E\_i) to another stop E\_i (S\_i < E\_i <= N) farther along the route.

The shuttle might not be able to pick up an entire group of cows (since it has limited capacity) but can pick up partial groups as appropriate.

Given the capacity C (1 <= C <= 100) of the shuttle truck and the descriptions of the groups of cows that want to visit various sites at the fair, determine the maximum number of cows that can ride the shuttle during the fair.

## 输入格式

第一行：包括三个整数：$K,N$ 和 $C$，彼此用空格隔开。

第二行到 $K+1$ 行：在第 $i+1$ 行，将会告诉你第 $i$ 组奶牛的信息：$S_i,E_i$ 和 $M_i$，彼此用空格隔开。

## 输出格式

第一行：可以坐班车的奶牛的最大头数。

## 样例 #1

### 样例输入 #1

```
8 15 3
1 5 2
13 14 1
5 8 3
8 14 2
14 15 1
9 12 1
12 15 2
4 6 1
```

### 样例输出 #1

```
10
```

## 提示

【样例说明】

班车可以把 $2$ 头奶牛从 $1$ 送到 $5$，$3$ 头奶牛从 $5$ 送到 $8$，$2$ 头奶牛从 $8$ 送到 $14$，$1$ 头奶牛从 $9$ 送到 $12$，$1$ 头奶牛从 $13$ 送到 $14$，$1$ 头奶牛从 $14$ 送到 $15$。

## 题解
我们这一题首先要采用我们的贪心，我们即先按照我们下车位置进行排序，然后每一次尽可能让早下车的先上车。
但是，我们想要上车，还需要满足下面的一个条件：如果我们选择 $a_{i}$,那么我们必须保证在 $s_{a_{i}}-e_{a_{i}}$ 这一段里面的任何一个时刻值都是小于 $c$ 的，而我们只需要维护我们区间的最大值即可。同时，如果我们选择了第 i 个区间，我们就要尽可能多的选，于是我们就有了一个区间修改。
上述两个操作，四舍五入一下，就相当于一个线段树。线段树维护的是在 $x$ 车站时，我们的车上有多少个人。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=5e4+10;
int n,k,ans,c;
struct Line{
	int m,l,r;
	bool operator<(const Line& l2)const{
		return r < l2.r;
	}
}line[MAXN];
int zt[MAXN];
int tree[MAXN<<2],tag[MAXN<<2];
inline int lc(int x){return x<<1;}
inline int rc(int x){return lc(x)|1;}
void push_up(int);
void push_down(int);
int query(int,int,int,int,int);
void update(int,int,int,int,int,int);
int main(){
	scanf("%d%d%d",&k,&n,&c);
	for(int i=1;i<=k;i++){
		scanf("%d%d%d",&line[i].l,&line[i].r,&line[i].m);
	}
	sort(line+1,line+1+k);
	for(int i=1;i<=k;i++){
		int l = line[i].l,r = line[i].r,m = line[i].m;//m是人数
		//max [l,r)
		int maxn = query(1,1,n,l,r-1);//计算区间最多有多少个人
		int chose =((c-maxn) < m)?(c-maxn):m;
		ans += chose;
		//[l,r) += chose
		update(1,1,n,l,r-1,chose);
	}
	cout<<ans;
	return 0;
}
void push_up(int x){
	tree[x] = max(tree[lc(x)],tree[rc(x)]);
}
void push_down(int x){
	//只维护max甚至不需要l,r？
	tree[lc(x)] += tag[x];
	tree[rc(x)] += tag[x];
	tag[lc(x)] += tag[x];
	tag[rc(x)] += tag[x]; 
	tag[x] = 0; 
}
int query(int x,int l,int r,int ql,int qr){
	if(ql <= l && qr >= r){
		return tree[x];
	}
	int mid = (l+r)>>1;
	int ans = 0;
	push_down(x);
	if(ql <= mid){
		ans = max(ans,query(lc(x),l,mid,ql,qr));
	}
	if(qr > mid){
		ans = max(ans,query(rc(x),mid+1,r,ql,qr));
	}
	push_up(x);
	return ans;
}
void update(int x,int l,int r,int ql,int qr,int value){
	if(ql <= l && qr >= r){
		tree[x] += value;
		tag[x] += value;
		return;
	}
	int mid = (l+r)>>1;
	push_down(x);
	if(ql <= mid){
		update(lc(x),l,mid,ql,qr,value);
	}
	if(qr > mid){
		update(rc(x),mid+1,r,ql,qr,value);
	}
	push_up(x);
}
```