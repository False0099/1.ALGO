The Master's Assistance Center has announced an entrance exam, which consists of the following.

The candidate is given a set $s$ of size $n$ and some strange integer $c$. For this set, it is needed to calculate the number of pairs of integers $(x, y)$ such that $0 \leq x \leq y \leq c$, $x + y$ **is not** contained in the set $s$, and also $y - x$ **is not** contained in the set $s$.

Your friend wants to enter the Center. Help him pass the exam!

**Input**

Each test consists of multiple test cases. The first line contains a single integer $t$ ($1 \leq t \leq 2 \cdot 10^4$) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $n$ and $c$ ($1 \leq n \leq 3 \cdot 10^5$, $1 \leq c \leq 10^9$) — the size of the set and the strange integer.

The second line of each test case contains $n$ integers $s_1, s_2, \ldots, s_{n}$ ($0 \leq s_1 \lt; s_2 \lt; \ldots \lt; s_{n} \leq c$) — the elements of the set $s$.

It is guaranteed that the sum of $n$ over all test cases does not exceed $3 \cdot 10^5$.

**Output**

For each test case, output a single integer — the number of suitable pairs of integers.

## 题解
本题的第一个点是使用容斥原理，把我们的原问题转换为简单易计算的问题，$(x+y)不在\land(x-y)不在$ = $ALL-(x+y)在-(x-y)在+(x+y)在\land(x-y)在$

又因为我们有：$x\leq y$,所以我们对应的方案书都是可以计算出来的。
假设我们的 $(x+y)$ 在，那么一定满足：$(x+y=s_{i})$,又因为我们的数量一定满足 $y\geq x$,所以我们就有：可能的对数一共有：$(\dfrac{s_{i}}{2})+1$ 种, 注意，我们要求我们的值小于我们的 C，所以我们的可能的取值范围就是：$\left[ \left( \dfrac{s_{i}}{2}+1 \right),c \right]$，两者之间取较小的。而又因为我们满足：$s_{i}\leq c$,所以我们可以直接省区讨论，直接就是我们的：$\left( \dfrac{s_{i}}{2}+1 \right)$。

假设我们的 $(x-y)$ 在，那么我们一定满足：$(y-x=s_{i})$,因此我们可能的 $y$ 就有：$s_{i}+x+1$ 种, 注意，因为我们要满足我们的值要小于我们的 C，所以我们可能的取值范围就是 $[c-s_{i}+1]$。

假设我们的两者同时都在，我们假设我们第一种对应的是 $s_{i}$,第二种对应的是 $s_{j}$,那么我们就有：$x=\frac{s_{1}+sj}{2},y=s_{1}-\frac{s_{j}}{2}$，也就是说，只要满足 $s_{1}+s{j}$ 为偶数，并且 $(s_{1}-s_{j})$ 为偶数，我们就一定能构成。因此，我们可以统计这个数列中的奇数和偶数个数，然后再对应的乘起来即可。


```cpp
#define int long long
void solve(){
    int n,c;
    cin>>n>>c;
    vector<int>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    
    //所有方案
    int s=(c+1)*(c+1+1)/2;
    //符合条件1，符合条件2的方案数,两个条件都符合的方案数
    int sa=0,sb=0,sab=0;
    for(int i=0;i<n;i++){
        int x=a[i];
        sa+=x/2+1;
        sb+=c-x+1;
    }
    //奇数和偶数
    int f=0,g=0;
    for(int i=0;i<n;i++){
        int x=a[i];
        if(x&1){
            f++;
            sab+=f;            
        } else {
            g++;
            sab+=g;
        }
    }
    int ans=s-sa-sb+sab;
    cout<<ans<<'\n';
}
```