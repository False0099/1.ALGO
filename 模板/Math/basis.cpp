//高斯消元
auto gauss = [&](vector<int> &a){
    int k=0;
    for(int i=62;i>=0;i--){
        for(int j=k;j<n;j++){
            if(a[j]>>i&1){
                swap(a[j],a[k]);
                break;
            }
        }
        if((a[k]>>i&1)==0){
            continue;
        }
        for(int j=0;j<n;j++){
            if(j!=k&&(a[j]>>i&1)){
                a[j]^=a[k];
            }
        }
        k++;
        if(k==n){
            break;
        }
    }
    return k;
}; 

//贪心
vector<int> p(64);
auto insert = [&](int x){
    for(int i=63;i>=0;i--){
        if(x>>i&1){
            if(p[i]){
                x^=p[i];
            }else{
                p[i]=x;
                break;
            }
        }
    }
};