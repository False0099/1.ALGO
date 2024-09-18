auto dij = [&](int s){
    priority_queue<pii> pq;
    vector<int> dis(n+1,INF);
    vector<bool> vis(n+1,0);
    pq.push({0,s});
    dis[s]=0;
    while(pq.size()){
        auto a=pq.top();
        pq.pop();
        int u=a.second;
        if(vis[u]) continue;
        vis[u]=true;    
        for(auto &t:g[u]){
            int v=t.first;int w=t.second;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                pq.push({-dis[v],v});
            }
        }
    }
    return dis;
};

auto dij = [&](int s){
    priority_queue<pair<double,int>> pq;
    vector<double> dis(4*n,INF);
    vector<bool> vis(4*n,0);
    pq.push({0,s});
    dis[s]=0;
    while(pq.size()){
        auto a=pq.top();
        pq.pop();
        int u=a.second;
        if(vis[u]) continue;
        vis[u]=true;    
        for(auto &t:g[u]){
            int v=t.first;double w=t.second;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                pq.push({-dis[v],v});
            }
        }
    }
    return dis;
};