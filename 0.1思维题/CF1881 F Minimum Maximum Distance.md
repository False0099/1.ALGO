You have a tree with $n$ vertices, some of which are marked. A tree is a connected undirected graph without cycles.

Let $f_i$ denote the maximum distance from vertex $i$ to any of the marked vertices.

Your task is to find the minimum value of $f_i$ among all vertices.

![](https://espresso.codeforces.com/274c072df56daa8245be057f40c9af87463bd559.png)

For example, in the tree shown in the example, vertices $2$, $6$, and $7$ are marked. Then the array $f(i) = [2, 3, 2, 4, 4, 3, 3]$. The minimum $f_i$ is for vertices $1$ and $3$.

**Input**

The first line contains an integer $t$ ($1 \le t \le 10^4$) — the number of test cases.

The first line of each test case contains two integers $n$ and $k$ ($1 \le k \le n \le 2 \cdot 10^5$) — the number of vertices in the tree and the number of marked vertices, respectively.

The second line of each test case contains $k$ integers $a_i$ ($1 \le a_i \le n, a_{i-1} &lt; a_i$) — the indices of the marked vertices.

The next $n - 1$ lines contain two integers $u_i$ and $v_i$ — the indices of vertices connected by the $i$ \-th edge.

It is guaranteed that the sum of $n$ over all test cases does not exceed $2 \cdot 10^5$.


**Output**

For each test case, output a single integer — the minimum value of $f_i$ among all vertices.

## 题解
下面的点从0开始记录

先找距离0最远的标记点，记作L

在找距离L最远的标记点，记作R

L到所有点的距离记录在b数组中，R则在c数组中

i 点到标记点最远距离一定是 max(b[i],c[i]);

```cpp

void solve(){
    int n,k;cin>>n>>k;
    //1标记,0未标记 
    vector<bool>mk(n,0);
    for(int i=0;i<k;i++){
        int x;cin>>x;x--;
        mk[x]=1;
    }  

    vector<vector<int>>adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto bfs=[&](int u) -> vector<int> {
        vector<int>d(n,-1);
        queue<int>q;
        q.push(u);d[u]=0;
        while(!q.empty()){
            int x=q.front();
            q.pop();
            for(auto y:adj[x]){
                if(d[y]!=-1) continue;
                d[y]=d[x]+1;
                q.push(y);
            }
        }
        return d;
    };
    auto a=bfs(0);
    int L=0,mx=-1;
    for(int i=0;i<n;i++){
        if(!mk[i]) continue;
        if(a[i]>mx){
            mx=a[i];L=i;
        }
    }
    auto b=bfs(L);
    int R=0;mx=-1;
    for(int i=0;i<n;i++){
        if(!mk[i]) continue;
        if(b[i]>mx){
            mx=b[i];R=i;
        }
    }
    auto c=bfs(R);

    vector<int>dis(n,-1);
    for(int i=0;i<n;i++){
        dis[i]=max({b[i],c[i]});
    }
    int mn=inf;
    for(int i=0;i<n;i++){
        mn=min(mn,dis[i]);
    }
    cout<<mn<<'\n';
    ```



