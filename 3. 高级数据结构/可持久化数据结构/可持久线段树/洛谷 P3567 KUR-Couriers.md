#主席树 #主席树求区间第k大
# [POI 2014] KUR-Couriers

## 题面翻译

给一个长度为 $n$ 的正整数序列 $a$。共有 $m$ 组询问，每次询问一个区间 $[l,r]$ ，是否存在一个数在 $[l,r]$ 中出现的次数严格大于一半。如果存在，输出这个数，否则输出 $0$。

$1 \leq n,m \leq 5 \times 10^5$，$1 \leq a_i \leq n$。

## 题目描述

Byteasar works for the BAJ company, which sells computer games.

The BAJ company cooperates with many courier companies    that deliver the games sold by the BAJ company to its customers.

Byteasar is inspecting the cooperation of the BAJ company with the couriers.

He has a log of successive packages with the courier company that made the delivery    specified for each package.

He wants to make sure that no courier company had an unfair advantage over the others.

If a given courier company delivered more than half of all packages sent in some period of time,    we say that it dominated in that period.

Byteasar wants to find out which courier companies dominated in certain periods of time, if any.

Help Byteasar out!

Write a program that determines a dominating courier company or that there was none.

给一个数列，每次询问一个区间内有没有一个数出现次数超过一半

## 输入格式

The first line of the standard input contains two integers, ![](http://main.edu.pl/images/OI21/kur-en-tex.1.png) and ![](http://main.edu.pl/images/OI21/kur-en-tex.2.png) (![](http://main.edu.pl/images/OI21/kur-en-tex.3.png)),    separated by a single space, that are the number of packages shipped by the BAJ company    and the number of time periods for which the dominating courier is to be determined, respectively.

The courier companies are numbered from ![](http://main.edu.pl/images/OI21/kur-en-tex.4.png) to (at most) ![](http://main.edu.pl/images/OI21/kur-en-tex.5.png).

The second line of input contains ![](http://main.edu.pl/images/OI21/kur-en-tex.6.png) integers, ![](http://main.edu.pl/images/OI21/kur-en-tex.7.png) (![](http://main.edu.pl/images/OI21/kur-en-tex.8.png)),    separated by single spaces;    ![](http://main.edu.pl/images/OI21/kur-en-tex.9.png) is the number of the courier company that delivered the ![](http://main.edu.pl/images/OI21/kur-en-tex.10.png)-th package (in shipment chronology).

The ![](http://main.edu.pl/images/OI21/kur-en-tex.11.png) lines that follow specify the time period queries, one per line.

Each query is specified by two integers, ![](http://main.edu.pl/images/OI21/kur-en-tex.12.png) and ![](http://main.edu.pl/images/OI21/kur-en-tex.13.png) (![](http://main.edu.pl/images/OI21/kur-en-tex.14.png)),    separated by a single space.

These mean that the courier company dominating in the period between the shipments of the    ![](http://main.edu.pl/images/OI21/kur-en-tex.15.png)-th and the ![](http://main.edu.pl/images/OI21/kur-en-tex.16.png)-th package, including those, is to be determined.

In tests worth ![](http://main.edu.pl/images/OI21/kur-en-tex.17.png) of total score, the condition ![](http://main.edu.pl/images/OI21/kur-en-tex.18.png) holds,    and in tests worth ![](http://main.edu.pl/images/OI21/kur-en-tex.19.png) of total score ![](http://main.edu.pl/images/OI21/kur-en-tex.20.png).

## 输出格式

The answers to successive queries should be printed to the standard output, one per line.

(Thus a total of ![](http://main.edu.pl/images/OI21/kur-en-tex.21.png) lines should be printed.)    Each line should hold a single integer: the number of the courier company that dominated    in the corresponding time period, or ![](http://main.edu.pl/images/OI21/kur-en-tex.22.png) if there was no such company.

## 样例 #1

### 样例输入 #1

```
7 5
1 1 3 2 3 4 3
1 3
1 4
3 7
1 7
6 6
```

### 样例输出 #1

```
1
0
3
0
4
```


## 题解
我们主席树的思路是通过构造我们的前缀，也就是对我们每一个 $x\in(0,N)$ ,我们构造一个数据结构能够存储 $[0,x]$ 所需要的所有信息，然后我们每一次查询 $(l,r)$,都可以转换为求 $(0,r)-(0,l-1)$。

我们这一题可以通过我们的主席树，查询一个区间有没有一个数出现次数超过一半（**这个数是唯一的**），对所有的前缀建值域主席树，对于区间 ${l,r}$ len=r-l+1, 比较两颗值域线段树在左子/右子的 sz 之差和 len/2 的关系。只要有一个能满足，我们就递归下去继续找

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=500001;//唯二和主席树模板不一样的地方
int n,q,m,cnt;
int a[N],b[N],t[N];
struct sb
{
	int s,l,r;
}tre[N<<5];
int build(int l,int r)//以下全部和主席树模板一样
{
	int p=++cnt;
	if(l<r)
	{
		int mid=(l+r)>>1;
		tre[p].l=build(l,mid);
		tre[p].r=build(mid+1,r);
	}
	return p;
}
int update(int p1,int l,int r,int x)
{
	int p=++cnt;
	tre[p].l=tre[p1].l;
	tre[p].r=tre[p1].r;
	tre[p].s=tre[p1].s+1;
	if(l<r)
	{
		int mid=(l+r)>>1;
		if(x<=mid)tre[p].l=update(tre[p1].l,l,mid,x);else tre[p].r=update(tre[p1].r,mid+1,r,x);
	}
	return p;
}//以上全部和主席树模板一样
int query(int u,int v,int l,int r,int k)//唯二和主席树模板不一样的地方，k表示区间长度的一半
{
    if(l>=r)return l;
    int l1=tre[tre[v].l].s-tre[tre[u].l].s,r1=tre[tre[v].r].s-tre[tre[u].r].s;//计算当前区间值域大于等于l小于等于mid的数字的数量和大于mid小于等于r的数字的数量
    int mid=(l+r)>>1;
    if(l1>k)return query(tre[u].l,tre[v].l,l,mid,k);//如果大于等于l小于等于mid的数字的数量超过一半就往下查询
    if(r1>k)return query(tre[u].r,tre[v].r,mid+1,r,k);//同上
    return 0;//否则说明该区间中不存在出现数量超过一半的数，返回0
}
int main()//以下全部和主席树模板一样
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	m=unique(b+1,b+n+1)-b-1;
	t[0]=build(1,m);
	for(int i=1;i<=n;i++)
	{
		int l=lower_bound(b+1,b+m+1,a[i])-b;
		t[i]=update(t[i-1],1,m,l);
	}
	while(q--)
	{
		int a1,a2;
		scanf("%d%d",&a1,&a2);
		printf("%d\n",b[query(t[a1-1],t[a2],1,m,(a2-a1+1)/2)]);//查询
	}
}//以上全部和主席树模板一样
```