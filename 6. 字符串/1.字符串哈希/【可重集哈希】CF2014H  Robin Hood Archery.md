At such times archery was always the main sport of the day, for the Nottinghamshire yeomen were the best hand at the longbow in all merry England, but this year the Sheriff hesitated...

Sheriff of Nottingham has organized a tournament in archery. It's the final round and Robin Hood is playing against Sheriff!

There are $n$ targets in a row numbered from $1$ to $n$. When a player shoots target $i$, their score increases by $a_i$ and the target $i$ is destroyed. The game consists of turns and players alternate between whose turn it is. Robin Hood always starts the game, then Sheriff and so on. The game continues until all targets are destroyed. Both players start with score $0$.

At the end of the game, the player with most score wins and the other player loses. If both players have the same score, it's a tie and no one wins or loses. In each turn, the player can shoot any target that wasn't shot before. Both play optimally to get the most score possible.

Sheriff of Nottingham has a suspicion that he might lose the game! This cannot happen, you must help Sheriff. Sheriff will pose $q$ queries, each specifying $l$ and $r$. This means that the game would be played only with targets $l, l+1, \dots, r$, as others would be removed by Sheriff before the game starts.

For each query $l$, $r$, determine whether the Sheriff can **not lose** the game when only considering the targets $l, l+1, \dots, r$.

**Input**

The first line of input contains one integer $t$ ($1 \le t \le 10^4$) — the number of test cases.

The first line of each test case contains two integers $n$, $q$ ($1 \le n,q \le 2\cdot10^5$) — the number of targets and the queries Sheriff will pose.

The second line of each test case contains $n$ integers $a_1, a_2, \ldots, a_n$ ($1 \le a_i \le 10^6$) — the points for hitting each target.

Then follow $q$ lines, each with two integers $l$ and $r$ ($1 \le l \le r \le n$) — the range of the targets that is considered for each query.

It is guaranteed that the sum of both $n$ and $q$ across all test cases does not exceed $2 \cdot 10^5$.


**Output**

For each query, output "YES", if the Sheriff **does not lose the game** when only considering the targets $l, l+1, \dots, r$, and "NO" otherwise.

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.


## 题解
本题我们一个显然的结论是，先手一定不会输，于是我们如果希望平局，我们如果希望平局，我们一定要满足**区间内所有出现的数字的次数都是偶数**，而这就让我们想起了我们的异或，于是我们考虑维护我们的一个区间前缀异或和，然后如果我们的一段区间异或为 0，我们就代表这一段的对应的结果和为 1.。

同时，为了防止我们的【1，2，3】这种情况的出现，我们为我们的每一个数采用随机数的方法进行随机赋值。这样就能够做到以一个较高的正确率来维护我们的对应的答案。

```
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
const int N=1e6+10;
int trans[N];
mt19937 rnd(time(0));
void init(){
    for(int i=1;i<=1e6;i++){
        trans[i]=rnd();
    }
}
void solve(){
    int n,q;
    cin>>n>>q;
    vector<int> a(n+1);
    vector<int> sum(n+1,0);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i]=trans[a[i]];
    }       
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]^a[i];
    }
//    cerr<<endl;
    while(q--){
        int l,r;
        cin>>l>>r;
        if((sum[r]^sum[l-1])==0){
            cout<<"YES"<<endl;
        }else{
            cout<<"NO"<<endl;
        }
    }

}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
    cin>>t;
    init();
    while(t--){
        solve();
    }
}
```