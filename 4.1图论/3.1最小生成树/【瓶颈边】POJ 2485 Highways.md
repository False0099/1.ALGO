The island nation of Flatopia is perfectly flat. Unfortunately, Flatopia has no public highways. So the traffic is difficult in Flatopia. The Flatopian government is aware of this problem. They're planning to build some highways so that it will be possible to drive between any pair of towns without leaving the highway system.  
  
Flatopian towns are numbered from 1 to N. Each highway connects exactly two towns. All highways follow straight lines. All highways can be used in both directions. Highways can freely cross each other, but a driver can only switch between highways at a town that is located at the end of both highways.  
  
The Flatopian government wants to minimize the length of the longest highway to be built. However, they want to guarantee that every town is highway-reachable from every other town.

Input

The first line of input is an integer T, which tells how many test cases followed.  
The first line of each case is an integer N (3 <= N <= 500), which is the number of villages. Then come N lines, the i-th of which contains N integers, and the j-th of these N integers is the distance (the distance should be an integer within [1, 65536]) between village i and village j. There is an empty line after each test case.

Output

For each test case, you should output a line contains an integer, which is the length of the longest road to be built such that all the villages are connected, and this value is minimum.

Sample

|Inputcopy|Outputcopy|
|---|---|
|1<br><br>3<br>0 990 692<br>990 0 179<br>692 179 0|692|


## 题解
我们要求我们图中生成树的最长边最短，于是我们就可以先按照我们的边降序，然后再去一个一个一个的加，加到我们联通时的那一条边权就是我们的答案。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <cmath>
#include <stack>
#include <map>
#include <set>
using namespace std;
#define ms(x, n) memset(x,n,sizeof(x));
typedef  long long LL;
const int inf = 1<<30;
const LL maxn = 505;

int par[maxn*10], rak[maxn*10];
void init(int n){
    for(int i = 0; i < n; i++)
        par[i] = i, rak[i] = 0;
}
int findr(int x){
    if(x==par[x]) return x;
    else return par[x] = findr(par[x]);
}
bool isSame(int x, int y){return findr(x)==findr(y);}
void unite(int x, int y){
    x = findr(x), y = findr(y);
    if(x==y) return;
    if(rak[x] < rak[y])
        par[x] = y;
    else{
        par[y] = x;
        if(rak[x]==rak[y]) ++rak[x];
    }
}

struct Edge{
    int u, v, w;
    Edge(int uu, int vv, int ww){u = uu, v = vv, w = ww;}
    Edge(){u = 0, v = 0, w = inf;}
}es[maxn*maxn];
bool cmp(const Edge &a, const Edge &b){return a.w < b.w;}
int V, E = 0; //顶点数和边数
int Kruskal(){
    sort(es, es+E, cmp); //对边排序
    init(V);             //以点为元素做并查集初始化
    int ret = 0;

    for(int i = 0; i < E; i++){
        Edge cur = es[i];
        if(!isSame(cur.u, cur.v)){
            unite(cur.u, cur.v);//只要不是同一连通分量即归入生成树
            ret = max(cur.w, ret);
        }
    }
    return ret;
}

int main()
{
    int T, w;
    scanf("%d",&T);
    while(T--){
        E = 0;
        scanf("%d",&V);
        for(int i = 0; i < V; i++)
            for(int j = 0; j < V; j++){
                scanf("%d",&w);
                es[E++] = Edge(i, j, w);
            }

        printf("%d\n",Kruskal());
    }

	return 0;
}


```