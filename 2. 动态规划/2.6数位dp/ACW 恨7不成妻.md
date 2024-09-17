# 知识点
  ## [[数位DP]]
# 题目
 单身！

依然单身！

吉哥依然单身！

DS 级码农吉哥依然单身！

所以，他平生最恨情人节，不管是 214214 还是 7777，他都讨厌！

吉哥观察了 214 和 7777 这两个数，发现：

2+1+4=7
7+7=7×2
77=7×11

最终，他发现原来这一切归根到底都是因为和 7 有关！

所以，他现在甚至讨厌一切和 7 有关的数！

什么样的数和 7 有关呢？

如果一个整数符合下面三个条件之一，那么我们就说这个整数和 7 有关：

1.  整数中某一位是 7；
2.  整数的每一位加起来的和是 7 的整数倍；
3.  这个整数是 7 的整数倍。

现在问题来了：吉哥想知道在一定区间内和 77 无关的整数的平方和。

#### 输入格式

第一行包含整数 T，表示共有 T 组测试数据。

每组数据占一行，包含两个整数 L 和 R。

#### 输出格式

对于每组数据，请计算 [L,R][�,�] 中和 7 无关的数字的平方和，并将结果对 10^9+7 取模后输出。

#### 数据范围

1≤T≤50
1≤L≤R≤1018

#### 输入样例：

```
3
1 9
10 11
17 17
```

#### 输出样例：

```
236
221
0
```

# 思路
·首先，我们有数学知识可以知道，一个数可以被 7 整除，等价于这一个数的位数交错加减的结果能被 7 整除
·
·
# AC 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 20, MOD = 1e9 + 7;

LL T, l, r;
int a[N], al;
int pow10[N];

//f记录的是枚举到第pos位，数字模7余数为val，数位之和模7余数为sum
struct F
{
    LL s0, s1, s2;
    F(): s0(0ll), s1(0ll), s2(0ll){};//无参构造函数
    F(LL _0, LL _1, LL _2): s0(_0), s1(_1), s2(_2){};//含参构造函数
    void operator += (const F& t)//重载+=，之后合并信息的时候用到的
    {
        s2 = (s2 + t.s2) % MOD;
        s1 = (s1 + t.s1) % MOD;
        s0 = (s0 + t.s0) % MOD;
    }
}f[N][N][N];

//val记录搜索到第pos位上时，当前数字模7的余数
//sum记录搜索到第pos位上时，前几位数位上数字之和模7的余数
//op记录当前搜索是否贴着上界：1:= 0:<
F dp(int pos, int val, int sum, int op)
{
    if (!pos)   //递归搜索结束，如果此时符合要求，则加一计数
    {
        if (val && sum) return {1, 0, 0};
        else return {0, 0, 0};
    }
    //记忆化搜索
    if (!op && ~f[pos][val][sum].s0) return f[pos][val][sum];

    F res(0, 0, 0);//答案
    int maxx = op ? a[pos] : 9;//搜索上界

    for (int i = 0; i <= maxx; i ++ )//合并信息
    {
        if (i != 7)//题目中要求数位上不能出现7
        {
            //dfs到下一层
            F t = dp(pos - 1, (val * 10 + i) % 7, (sum + i) % 7, op && i == a[pos]);
            //为了方便看代码，这里用一个中间变量k来存储 a * 10^{p-1}
            LL k = (LL) i * pow10[pos - 1] % MOD;  //k = a * 10^{p-1}
            //二次幂和的合并
            t.s2 = (t.s2 + 2ll * k % MOD * t.s1 % MOD) % MOD;
            t.s2 = (t.s2 + k * k % MOD * t.s0 % MOD) % MOD;
            //一次幂和的合并
            t.s1 = (t.s1 + k * t.s0 % MOD) % MOD;
            //信息合并（用到之前重载的+=运算符
            res += t;
        }
    }
    return op ? res : f[pos][val][sum] = res;
}
LL calc(LL x)
{
    memset(f, -1, sizeof f); al = 0;        //初始化
    for ( ; x; x /= 10) a[ ++ al] = x % 10; //扣数位
    return dp(al, 0, 0, 1).s2;              //记忆化搜索
}
int main()
{
    //预处理10的幂次
    pow10[0] = 1;
    for (int i = 1; i < 20; i ++ )
    {
        pow10[i] = 10ll * pow10[i - 1] % MOD;
    }
    //solve
    cin >> T;
    while (T -- )
    {
        cin >> l >> r;
        //这里一个减法取模要注意（我调了一小时，没发现这里爆了
        cout << ((calc(r) - calc(l - 1)) % MOD + MOD) % MOD << endl;
    }
    return 0;
}
```
# 备注
