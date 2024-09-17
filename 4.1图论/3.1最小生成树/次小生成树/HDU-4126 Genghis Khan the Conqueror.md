Genghis Khan(成吉思汗)(1162-1227), also known by his birth name Temujin(铁木真) and temple name Taizu(元太祖), was the founder of the Mongol Empire and the greatest conqueror in Chinese history. After uniting many of the nomadic tribes on the Mongolian steppe, Genghis Khan founded a strong cavalry equipped by irony discipline, sabers and powder, and he became to the most fearsome conqueror in the history. He stretched the empire that resulted in the conquest of most of Eurasia. The following figure (origin: Wikipedia) shows the territory of Mongol Empire at that time.  

![](https://vj.csgrandeur.cn/cc1beea55fa010ee4a157f70d2749e5d?v=1697517877)

  
Our story is about Jebei Noyan(哲别), who was one of the most famous generals in Genghis Khan’s cavalry. Once his led the advance troop to invade a country named Pushtuar. The knights rolled up all the cities in Pushtuar rapidly. As Jebei Noyan’s advance troop did not have enough soldiers, the conquest was temporary and vulnerable and he was waiting for the Genghis Khan’s reinforce. At the meantime, Jebei Noyan needed to set up many guarders on the road of the country in order to guarantee that his troop in each city can send and receive messages safely and promptly through those roads.  
  
There were N cities in Pushtuar and there were bidirectional roads connecting cities. If Jebei set up guarders on a road, it was totally safe to deliver messages between the two cities connected by the road. However setting up guarders on different road took different cost based on the distance, road condition and the residual armed power nearby. Jebei had known the cost of setting up guarders on each road. He wanted to guarantee that each two cities can safely deliver messages either directly or indirectly and the total cost was minimal.  
  
Things will always get a little bit harder. As a sophisticated general, Jebei predicted that there would be one uprising happening in the country sooner or later which might increase the cost (setting up guarders) on exactly ONE road. Nevertheless he did not know which road would be affected, but only got the information of some suspicious road cost changes. We assumed that the probability of each suspicious case was the same. Since that after the uprising happened, the plan of guarder setting should be rearranged to achieve the minimal cost, Jebei Noyan wanted to know the new expected minimal total cost immediately based on current information.  

Input

There are no more than 20 test cases in the input.  
For each test case, the first line contains two integers N and M (1<=N<=3000, 0<=M<=N×N), demonstrating the number of cities and roads in Pushtuar. Cities are numbered from 0 to N-1. In the each of the following M lines, there are three integers xi, yi and ci(ci<=107), showing that there is a bidirectional road between xi and yi, while the cost of setting up guarders on this road is ci. We guarantee that the graph is connected. The total cost of the graph is less or equal to 109.  
  
The next line contains an integer Q (1<=Q<=10000) representing the number of suspicious road cost changes. In the following Q lines, each line contains three integers Xi, Yi and Ci showing that the cost of road (Xi, Yi) may change to Ci (Ci<=107). We guarantee that the road always exists and Ci is larger than the original cost (we guarantee that there is at most one road connecting two cities directly). Please note that the probability of each suspicious road cost change is the same.  

Output

For each test case, output a real number demonstrating the expected minimal total cost. The result should be rounded to 4 digits after decimal point.  

Sample

|Inputcopy|Outputcopy|
|---|---|
|3 3<br>0 1 3<br>0 2 2<br>1 2 5<br>3<br>0 2 3<br>1 2 6<br>0 1 6<br>0 0|6.0000|

Hint

  
The initial minimal cost is 5 by connecting city 0 to 1 and city 0 to 2. In the first suspicious case, the minimal total cost is increased to 6;  
the second case remains 5; the third case is increased to 7. As the result, the expected cost is (5+6+7)/3 = 6.


## 题解
我们求 n 个点的最小生成树，其中有 q 次改变使得我们的某一条边权发生变化，求经过 q 次改变后，求我们期望的最小生成树是多少？

如果这条边是原图中的最小生成树的边，那么我们就先删掉这条边，然后可以得到两个连通分量，然后再加上可以连通着这两个连通分量的最小边，那么我们要怎么去求得这个最小边呢？我们可以使用树形 DP 的方法去求得每个点与其他点的除了最小生成树的最小边。
我们每一次 dfs，都只能得到一颗子树项根节点所能得到的最小距离。
![[无标题 15.png]]
我们可以**使用 $dp[i][j]$ 记录 i 点到 j 点删除 $i\to j$ 这条树上边后使我们的两个连通块的最小距离**，关于这一个的求法，我们可以先枚举我们的一个新建边的位置我们记为 root，我们可以发现，我们如果**我们每一次删边后，新建边的目标一定要指向我们的 root**，那么我们就可以通过 n 次树的遍历，来得到我们最后两个连通块相连时我们能够获得的最小距离，于是我们的代码如下:

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=3100;
const int inf=0x3f3f3f3f;
struct node {
   int u,v,w;
   bool operator <(node a)const {
       return w<a.w;
   }
} e[maxn*maxn];
struct edge {
   int v,next;
} t[maxn];
int head[maxn],cnt;
void add(int a,int b) {
   t[++cnt]=edge{b,head[a]};
   head[a]=cnt;
}
int mst,n,m,fa[maxn],dis[maxn][maxn],use[maxn][maxn],dp[maxn][maxn];
int findfa(int x) {
   return fa[x]=(fa[x]==x?x:findfa(fa[x]));
}
void eurl() {
   sort(e+1,e+m+1);
   mst=0;
   int tot=0;
   for(int i=1; i<=m; i++) {
       int u=e[i].u,v=e[i].v,w=e[i].w;
       int tx=findfa(u),ty=findfa(v);
       if(tx!=ty) {
           fa[tx]=ty;
           mst+=w;
           tot++;use[u][v]=use[v][u]=1;
           add(u,v);//根据我们的树建边
           add(v,u);
       }
       if(tot>=n-1)
           return ;
   }
}
int dfs(int root,int u,int f)
{
   int minn=inf;
   for(int i=head[u];i;i=t[i].next){
       int v=t[i].v;
       if(v==f)continue;
       int tmp=dfs(root,v,u);
       minn=min(tmp,minn);
       dp[u][v]=dp[v][u]=min(dp[u][v],tmp);
   }
   if(f!=root) minn=min(minn,dis[u][root]);
   return minn;
}
int main() {
   while(~scanf("%d%d",&n,&m)&&n&&m) {
       memset(dis,inf,sizeof dis);
       for(int i=1; i<=n; i++) {
           fa[i]=i;
           head[i]=0;
           dis[i][i]=0;
       }
       cnt=0;
       memset(head,0,sizeof head);
       memset(dp,inf,sizeof dp);
       memset(use,0,sizeof use);
       for(int i=1;i<=m;i++){
           int x,y,w;
           scanf("%d%d%d",&x,&y,&w);
           x++,y++;
           e[i]=node{x,y,w};
           dis[x][y]=dis[y][x]=w;
       }
       eurl();//最小生成树
       for(int i=1;i<=n;i++)dfs(i,i,i);
       int q;
       scanf("%d",&q);
       int l=q;
       double ans=0;
       while(l--){
           int x,y,w;
           scanf("%d%d%d",&x,&y,&w);
           x++,y++;
           if(use[x][y]) ans+=mst-dis[x][y]+min(dp[x][y],w);
           else ans+=mst;
       }
       printf("%.4f\n",ans/q);
   }
   return 0;
}

```
