## 描述 ：

对于一个迷宫而言，即使你不能迅速找到出路，也可以用一种简单的方法试探出走法。
比如在迷宫中，能直走时就直走，如果被墙阻挡，就优先向左拐（向当时你实际的左手方向转弯），如果不能左拐就沿原方向继续走，如果原方向也被阻挡则向右拐，如果这三个方向都被阻挡就向后转然后直走，接着继续优先向右拐……（当然，你也可以将所有的优先向左拐变为优先向右拐）。此外，如果给你足够的时间，你一定可以找到从起点到终点最短的路径和距离，而不需要每个方向试探。
希望你编写一个计算机程序，可以模拟第一种试探的方法，找到利用这种方法从起点走到终点的距离，同时也可以计算出从起点到终点的最短距离。

## 输入 ：

这个问题的第一行输入是一个整数n，表示迷宫的数量，即测试用例的数量。每个迷宫将包括一行大小描述，即以空格分割的两个整数，宽度w和高度h (3 ≤ w,  h ≤ 40)，后面是h行，每行w个字符代表迷宫布局（不含分割字符）。墙用符号('#')表示，空格用句号('.')表示，开头用'S'表示，出口用'E'表示。

## 输出 ：

对于输入中的每个迷宫，在单行上输出以空格隔开的3个整数，分别是：
1.	优先向左转，从S到E的步数。
2.	优先向右转，从S到E的步数。
3.	S到E的最短路径，小于等于前面二者。

## 注意 ：

只允许在水平或垂直方向上从一个正方形移动到另一个正方形;不允许沿对角线移动。从S到E的步数定义为从S到E经历过的单元格数，包含S和E，有些单元格可能重复被经历。只有一个S和一个E会出现在迷宫中，而且它们总是位于迷宫的某个边缘，而不是角落里。迷宫将被墙壁('#')完全包围，唯一的开口是S和E。S和E也将被至少一面墙('#')隔开。

样例：

## 输入 ：
2
8 8
########
#......#
#.####.#
#.####.#
#.####.#
#.####.#
#...#..#
$# S # E ####$
9 5
#########
#.#.#.#.#
S.......E
#.#.#.#.#
#########

输出：
37 5 5
17 17 9

## 题解
我们这一题不一般，因为他当中有一个走路的优先级顺序，所以我们需要用到 dfs 和 bfs 结合的思路，用 dfs 解决我们的优先性问题，用 bfs 解决我们的最短路问题。

注意，我们使用 dfs 时，因为我们**采用固定的顺序**，所以我们**不需要所谓的恢复现场**，。

```cpp
/*
Problem: 3083		User: *************
Memory: 728K		Time: 16MS
Language: G++		Result: Accepted
*/
#include"iostream"
#include"cstdio"
#include"cstring"
#include"cstdlib"
 
using namespace std;
 
typedef struct node
{
	int x;
	int y;
	int step;
}point;
 
int x,y;
char map[45][45];
bool book[45][45];  //检查是否访问过了
int move_1[4][4][2]=    //map[0] - 1,map[1]-2   map[2]-3   map[3]-4 左偏向 
{
    {{-1,0},{0,1},{1,0},{0,-1}},
    {{0,1},{1,0},{0,-1},{-1,0}},
    {{1,0},{0,-1},{-1,0},{0,1}},
    {{0,-1},{-1,0},{0,1},{1,0}}
};
int move_2[4][4][2]=   //右偏向 
{
	{{1,0},{0,1},{-1,0},{0,-1}},
    {{0,-1},{1,0},{0,1},{-1,0}},
    {{-1,0},{0,-1},{1,0},{0,1}},
    {{0,1},{-1,0},{0,-1},{1,0}}
};
int bx,by,ex,ey;
int left_;
int right_;
int minp;
int pre_dir;
bool bl;
bool br;
 
void dfs_left(int dx,int dy,int atom,int time)//atom表示方向
{
	int px,py;
	for(int i=0;i<4;i++)
	{
		px=dx+move_1[atom-1][i][0];
		py=dy+move_1[atom-1][i][1];
		if(px==ex&&py==ey) 
		{
			left_=time+1;
			bl=true;
			return ;
		}
		if(map[px][py]=='#'||px<1||px>x||py<1||py>y) continue;
		else
		{
			if(atom==4)
			{
				if(i==0) dfs_left(px,py,3,time+1);
				else if(i==1) dfs_left(px,py,4,time+1);
				else if(i==2) dfs_left(px,py,1,time+1);
				else dfs_left(px,py,2,time+1);
			}
			else if(atom==3)
			{
				if(i==0) dfs_left(px,py,2,time+1);
				else if(i==1) dfs_left(px,py,3,time+1);
				else if(i==2) dfs_left(px,py,4,time+1);
				else dfs_left(px,py,1,time+1);
			}
			else if(atom==2)
			{
				if(i==0) dfs_left(px,py,1,time+1);
				else if(i==1) dfs_left(px,py,2,time+1);
				else if(i==2) dfs_left(px,py,3,time+1);
				else dfs_left(px,py,4,time+1);
			}
			else
			{
				if(i==0) dfs_left(px,py,4,time+1);
				else if(i==1) dfs_left(px,py,1,time+1);
				else if(i==2) dfs_left(px,py,2,time+1);
				else dfs_left(px,py,3,time+1);
			}
			if(bl) return ;
		}
	}
}
 
void dfs_right(int dx,int dy,int atom,int time)
{
	int px,py;
	for(int i=0;i<4;i++)
	{
		px=dx+move_2[atom-1][i][0];
		py=dy+move_2[atom-1][i][1];
		if(px==ex&&py==ey) 
		{
			right_=time+1;
			br=true;
			return ;
		}
		if(map[px][py]=='#'||px<1||px>x||py<1||py>y) continue;
		else
		{
			if(atom==4)
			{
				if(i==0) dfs_right(px,py,1,time+1);
				else if(i==1) dfs_right(px,py,4,time+1);
				else if(i==2) dfs_right(px,py,3,time+1);
				else dfs_right(px,py,2,time+1);
			}
			else if(atom==3)
			{
				if(i==0) dfs_right(px,py,4,time+1);
				else if(i==1) dfs_right(px,py,3,time+1);
				else if(i==2) dfs_right(px,py,2,time+1);
				else dfs_right(px,py,1,time+1);
			}
			else if(atom==2)
			{
				if(i==0) dfs_right(px,py,3,time+1);
				else if(i==1) dfs_right(px,py,2,time+1);
				else if(i==2) dfs_right(px,py,1,time+1);
				else dfs_right(px,py,4,time+1);
			}
			else
			{
				if(i==0) dfs_right(px,py,2,time+1);
				else if(i==1) dfs_right(px,py,1,time+1);
				else if(i==2) dfs_right(px,py,4,time+1);
				else dfs_right(px,py,3,time+1);
			}
			if(br) return ;
		}
	}
}
 
void bfs()
{
	memset(book,0,sizeof(book));
	int nn[4][2]={{-1,0},{0,-1},{1,0},{0,1}};
	point queue[41*41];
	int head=1;
	int tail=2;
	queue[1].x=bx;
	queue[1].y=by;
	queue[1].step=1;
	book[bx][by]=true;
	while(head!=tail)
	{
		for(int i=0;i<4;i++)
		{
			int dx=queue[head].x+nn[i][0];
			int dy=queue[head].y+nn[i][1];
			if(map[dx][dy]=='E')
			{
				minp=queue[head].step+1;
				return ;
			}
			if(dx<1||dx>x||dy<1||dy>y||map[dx][dy]=='#'||book[dx][dy]) continue;
			else
			{
				book[dx][dy]=true;
				queue[tail].x=dx;
				queue[tail].y=dy;
				queue[tail].step=queue[head].step+1;
				tail++;
			}
		}
		head++;
	}
}
 
int main()
{
	int t;
	scanf("%d",&t);getchar();
	while(t--)
	{ 
	    bl=br=false;
		minp=left_=right_=1;  //刚开始S也算 
		scanf("%d%d",&y,&x);getchar();
		for(int i=1;i<=x;i++)
		{
			for(int j=1;j<=y;j++)
			{
				scanf("%c",&map[i][j]);
				if(map[i][j]=='S') 
				{
					bx=i,by=j;
					if(i==1) pre_dir=2;
					else if(i==x) pre_dir=4;
					else if(j==1) pre_dir=1;
					else if(j==y) pre_dir=3; 
				}
				if(map[i][j]=='E') ex=i,ey=j;
			}
			getchar();
		}
		dfs_left(bx,by,pre_dir,1);
		dfs_right(bx,by,pre_dir,1);
		bfs();
		printf("%d %d %d\n",left_,right_,minp);
	}
	return 0;
}
```