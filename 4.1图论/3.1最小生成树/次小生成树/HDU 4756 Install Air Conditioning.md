![](https://vj.csgrandeur.cn/2b01badb9baed1b7ba09738a79d6aa46?v=1698677892)

  
  NJUST carries on the tradition of HaJunGong. NJUST, who keeps up the ”people-oriented, harmonious development” of the educational philosophy and develops the ”unity, dedication, truth-seeking, innovation” school motto, has now become an engineering-based, multidisciplinary university.  
  
  As we all know, Nanjing is one of the four hottest cities in China. Students in NJUST find it hard to fall asleep during hot summer every year. They will never, however, suffer from that hot this year, which makes them really excited. NJUST’s 60th birthday is approaching, in the meantime, 50 million is spent to install air conditioning among students dormitories. Due to NJUST’s long history, the old circuits are not capable to carry heavy load, so it is necessary to **set new high-load wires**. To reduce cost, every wire between two dormitory is considered a segment. Now, known about all the location of dormitories and a power plant, and the cost of high-load wire per meter, Tom200 wants to know in advance, under the premise of all dormitories being able to supply electricity, the minimum cost be spent on high-load wires. And this is the **minimum** strategy. But Tom200 is informed that there are so many wires between **two specific dormitories** that we cannot set a new high-load wire between these two, otherwise it may have potential risks. The problem is that Tom200 doesn’t know exactly which two dormitories until the setting process is started. So according to the minimum strategy described above, how much cost **at most** you'll spend?

Input

  The first line of the input contains a single integer T(T ≤ 100), the number of test cases.  
  For each case, the first line contains two integers n(3 ≤ n ≤ 1000), k(1 ≤ k ≤ 100). n represents n-1 dormitories and one power plant, k represents the cost of high-load wire per meter. n lines followed contains two integers x, y(0 ≤ x, y ≤ 10000000), representing the location of dormitory or power plant. Assume no two locations are the same, and no three locations are on a straight line. The first one is always the location of the power plant.

Output

  For each case, output the cost, correct to two decimal places.

Sample

|Inputcopy|Outputcopy|
|---|---|
|2<br><br>4 2<br>0 0<br>1 1<br>2 0<br>3 1<br><br>4 3<br>0 0<br>1 1<br>1 0<br>0 1|9.66<br>9.00|

## 题解
我们这一题相当于给定 n 个点，让我们求其中某些边不能用的最小生成树是多少。这个我们还是可以按照我们的次小生成树的思路去计算，我们设我们 $f[i][j]$ 为我们从 $i\to j$，新建边必须联向我们的 root 时，我们的最大花费，这里我们的 $root$ 需要我们枚举。然后我们就可以对于我们的树上
```cpp

#include <iostream>
#include <cstdio>
#include <cstring>
#include <math.h>

using namespace std;

const int maxn = 1010;
const int inf = 0x3f3f3f3f;

int n,m;
double mst,ans;
double map[maxn][maxn],dis[maxn],dp[maxn][maxn];
int pre[maxn],vis[maxn];
int flag[maxn][maxn];

struct Coor
{
    int x,y;
}coor[maxn];

struct Node
{
    int e,next;
}edge[maxn*2];
int head[maxn],pos;

double Dis(int x1,int y1,int x2,int y2)
{
    return sqrt(1.0*(x1-x2)*(x1-x2) + 1.0*(y1-y2)*(y1-y2));
}

void inputAndinit()
{
    pos = 0;
    for(int i = 0;i < n; i++) 
        scanf("%d%d",&coor[i].x,&coor[i].y);
    for(int i = 0;i < n; i++) {
        head[i] = -1;
        for(int j = i;j < n; j++) {
            dp[i][j] = dp[j][i] = inf;
            flag[i][j] = flag[j][i] = 0;
            if(i == j) map[i][i] = 0;
            else 
                map[i][j] = map[j][i] = Dis(coor[i].x,coor[i].y,coor[j].x,coor[j].y);
        }
    }
}

void prim()
{
    for(int i = 0;i < n; i++) {
        pre[i] = 0;
        vis[i] = 0;
        dis[i] = map[0][i];
    }
    dis[0] = inf;       //不可缺少
    pre[0] = -1;
    vis[0] = true;
    mst = 0;
    for(int i = 0;i < n-1; i++) {
        int k = 0;
        for(int j = 0;j < n; j++) {
            if(!vis[j] && dis[k] > dis[j])
                k = j;
        }
        mst += dis[k];
        vis[k] = true;
        if(pre[k] != -1) {
            edge[pos].e = k;
            edge[pos].next = head[pre[k]];
            head[pre[k]] = pos++;
            edge[pos].e = pre[k];
            edge[pos].next = head[k];
            head[k] = pos++;

            flag[k][pre[k]] = flag[pre[k]][k] = true;
        }
        for(int j = 0;j < n; j++) {
            if(!vis[j] && dis[j] > map[k][j]) {
                dis[j] = map[k][j];
                pre[j] = k;
            }
        }
    }
}

double dfs(int pos,int u,int fa)
{
    double ans = inf;
    for(int i = head[u];i != -1; i = edge[i].next) {
        int to = edge[i].e;
        if(to == fa) continue;
        double temp = dfs(pos,to,u);
        dp[u][to] = dp[to][u] = min(dp[u][to],temp);
        ans = min(ans,temp);
    }
    if(pos != fa) ans = min(ans,map[pos][u]);
    return ans;
}

void solve()
{
    for(int i = 0;i < n; i++) {
        dfs(i,i,-1);
    }
}

void output()
{
    double ans = mst;
    for(int i = 1;i < n; i++) {
        for(int j = i+1;j < n; j++) {
            if(flag[i][j]) {
                ans = max(ans,mst - map[i][j] + dp[i][j]);
            }
        }
    }
    printf("%.2f\n",ans*m);
}

int main(int argc, char const *argv[])
{
    //freopen("in.txt","r",stdin);

    int tt;
    scanf("%d",&tt);
    while(tt--) {
        scanf("%d%d",&n,&m);
        inputAndinit();
        prim();
        solve();
        output();
    }

    return 0;
}
```