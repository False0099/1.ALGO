Faineant Komorebi comes to play games with Setsuna again! To make the game fun, Komorebi decides to ask Setsuna to create a new game that he has never played before.

Thus, Setsuna gives the rule of the game as follow:

1.  Setsuna brings a pile of $x$ stones and chooses a magical number $k$, where $x>0$.
2.  Komorebi brings a pile of $y$ stones, where $y>0$. So now there are two piles of stones, each containing $x$ stones and $y$ stones.
3.  Setsuna and Komorebi take turns to take the stones, and Setsuna goes first. If someone can't do any operation in this turn, he loses the game.

During each turn, the player has only two choices:

1.  Take $a$ stones from one of the piles, where $a>0$.
2.  Take $a$ stones from Setsuna's pile and $b$ stone from Komorebi's pile, where $a>0,b>0,|a-b| \leq k$.

Even if Komorebi's brain is exhausted, he still thinks there must be something wrong with the game. When Setsuna gives the number of stones in the first pile, how many stones should Komorebi bring in order to be sure to win?

As Komorebi is quite lazy, if there are multiple answers, output the minimum one.

Formally, when $x$ and $k$ are determined, find the minimum $y$ to ensure that Komorebi wins.

## 输入
Each test contains multiple test cases.

The first line contains $t (1\leq t\leq 2 \times 10^5)$, the number of test cases.

Each test case contains two integers $x,k(1 \leq x,k \leq 10^7)$.

## 输出
Output $t$ lines.

Each line contains an integer indicating the minimum $y$.

## 题解
我们这一题就是给定两堆石子，然后要求我们那的两堆式子取得差值不能超过 k，这个就是我们的威佐夫游戏，而对于这种游戏，我们有一个固定的结论：如果我们满足
$x_{i}=\lfloor \phi \times i\rfloor,y=\lfloor\phi^2 \times i \rfloor$,那么我们这个状态一定是我们的必败态。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

void solve()
{
    int x,k;
    scanf("%d%d",&x,&k);
    ll b=k-1,c=-k-1;
    long double r=(sqrtl(b*b-4*c)-b)/2,s=r+k+1;
    if((ll)(ceil(x/s)*s)==x) printf("%lld\n",(ll)(ceil(x/s)*r));
    else printf("%lld\n",(ll)(ceil(x/r)*s));
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}
```