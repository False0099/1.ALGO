## Problem J. Master of GCD  
Hakase has n numbers in a line. At first, they are all equal to 1. Besides, Hakase is interested in primes.She will choose a continuous subsequence $[l,r]$ and a prime parameter x each time and for every $l ≤ i ≤ r$, she will change ai into ai ∗ x. To simplify the problem, **x will be 2 or 3**. After m operations, Hakase wants to know what is the **greatest common divisorof all the numbers**.

## Input  
The first line contains an integer T (1 ≤ T ≤10) representing the number of test cases.

For each test case, the first line contains two integers n (1 ≤ n ≤100000) and m (1≤ m ≤ 100000),where n refers to the length of the wholesequence and m means there are m operations.

The following m lines, each line contains three integers li (1 ≤ li≤ n), ri (1 ≤ ri ≤ n), xi (xi ∈{2,3}), whichare referred above.

## Output  
For each test case, print an integer inone line, representing the greatest common divisor of the sequence. Due to the answer might be very large,print the answer modulo 998244353.

![](https://img2023.cnblogs.com/blog/3203266/202305/3203266-20230524135711870-288377258.png)

![](https://img2023.cnblogs.com/blog/3203266/202305/3203266-20230524135803479-1161665301.png)


## 题解
我们可以显然的发现，gcd 只与我们这个区间内**每个 2 出现次数和 3 出现次数**。因此，我们的思路是，对于每一个数字，维护一个 $a[i],b[i]$  数组，用来储存我们的每一个位置上被乘 2 或乘 3 的次数。

最后，我们只需要**统计整个区间内的最小值**就行了。

当然，如果**我们变成给定 q 个查询的时候，我们这下就又变成一个数据结构题了呢....**
```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
const int N = 100010;
const int mod = 998244353;

LL a[N], b[N];

LL quick_pow(LL a, LL b)//快速幂算法
{
    LL ans = 1;
    while(b)
    {
        if(b & 1){
            ans = (ans * a) % mod;
        }
        a = (a * a)% mod;
        b >>= 1;
    }
    return ans;//返回算得的
}

int main()
{ 
    int T;
    scanf("%d", &T);//测试用例数量
    while(T -- ){
        int n, m;
        scanf("%d%d", &n, &m);
        memset(a, 0, sizeof(a));//初始化差分数组
        memset(b, 0, sizeof(b));
        while(m -- ){//m 个操作
            int l, r, x;
            scanf("%d%d%d", &l, &r, &x);
            if(x == 2) a[l] ++, a[r + 1] --;//若要乘的区间要乘的数为2 就让那个区间的前缀和数组+1
            else if(x == 3) b[l] ++, b[r + 1] --;//若要乘的区间要乘的数为3 就让那个区间的前缀和数组+1
        }
        
        LL min2 = a[1], min3 = b[1];//默认先让下标1处为最小值
        
        for(int i = 2; i <= n; i ++ )//从下标2处开始求前缀和 
        {
            a[i] += a[i - 1], b[i] += b[i - 1];//求前缀和
            min2 = min(min2, a[i]);//查找2出现的最小次数
            min3 = min(min3, b[i]);//查找3出现的最小次数
        }
        
        LL ans = (quick_pow(2, min2)%mod * quick_pow(3, min3) %mod)%mod;//2的最小出现次数*3的最小出现次数=最大公约数
        //为什么要mod两次， 因为(a*b)%mod = ((a % mod) * (b % mod))
        printf("%lld\n", ans);
    }
    
}
```