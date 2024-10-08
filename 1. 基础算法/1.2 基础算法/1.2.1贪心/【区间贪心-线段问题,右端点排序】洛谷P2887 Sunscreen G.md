# [USACO 07 NOV] Sunscreen G

## 题目描述

To avoid unsightly burns while tanning, each of the C (1 ≤ C ≤ 2500) cows must cover her hide with sunscreen when they're at the beach. Cow i has a minimum and maximum SPF rating (1 ≤ minSPFi ≤ 1,000; minSPFi ≤ maxSPFi ≤ 1,000) that will work. If the SPF rating is too low, the cow suffers sunburn; if the SPF rating is too high, the cow doesn't tan at all........

The cows have a picnic basket with L (1 ≤ L ≤ 2500) bottles of sunscreen lotion, each bottle i with an SPF rating SPFi (1 ≤ SPFi ≤ 1,000). Lotion bottle i can cover coveri cows with lotion. A cow may lotion from only one bottle.

What is the maximum number of cows that can protect themselves while tanning given the available lotions?

有 C 个奶牛去晒太阳 (1 <=C <= 2500)，每个奶牛各自能够忍受的阳光强度有一个最小值和一个最大值，太大就晒伤了，太小奶牛没感觉。

而刚开始的阳光的强度非常大，奶牛都承受不住，然后奶牛就得涂抹防晒霜，防晒霜的作用是让阳光照在身上的阳光强度固定为某个值。

那么为了不让奶牛烫伤，又不会没有效果。

给出了 L 种防晒霜。每种的数量和固定的阳光强度也给出来了

每个奶牛只能抹一瓶防晒霜，最后问能够享受晒太阳的奶牛有几个。

## 输入格式

\* Line 1: Two space-separated integers: C and L

\* Lines 2.. C+1: Line i describes cow i's lotion requires with two integers: minSPFi and maxSPFi

\* Lines C+2.. C+L+1: Line i+C+1 describes a sunscreen lotion bottle i with space-separated integers: SPFi and coveri

## 输出格式

A single line with an integer that is the maximum number of cows that can be protected while tanning

## 样例 #1

### 样例输入 #1

```
3 2
3 10
2 5
1 5
6 2
4 1
```

### 样例输出 #1

```
2
```

## 题解
1.有 c 条线段，已知它们的端点；
2.有l种点，已知它们的坐标以及每种点的个数；
3.问如果把那些点放入线段中，最多可以放进几个。

这个时候，我们的问题就已经转变为了我们贪心问题中的线段覆盖问题。首先，我们根据我们的经验，我们不妨把我们的线段按照我们的右端点来进行排序。

然后，我们就能够发现，我们对于某一个端点来说，最好就是选择我们靠左的方案，因为我们的方案越靠左，我们对后续方案的影响就会越小。

```
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct line{
	int l;
	int r;
	bool operator<(line &a){
		return r<a.r;
	}
}Line[N];
struct point{
	int num;
	int x;
	bool operator<(point &a){
		return x<a.x;
	}
}Point[N];
int main(){
	int c,l;
	cin>>c>>l;
	for(int i=0;i<c;i++){
		int l,r;
		cin>>l>>r;
		Line[i].l=l;
		Line[i].r=r;
	}
	for(int i=0;i<l;i++){
		int x,num;
		cin>>x>>num;
		Point[i].num=num;
		Point[i].x=x;
	}
	sort(Line,Line+c);
	sort(Point,Point+l);
	int cnt=0;
	for(int i=0;i<c;i++){
		int r=Line[i].r;
		int ll=Line[i].l;
		for(int j=0;j<l;j++){
			if(Point[j].x<=r&&Point[j].x>=ll){
				if(Point[j].num>0){
					Point[j].num--;
					cnt++; 
					break;
				}
			}
		}
	}
	cout<<cnt<<endl;
}
```

