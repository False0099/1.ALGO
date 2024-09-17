Kirill has two integer arrays $a_1,a_2,\ldots,a_n$ and $b_1,b_2,\ldots,b_n$ of length $n$. He defines the absolute beauty of the array $b$ as

$$
\sum_{i=1}^{n} |a_i - b_i|.
$$
 Here, $|x|$ denotes the absolute value of $x$.

Kirill can perform the following operation **at most once**:

-   select two indices $i$ and $j$ ($1 \leq i &lt; j \leq n$) and swap the values of $b_i$ and $b_j$.

Help him find the maximum possible absolute beauty of the array $b$ after performing **at most one** swap.

**Input**

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \leq t \leq 10\,000$). The description of test cases follows.

The first line of each test case contains a single integer $n$ ($2\leq n\leq 2\cdot 10^5$) — the length of the arrays $a$ and $b$.

The second line of each test case contains $n$ integers $a_1, a_2, \ldots, a_n$ ($1\leq a_i\leq 10^9$) — the array $a$.

The third line of each test case contains $n$ integers $b_1, b_2, \ldots, b_n$ ($1\leq b_i\leq 10^9$) — the array $b$.

It is guaranteed that the sum of $n$ over all test cases does not exceed $2\cdot 10^5$.

**Output**

For each test case, output one integer — the maximum possible absolute beauty of the array $b$ after no more than one swap.

## 题解
我们考虑直接进行我们的分类讨论，我们原始子中要求我们的 $|a_{i}-b_{i}|+|a_{j}-b_{j}|$,然后交换后，我们有 $|a_{i}-b_{j}|+|a_{j}-b_{i}|$,然后问我们最后的值是多少
或者我们也可以用我们的几何意义来计算：
**将 $a_{i}$ 和 $b_{i}$ 当作是线段的两个端点**，那么交换 $b_{i}$ 值相当于是交换了两个线段的端点，稍加模拟一下就会发现，交换之后多出了两倍的原线段之间的间隔，于是求最大两线段的间隔即可。

```cpp
#include<bits/stdc++.h>

#define i64 long long
#define ull unsigned long long
#define pii pair<int,int>
#define pll pair<i64,i64>

using namespace std;

const i64 mod=1e9+7;

struct node{
    i64 l,r,id;
};
void solve()
{
    int n;cin>>n;
    vector<pll>v(n+1);
    for(int i=1;i<=n;i++) cin>>v[i].first;
    for(int i=1;i<=n;i++) cin>>v[i].second;
    i64 sum=0;
    for(int i=1;i<=n;i++)
    {
        sum+=abs(v[i].first-v[i].second);
    }
    vector<node>line(n+1);
    for(int i=1;i<=n;i++)
    {
        if(v[i].first<=v[i].second) line[i]={v[i].first,v[i].second,1};
        else line[i]={v[i].second,v[i].first,2};
    }
    sort(line.begin()+1,line.end(),[&](const node &x,const node &y){
        if(x.l==y.l) return x.r<y.r;
        else return x.l<y.l;
    });
    i64 ans=sum;
    for(int i=1;i<=n;i++)
    {
        if(line[i].r < line[n].l)
        {
            i64 res=0;
            res-=abs(line[i].l-line[i].r)+abs(line[n].l-line[n].r);
            res+=line[n].r-line[i].l+line[n].l-line[i].r;
            ans=max(ans,res+sum);
        }
    }
    cout<<ans<<"\n";
}

int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout<<fixed<<setprecision(20);
    
    int t;cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;    
}
```