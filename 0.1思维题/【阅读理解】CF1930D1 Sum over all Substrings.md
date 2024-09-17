**This is the easy version of the problem. The only difference between the two versions is the constraint on $t$ and $n$. You can make hacks only if both versions of the problem are solved.**

For a binary $^\dagger$ pattern $p$ and a binary string $q$, both of length $m$, $q$ is called $p$ \-good if for every $i$ ($1 \leq i \leq m$), there exist indices $l$ and $r$ such that:

-   $1 \leq l \leq i \leq r \leq m$, and
-   $p_i$ is a mode $^\ddagger$ of the string $q_l q_{l+1} \ldots q_{r}$.

For a pattern $p$, let $f(p)$ be the minimum possible number of $\mathtt{1}$ s in a $p$ \-good binary string (of the same length as the pattern).

You are given a binary string $s$ of size $n$. Find

$$
\sum_{i=1}^{n} \sum_{j=i}^{n} f(s_i s_{i+1} \ldots s_j).
$$
 In other words, you need to sum the values of $f$ over all $\frac{n(n+1)}{2}$ substrings of $s$.

$^\dagger$ A binary pattern is a string that only consists of characters $\mathtt{0}$ and $\mathtt{1}$.

$^\ddagger$ Character $c$ is a mode of string $t$ of length $m$ if the number of occurrences of $c$ in $t$ is at least $\lceil \frac{m}{2} \rceil$. For example, $\mathtt{0}$ is a mode of $\mathtt{010}$, $\mathtt{1}$ is not a mode of $\mathtt{010}$, and both $\mathtt{0}$ and $\mathtt{1}$ are modes of $\mathtt{011010}$.

**Input**

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 500$) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $n$ ($1 \le n \le 100$) — the length of the binary string $s$.

The second line of each test case contains a binary string $s$ of length $n$ consisting of only characters $\mathtt{0}$ and $\mathtt{1}$.

It is guaranteed that the sum of $n^2$ over all test cases does not exceed $10^4$.

**Output**

For each test case, output the sum of values of $f$ over all substrings of $s$.

## 题意：
给你一个字符串，要你对他的所有子串的函数值 $f(p)$ 之和，其中 $f(p)$ 的定义为：使得与 p 匹配的，含有 1 最少的字符串中，1 的个数。

## 题解
首先我们的第一个难点是读题，接下来，因为我们本题的数据非常友好，我们可以考虑使用我们的暴力方法，先去枚举每一个子串，然后对每一个子串，计算我们的答案。

这里，我们计算答案的方法如下：

我们首席那观察到，如果一个位置放 1 了，那么他向后的连续 3 个位置（包括这个位置），都可以不放 1. 于是，我们就可以根据我们在某一个位置有没有 1，来决策我们的防止情况。

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define x first
#define y second
#define pdd pair<double,double>
#define pii pair<int,int>
#define pll pair<LL,LL>
#define mp make_pair
#define LL long long
#define ULL unsigned long long
#define sqr(x) ((x)*(x))
#define pi acos(-1)
#define MEM(x) memset(x,0,sizeof(x))
#define MEMS(x) memset(x,-1,sizeof(x))
using namespace std;
#define plus Plus
const int mod=998244353;

LL dp[1000005];
char c[1000005];
void solve(int T){
    int n;//=rand()%10+1;
    scanf("%d",&n);
    scanf("%s",c+1);
    //for(int i = 1;i<=n;i++){
   //     c[i]="01"[rand()%2];
  //  }
  //  c[n+1]=0;
  //  printf("%s\n",c+1);
    /*int aans=0;
    for(int i = 1;i<=n;i++){
        for(int j = i;j<=n;j++){
            int l=i;
            while(l<=j){
                if(c[l]=='1')aans++,l+=3;
                else l++;
            }
        }
    }*/
    dp[0]=0;
    for(int i = 1;i<=3&&i<=n;i++){
        if(c[i]=='1')dp[i]=i;
        else 
        dp[i]=dp[i-1];
    }
    for(int i = 4;i<=n;i++){
        if(c[i]=='0')dp[i]=dp[i-1];
        else{
            dp[i]=dp[i-3]+i;
        }
    }
    LL ans=0;
    for(int i =1;i<=n;i++){
        
        ans+=dp[i];
    }
    printf("%lld\n",ans);
    //printf("%d\n",aans);
    //assert(ans==aans);
}
int main(){
   
    int t=1;0000;
    scanf("%d",&t);
    for(int i = 1;i<=t;i++){
        solve(i);
    }
    return 0;
}
/*
*/
```