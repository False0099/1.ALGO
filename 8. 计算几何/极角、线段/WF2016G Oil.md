A large part of the world economy depends on oil, which is why research into new methods for finding and extracting oil is still active. Profits of oil companies depend in part on how efficiently they can drill for oil. The International Crude Petroleum Consortium (ICPC) hopes that extensive computer simulations will make it easier to determine how to drill oil wells in the best possible way. Drilling oil wells optimally is getting harder each day – the newly discovered oil deposits often do not form a single body, but are split into many parts. The ICPC is currently concerned with stratified deposits, as illustrated in Figure G.1.

![[Pasted image 20231026175535.png]]

To simplify its analysis, the ICPC considers only the 2-dimensional case, where oil deposits are modeled as horizontal line segments parallel to the earth’s surface. The ICPC wants to know how to place a single oil well to extract the maximum amount of oil. The oil well is drilled from the surface along a straight line and can extract oil from all deposits that it intersects on its way down, even if the intersection is at an endpoint of a deposit. One such well is shown as a dashed line in Figure G.1, hitting three deposits. In this simple model the amount of oil contained in a deposit is equal to the width of the deposit. Can you help the ICPC determine the maximum amount of oil that can be extracted by a single well?

## Input
The first line of input contains a single integer n (1 ≤ n ≤ 2 000), which is the number of oil deposits. This is followed by n lines, each describing a single deposit. These lines contain three integers x0, x1, and y giving the deposit’s position as the line segment with endpoints (x0, y) and (x1, y). These numbers satisfy |x0|, |x1| ≤ 106 and 1 ≤ y ≤ 106 . No two deposits will intersect, not even at a point.

## Output
Display the maximum amount of oil that can be extracted by a single oil well.

## 题解
题目翻译：给定你 n 条平行于 x 轴的线段，问我们能否找到一条直线，使得我们相交的线段权值和最大，并求出我们最后的一个最大权值和。

我们这一题可以通过枚举 1 个端点，然后对于这一个端点，我们求出能够覆盖每一条线段的斜率区间，然后我们求一个斜率范围。然后我们就可以利用我们类似于**扫描线**的做法去解决我们的问题，求出我们范围内的一个最大值是多少
```cpp
#include<set>
#include<map>
#include<deque>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<bitset>
#include<string>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<climits>
#include<complex>
#include<algorithm>
#define ll long long
#define ld long double
using namespace std;

const int maxn = 2100;
const ld eps = 1e-7;

int Sgn(ld x){ return fabs(x)<eps?0:(x>0?1:-1); }

int n;
struct point
{
    ld x,y;
    friend inline point operator -(const point &a,const point &b){return (point){a.x-b.x,a.y-b.y};}
    inline ld rad(){ return x/y; }
};
struct Line
{
    point a,b;
    ld val;
}L[maxn];

struct node
{
    int i,ad;
    ld rad;
    friend inline bool operator <(const node x,const node y)
    {
        int Sig=Sgn(x.rad-y.rad);
        if(!Sig) return x.ad>y.ad;
        return Sig<0;
    }
}a[maxn<<1]; int cnt;
ld ans;
void Upd(ld now)
{
    for(int i=1;i<=cnt;i++)
    {
        if(a[i].ad==1) now+=L[a[i].i].val;
        else now-=L[a[i].i].val;
        ans=max(ans,now);
    }
}

int main()
{
    //freopen("tmp.in","r",stdin);
    //freopen("tmp.out","w",stdout);

    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        ld l,r,h; scanf("%Lf%Lf%Lf",&l,&r,&h); if(Sgn(l-r)>0) swap(l,r);
        L[i]=(Line){(point){l,h},(point){r,h}};
        L[i].val=r-l;
        ans=max(ans,L[i].val);
    }

    for(int i=1;i<=n;i++)
    {
        cnt=0;
        for(int j=1;j<=n;j++) if(Sgn(L[i].a.y-L[j].a.y))
        {
            ld r1=(L[j].a-L[i].a).rad(),r2=(L[j].b-L[i].a).rad();
            if(Sgn(r1-r2)>0) swap(r1,r2);
            a[++cnt]=(node){j,1,r1};
            a[++cnt]=(node){j,-1,r2};
        }
        sort(a+1,a+cnt+1);
        Upd(L[i].val);
    }
    printf("%.0Lf\n",ans);

    return 0;
}
```