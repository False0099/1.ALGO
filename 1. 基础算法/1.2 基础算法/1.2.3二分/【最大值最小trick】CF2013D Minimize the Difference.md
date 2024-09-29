## 题意；
省流：
给你一个序列，每一次你可以让 $a[i]+1,a[i+1]-1$,问你无限操作后我们的极差最小是多少。
Zhan, tired after the contest, gave the only task that he did not solve during the contest to his friend, Sungat. However, he could not solve it either, so we ask you to try to solve this problem.

You are given an array $a_1, a_2, \ldots, a_n$ of length $n$. We can perform any number (possibly, zero) of operations on the array.

In one operation, we choose a position $i$ ($1 \leq i \leq n - 1$) and perform the following action:

-   $a_i := a_i - 1$, and $a_{i+1} := a_{i+1} + 1$.

Find the minimum possible value of $\max(a_1, a_2, \ldots, a_n) - \min(a_1, a_2, \ldots, a_n)$.

**Input**

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^5$). The description of the test cases follows.

The first line of each test case contains an integer $n$ ($1 \leq n \leq 2 \cdot 10^5$).

The second line of each test case contains $n$ integers $a_1, a_2, \ldots, a_n$ ($1 \leq a_i \leq 10^{12}$).

The sum of $n$ over all test cases does not exceed $2 \cdot 10^5$.

**Output**

For each test case, output a single integer: the minimum possible value of $\max(a_1, a_2, \ldots, a_n) - \min(a_1, a_2, \ldots, a_n)$.

## 题解
本题，我们首先发现，我们的这一个操作，一定可以让我们的**总和不变**，同时，我们还可以注意到，如果我们的总和是不变的。

那么我们的一个显然的思路是，先把我们的所有元素都分配到我们的最右端，然后再通过我们的几次分配，来得到我们的答案，我们这个时候显然可以发现，如果我们给我们的左侧分配的尽可能的多，我们最后的极差也会尽可能的更小。于是，我们就可以**二分我们的最小值最大是多少**。

在 check 的时候，我们只需要 check 我们的**前缀和是不是满足我们的对应的哟球**。

在我们确定了我们的最小值最大是多少后，**我们还可以要求我们的最大值最小是多少**。同样的，我们也可以通过我们的二分来解决我们的上面的问题。

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
    int sum=0;
    vector<int> pref(n+1,0);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        pref[i]=pref[i-1]+a[i];
        sum+=a[i];
    }   
    int l=0,r=INF;
    auto check=[&](int mid){
        int maxx=sum-mid*(n-1);
        int minn=mid;
        if(maxx<0){
            return false;
        }
        if(maxx<minn){
            return false;
        }
        int pref_sum_now=0;
        for(int i=1;i<=n;i++){
            if(pref[i]<pref_sum_now+minn){
                return false;
            }
            pref_sum_now+=minn;
        }
        return true;
    };
    while(l<r){
        int mid=l+r>>1;
        //cerr<<l<<" "<<r<<" "<<mid<<endl;
        if(check(mid)){
            l=mid+1;
        }else{
            r=mid;
        }
    }
    //二分最小值最大是多少？
    int ans=INF;
    auto calc=[&](int mid){
       //mid表示我们的最小值是多少
       vector<int> b(n+1);
       vector<int> sumb(n+1);
       int maxl=mid,maxr=INF;
       auto check2=[&](int mid2){
            b[n]=mid2;
            b[1]=mid;
            int pref_sum_check2=b[1];
            for(int i=2;i<n;i++){
                pref_sum_check2=min(pref_sum_check2+mid2,pref[i]);
//                pref_sum_check2+=min(mid2,pref[i]-pref[i-1]);
            }
            if(pref_sum_check2+mid2>=pref[n]){
                return true;
            }else{
                return false;
            }
       };
       while(maxl<maxr){
            int maxmid=maxl+maxr>>1;
            if(check2(maxmid)){
                maxr=maxmid;
            }else{
                maxl=maxmid+1;
            }
       }
       //二分我们的最大值最小是多少

       return maxl-mid;
    };
    //cerr<<l-1<<endl;
    for(int dx=0;dx<=2;dx++){

        if(check(l+dx)==1){
            ans=min(ans,calc(l+dx));
        }
        if(check(l-dx)==1){
            ans=min(ans,calc(l-dx));
        }
    }
    //cout<<calc(1)<<endl;
    //cerr<<sum-n<<endl;
    //cerr<<check(1)<<endl;
//    cerr<<l<<endl;
  //  cout<<(sum-l*(n-1)-l)<<endl;
    cout<<ans<<endl;
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