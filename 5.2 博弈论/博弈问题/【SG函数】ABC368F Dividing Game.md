### Problem Statement
题意：给你一个数列，其中有 N 个数，要求进行变化，每一次选择一个 $a$,将他变成一个非自身的因数，问你最后谁必胜。


You are given a sequence of $N$ positive integers $A = (A_1, A_2, \dots ,A_N)$, where each element is at least $2$. Anna and Bruno play a game using these integers. They take turns, with Anna going first, performing the following operation.

-   Choose an integer $i \ (1 \leq i \leq N)$ freely. Then, freely choose a positive divisor $x$ of $A_i$ that is not $A_i$ itself, and replace $A_i$ with $x$.

The player who cannot perform the operation loses, and the other player wins. Determine who wins assuming both players play optimally for victory.

## 题解
本题我们一眼丁真，鉴定为抄 CF 炒的，我们直接使用一个 SG 函数来进行计算打表，**但是，我们注意到**，因为我们的值域比较小，所以我们甚至可以进行 $o(n\sqrt{ n })$ 的算法，我们于是就可以直接利用我们的 $sg$ 函数打表通过本题：
```cpp
#include <bits/stdc++.h>

#define int long long

#define endl '\n'

int INF=0x3f3f3f3f3f3f3f3f;

using namespace std;

typedef pair<int,int> PII;

unordered_map<int,int> sg;

  

int dfs(int u){

    if(sg.count(u)){

        return sg[u];

    }

    set<int> st;

    for(int i=1;i*i<=u;i++){

        if(u%i==0&&i!=u){

            st.insert(dfs(i));

            if(i!=(u/i)&&(u/i)!=u){

                st.insert(dfs(u/i));

            }

        }

    }

    for(int i=0;;i++){

        if(st.count(i)==false){

            return sg[u]=i;

        }

    }

}

void solve(){

    int n;

    cin>>n;

//    vector<int> a(n);

  //  int tmp=0;

    auto deprime=[&](int u){

        int cnt=0;

        for(int i=2;i*i<=u;i++){

            while(u&&u%i==0){

                cnt++;

                u/=i;

            }

        }

        return cnt;

    };

    vector<int> a(n);

    for(int i=0;i<n;i++){

        cin>>a[i];

    }

    const int maxx_=*(max_element(begin(a),end(a)));

    for(int i=1;i<=maxx_;i++){

        dfs(i);

    }

    int ans=0;

    for(int i=0;i<n;i++){

        ans^=sg[a[i]];

    }

    if(ans==0){

        cout<<"Bruno"<<endl;

    }else{

        cout<<"Anna"<<endl;

    }

//    cout<<ans<<endl;

}

signed main(){

    ios::sync_with_stdio(false),cin.tie(0);

    int t;

    t=1;

 //   cin>>t;

//    init();

    while(t--){

        solve();

    }

}
```