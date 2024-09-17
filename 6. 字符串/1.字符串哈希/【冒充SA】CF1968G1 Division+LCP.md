# Division + LCP (easy version)

## 题目描述

This is the easy version of the problem. In this version $ l=r $ .

You are given a string $ s $ . For a fixed $ k $ , consider a division of $ s $ into exactly $ k $ continuous substrings $ w_1,\dots, w_k $ . Let $ f_k $ be the maximal possible $ LCP (w_1,\dots, w_k) $ among all divisions.

 $ LCP (w_1,\dots, w_m) $ is the length of the Longest Common Prefix of the strings $ w_1,\dots, w_m $ .

For example, if $ s=abababcab $ and $ k=4 $ , a possible division is $ \color{red}{ab}\color{blue}{ab}\color{orange}{abc}\color{green}{ab} $ . The $ LCP (\color{red}{ab},\color{blue}{ab},\color{orange}{abc},\color{green}{ab}) $ is $ 2 $ , since $ ab $ is the Longest Common Prefix of those four strings. Note that each substring consists of a continuous segment of characters and each character belongs to exactly one substring.

Your task is to find $ f_l, f_{l+1},\dots, f_r $ . In this version $ l=r $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ , $ l $ , $ r $ ( $ 1 \le l = r \le n \le 2 \cdot 10^5 $ ) — the length of the string and the given range.

The second line of each test case contains string $ s $ of length $ n $ , all characters are lowercase English letters.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output $ r-l+1 $ values: $ f_l,\dots, f_r $ .

## 样例 #1

### 样例输入 #1

```
7
3 3 3
aba
3 3 3
aaa
7 2 2
abacaba
9 4 4
abababcab
10 1 1
codeforces
9 3 3
abafababa
5 3 3
zpozp
```

### 样例输出 #1

```
0
1
3
2
10
2
0
```

## 提示

In the first sample $ n=k $ , so the only division of $ aba $ is $ \color{red}a\color{blue}b\color{orange}a $ . The answer is zero, because those strings do not have a common prefix.

In the second sample, the only division is $ \color{red}a\color{blue}a\color{orange}a $ . Their longest common prefix is one.

## 题解
我们本题的想法是，通过我们**二分答案**来计算出我们每一个位置对应的答案可能是多少，这个时候，我们不难发现，我们的二分答案时我们的检查方法可以通过：

找到第一个和我们的前缀匹配的位置，然后再去找其他部分，看我们总共是不是能够分成 $t$ 个部分。其中，我们的比较部分可以采用哈希或者 kmp 或者其他方法都可。

```
#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define fr(m) for(int i=0; i<m; i++)
#define fro(m) for(int i=1; i<m; i++)
#define frj(m) for(int j=0; j<m; j++)
#define frr(n) for(int i=n; i>=0; i--)
#define pb push_back
#define pf push_front
#define orr ||
#define nl '\n'
#define nll cout<<'\n'
// #define mod 1000000007
#define inf (1LL<<60)
#define inff (1<<30)-1
#define yes cout<<"YES"<<nl
#define no cout<<"NO"<<nl
#define ff first
#define ss second
#define all(v) v.begin(), v.end()
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
#define mxn 200005
const ll m1=1e9+1011;

ll b1=1e9+21, b2=1e9+181, ib1=516162138, ib2=374699174;
ll p1[mxn], p2[mxn], ip1[mxn], ip2[mxn];
int n, L, R;
string s;

void getps(){
    p1[0]=p2[0]=ip1[0]=ip2[0]=1;
    fro(mxn){
        p1[i]=p1[i-1]*b1%m1;
        p2[i]=p2[i-1]*b2%m1;
        ip1[i]=ip1[i-1]*ib1%m1;
        ip2[i]=ip2[i-1]*ib2%m1;
    }
}

struct Hash{
    vector<ll>h1,h2;
    void init(string s){
        int m=s.size();
        h1.resize(m+2);
        h2.resize(m+2);
        h1[0]=h2[0]=0;
        for(int i=1; i<m; i++){
            h1[i]=(h1[i-1]+int(s[i])*p1[i-1])%m1;
            h2[i]=(h2[i-1]+int(s[i])*p2[i-1])%m1;
        }
    }
    ll forhash(int l, int r){
        ll H1=(h1[r]-h1[l-1]+m1)*ip1[l]%m1;
        ll H2=(h2[r]-h2[l-1]+m1)*ip2[l]%m1;
        return H1<<32|H2;
    }
};
//getps();
//string s;//1based
//Hash H;
//H.init(s);
//comment out mod

int main()
{
    fastio;
    getps();
    int t, cnt=1;
    cin>>t;
    while(t--){
        cin>>n>>L>>R;
        cin>>s;
        s="$"+s;
        Hash H;
        H.init(s);
        ll l=1, r=n, ans=0;
        while(l<=r){
            ll mid=(l+r)/2;
            ll hs=H.forhash(1,mid), koyta=1;
            for(int i=mid+1; i+mid-1<=n; i++){
                if(H.forhash(i,i+mid-1)==hs){
                    koyta++, i+=mid-1;
                }
            }
            if(koyta>=L){
                ans=mid, l=mid+1;
            }
            else r=mid-1;
        }
        cout<<ans<<nl;
    }
    return 0;
}
```