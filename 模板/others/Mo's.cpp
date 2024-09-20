struct Q{
    int l,r,id;
};

vector<int> a(n+1,0);
for(int i=1;i<=n;i++){
    cin>>a[i];
}
vector<int> pos(n+1,0);
int siz = sqrt(n);
for(int i=1;i<=n;i++){
    pos[i]=i/siz;
}
vector<Q> query(m); 
for(int i=0;i<m;i++){
    int l,r;
    cin>>l>>r;
    query[i]={l,r,i};
}
sort(query.begin(),query.end(),[&](Q a,Q b){
    return pos[a.l]==pos[b.l]?a.r<b.r:pos[a.l]<pos[b.l];
});
int l=1,r=0;
int res=0;
auto add = [&](int x){

};
auto del = [&](int x){

};
vector<int> ans(m,0);
for(int i=0;i<m;i++){
    auto [ql,qr,id] = query[i];
    while(ql<l) add(--l);
    while(qr>r) add(++r);
    while(ql>l) del(l++);
    while(qr<r) del(r--);
    ans[id]=res;
}