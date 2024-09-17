# 
## 题目描述
TooY0ung可以负责任地告诉你，这是一道温暖的签到题。

TooY0ung 某一天和TooSimple进行挑数字游戏，游戏规则如下：

TooSimple拿出了N个数字给TooY0ung，希望TooY0ung从中挑选出k个数字，使得k个数字的总和为N的倍数。

1<=k<=N

TooY0ung转念一想，这个拿计算机来做会非常简单。

现在，聪明的你快来帮TooY0ung实现一下这个问题吧！

## 输入格式
第一行输入一个正整数N，(1<=N<=10000)

第二行输入N个数，每个数的大小均小于等于15000。

这些数字不一定不同（因此它们中的两个或多个可能相等）


## 输出格式
如果TooY0ung无法找到这样的数，那么输出仅包含一行，一个数字0。

如果TooY0ung可以找到这样的数，那么输出包含k+1行，

第一行输出一个数字k，接下来每一行输出一个数，代表所选数字。

如果有多种方案都可以满足TooSimple的要求，输出任意一种情况即可。


## 样例 #1

### 样例输入 #1

```
5
1
2
5
4
1
```

### 样例输出 #1

```
3
1
5
4
```

## 提示
我们可以先求出这n个数的前缀和，如果已经存在一些满足是n的倍数，那么我们就直接输出就可以。
否则的话，我们就把所有的前缀给模上n，并找到当中的一组，使得两个模后的数字加起来为n。（由鸽巢原理可得，这样的数一定存在）



## 题解


## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
 
#define e exp(1)
#define pi acos(-1)
#define mod 1000000007
#define inf 0x3f3f3f3f
#define ull unsigned long long
#define ll long long
 
int a[10000+10];
int sum[10000+10];
int main()
{
    int n;
    while(scanf("%d",&n)==1)
    {
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        memset(sum,0,sizeof(sum));
        if(n==1&&a[1]==0)
        {
            printf("0\n");
            continue;
        }
        for(int i=1;i<=n;i++)
        {
            sum[i]=sum[i-1]+a[i];
            sum[i]=sum[i]%n;
        }
        int flag=0;
        for(int i=1;i<=n;i++)
        {
            if(sum[i]==0)
            {
                printf("%d\n",i);
                for(int j=1;j<=i;j++)
                {
                    printf("%d\n",a[j]);
                }
                printf("\n");
                flag=1;
                break;
            }
        }
        if(!flag)
        {
            for(int i=1;i<=n;i++)
            {
                for(int j=i+1;j<=n;j++)
                {
                    if(sum[i]-sum[j]==0)
                    {
                        flag=1;
                        printf("%d\n",j-i);
                        for(int k=i+1;k<=j;k++)
                        {
                            printf("%d\n",a[k]);
                        }
                        break;
                    }
                }
                if(flag)
                    break;
            }
        }
        if(flag==0)
            printf("0\n");
    }
    return 0;
}
```