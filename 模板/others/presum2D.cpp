#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> a(n+1,vector<int>(m+1,0));
    vector<vector<int>> pre(n+1,vector<int>(m+1,0));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
            pre[i][j]=pre[i][j-1]+pre[i-1][j]-pre[i-1][j-1]+a[i][j];
        }
    }
    int maxn=-0x3f3f3f3f;
    // k<->i r<->j wid=k-i+1 hei=r-j+1
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int k=i;k<=n;k++){
                for(int r=j;r<=m;r++){
                    maxn=max(maxn,pre[k][r]-pre[k][j-1]-pre[i-1][r]+pre[i-1][j-1]);
                }
            }
        }
    }
}