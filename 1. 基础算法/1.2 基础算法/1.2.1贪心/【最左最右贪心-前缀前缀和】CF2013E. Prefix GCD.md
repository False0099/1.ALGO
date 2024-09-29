## 题意：
省流：给你一个数组 a，要求你对这个数组进行排列，要求排列后的前缀 gcd 和最小（前缀 gcd 和的定义见下面的表达式）


Since Mansur is tired of making legends, there will be no legends for this task.

You are given an array of positive integer numbers $a_1, a_2, \ldots, a_n$. The elements of the array can be rearranged in any order. You need to find the smallest possible value of the expression

$$
\gcd(a_1) + \gcd(a_1, a_2) + \ldots + \gcd(a_1, a_2, \ldots, a_n),
$$
 where $\gcd(a_1, a_2, \ldots, a_n)$ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of $a_1, a_2, \ldots, a_n$.

## 题解
本题，我们注意到，我们要求我们的**前缀和的和**，这个就按时我们**交换贪心**，我们考虑**每一步都取到我们的相对最小的**，这样一定能够取到我们的最优结果。这一步是因为，我们任意交换 $i,i+1$ 影响的因素都是**有限的**。

因此，我们就可以通过我们的 gcd 来进行对应的处理，我们首先枚举我们的 $i$ 对应的一个 $j$，是的我们的 $gcd(i,j)$ 是最小的，然后重复上述步骤，知道我们的 $gcd(i,j)$ 为 $gcd(all)$。

我们这么做时间复杂度由于 gcd 的性质，我们的最终结果不会超过 $o(n\log n)$（我也不会证，很玄学）

```
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
void solve(){
    int n;
    cin>>n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(begin(a)+1,end(a));
    int res_g=0;
    for(int i=1;i<=n;i++){
        res_g=__gcd(res_g,a[i]);
    }
    int now_g=0;
    vector<int> res(n+1,0);
    for(int i=1;i<=n;i++){
        int min_g=INF;
        int idx=i;
        for(int j=i;j<=n;j++){
            int tmo=__gcd(now_g,a[j]);
            if(tmo<min_g){
                min_g=tmo;
                idx=j;
            }
        }
        swap(a[i],a[idx]);
        if(min_g==res_g){
            for(int j=i;j<=n;j++){
                res[j]=res_g;
            }
            break;
        }
        res[i]=min_g;
        now_g=min_g;
        //cerr<<res[i]<<" "<<endl;
    }
    int tot=0;
    for(int i=1;i<=n;i++){
        tot+=res[i];
    }
    cout<<tot<<endl;
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
