# Lunatic Never Content

## 题面翻译

**题目描述**

现在有一个数组 $a$，和 $n$ 个非负整数，定义 $f(a,x)=[a_1\bmod x,a_2\bmod x,\dots,a_n\bmod x]$，其中 $x$ 为正整数。现要你找到最大的 $x$，使得 $f(a,x)$ 是回文的。

这里，$a \bmod x$ 的含义为 $a$ 除以 $x$ 得到的余数。

我们认为一个数组是回文的，当且仅当从前往后读得到的结果和从后往前读得到的结果完全相同。换句话说，一个长度为 $n$ 的数组 $a$ 是回文的，当且仅当 $\forall 1\leq i \leq n$，有 $a_i=a_{n-i+1}$。

**输入格式**

第一行一个整数 $t(1 \leq t \leq 10^5)$，代表测试数据的组数。

对于每一组测试数据：

第一行一个整数 $n(1 \leq n \leq 10^5)$，代表数组 $a$ 的长度。

第二行共 $n$ 个数，以空格隔开，对于 $1\leq i \leq n$，第 $i$ 个数代表 $a_i$。

数据保证 $\sum n \leq 10^5$。

**输出格式**

对于每一组测试用例，输出最大的 $x$ ，使得 $f(a,x)$ 是回文的。如果 $x$ 可以为无穷大，输出 $0$ 来代替。

## 题目描述

You have an array $ a $ of $ n $ non-negative integers. Let's define $ f (a, x) = [a_1 \bmod x, a_2 \bmod x, \dots, a_n \bmod x] $ for some positive integer $ x $ . Find the biggest $ x $ , such that $ f (a, x) $ is a palindrome.

Here, $ a \bmod x $ is the remainder of the integer division of $ a $ by $ x $ .

An array is a palindrome if it reads the same backward as forward. More formally, an array $ a $ of length $ n $ is a palindrome if for every $ i $ ( $ 1 \leq i \leq n $ ) $ a_i = a_{n - i + 1} $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^5 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 10^5 $ ).

The second line of each test case contains $ n $ integers $ a_i $ ( $ 0 \leq a_i \leq 10^9 $ ).

It's guaranteed that the sum of all $ n $ does not exceed $ 10^5 $ .

## 输出格式

For each test case output the biggest $ x $ , such that $ f (a, x) $ is a palindrome. If $ x $ can be infinitely large, output $ 0 $ instead.

## 样例 #1

### 样例输入 #1

```
4
2
1 2
8
3 0 1 2 0 3 2 1
1
0
3
100 1 1000000000
```

### 样例输出 #1

```
1
2
0
999999900
```

## 提示

In the first example, $ f (a, x = 1) = [0, 0] $ which is a palindrome.

In the second example, $ f (a, x = 2) = [1, 0, 1, 0, 0, 1, 0, 1] $ which is a palindrome.

It can be proven that in the first two examples, no larger $ x $ satisfies the condition.

In the third example, $ f (a, x) = [0] $ for any $ x $ , so we can choose it infinitely large, so the answer is $ 0 $ .]

## 题解
我们本题考虑用我们的数学方法，我们线计算出我们的 $a_{1}-a_{n}$,如果我们要回文串相等，我们就相当于让我们 $(a_{1}-a_{n})$ 两侧同时模上一个 x 后相等。
依次类推，最后我们要求的就是我们所有数的最小公约数。
```cpp
```cpp
#include<bits/stdc++.h>
#define int long long //以防万一
using namespace std;
int T,n,a[100001],ans;
signed main(){
    cin>>T;
    while(T--){//多组数据
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        ans=0;//初始化
        for(int l=1,r=n;l<=r;l++,r--)//从头尾开始来搞（因为我懒）
            ans=__gcd(ans,abs(a[l]-a[r]));//差进行最大公因数
        cout<<ans<<endl;//输出（勿忘换行）
    }
    return 0;
}
```
```

