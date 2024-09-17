During the Warring States Period of ancient China(476 BC to 221 BC), there were seven kingdoms in China ---- they were Qi, Chu, Yan, Han, Zhao, Wei and Qin. Ying Zheng was the king of the kingdom Qin. Through 9 years of wars, he finally conquered all six other kingdoms and became the first emperor of a unified China in 221 BC. That was Qin dynasty ---- the first imperial dynasty of China(not to be confused with the Qing Dynasty, the last dynasty of China). So Ying Zheng named himself "Qin Shi Huang" because "Shi Huang" means "the first emperor" in Chinese.  

![](https://vj.csgrandeur.cn/da894c8b7e07190a463e00c9598bf3e7?v=1698561806)

  
Qin Shi Huang undertook gigantic projects, including the first version of the Great Wall of China, the now famous city-sized mausoleum guarded by a life-sized Terracotta Army, and a massive national road system. There is a story about the road system:  
There were n cities in China and Qin Shi Huang wanted them all be connected by n-1 roads, in order that he could go to every city from the capital city Xianyang.  
Although Qin Shi Huang was a tyrant, he wanted the total length of all roads to be minimum,so that the road system may not cost too many people's life. A daoshi (some kind of monk) named Xu Fu told Qin Shi Huang that he could build a road by magic and that magic road would cost no money and no labor. But Xu Fu could only build ONE magic road for Qin Shi Huang. So Qin Shi Huang had to decide where to build the magic road. Qin Shi Huang wanted the total length of all none magic roads to be as small as possible, but Xu Fu wanted the magic road to benefit as many people as possible ---- So Qin Shi Huang decided that the value of A/B (the ratio of A to B) must be the maximum, which A is the total population of the two cites connected by the magic road, and B is the total length of none magic roads.  
Would you help Qin Shi Huang?  
A city can be considered as a point, and a road can be considered as a line segment connecting two points.

Input

The first line contains an integer t meaning that there are t test cases(t <= 10).  
For each test case:  
The first line is an integer n meaning that there are n cities(2 < n <= 1000).  
Then n lines follow. Each line contains three integers X, Y and P ( 0 <= X, Y <= 1000, 0 < P < 100000). (X, Y) is the coordinate of a city and P is the population of that city.  
It is guaranteed that each city has a distinct location.

Output

For each test case, print a line indicating the above mentioned maximum ratio A/B. The result should be rounded to 2 digits after decimal point.

Sample

|Inputcopy|Outputcopy|
|---|---|
|2<br>4<br>1 1 20<br>1 2 30<br>200 2 80<br>200 1 100<br>3<br>1 1 20<br>1 2 30<br>2 2 40|65.00<br>70.00|


## 题解
最少代价使得所有点都连通，很容易能够想到最小生成树。

从最终答案是 A/B 入手，要使这个结果最大，但是明显 A 与 B 的大小会互相影响，故不符合贪心的要求。所以采用的只能是枚举每一条边，在指定 A 的前提下，使 B 最小。

考虑一下删边是两种情况：

1. i,j 边恰好在最小生成树上，那么直接删掉；
    
2. i,j 边不在最小生成树上，那么要在最小生成树中找到 i,j 路径上最长的边删去；
    

由于本题完全图的特殊性，如果 i,j 边在最小生成树上，那么 i,j 边直接就是路径上的最长边了，也即问题转化为给定两个点，要求在最小生成树上找到两个点路径上最长的边。

而这恰好是求解次小生成树的方法。

```cpp
/* ***********************************************
MYID    : Chen Fan
LANG    : G++
PROG    : 4081
************************************************ */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
#include <bitset>

using namespace std;

typedef struct pnod
{
    int x,y,p;
} pnode;
pnode p[1010];

typedef struct nod
{
    int a,b;
    double c;
    friend bool operator < (nod a,nod b)
    {
        return a.c>b.c;
    }
} node;

node edge[1000010];
int start[1010],num[1010];

bool op(node a,node b)
{
    if (a.a==b.a) return a.c<b.c;
    else return a.a<b.a;
}

node ntoh(int a,int b,double c)
{
    node x;
    x.a=a;
    x.b=b;
    x.c=c;
    return x;
}

double maxx[1010][1010];
bitset<1010> inway[1010];

double prim(int s,int n)
{
    /**/
    int list[1010],listail=1;
    list[1]=s;
    /**/
    priority_queue<node> heap;
    while (!heap.empty()) heap.pop();
    bitset<1010> flag;
    flag.reset();
    flag[s]=1;
    double ans=0;
    memset(maxx,0,sizeof(maxx));
    for (int i=0;i<num[s];i++) heap.push(edge[start[s]+i]);

    for (int i=1;i<n;i++)
    {
        node now=heap.top();
        heap.pop();
        while (flag[now.b])
        {
            now=heap.top();
            heap.pop();
        }
        /**/
        for (int j=1;j<=listail;j++) 
        {
            maxx[list[j]][now.b]=max(maxx[list[j]][now.a],now.c);
            maxx[now.b][list[j]]=maxx[list[j]][now.b];
        }
        listail++;
        list[listail]=now.b;
        /**/
        flag[now.b]=true;
        ans+=now.c;
        for (int j=0;j<num[now.b];j++)
        if (!flag[edge[start[now.b]+j].b]) heap.push(edge[start[now.b]+j]);
    }

    return ans;
}

double getdis(int x,int y)
{
    return sqrt((p[x].x-p[y].x)*(p[x].x-p[y].x)+(p[x].y-p[y].y)*(p[x].y-p[y].y));
}

int main()
{
    freopen("4081.txt","r",stdin);

    int t;
    scanf("%d",&t);
    for (int tt=1;tt<=t;tt++)
    {
        int n;
        scanf("%d",&n);
        for (int i=1;i<=n;i++) scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].p);

        int m=0;
        for (int i=1;i<=n;i++)
        {
            start[i]=m+1;
            num[i]=n-1;
            for (int j=1;j<=n;j++)
            if (i!=j)
            {
                m++;
                edge[m].a=i;
                edge[m].b=j;
                edge[m].c=getdis(i,j);
            }
        }
        
        double sum=prim(1,n);

        double ma=0;
        for (int i=1;i<=m;i++)
        {
            double temp=(p[edge[i].a].p+p[edge[i].b].p)/(sum-maxx[edge[i].a][edge[i].b]);
            if (ma<temp) ma=temp;
        }

        printf("%.2f\n",ma);
    }

    return 0;
}
```