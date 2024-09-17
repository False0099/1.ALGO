Benny has a spacious farm land to irrigate. The farm land is a rectangle, and is divided into a lot of samll squares. Water pipes are placed in these squares. Different square has a different type of pipe. There are 11 types of pipes, which is marked from A to K, as Figure 1 shows.  
  

![](https://vj.csgrandeur.cn/5ccee528d98fbd47847e51eb3c952d09?v=1695160744)

  

Figure 1

  
  
Benny has a map of his farm, which is an array of marks denoting the distribution of water pipes over the whole farm. For example, if he has a map  
  
ADC  
FJK  
IHE  
  
then the water pipes are distributed like  
  

![](https://vj.csgrandeur.cn/873260580c7a7a940f4ea25346ecdcb3?v=1695160744)

  

Figure 2

  
  
Several wellsprings are found in the center of some squares, so water can flow along the pipes from one square to another. If water flow crosses one square, the whole farm land in this square is irrigated and will have a good harvest in autumn.  
  
Now Benny wants to know at least how many wellsprings should be found to have the whole farm land irrigated. Can you help him?  
  
Note: In the above example, at least 3 wellsprings are needed, as those red points in Figure 2 show.  

## Input

There are several test cases! In each test case, the first line contains 2 integers M and N, then M lines follow. In each of these lines, there are N characters, in the range of 'A' to 'K', denoting the type of water pipe over the corresponding square. A negative M or N denotes the end of input, else you can assume 1 <= M, N <= 50.  

## Output

For each test case, output in one line the least number of wellsprings needed.  

Sample

|Inputcopy|Outputcopy|
|---|---|
|2 2<br>DK<br>HF<br><br>3 3<br>ADC<br>FJK<br>IHE<br><br>-1 -1|2<br>3|


## 题解
我们这一题类似于我们的 FLOOD FILL 操作，我们就找到每个点，能够到达的点，类似于我们的二维并查集？

我们就把我们的二维点映射到一维上，然后，我们的问题就变成了给定若干边，然后给定 n* m 个点，问要多少个能让我们联通。

本题中还有一些细节，就是我们输入时给定我们的水管，我们再每个点连边时，还要注意连边两侧必须是水管匹配的才能进行连边，否则我们不能进行我们的连边，也就不能进行我们的并查集。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 50;
int n,m,ans,pre[maxn*maxn+10];
int zz[11][4]={{1,1,0,0},{1,0,0,1},{0,1,1,0},{0,0,1,1},
               {1,0,1,0},{0,1,0,1},{1,1,0,1},{1,1,1,0},
               {0,1,1,1},{1,0,1,1},{1,1,1,1}
};
char a[maxn][maxn];
void Init(int x)
{
    for(int i=1;i<=x;i++) pre[i]=i;
    ans=x;
}
int f(int x)
{
    if(x==pre[x]) return x;
    else
    {
        pre[x]=f(pre[x]);
        return pre[x];
    }
}
void Merge(int ax,int ay,int bx,int by,int xh)
{
    if(bx>n||by>m) return ;
    int fg=0;
    int ta=a[ax][ay]-'A';
    int tb=a[bx][by]-'A';
    if(xh==1) //水平 
    {
        if(zz[ta][3]&&zz[tb][1]) fg=1;
    }
    else if(xh==2) //竖直方向 
    {
        if(zz[ta][2]&&zz[tb][0]) fg=1;
    }
    if(fg)
    {
        int t1=f((ax-1)*m+ay);
        int t2=f((bx-1)*m+by);
        if(t1!=t2)
        {
            pre[t2]=t1;
            ans--;
        }
    }
}
int main(void)
{
    int i,j;
    while(~scanf("%d %d",&n,&m)&&(n+m)>0)
    {
        Init(m*n);
        for(i=1;i<=n;i++) scanf("%s",a[i]+1);
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=m;j++)
            {
                Merge(i,j,i,j+1,1);
                Merge(i,j,i+1,j,2);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
```