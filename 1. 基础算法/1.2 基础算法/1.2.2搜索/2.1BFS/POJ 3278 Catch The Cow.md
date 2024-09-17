lm 同学在上课的时候就已经想好了中午去哪里吃饭.一下课,他就冲出教室,希望能以最快速度到达梆子井餐厅干饭。lm 同学初始时从数轴上的点 N (0 ≤ N ≤ 100,000) 开始，而梆子井餐厅在同一数轴上的点 K (0 ≤ K ≤ 100,000) 处。  
步行：lm同学可以在一分钟内从任意点 X 移动到点 X - 1 或 X + 1  
传送：lm同学可以在一分钟内从任意点 X 移动到点 2 × X。  
lm同学着急干饭,请问lm同学最快什么时候到达学子餐厅？

## Input

仅一行,输入N (0 ≤ N ≤ 100,000) 和 K (0 ≤ K ≤ 100,000) .

## Output

仅一行,输出lm同学最快什么时候到达梆子井餐厅

## Sample

|Inputcopy|Outputcopy|
|---|---|
|5 17|4|

## Hint

最快到达餐厅的方式为5-10-9-18-17, 一共需要四分钟

## 题解
我们这一题理论上如果没有第二个部分，我们就能转化为一个同源最短路的问题，但是因为有了第二步，所以我们就不能够这样去做了，我们现在需要用我们的 dfs 爆搜或是 bfs 爆搜，而因为我们题目中要求我们给出到达目的地的最小时间，所以我们应该**考虑使用 bfs**，流程如下

终止条件：当我们到达了我们的目的地
转移条件：对于每一个点，我们可以转移到 x-1, x+1,2 * x 这三个点上，之后，我们标记我们原来的点为已处理，之后如果的数字是已处理的，我们直接跳过即可。

**优化：当我们乘 2 之后，我们和目的地的差值大于我们目前的直接差值，我们可以直接不走这一个选项，

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <stack>
#include <cmath>
#include <set>
#include <map>
using namespace std;
const int MAXN=100009;
bool vis[MAXN];
int d[MAXN];
int n,k;
void init()
{
    read(n);    read(k);
    if(n>k)
    {
        printf("%d\n",n-k);
        exit(0);
    }
}

void work()
{
    queue<int> q;
    vis[n]=1;   d[n]=0;
    q.push(n);
    while(!q.empty())
    {
        int u=q.front();    q.pop();
        if(u==k)
        {
            printf("%d\n",d[k]);
            return;
        }
        int x;
        x=u+1;
        if(x>=0&&x<=100000&&!vis[x])
        {
            d[x]=d[u]+1;
            vis[x]=1;
            q.push(x);
        }
        x=u-1;
        if(x>=0&&x<=100000&&!vis[x])
        {
            d[x]=d[u]+1;
            vis[x]=1;
            q.push(x);
        }
        x=u*2;
        if(x>=0&&x<=100000&&!vis[x])
        {
            d[x]=d[u]+1;
            vis[x]=1;
            q.push(x);
        }
    }
}

int main()
{
    init();
    work();
    return 0;
}

```