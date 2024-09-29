## 题目描述
在一片广袤无垠的原野上，散落着 N 块磁石。

每个磁石的性质可以用一个五元组 (x,y,m,p,r) 描述，其中 x,y 表示其坐标，m 是磁石的质量，p 是磁力，r 是吸引半径。

若磁石 A 与磁石 B 的距离不大于磁石 A 的吸引半径，并且磁石 B 的质量不大于磁石 A 的磁力，那么 A 可以吸引 B。

小取酒带着一块自己的磁石 L 来到了这片原野的 (x0,y0)处，我们可以视磁石 L 的坐标为 (x0,y0)。

小取酒手持磁石 L 并保持原地不动，所有可以被 L 吸引的磁石将会被吸引过来。

在每个时刻，他可以选择更换任意一块自己已经获得的磁石（当然也可以是自己最初携带的 L 磁石）在 (x0,y0) 处吸引更多的磁石。

小取酒想知道，他最多能获得多少块磁石呢？

## 输入格式
第一行五个整数 x0,y0,pL,rL,N，表示小取酒所在的位置，磁石 L磁力、吸引半径和原野上散落磁石的个数。

接下来 N 行每行五个整数 x,y,m,p,r，描述一块磁石的性质。


## 输出格式
输出一个整数，表示最多可以获得的散落磁石个数（不包含最初携带的磁石 L）。


## 样例 #1

### 样例输入 #1

```
0 0 5 10 5
5 4 7 11 5
-7 1 4 7 8
0 2 13 5 6
2 -3 9 3 4
13 5 1 9 9
```


### 样例输出 #1

```
3
```

## 题解
这一题是分块优化搜索速度的典型题目，这一题如果我们采用标准的做法的话，我们一定是能够得到我们的

我们这一题采用我们的分块做法，首先把我们把我们的磁石按照到我们的距离进行**排序，并分块**，在我们的块内，我们由按照我们的质量从小到大排序。这样我们的每一个大块内，都可以通过判断我们**当前的刺针**在我们的**大块内**的位置，这个位置我们可以二分来得到。在边界块，我们就可以直接暴力判断即可。

## 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

#define ll long long
const int N=2e6;
const int w=500;

struct node
{
    ll d,r;             //d:距离 r:半径 
    ll m,p;             //m:质量 p:磁力 
}a[N];

ll D[N],x0,y_0,now,L[N],R[N],v[N],n,tot,l,r,p,x,y;
queue<ll> q;

bool cmp_d(node a,node b)//比较距离 
{
    return a.d<b.d;
}

bool cmp_m(node a,node b)//比较质量 
{
    return a.m<b.m;
}

int main()
{
    cin>>x0>>y_0>>a[0].p>>a[0].r>>n;
    a[0].r*=a[0].r;
    for(int i=1;i<=n;i++)
    {
        cin>>x>>y>>a[i].m>>a[i].p>>a[i].r;
        a[i].r*=a[i].r;
        a[i].d=(x0-x)*(x0-x)+(y_0-y)*(y_0-y); 
    }
    sort(a+1,a+n+1,cmp_d);
    for(ll i=1;i<=n;i+=w)
    {
        L[++tot]=i;
        R[tot]=min(n,i+w-1);
        D[tot]=a[R[tot]].d;//本区间中d最大的 
        sort(a+L[tot],a+R[tot]+1,cmp_m);    
    }
    q.push(0);
    ll ans=1;
    while(q.size())
    {
        ll l=q.front();
        now=a[l].r;
        p=a[l].p;
        q.pop();
        for(ll i=1;i<=tot;i++)//枚举所有块
        {
            if(D[i]>now)//第一个比吸收半径大的 
            {
                for(ll j=L[i];j<=R[i];j++)
                {
                    if(!v[j]&&a[j].d<=now&&a[j].m<=p)
                    {
                        q.push(j);
                        ans++;
                        v[j]=1;
                    }
                }
                break;
            }
            while(L[i]<=R[i]&&a[L[i]].m<=p)//半径已经保证<=now并且质量也符合要求 
            {
                if(!v[L[i]])
                {
                    q.push(L[i]);
                    ans++;
                }
                ++L[i];                     //更新L[i],即下次再吸收时，不计算之前的数字 
            }
        }
    }
    cout<<ans-1<<endl;                      //不算最开始的 
    return 0;
}


```