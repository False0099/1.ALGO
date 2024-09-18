#include<bits/stdc++.h>
using namespace std;
int dp[1010];
int w[10005],v[10005],c[10005];
int cnt,co[1000005],V[1000005];
inline void solve(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>w[i]>>v[i]>>c[i];
    }
    auto pre = [&](){
        for(int i=1;i<=n;i++) {
            int t=1;
            while(c[i]) {
                co[++cnt]=t*w[i];
                V[cnt]=t*v[i];
                c[i]-=t; t*=2;
                if(c[i]<t) {
                    co[++cnt]=w[i]*c[i];
                    V[cnt]=v[i]*c[i];
                    break;
                }
            }
        }        
    };
    pre();
    for(int i=1;i<=cnt;i++){
        for(int j=m;j>=co[i];j--){
            dp[j]=max(dp[j],dp[j-co[i]]+V[i]);
        }
    }
    cout<<dp[m]<<"\n";
}