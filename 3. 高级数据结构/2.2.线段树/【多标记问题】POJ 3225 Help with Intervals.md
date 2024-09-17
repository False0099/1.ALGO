LogLoader, Inc. is a company specialized in providing products for analyzing logs. While Ikki is working on graduation design, he is also engaged in an internship at LogLoader. Among his tasks, one is to write a module for manipulating time intervals, which have confused him a lot. Now he badly needs your help.

In discrete mathematics, you have studied several basic set operations, namely union, intersection, relative complementation and symmetric difference, which naturally apply to the specialization of sets as intervals.. For your quick reference they are summarized in the table below:

> |Operation|Notation|Definition|
> |---|---|---|
> |Union|_A_ ∪ _B_|{_x_ : _x_ ∈ _A_ or _x_ ∈ _B_}|
> |Intersection|_A_ ∩ _B_|{_x_ : _x_ ∈ _A_ and _x_ ∈ _B_}|
> |Relative complementation|_A_ − _B_|{_x_ : _x_ ∈ _A_ but _B_}|
> |Symmetric difference|_A_ ⊕ _B_|(_A_ − _B_) ∪ (_B_ − _A_)|

Ikki has abstracted the interval operations emerging from his job as a tiny programming language. He wants you to implement an interpreter for him. The language maintains a set _S_, which starts out empty and is modified as specified by the following commands:

> |Command|Semantics|
> |---|---|
> |`U` _T_|_S_ ← _S_ ∪ _T_|
> |`I` _T_|_S_ ← _S_ ∩ _T_|
> |`D` _T_|_S_ ← _S_ − _T_|
> |`C` _T_|_S_ ← _T_ − _S_|
> |`S` _T_|_S_ ← _S_ ⊕ _T_|

Input

The input contains exactly one test case, which consists of between 0 and 65,535 (inclusive) commands of the language. Each command occupies a single line and appears like

> `X` _T_

where `X` is one of ‘`U`’, ‘`I`’, ‘`D`’, ‘`C`’ and ‘`S`’ and _T_ is an interval in one of the forms `(`_a_`,`_b_`)`, `(`_a_`,`_b_`]`, `[`_a_`,`_b_`)` and `[`_a_`,`_b_`]` (_a_, _b_ ∈ _**Z**_, 0 ≤ _a_ ≤ _b_ ≤ 65,535), which take their usual meanings. The commands are executed in the order they appear in the input.

End of file (EOF) indicates the end of input.

Output

Output the set _S_ as it is after the last command is executed as the union of a minimal collection of disjoint intervals. The intervals should be printed on one line separated by single spaces and appear in increasing order of their endpoints. If _S_ is empty, just print “`empty set`” and nothing else.

Sample

|Inputcopy|Outputcopy|
|---|---|
|U [1,5]<br>D [3,3]<br>S [2,4]<br>C (1,5)<br>I (2,3]|(2,3)|


## 题解
我们这一题的思想，就是把我们的 S 集合转换改编为我们 0-1 序列上连续长度的变化，我们于是就可以用我们的 0 表示不在 S 集合，1 表示在 S 集合。
一开始有一个大的区间0-maxn  
U:把区间[l,r]覆盖成1  
I:把[-∞,l)(r,∞]覆盖成0  
D:把区间[l,r]覆盖成0  
C:把[-∞,l)(r,∞]覆盖成0 , 且[l,r]区间0/1互换  
S:[l,r]区间0/1互换‘

所以问题演变成覆盖和 xor 的线段树嗯哼！


我们现在的问题就变成维护多个标签，以及我们的顺序，首先我们都规定我们先进行我们的 0/1 互换，然后再进行我们的覆盖，因为这样，当我们合并两个区间的时候就非常好判定了，**如果有覆盖，我们就直接让我们的 0、1 操作清零，直接覆盖即可。**

```cpp
#include <stdio.h>
#include <iostream>
#include <map>
#include <set>
#include <list>
#include <stack>
#include <vector>
#include <math.h>
#include <string.h>
#include <queue>
#include <string>
#include <stdlib.h>
#include <algorithm>
//#define LL long long
#define LL __int64
#define eps 1e-12
#define PI acos(-1.0)
using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn = 131072;
 
struct node
{
	int l,r;
	int col;
	int rev;
}tree[maxn*4];
 
char s1[10],s2[10];
int a[maxn+10];
 
void build(int v, int l, int r)
{
	tree[v].l = l;
	tree[v].r = r;
	tree[v].col = 0;
	tree[v].rev = 0;
	if(l == r)
		return;
	int mid = (l+r)>>1;
	build(v*2,l,mid);
	build(v*2+1,mid+1,r);
}
 
void push_down(int v)
{
	if(tree[v].l == tree[v].r)
		return;
	if(tree[v].col != -1) //区间被完全覆盖
	{
		tree[v*2].col = tree[v*2+1].col = tree[v].col; //向下推送，并把自己的col置为-1
		tree[v].col = -1;
		tree[v].rev = 0;
		tree[v*2].rev = tree[v*2+1].rev = 0; //儿子节点也被完全覆盖，因此抹去异或操作
	}
	if(tree[v].rev) //区间没被完全覆盖且需要异或
	{
		if(tree[v*2].col != -1) //儿子节点被完全覆盖，直接异或
			tree[v*2].col ^= 1;
		else tree[v*2].rev ^= 1;//否则rev进行异或。
		if(tree[v*2+1].col != -1)
			tree[v*2+1].col ^= 1;
		else tree[v*2+1].rev ^= 1;
		tree[v].rev = 0;
	}
}
 
void update(int v, int l, int r, int col)
{
	if(l > r) //l > r的区间忽略不计
		return;
	if(tree[v].l == l && tree[v].r == r)
	{
		if(col == 0 || col == 1)
		{
			tree[v].col = col;
			tree[v].rev = 0;
		}
		else
		{
			if(tree[v].col != -1)
				tree[v].col ^= 1;
			else
				tree[v].rev ^= 1;
		}
		return;
	}
	push_down(v);
	int mid = (tree[v].l + tree[v].r) >> 1;
	if(r <= mid)
		update(v*2,l,r,col);
	else if(l > mid)
		update(v*2+1,l,r,col);
	else
	{
		update(v*2,l,mid,col);
		update(v*2+1,mid+1,r,col);
	}
}
 
void query(int v)
{
	if(tree[v].col == 1)
	{
		for(int i = tree[v].l; i <= tree[v].r; i++)
			a[i] = tree[v].col;
		return;
	}
	if(tree[v].col == 0)
		return;
	if(tree[v].l == tree[v].r)
		return;
	push_down(v);
	query(v*2);
	query(v*2+1);
}
 
int main()
{
	build(1,0,maxn);
	int l,r,len;
    memset(a,0,sizeof(a));
	while(~scanf("%s %s",s1,s2))
	{
		l = 0;
		r = 0;
		len = strlen(s2);
		int i;
		for(i = 1; s2[i] >= '0' && s2[i] <= '9'; i++)
			l = l*10 + s2[i]-'0';
		i++;
		for(; s2[i] >= '0' && s2[i] <= '9'; i++)
			r = r*10 + s2[i]-'0';
 
		if(s2[0] == '[')
			l = l*2;
		else l = l*2+1;
		if(s2[len-1] == ']')
			r = r*2;
		else r = r*2-1;
 
		if(s1[0] == 'U')
		{
			update(1,l,r,1);
		}
		else if(s1[0] == 'I')
		{
			update(1,0,l-1,0);
			update(1,r+1,maxn,0);
		}
		else if(s1[0] == 'D')
		{
			update(1,l,r,0);
		}
		else if(s1[0] == 'C')
		{
			update(1,0,l-1,0);
			update(1,r+1,maxn,0);
			update(1,l,r,2); //取反
		}
		else
		{
			update(1,l,r,2);//取反
		}
	}
 
	query(1);
	int flag = 0;
 
	for(int i = 0; i < maxn; i++)
	{
		if(a[i] == 1 && (i == 0 || a[i-1] == 0)) l = i;
		if(a[i] == 1 && (i == maxn-1 || a[i+1] == 0))
		{
			if(flag == 0) flag = 1;
			else printf(" ");
			if(l%2)
				printf("(");
			else printf("[");
			printf("%d,",l/2);
			printf("%d",(i+1)/2);
			if(i%2)
				printf(")");
			else printf("]");
		}
	}
	if(flag == 0)
		printf("empty set\n");
	else printf("\n");
	return 0;
}
```