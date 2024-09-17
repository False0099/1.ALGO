ittle Johnny has got a new car. He decided to drive around the town to visit his friends. Johnny wanted to visit all his friends, but there was many of them. In each street he had one friend. He started thinking how to make his trip as short as possible. Very soon he realized that the best way to do it was to travel through each street of town only once. Naturally, he wanted to finish his trip at the same place he started, at his parents' house.  
  
The streets in Johnny's town were named by integer numbers from 1 to n, n < 1995. The junctions were independently named by integer numbers from 1 to m, m <= 44. No junction connects more than 44 streets. All junctions in the town had different numbers. Each street was connecting exactly two junctions. No two streets in the town had the same number. He immediately started to plan his round trip. If there was more than one such round trip, he would have chosen the one which, when written down as a sequence of street numbers is lexicographically the smallest. But Johnny was not able to find even one such round trip.  
  
Help Johnny and write a program which finds the desired shortest round trip. If the round trip does not exist the program should write a message. Assume that Johnny lives at the junction ending the street appears first in the input with smaller number. All streets in the town are two way. There exists a way from each street to another street in the town. The streets in the town are very narrow and there is no possibility to turn back the car once he is in the street  

Input

Input file consists of several blocks. Each block describes one town. Each line in the block contains three integers x; y; z, where x > 0 and y > 0 are the numbers of junctions which are connected by the street number z. The end of the block is marked by the line containing x = y = 0. At the end of the input file there is an empty block, x = y = 0.

Output

Output one line of each block contains the sequence of street numbers (single members of the sequence are separated by space) describing Johnny's round trip. If the round trip cannot be found the corresponding output block contains the message "Round trip does not exist."

Sample

|Inputcopy|Outputcopy|
|---|---|
|1 2 1<br>2 3 2<br>3 1 6<br>1 2 5<br>2 3 3<br>3 1 4<br>0 0<br>1 2 1<br>2 3 2<br>1 3 3<br>2 4 4<br>0 0<br>0 0|1 2 3 5 4 6 <br>Round trip does not exist.|

## 题解
我们这一题，给定了一个连通块，要我们求这个连通块内是否存在欧拉回路。如果存在，我们输出路径长度，否则，我们

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MaxN = 10010, MaxM = 100010;
int ver[MaxM], head[MaxN], Next[MaxM], edge[MaxM];
int n, tot;
int deg[MaxN];	//每一点的入度
int s[MaxM], ans[MaxM], top, t;		//栈中存放的是边的权值（边的编号）
bool vis[MaxM];	//记录每一条边是否已经访问

void add(int x, int y, int z)
{
	ver[++tot] = y, edge[tot] = z, Next[tot] = head[x], head[x] = tot;
}

void euler()
{
	top = 0, t = 0;
	s[++top] = 2, vis[2] = true, vis[3] = true;
	while(top > 0)
	{
		int e = s[top], x = ver[e], i = head[x];
		while(i && vis[i])	i = Next[i];
		if(i)
		{
			s[++top] = i;
			head[x] = Next[i];
			vis[i] = vis[i ^ 1] = true;	
		}else{
			ans[++t] = edge[s[top]];
			top--;
		}
	}
}

void solve()
{
	for(int i = 1; i <= n; ++i)
	{
		if(deg[i] & 1)
		{
			printf("Round trip does not exist.\n");
			return;
		}
	}
	euler();
	for (int i = t; i > 1; i--) printf("%d ", ans[i]);
	printf("%d\n", ans[1]);
}

int main()
{
	int x, y, z;
	while(true)
	{
		n = 0, tot = 1;
		memset(head, 0, sizeof head);
		memset(vis, false, sizeof vis);
		memset(Next, 0, sizeof Next);
		memset(deg, 0, sizeof deg);
		scanf("%d%d", &x, &y);
		if(0 == x && 0 == y)
		{
			break;
		}else{
			scanf("%d", &z);	
			add(x, y, z);
			add(y, x, z);
			deg[x]++, deg[y]++;
			n = max(x, n), n = max(y, n);
		}
		while(true)
		{
			scanf("%d%d", &x, &y);
			if(0 == x && 0 == y)
			{
				break;
			}else{
				scanf("%d", &z);
				add(x, y, z);
				add(y, x, z);
				deg[x]++, deg[y]++;
				n = max(x, n), n = max(y, n);
			}
		}
		solve();
	}
	return 0;
}

/*
1 2 1
2 3 2
3 1 6
1 2 5
2 3 3
3 1 4
0 0
1 2 1
2 3 2
1 3 3
2 4 4
0 0
0 0
*/

/*
1 2 3 5 4 6 
Round trip does not exist.
*/


```