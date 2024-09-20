#include<bits/stdc++.h>
using namespace std;
constexpr int N = 1e6+10;
int a[N];
void quick_sort(int q[],int l,int r){
    if(l>=r) return;
    int x=q[l],i=l-1,j=r+1;
    while(i<j){
        do i++; while(q[i]<x);
        do j--; while(q[j]>x);
        if(i<j){
            swap(q[i],q[j]);
        }
    }
    quick_sort(q,l,j);
    quick_sort(q,j+1,r);
}
// 用两个数组模拟不合并key的map若需排序时使用
void quick_sort_hash(int q[],int ind[],int l,int r){
    if(l>=r) return;
    int x=q[l],i=l-1,j=r+1;
    while(i<j){
        do i++; while(q[i]<x);
        do j--; while(q[j]>x);
        if(i<j){
            swap(q[i],q[j]);
            swap(ind[i],ind[j]);
        }
    }
    quick_sort_hash(q,ind,l,j);
    quick_sort_hash(q,ind,j+1,r);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    quick_sort(a,0,n-1);
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
    }
    return 0;
}