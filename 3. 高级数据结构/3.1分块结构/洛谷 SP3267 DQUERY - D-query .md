# DQUERY - D-query

## 题面翻译

给出一个长度为n 的数列，$a_{1}$​ ,$a_{2}$​ ,...,$a_{n}$ ，有q 个询问，每个询问给出数对$(i,j)$，需要你给出$a_{i}$​ ，$a_{i+1}$​ ，...，$a_{j}$​ 这一段中有多少不同的数字

## 题目描述

[English](/problems/DQUERY/en/) [Vietnamese](/problems/DQUERY/vn/)Given a sequence of n numbers a $ _{1} $ , a $ _{2} $ , ..., a $ _{n} $ and a number of d-queries. A d-query is a pair (i, j) (1 ≤ i ≤ j ≤ n). For each d-query (i, j), you have to return the number of distinct elements in the subsequence a $ _{i} $ , a $ _{i+1} $ , ..., a $ _{j} $ .

## 输入格式

- Line 1: n (1 ≤ n ≤ 30000).
- Line 2: n numbers a $ _{1} $ , a $ _{2} $ , ..., a $ _{n} $ (1 ≤ a $ _{i} $ ≤ 10 $ ^{6} $ ).
- Line 3: q (1 ≤ q ≤ 200000), the number of d-queries.
- In the next q lines, each line contains 2 numbers i, j representing a d-query (1 ≤ i ≤ j ≤ n).

## 输出格式

- For each d-query (i, j), print the number of distinct elements in the subsequence a $ _{i} $ , a $ _{i+1} $ , ..., a $ _{j} $ in a single line.

## 样例 #1

### 样例输入 #1

```
5
1 1 2 1 3
3
1 5
2 4
3 5
```

### 样例输出 #1

```
3
2
3
```

## 思路
莫队板子题，开一个col数组统计出现的数字

## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f3f3f3f3f
#define L(i, j, k, len) for(int i = (j); i < (k); i+=(len))
#define R(i, j, k, len) for(int i = (j); i > (k); i-=(len))
#define all(x) (x).begin(),(x).end()
#define allp(x,n) (x).begin()+(n),(x).end()
#define ms(x,y) memset(x,y,sizeof(x))
#define dbg(x) cerr<<__LINE__<<" | "<<#x<<" = "<<x<<"\n"
#define dbgl(i,x) cerr<<__LINE__<<" ["<<#i<<"]: "<<i<<" -> { "<<#x<<" = "<<x<<" }\n"
#define ok cerr<<"ok"<<"\n"
#define YES cout<<"YES"<<"\n"
#define NO  cout<<"NO"<<"\n"
#define Yes cout<<"Yes"<<"\n"
#define No  cout<<"No"<<"\n"

#ifdef KROWFEATHER
    #include<bits/KrowFeather.h>
#endif
#define int long long
using ull = unsigned long long;                                                                              
using ll = long long;
using pii = pair<int,int>;
using psi = pair<string,int>;
constexpr ll MOD = 1e9+7;
//-------------------------------------------------------->>>>>>>>>>
struct Q{
    int l,r,id;
};

inline void solve(){
    int n;
    cin>>n;
    vector<int> a(n+1,0);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    vector<int> pos(n+1,0);
    int siz = sqrt(n);
    for(int i=1;i<=n;i++){
        pos[i]=i/siz;
    }
    int m;
    cin>>m;
    vector<Q> query(m); 
    for(int i=0;i<m;i++){
        int l,r;
        cin>>l>>r;
        query[i]={l,r,i};
    }
    sort(query.begin(),query.end(),[&](Q a,Q b){
        return pos[a.l]==pos[b.l]?a.r<b.r:pos[a.l]<pos[b.l];
    });
    int l=1,r=0;
    int res=0;
    vector<int> col(1e6+10);
    auto add = [&](int x){
        if(col[a[x]]==0){
            res++;
        }
        col[a[x]]++;
    };
    auto del = [&](int x){
        col[a[x]]--;
        if(col[a[x]]==0){
            res--;
        }
    }; 
    vector<int> ans(m,0);
    for(int i=0;i<m;i++){
        auto [ql,qr,id] = query[i];
        while(ql<l) add(--l);
        while(qr>r) add(++r);
        while(ql>l) del(l++);
        while(qr<r) del(r--);
        ans[id]=res;
    }
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<"\n";
    }
}
inline void prework(){
    
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    cout<<fixed<<setprecision(12);
    prework();
    int T=1; 
    // cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
```