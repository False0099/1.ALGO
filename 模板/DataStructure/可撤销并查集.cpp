struct Msg
{
    int x;
    int y;
    int sz;
}stk[N];
int top=0;

mt19937 rnd(time(0));
struct Dsu{
    int fa[N], rk[N],sz[N];
    void init(int n){
            for(int i=1;i<=n;i++){
              fa[i]=i;
               sz[i]=1;
               rk[i]=rnd();
           }
    }
    int find(int x){
        return x==fa[x]? x: find(fa[x]);
    }
    bool same(int x, int y){
        return find(x)==find(y);
    }
    void merge(int x, int y){
        x=find(x), y=find(y);
        if(x==y) return;
        if(rk[x]>rk[y]) swap(x, y);
        fa[x]=y;
        sz[y]+=sz[x];
        stk[++top]={x, y, sz[x]};
//if(rk[x]==rk[y]) rk[y]++;
    }
    void resume(){
        Msg t=stk[top--];
        int y=fa[t.x];
        int x=t.x;
        sz[y]-=sz[x];
        fa[x]=x;
    //        fa[t.y]-=t.sz;
    //fa[t.x]=t.x;
    }
}dsu;