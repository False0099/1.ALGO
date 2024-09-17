You accidentally sprained your ankle, and now you are facing a long recovery phase. Initially, you are at stage 0, and your recovery progresses until you reach stage n.

Each day, if you rest properly, you advance by exactly one stage. So it takes n days for you to recover, that is, if you do not do anything improper.

However, instead of resting, you have the option to challenge yourself, which also takes one day. If you are at stage i and succeed, you will instantly recover. However, if you fail, you will regress to stage ai​ (0≤ai​≤i). The probability of success is pi​.

Now, you are wondering what the **expected time** required for your recovery would be, assuming you adopt the best strategy.

### Input

The first line contains a positive integer T (1≤T≤104), denoting the number of test cases.

For each test case:

- The first line contains one integer n (1≤n≤5×105), denoting the number of stages of recovery.
- The next line contains n integers a0​,a1​,⋯,an−1​ (0≤ai​≤i), denoting the stage you will go back to if you fail at stage i.
- The next line contains n integers q0​,q1​,⋯,qn−1​ (0≤qi​≤105), where pi​=qi​/105 denotes the probability of success at stage i.

It is guaranteed that ∑n≤5×105.

### Output

For each test case, print one decimal number, denoting the expected time needed for you to recover if you take the best strategy. The answer will be considered correct if its absolute or relative error is less than 10−9.

### Sample Input

```in
5
1
0
0
3
0 1 2
99999 0 0
3
0 1 2
0 50001 100000
5
0 1 2 0 1
21735 25194 37976 89936 99999
8
0 0 2 2 4 3 4 1
12839 27084 17777 35472 31951 64686 96898 0
```

### Sample Output

```out
1.000000000000
1.000010000100
2.999960000800
4.447607187333
7.096039133935
```


## 题解
我们这一题就是为我们从起点出发到达终点的期望值，如果我们存在一个可以挑战的最佳状态 i，那么我们挑战失败后也会等状态恢复到 i 再次挑战，直到挑战呈贡，那么我们就可以枚举哪一个状态是最优的。
如果状态 i 是最优的状态，那么他的期望就是到达这个状态需要的时间 i，以及挑战成功的期望次数-1 乘回复状态需要的天数。
```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=l;i<=r;i++)
#define all(x) (x).begin(),(x).end()
#define show(x) {for(auto it:x) cout<<it<<" ";cout<<endl;}
typedef long long ll;

void sol(){

    int n;cin>>n;
    vector<int> a(n+1);
    double ans=n;
    rep(i,1,n) cin>>a[i];
    rep(i,1,n){
        double now=i;
        int p;scanf("%d",&p);
        if(!p) continue;
        double q=p/1e5;
        now=i+(1/q-1)*(i-a[i]);
        ans=min(ans,now);
    }

    printf("%.12f\n",ans);

    
}

int main(){
    #ifdef LOCAL
        freopen("C:\\Users\\Administrator\\Desktop\\code1\\zz.in","r",stdin);
        freopen("C:\\Users\\Administrator\\Desktop\\code1\\zz.out","w",stdout);
    #endif

    int t;cin>>t;
    while(t--){
        sol();
    }

}
```