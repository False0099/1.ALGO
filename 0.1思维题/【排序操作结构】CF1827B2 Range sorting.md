# Range Sorting (Hard Version)

## 题面翻译

对一个元素两两不同的数组 $\{p_i\}$ 的一段区间 $[l,r]$ 排序的代价为 $r-l$ ，对整个数组 $p_i$ 排序的代价为选定若干区间并排序，使得整个数组有序的代价之和。

求 $\{a_i\}$ 的所有子段排序的代价之和。

## 题目描述

The only difference between this problem and the easy version is the constraints on $ t $ and $ n $ .

You are given an array $ a $ , consisting of $ n $ distinct integers $ a_1, a_2, \ldots, a_n $ .

Define the beauty of an array $ p_1, p_2, \ldots p_k $ as the minimum amount of time needed to sort this array using an arbitrary number of range-sort operations. In each range-sort operation, you will do the following:

- Choose two integers $ l $ and $ r $ ( $ 1 \le l < r \le k $ ).
- Sort the subarray $ p_l, p_{l + 1}, \ldots, p_r $ in $ r - l $ seconds.

Please calculate the sum of beauty over all subarrays of array $ a $ .

A subarray of an array is defined as a sequence of consecutive elements of the array.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line of each test case consists of $ n $ integers $ a_1, a_2,\ldots, a_n $ ( $ 1\le a_i\le 10^9 $ ). It is guaranteed that all elements of $ a $ are pairwise distinct.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output the sum of beauty over all subarrays of array $ a $ .

## 样例 #1

### 样例输入 #1

```
5
2
6 4
3
3 10 6
4
4 8 7 2
5
9 8 2 4 6
12
2 6 13 3 15 5 10 8 16 9 11 18
```

### 样例输出 #1

```
1
2
8
16
232
```

## 提示

In the first test case:

- The subarray $ [6] $ is already sorted, so its beauty is $ 0 $ .
- The subarray $ [4] $ is already sorted, so its beauty is $ 0 $ .
- You can sort the subarray $ [6, 4] $ in one operation by choosing $ l = 1 $ and $ r = 2 $ . Its beauty is equal to $ 1 $ .

 The sum of beauty over all subarrays of the given array is equal to $ 0 + 0 + 1 = 1 $ .In the second test case:

- The subarray $ [3] $ is already sorted, so its beauty is $ 0 $ .
- The subarray $ [10] $ is already sorted, so its beauty is $ 0 $ .
- The subarray $ [6] $ is already sorted, so its beauty is $ 0 $ .
- The subarray $ [3, 10] $ is already sorted, so its beauty is $ 0 $ .
- You can sort the subarray $ [10, 6] $ in one operation by choosing $ l = 1 $ and $ r = 2 $ . Its beauty is equal to $ 2 - 1 = 1 $ .
- You can sort the subarray $ [3, 10, 6] $ in one operation by choosing $ l = 2 $ and $ r = 3 $ . Its beauty is equal to $ 3 - 2 = 1 $ .

 The sum of beauty over all subarrays of the given array is equal to $ 0 + 0 + 0 + 0 + 1 + 1 = 2 $ .
## 题解
首先，本题我们有结论：对于一个区间 $[l,r]$ 我们的最少的操作次数就是：$$r-l+1-\sum_{i=l}^{r-1}\left[\max_{j=l}^ia_j<\min_{j=i+1}^ra_j\right]$$
证明如下：
首先，我们的 $r-l+1$ 表示我们对我们的每一个间隙都去进行排序，这么操作可以**保证我们是有序地**，然后我们的 $[max_{j=l}^i a_{j}<min_{j=i}^ra_{j}]$ 的**几何**含义也就是说，我们的右侧是**完完全全**大于我们的左侧的，在这种情况下，我们就可以分开两侧来处理，我们**不需要在这一个间隙还去交换**。因而我们的次数能够$-1$ 。

或者：考虑位置为 $x$,如果只用对 $[l,x]$ 和 $[x+1,r]$ 分别排序。当前区间排序的贡献就会-1。
那么 $\operatorname*{max}_j=l^xa_j<\operatorname*{min}_{j=x+1}^ra_j.$


之后，我们考虑怎么对于我们的每一个区间，都去求出我们的这一个答案。这个时候，我们显然就有：$$\sum_{l=1}^{n-1}\sum_{r=l+1}^{n}\left(r-l+1\right)-\sum_{i=l}^{r-1}[max<min],$$

然后就到了经典的交换求和顺序的环节。发现直接枚举不好算，我们可以钦定每个 $a_i$ 为 $[x+1,r]$ 的最小值。 (钦定为最大值也可以)。然后求当前满足要求的区间个数。


· 实际是寻找满足上述式子的 $l_{min}$ 和 $r_{max}$,那么区间数量就是 $(r_{max}-i+1)\times(x-l_{min}+1)$
![[Pasted image 20240508172936.png]]



·可以发现，$x$ 是从 $i$ 往前第一个值小于 $a_i$ 的位置，否则 $a_i$ 一定不是 $[x+1,r]$ 的最小值。
根据 $\operatorname*{max}_j=l^xa_j<a_i$,从 $x$ 往前找 $l_min$ 即可。
·根据 $a_i$ 是 $[x+1,r]$ 的最小值，$r_{max}$ 是从 $i$ 往后第一个值小于 $a_i$ 的往前一个位置，否则 $a_i$ 一定不是 $[x+1,r]$ 的最小值。

对于我们怎么求出我们的上面两个值，我们可以考虑分别用单调栈和我们的 ST 表来求解。
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=5e5+5;
int n,t,a[N],f[20][N],r[N];
long long ans;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--)
    {
        ans=0;
        cin>>n;
        a[0]=a[n+1]=0;
        for(int i=1;i<=n;i++) cin>>a[i],f[0][i]=a[i],ans+=1ll*i*(i-1)/2;
        for(int j=1;j<20;j++)
            for(int i=1;i+(1<<j)-1<=n;i++)
                f[j][i]=max(f[j-1][i],f[j-1][i+(1<<j-1)]);
        stack<int> st;
        st.push(n+1);
        for(int i=n;i;i--)
        {
            //这里求的实际是 r_min+1，从后往前第一个小于 a[i] 的位置
            while(a[st.top()]>a[i]) st.pop();
            r[i]=st.top();
            st.push(i);
        }
        while(!st.empty()) st.pop();
        st.push(0);
        for(int i=1;i<=n;i++)
        {
            //这里求的是 x
            while(a[st.top()]>a[i]) st.pop();
            int j=st.top();
            //跳表求 l_min
            for(int k=19;~k;k--)
                if(j>(1<<k)&&f[k][j-(1<<k)]<a[i]) j-=1<<k;
            if(st.top()>0) ans-=1ll*(r[i]-i)*(st.top()-j+1);
            st.push(i);
        }
        cout<<ans<<'\n';
    }
}
```