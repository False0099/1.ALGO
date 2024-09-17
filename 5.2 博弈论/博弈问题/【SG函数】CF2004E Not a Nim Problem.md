题意：给你 n 个石堆，每一次你只能从一个石堆里取与这个石堆最大公约数为 1 数量的石堆，问先手是否必胜？

Two players, Alice and Bob, are playing a game. They have $n$ piles of stones, with the $i$ \-th pile initially containing $a_i$ stones.

On their turn, a player can choose any pile of stones and take any positive number of stones from it, with one condition:

-   let the current number of stones in the pile be $x$. It is not allowed to take from the pile a number of stones $y$ such that the greatest common divisor of $x$ and $y$ is not equal to $1$.

The player who cannot make a move loses. Both players play optimally (that is, if a player has a strategy that allows them to win, no matter how the opponent responds, they will win). Alice goes first.

Determine who will win.

**Input**

The first line contains a single integer $t$ ($1 \le t \le 10^4$) — the number of test cases.

Each test case consists of two lines:

-   the first line contains a single integer $n$ ($1 \le n \le 3 \cdot 10^5$);
-   the second line contains $n$ integers $a_1, a_2, \dots, a_n$ ($1 \le a_i \le 10^7$).

Additional constraint on the input: the sum of $n$ across all test cases does not exceed $3 \cdot 10^5$.

**Output**

For each test case, output Alice if Alice wins, or Bob if Bob wins.

## 题解
本题显然我们需要通过一个 SG 函数来进行处理，我们直接来进行一个打表，我们的达标代码如下所示：
```
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
map<int,int> mem;
void init(){
    function<int(int)> sg=[&](int num){
        if(mem.count(num)){
            return mem[num];
        }
        set<int> st;
        for(int i=1;i<=num;i++){
            if(__gcd(i,num)==1){
                //cerr<<mem[num-i]<<endl;
                st.insert(sg(num-i));
            }
        }
        for(int i=0;;i++){
            if(st.count(i)==false){
                return mem[num]=i;
            }
        }
    };
    sg(200);
    
}
//1 0 2 0 3 0 4 0 2 0 5 0 6 0 2 0 7 0 8 0 
void solve(){
    int n;
    cin>>n;
    //cerr<<"ok"<<endl;
    vector<int> a(n+1);
    int res=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        res^=mem[a[i]];
    }
    // for(int i=0;i<=200;i++){
    //     cout<<"i="<<i<<" sg="<<mem[i]<<endl;
    //     if(mem[i]==4){
    //         cerr<<"i="<<i<<" sg="<<mem[i]<<endl;
    //     }
    // }
    // cout<<endl;
    if(res==1){
        cout<<"Alice"<<endl;
    }else{
        cout<<"Bob"<<endl;
    }
    //cout<<endl;
   // cout<<endl;
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

之后，我们不难发现，我们的规律如下：
1. 我们的 $sg[质数]=质数编号$
2. 我们的 $sg[非质数]=最小的质因子的编号$

于是，我们就可以通过我们的简单的 log 级别的倍增来求出我们的结果，最后得到我们的答案。

```
#include <bits/stdc++.h>

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

constexpr int N = 1E7;

int sg[N + 1];
std::vector<int> minp, primes;

void sieve(int n) {
    minp.assign(n + 1, 0);
    primes.clear();
    
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            primes.push_back(i);
        }
        
        for (auto p : primes) {
            if (i * p > n) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                break;
            }
        }
    }
}

void solve() {
    int n;
    std::cin >> n;
    
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int a;
        std::cin >> a;
        ans ^= sg[a];
    }
    
    if (ans != 0) {
        std::cout << "Alice\n";
    } else {
        std::cout << "Bob\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    sieve(N);
    sg[0] = 0;
    sg[1] = 1;
    sg[2] = 0;
    for (int i = 1; i < primes.size(); i++) {
        sg[primes[i]] = i + 1;
    }
    for (int i = 3; i <= N; i++) {
        sg[i] = sg[minp[i]];
    }
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
```