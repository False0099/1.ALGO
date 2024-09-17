You are given two arrays $a$ and $b$ of size $n$. The beauty of the arrays $a$ and $b$ is the number of indices $i$ such that $a_i \gt b_i$.

You are also given an integer $x$. Determine whether it is possible to rearrange the elements of $b$ such that the beauty of the arrays becomes $x$. If it is possible, output one valid rearrangement of $b$.

**Input**

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.

The first line of each test case contains two integers $n$ and $x$ ($1 \le n \le 2\cdot 10^5$, $0 \le x \le n$) — the size of arrays $a$ and $b$ and the desired beauty of the arrays.

The second line of each test case contains $n$ integers $a_1, a_2, \ldots, a_n$ ($1 \le a_i \le 2n$) — the elements of array $a$.

The third line of each test case contains $n$ integers $b_1, b_2, \ldots, b_n$ ($1 \le b_i \le 2n$) — the elements of array $b$.

It is guaranteed that the sum of $n$ over all test cases does not exceed $2\cdot 10^5$.

**Output**

For each test case, output "NO" if it is not possible to rearrange $b$ to make the beauty of the arrays equal to $x$.

Otherwise, output "YES". Then, on the next line, output $n$ integers which represent the rearrangement of $b$.

If there are multiple solutions, you may output any of them.

You can output "YES" and "NO" in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 题解
我们这一题的关键也是找到我们最后达到要求时的状态。首先，因为我们对于位子没有要求，我们就可以先将我们的两个数组都进行一个排序，之后，我们可以再根据我们的排序结果去进行我们的构造。
我们发现，如果最后的数组之美为 x，那么我们最后就有 x 个 $a_{i}>b_{i}$,剩下的都比我们的 $b$ 要小。我们就让我们的 a 的最大元素和我们 $b$ 的最小 k 个元素按照大小依次匹配，剩下的用于我们去检查我们是否合法。如果合法，代表我们存在一种方案，否则我们就不存在一种方案。
```cpp
#include<bits/stdc++.h>

#define i64 long long
#define ull unsigned long long
#define pii pair<int,int>
#define pll pair<i64,i64>

using namespace std;

const i64 mod=1e9+7;

void solve()
{
    int n,x;cin>>n>>x;
    vector<int>a(n+1,0),b(n+1,0);
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    vector<pii>v(n+1);
    for(int i=1;i<=n;i++)
    {
        v[i]={a[i],i};
    }
    sort(v.begin()+1,v.end());
    sort(b.begin()+1,b.end());
    vector<int>ans(n+1,0);
    int now=x;
    for(int i=n;i>=n-x+1;i--)
    {
        if(v[i].first <= b[now])
        {
            cout<<"NO"<<"\n";
            return;
        }
        ans[v[i].second]=b[now];
        now--;
    }
    now=n;
    for(int i=n-x;i>=1;i--)
    {
        if(v[i].first > b[now])
        {
            cout<<"NO"<<"\n";
            return;
        }
        ans[v[i].second]=b[now];
        now--;
    }
    cout<<"YES"<<"\n";
    for(int i=1;i<=n;i++)
    {
        cout<<ans[i]<<" ";
    }
    cout<<"\n";
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