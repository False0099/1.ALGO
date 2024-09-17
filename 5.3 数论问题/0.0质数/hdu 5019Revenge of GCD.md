## 题目描述
在数学中，两个或多个整数（当其中至少有一个不为零时）的最大公约数(gcd)，也称为最大公因数(gcf)、最高公因数(hcf)或最大公约数(gcm)，是除数不带余数的最大正整数。 ---维基百科 今天，GCD向你复仇。你得算出X和y的第k次GCD。

## 输入格式
第一行包含一个整数T，表示测试用例的数量。 每个测试用例只包含三个整数X、Y和K。 【技术规范】  
1. 1 <= T <= 100  
2. 1 <= X, Y, K <= 1 000 000 000 000


## 输出格式
对于每个测试用例，输出X和y的第k个GCD。如果不存在这样的整数，输出-1。


## 样例 #1

### 样例输入 #1

```
3
2 3 1
2 3 2
8 16 3
```

### 样例输出 #1

```
1
-1
2
```

## 题解
我们利用最大公约数的性质，最大公约数的所有约数一定是那两个数的公约数，所以我们只需要求出a,b的公约数，然后对这个公约数进行因式分解后排序即可。

## 代码
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstdlib>
 
using namespace std;
 
typedef __int64 LL;
 
LL gcd(LL a, LL b)
{
    if(b==0)
        return a;
    return gcd(b, a%b);
}
 
int main()
{
    LL a, b, c;
    int T;
    vector<LL> v;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%I64d%I64d%I64d", &a, &b, &c);
        LL temp = gcd(a, b);
        v.clear();
        int cnt = 0;
        for(LL i=1; i*i<=temp; ++i)
        {
            if(temp%i==0)
             {
                 v.push_back(i);
                 if(i*i!=temp)
                    v.push_back(temp/i);
             }
 
        }
        sort(v.begin(), v.end());
        if(v.size() >= c)
            printf("%I64d\n", v[v.size()-c]);
        else
            printf("-1\n");
    }
    return 0;
}
```