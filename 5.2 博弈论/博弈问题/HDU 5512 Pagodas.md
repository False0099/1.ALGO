## 题目描述
曾经在牛首山和云台山的中央，有 n 座古塔矗立在宏觉寺，从 1 标号至 n。然而只有其中的两座（标号为 a 与 b, 满足 1 <= a < b <= n）承受住了时间的考验。  
  
有两个和尚，分别叫做 Yuwgna 和 Iaka，想让其重现佛光，便决定轮流修建古塔，Yuwgna 执先。对于每一个回合，其中一个人可以选择修建编号为 i （i∉{a,b},1 <= i <= n）的古塔，对于编号 i 应满足：设现有两古塔编号为 j 与 k ，则 i=j+k 或 i=j-k。每一座古塔不能建造两次。  
  
视其为一个游戏，当某一个和尚不能再建造新塔时视为游戏失败，同样的，另一个和尚获得胜利。

## 输入格式
第一行输入一个数 t (1<= t <= 500) 代表着将要测试的样例数。  
对于每一个例子，第一行输入一个 n (2<= n<= 20000) 并且跟着两个数 a 和 b。


## 输出格式

对于每一个例子，输出胜者 (``Yuwgna" 或 ``Iaka”)。假设他们每次都会做出最佳决定。

## 样例 #1

### 样例输入 #1

```
16
2 1 2
3 1 3
67 1 2
100 1 2
8 6 8
9 6 8
10 6 8
11 6 8
12 6 8
13 6 8
14 6 8
15 6 8
16 6 8
1314 6 8
1994 1 13
1994 7 12
```

### 样例输出 #1

```
Case #1: Iaka
Case #2: Yuwgna
Case #3: Yuwgna
Case #4: Iaka
Case #5: Iaka
Case #6: Iaka
Case #7: Yuwgna
Case #8: Yuwgna
Case #9: Iaka
Case #10: Iaka
Case #11: Yuwgna
Case #12: Yuwgna
Case #13: Iaka
Case #14: Yuwgna
Case #15: Iaka
Case #16: Iaka
```

## 题解
这一题如果我们能够解出所有能修的塔的数目P，那么我们就能够判断出最后的胜负。
根据裴蜀定理，$ax+by$是$gcd(a,b)$的整数倍，即P是所有$gcd(a,b)$的倍数的个数，则$p=\frac{n}{gcd(a,b)}$。

## 代码
```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

int gcd(int a,int b)
{
    return a==0? b:gcd(b%a,a);
}
int main()
{
    int T,a,b,n;
    int kase=0;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        scanf("%d %d",&a,&b);
        int g=gcd(a,b);
        int t=n/g-2;
        printf("Case #%d: ",++kase);
        if(t%2)
            puts("Yuwgna");
        else
            puts("Iaka");
    }
    return 0;
}
```