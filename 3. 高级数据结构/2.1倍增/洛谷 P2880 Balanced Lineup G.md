# [USACO 07 JAN] Balanced Lineup G

## 题目描述

For the daily milking, Farmer John's N cows (1 ≤ N ≤ 50,000) always line up in the same order. One day Farmer John decides to organize a game of Ultimate Frisbee with some of the cows. To keep things simple, he will take a contiguous range of cows from the milking lineup to play the game. However, for all the cows to have fun they should not differ too much in height.

Farmer John has made a list of Q (1 ≤ Q ≤ 180,000) potential groups of cows and their heights (1 ≤ height ≤ 1,000,000). For each group, he wants your help to determine the difference in height between the shortest and the tallest cow in the group.

每天, 农夫 John 的 $n(1\le n\le 5\times 10^4)$ 头牛总是按同一序列排队。

有一天, John 决定让一些牛们玩一场飞盘比赛。他准备找一群在队列中位置连续的牛来进行比赛。但是为了避免水平悬殊，牛的身高不应该相差太大。John 准备了 $q(1\le q\le 1.8\times10^5)$ 个可能的牛的选择和所有牛的身高 $h_i(1\le h_i\le 10^6,1\le i\le n)$。他想知道每一组里面最高和最低的牛的身高差。

## 输入格式

Line 1: Two space-separated integers, N and Q.


Lines 2.. N+1: Line i+1 contains a single integer that is the height of cow i


Lines N+2.. N+Q+1: Two integers A and B (1 ≤ A ≤ B ≤ N), representing the range of cows from A to B inclusive.

第一行两个数 $n,q$。

接下来 $n$ 行，每行一个数 $h_i$。

再接下来 $q$ 行，每行两个整数 $a$ 和 $b$，表示询问第 $a$ 头牛到第 $b$ 头牛里的最高和最低的牛的身高差。

## 输出格式

Lines 1.. Q: Each line contains a single integer that is a response to a reply and indicates the difference in height between the tallest and shortest cow in the range.

输出共 $q$ 行，对于每一组询问，输出每一组中最高和最低的牛的身高差。

## 样例 #1

### 样例输入 #1

```
6 3
1
7
3
4
2
5
1 5
4 6
2 2
```

### 样例输出 #1

```
6
3
0
```


## 题解
我们这一题是我们 ST 表的例题，我们这一题需要开两个 ST 表，一个用来维护我们的区间最大值，另一个用来维护我们的区间最小值。最后的答案就是我们的最大值减去最小值即可。

```cpp
```cpp
#include<cstdio>
#include<iostream>
#define re register
using namespace std;
int a[2000005],f[50005][20],dp[50005][20];
void work(int n) 
{
    for (re int i=1;i<=n;i++) f[i][0]=a[i];
    for (re int j=1;(1<<j)<=n;j++) 
        for (re int i=1;i+(1<<j)-1<=n;i++) 
            f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j - 1]);
}
int RMQ(int l, int r) 
{
    re int k=0;
    while ((1<<(k+1))<=r-l+1)
         k++;
    return max(f[l][k],f[r-(1<<k)+1][k]);
}
void work2(int n) 
{
    for (re int i=1;i<=n;i++) dp[i][0]=a[i];
    for (re int j=1;(1<<j)<=n;j++) 
        for (re int i=1;i+(1<<j)-1<=n;i++) 
            dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j - 1]);
}
int RMQ2(int l, int r) 
{
    re int k=0;
    while ((1<<(k+1))<=r-l+1)
         k++;
    return min(dp[l][k],dp[r-(1<<k)+1][k]);
}
int main()
{
    re int n,m;
    scanf("%d %d",&n,&m);
    for (re int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    work(n);    
    work2(n);
    for (int i=1;i<=m;i++)
    {
    	int l,r;
    	cin>>l>>r;
    	printf("%d\n",RMQ(l,r)-RMQ2(l,r));
	}
}
```
```