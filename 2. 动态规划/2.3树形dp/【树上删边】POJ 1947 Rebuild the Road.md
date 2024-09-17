The cows have reconstructed Farmer John's farm, with its N barns (1 <= N <= 150, number 1..N) after the terrible earthquake last May. The cows didn't have time to rebuild any extra roads, so now there is exactly one way to get from any given barn to any other barn. Thus, the farm transportation system can be represented as a tree.  
  
Farmer John wants to know how much damage another earthquake could do. He wants to know the minimum number of roads whose destruction would isolate a subtree of exactly P (1 <= P <= N) barns from the rest of the barns.

将一棵n个节点的有根树，删掉一些边变成恰有m个节点的新树。求最少需要去掉几条边。

## Input

* Line 1: Two integers, N and P  
  
* Lines 2..N: N-1 lines, each with two integers I and J. Node I is node J's parent in the tree of roads.  

  
第一行两个整数N和P  
接下来N-1行，每行两个整数a和b，表示a是b的父亲

## Output

A single line containing the integer that is the minimum number of roads that need to be destroyed for a subtree of P nodes to be isolated.  

输出形成一个P大小的子树最少需要删掉的边

## Sample Input

11 6
1 2
1 3
1 4
1 5
2 6
2 7
2 8
4 9
4 10
4 11

## Sample Output

2

## Hint

[A subtree with nodes (1, 2, 3, 6, 7, 8) will become isolated if roads 1-4 and 1-5 are destroyed.]

## 题解
我们这一题为我们可以把我们的 $dp[u][j]$ 表示再结点 u 的子树上选 j 个结点最少要删除的边（其中，一定包含结点 u），那么我们有 $dp[u][1]=num[u]$, $num[u]$ 表示结点 u 的子节点个数。
那么我们的转移方程为 $dp[u][j]=min(dp[u][j],dp[son][k]-1+dp[u][j-k])$
最后，我们的结果就是 $min(dp[1][p],dp[i][p]+1)$.

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn=155;
const int inf=0x3f3f3f3f;
int n,p,ans,cnt,head[maxn],son[maxn],num[maxn],dp[maxn][maxn];

struct node{
    int v,nex;
}edge[maxn];

void adde(int u,int v){
    edge[++cnt].v=v;
    edge[cnt].nex=head[u];
    head[u]=cnt;
}

void dfs(int u){
    son[u]=1;
    dp[u][1]=num[u];
    for(int i=head[u];i;i=edge[i].nex){
        int v=edge[i].v;
        dfs(v);
        son[u]+=son[v];
        for(int j=son[u];j>0;--j)
            for(int k=1;k<=min(j-1,son[v]);++k)
                dp[u][j]=min(dp[u][j],dp[u][j-k]+dp[v][k]-1);
    }
}

int main(){
    while(~scanf("%d%d",&n,&p)){
        cnt=0;
        for(int i=1;i<=n;++i)
            head[i]=num[i]=0;
        for(int i=1;i<n;++i){
            int u,v;
            scanf("%d%d",&u,&v);
            adde(u,v);
            ++num[u];
        }
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                dp[i][j]=inf;
        dfs(1);
        ans=dp[1][p];
        for(int i=2;i<=n;++i)
            if(son[i]>=p)
                ans=min(ans,dp[i][p]+1);
        printf("%d\n",ans);
    }
    return 0;
}
```