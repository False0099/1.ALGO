Let us consider a special type of a binary search tree, called a cartesian tree. Recall that a binary search tree is a rooted ordered binary tree, such that for its every node x the following condition is satisfied: each node in its left subtree has the key less then the key of x, and each node in its right subtree has the key greater then the key of x.  
That is, if we denote left subtree of the node x by L(x), its right subtree by R(x) and its key by kx then for each node x we have  

- if y ∈ L(x) then ky < kx  
    
- if z ∈ R(x) then kz > kx

  
The binary search tree is called cartesian if its every node x in addition to the main key kx also has an auxiliary key that we will denote by ax, and for these keys the heap condition is satisfied, that is  

- if y is the parent of x then ay < ax

  
Thus a cartesian tree is a binary rooted ordered tree, such that each of its nodes has a pair of two keys (k, a) and three conditions described are satisfied.  
Given a set of pairs, construct a cartesian tree out of them, or detect that it is not possible.

Input

The first line of the input file contains an integer number N -- the number of pairs you should build cartesian tree out of (1 <= N <= 50 000). The following N lines contain two numbers each -- given pairs (ki, ai). For each pair |ki|, |ai| <= 30 000. All main keys and all auxiliary keys are different, i.e. ki != kj and ai != aj for each i != j.

Output

On the first line of the output file print YES if it is possible to build a cartesian tree out of given pairs or NO if it is not. If the answer is positive, on the following N lines output the tree. Let nodes be numbered from 1 to N corresponding to pairs they contain as they are given in the input file. For each node output three numbers -- its parent, its left child and its right child. If the node has no parent or no corresponding child, output 0 instead.  
The input ensure these is only one possible tree.

Sample

|Inputcopy|Outputcopy|
|---|---|
|7<br>5 4<br>2 2<br>3 9<br>0 5<br>1 3<br>6 6<br>4 11|YES<br>2 3 6<br>0 5 1<br>1 0 7<br>5 0 0<br>2 4 0<br>1 0 0<br>3 0 0|

## 题解
这道题我开始是用第二关键字从小到大排序，然后从1-n 去添加节点。这样是符合最小堆的性质，假设添加第 i 个节点，那么首先去找[1,i-1]这段区间的第一关键字的最小值和最大值，如果 i 节点的第一关键字大于最大值，就直接添加到最大值节点的右儿子，如果小于最小值，就添加到最小值节点的左儿子，否则就直接从根节点往下找。可是超时了，其实超时的原因还蛮明显的，因为你添加的 i 节点不一定每次都是大于最大值，小于最小值，更多的情况可能是在中间值，这样每次都要从根节点出发往下走，这样就会造成遍历的时间太多了。但按照这种思路，很难直接找到 i 节点的父节点是谁，因为[1,i-1]区间内的第一关键字是无序的。

参考了网上的思路，绝大部分都是按照第一关键字排序，然后再去找区间段内的最小值作为子树的根节点。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
 
const int maxn = 50005;
struct Node
{
	int k,a;
	int id;
 
	bool operator < (const Node &T)
	{
		return a < T.a;
	}
}tree[maxn];
struct Result
{
	int parent,left,right;
}res[maxn];
int n,value[maxn],dp_max[maxn][20],dp_min[maxn][20];
 
int _max(int l,int r)
{
	if(tree[l].k > tree[r].k) return l;
	return r;
}
 
int _min(int l,int r)
{
	if(tree[l].k < tree[r].k) return l;
	return r;
}
 
void initRMQ()
{
	for(int i = 1; i <= n; i++)
		dp_max[i][0] = dp_min[i][0] = i;
	for(int j = 1; (1 << j) <= n; j++)
		for(int i = 1; i + (1 << j) - 1 <= n; i++)
		{
			dp_max[i][j] = _max(dp_max[i][j-1],dp_max[i+(1<<j-1)][j-1]);
			dp_min[i][j] = _min(dp_min[i][j-1],dp_min[i+(1<<j-1)][j-1]);
		}
}
 
int MaxValue(int l,int r)
{
	int k = (int)(log((r - l + 1)*1.0) / log(2.0));
	return _max(dp_max[l][k],dp_max[r-(1<<k)+1][k]);
}
 
int MinValue(int l,int r)
{
	int k = (int)(log((r - l + 1)*1.0) / log(2.0));
	return _min(dp_min[l][k],dp_min[r-(1<<k)+1][k]);
}
 
void Build()
{
	int maxm,minm;
	for(int i = 1; i <= n; i++)
		res[i].parent = res[i].left = res[i].right = 0;
	for(int i = 2; i <= n; i++)
	{
		maxm = MaxValue(1,i-1);
		minm = MinValue(1,i-1);
		if(tree[i].k > tree[maxm].k)
		{
			res[tree[maxm].id].right = tree[i].id;
			res[tree[i].id].parent = tree[maxm].id;
		}
		else if(tree[i].k < tree[minm].k)
		{
			res[tree[minm].id].left = tree[i].id;
			res[tree[i].id].parent = tree[minm].id;
		}
		else
		{
			int p = tree[1].id;
			while(true)
			{
				if(tree[i].k > value[p])
				{
					if(res[p].right != 0)
						p = res[p].right;
					else
					{
						res[p].right = tree[i].id;
						res[tree[i].id].parent = p;
						break;
					}
				}
				else
				{
					if(res[p].left != 0)
						p = res[p].left;
					else
					{
						res[p].left = tree[i].id;
						res[tree[i].id].parent = p;
						break;
					}
				}
			}
		}
	}
}
 
int main()
{
	while(scanf("%d",&n)!=EOF)
	{
		for(int i = 1; i <= n; i++)
		{
			scanf("%d%d",&tree[i].k,&tree[i].a);
			tree[i].id = i;
			value[i] = tree[i].k;
		}
		sort(tree+1,tree+1+n);
		initRMQ();
		Build();
		printf("YES\n");
		for(int i = 1; i <= n; i++)
			printf("%d %d %d\n",res[i].parent,res[i].left,res[i].right);
	}
	return 0;
}
```