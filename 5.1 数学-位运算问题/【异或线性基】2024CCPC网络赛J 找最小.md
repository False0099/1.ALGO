## 题意：
Mandy 发现了两个很好玩的长度为 $n$ 的序列，记为 $a,b$,她觉得一个序列的无趣度为序列内所有元素的
异或和。
现在她想要这两个序列尽可能有趣，具体来说，她希望最无趣的序列尽可能有趣。她觉得交换两个序列
中对应位置的元素是无伤大雅的，可以讲行任意次这样的操作。
现在她想要知道，最有趣的情况下两个序列无趣度较大者的无趣度是多少呢？
形式化地来说，你有两个长度为 $n$ 的序列 $a,b$,你可以进行若干次选择一个 $i\left(1\leq i\leq n\right)$,然后交换
$a_i,b_i$,希望使得 $\max\{f(a),f(b)\}$ 最小，其中对于一个序列 $A,f(A)=\oplus_i=1^nA_i$ ($\oplus$ 表示按位异或)。

## 题解：
本题，我们要求我们的**最大值最小**，并且我们的两者的异或和是固定的，我们有一个经典的 trick，我们对于**抑或序列进行一次交换**等价于我们的两边的异或和都去抑或上我们的 $a[i]\oplus b[i]$。

这样，我们就可以对我们的每一个 $i$，构成的所有数字，构成一个**线性基**，那么我们的最大化最小值，就可以通过我们的简单的，轻松的，不复杂的按位贪心来进行处理，每一次我们对于每一个线性基上的一位，我们看这一位是否是可行的，如果是，我们就进行对应的处理。

```
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
const int N=66;
int d[N];
void insert(int x){
    for(int i=62;i>=0;i--){
        if((x>>i)&1){
            if(d[i]){
                x^=d[i];
            }else{
                d[i]=x;
                break;
            }
        }
    }
}
void solve(){
    int n;
    cin>>n;
    vector<int> a(n+1);
    vector<int> b(n+1);
    for(int i=62;i>=0;i--){
        d[i]=0;
    }   
    int x1=0;
    int x2=0;
    for(int i=0;i<n;i++){
        cin>>a[i];
        x1^=a[i];
    }
    for(int i=0;i<n;i++){
        cin>>b[i];
        x2^=b[i];
        insert(a[i]^b[i]);
    }
    int tmp=max(x1,x2);
    for(int i=62;i>=0;i--){
        if(max(x1,x2)>max(x1^d[i],x2^d[i])){
            x1^=d[i];
            x2^=d[i];
        }
//        tmp=min(max(x1,x2),max(x1^d[i],x2^d[i]));
    }
    cout<<max(x1,x2)<<endl;
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