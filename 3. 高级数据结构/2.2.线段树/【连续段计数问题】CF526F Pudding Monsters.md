# Pudding Monsters

## 题面翻译

给定一个 $n \times n$ 的棋盘，其中有 $n$ 个棋子，每行每列恰好有一个棋子。

对于所有的 $1 \leq k \leq n$，求有多少个 $k \times k$ 的子棋盘中恰好有 $k$ 个棋子。

$n \le 3 \times 10^5$。

## 题目描述

In this problem you will meet the simplified model of game Pudding Monsters.

An important process in developing any game is creating levels. A game field in Pudding Monsters is an $ n×n $ rectangular grid, $ n $ of its cells contain monsters and some other cells contain game objects. The gameplay is about moving the monsters around the field. When two monsters are touching each other, they glue together into a single big one (as they are from pudding, remember?).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526F/20aa5815ee72cc21be376a3c3bc47e609a6b5dc1.png)Statistics showed that the most interesting maps appear if initially each row and each column contains exactly one monster and the rest of map specifics is set up by the correct positioning of the other game objects.

A technique that's widely used to make the development process more efficient is reusing the available resources. For example, if there is a large $ n×n $ map, you can choose in it a smaller $ k×k $ square part, containing exactly $ k $ monsters and suggest it as a simplified version of the original map.

You wonder how many ways there are to choose in the initial map a $ k×k $ ( $ 1<=k<=n $ ) square fragment, containing exactly $ k $ pudding monsters. Calculate this number.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=3×10^{5} $ ) — the size of the initial field.

Next $ n $ lines contain the coordinates of the cells initially containing monsters. The $ i $ -th of the next lines contains two numbers $ r_{i}, c_{i} $ ( $ 1<=r_{i}, c_{i}<=n $ ) — the row number and the column number of the cell that initially contains the $ i $ -th monster.

It is guaranteed that all $ r_{i} $ are distinct numbers and all $ c_{i} $ are distinct numbers.

## 输出格式

Print the number of distinct square fragments of the original field that can form a new map.

## 样例 #1

### 样例输入 #1

```
5
1 1
4 3
3 2
2 4
5 5
```

### 样例输出 #1

```
10
```


## 题解
首先，我们每一行每一列恰好有一个棋子的棋盘，可以抽象成一个排列，而操作也是对于我们的一个排列的一段来进行的。因我们 $k*k$ 的棋盘内有 $k$ 个棋子就等价于我们在我们的原来的数组中 $a_{x}=y$ 中，存在一个子数组，且连续的一段中，且段中的元素排好后必须是公差为 1 的等差数列。

考虑我们应该怎么样刻画我们的"连续的一段中，且段中的元素排好序后必须是公差为 1 的等差数列。因为我们的没有重复元素，所以我们就有：$Max[l,r]-Min[l,r]=(R-L)$。我们直接计算我们的 $Max[l,r]-Min[l,r]$ 再去检查的时间复杂度是 $o(n^2)$ 的，而我们显然不能够去枚举我们的 $[l,r]$ 所以我们考虑下面的方法，

形式化的，现在我们就转而要求，给定一个序列 $a$，问你：$f(l,r)=Max(l,r)+L-Min(l,r)-R=0$ 的区间 $l,r$ 有多少个，面对这一类问题我们的思路一般是分开来看，分成我们的 $l,r$ 两个端点对我们的贡献分别是多少，然后我们再去求对应的可选范围是到哪里。但是这里，我们发现，我们的 $Max(l,r)$ 和我们的 $Min(l,r)$ 的更新并不能简单的处理。

想要处理我们的 $Max(l,r)$ 和我们的 $Min(l,r)$ 我们就需要通过我们的后缀数据结构来进行处理，而我们的后缀数据结构维护我们的最大值和我们的最小值，我们一般来说，都是通过我们的单调栈来进行维护的，因此，我们也考虑我们能不能采用我们的后缀数据结构来处理我们的 $f(l)$ ，即让我们的 $f(l)$ 表示我们的 $l\to r$ 这一段区间内的答案是多少。

这里我们考虑每一次添加一个 $R$ 会对我们的答案造成什么影响，首先我们的影响的过程类似于一个 $Pk$ 的过程，如果我们每一次 PK 干掉了上一个，那么我们上一个就不需要存在了，我们直接替换即可。如果我们 PK 没有干掉我们的上一个，我们肯定也不可能干的掉这个元素再向前的其他元素了。我们直接退出即可。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define ll long long
const int N=500000;
int n,top1,top2;
ll ans;
struct chess
{
	int x,y;
	bool operator <(const chess &P) const {return x<P.x;}
}c[N],stk1[N],stk2[N];
struct node
{
	int Min,tag;ll cnt;
} t[N<<2];

void build(int i,int l,int r)
{
	if (l==r) {t[i].Min=l;t[i].cnt=1;return;}
	int mid=(l+r)>>1;
	build(i<<1,l,mid);build(i<<1|1,mid+1,r);
	t[i]=t[i<<1];
}

void pushdown(int i)
{
	int ls=i<<1,rs=ls|1;
	t[ls].Min+=t[i].tag;t[rs].Min+=t[i].tag;
	t[ls].tag+=t[i].tag;t[rs].tag+=t[i].tag;
	t[i].tag=0;
}

void pushup(int i)
{
	int ls=i<<1,rs=ls|1;
	t[i].Min=min(t[ls].Min,t[rs].Min);t[i].cnt=0;
	if (t[i].Min==t[ls].Min) t[i].cnt+=t[ls].cnt;
	if (t[i].Min==t[rs].Min) t[i].cnt+=t[rs].cnt;
}

void update(int i,int l,int r,int x,int y,int val)
{
	if (l>=x&&r<=y) {t[i].Min+=val;t[i].tag+=val;return;}
	int mid=(l+r)>>1;pushdown(i);
	if (mid>=x) update(i<<1,l,mid,x,y,val);
	if (mid<y) update(i<<1|1,mid+1,r,x,y,val);
	pushup(i);
}

int query(int i,int l,int r,int x,int y)
{
	if (l>=x&&r<=y) return t[i].Min==0?t[i].cnt:0;
	int mid=(l+r)>>1,ans=0;pushdown(i);
	if (mid>=x) ans+=query(i<<1,l,mid,x,y);
	if (mid<y) ans+=query(i<<1|1,mid+1,r,x,y);
	return ans;
}

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d",&c[i].x,&c[i].y);
	sort(c+1,c+n+1);build(1,1,n);
	for (int i=1;i<=n;i++)
	{
		update(1,1,n,1,n,-1);
		while (top1&&stk1[top1].y<c[i].y)
			update(1,1,n,stk1[top1-1].x+1,stk1[top1].x,c[i].y-stk1[top1].y),--top1;
		stk1[++top1]={i,c[i].y};
		while (top2&&stk2[top2].y>c[i].y)
			update(1,1,n,stk2[top2-1].x+1,stk2[top2].x,stk2[top2].y-c[i].y),--top2;
		stk2[++top2]={i,c[i].y};
		ans+=query(1,1,n,1,i);
	}
	printf("%lld\n",ans);
}

```


