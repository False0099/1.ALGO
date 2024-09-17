## 描述：
Putata and Budada are organizing a game with $n$ players. Each player has some deposit, which is a real number. Player $i$ has $a_i$ deposits in the beginning. During each round of the game, the followings happen **in order**:

-   Player $1$ gives player $2$ half of player $1$ 's deposit.
-   Player $2$ gives player $3$ half of player $2$ 's deposit.
-   ...
-   Player $n-1$ gives player $n$ half of player $n-1$ 's deposit.
-   Player $n$ gives player $1$ half of player $n$ 's deposit.

The $n$ players played this game for exactly $2022^{1204}$ rounds. Putata wonders how much deposit each player has after the game. Please write a program to answer his question.

## 输入：
**Input**

The first line contains an integer $n$ ($2\leq n\leq 10^5$), denoting the number of players.

The second line contains $n$ integers $a_1,a_2,\ldots,a_n$ ($1\leq a_i \leq 10^6$), denoting the deposit player $i$ has in the beginning.

## 输出：
**Output**

Output one line with $n$ real numbers, denoting the deposit each player has after they played this game.

Your answer will be considered correct if its absolute or relative error does not exceed $10^{-6}$. Formally, let your answer be $a$, and the jury's answer be $b$. Your answer will be considered correct if $\frac{|a-b|}{\max(1,|b|)}\leq 10^{-6}$.

## 结果：
```
2
4 2

4.00 2.00
```

## 题解
对于本体来说，我们一开始没有什么思路，我们不妨打一个表看看我们的结果是多少：
```
#include <bits/stdc++.h>

#define int long long

int INF=0x3f3f3f3f3f;

using namespace std;

void solve(){

    int n;

    cin>>n;

    vector<double> a(n);

    for(int i=0;i<n;i++){

        cin>>a[i];

    }

    vector<double> prev=a;

    while(1){

        for(int i=0;i<n;i++){

            double tmp=a[i]/2;

            a[i]-=tmp;

            a[(i+1)%n]+=tmp;

        }

        bool tag=1;

        for(int i=0;i<n;i++){

            if(a[i]!=prev[i]){

                tag=0;

            }

        }

        if(tag){

            break;

        }

        prev=a;

    }

    for(auto u:prev){

        cout<<fixed<<setprecision(10)<<u<<" ";

    }

}

signed main(){

    ios::sync_with_stdio(false),cin.tie(0);

    int t;

 //   cin>>t;

    t=1;

    while(t--){

        solve();

    }

}
```

经过打表后，我们不难发现，我们的最终的**平衡态**一定是满足，我们的第一个是 $2t$,剩余的元素都是 $t$ 的。且我们的总和是不变的，于是我们就可以 $o(1)$ 的计算出我么的最终结果。

```
#include <bits/stdc++.h>

#define int long long

int INF=0x3f3f3f3f3f;

using namespace std;

void solve(){

    int n;

    cin>>n;

    cout<<fixed<<setprecision(10);

    vector<double> a(n);

    double sum=0;

    for(int i=0;i<n;i++){

        cin>>a[i];

        sum+=a[i];

    }

    double t=sum/(n+1);

    cout<<2*t<<" ";

    for(int i=1;i<n;i++){

        cout<<t<<" ";

    }

    cout<<endl;

}

signed main(){

    ios::sync_with_stdio(false),cin.tie(0);

    int t;

 //   cin>>t;

    t=1;

    while(t--){

        solve();

    }

}
```