Stan and Ollie play the game of Odd Brownie Points. Some brownie points are located in the plane, at integer coordinates. Stan plays first and places a vertical line in the plane. The line must go through a brownie point and may cross many (with the same x-coordinate). Then Ollie places a horizontal line that must cross a brownie point already crossed by the vertical line.  
Those lines divide the plane into four quadrants. The quadrant containing points with arbitrarily large positive coordinates is the top-right quadrant.  
  
The players score according to the number of brownie points in the quadrants. If a brownie point is crossed by a line, it doesn't count. Stan gets a point for each (uncrossed) brownie point in the top-right and bottom-left quadrants. Ollie gets a point for each (uncrossed) brownie point in the top-left and bottom-right quadrants.  
  
Stan and Ollie each try to maximize his own score. When Stan plays, he considers the responses, and chooses a line which maximizes his smallest-possible score.

Input

Input contains a number of test cases. The data of each test case appear on a sequence of input lines. The first line of each test case contains a positive odd integer 1 < n < 200000 which is the number of brownie points. Each of the following n lines contains two integers, the horizontal (x) and vertical (y) coordinates of a brownie point. No two brownie points occupy the same place. The input ends with a line containing 0 (instead of the n of a test).

Output

For each input test, print a line of output in the format shown below. The first number is the largest score which Stan can assure for himself. The remaining numbers are the possible (high) scores of Ollie, in increasing order.

Sample

|Inputcopy|Outputcopy|
|---|---|
|11<br>3 2<br>3 3<br>3 4<br>3 6<br>2 -2<br>1 -3<br>0 0<br>-3 -3<br>-3 -2<br>-3 -4<br>3 -7<br>0|Stan: 7; Ollie: 2 3;|

在平面直角坐标系中给你 N 个点，stan 和 ollie 玩一个游戏，首先 stan 在竖直方向上画一条直线，该直线必须要过其中的某个点，然后 ollie 在水平方向上画一条直线，该直线的要求是要经过一个 stan 之前画过的点。这时候平面就被分割成了四块，两个人这时候会有一个得分，stan 的得分是平面上第1、3象限内的点的个数，ollie 的得分是平面上第2、4象限内的点的个数，在统计的时候在所画线上的点都不计算在内。求最终 stan 使得自己的最差得分最高，并且输出此时 ollie 的得分。

我们先把数据离散化，同时记录每一个 X 左右边有多少，X 有多少，Y 同理；然后我们按先 X 再 Y 从小到大排序，再来扫描，用线段树记录区间里面的点的个数。

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using std::sort;
 
const int nsize=222222;
 
struct Point
{
    int x,y;
} pot[nsize];
 
int n,k,nx,ny,maxs;
int maxy[nsize],num[nsize<<2];
int lft[nsize],rgt[nsize];
int up[nsize],down[nsize];
int curx[nsize],cury[nsize];
int *px[nsize],*py[nsize];
int cntx[nsize],cnty[nsize];
 
int Max(int a1,int a2)
{
    return a1>a2?a1:a2;
}
 
int Min(int a1,int a2)
{
    return a1<a2?a1:a2;
}
 
bool cmp1(int *a1,int *a2)
{
    return *a1<*a2;
}
 
bool cmp2(Point a1,Point a2)
{
    if (a1.x==a2.x) return a1.y<a2.y;
    return a1.x<a2.x;
}
 
void leave()
{
    int i,tx,ty;
    sort(px,px+n,cmp1);
    sort(py,py+n,cmp1);
    nx=ny=1;
    tx=*px[0],ty=*py[0];
    *px[0]=*py[0]=1;
    lft[0]=lft[1]=0;
    down[0]=down[1]=0;
    for (i=1; i<n; i++)
    {
        if (*px[i]!=tx)
        {
            tx=*px[i];
            curx[nx]=i-lft[nx];
            rgt[nx]=n-i;
            lft[++nx]=i;
        }
        *px[i]=nx;
 
        if (*py[i]!=ty)
        {
            ty=*py[i];
            cury[ny]=i-down[ny];
            up[ny]=n-i;
            down[++ny]=i;
        }
        *py[i]=ny;
    }
    rgt[nx]=up[ny]=0;
    curx[nx]=n-lft[nx];
    cury[ny]=n-down[ny];
}
 
int query(int rt,int l,int r,int L,int R)
{
    if (L<=l&&r<=R) return num[rt];
    int m=(l+r)>>1,ans=0;
    if (L<=m) ans+=query(rt<<1,l,m,L,R);
    if (R>m)  ans+=query(rt<<1|1,m+1,r,L,R);
    return ans;
}
 
void PushUp(int rt)
{
    num[rt]=num[rt<<1]+num[rt<<1|1];
}
 
void update(int rt,int l,int r,int p)
{
    if (l==r)
    {
        num[rt]++;
        return ;
    }
    int m=(l+r)>>1;
    if (p<=m) update(rt<<1,l,m,p);
    else update(rt<<1|1,m+1,r,p);
    PushUp(rt);
}
 
void solve()
{
    int i,tx,ty;
    int lu,ld,ru,rd;
    int mins=nsize,may=-1;
    maxs=0,k=0;
    sort(pot,pot+n,cmp2);
    memset(num,0,sizeof(num));
    memset(cntx,0,sizeof(cntx));
    memset(cnty,0,sizeof(cnty));
    for (i=0; i<n; i++)
    {
        tx=pot[i].x;
        ty=pot[i].y;
        lu=query(1,1,ny,ty+1,ny);
        ld=lft[tx]-lu-cnty[ty];
        rd=down[ty]-ld-cntx[tx];
        ru=up[ty]-lu-(curx[tx]-cntx[tx]-1);
        //      ru=n-curx[tx]-cury[ty]+1-ld-rd-lu;
        mins=Min(mins,ld+ru);
        may=Max(may,lu+rd);
        update(1,1,ny,ty);
        cntx[tx]++;
        cnty[ty]++;
        if (i==(n-1)||(tx!=pot[i+1].x))
        {
            if (maxs<mins)
            {
                maxs=mins;
                maxy[0]=may;
                k=1;
            }
            else if (maxs==mins)
                maxy[k++]=may;
            mins=nsize,may=-1;
        }
 
    }
    printf("Stan: %d; Ollie:",maxs);
    sort(maxy,maxy+k);
    for (ty=i=1; i<k; i++)
        if (maxy[i]!=maxy[i-1]) maxy[ty++]=maxy[i];
    for (i=0; i<ty; i++) printf(" %d",maxy[i]);
    puts(";");
}
 
int main()
{
    int i;
    while (scanf("%d",&n)&&n)
    {
        for (i=0; i<n; i++)
        {
            scanf("%d %d",&pot[i].x,&pot[i].y);
            px[i]=&pot[i].x,py[i]=&pot[i].y;
        }
        leave();
        solve();
    }
    return 0;
}
```


## 题解
我们这一题