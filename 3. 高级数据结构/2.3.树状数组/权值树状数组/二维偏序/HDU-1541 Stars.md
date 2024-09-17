现有二维平面 N（N 不超过15000）个点的坐标，以按纵坐标为第一关键字、横坐标为第二关键字升序的方式给出（当两个点的纵坐标不同时纵坐标小的在前，纵坐标相同时横坐标小的在前，保证不存在两个点坐标相同）。问对于每个点，其权值定义为有多少个点在它的左下方（包括正左方和正下方），问对于权值从0~n-1，对应权值的点有多少个？

Input

多组数据，处理到EOF为止
第一行给出一个整数N（N<=15000），表示点的个数
接下来N行每行给出两个整数Xi、Yi(0<=Xi,Yi<=32000)，表示第i个点的坐标

Output

输出N行，第i行表示在权值为i-1的点的个数

Sample Input

5
1 1
5 1
7 1
3 3
5 5

Sample Output

1
2
1
1
0

## 题解
我们这一题是一个标准的二维偏序问题，我们只需要先按照横坐标排序，然后再按照我们的纵坐标进行排序，那么我们排序后，按顺序把我们的纵坐标加入权值树状数组，回头再去统计比我们小的就行了。

```cpp
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
 
#define Fi first
#define Se second
#define ll long long
#define inf 0x3f3f3f3f
#define lowbit(x) (x&-x)
#define PLL pair<ll,ll>
#define PII pair<int,int>
#define in(b) scanf("%d",&b)
#define l_inf 0x3f3f3f3f3f3f3f
#define mmin(a,b,c) min(a,min(b,c))
#define mmax(a,b,c) max(a,max(b,c))
#define debug(a) cout<<#a<<"="<<a<<endl;
#define debug2(a,b) cout<<#a<<"="<<a<<" "<<#b<<"="<<b<<endl;
using namespace std;
const int N=32010;
int s[N];
void update(int p)
{
    while(p<N)
    {
        s[p]++;
        p+=lowbit(p);
    }
}
int query(int p)
{
    int ans=0;
    while(p)
    {
        ans+=s[p];
        p-=lowbit(p);
    }
    return ans;
}
int cnt[N];
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        int ans=0;
        memset(s,0,sizeof s);
        memset(cnt,0,sizeof cnt);
        for(int i=1;i<=n;i++)
        {
            int x,y;
            in(x);in(y);
            x++;y++;
            update(x);
            cnt[query(x)]++;
    //        ans+=query(x);
        }
        for(int i=1;i<=n;i++)
        {
            printf("%d\n",cnt[i]);
        }
    //    cout<<ans<<endl;
    }
 
    return 0;
}
/*
1000 1111
1010 1011
*/
```