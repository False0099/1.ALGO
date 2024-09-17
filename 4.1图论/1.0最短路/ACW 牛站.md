# 知识点
  ## [[Floyd算法]] [[快速幂]] [[求最值]]
# 题目
 给定一张由 T条边构成的无向图，点的编号为 1∼1000之间的整数。

求从起点 S到终点 E恰好经过 N条边（可以重复经过）的最短路。

注意: 数据保证一定有解。

# 输入格式
第 1 行：包含四个整数 N，T，S，E。

第 2.. T+1行：每行包含三个整数，描述一条边的边长以及构成边的两个点的编号。

# 输出格式
输出一个整数，表示最短路的长度。

# 数据范围
2≤T≤100
,
2≤N≤106
# 输入样例 ：
2 6 6 4
11 4 6
4 4 8
8 4 9
6 6 8
2 6 9
3 8 9
# 输出样例 ：
10

# 思路
 恰好经过 n 条边到达某一位置的最短距离，我们应该建立一个模板。我们按照类 Floyd 算法的思路，期中 res【i】【j】储存的是从 i 到 j 恰好经历 n 条边所需要的最小的代价。
 我们的按照从 1 开始倍增我们每一次走过的边数，知道最后我们走到了最后的位置。
 每一次走过的边数的数组我们可以也可以通过类 floyd 算法算法来进行·
 这个算法利用了扩展的矩阵乘法，即 $cij = min（aik+akj，cij）$ 表示我们走一步能从 i 走到 k 然后再走一步能走到哪里。
 我们最后只需要求矩阵的 N 次幂后我们所能获得的 $c[start][end]$ 就可以了。
# AC 代码
```cpp
#include<iostream>
#include<cstring>
#include<map>

using namespace std;

const int N=210;

int res[N][N],g[N][N];
int k,n,m,S,E;
map<int,int> id;

void mul(int c[][N],int a[][N],int b[][N])
{
    static int temp[N][N];
    memset(temp,0x3f,sizeof temp);
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                temp[i][j]=min(temp[i][j],a[i][k]+b[k][j]);
    memcpy(c,temp,sizeof temp);
}//mul函数意味着我们将a矩阵按照b矩阵的方式移动后成为c矩阵的样子，主要是通过temp数组来限制了我们每一次走的次数是恒定的，才使得floyd算法有了统计边数的能力。

void qmi()
{
    memset(res,0x3f,sizeof res);
    for(int i=1;i<=n;i++) res[i][i]=0;//经过0条边
    while(k)//更新的过程
    {
        if(k&1) mul(res,res,g);//res=res*g;根据k决定是否用当前g的结果去更新res
        mul(g,g,g);//g=g*g;g的更新
        k>>=1;
    }
}

int main()
{
    cin>>k>>m>>S>>E;//虽然点数较多，但由于边数少，所以我们实际用到的点数也很少，可以使用map来离散化来赋予
    //他们唯一的编号
    memset(g,0x3f,sizeof g);
    //这里我们来解释一下为什么不去初始化g[i][i]=0呢？
    //我们都知道在类Floyd算法中有严格的边数限制，如果出现了i->j->i的情况其实在i->i中我们是有2条边的
    //要是我们初始化g[i][i]=0,那样就没边了，影响了类Floyd算法的边数限制！
    if(!id.count(S)) id[S]=++n;
    if(!id.count(E)) id[E]=++n;
    S=id[S],E=id[E];
    while(m--)
    {
        int a,b,c;
        scanf("%d%d%d",&c,&a,&b);
        if(!id.count(a)) id[a]=++n;
        if(!id.count(b)) id[b]=++n;
        a=id[a],b=id[b];
        g[a][b]=g[b][a]=min(g[a][b],c);
    }
    qmi();
    cout<< res[S][E] <<endl;
    return 0;
}

作者：Accepting
链接：https://www.acwing.com/solution/content/17209/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
# 备注
