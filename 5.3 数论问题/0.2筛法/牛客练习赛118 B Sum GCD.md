给定一个 $n$ 个正整数的序列 $a$，这 $n$ 个数两两互质，给定一个正整数 $k$，求：  
  
$\sum_{i=1}^n\sum_{j=1}^n\frac{\gcd({a_i}\times{a_j},k)}{\gcd({a_i},k)}$  
  
特别地，答案对 $2^{64}$ 取模。

## 输入
第一行两个数 $n,k(1\leq n\leq 10^6,1\leq k\leq 10^9)$ 。  
  
第二行 $n$ 个数，第 $i$ 个数为 $a_i(1\leq a_i\leq 10^9)$。

## 输出
一个数，表示答案。

## 示例
输入
--

 3 2 3 4 7

```
3 2
3 4 7```

输出
--

 11

```


## 题解
我们本题的思路就是通过化简我们的公式来方便我们的预处理：首先因为我们的 $f(x)=gcd(x,k)$ 是积性函数，因此，我们在 $i\neq j$ 时满足有 $\dfrac{gcd(a_{i}\times a_{j},k)}{gcd(a_{i},k)}=gcd(a_{j},k)$。**特别注意我们在 $i=j$ 的时候要单独计算。**

```cpp
`#include<bits/stdc++.h>`

`#define int unsigned long long`

`using` `namespace` `std;`

`//typedef unsigned long long int;`

`signed` `main(){`

    `int` `a,k;`

    `int` `n;`

    `int` `ans=0;`

    `cin>>n>>k;`

    `for``(``int` `i=1;i<=n;i++)`

    `{`

        `cin>>a;`

        `ans+=gcd(a,k)*(n-1)+gcd(a*a,k)/gcd(a,k);`//直接计算每一位的贡献

    `}`

    `cout<<ans;`

    `return` `0;`

`}`
```
