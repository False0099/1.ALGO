#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 110;
struct Gauss{
    const double eps = 1e-8;
    double a[N][N];
    ll n;
    Gauss(int n):n(n){}
    ll gauss(){
        ll c, r;
        for (c = 0, r = 0; c < n; c ++ ){
            ll t = r;
            for (int i = r; i < n; i ++ )   
                if (fabs(a[i][c]) > fabs(a[t][c]))
                    t = i;
            if (fabs(a[t][c]) < eps) continue;
            for (int j = c; j < n + 1; j ++ ) swap(a[t][j], a[r][j]);   
            for (int j = n; j >= c; j -- ) a[r][j] /= a[r][c];    
            for (int i = r + 1; i < n; i ++ )   
                if (fabs(a[i][c]) > eps)
                    for (int j = n; j >= c; j -- )
                        a[i][j] -= a[r][j] * a[i][c];
            r ++ ;
        }
        if (r < n){
            for (int i = r; i < n; i ++ )
                if (fabs(a[i][n]) > eps)
                    return 2;
            return 1;
        }
        for (int i = n - 1; i >= 0; i -- )
            for (int j = i + 1; j < n; j ++ )
                a[i][n] -= a[i][j] * a[j][n];
        return 0;
    }
    void work(){
        int t=gauss();
        if(t==0){
            for (int i = 0; i < n; i ++ ){
                if (fabs(a[i][n]) < eps) a[i][n] = abs(a[i][n]);
                cout<<a[i][n]<<"\n";
            }
        }
        else if (t == 1) cout << "Infinite group solutions\n";
        else cout << "No solution\n";
    }
};

//高斯消元求异或线性方程组
const int N = 110;
struct Gauss_Xor{
    int n;
    int a[N][N];
    Gauss_Xor(int n):n(n){}
    int gauss(){
        int c,r;
        for(c=0,r=0;c<n;c++){
            int t=-1;
            for(int i=r;i<n;i++)
                if(a[i][c]){
                    t=i;
                    break;
                }
            if(t==-1) continue;
            for(int j=c;j<=n;j++) swap(a[r][j],a[t][j]);
            for(int i=r+1;i<n;i++)
                if(a[i][c])
                    for(int j=n;j>=c;j--)
                        a[i][j] ^= a[r][j];
            r++;
        }
        if(r<n){
            for(int i=r;i<n;i++)
                if(a[i][n]) return 2;
            return 1;
        }
        for(int i=n-1;i>=0;i--)
            for(int j=i+1;j<n;j++)
                if(a[i][j])
                    a[i][n]^=a[j][n];
        return 0;
    }
    void work(){
        int t=gauss();
        if(t==0){
            for(int i=0;i<n;i++) cout<<a[i][n]<<"\n";
        }else if(t==1){
            cout<<"Multiple sets of solutions\n";
        }else{
            cout<<"No solution\n";
        }
    }
};