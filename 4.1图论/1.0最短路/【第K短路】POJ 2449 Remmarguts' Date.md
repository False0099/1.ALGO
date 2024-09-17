"Good man never makes girls wait or breaks an appointment!" said the mandarin duck father. Softly touching his little ducks' head, he told them a story.  
  
"Prince Remmarguts lives in his kingdom UDF – United Delta of Freedom. One day their neighboring country sent them Princess Uyuw on a diplomatic mission."  
  
"Erenow, the princess sent Remmarguts a letter, informing him that she would come to the hall and hold commercial talks with UDF if and only if the prince go and meet her via the K-th shortest path. (in fact, Uyuw does not want to come at all)"  
  
Being interested in the trade development and such a lovely girl, Prince Remmarguts really became enamored. He needs you - the prime minister's help!  
  
DETAILS: UDF's capital consists of N stations. The hall is numbered S, while the station numbered T denotes prince' current place. M muddy directed sideways connect some of the stations. Remmarguts' path to welcome the princess might include the same station twice or more than twice, even it is the station with number S or T. Different paths with same length will be considered disparate.  

Input

The first line contains two integer numbers N and M (1 <= N <= 1000, 0 <= M <= 100000). Stations are numbered from 1 to N. Each of the following M lines contains three integer numbers A, B and T (1 <= A, B <= N, 1 <= T <= 100). It shows that there is a directed sideway from A-th station to B-th station with time T.  
  
The last line consists of three integer numbers S, T and K (1 <= S, T <= N, 1 <= K <= 1000).

Output

A single line consisting of a single integer number: the length (time required) to welcome Princess Uyuw using the K-th shortest path. If K-th shortest path does not exist, you should output "-1" (without quotes) instead.

Sample

|Inputcopy|Outputcopy|
|---|---|
|2 2<br>1 2 5<br>2 1 4<br>1 2 2|14|

## 题解
我们这一题要求我们的第 k 短路，一个思路是用我们的 $A$ 算法，当某个位置出现了 K 次，那么此时的距离就是我们的第 K 段路，这里我们要用我们的 dij 来计算，否则我们就是计算出一个错误的结果。

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<queue> 
using namespace std;
typedef pair<int,int> P;
const int inf=0x3f3f3f3f;
int n,m,ai,bi,ti,s,t,k,head[1005],cnt,dis[1005],ans,tim[1005],flag,head2[1005];
struct ed
{
	int to,next,cost;
}edge[200005],edge2[200005];//边与反边 
struct point
{
	int to,h,g;
	point(int _to,int _h,int _g) : to(_to),h(_h),g(_g){}//构造函数 
	friend bool operator <(point w,point l)//重载操作符 
	{
		return (w.h+w.g>l.h+l.g);
	}
};
void add(int w,int l,int e)
{
	cnt++;
	edge[cnt].to=l;
	edge[cnt].cost=e;
	edge[cnt].next=head[w];//建正边 
	head[w]=cnt;
	edge2[cnt].to=w;
	edge2[cnt].cost=e;
	edge2[cnt].next=head2[l];
	head2[l]=cnt;//建反边 
}
void dijkstra(void)
{
	memset(dis,0x3f,sizeof(dis));//距离数组 
	priority_queue<P,vector<P>,greater<P> > que;
	dis[t]=0;que.push(P(dis[t],t));
	while (!que.empty())
	{
		P u=que.top();que.pop();
		if (u.first>dis[u.second]) continue;
		int ki=u.first,di=u.second;
		for (int i=head2[di];i;i=edge2[i].next)//这里都要用反边，不能用正边 
		{
			int til=edge2[i].to;
			if (dis[til]>dis[di]+edge2[i].cost)
			{
				dis[til]=dis[di]+edge2[i].cost;
				que.push(P(dis[til],til));
			}
		}
	}
}
void Astar(void)
{
	if (dis[s]==inf) return;
	priority_queue<point> que;
	que.push(point(s,0,0));
	while (!que.empty())
	{
		point u=que.top();que.pop();
		tim[u.to]++;//该结点弹出次数加1 
		if (u.to==t&&tim[u.to]==k)//如果是终点且弹出次数等于k 
		{
			printf("%d",u.g);flag=1;//输出并结束进程 
			return;
		}
		if (tim[u.to]>k) continue;//如果非终点的结点弹出超过k次，跳过 
		for (int i=head[u.to];i;i=edge[i].next)
		{
			int til=edge[i].to;
			que.push(point(til,dis[til],u.g+edge[i].cost));//不管三七二十一直接加入队列中 
		}
	}
}
int main(void)
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&ai,&bi,&ti);
		add(ai,bi,ti);
	}
	scanf("%d%d%d",&s,&t,&k);
	if (s==t) k++;//如果起点等于终点，k加1 
	dijkstra();
	Astar();
	if (!flag) printf("-1");//如果没找到k短距离，输出-1 
	return 0;
}
```