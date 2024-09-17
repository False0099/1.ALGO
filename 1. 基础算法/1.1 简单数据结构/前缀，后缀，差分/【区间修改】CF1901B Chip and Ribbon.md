There is a ribbon divided into $n$ cells, numbered from $1$ to $n$ from left to right. Initially, an integer $0$ is written in each cell.

Monocarp plays a game with a chip. The game consists of several turns. During the first turn, Monocarp places the chip in the $1$ \-st cell of the ribbon. During each turn **except for the first turn**, Monocarp does **exactly one** of the two following actions:

-   move the chip to the next cell (i. e. if the chip is in the cell $i$, it is moved to the cell $i+1$). This action is impossible if the chip is in the last cell;
-   choose any cell $x$ and teleport the chip into that cell. **It is possible to choose the cell where the chip is currently located**.

At the end of each turn, the integer written in the cell with the chip is increased by $1$.

Monocarp's goal is to make some turns so that the $1$ \-st cell contains the integer $c_1$, the $2$ \-nd cell contains the integer $c_2$, ..., the $n$ \-th cell contains the integer $c_n$. He wants to teleport the chip as few times as possible.

Help Monocarp calculate the minimum number of times he has to teleport the chip.

**Input**

The first line contains one integer $t$ ($1 \le t \le 10^4$) — the number of test cases.

Each test case consists of two lines:

-   the first line contains one integer $n$ ($1 \le n \le 2 \cdot 10^5$);
-   the second line contains $n$ integers $c_1, c_2, \dots, c_n$ ($0 \le c_i \le 10^9$; $c_1 \ge 1$).

It can be shown that under these constraints, it is always possible to make a finite amount of turns so that the integers in the cells match the sequence $c_1, c_2, \dots, c_n$.

Additional constraint on the input: the sum of values of $n$ over all test cases does not exceed $2 \cdot 10^5$.

**Output**

For each test case, print one integer — the minimum number of times Monocarp has to teleport the chip.

## 题解
模拟法：
我们这是一个比较朴素的模型，每次我们将一个区间+1，问我们多少次能够得到这个数组。特别的是我们可以将某个 $[1,i]$ 区间免费加一次。**相当于我们一开始的值不全是 0 而是全是 1**.这一点就体现在了我们的起始时，我们的 last 不是 0 而是 1。

我们发现，如果我们的数组是形如：`5 4 3 2 1` 这样的，那么我们只需要满足把我们的最大值安排好，在他右边的相连的，比它小的也都能一起安排好。
之后，我们就只需要找到数列中所有的递减数列。然后我们每个递减数列变得合法的代价就是我们的 $a[i]-last$,其中 $last$ 指的是我们的递减数列第一个元素和我们前面元素的差值。


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
    vector<int>a(n+1,0);
    for(int i=1;i<=n;i++) cin>>a[i];
    
    i64 ans=0;
    i64 ad=0;
    for(int i=1;i<=n;)
    {
        if(a[i]==0)
        {
            ad=0;
            i++;
            continue;
        }
        int r=i;
        while(r<n && a[r+1]<=a[r]) r++;
        if(i==1)
        {
            ans+=a[i]-1;
            ad=a[r];
        }
        else
        {
            ans+=a[i]-ad;
            ad=a[r];
        }
        i=r+1;
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