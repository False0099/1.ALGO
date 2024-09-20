int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}

//加速版gcd
ll gcd(ll a,ll b){
    int tims(0);if(a<b) swap(a,b);
    while(!(a%2)&&!(b%2)) a=a/2,b=b/2,++tims;
    while(!(a==b)){
        int t1(a%2),t2(b%2);
        !t1?a=a/2:(!t2?b=b/2:a=a-b);
        if(a<b) swap(a,b);
    }
    while(tims--) a=a*2;
    return a;
}

ll lcm(ll m,ll n){
    ll g1,b;
    g1 = __gcd(m,n);
    b = (m*n) / g1; 
    return b;
}

int gcd(vector<int> a){
    int res=0;
    for(int i=0;i<a.size();i++){
        res=__gcd(res,a[i]);
    }
    return res;
}

int lcm(vector<int> a){
    int res=a[0];
    for(int i=1;i<a.size();i++){
        res=res/__gcd(res,a[i])*a[i];
    }
    return res;
}