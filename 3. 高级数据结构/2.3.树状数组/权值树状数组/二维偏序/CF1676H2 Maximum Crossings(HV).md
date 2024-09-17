# Maximum Crossings (Hard Version)

## 题面翻译

两个版本间唯一的区别是，此版本中 $n≤2·10^5，\sum n≤2·10^5$。

一个终端是一排 $n$ 个连接在一起的相等的线段，有两个终端，一上一下。

有一个数组 $a_i$，代表从上面的终端中第 $i$ 条线段，到下面的终端中第 $a_i$ 条线段，有一条连线。

问这些连线最多有几个交点。

## 题目描述

The only difference between the two versions is that in this version $ n \leq 2 \cdot 10^5 $ and the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

A terminal is a row of $ n $ equal segments numbered $ 1 $ to $ n $ in order. There are two terminals, one above the other.

You are given an array $ a $ of length $ n $ . For all $ i = 1, 2, \dots, n $ , there should be a straight wire from some point on segment $ i $ of the top terminal to some point on segment $ a_i $ of the bottom terminal. For example, the following pictures show two possible wirings if $ n=7 $ and $ a=[4,1,4,6,7,7,5] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676H2/71a1fe41f3cad0f3cbda88716457eefb4e46b4ca.png)A crossing occurs when two wires share a point in common. In the picture above, crossings are circled in red.

What is the maximum number of crossings there can be if you place the wires optimally?

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the length of the array.

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \leq a_i \leq n $ ) — the elements of the array.

The sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the maximum number of crossings there can be if you place the wires optimally.

## 样例 #1

### 样例输入 #1

```
4
7
4 1 4 6 7 7 5
2
2 1
1
1
3
2 2 2
```

### 样例输出 #1

```
6
1
0
3
```

## 提示

The first test case is shown in the second picture in the statement.

In the second test case, the only wiring possible has the two wires cross, so the answer is $ 1 $ .

In the third test case, the only wiring possible has one wire, so the answer is $0$ .

## 题解
我们对于这种问题，可以进行一波归纳，如果我们得两个线段相交了，那么我们一定有满足 $a_{i}\geq a_{j}$,并且**只要有 $a_{i}\geq a_{j}$ 我们就一定会相交**。这一点是我们可以通过我们画图来只管理解的。此时，我们得问题就变成了求逆序对，我们就可以用我们的树状数组去求了。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int> 
#define fir first
#define sec second
int tt;
int n,ans,a[200010],b[200010],c[200010];
int low_bit(int x)
{
    return x&(-x);
}
int query(int x)
{
    int s=0;
    while(x>0)
    {
        s+=c[x];
        x-=low_bit(x);
    }
    return s;
}
void add(int x,int v)
{
    while(x<=n)
    {
        c[x]+=v;
        x+=low_bit(x);
    }
}
void solve()
{
	cin>>n;
	memset(c,0,sizeof(c));
    ans=0;
    for(int i=1;i<=n;i++)b[i]=0;
    for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		b[a[i]]++;
	}
	for(int i=1;i<=n;i++)ans+=b[i]*(b[i]-1)/2;
    for(int i=n;i>=1;i--)
    {
        add(a[i],1);
        if(a[i]>1)ans+=query(a[i]-1);
    }
    cout<<ans<<endl;
}
signed main()
{
	cin>>tt;
	while(tt--)solve();
    return 0;
}
```