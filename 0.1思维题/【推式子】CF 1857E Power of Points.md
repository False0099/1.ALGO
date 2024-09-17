# Power of Points

## 题面翻译

给定 $n$ 个数轴上的点，你需要依次选中每个点，计算选中该点的权值。

选中一个点后，将它和每一个点之间连一条线段（包括它自己），线段会覆盖两端点之间的整点一次（包括两个端点），权值定义为数轴上每个整点被覆盖的次数的和。

依次选中 $1$ 到 $n$ 的每个点，计算权值并输出。

## 题目描述

You are given $ n $ points with integer coordinates $ x_1,\dots x_n $ , which lie on a number line.

For some integer $ s $ , we construct segments \[ $ s, x_1 $ \], \[ $ s, x_2 $ \], $ \dots $ , \[ $ s, x_n $ \]. Note that if $ x_i<s $ , then the segment will look like \[ $ x_i, s $ \]. The segment \[ $ a, b $ \] covers all integer points $ a, a+1, a+2, \dots, b $ .

We define the power of a point $ p $ as the number of segments that intersect the point with coordinate $ p $ , denoted as $ f_p $ .

Your task is to compute $ \sum\limits_{p=1}^{10^9}f_p $ for each $ s \in \{x_1,\dots, x_n\} $ , i.e., the sum of $ f_p $ for all integer points from $ 1 $ to $ 10^9 $ .

For example, if the initial coordinates are $ [1,2,5,7,1] $ and we choose $ s=5 $ , then the segments will be: $ [1,5] $ , $ [2,5] $ , $ [5,5] $ , $ [5,7] $ , $ [1,5] $ . And the powers of the points will be: $ f_1=2, f_2=3, f_3=3, f_4=3, f_5=5, f_6=1, f_7=1, f_8=0, \dots, f_{10^9}=0 $ . Their sum is $ 2+3+3+3+5+1+1=18 $ .

## 输入格式

The first line contains an integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 2\cdot 10^5 $ ) — the number of points.

The second line contains $ n $ integers $ x_1, x_2 \dots x_n $ ( $ 1 \le x_i \le 10^9 $ ) — the coordinates of the points.


It is guaranteed that the sum of the values of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output $ n $ integers, where the $ i $ -th integer is equal to the sum of the powers of all points for $ s=x_i $ .

## 样例 #1

### 样例输入 #1

```
3
3
1 4 3
5
1 2 5 7 1
4
1 10 100 1000
```

### 样例输出 #1

```
8 7 6
16 15 18 24 16
1111 1093 1093 2893
```

## 提示

In the first test case we first choose $ s=x_1=1 $ , then the following segments are formed: $ [1,1] $ , $ [1,4] $ , $ [1,3] $ .

The powers of the points will be as follows: $ f_1=3, f_2=2, f_3=2, f_4=1, f_5=0 \dots $ The sum of powers of the points: $ 3+2+2+1+0+\dots+0=8 $ .

After that we choose $ s=x_2=4 $ . Then there will be such segments: $ [1,4] $ , $ [4,4] $ , $ [3,4] $ , and powers of the points are $ f_1=1, f_2=1, f_3=2, f_4=3 $ .

At the end we take $ s=x_3=3 $ and the segments look like this: $ [1,3] $ , $ [3,4] $ , $ [3,3] $ , the powers of the points are $ f_1=1, f_2=1, f_3=3, f_4=1 $ .

## 题解
对于本题来说，我们一个看似合理的方法显然是推式子，首先我们可以通过我们的排序来简化我们的分析构成，因为显然，我们的排序不会影响到我们的答案。
我们假设我们当前的位置为 $i$,然后我们就可以有下面的计算方式：$val[i]=\sum_{i=l}^i(a[i]-a[l]+1)+\sum_{R=i+1}^{n}(a[r]-a[l]+1)$

我们不妨把我们的上述式子进行我们的化简，我们就有：
$val[i]=\sum_{l=1}^ia[l]+n+\sum_{r=i+1}^na[r]+(2i-n)a[i]$,

我们发现，我们的前面的和后面的都是一个前缀和形式，于是我们就可以 $o(1)$ 的计算我们的上面的式子，最后求 $n$ 个式子的时间复杂度就是 $o(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=2e5+84;
struct Point{
    ll ad,id,ans;
    friend bool operator<(Point xy,Point zb){
        return xy.ad<zb.ad;
    }
}p[maxn];
ll T,n,qzh[maxn],hzh[maxn];
inline bool cmp(Point xy,Point zb){
    return xy.id<zb.id;
}
int main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld",&n);
        for(ll i=1;i<=n;i++){
            scanf("%lld",&p[i].ad);
            p[i].id=i;
        }
        sort(p+1,p+n+1);
        for(ll i=1;i<=n;i++)
            qzh[i]=qzh[i-1]+p[i].ad;
        hzh[n+1]=0;
        for(ll i=n;i>=1;i--)
            hzh[i]=hzh[i+1]+p[i].ad;
        for(ll i=1;i<=n;i++)
            p[i].ans=p[i].ad*(i-1)-qzh[i-1]-1+hzh[i+1]-p[i].ad*(n-i)+n+1;
        sort(p+1,p+n+1,cmp);
        for(ll i=1;i<=n;i++)
            printf("%lld ",p[i].ans);
        putchar('\n');
    }
    return 0;
}

```