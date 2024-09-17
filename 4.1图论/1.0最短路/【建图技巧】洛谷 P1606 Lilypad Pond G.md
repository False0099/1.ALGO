# [USACO 07 FEB] Lilypad Pond G

## 题面翻译

为了让奶牛们娱乐和锻炼，农夫约翰建造了一个美丽的池塘。这个长方形的池子被分成了 $M$ 行 $N$ 列个方格（$1 \le M,N \le 30$）。一些格子是坚固得令人惊讶的莲花，还有一些格子是岩石，其余的只是美丽、纯净、湛蓝的水。

贝西正在练习芭蕾舞，她站在一朵莲花上，想跳到另一朵莲花上去，她只能从一朵莲花跳到另一朵莲花上，既不能跳到水里，也不能跳到岩石上。

贝西的舞步很像象棋中的马步：每次总是先横向移动一格，再纵向移动两格，或先纵向移动两格，再横向移动一格。最多时，贝西会有八个移动方向可供选择。

约翰一直在观看贝西的芭蕾练习，发现她有时候不能跳到终点，因为中间缺了一些荷叶。于是他想要添加几朵莲花来帮助贝西完成任务。一贯节俭的约翰只想添加最少数量的莲花。当然，莲花不能放在石头上。

请帮助约翰确定必须要添加的莲花的最少数量，以及有多少种放置这些莲花的方法。

## 题目描述

FJ has installed a beautiful pond for his cows' aesthetic enjoyment and exercise.

The rectangular pond has been partitioned into square cells of M rows and N columns (1 ≤ M ≤ 30; 1 ≤ N ≤ 30). Some of the cells have astonishingly sturdy lilypads; others have rocks; the remainder are just beautiful, cool, blue water.

Bessie is practicing her ballet moves by jumping from one lilypad to another and is currently located at one of the lilypads. She wants to travel to another lilypad in the pond by jumping from one lilypad to another.

Surprising only to the uninitiated, Bessie's jumps between lilypads always appear as a chess-knight's move: one move in one direction and then two more in the orthogonal direction (or perhaps two in one direction and then one in the orthogonal direction).

Farmer John is observing Bessie's ballet drill and realizes that sometimes she might not be able to jump to her destination lilypad because intermediary lilypads are missing.

Ever thrifty, he wants to place additional lilypads so she can complete her quest (perhaps quickly, perhaps by using a large number of intermediate lilypads). Of course, lilypads cannot be placed where rocks already intrude on a cell.

Help Farmer John determine the minimum number of additional lilypads he has to place, and in how many ways he can place that minimum number.

## 输入格式

第一行两个用空格分开的整数 $M$ 和 $N$。

第二行到 $M+1$ 行，第 $i+1$ 行有 $N$ 个用空格分开的整数，描述了池塘第 $i$ 行的状态：

- $0$ 为水，$1$ 为莲花，$2$ 为岩石，$3$ 为贝西所在的起点，$4$ 为贝西想去的终点。

## 输出格式

第一行一个整数，需要增加的最少莲花数；如果无解，输出 $-1$。

第二行输出放置这些莲花的方案数量，保证这个数字可用一个 $64$ 位的有符号整数，表示。

特别地，如果第一行是 $-1$，不要输出第二行。

## 样例 #1

### 样例输入 #1

```
4 5
1 0 0 0 0
3 0 0 0 0
0 0 2 0 0
0 0 0 4 0
```

### 样例输出 #1

```
2
3
```

## 提示

### 样例解释

池塘分成四行五列，贝西的起点在第二行第一列，想去的终点在第四行第四列，池塘里一共有三朵莲花和一块石头。

最少需要两朵莲花，有三种方式可以放置，

如下 $\verb!X!$ 所示：

$$\begin{bmatrix}
\verb!10000! \\
\verb!30X00! \\
\verb!00200! \\
\verb!0X040! \\
\end{bmatrix},\begin{bmatrix}
\verb!10X00! \\
\verb!30000! \\
\verb!0X200! \\
\verb!00040! \\
\end{bmatrix},\begin{bmatrix}
\verb!10X00! \\
\verb!3000X! \\
\verb!00200! \\
\verb!00040! \\
\end{bmatrix}
$$


## 题解
我们这一题考虑一下能否用双向广搜的方法来求解我们这一题，我们这一题需要我们用我们的最短路进行一个计数：我们**对我们的二维数组建图，然后问我们走到目标的最短路径是多少**？

问题 1：怎么建图？
我们首先，对于我们二维格点上的每一个点进行一个编号，
```cpp
for(int i=0;i<=n;i++){
	for(int j=0;j<=m;j++){
		if(map[i][j]==0||map[i][j]==3){
			memset(used,0,sizeof used);
			set(bianhao[i][j],i,j);
		}
	}
}
```

然后我们考虑用 dfs 去进行我们的建图。
```cpp
void set(int num,int x,int y){
	if(used[x][y]) return;
	used[x][y]=true;
	for(int i=0;i<8;i++){
		int nowx=x+fx[i];
		int nowy=y+fy[i];
		if(now>=1&&nowx<=n&&nowy>=1&&nowy<=n&!used[nowx][nowy])
		if(map[nowx][nowy]==1) set(num,nowx,nowy);
	}

}
```

2. 我们直接跑一个最短路即可。

```cpp
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>

#define man 35
#define maxn 1233333

using namespace std;

inline int read ()
{
    int f = 1, x = 0;
	char ch;
    do {ch = getchar (); if (ch== '-') f = -1;} while (ch < '0' || ch > '9');
    do {x = x * 10 + ch - '0'; ch = getchar ();} while (ch >= '0' && ch <= '9');
    return f * x;
}

struct node
{
	int q, z, next;
} edge[maxn * 5];

int n, m;
int map[man][man];
int bianhao[man][man];
int qx, qy, zx, zy;
bool used[man][man];
int head[maxn];
int fx[] = {2, -2, 2, -2, -1, 1, -1, 1};
int fy[] = {1, 1, -1, -1, 2, 2, -2, -2};
int cnt;

int d[maxn];
long long tot[maxn];
bool in_que[maxn];

queue < int > q;

void add (int q, int z)
{
	edge[++ cnt].q = q;
	edge[cnt].z = z;
	edge[cnt].next = head[q];
	head[q] = cnt;
}

void This_is_for_you (int num, int x, int y)
{
	if (used[x][y]) return ;
	used[x][y] = true;
	for (int i = 0; i < 8; i ++)
	{
		int nowx = x + fx[i]; int nowy = y + fy[i];
		if (nowx >= 1 && nowx <= n && nowy >= 1 && nowy <= m && !used[nowx][nowy])
		{
			if (map[nowx][nowy] == 1) This_is_for_you (num, nowx, nowy);
			else
			if (map[nowx][nowy] != 2)
			{
				used[nowx][nowy] = true;
				int zd = bianhao[nowx][nowy];
				add (num, zd);
			}
		}
	}
}

void so_go_and_do_it ()
{
	int sta = bianhao[qx][qy]; int en = bianhao[zx][zy];
	memset (d, 0x3f, sizeof (d));
	d[sta] = 0;
	in_que[sta] = true;
	tot[sta] = 1;
	q.push (sta);
	while (!q.empty ())
	{
		int now = q.front (); q.pop (); in_que[now] = false;
		for (int i = head[now]; i; i = edge[i].next)
		{
			int end = edge[i].z;
			int newd = d[now] + 1;
			if (d[end] > newd)
			{
				d[end] = newd;
				tot[end] = tot[now];
				if (in_que[end] == false)
				{
					q.push (end);
					in_que[end] = true;
				}
			}
			else
			if (d[end] == newd) tot[end] += tot[now];
		}
	}
}

int main ()
{
	n = read (); m = read ();
	
	for (int i = 1; i <= n; i ++)
	 for (int j = 1; j <= m; j ++)
	 {
	 	map[i][j] = read ();
	 	bianhao[i][j] = (i - 1) * m + j;
	 	if (map[i][j] == 3) qx = i, qy = j;
	 	if (map[i][j] == 4) zx = i, zy = j;
	 }
	
	for (int i = 1; i <= n; i ++)
	 for (int j = 1; j <= m; j ++)
	 {
	 	if (map[i][j] == 0 || map[i][j] == 3) 
	 	{
	 		memset (used, 0, sizeof (used));
	 		This_is_for_you(bianhao[i][j], i, j);
		}
	 }
	so_go_and_do_it ();
	if (d[bianhao[zx][zy]] == 1061109567) puts("-1");
	else printf ("%d\n%lld", d[bianhao[zx][zy]] - 1, tot[bianhao[zx][zy]]);
	return 0;
}
```
```