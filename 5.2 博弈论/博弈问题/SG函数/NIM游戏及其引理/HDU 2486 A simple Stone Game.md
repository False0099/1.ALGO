After he has learned how to play Nim game, Mike begins to try another stone game which seems much easier.  
  
The game goes like this: Two players start the game with a pile of n stones. They take stones from the pile in turn and every time they take at least one stone. The one who goes first can take at most n-1 stones for his first move. From then on a player can take at most k times as many stones as his opponent has taken last time. For example, if one player take m stones in his turn, then the other player can take at most k × m stones next time. The player who takes the last stone wins the game. Suppose that those two players always take the best moves and never make mistakes, your job is to find out who will definitely win the game.  

Input

The first line contains a integer t, indicating that there are t test cases following.(t<=20).  
  
Each test case is a line consisting of two integer n and k.(2<=n<=10^8,1<=k<=10^5).  

Output

For each test case, output one line starting with “Case N: ”, N is the case number. And then, if the first player can ensure a winning, print the minimum number of stones he should take in his first turn. Otherwise, print "lose". Please note that there is a blank following the colon.

Sample

|Inputcopy|Outputcopy|
|---|---|
|5<br>16 1<br>11 1<br>32 2<br>34 2<br>19 3|Case 1: lose<br>Case 2: 1<br>Case 3: 3<br>Case 4: lose<br>Case 5: 4|

## 题解
我们这一题首先有我们的 n=2 是我们的必败态，之后我们可以考虑用我们的 sg 函数进行我们的扩展。考虑我们的 $k=1$,此时，我们有 ![[Pasted image 20231119113400.png]]

不难发现，我们的所有必败状态是我们的 $2^i$。
于是我们就考虑构造我们的必胜策略：我们把我们必胜态的 n 分解为二进制，然后我们先手就去掉我们的最后一个 1，假设我们原本是 1101，现在变成 1100，然后后手不能去掉更高位的 1。然后我们每一次后手就一定能消掉 1，先手一定不能消掉一个 1.

考虑 $k=2$,那么此时，我们可以发现，我们的必败态是我们的 $Fibonacci$ 数列，
将一个数利用 Fibonacci 分解有这么一个特殊性质：一定不存在相邻的 1. 那么我们就可以利用我们的 $k=1$ 完全相同的策略来解决我们 $K=2$ 的问题
我们考虑下面的构造：我们把 n 写成数列中一些项的和。使这些被取到的相邻两个倍数 $>k$,那么仍然利用 $k=1$ 方法即可解决。
设这个数列已经构造了 $i$ 项，前 $i$ 项可以对 $1-b_{i}$ 进行完美编码：
完美编码意为：存在一个 $a_{i_{1}},a_{i_{2}},a_{i_n}$ 的组合，使得我们 $\sum a_{i_{k}}=n$，且我们 $\dfrac{a_{i_{j+1}}}{a_{i_{j}}}>k$,那么我们有 $a_{i+1}=b_{i}+1,b_{i+1}=b_{t}+a_{i+1}$,其中，我们的 $t$ 为满足 $\frac{a_{t+1}}{a_{t}}>k$ 的 t。
我们只需要判断 n 是否在这个数列中即可。
例如：我们有 85=55+21+8+1，那么我们先手取，我们就可以先取一个 1，然后我们后手就只能取，$f[a(p-1)]$ 这一堆，且不能一次取完。


```cpp
//
//  main.cpp
//  A simple Stone Game
//
//  Created by teddywang on 2016/10/4.
//  Copyright © 2016年 teddywang. All rights reserved.
//
#include <iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=2000000;
int a[maxn],b[maxn];
int main()
{
    int t,n,k;
    cin>>t;
    for(int cas=1;cas<=t;cas++)
    {
        cin>>n>>k;
        printf("Case %d: \n",cas);
        if(n<=k+1)
        {
            printf("lose\n");
            continue;
        }
        a[0]=b[0]=1;
        int i=0,j=0;
        while(a[i]<n)
        {
            i++;
            a[i]=b[i-1]+1;
            while(a[j+1]*k<a[i]) j++;
            if(a[j]*k<a[i]) b[i]=b[j]+a[i];
            else b[i]=a[i];
        }
//        for(int l=0;l<=i;l++)
//            cout<<a[l]<<" ";
//        cout<<endl;
//        for(int l=0;l<=j;l++)
//            cout<<b[l]<<" ";
//        cout<<endl;
        if(a[i]==n)printf("lose\n");
        else
        {
            int ans=0;
            while(n)
            {
                if(n>=a[i])
                {
                    n-=a[i];
                    ans=a[i];
                }
                i--;
            }
            cout<<ans<<endl;
        }
    }
}
```