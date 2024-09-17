你有 n 个数 s1, s2…sn，给你一个整数 m，求 m 个子段和的最大值

## Input

输入m，输入n。后面跟着输入n个ai

(n < 1e6)

## Output

输出最大和

## Sample Input

1 3 1 2 3
2 6 -1 4 -2 3 -2 3

## Sample Output

6
8



 

Hint

Huge input, scanf and dynamic programming is recommended.
注意：本题可以使用 O(nm)的时间复杂度。

## 题解
我们本题可以采用动态规划的方式，我们显然我们的最终状态是 $f[i][j]$,表示我们从 1-i，一共分为 j 段，且我们的 $a[i]$ 在第 j 段时 最大值，于是我们就可以采用类似于区间 dp 的更新思路：

我们先按照 i 是否在我们是我们第 j 段的第一个数来划分，是 $f[i][j]=max(f[k][j-1])+arr[i]$,不是，$f[i][j]=f[i-1][j]+arr[i]$，不是而且我们不选，$f[i][j]=f[i][j]$。但是，我们还有最后一种情况，就是不选上我们的 j，那么此时我们的状态就是 $max(f[k][j])$,

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll unsigned long long
#define inf 1<<30
using namespace std;
const int manx=1e6+5;
int a[manx],dp[manx],f[manx];
int main()
{
    int n,m;
    while(scanf("%d%d",&m,&n)!=EOF) //数据较大，用scanf，不然会超时
    {
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        int maxx;
        memset(dp,0,sizeof(dp));
        memset(f,0,sizeof(f));
        for(int i=1;i<=m;i++)
        {
            maxx=-inf; 
            for(int j=i;j<=n;j++) //分成i组的话那么必须从i开始
            {
                dp[j]=max(dp[j-1]+a[j],f[j-1]+a[j]);
                //f[j-1]是前面j-1个数取i-1组的最大值
                //dp[j-1]是前面j-1个数取i组的最大值
                //那么dp[j]就是j个数分i组的最大值
                f[j-1]=maxx; 
   //这里j-1是因为maxx是上个循环得到的，就是前面dp[j-1]和maxx的较大值
                maxx=max(dp[j],maxx);
        //假设当前是循环到i组的时候，这个f数组是会在i+1组的时候用到
            }
        }
        printf("%d\n",maxx);
    }
    return 0;
}


```


```

