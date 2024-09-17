You have to restore the wall. The wall consists of N pillars of bricks, the height of the i-th pillar is initially equal to hi, the height is measured in number of bricks. After the restoration all the N pillars should have equal heights.

You are allowed the following operations:

- put a brick on top of one pillar, the cost of this operation is A;
- remove a brick from the top of one non-empty pillar, the cost of this operation is R;
- move a brick from the top of one non-empty pillar to the top of another pillar, the cost of this operation is M.

You cannot create additional pillars or ignore some of pre-existing pillars even if their height becomes 00.

What is the minimal total cost of restoration, in other words, what is the minimal total cost to make all the pillars of equal height?

## Input

The first line of input contains four integers N, A, R, M (1≤N≤105, 0≤A,R,M≤104) — the number of pillars and the costs of operations.

The second line contains N integers hi (0≤hi≤109) — initial heights of pillars.

## Output

Print one integer — the minimal cost of restoration.

## Sample 1

|Inputcopy|Outputcopy|
|---|---|
|3 1 100 100<br>1 3 8|12|

## Sample 2

|Inputcopy|Outputcopy|
|---|---|
|3 100 1 100<br>1 3 8|9|

## Sample 3

|Inputcopy|Outputcopy|
|---|---|
|3 100 100 1<br>1 3 8|4|

## Sample 4

|Inputcopy|Outputcopy|
|---|---|
|5 1 2 4<br>5 5 3 6 5|4|

## Sample 5

|Inputcopy|Outputcopy|
|---|---|
|5 1 2 2<br>5 5 3 6 5|3|


## 题解
对于本题，我们应该有一种既视感，感觉这个题是不是跟我们的考试时间有点像，我们可以考虑枚举我们的最终高度 h，并贪心的计算，达到这个 h 我们所需要的代价，并且每次比较即可。

```cpp
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 5;
ll A[MAXN];
ll n, a, r, m;
ll run(ll x)
{
    ll low = 0, high = 0;
    for (int i = 0; i < n; ++i)
        if (A[i] < x)
            low += x - A[i];
        else
            high += A[i] - x;
    if (m > a + r)
        return low * a + high * r;
    else if (high > low)
        return m * low + (high - low) * r;
    else
        return m * high + (low - high) * a;
}
int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> a >> r >> m;
    for (int i = 0; i < n; ++i)
        cin >> A[i];
    int l = 0, r = 1e9, mid;
    ll ans = 1e18;
    while (l + 1 < r) // 直到只剩不到三个数为止
    {
        mid = (l + r) / 2;
        ll a1 = run(mid - 1), a2 = run(mid + 1);
        if (a1 > a2)
            ans = min(ans, a1), l = mid;
        else
            ans = min(ans, a2), r = mid;
    }
    ans = min(ans, run(l));
    ans = min(ans, run(r));
    cout << ans << endl;
    return 0;
}
```
```
