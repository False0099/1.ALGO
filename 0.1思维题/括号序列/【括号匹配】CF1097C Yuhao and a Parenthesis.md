# Yuhao and a Parenthesis

## 题面翻译

有 $n$ 组不一定合法的括号序列，要使这 $n$ 个括号序列两两配对，成为合法括号序列。求最多能配对出多少对。

### 数据范围

- $1\leq n \leq 10^5$
- 所有括号序列的长度之和不超过 $5\cdot 10^5$。

## 题目描述

One day, Yuhao came across a problem about checking if some bracket sequences are correct bracket sequences.

A bracket sequence is any non-empty sequence of opening and closing parentheses. A bracket sequence is called a correct bracket sequence if it's possible to obtain a correct arithmetic expression by inserting characters "+" and "1" into this sequence. For example, the sequences " (())()", " ()" and " (()(()))" are correct, while the bracket sequences ")(", " (()" and " (()))(" are not correct.

Yuhao found this problem too simple for him so he decided to make the problem harder. You are given many (not necessarily correct) bracket sequences. The task is to connect some of them into ordered pairs so that each bracket sequence occurs in at most one pair and the concatenation of the bracket sequences in each pair is a correct bracket sequence. The goal is to create as many pairs as possible.

This problem unfortunately turned out to be too difficult for Yuhao. Can you help him and solve it?

## 输入格式

The first line contains one integer $ n $ ( $ 1 \leq n \leq 10^5 $ ) — the number of bracket sequences.

Each of the following $ n $ lines contains one bracket sequence — a non-empty string which consists only of characters " (" and ")".

The sum of lengths of all bracket sequences in the input is at most $ 5 \cdot 10^5 $ .

Note that a bracket sequence may appear in the input multiple times. In this case, you can use each copy of the sequence separately. Also note that the order in which strings appear in the input doesn't matter.

## 输出格式

Print a single integer — the maximum number of pairs which can be made, adhering to the conditions in the statement.

## 样例 #1

### 样例输入 #1

```
7
)())
)
((
((
(
)
)
```

### 样例输出 #1

```
2
```

## 样例 #2

### 样例输入 #2

```
4
(
((
(((
(())
```

### 样例输出 #2

```
0
```

## 样例 #3

### 样例输入 #3

```
2
(())
()
```

### 样例输出 #3

```
1
```

## 提示

In the first example, it's optimal to construct two pairs: " (( )())" and " ( )".

## 题解
我们这一题就是要利用我们的一个括号序列与正负一之间的转换来进行我们的操作，我们对于每一个括号，我们都要找到一个与他相加为 0 的那个序列，最后找到的就是我们的答案。

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(ll i=a;i<=b;i++)
using namespace std;
typedef long long ll;
ll n;
string s[100005];
ll checkL(string s){
    ll ans=0;
    for(auto i:s){
        if(i=='(')ans++;
        else ans--;
        if(ans<0)return -1;
    }
    return ans;
}
ll checkR(string s){
    ll ans=0;
    for(ll i=s.size()-1;i>=0;i--){
        if(s[i]==')')ans++;
        else ans--;
        if(ans<0)return -1;
    }
    return ans;
}
map<ll,ll>L,R;
ll M=0;
int main(){
    cin>>n;
    rep(i,1,n){
        cin>>s[i];
        ll l=checkL(s[i]),r=checkR(s[i]);
        if(l==0)M++;
        else if(l>0)L[l]++;
        else if(r>0)R[r]++;
    }
    ll ans=0;
    for(auto it=L.begin();it!=L.end();it++){
        ll l=it->first;
        ans+=min(L[l],R[l]);
    }
    ans+=M/2;
    cout<<ans<<endl;
    return 0;
}
```