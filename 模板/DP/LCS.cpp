#include<bits/stdc++.h>
using namespace std;
//最长公共子序列
const int N=101000;
int a[N],ind[N],n;
int main(){
    cin>>n;
    int tmp;
    memset(a,0x3f,sizeof(a));
    for (int i=1;i<=n;i++){
        cin>>tmp;
        ind[tmp]=i;
    }
    for (int i=1;i<=n;i++){
        cin>>tmp;
        int x=ind[tmp];
        *lower_bound(a+1,a+n+1,x)=x;
    }
    cout<<(lower_bound(a+1,a+n+1,a[0])-a-1);
    return 0;
}