![](https://vj.csgrandeur.cn/839547145686ac928288e786d4a6c17d?v=1698692937)

  
  With the 60th anniversary celebration of Nanjing University of Science and Technology coming soon, the university sets n tourist spots to welcome guests. Of course, Redwood forests in our university and its Orychophragmus violaceus must be recommended as top ten tourist spots, probably the best of all. Some undirected roads are made to connect pairs of tourist spots. For example, from Redwood forests (suppose it’s a) to fountain plaza (suppose it’s b), there may exist an undirected road with its length c. By the way, there is m roads totally here. Accidently, these roads’ length is an integer, and all of them are different. Some of these spots can reach directly or indirectly to some other spots. For guests, they are travelling from tourist spot s to tourist spot t, they can achieve some value f. According to the statistics calculated and recorded by us in last years, We found a strange way to calculate the value f:  
  From s to t, there may exist lots of different paths, guests will try every one of them. One particular path is consisted of some undirected roads. When they are travelling in this path, they will try to remember the value of longest road in this path. In the end, guests will remember too many longest roads’ value, so he cannot catch them all. But, one thing which guests will keep it in mind is that the minimal number of all these longest values. And value f is exactly the same with the minimal number.  
  Tom200 will recommend pairs (s, t) (start spot, end spot points pair) to guests. P guests will come to visit our university, and every one of them has a requirement for value f, satisfying f>=t. Tom200 needs your help. For each requirement, how many pairs (s, t) you can offer?  

Input

  Multiple cases, end with EOF.  
  First line:n m  
  n tourist spots ( 1<n<=10000), spots’ index starts from 0.  
  m undirected roads ( 1<m<=500000).  
  
  Next m lines, 3 integers, a b c  
  From tourist spot a to tourist spot b, its length is c. 0<a, b<n, c(0<c<1000000000), all c are different.  
  
  Next one line, 1 integer, p (0<p<=100000)  
  It means p guests coming.  
  
  Next p line, each line one integer, t(0<=t)  
  The value t you need to consider to satisfy f>=t.  

Output

  For each guest's requirement value t, output the number of pairs satisfying f>=t.  
  Notice, (1,2), (2,1) are different pairs.  

Sample

|Inputcopy|Outputcopy|
|---|---|
|2 1<br>0 1 2<br>3<br>1<br>2<br>3<br>3 3<br>0 1 2<br>0 2 4<br>1 2 5<br>5<br>0 <br>2<br>3<br>4<br>5|2<br>2<br>0<br>6<br>6<br>4<br>4<br>0|

题意：给定一个边权都不一样的图，然后给出10W 个询问，每个询问有个 T，求图中任意两点所有路径中满足最长边中的最小值（瓶颈边）大于等于 T 的(s,t)对数

## 题解
我们按照 Kruskal 的顺序合并边，每一次合并边，可以发现，我们合并的边，就是我们的连接两个集合的瓶颈路，这样我们就可以求出以这条边为瓶颈边的定点对数，这一题也与我们的启发式合并哪一题[[【暴力维护】路径最小值]]有一定的类似之处。

```cpp
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;
 
const int N = 10010;
const int M = 500010;
 
int sum[N];
int fa[N];
int tot[N];
int cnt;
vector <int> v;
 
struct edge
{
    int a, b, w;
    edge() {}
    edge(int a, int b, int w) : a(a), b(b), w(w) {}
    bool operator < (const edge &rhs) const
    {
        return w < rhs.w;
        if(a != rhs.a)
            return a < rhs.a;
        if(b != rhs.b)
            return b < rhs.b;
    }
} e[M];
 
void init()
{
    cnt = 1;
    v.clear();
    for(int i = 0; i <= N; i++)
    {
        fa[i] = i;
        sum[i] = 1;
    }
    memset(tot, 0, sizeof(tot));
}
 
int Find(int x)
{
    if(x == fa[x])
        return x;
    return fa[x] = Find(fa[x]);
}
 
int main()
{
    int n, m, q;
    while(~scanf("%d%d", &n, &m))
    {
        init();
        for(int i = 0; i < m; i++)
        {
            int a, b, w;
            scanf("%d%d%d", &a, &b, &w);
            e[i] = edge(a, b, w);
        }
        sort(e, e + m);
        for(int i = 0; i < m; i++)
        {
            int fx = Find(e[i].a);
            int fy = Find(e[i].b);
            if(fx != fy)
            {
                v.push_back(e[i].w);
                tot[cnt++] = sum[fx] * sum[fy] * 2;
                sum[fy] += sum[fx];
                fa[fx] = fy;
            }
        }
        for(int i = 1; i < cnt; i++)
            tot[i] += tot[i - 1];
        scanf("%d", &q);
        for(int i = 0; i < q; i++)
        {
            int w;
            scanf("%d", &w);
            int idx = lower_bound(v.begin(), v.end(), w) - v.begin();
            printf("%d\n", tot[cnt - 1] - tot[idx]);
        }
    }
    return 0;
}
```