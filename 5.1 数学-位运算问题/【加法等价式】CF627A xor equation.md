# XOR Equation

## 题面翻译

## 题目描述

两个合法的正整数 $a$ 和 $b$ 的和为 $s$，它们的按位异或和为 $x$。请计算出所有可能的有序数对 $(a,b)$ 的个数。
## 输入格式
输入共一行，包含两个整数 $s(2\leq s\leq 10^{12})$ 和 $x(2\leq x\leq 10^{12})$。
## 输出格式

输出一个整数，为合法的有序数对的个数。如果不存在合法的数对，则输出 $0$。


## 样例解释

对于第一个样例，有以下合法的数对：$(2,7)$ $(3,6)$ $(6,3)$ $(7,2)$；

对于第二个样例，有以下合法的数对：$(1,2)$  $(2,1)$。

## 题目描述

Two positive integers $ a $ and $ b $ have a sum of $ s $ and a bitwise XOR of $ x $ . How many possible values are there for the ordered pair $ (a, b) $ ?

## 输入格式

The first line of the input contains two integers $ s $ and $ x $ ( $ 2<=s<=10^{12} $ , $ 0<=x<=10^{12} $ ), the sum and bitwise xor of the pair of positive integers, respectively.

## 输出格式

Print a single integer, the number of solutions to the given conditions. If no solutions exist, print $ 0 $ .

## 样例 #1

### 样例输入 #1

```
9 5
```

### 样例输出 #1

```
4
```

## 样例 #2

### 样例输入 #2

```
3 3
```

### 样例输出 #2

```
2
```

## 样例 #3

### 样例输入 #3

```
5 2
```

### 样例输出 #3

```
0
```

## 提示

In the first sample, we have the following solutions: $ (2,7) $ , $ (3,6) $ , $ (6,3) $ , $ (7,2) $ .

In the second sample, the only solutions are $ (1,2) $ and $ (2,1) $ .

## 题解
我们本体可以通过我们的加法恒等式来尽心我们的处理，我们现在有我们的下面的恒等式：
$$a+b=(a\operatorname{xor}b)+2\cdot(a\operatorname{and}b)$$


又加上我们现在有下面的式子：$(a\oplus b)=t$,那么我们就可以很简单的求出我们的 $a \text{\ and\ }b$ 的值是多少。然后我们再去进行我们的拆位就可以得到我们的对应的组数。
```
#include <bits/stdc++.h>

#define int long long

int INF=0x3f3f3f3f3f;

using namespace std;

void solve(){

    int sum,xor_sum;

    cin>>sum>>xor_sum;

    int and_sum=(sum-xor_sum)/2;

    if((sum-xor_sum)%2!=0||(sum-xor_sum)<0){

        cout<<0<<endl;

        return;

    }

    int res=1;

    int cnt=0;

    for(int i=62;i>=0;i--){

        int u=(and_sum>>i)&1;

        int v=(xor_sum>>i)&1;

        //cerr<<u<<" "<<v<<endl;

        if(u==1&&v==1){

            res=0;

        }else if(v==1&&u==0){

            res*=2;

        }

    }

    //cout<<res*2<<endl;

    if(and_sum==0){

        res-=2;

    }

    cout<<res<<endl;

}

signed main(){

    ios::sync_with_stdio(false),cin.tie(0);

    int t;

    t=1;

    while(t--){

        solve();

    }

}
```