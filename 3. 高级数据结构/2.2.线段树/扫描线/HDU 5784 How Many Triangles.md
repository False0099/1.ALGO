Alice has n points in two-dimensional plane. She wants to know how many different acute triangles they can form. Two triangles are considered different if they differ in at least one point.

Input

The input contains multiple test cases.  
For each test case, begin with an integer n,  
next n lines each contains two integers $x_{i}$ and $y_{i}$.  
$3 \leq n \leq 2000$  
$0 \leq x_{i},y_{i} \leq 1e9$  
Any two points will not coincide.

Output

For each test case output a line contains an integer.

Sample

|Inputcopy|Outputcopy|
|---|---|
|3<br>1 1<br>2 2<br>2 3<br>3<br>1 1<br>2 3<br>3 2<br>4<br>1 1<br>3 1<br>4 1<br>2 3|0<br>1<br>2|

## 题解
我们这一题的思路在于：正难则反，我们考虑三个点构成的钝角和直角三角形，然后再用我们的所有个数减去我们的这么构成的，就是我们的答案了。

怎么求我们的三角形呢？我们可以枚举我们的第一个点，然后再用我们的极角排序+双指针确定我们剩下的两个点，就能计算我们角的个数了。

```cpp
//#pragma GCC optimize(2)
//#pragma GCC optimize("Ofast","inline","-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<iostream>
#include<cstdio>
#include<string>
#include<ctime>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<stack>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<cassert>
#include<bitset>
#include<unordered_map>
#define double LL
using namespace std;
      
typedef long long LL;
      
typedef unsigned long long ull;
      
const int inf=0x3f3f3f3f;
    
const int N=2e3+100;//顶点数 
 
LL ans,not_ans;
 
int n;
 
int sgn(double x){
    if(x==0)return 0;
    if(x < 0)return -1;
    else return 1;
}
 
struct Point{
    double x,y;
    Point(){}
    Point(double _x,double _y){
        x = _x;
        y = _y;
    }
    void input(){
        scanf("%lld%lld",&x,&y);
    }
    bool operator == (Point b)const{
        return sgn(x-b.x) == 0 && sgn(y-b.y) == 0;
    }
    bool operator < (Point b)const{
        return sgn(x-b.x)== 0?sgn(y-b.y)<0:x<b.x;
    }
    Point operator -(const Point &b)const{
        return Point(x-b.x,y-b.y);
    }
    Point operator +(const Point &b)const{
        return Point(x+b.x,y+b.y);
    }
    //叉积
    double operator ^(const Point &b)const{
        return x*b.y - y*b.x;
    }
    //点积
    double operator *(const Point &b)const{
        return x*b.x + y*b.y;
    }
    //返回两点的距离
    double distance(Point p){
        return (x-p.x)*(x-p.x)+(y-p.y)*(y-p.y);
    }
}p[N],q[N<<1];
 
int getxx(Point& a) 
{
    if(a.x>0 && a.y>=0) return 1;
    if(a.x<=0 && a.y>0) return 2;
    if(a.x<0 && a.y<=0) return 3;
    if(a.x>=0 && a.y<0) return 4;
}
 
bool cmp(Point a,Point b)
{
	if(getxx(a)!=getxx(b))
		return getxx(a)<getxx(b);
	return sgn(a^b)>0;
}
 
void solve(int id)
{
    for(int i=0,j=0;i<n;i++)
        if(i!=id)
        	q[j++]=p[i]-p[id];
    sort(q,q+n-1,cmp);//极角排序
    int n=::n-1;
    for(int i=0;i<n;i++)
        q[i+n]=q[i];
    int j=0,k=0,l=0;//相同极角的点的位置，锐角极角的位置，钝角极角的位置
    for(int i=0;i<n;i++)
    {
        while(j<i+n&&(q[i]^q[j])==0&&(q[i]*q[j])>0)
            j++;
        k=max(k,j);
        while(k<i+n&&(q[i]^q[k])>0&&(q[i]*q[k])>0)
            k++;
        l=max(l,k);
        while(l<i+n&&(q[i]^q[l])>0)
            l++;
        ans+=k-j;
        not_ans+=l-k;
    }
}
 
int main()
{
#ifndef ONLINE_JUDGE
//  freopen("data.in.txt","r",stdin);
//  freopen("data.out.txt","w",stdout);
#endif
//  ios::sync_with_stdio(false);
    while(scanf("%d",&n)!=EOF)
    {
        ans=0,not_ans=0;
        for(int i=0;i<n;i++)
            p[i].input();
        for(int i=0;i<n;i++)
        	solve(i);
        printf("%lld\n",(ans-2*not_ans)/3);
    }
   return 0;
}
```
}