# 
## 题目描述
有一个长度为n个序列，有m个操作。每个操作如下：  
S X Y；表示$a[X]=y$  
Q L R D P:表示询问，下标在$[L,R]$范围内的数，有多少个数的第D位是P  
个位为第1位。

## 输入格式
第一行一个整数T，表示测试数据组数。  
每组测试数据第一行两个整数N和M  
第二行为N个元素  
接下来为M个操作


## 输出格式
对于每个操作，输出相应的结果


## 样例 #1

### 样例输入 #1

```
1
5 7
10 11 12 13 14
Q 1 5 2 1
Q 1 5 1 0
Q 1 5 1 1
Q 1 5 3 0
Q 1 5 3 1
S 1 100
Q 1 5 3 1
```

### 样例输出 #1

```
5
1
1
5
0
1
```


## 题解
本题是一个单点修改+区间查询，维护区间内数位的和。我们采用可能不过的分块算法，我们维护第 J 块我们块第 K 位是 J 得个数综合。单点修改只需要我们对原来的数字进行暴力删除，然后把我们得后面的数字加到我们的数组中即可。


## 代码
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

int a[100005],belong[100005],L[100005],R[100005],block[400][11][10],n,m;
int ten[11] = {0,1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};

void build()
{
    int sizee = sqrt(n);
    int num = n/sizee;
    if(n%sizee)  num++;
    for(int i = 1;i <= num;i++)
    {
        L[i] = (i-1)*sizee+1;
        R[i] = i*sizee;
    }
    for(int i = 1;i <= n;i++)   belong[i] = (i-1)/sizee+1;
    for(int i = 1;i <= n;i++)
    {
        int temp = a[i];
        for(int j = 1;j <= 10;j++)
        {
            block[belong[i]][j][temp%10]++;
            temp /= 10;
        }
    }
}

int getnum(int l,int r,int d,int p)
{
    int ans = 0;
    if(belong[l] == belong[r])
    {
        for(int i = l;i <= r;i++)
        {
            if((a[i]/ten[d])%10 == p) ans++;
        }
        return ans;
    }

    for(int i = belong[l]+1;i < belong[r];i++)  ans += block[i][d][p];
    for(int i = l;i <= R[belong[l]];i++)
    {
        if((a[i]/ten[d])%10 == p) ans++;
    }
    for(int i = L[belong[r]];i <= r;i++)
    {
        if((a[i]/ten[d])%10 == p) ans++;
    }
    return ans;
}

void update(int x,int y)
{
    for(int i = 1;i <= 10;i++)
    {
        block[belong[x]][i][a[x]%10]--;
        a[x] /= 10;
    }
    a[x] = y;
    for(int i = 1;i <= 10;i++)
    {
        block[belong[x]][i][y%10]++;
        y /= 10;
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        memset(block,0,sizeof(block));
        scanf("%d%d",&n,&m);
        for(int i = 1;i <= n;i++)   scanf("%d",&a[i]);
        build();
        char s[5];
        while(m--)
        {
            scanf("%s",s);
            if(s[0] == 'S')
            {
                int x,y;
                scanf("%d%d",&x,&y);
                update(x,y);
            }
            else
            {
                int l,r,d,p;
                scanf("%d%d%d%d",&l,&r,&d,&p);
                printf("%d\n",getnum(l,r,d,p));
            }
        }
    }
    return 0;
}
```