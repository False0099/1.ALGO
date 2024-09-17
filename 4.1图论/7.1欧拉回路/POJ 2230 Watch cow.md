Besis 最近做了农场看守，他每天晚上的工作就是巡视农场并且保证没有坏人破坏农
场。从谷仓出发去巡视,并且最终回到谷仓。
Bessie的视力不是很好，不能像其他的农场看守一样，对农场的每一条连接不同场地的
路走一遍就可以发现是不是有异常的情况，他需要每条路走两遍，并且这两遍必须是不同的
方向,因为他觉得自己应该不会两次都忽略农场中的异常情况。
每两块地之间一定会由至少一条路连接。现在的任务就是帮他制定巡视路径。前提假
设一定存在满足题意的路径

输入

第一行输人两个数N(2 <= N <= 10000) 和M(1 <= M <= 50000),表示农场一共有N块地M条路。

第2 到M + 1行输人两个整数,表示对应的两块地之间有一条边

输出

输出1到2M+1行，每行一个数字，表示Bessie巡查路径上地的标号1号为谷仓，从1开始，以1结束。如果有多种答案，输出任意一种。

样例输入

4 5
1 2
1 4
2 3
2 4
3 4

样例输出

1
2
3
4
2
1
4
3
2
4
1

## 题解
我们这一题相当于把我们原来的有向图的建边变成两个无向图，依次来实现我们的一条鞭走两次。然后我们求我们这个有向图的欧拉回路即可。

```cpp
#include<cstdio>
#include<stack>
using namespace std;
const int N = 10010, M = 50010;
int h[N],e[M*2],ne[M*2],idx=1;
int n,m;
stack<int> s,ans;
void add(int a,int b)
{
	e[idx]=b;ne[idx]=h[a];h[a]=idx++;
}
void euler()
{
	s.push(1);
	while(!s.empty())
	{
		int x=s.top(),i=h[x];
		if(i)
		{
			h[x]=ne[i];
			s.push(e[i]);
		}
		else
		{
			ans.push(x);
			s.pop();
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m); 
	for(int i=1;i<=m;i++)
	{
		int a,b;scanf("%d%d",&a,&b);
		add(a,b);add(b,a);
	}
	euler();
	while(!ans.empty())
	{
		printf("%d\n",ans.top());
		ans.pop();
	}
	return 0;
}

```