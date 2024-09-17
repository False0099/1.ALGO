# Strong Vertices

## 题面翻译

给定两个数组 $a$ 和 $b$，对此构造一张有向图：

- 若 $a_u-a_v\ge b_u-b_v$，则 $u$ 向 $v$ 连边。

求所有向其他**所有**顶点连边的顶点个数，并按**从小到大**顺序输出它们。

## 题目描述

Given two arrays $ a $ and $ b $ , both of length $ n $ . Elements of both arrays indexed from $ 1 $ to $ n $ . You are constructing a directed graph, where edge from $ u $ to $ v $ ( $ u\neq v $ ) exists if $ a_u-a_v \ge b_u-b_v $ .

A vertex $ V $ is called strong if there exists a path from $ V $ to all other vertices.

A path in a directed graph is a chain of several vertices, connected by edges, such that moving from the vertex $ u $ , along the directions of the edges, the vertex $ v $ can be reached.

Your task is to find all strong vertices.

For example, if $ a=[3,1,2,4] $ and $ b=[4,3,2,1] $ , the graph will look like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1857D/d82544424ea2e3e9ac339f1c8fa7dad6ac60fbfc.png) The graph has only one strong vertex with number $ 4 $

## 输入格式

The first line contains an integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 2 \le n \le 2\cdot 10^5 $ ) — the length of $ a $ and $ b $ .

The second line of each test case contains $ n $ integers $ a_1, a_2 \dots a_n $ ( $ -10^9 \le a_i \le 10^9 $ ) — the array $ a $ .

The third line of each test case contains $ n $ integers $ b_1, b_2 \dots b_n $ ( $ -10^9 \le b_i \le 10^9 $ ) — the array $ b $ .

It is guaranteed that the sum of $ n $ for all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output two lines: in the first line, output the number of strong vertices, and in the second line, output all strong vertices in ascending order.

## 样例 #1

### 样例输入 #1

```
5
4
3 1 2 4
4 3 2 1
5
1 2 4 1 2
5 2 3 3 1
2
1 2
2 1
3
0 2 1
1 3 2
3
5 7 4
-2 -3 -6
```

### 样例输出 #1

```
1
4 
2
3 5 
1
2 
3
1 2 3 
2
2 3
```

## 提示

The first sample is covered in the problem statement.

For the second sample, the graph looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1857D/4f95c34528d6169c692c6bf6f2ed63814b90c73c.png) The graph has two strong vertices with numbers $ 3 $ and $ 5 $ . Note that there is a bidirectional edge between vertices $ 3 $ and $ 5 $ .In the third sample, the vertices are connected by a single directed edge from vertex $ 2 $ to vertex $ 1 $ , so the only strong vertex is $ 2 $ .

In the fourth sample, all vertices are connected to each other by bidirectional edges, so there is a path from every vertex to any other vertex.

## 题解
我们转换前的式子为：$a_{u}-a_{v}\geq b_{u}-b_{v}$，我们转换后不难得到，我们希望得到的式子是：$(a_{u}-b_{u})\geq a_{v}-b_{v}$,而在这里，我们的 $(u,v)$ 又是一个可以确定的，于是我们就可以转换为 $f(u)\geq f(v)$,然后我们就变成求 $f(u)\geq f(v)$ 的个数有多少个。于是我们就可以通过我们的排序来简单计算即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node
{
	int a,b,pos,sub;//a数组，b数组，位置，同位置的差
}s[int(2e5+10)];
int cmp(node x,node y)//按照差为第一关键字，位置为第二关键字
{
	if(x.sub!=y.sub) return x.sub>y.sub;
	else return x.pos<y.pos;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>s[i].a;
			s[i].pos=i;//记录位置
		} 
		for(int i=1;i<=n;i++)
		{
			cin>>s[i].b;
			s[i].sub=s[i].a-s[i].b;//记录差值
		}
		sort(s+1,s+n+1,cmp);
		s[0].sub=s[1].sub;//判断的时候会往前判一位，提前把0赋值了避免忽略1
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			if(s[i].sub!=s[i-1].sub) break;//不是最大，退出
			ans++;//答案加一
		}
		cout<<ans<<endl;
		for(int i=1;i<=ans;i++) cout<<s[i].pos<<' ';//循环答案个数次，输出答案
		cout<<endl;
	}
	return 0;
}
```