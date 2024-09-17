## 题目描述
小红拿到了一个数组：$a_1,a_2,...,a_n$。她定义 f(i) 为，删除第 $i$ 个元素后，数组的中位数。现在小红想让你求出 $f(1),f(2)...f(n)$ 的值，你能帮帮她吗？

## 输入
第一行输入一个正整数 $n$，代表数组的大小。  
第二行输入 $n$ 个正整数 $a_i$，代表数组的元素。  
$2\leq n \leq 10^5$  
$1\leq a_i \leq 10^9$

## 输出
输出 $n$ 行，每行输出一个浮点数，第 $i$ 行代表 $f(i)$ 的值。保留一位小数。

## 题解
我们这一题，我们的思路是，我们每一次修改，对于我们中位数的影响是固定的，假设我们现在是一个奇数个，那么我们只需要维护我们的中位数和他的左侧和右侧的数，如果我们删除的数字在中位数的左左侧，那么我们的答案就是我们的中位数+中位数右侧
如果我们删除的数字在中位数的右右测，那么我们的答案就是我们的中位数+中位数左侧。
如果我们删除的数字是我们的中位数，那么我们的答案就是我们的中位数的左侧+中位数的右侧。

如果我们删除后的长度是一个奇数，那么我们只需要维护我们的原本的两个中位数。
如果我们删除的是左中位数，那么我们的结果就是我们的左中位数。反之，答案就是我们的右中位数。

```
#include<set>
#include<map>
#include<stack>
#include<queue>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
using ll=long long ;
using pii=pair<int,int> ;
using pdi=pair<double,int>;
#define endl "\n"

constexpr int N=1e5+10;
pdi p[N];
double a[N];
int pre[N],rear[N];

void solve()
{
    int n;
    cin>>n;
    
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        p[i]={a[i],i};
    }
    
    sort(p+1,p+1+n,[&](pdi a,pdi b)
         {
             return a.first<b.first;
         });
    
    for(int i=1;i<=n;i++)
    {
        int tag=p[i].second;
        pre[tag]=i;
    }
    
    if(n%2==0)
    {
        for(int i=1;i<=n;i++)
        {
            if(pre[i]>n/2)printf("%.1lf\n",p[n/2].first);
            else printf("%.1lf\n",p[n/2+1].first);
        }
    }
    else
    {
        for(int i=1;i<=n;i++)
        {
            if(pre[i]<(n+1)/2)printf("%.1lf\n",(p[(n+1)/2].first+p[(n+1)/2+1].first)/2.0);
            else if(pre[i]==(n+1)/2)printf("%.1lf\n",(p[(n)/2].first+p[(n+1)/2+1].first)/2.0);
            else printf("%.1lf\n",(p[(n)/2].first+p[(n+1)/2].first)/2.0);
        }
    }
}
signed main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(0);cout.tie(0);
    
    int t;
    t=1;
    
    while(t--)
    solve();
    return 0;
}
```