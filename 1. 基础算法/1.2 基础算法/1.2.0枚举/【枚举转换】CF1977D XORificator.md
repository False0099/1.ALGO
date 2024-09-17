# XORificator

## 题目描述

You are given a binary (consisting only of 0 s and 1 s) $ n \times m $ matrix. You are also given a XORificator, using which you can invert all the values in a chosen row (i.e. replace 0 with 1 and 1 with 0).

A column in the matrix is considered special if it contains exactly one 1. Your task is to find the maximum number of columns that can be made special at the same time, and the set of rows the XORificator should be used on to achieve that.

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \leq n, m \leq 3 \cdot 10^5 $ , $ n \cdot m \leq 3 \cdot 10^5 $ ).

Each of the following $ n $ lines of the test case contains a binary string of length $ m $ .

It is guaranteed that the sum of $ n \cdot m $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output two lines.

In the first line, output the maximum number of special columns that is possible to get simultaneously.

In the second line, output a binary string of length $ n $ , where the $ i $ -th character is 0, if you don't use the XORificator on the $ i $ -th row, and 1, if you use the XORificator on the $ i $ -th row.

If there are multiple valid XORificator configurations that achieve the optimal answer, you can output any of them.

## 样例 #1

### 样例输入 #1

```
5
3 4
1010
0110
0100
1 1
1
1 1
0
2 5
00101
10110
3 3
101
111
000
```

### 样例输出 #1

```
3
010
1
0
1
1
3
00
2
010
```

## 提示

In the first test case, you can use the XORificator on the second row to make the columns $ 2 $ , $ 3 $ , and $ 4 $ special.

In the second test case, the only column is already special, so you don't need to use the XORificator.

## 题解
我们本题不难发现，我们如果**固定了某一行某一列的某一个元素为 1**，那么我们的操作一定是**唯一的**。

那么，我们就可以枚举我们把哪一行，哪一列设置为我们的 1，然后让这一种操作对答案的贡献++，最后，我们只需要统计我们的每一个操作最后的最大贡献是多少，然后我们再去计算出我们的这一个操作方法的最终答案。

最后，我们就能够得到我们的结果：
```
#include<bits/stdc++.h>
#define ll long long
#define ul unsigned long long
#define N 300005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
ll P4=131,xn4[N];
ll P5=97,xn5[N];
const ll mod2=1145141;//
const ll mod3=19260817;//质数生日！
ll st,ed;
struct Hash{
    ul x1,x2;
    ll x4,x5;
    //自然溢出日常被叉，所以多写了点。
    friend bool operator==(const Hash &a,const Hash &b){
        return a.x1==b.x1&&a.x2==b.x2&&a.x4==b.x4&&a.x5==b.x5;
    }   
    friend Hash operator+(const Hash &a,const Hash &b){
        return {a.x1+b.x1,a.x2^b.x2,(a.x4+b.x4)%mod2,(a.x5+b.x5)%mod3};
    }   
    friend Hash operator-(const Hash &a,const Hash &b){
        return {a.x1-b.x1,a.x2^b.x2,(a.x4-b.x4+mod2+mod2)%mod2,(a.x5-b.x5+mod3+mod3)%mod3};
    }   
    friend bool operator<(const Hash &a,const Hash &b){
        if(a.x1!=b.x1)return a.x1<b.x1;
        if(a.x2!=b.x2)return a.x2<b.x2;
        if(a.x4!=b.x4)return a.x4<b.x4;
        return a.x5<b.x5;
    }
}h[N],res;
map<Hash,ll>mp;
string ans;
ll n,m;
void sol(){
    mp.clear();
    cin>>n>>m;
    res={0,0,-1,-1};
    string s="\n";//习惯下标从 1 开始，正常输出会 0 的位置，所以把0换成换行，后续就不需要换行；
    ans="\n";
    vector<string>v(n+2);//放置炸，用vector
    for(int i=1;i<=n;i++){
        s+='0';
        cin>>v[i];
        v[i]=" "+v[i];
    }
    mp[res]=-1;
    for(int j=1;j<=m;j++){
        Hash now={0,0,0,0};
        for(int i=1;i<=n;i++){
            s[i]='0';//先将该列所有位置翻转成0
            ///后续只需要每次更改一位即可。
            if(v[i][j]-'0'==1)now=now+h[i],s[i]='1';
        }
        for(int i=1;i<=n;i++){
            if(v[i][j]-'0'==0)now=now+h[i],s[i]='1';
            if(v[i][j]-'0'==1)now=now-h[i],s[i]='0';
            mp[now]++;
            if(mp[res]<mp[now]){//写等于会提埃奥义
                res=now;
                ans=s;
            }
            if(v[i][j]-'0'==0)now=now-h[i],s[i]='0';
            if(v[i][j]-'0'==1)now=now+h[i],s[i]='1';
        }
    }
    cout<<mp[res]<<ans<<endl;
}
int main(){
    xn4[0]=xn5[0]=1;
    for(int i=1;i<=N-3;i++){
        xn4[i]=xn4[i-1]*P4%mod2;
        xn5[i]=xn5[i-1]*P5%mod3;
        ul x1=xn4[i]*xn5[i];
        ul x2=xn4[i]^xn5[i];
        h[i]={x1,x2,xn4[i],xn5[i]};
    }
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();
    return 0;
}
```