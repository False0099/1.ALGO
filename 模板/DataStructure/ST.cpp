#include<bits/stdc++.h>
using namespace std;
const int N = 50005;
int n;
int a[N],dp_max[N][22],dp_min[N][21];
void init(){    //先输入a再init
    for(int i=1;i<=n;i++){
        dp_min[i][0]=a[i];
        dp_max[i][0]=a[i];
    }
    int p=log2(n);
    for(int k=1;k<=p;k++){
        for(int s=1;s+(1<<k)<=n+1;s++){
            dp_max[s][k]=max(dp_max[s][k-1],dp_max[s+(1<<(k-1))][k-1]);
            dp_min[s][k]=min(dp_min[s][k-1],dp_min[s+(1<<(k-1))][k-1]);
        }
    }
}
int query(int L,int R){
    int k = log2(R-L+1);
    int x=max(dp_max[L][k],dp_max[R-(1<<k)+1][k]);//取区间最大
    int y=min(dp_min[L][k],dp_min[R-(1<<k)+1][k]);//取区间最小
    return x-y;
}

struct ST {
    int n;
    vector<int> in1, in2, lg;
    vector<vector<int>> Max, Min;
    ST(int n) : n(n), in1(n + 1), in2(n + 1), lg(n + 1) {
        for (int i = 2; i <= n; i++) {
            lg[i] = lg[i / 2] + 1;
        }
        Max.resize(n + 1, vector<int>(lg[n] + 1));
        Min.resize(n + 1, vector<int>(lg[n] + 1));
    }
    void init() {
        for (int i = 1; i <= n; i++) {
            Max[i][0] = in1[i];
            Min[i][0] = in2[i];
        }
        int k = lg[n];
        for (int j = 1; j <= k; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                Max[i][j] = max(Max[i][j - 1], Max[i + (1 << (j - 1))][j - 1]);
                Min[i][j] = min(Min[i][j - 1], Min[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    int getMax(int l, int r) {
        if (l > r) {
            swap(l, r);
        }
        int k = lg[r - l + 1];
        return max(Max[l][k], Max[r - (1 << k) + 1][k]);
    }
    int getMin(int l, int r) {
        if (l > r) {
            swap(l, r);
        }
        int k = lg[r - l + 1];
        return min(Min[l][k], Min[r - (1 << k) + 1][k]);
    }
};