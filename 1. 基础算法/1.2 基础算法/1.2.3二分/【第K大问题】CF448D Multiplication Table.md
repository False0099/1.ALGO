# Multiplication Table

## 题面翻译

给出 n, m, k（$1\leq n,m\leq 5\times10^5,1\leq k\leq n\cdot m$）

请输出在 n*m 的乘法表中第 k 小的数。

即，给出一个 f[i][j]=i*j（$1\le i\le n,1\le j\le m$）的数组，将该数组内所有数（包含重复的）从小到大排序后的第 k 个数。

## 题目描述

Bizon the Champion isn't just charming, he also is very smart.

While some of us were learning the multiplication table, Bizon the Champion had fun in his own manner. Bizon the Champion painted an $ n×m $ multiplication table, where the element on the intersection of the $ i $ -th row and $ j $ -th column equals $ i·j $ (the rows and columns of the table are numbered starting from 1). Then he was asked: what number in the table is the $ k $ -th largest number? Bizon the Champion always answered correctly and immediately. Can you repeat his success?

Consider the given multiplication table. If you write out all $ n·m $ numbers from the table in the non-decreasing order, then the $ k $ -th number you write out is called the $ k $ -th largest number.

## 输入格式

The single line contains integers $ n $ , $ m $ and $ k $ $ (1<=n, m<=5·10^{5}; 1<=k<=n·m) $ .

## 输出格式

Print the $ k $ -th largest number in a $ n×m $ multiplication table.

## 样例 #1

### 样例输入 #1

```
2 2 2
```

### 样例输出 #1

```
2
```

## 样例 #2

### 样例输入 #2

```
2 3 4
```

### 样例输出 #2

```
3
```

## 样例 #3

### 样例输入 #3

```
1 10 5
```

### 样例输出 #3

```
5
```

## 提示

A $ 2×3 $ multiplication table looks like this:

`<br></br>1 2 3<br></br>2 4 6<br></br><br></br>`

## 题解
本体发现按，我们的元素是存在**可二分性的**，我们的第 K 大元素，也就是说要有 $K$ 个元素比他还要小，这个比他还要小的元素，我们就可以通过我们的二分法，我们再去**枚举我们的每一个 n**，求出对于这一个 $n$，有多少个元素比他还要小。全部加起来就是我们的最终答案。

于是，我们就可以通过下面的代码来求得我们的答案：
```
#include <bits/stdc++.h>

#define int long long

int INF=0x3f3f3f3f3f;

using namespace std;

void solve(){

    int n,m,k;

    cin>>n>>m>>k;

    int l=0,r=INF;

    auto check=[&](int mid){

        int sum=0;

        for(int i=1;i<=n;i++){

           sum+=min(m,mid/i);

        }

        if(sum>=k){

            return true;

        }else{

            return false;

        }

    };

    //cerr<<check(2)<<" "<<check(3)<<endl;

    while (l<r)

    {

        int mid=l+r>>1;

        if(check(mid)){

            r=mid;

        }else{

            l=mid+1;

        }

    }

    cout<<l<<endl;

}

signed main(){

    ios::sync_with_stdio(false),cin.tie(0);

    int t;

 //   cin>>t;

   t=1;

    while(t--){

        solve();

    }

}
```