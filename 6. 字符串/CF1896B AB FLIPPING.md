You are given a string $s$ of length $n$ consisting of characters $\texttt{A}$ and $\texttt{B}$. You are allowed to do the following operation:

-   Choose an index $1 \le i \le n - 1$ such that $s_i = \texttt{A}$ and $s_{i + 1} = \texttt{B}$. Then, swap $s_i$ and $s_{i+1}$.

You are only allowed to do the operation **at most once** for each index $1 \le i \le n - 1$. However, you can do it in any order you want. Find the maximum number of operations that you can carry out.

**Input**

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 1000$). Description of the test cases follows.

The first line of each test case contains a single integer $n$ ($2 \le n \le 2\cdot 10^5$) — the length of string $s$.

The second line of each test case contains the string $s$ ($s_i=\texttt{A}$ or $s_i=\texttt{B}$).

It is guaranteed that the sum of $n$ over all test cases does not exceed $2\cdot 10^5$.

**Output**

For each test case, print a single integer containing the maximum number of operations that you can carry out.

## 题解
我们这一题不难发现，我们只需要找到第一个 $A$，然后再找到我们最后一个 B，然后我们能交换的长度就是我们的 $pos[B]-pos[A]$ 次,
或者我们也可采用我们的直接模拟法，模拟我们的操作即可。
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
    int n;cin>>n;
    string s;cin>>s;s=" "+s;
    int ans=0;
    vector<int>vis(n+1,0);
    for(int i=n-1;i>=1;i--)
    {
        if(s[i]=='A')
        {
            int r=i;
            while(r<n && !vis[r] && s[r+1]=='B')
            {
                swap(s[r],s[r+1]);
                vis[r]=1;ans++;
                r++;
            }
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