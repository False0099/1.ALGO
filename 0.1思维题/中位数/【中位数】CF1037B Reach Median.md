# Reach Median

## 题面翻译

**题目大意：**

给定一个长度为 $n$ 的序列和一个整数 $s$，$n$ 一定为奇数

一次操作可以将序列中的某个数 $+1$ 或者 $-1$，问至少几次操作可以使这个序列的中位数等于 $s$

**输入格式：**

第一行，两个整数 $n,s$

第二行，$n$ 个整数，表示序列中的数

**输出格式：**

一个整数，表示最少的操作次数

## 题目描述

You are given an array $ a $ of $ n $ integers and an integer $ s $ . It is guaranteed that $ n $ is odd.

In one operation you can either increase or decrease any single element by one. Calculate the minimum number of operations required to make the median of the array being equal to $ s $ .

The median of the array with odd length is the value of the element which is located on the middle position after the array is sorted. For example, the median of the array $ 6, 5, 8 $ is equal to $ 6 $ , since if we sort this array we will get $ 5, 6, 8 $ , and $ 6 $ is located on the middle position.

## 输入格式

The first line contains two integers $ n $ and $ s $ ( $ 1\le n\le 2\cdot 10^5-1 $ , $ 1\le s\le 10^9 $ ) — the length of the array and the required value of median.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1\le a_i \le 10^9 $ ) — the elements of the array $ a $ .

It is guaranteed that $ n $ is odd.

## 输出格式

In a single line output the minimum number of operations to make the median being equal to $ s $ .

## 样例 #1

### 样例输入 #1

```
3 8
6 5 8
```

### 样例输出 #1

```
2
```

## 样例 #2

### 样例输入 #2

```
7 20
21 15 12 11 20 19 12
```

### 样例输出 #2

```
6
```

## 提示

In the first sample, $ 6 $ can be increased twice. The array will transform to $ 8, 5, 8 $ , which becomes $ 5, 8, 8 $ after sorting, hence the median is equal to $ 8 $ .

In the second sample, $ 19 $ can be increased once and $ 15 $ can be increased five times. The array will become equal to $ 21, 20, 12, 11, 20, 20, 12 $ . If we sort this array we get $ 11, 12, 12, 20, 20, 20, 21 $ , this way the median is $ 20 $ .

## 题解
我们这一题首先，要修改我们的中位数为 s，我们的最好方法就是把我们的中间的数正好修改成我们的目标数，然后再把我们的其他数也修改为满足条件的数字。
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef long long ll;
int a[200005];
int main()
{
  int n,s;
  while(~scanf("%d%d",&n,&s))
  {
    rep(i,1,n)scanf("%d",&a[i]);
    sort(a+1,a+1+n);
    int pos=lower_bound(a+1,a+1+n,s)-a;
    ll ans=0;
    if(pos>n/2+1)
    {
      rep(i,n/2+1,pos-1)ans+=s-a[i];
    }
    else
    {
      rep(i,pos,n/2+1)ans+=a[i]-s;
    }
    printf("%lld\n",ans);
  }
  return 0;
}
```