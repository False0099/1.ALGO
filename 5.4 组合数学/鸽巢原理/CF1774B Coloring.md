# Coloring

## 题面翻译

Cirno_9 baka 的纸条上有 $n$ 个格子，他觉得空白的纸条看着有点无趣，于是想在纸条的格子上涂上 $m$ 种颜色。同时，他认为第 $i$ 种颜色必须要用 $a_i$ 次，且每连续 $k$ 个格子里涂的颜色必须互不相同。

Cirno_9 baka 想知道有没有这样的一种涂色方案能符合他的要求。
### 输入格式
第一行，一个整数 $t$ ( $1 \leq t \leq 10\,000$ ) 表示测试用例的个数。

**对于每组测试用例：**

第一行，输入三个整数 $n$ , $m$ , $k$ ( $1 \leq k \leq n \leq 10^9$ , $1 \leq m \leq 10^5$ , $m \leq n$ )$\\$

第二行，$m$ 个整数 $a_1,a_2,\cdots,a_m$ ( $1\leq a_i\leq n$ ) 并且保证 $ a_1 + a_2 + \ldots + a_m = n $

保证每组测试用例中的 $m$ 的和不超过 $10^5$。
### 输出格式
对于每组测试用例，如果有至少一种涂色的方案，输出"YES"；否则输出"NO"。

输出不区分大小写。
### 样例提示
第一个测试用例中，没有任何涂色的方案满足所有要求。

第二个测试用例中，可以将纸条涂成 $(1,2,1,2,3,4,3,4,5,6,5,6)$，对于每两个连续的格子，颜色都是互不相同的。

## 题目描述

Cirno\_9 baka has a paper tape with $ n $ cells in a row on it. As he thinks that the blank paper tape is too dull, he wants to paint these cells with $ m $ kinds of colors. For some aesthetic reasons, he thinks that the $ i $ -th color must be used exactly $ a_i $ times, and for every $ k $ consecutive cells, their colors have to be distinct.

Help Cirno\_9 baka to figure out if there is such a way to paint the cells.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10\, 000 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains three integers $ n $ , $ m $ , $ k $ ( $ 1 \leq k \leq n \leq 10^9 $ , $ 1 \leq m \leq 10^5 $ , $ m \leq n $ ). Here $ n $ denotes the number of cells, $ m $ denotes the number of colors, and $ k $ means that for every $ k $ consecutive cells, their colors have to be distinct.

The second line of each test case contains $ m $ integers $ a_1, a_2, \cdots , a_m $ ( $ 1 \leq a_i \leq n $ ) — the numbers of times that colors have to be used. It's guaranteed that $ a_1 + a_2 + \ldots + a_m = n $ .

It is guaranteed that the sum of $ m $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output "YES" if there is at least one possible coloring scheme; otherwise, output "NO".

You may print each letter in any case (for example, "YES", "Yes", "yes", and "yEs" will all be recognized as positive answers).

## 样例 #1

### 样例输入 #1

```
2
12 6 2
1 1 1 1 1 7
12 6 2
2 2 2 2 2 2
```

### 样例输出 #1

```
NO
YES
```

## 提示

In the first test case, there is no way to color the cells satisfying all the conditions.

In the second test case, we can color the cells as follows: $ (1, 2, 1, 2, 3, 4, 3, 4, 5, 6, 5, 6) $ . For any $ 2 $ consecutive cells, their colors are distinct.

## 题解
我们这一题可以通过鸽巢原理来进行涂色，因为我们连续 k 种不能相同，于是，我们就在 1, k+1, k+k+1 的位置涂上相同的颜色，也就是说，我们最多只能图 $\dfrac{n}{k}$ 种我们的颜色，因此，只要有一个 $a_{i}>n/k$,我们就不满足。

另外，我们还有一种情况需要考虑，就是达到我们的上限的颜色种类，只能有一种。
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,k,p,x,nm;
bool b;
void IOS()//个人写习惯了 cin/cout，这三句是对 cin 的优化，可以让 cin 和 scanf 速度差不多
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return;
}
int main()
{
    IOS();
    cin>>T;
    while(T--)
    {
    	cin>>n>>m>>k;
    	p=n/k;
        //这里以 p+1 作为最大值
        //如果 k 是 n 的因数，虽然最大值会多 1，但下一句中 nm（统计最大值个数）就会变成 0，不会有问题
    	nm=n-p*k;
    	b=1;
    	for(int i=1;i<=m;i++)
    	{
            cin>>x;
            if(x>p+1) b=0;//大于最大值不行
            if(x==p+1) nm--;//等于最大值，个数减一
            if(nm<0) b=0;//个数小于 0 也不行
        }
        if(!b) cout<<"NO"<<endl;
        else cout<<"YES"<<endl;
    }
    return 0;
}
```

 