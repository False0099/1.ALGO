#include<bits/stdc++.h>
using namespace std;
const int N = 100010;
int dp[N], w[N], v[N];
int main(){
    int n,m;
    for(int i=1;i<=n;i++){
        for(int j=w[i];j<=m;j++){
            dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
        }
    }
}