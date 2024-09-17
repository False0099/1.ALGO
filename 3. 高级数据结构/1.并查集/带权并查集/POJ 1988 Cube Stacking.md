有 n 个箱子，编号从1到 n,初始时每个箱子单独为一列；  
接下来有p行输入，M, x, y 或者 C, x；  
对于M,x,y：表示将编号x的箱子所在的一列箱子搬到编号的y箱子所在的一列箱子上；  
对于C,x：表示求箱子编号x的箱子下面有多少个箱子；

## Input

第一行一个整数P,表示操作次数。  
接下来有p（1<= P <= 100,000）行输入，M, x, y 或者 C, x；（x,y<=N）  
箱子的个数N，不会出现在输入中。（1 <= N <= 30,000），初始时每个箱子单独为一列；你可以认为，操作过程中，不会出现编号大于30000的箱子

## Output

对于每个询问，输出相应的值。

## Sample Input

6
M 1 6
C 1
M 2 4
M 2 6
C 3
C 4

## Sample Output

1
0
2

## 题解
我们这一题是属于我们带权并查集的标准题，我们只需要记录，我们从哪一个箱子搬到哪一个箱子上，然后我们的转移固定为从前面的转移到后面的即可。
```cpp
```cpp
#include<string.h>
#include<stdio.h>
#include<algorithm>
 
using namespace std;
 
int fa[30500];// 存节点
int a[30500];// 以该节点为父节点的节点一共有几个
int b[30200];// 该节点到其父节点的距离
 
int find(int x)
{// 整个程序的核心算法 递归用的真是666666
    if(fa[x]!=x)
    {
        int s=fa[x];// 将其上一个节点的值付给s
        fa[x]=find(fa[x]);
        a[x]+=a[s];//x到其祖先节点的值等于他到他父节点的值加
                   //上起父节点到其祖先节点的距离
    }
    return fa[x];
}
 
void jion(int x,int y)
{
    int xx=find(x);
    int yy=find(y);
    if(xx!=yy)
    {
        fa[yy]=xx;
        a[yy]+=b[xx];//因为把yy的父节点接到xx的父节点后面了
        b[xx]+=b[yy];//所以yy到最终祖先节点的距离等于他到本来的祖先的距离
    }  //加上xx到其祖先节点的距离，此时新的祖先节点的子孙
}   //数量等于 以前 xx 的子孙加上 yy 的祖孙；
 
int main()
{
    int n,x,y;
    char c;
    while(~scanf("%d",&n))
    {
        for(int i=1;i<=30009;i++)
        {
            a[i]=0;//自己到自己的距离为0；
            b[i]=1;//刚开始的时候每个节点都是一个祖先节点包含自己所以为1；
            fa[i]=i;//第i个值为自己方便以后找祖先节点
        }
        while(n--)
        {
            scanf(" %c",&c);
            if(c=='M')
            {
                scanf("%d%d",&x,&y);
                jion(x,y);
            }
            else {
                scanf("%d",&x);
                int s=find(x);//查找 x的祖先节点
                printf("%d\n",b[s]-a[x]-1);
            }// x 下面的节点等于总结点数减去x到祖先节点的个数
        }
    }
    return 0;
}
```
```