#include<bits/stdc++.h>
using namespace std;
//最长上升子序列(严格单调递增)
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    int n;
    cin>>n;
    vector<int> a(n);
    vector<int> st;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    st.push_back(a[0]);
    for(int i=1;i<n;i++){
        if(a[i]>st.back()){
            st.push_back(a[i]);
        }else{
            *lower_bound(st.begin(),st.end(),a[i]) = a[i];
        }
    }
    cout<<st.size();
    return 0;
}