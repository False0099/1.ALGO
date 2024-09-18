#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int N= 1e6+10;
int a[N];
int q[N];
int tmp[N];
void merge_sort(int q[],int l,int r){
    if(l>=r) return;
    int mid=l+r>>1;
    merge_sort(q,l,mid);
    merge_sort(q,mid+1,r);
    int k=0,i=l,j=mid+1;
    while(i<=mid&&j<=r){
        if(q[i]<=q[j])tmp[k++]=q[i++];
        else tmp[k++]=q[j++];
    }
    while(i<=mid){
        tmp[k++]=q[i++];
    }
    while(j<=r){
        tmp[k++]=q[j++];
    }
    for(i=l,j=0;i<=r;i++,j++){
        q[i]=tmp[j];
    }
}

//归并排序求逆序对 merge_sort(0,n-1);
vector<int> tp;
ll merge_sort(int l,int r,vector<int> &q){
    if(l>=r) return 0;
    int mid=l+r>>1;
    ll res = merge_sort(l,mid,q)+merge_sort(mid+1,r,q);
    int k=0,i=l,j=mid+1;
    tp.resize(q.size(),0);
    while(i<=mid&&j<=r){
        if(q[i]<=q[j]){
            tp[k++]=q[i++];
        }else{
            tp[k++]=q[j++];
            res+=mid-i+1;
        }
    }
    while(i<=mid){
        tp[k++]=q[i++];
    }
    while(j<=r){
        tp[k++]=q[j++];
    }
    for(int i=l,j=0;i<=r;i++,j++){
        q[i]=tp[j];
    }
    return res;
}

int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    merge_sort(a,0,n-1);
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
    }
    return 0;
}