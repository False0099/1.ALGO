const int N = 1e6+10;
#define ls(x) x<<1
#define rs(x) x<<1|1
struct Node{
    int l,r;
    
}tr[N<<2];
int a[N];
void pushup(Node &u,Node l,Node r){

}
void pushup(int u){
    pushup(tr[u],tr[ls(u)],tr[rs(u)]);
}
void build(int u,int l,int r){
    if(l==r){
        
        return;
    }
    tr[u]={l,r};
    int mid=l+r>>1;
    build(ls(u),l,mid);build(rs(u),mid+1,r);
    pushup(u);
}
void modify(int u,int x,int v){
    if(tr[u].l==x&&tr[u].r==x){
        
        return;
    }
    int mid=tr[u].l+tr[u].r>>1;
    if(x<=mid){
        modify(ls(u),x,v);
    }else{
        modify(rs(u),x,v);
    }
    pushup(u);
}
void modify(int u,int l,int r,int v){
    if(tr[u].l>=l&&tr[u].r<=r){

        return;
    }
    int mid=tr[u].l+tr[u].r>>1;
    if(l<=mid){
        modify(ls(u),l,r,v);
    }
    if(r>mid){
        modify(rs(u),l,r,v);
    }
    pushup(u);
}
int query(int u,int l,int r){
    if(tr[u].l>=l&&tr[u].r<=r){
        
    }
    int res=0;
    int mid=tr[u].l+tr[u].r>>1;
    if(l<=mid){
        res=query(ls(u),l,r);
    }
    if(r>mid){
        
    }
    return res;
}
