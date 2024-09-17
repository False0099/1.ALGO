# 
## 题目描述
一个图，N 个顶点，M 条边，每条边的权值要么为0要么为1

问你能否选出n-1条边是n个点相连，且边的权值之和为斐波那契数

## 输入格式

第一行输入一个整数 T，表示样例个数。

每个样例第一行包括两个整数 N(1 <= N <= 10^5) and M(0 <= M <= 10^5) ，分别表示点和边的数量。

接下来 M 行，每行包括三个整数 u, v (1 <= u,v <= N, u<> v)和 c (0 <= c <= 1)，表示u和v之间边的权值（1或者0）。

## 输出格式

对于每个样例，输出一行“Case #x: s”。x表示第几个样例， s表示答案（“Yes” 或 “No”）。

## 样例 #1

### 样例输入 #1

```
2
4 4
1 2 1
2 3 1
3 4 1
1 4 0
5 6
1 2 1
1 3 1
1 4 1
1 5 1
3 5 1
4 2 1
```

### 样例输出 #1

```
Case #1: Yes
Case #2: No
```

## 题解
我们这一题要求生成一颗生成树，并且我们生成树的边权之和为我们的斐波那契数。
我们考虑将**所有白边优先建最小生成树得到的白边的最多个数**，再将所有的黑边优先建立最小生成树，得到白边的最少数，然后看**这个区间是否存在斐波那契数**

## 代码
```cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<algorithm>
#include<math.h>
#include<queue>
using namespace std;
const int N=100010;
typedef long long ll;
int m,n;
struct data
{
    int a,b,w;
} tu[N];
 
int f[N];
 
bool cmp1(data a,data b)
{
    return a.w>b.w;
}
 
bool cmp2(data a,data b)
{
    return a.w<b.w;
}
 
int fa(int x)
{
    if(x!=f[x])
        return f[x]=fa(f[x]);
    return f[x];
}
 
int main()
{
    int t,o=1;
    cin>>t;
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=0; i<m; i++)
            scanf("%d%d%d",&tu[i].a,&tu[i].b,&tu[i].w);
        sort(tu,tu+m,cmp1);
        for(int i=1; i<=n; i++)
            f[i]=i;
        int l=0;
        for(int i=0; i<m; i++)
        {
            int f1=fa(tu[i].a),f2=fa(tu[i].b);
            if(f1!=f2)
            {
                f[f1]=f2;
                if(tu[i].w==1)l++;
            }
        }
        sort(tu,tu+m,cmp2);
        for(int i=1; i<=n; i++)
            f[i]=i;
        int r=0;
        for(int i=0; i<m; i++)
        {
            int f1=fa(tu[i].a),f2=fa(tu[i].b);
            if(f1!=f2)
            {
                f[f1]=f2;
                if(tu[i].w==1)r++;
            }
        }
        if(r<l)swap(l,r);
        int ff=fa(1),flag=1;
        for(int i=2; i<=n; i++)
            if(fa(i)!=ff)
            {
                flag=0;
                break;
            }
        if(!flag)
            printf("Case #%d: No\n",o++);
        else
        {
            int f0=0,f1=1,f2;
            for(int i=0;; i++)
            {
                f2=f1+f0;
                if(f2>=l&&f2<=r)
                {
                    printf("Case #%d: Yes\n",o++);
                    break;
                }
                else if(f2>r)
                {
                    printf("Case #%d: No\n",o++);
                    break;
                }
                f0=f1,f1=f2;
            }
        }
    }
    return 0;
}
```