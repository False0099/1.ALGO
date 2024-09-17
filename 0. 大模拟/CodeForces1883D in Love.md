#暴力模拟 #STL库 
Initially, you have an empty multiset of segments. You need to process $q$ operations of two types:

-   $+$ $l$ $r$ — Add the segment $(l, r)$ to the multiset,
-   $-$ $l$ $r$ — Remove **exactly** one segment $(l, r)$ from the multiset. It is guaranteed that this segment exists in the multiset.

After each operation, you need to determine if there exists a pair of segments in the multiset that do not intersect. A pair of segments $(l, r)$ and $(a, b)$ do not intersect if there does not exist a point $x$ such that $l \leq x \leq r$ and $a \leq x \leq b$.

**Input**

The first line of each test case contains an integer $q$ ($1 \leq q \leq 10^5$) — the number of operations.

The next $q$ lines describe two types of operations. If it is an addition operation, it is given in the format $+$ $l$ $r$. If it is a deletion operation, it is given in the format $-$ $l$ $r$ ($1 \leq l \leq r \leq 10^9$).

**Output**

After each operation, print "YES" if there exists a pair of segments in the multiset that do not intersect, and "NO" otherwise.

You can print the answer in any case (uppercase or lowercase). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive answers.

## 题解
我们这一题直接按照他说的用一个 multiset 来模拟, 注意判断是否有覆盖，只要对于我们之前是 no 的时候，看我们的新增后是否是我们的

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

void solve()
{
    int n, l, r; cin>>n;
    char c;

    multiset<int> sts, ends;
    while(n--)
    {
        cin>>c>>l>>r;
        if(c == '+')sts.insert(l), ends.insert(r);
        else sts.erase(sts.find(l)), ends.erase(ends.find(r));

        if(ends.size() && *ends.begin() < *sts.rbegin())cout<<"YES\n";
        else cout<<"NO\n";
    }
}

signed main()
{
    int t = 1;
    while(t--)solve();
}
```