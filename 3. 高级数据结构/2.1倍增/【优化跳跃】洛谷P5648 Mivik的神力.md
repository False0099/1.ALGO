# Mivik 的神力

## 题目背景

$\textcolor{black}{\text{M}} \textcolor{red}{\text{ivik}}$ 发怒了，机房的 $\textcolor{grey}{\text{deco}}$ 瑟瑟发抖

## 题目描述

$\textcolor{black}{\text{M}} \textcolor{red}{\text{ivik}}$ 要写一篇文章，在写文章时，他有 $n$ 个备选的单词，第 $i$ 个单词有一个长度 $a_i$，$\textcolor{black}{\text{M}} \textcolor{red}{\text{ivik}}$ 可以选择从第 $i$ 个单词开始写作，一共写 $k$ 秒，第 $j$ 秒会写上第 $i+j-1(j\in[1,k])$ 个单词，并且他在写作时每秒都会获得愉悦值，第 $j$ 秒的愉悦值为 $max_{l=i}^{i+j-1} a_l$，现在，请你帮他算出，他每一次写作获得的愉悦值之和

**一句话题意：给出一个序列和多组询问 $(l,q)$ ，求**

$$
\sum_{i=l}^{l+q-1} \max_{l\le j\le i}a_j
$$

**数据要求强制在线**

## 输入格式

第一行，两个数，$n$，$t$，代表词汇个数和问题个数

第二行，$n$ 个数，第 $i$ 个数代表 $a_i$

接下来 $t$ 行，每行两个数，$u$，$v$，$l=1+(u ⊕ lastans)\%n$，$q=1+(v ⊕ (lastans+1))\%(n-l+1)$，代表查询从第 $l$ 秒开始，写作 $q$ 秒的愉悦度之和

$lastans$ 表示上一次查询的答案，初始 $lastans$ 为 $0$

## 输出格式

对于每个询问，回答一行，代表答案

## 样例 #1

### 样例输入 #1

```
3 2
1 2 3
1 1
1 2
```

### 样例输出 #1

```
2
3
```

## 提示

**样例解释**

第一个询问 $1,1$，解密后得到 $l=2,q=1$ ，则按题意可得所求即为区间 $[2,2]$ 的最大值，为 $2$

第一个询问 $1,2$ ，解密后得到 $l=1,q=2$ ，则所求即为区间 $[1,1]$ 和区间 $[1,2]$ 的最大值之和，为 $3$

-----

对于 $20\%$ 的数据，$n \leq 1000$，$t \leq 1000$

对于 $100\%$ 的数据，$n\leq 500000$，$t\leq 500000$，$1 \leq a_i\leq 10^9(i\in [1,n])$

## 题解
本题，我们可以通过简单的处理来得到我们的答案：首先我们的原文，我们转换为人话就是要求：$max(l,l)+max(l,l+1)+\dots+max(l,l+q-1)$，

对于我们的这一种区间固定某一个端点求最大值，我们可以通过我们的分段来进行，我们对于每一个元素，记录**下一个比它大的数在哪里**。然后我们的这一个数字的贡献就是：$a[i]*(r-i+1)$。这个时候，为了优化，我们可以采用我们的**倍增来进行处理**。

我们记我们的 $f[i][j]$ 表示从 $j$ 点开始，我们跳了 $2^{i}$ 步后，我们的结束位置在哪里。那么我们从大到小枚举我们的 j，能跳就跳，把答案加在一起即可。
```
```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f;
using namespace std;
const int N=500010;
typedef pair<int,int> PII;
PII st[N][32];
int lg[N];
int next_num[N];
int sum[N];
int last[N];
void init(){
    
}
PII query(int l,int r){
    int len=lg[r-l+1];
    auto u=st[l][len];
    auto v=st[r-(1ll<<len)+1][len];
    if(u.first>=v.first){
        return u;
    }else{
        return v;
    }
}
void solve(){
   int n,m;
   cin>>n>>m;
   vector<int> a(n+1);
   lg[1]=0;
   for(int i=1;i<=n;i++){
        cin>>a[i];
        st[i][0]={a[i],i};
   }
   stack<int> stk;
   for(int i=n;i>=1;i--){
        while(stk.size()&&a[stk.top()]<=a[i]){
            stk.pop();
        }
        if(stk.size()){
            next_num[i]=stk.top();
        }else{
            next_num[i]=n+1;
        }
        stk.push(i);
   }
   for(int i=n;i>=1;i--){
        sum[i]=sum[next_num[i]]+(next_num[i]-i)*a[i];
   }
   for(int i=2;i<=n;i++){
        lg[i]=lg[i>>1]+1;
   }
   for(int k=1;k<=lg[n];k++){
        for(int i=1;i+(1ll<<k)-1<=n;i++){
            auto u=st[i][k-1];
            auto v=st[i+(1ll<<k-1)][k-1];
            if(u.first>=v.first){
                st[i][k]=u;
            }else{
                st[i][k]=v;
            }
        }
   }
   int lastans=0;
   for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        int l=1+(u^lastans)%n;
        int q=1+(v^(lastans+1))%(n-l+1);
        int r=l+q-1;
       // cerr<<l<<" "<<q<<endl;
        int max_pos=query(l,r).second;
        //cerr<<max_pos<<endl;
        lastans=sum[l]-sum[max_pos]+a[max_pos]*(r-max_pos+1);
        cout<<sum[l]-sum[max_pos]+a[max_pos]*(r-max_pos+1)<<endl;
   }
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
 //   cin>>t;
    init();
    while(t--){
        solve();
    }
}
```
```