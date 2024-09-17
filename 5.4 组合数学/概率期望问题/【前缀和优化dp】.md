Problem Description

有 n 个格子，你现在在第 x 个格子，想到第 y 个格子。  
  
每次，如果你当前的格子编号小于 y，你就会等概率跳到比当前编号更大的一个格子中，反之则等概率跳到比当前编号更小的一个格子中。  
  
求期望跳的次数。

  

**Input**

第一行一个正整数 $T$ 代表数据组数。接下来 $T$ 行，每行三个正整数 $n,x,y$,分别为函数的三个参数。
 满足 $1\leq n,T\leq2\times10^6,\quad1\leq x,y\leq n$。

  

**Output**

对每组数据，输出一个正整数，$i$ 的期望对 $10^9+7$ 取模后的值。

**Sample Input**

4
2 1 2
3 1 3
3 1 2
114514 1919 810

  

**Sample Output**

1
500000005
2
680707294

  

Hint

  
对于第一组 n=2，x=1，y=2 的情况，第一次跳跃的范围为 [2,2]，因此答案为 1。  
  
对于第二组 n=3，x=1，y=3 的情况，第一次跳跃的范围为 [2,3]。  
  
若第一次跳到第 2 格，答案为 2；若第一次跳到第三格，答案为 1，因此答案为 12×2+12×1≡32≡5×108+5(mod109+7)  
  
对于第三组 n=3，x=1，y=2 的情况，  
  
有 12n 的情况答案为 n，  
  
故答案为 ∑\infini=1i2i=2。


## 题解
我们本题的思路是：通过我们的期望 dp 来进行转移，首先，我们设我们的 $g[i]$ 表示我们从 i 点出发到达目标点的期望的移动次数：
根据我们的题目意思我们就有：
$$\begin{gathered}
g[i] =\frac1{n-i}\sum_{j>i}g[j]+1(i<y) \\
g[i] =\frac1{i-1}\sum_{j<i}g[j]+1(i>y) \\
g[y]=0 
\end{gathered}$$

我们考虑使用前缀和进行优化：

$$\begin{gathered}sum[i]=\frac{n-i}{n-i+1}sum[i-1]+\frac1{n-i+1}sum[n]+\frac1{n-i+1}(i<y)\\sum[i]=\frac i{i-1}sum[i-1]+1(i>y)\\sum[y-1]=sum[y]\end{gathered}$$


我们把前两条式子郑立伟封闭的递推式，我们就有：
$$\begin{gathered}sum[i]=\frac insum[n]+(n-i)\sum_{j=n-i+1}^n\frac1j(i<y)\\\\sum[i]=\frac iysum[y]+i\sum_{j=y+1}^i\frac1j(i>y)\end{gathered}$$

将 y-1 带入第一条式子，将 n 带入第二条式子，又因为 $sum[y-1]=sum[y]$,得到 $sum[y]$和 $sum[n]$的两条式子，联立解出 $sum[y]$即可。解出 $sum[y]$后，可以依次解出 $sum[x]$和 $sum[x-1]$。需要预处理逆元 (这里是线性逆元) 和逆元前缀和。

```cpp
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

#define B 32767
namespace IO
{
    char a[B], b[B];
    int c;

    int Getchar(void)
    {
        static int c = B;

        if(c == B)
        {
            fread(a, sizeof(char), B, stdin);
            c = 0;
        }

        return a[c ++];
    }

    void Flush(void)
    {
        fwrite(b, sizeof(char), c, stdout);
        c = 0;

        return;
    }

    void Putchar(int x)
    {
        if(c == B)
            Flush();
        b[c ++] = x;

        return;
    }

    int Scan(void)
    {
        int c;
        int s;

        for(s = 0; (c = Getchar()) < '0' || c > '9'; )
            ;
        do
            s = s * 10 + (c & 15);
        while((c = Getchar()) >= '0' && c <= '9');

        return s;
    }

    void Print(int x)
    {
        int c;
        static int b[20];

        if(!x)
            Putchar('0');
        else
        {
            for(c = 0; x; x /= 10)
                b[c ++] = x % 10;
            while(c --)
                Putchar(b[c] + 48);
        }

        return;
    }
}

const LL M=1000000007ll;
const int maxn=2000010;
LL inv[maxn];
LL inv_sum[maxn];
LL f[maxn];
int t,n,x,y;
inline int Read()
{
   int s=0;
   char ch=getchar();
   while(ch<'0'||ch>'9'){ch=getchar();}
   while(ch>='0'&&ch<='9') s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
   return s;
}
inline void Print(long long x)
{
	if(x > 9) Print(x/10);
	putchar(x%10 + '0');
}
int main()
{
    freopen("b.in","r",stdin);
    freopen("b.out","w",stdout);
    inv[1]=1;
    inv_sum[1]=1;
    f[1]=1;
    for (register int i=2; i<maxn; ++i)
    {
        inv[i]=M-(M/i)*inv[M%i]%M;
        inv_sum[i]=inv_sum[i-1]+inv[i];
        if (inv_sum[i]>=M) inv_sum[i]-=M;
        f[i]=inv_sum[i]*(long long)i%M;
    }
    scanf("%d",&t);
    while (t--)
    {
        n=IO::Scan();
        x=IO::Scan();
        y=IO::Scan();
        if (x==y)
        {
            IO::Putchar('0');
            IO::Putchar('\n');
            continue;
        }
        if (x<y)
        {
            x=n-x+1;
            y=n-y+1;
        }
        LL ans=f[n]-f[y]-f[n-y+1]+M+M+inv_sum[x-1]+1;
        while (ans>=M) ans-=M;
        IO::Print(ans);
        IO::Putchar('\n');
    }
    IO::Flush();
    return 0;
}

```
