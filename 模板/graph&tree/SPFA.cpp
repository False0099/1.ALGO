struct SPFA{
    #define INFI 0x3f3f3f3f
    struct Node{int v,w;};
    int n;
    vector<vector<Node>> G;
    vector<int> dis,cnt;
    vector<bool> in;
    SPFA(int n):n(n){G.resize(n+1);}
    //存在负环为true
    bool work(int st){
        dis.resize(n+1,INFI);
        in.resize(n+1,false);
        cnt.resize(n+1,0);
        queue <int> q;
        q.push(st);
        dis[st] = 0;
        in[st] = true;
        cnt[st] = 1;
        while (!q.empty()){
            int u = q.front();
            q.pop();
            in[u] = false;
            for(auto &t:G[u]){
                int v = t.v;
                int w = t.w;
                if (dis[v] > dis[u] + w){
                    dis[v] = dis[u] + w;
                    if (!in[v]){
                        cnt[v]++;
                        q.push(v);
                        in[v] = true;
                        if (cnt[v] >= n){
                            return true;
                        } 
                    }
                }
            }
        }
        return false;
    }
    void add(int u,int v,int w){
        G[u].push_back({v,w});
    }
    int query(int n){
        return dis[n];
    }
};


struct SPFA{
    #define INFI 0x3f3f3f3f
    #define NINFI 0x80808080
    struct Node{
        int v,w;
    };
    int n;
    vector<vector<Node>> G;
    vector<int> dis;
    vector<int> cnt;
    vector<bool> in;
    SPFA(int n){
        this->n=n;
        G.resize(n+1);
    }
    //存在负环为true
    bool work_sp(int st){
        dis.resize(n+1,INFI);
        in.resize(n+1,false);
        cnt.resize(n+1,0);
        queue <int> q;
        q.push(st);
        dis[st] = 0;
        in[st] = true;
        cnt[st] = 1;
        while (!q.empty()){
            int u = q.front();
            q.pop();
            in[u] = false;
            for (auto &t:G[u]){
                int v = t.v;
                int w = t.w;
                if (dis[v] > dis[u] + w){
                    dis[v] = dis[u] + w;
                    if (!in[v]){
                        cnt[v]++;
                        q.push(v);
                        in[v] = true;
                        if (cnt[v] >= n){
                            return true;
                        } 
                    }
                }
            }
        }
        return false;
    }
    bool work_lp(int st){
        dis.resize(n+1,NINFI);
        in.resize(n+1,false);
        cnt.resize(n+1,0);
        queue <int> q;
        q.push(st);
        dis[st] = 0;
        in[st] = true;
        cnt[st] = 1;
        while (!q.empty()){
            int u = q.front();
            q.pop();
            in[u] = false;
            for (auto &t:G[u]){
                int v = t.v;
                int w = t.w;
                if (dis[v] < dis[u] + w){
                    dis[v] = dis[u] + w;
                    if (!in[v]){
                        cnt[v]++;
                        q.push(v);
                        in[v] = true;
                        if (cnt[v] >= n){
                            return true;    
                        } 
                    }
                }
            }
        }
        return false;        
    }
    void add_one(int u,int v,int w){
        G[u].push_back({v,w});
    }
    void add_two(int u,int v,int w){
        G[u].push_back({v,w});
        if(w>=0){
            G[v].push_back({u,w});
        }
    }
    int query(int n){
        return dis[n];
    }
};