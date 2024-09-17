# 
## 题目描述
给定你两个正整数 G 和 L，你能告诉我存在多少个三元组 (x, y, z) ，使得 gcd(x, y, z) = G 以及 lcm(x, y, z) = L 吗？  
提示 1：gcd(x, y, z) 表示 x、y 和 z 的最大公约数，而 lcm(x, y, z) 表示x、y 和 z 的最小公倍数。  
提示 2：(1, 2, 3) 和 (1, 3, 2) 表示不同的解决方案。

## 输入格式
第一行输入一个整数 T (T <= 12)，表示测试数据的组数。  
接下来的 T 行，每行包含两个 32 位的正整数 G 和 L。  
题目保证答案可以用 32 位的整数表示。


## 输出格式
对于每组测试数据，输出满足题目的方案数。


## 样例 #1

### 样例输入 #1

```
2 
6 72 
7 33 

```

### 样例输出 #1

```
72 
0

```

## 题解
我们首先判断L%G是否为0，如果不为0，那么直接输出不行即可。
当L%G不为0时，我们对上面两个等式同时除以G，我们就能得到$gcd\left( \frac{x}{G},\frac{y}{G} ,\frac{z}{G}\right)=1$,以及我们的$lcm\left( \frac{x}{G},\frac{y}{G},\frac{z}{G} \right)=\frac{L}{G}$。接下来我们由算数基本定理，假设我们的$\frac{x}{G}$可以分解成$p_{1}^{x_{1}}p_{2}^{x_{2}}\dots p_{n}^{x_{n}}$，$\frac{y}{G}$可以分解成$p_{1}^{y_{1}}p_{2}^{y_{2}}\dots p_{n}^{y_{n}}$。$\frac{z}{G}$可以分解成$p_{1}^{z_{1}}p_{2}^{z_{2}}\dots p_{n}^{z_{n}}$。那么我们的最大公倍数$\frac{L}{G}=p_{1}^{max(x_{1},y_{1},z_{1})}p_{2}^{max(x_{2},y_{2},z_{2})}\dots$
同时因为三者最大公约数为1，所以要保证至少有一个指数为0。
所以我们只需要先知道$\frac{L}{G}$的因式分解结果，然后再根据结果去进行计数。

对于每一个因子，我们可以有{0,0,t1},{0,t1,t1},{0,t1,1-t1-1}共t1 * 6种排列，其中t1是指我们的L/G分解所得到在这一位上的结果。



## 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 200005

using namespace std;

bool not_prime[N];
int prim[N];

void init()
{
    memset(not_prime, 0, sizeof(not_prime));

    prim[1] = 0;
    int cnt = 0;

    for(int i = 2; i < N; i++) 
    {  
        if(!not_prime[i]) 
        {   
            prim[cnt++] = i;
            for(int j = i + i; j < N; j += i)
            {  
                not_prime[j] = 1;  
            }  
        }  
    }  
}

void get(int m)
{
    int ans = 1;

    for (int i = 0; prim[i] * prim[i] <= m; i++)
    {
        if (m % prim[i] == 0)
        {
            int cnt = 0;

            while (m % prim[i] == 0)
            {
                cnt++;
                m /= prim[i];
            }

             ans *= 6 * cnt;
        }
    }

    if (m > 1)
    {
        ans *= 6;
    }

    printf("%d\n", ans);
}

int main()
{
    init();

    int T;
    scanf("%d", &T);

    while (T--)
    {
        int gcd, lcm;
        scanf("%d%d", &gcd, &lcm);

        if (lcm % gcd != 0)
        {
            printf("0\n");
            continue;
        }

        int m = lcm / gcd;
        get(m);
    }

    return 0;
}
```