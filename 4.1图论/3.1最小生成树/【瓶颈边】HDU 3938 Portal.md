小 s 最近学习了空间魔法，他能够在两个空间点处建立空间传送阵进行连接，整个空间包含 n 个点和 m 条边,每条边有一定的花费 cost，在两个点建立连接的代价是两点间所有路径中最小的路径代价 T，定义一条路径的代价 T 为路径中花费最大的那条边，现在小 s 想要多次询问你，如果对于一个能量值 s，他最多能够对多少对点建立传送阵进行连接呢？(你可以认为每对点的建立都是独立的，也就是说只要能建立的点都可以建立，建立之后不会产生花费)

## Input

输入包含多组数据，这就意味你的读入要一直到不等于EOF才能停止.

每组数据第一行包含三个整数 N, M , Q (1 < N ≤ 10,000, 0 < M ≤ 50,000, 0 < Q ≤ 10,000). 点的数量，边的数量以及询问的数量.

接下来m行，代表边的信息，a ，b，cost (1 ≤ a, b ≤ N, 0 ≤ cost ≤ 10^8)

最后Q行，每行一个整数s，代表小s询问的能量值(0 ≤ s ≤ 10^8).

## Output

Output the answer to each query on a separate line.

Sample

|Inputcopy|Outputcopy|
|---|---|
|10 10 10<br>7 2 1<br>6 8 3<br>4 5 8<br>5 8 2<br>2 8 9<br>6 4 5<br>2 1 5<br>8 10 5<br>7 3 7<br>7 8 8<br>10<br>6<br>1<br>5<br>9<br>1<br>8<br>2<br>7<br>6|36<br>13<br>1<br>13<br>36<br>1<br>36<br>2<br>16<br>13|


## 题解
我们本题要求的是我们图上任意两点之间的瓶颈边，我们瓶颈边一定就是我们最小生成树中的某一个部分。这一点我们也许可以用我们的反证法去证明，但总之，我们的步骤就是先对我们的图建立一个 Kruskal 树。**将每个查询保存起来，根据我们的 value，也就是我们的瓶颈边边长排序，如果比这个边长要长，我们就不加进去**，之后我们每一条边添加时，我们的贡献就是边添加前后，我们两侧的点的数量的成绩（乘法原理）
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 5;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
struct node{
    int u, v, val;
}e[N];
struct question{
    int val, id, ans;
}q[N];
int fa[N],num[N],n,m,query;
void init(){
    for(int i = 0;i < N;i ++)
        fa[i] = i,num[i] = 1;
}
int Find(int k){
    if(k != fa[k])
        fa[k] = Find(fa[k]);
    return fa[k];
}
int Merge(int x,int y){
    int dx = Find(x);
    int dy = Find(y);
    if(dx == dy)
        return 0;
    fa[dy] = dx;
    int tmp = num[dx];
    num[dx] = num[dx] + num[dy];
    return tmp*num[dy];
}
bool cmpEdge(node a,node b){
    return a.val < b.val;
}
bool cmpq1(question a,question b){
    return a.val <b.val;
}
bool cmpq2(question a,question b){
    return a.id < b.id;
}
int main()
{
    while(~scanf("%d%d%d",&n,&m,&query)){
        init();
        for(int i = 1;i <= m;i ++){
            scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].val);
        }
        for(int i = 1;i <= query;i ++){
            scanf("%d",&q[i].val);
            q[i].id = i;
            q[i].ans = 0;
        }
        sort(e + 1,e + m + 1,cmpEdge);
        sort(q + 1,q + query + 1,cmpq1);
        int p = 1;
        q[0].ans = 0;
        for(int i = 1;i <= query;i ++){
            q[i].ans = q[i-1].ans;
            while(e[p].val <= q[i].val && p <= m){
                q[i].ans += Merge(e[p].u,e[p].v);
                p ++;
            }
        }
        sort(q + 1,q + query + 1,cmpq2);
        for(int i = 1;i <= query;i ++)
            printf("%d\n",q[i].ans);
    }
	return 0;
}
```