XX 星球有很多城市，每个城市之间有一条或多条飞行通道，但是并不是所有的路都是很安全的，每一条路有一个安全系数 s,s 是在 0 和 1 间的实数(包括0，1)，一条从 u 到 v 的通道 P 的安全度为 $Safe(P) = s(e1)*s(e2)…*s(ek)$ e1,e2,ek 是 P 上的边，现在8600 想出去旅游，面对这这么多的路，他想找一条最安全的路。但是8600 的数学不好，想请你帮忙 ^_^

Input

输入包括多个测试实例，每个实例包括：  
第一行：n。n表示城市的个数n<=1000;  
接着是一个$n*n$的矩阵表示两个城市之间的安全系数，(0可以理解为那两个城市之间没有直接的通道)  
接着是Q个8600要旅游的路线,每行有两个数字，表示8600所在的城市和要去的城市

Output

如果86无法达到他的目的地，输出"What a pity!",  
其他的输出这两个城市之间的最安全道路的安全系数,保留三位小数。

Sample

|Inputcopy|Outputcopy|
|---|---|
|3<br>1 0.5 0.5<br>0.5 1 0.4<br>0.5 0.4 1<br>3<br>1 2<br>2 3<br>1 3|


## 题解
我们这一题要让我们求一个从起点到终点的乘积最大路，显然，我们可以用我们的 floyd 来求我们各个点之间的距离分别是多少。最大路显然也是具有我们的最优子结构性质的，所以我们直接套公式即可

```cpp
#include <stdio.h>
#define max(e1,e2) ((e1)>(e2)?(e1):(e2))

double  safe[1005][1005];
int n;

int main()
{

    while(scanf("%d",&n)!=EOF)
    {
        //cin>>n;

        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                //cin>>safe[i][j];
                scanf("%lf",&safe[i][j]);
            }
        }
        for(int k=1;k<=n;k++)
        {
            for(int i=1;i<=n;i++)
            {
                if(safe[i][k]>0.00000001)
                for(int j=1;j<=n;j++)
                {
                    safe[i][j]=max(safe[i][k]*safe[k][j],safe[i][j]);
                }
            }
        }
        int q;
        //cin>>q;
        scanf("%d",&q);
        int start,end;
        for(int i=0;i<q;i++)
        {
            //cin>>start>>end;
            scanf("%d%d",&start,&end);
            if(safe[start][end]<0.00000001) printf("What a pity!\n");
            else
            printf("%.3lf\n",safe[start][end]);

        }
    }
    return 0;
}
```