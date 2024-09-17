Beacon towers are built throughout and alongside the Great Wall. There was once a time when there were $n$ beacon towers built from west to east for defending against the invaders. The altitude of the $i$ \-th beacon tower, based on historical records, is $a_i$.

The defenders divide strategically all beacon towers into $k$ parts where each part contains several, but at least one, consecutive beacon towers. The scale of an individual part is given by the difference between the highest and the lowest altitudes of beacon towers, and the most sensible partition maximizes the sum of scales of all parts.

As a historian, you are dying to know the maximum sums of scales for every $k = 1, 2, \ldots, n$.

**Input**

The first line contains an integer $n$ $(1 \leq n \leq 10^4)$, denoting the number of beacon towers alongside the Great Wall.

The second line contains $n$ integers $a_1, a_2, \ldots, a_n$, where the $i$ \-th integer $a_i$ $(1 \leq a_i \leq 10^5)$ is the altitude of the $i$ \-th beacon tower.

**Output**

Output $n$ lines, the $i$ \-th of which contains an integer indicating the maximum sum for $k = i$.

## 题解
我们这一题需要求解把我们的数组分成 K 段后，我们的最大价值之和是多少。这里，我们就可以用我们的一个 dp 来进行。

我们考虑怎么样设计我们的 dp 状态，首先，常规的，我们需要知道当前进行到第几个，也要知道当前已经有多少个子段了，之后，我们还需要知道，我们的每一段中是否已经确定了我们的最大值，最小值。

在这里，我们的方法是，通过设置一个额外的状态为，表示我们对于每一段，是否已经选择了他对应的最大值或者最小值。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define pb push_back
#define mp make_pair
#define vi vector<int>
#define vll vector<ll>
#define fi first
#define se second
const int maxn = 1e4 + 5;
const int mod = 1e9 + 7;
const int inf = 1e9;
int a[maxn] , dp[maxn][maxn][3];
int main()
{
    for (int i = 0 ; i < maxn ; i++)
        for (int j = 0 ; j < maxn ; j++)
            for (int k = 0 ; k <= 2 ; k++)
                dp[i][j][k] = -inf;

    ios::sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 1 ; i <= n ; i++) cin >> a[i];
    dp[1][0][0] = 0;
    for (int i = 1 ; i <= n ; i++){
        for (int j = 0 ; j < i ; j++){
            if (dp[i][j][0] != -inf){
                // 不填
                dp[i + 1][j][0] = max(dp[i + 1][j][0] , dp[i][j][0]);
                // 填一个-1
                dp[i + 1][j][2] = max(dp[i + 1][j][2] , dp[i][j][0] - a[i]);
                // 填一个1
                dp[i + 1][j][1] = max(dp[i + 1][j][1] , dp[i][j][0] + a[i]);
                // 同时填 +1 -1
                dp[i + 1][j + 1][0] = max(dp[i + 1][j + 1][0] , dp[i][j][0]);
            }
            if (dp[i][j][1] != -inf){
                // 不填
                dp[i + 1][j][1] = max(dp[i + 1][j][1] , dp[i][j][1]);
                // 填一个-1
                dp[i + 1][j + 1][0] = max(dp[i + 1][j + 1][0] , dp[i][j][1] - a[i]);
            }
            if (dp[i][j][2] != -inf){
                // 不填
                dp[i + 1][j][2] = max(dp[i + 1][j][2] , dp[i][j][2]);
                // 填一个+1
                dp[i + 1][j + 1][0] = max(dp[i + 1][j + 1][0] , dp[i][j][2] + a[i]);
            }
        }
    }
    for (int i = 1 ; i <= n ; i++){
        cout << dp[n + 1][i][0] << endl;
    }
    return 0;
}

```