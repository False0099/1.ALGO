vector<vector<int>> dis(n+1,vector<int>(n+1,INF));
for(int i=0;i<=n;i++){
    dis[i][i]=0;
}
auto add = [&](int u,int v,int w){
    dis[u][v]=min(dis[u][v],w);
};
auto floyd = [&](){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int k=1;k<=n;k++)
                dis[j][k]=min(dis[j][k],dis[j][i]+dis[i][k]);
                // dis[i][j] = max(dis[i][j], min(dis[i][k] , dis[k][j])); 传递闭包
};



template<typename T>
struct Floyd{
    #define MAXN 201
    vector<T> d[MAXN];
    int n;
    Floyd(int n):n(n){
        for(int i=0;i<=n;i++){
            d[i].resize(n+1,INF);
            for(int j=0;j<=n;j++){
                if(i==j){
                    d[i][j]=0;
                }
            }
        }
    }
    void work(){
        for (int k = 1; k <= n; k ++ )
            for (int i = 1; i <= n; i ++ )
                for (int j = 1; j <= n; j ++ )
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                    // d[i][j] = max(d[i][j], min(d[i][k] , d[k][j])); 传递闭包
    }
    T query(int st,int ed){
        if(d[st][ed]>INF/2){
            return 0x80808080;
        }
        return d[st][ed];
    }
    void add(int u,int v,T w){
        d[u][v]=min(d[u][v],w);
    }
    int cog;
    T getCog(vector<int> surr){
        MinSum(surr);
        return cog;
    }
    T MinSum(vector<int> surr){
        T Minval=INF;
        for(int i=1;i<=n;i++){
            T sum=0;
            for(auto &v:surr){
                sum+=query(i,v);
            }
            if(sum<Minval){
                cog=i;
                Minval=min(Minval,sum);
            }
        }
        return Minval;
    }
};