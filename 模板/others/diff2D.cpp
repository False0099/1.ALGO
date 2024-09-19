#include<bits/stdc++.h>
using namespace std;
const int N = 1010;
int a[N][N];
int b[N][N];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            b[i][j]=a[i][j]-a[i-1][j]-a[i][j-1]+a[i-1][j-1];
        }
    }
    while(m--){
        int sx,sy,ex,ey;
        cin>>sx>>sy>>ex>>ey;
        ++b[sx][sy];
        --b[ex+1][sy];
        --b[sx][ey+1];
        ++b[ex+1][ey+1];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            a[i][j]=a[i-1][j]+a[i][j-1]-a[i-1][j-1]+b[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}