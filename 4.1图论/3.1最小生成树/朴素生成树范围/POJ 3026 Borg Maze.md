The Borg is an immensely powerful race of enhanced humanoids from the delta quadrant of the galaxy. The Borg collective is the term used to describe the group consciousness of the Borg civilization. Each Borg individual is linked to the collective by a sophisticated subspace network that insures each member is given constant supervision and guidance.  
  
Your task is to help the Borg (yes, really) by developing a program which helps the Borg to estimate the minimal cost of scanning a maze for the assimilation of aliens hiding in the maze, by moving in north, west, east, and south steps. The tricky thing is that the beginning of the search is conducted by a large group of over 100 individuals. Whenever an alien is assimilated, or at the beginning of the search, the group may split in two or more groups (but their consciousness is still collective.). The cost of searching a maze is definied as the total distance covered by all the groups involved in the search together. That is, if the original group walks five steps, then splits into two groups each walking three steps, the total distance is 11=5+3+3.

Input

On the first line of input there is one integer, N <= 50, giving the number of test cases in the input. Each test case starts with a line containg two integers x, y such that 1 <= x,y <= 50. After this, y lines follow, each which x characters. For each character, a space `` '' stands for an open space, a hash mark ``#'' stands for an obstructing wall, the capital letter ``A'' stand for an alien, and the capital letter ``S'' stands for the start of the search. The perimeter of the maze is always closed, i.e., there is no way to get out from the coordinate of the ``S''. At most 100 aliens are present in the maze, and everyone is reachable.

Output

For every test case, output one line containing the minimal cost of a succesful search of the maze leaving no aliens alive.

Sample




## 题解
给定一个迷宫，迷宫中有四种格子：

"#"：墙，不能走上去，也不能穿过。  
" "： 空气，可以走上去。  
"S"：玩家的起始点。  
"A"：关键节点，玩家必须要走到所有关键节点过，才能通关。

游戏流程如下：

玩家从 "S" 点出发，玩家或玩家的分身在起始点和关键节点均可以召唤分身，分身走到关键节点等同玩家走到关键节点。

请你设计一条路线，使得玩家通关时，玩家和玩家的分身所走的路径总长度最小。



我们这一题转化为我们求最小生成树就可以了。**因为我们把分身和本题所有路径加起来就相当于走了一个最小生成树。**

```cpp
include<stdio.h>
#include<math.h>
#include<queue>
#include<stdlib.h>
#include<string.h>
const int N=251;
const int inf=0x3fffffff;
using namespace std;
int num,f[N],n,m,k,map[51][51],dir[4][2]={0,1,0,-1,1,0,-1,0};
bool vis[51][51];
char cap[51][51];
struct edge
{
	int st,ed,w;
}e[N*N];
struct node
{
	int x,y;
}p[N];
void addedge(int x,int y,int w)
{
	e[num].st=x;e[num].ed=y;e[num++].w=w;
}
int dis(int i,int j)
{
	return abs(p[i].x-p[j].x)+abs(p[i].y-p[j].y);
}
int cmp(void const *a,void const *b)
{
	edge *c,*d;
	c=(edge *)a;
	d=(edge *)b;
	return c->w-d->w;
}
int find(int a)
{
	if(a!=f[a])
		f[a]=find(f[a]);
	return f[a];
}
void bfs(int u)
{
	queue<edge>Q;
	edge cur,next;
	int i,j,x,y;
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
		{
			map[i][j]=inf;
			vis[i][j]=false;
		}
	map[p[u].x][p[u].y]=0;vis[p[u].x][p[u].y]=true;
	cur.st=p[u].x;cur.ed=p[u].y,cur.w=0;
	Q.push(cur);
	while(!Q.empty())
	{
		cur=Q.front();
		Q.pop();vis[cur.st][cur.ed]=false;
		for(i=0;i<4;i++)
		{
			next.st=x=cur.st+dir[i][0];
			next.ed=y=cur.ed+dir[i][1];
			if(x>=0&&x<n&&y>=0&&y<m&&cap[x][y]!='#')
			{
				next.w=cur.w+1;
				if(map[x][y]>next.w)
				{
					map[x][y]=next.w;
					if(vis[x][y]==false)
					{Q.push(next);vis[x][y]=true;}
				}
			}
		}
	}
	for(i=1;i<k;i++)
	{
		if(i==u)continue;
		addedge(u,i,map[p[i].x][p[i].y]);
	}
	
}
int main()
{
	int i,j,t,sum,x,y;
	char str[100],ch;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&m,&n);
		ch=getchar();
		while(ch!='\n')
			ch=getchar();
		k=1;num=0;sum=0;
		for(i=0;i<n;i++)
		{
			gets(str);
			for(j=0;j<m;j++)
			{
				cap[i][j]=str[j];
				if(str[j]=='A'||str[j]=='S')
				{p[k].x=i;p[k++].y=j;}				 
			}
		}
		for(i=1;i<k;i++)
		{f[i]=i;bfs(i);}
		qsort(e,num,sizeof(e[0]),cmp);
		for(i=0;i<num;i++)
		{
			x=find(e[i].st);
			y=find(e[i].ed);
			if(x==y)continue;
			sum+=e[i].w;
			f[x]=find(y);
		}
		printf("%d\n",sum);
	}
	return 0;
}
```