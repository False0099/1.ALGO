# Compress Words

## 题面翻译

Amugae 有 $n$ 个单词，他想把这个 $n$ 个单词变成一个句子，具体来说就是从左到右依次把两个单词合并成一个单词。合并两个单词的时候，要找到最大的 $i(i\ge 0)$，满足第一个单词的长度为 $i$ 的后缀和第二个单词长度为 $i$ 的前缀相等，然后把第二个单词第 $i$ 位以后的部分接到第一个单词后面。输出最后那个单词。

注：题中的字符串存在大小写字母和数字。

## 题目描述

Amugae has a sentence consisting of $ n $ words. He want to compress this sentence into one word. Amugae doesn't like repetitions, so when he merges two words into one word, he removes the longest prefix of the second word that coincides with a suffix of the first word. For example, he merges "sample" and "please" into "samplease".

Amugae will merge his sentence left to right (i.e. first merge the first two words, then merge the result with the third word and so on). Write a program that prints the compressed word after the merging process ends.

## 输入格式

The first line contains an integer $ n $ ( $ 1 \le n \le 10^5 $ ), the number of the words in Amugae's sentence.

The second line contains $ n $ words separated by single space. Each words is non-empty and consists of uppercase and lowercase English letters and digits ('A', 'B', ..., 'Z', 'a', 'b', ..., 'z', '0', '1', ..., '9'). The total length of the words does not exceed $ 10^6 $ .

## 输出格式

In the only line output the compressed word after the merging process ends as described in the problem.

## 样例 #1

### 样例输入 #1

```
5
I want to order pizza
```

### 样例输出 #1

```
Iwantorderpizza
```

## 样例 #2

### 样例输入 #2

```
5
sample please ease in out
```

### 样例输出 #2

```
sampleaseinout
```

## 题解
本题，我们的想法很简答，我们**二分公共长度是多少**，然后我们再用 hash 分别取检验我们的这一个能否取到，但是，这我们需要主义的一点是，我们每一次合并压缩后，我们的最终结果的**新的字符串**需要在后面**添加新元素**，并且维护**新的字符串的 DP**，这一个需求其实显然我们可以通过**魔改我们的 Hash 模板来实现**。于是现在我们就变成了一个简单题。

```
#include <bits/stdc++.h>

using namespace std;
#define IOS ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
#define int long long


std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

bool isprime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}

int findPrime(int n) {
    while (!isprime(n))
        n++;
    return n;
}

template<int N>
struct StringHash {
    static array<int, N> mod;
    static array<int, N> base;
    vector<array<int, N>> p, h;

    StringHash() = default;

    StringHash(const string &s) {
        int n = s.size();
        p.resize(n);
        h.resize(n);
        fill(p[0].begin(), p[0].end(), 1);
        fill(h[0].begin(), h[0].end(), 1);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < N; j++) {
                p[i][j] = 1ll * (i == 0 ? 1ll : p[i - 1][j]) * base[j] % mod[j];
                h[i][j] = (1ll * (i == 0 ? 0ll : h[i - 1][j]) * base[j] + s[i]) % mod[j];
            }
    }
    void add(char s){
        int n=p.size();
        p.resize(n+1);
        h.resize(n+1);
        for(int j=0;j<N;j++){
            p[n][j]=1ll * (n == 0 ? 1ll : p[n - 1][j]) * base[j] % mod[j];
            h[n][j]=(1ll * (n == 0 ? 0ll : h[n - 1][j]) * base[j] + s) % mod[j];
        }
    }
    array<int, N> query(int l, int r) {
        assert(r >= l - 1);
        array<int, N> ans{};
        if (l > r) return {0, 0};
        for (int i = 0; i < N; i++) {
            ans[i] = (h[r][i] - 1ll * (l == 0 ? 0ll : h[l - 1][i]) * (r - l + 1 == 0 ? 1ll : p[r - l][i]) % mod[i] +
                      mod[i]) % mod[i];
        }
        return ans;
    }
};

constexpr int HN = 2;
template<>
array<int, 2> StringHash<HN>::mod =
        {findPrime(rng() % 900000000 + 100000000),
         findPrime(rng() % 900000000 + 100000000)};
template<>
array<int, 2> StringHash<HN>::base{13331, 131};
using Hashing = StringHash<HN>;

void solve() {
    int n;
    cin>>n;
    string s0;
    cin>>s0;
    Hashing ha=(s0);
    for(int i=1;i<n;i++){
        string s;
        cin>>s;
        int l=1;
        int r=min(s0.size(),s.size());
        int n=s0.size();
        //cerr<<s0.substr(n-r,r)<<" "<<s.substr(0,r)<<endl;
        //Hashing ha=(s0.substr(n-r,r));
        Hashing hb=(s.substr(0,r));
        //string pre_s0=s0;
        //string pre_s=s;
        //s0=s0.substr(n-r,r);
        //s=s.substr(0,r);
        auto check=[&](int len){
            int l1=s0.size()-len;
            int r2=len-1;
            if((ha.query(l1,s0.size()-1)==(hb.query(0,r2)))){
                return true;
            }else{
                
                return false;
            }
        };
        int res=-1;
        //cerr<<l<<" "<<r<<endl;
        
        for(int len=r;len>=l;len--){
            //cerr<<len<<" ";
            if(check(len)){
               res=len; 
//               cerr<<"update"<<endl;
               break;
            }
            //cerr<<endl;
        }
        //cout<<s[0]<<" "<<check(1)<<endl;
        //cerr<<l-1;
        //cerr<<res<<endl;
        for(int j=0;s[j];j++){
            if(j>=res){
                ha.add(s[j]);
                s0+=s[j];
            }
        }
     //   cerr<<s<<" "<<s0<<endl;
    }
    cout<<s0<<endl;
}

signed main() {
    IOS
    int t;
    t=1;
    while (t--)solve();
    return 0;
}
```