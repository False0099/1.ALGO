# Tree Tag

## 题面翻译

有一棵 $n$ 个点的树， Alice 和 Bob 初始在这棵树上的节点 $a$, $b$。

他们可以在树上轮流移动一段距离不超过 $da$ 和 $db$ 的路径。

路径长度的定义是两点之间树上简单路径的边数。

如果 Alice 能在 $10^{100}$ 次内追到 Bob ，那么则算 Alice 赢，否则算 Bob 赢。

## 题目描述

Alice and Bob are playing a fun game of tree tag.

The game is played on a tree of $ n $ vertices numbered from $ 1 $ to $ n $ . Recall that a tree on $ n $ vertices is an undirected, connected graph with $ n-1 $ edges.

Initially, Alice is located at vertex $ a $ , and Bob at vertex $ b $ . They take turns alternately, and Alice makes the first move. In a move, Alice can jump to a vertex with distance at most $ da $ from the current vertex. And in a move, Bob can jump to a vertex with distance at most $ db $ from the current vertex. The distance between two vertices is defined as the number of edges on the unique simple path between them. In particular, either player is allowed to stay at the same vertex in a move. Note that when performing a move, a player only occupies the starting and ending vertices of their move, not the vertices between them.

If after at most $ 10^{100} $ moves, Alice and Bob occupy the same vertex, then Alice is declared the winner. Otherwise, Bob wins.

Determine the winner if both players play optimally.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). Description of the test cases follows.

The first line of each test case contains five integers $ n, a, b, da, db $ ( $ 2\le n\le 10^5 $ , $ 1\le a, b\le n $ , $ a\ne b $ , $ 1\le da, db\le n-1 $ ) — the number of vertices, Alice's vertex, Bob's vertex, Alice's maximum jumping distance, and Bob's maximum jumping distance, respectively.

The following $ n-1 $ lines describe the edges of the tree. The $ i $ -th of these lines contains two integers $ u $ , $ v $ ( $ 1\le u, v\le n, u\ne v $ ), denoting an edge between vertices $ u $ and $ v $ . It is guaranteed that these edges form a tree structure.

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single line containing the winner of the game: "Alice" or "Bob".

## 样例 #1

### 样例输入 #1

```
4
4 3 2 1 2
1 2
1 3
1 4
6 6 1 2 5
1 2
6 5
2 3
3 4
4 5
9 3 9 2 5
1 2
1 6
1 9
1 3
9 5
7 9
4 8
4 3
11 8 11 3 3
1 2
11 9
4 9
6 5
2 10
3 2
5 9
8 3
7 4
7 10
```

### 样例输出 #1

```
Alice
Bob
Alice
Alice
```

## 提示

In the first test case, Alice can win by moving to vertex $ 1 $ . Then wherever Bob moves next, Alice will be able to move to the same vertex on the next move.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1404B/49586895aed4babac3e35aba1e1c4162a3ac0674.png)In the second test case, Bob has the following strategy to win. Wherever Alice moves, Bob will always move to whichever of the two vertices $ 1 $ or $ 6 $ is farthest from Alice.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1404B/514885d88075ac42c59e9da88fb4903131f99500.png)
## 题解
本题，我们的思路是：**先去手玩样例，然后再去找极端情况**，我们显然对于本题，我们的 $Alice$ 是比较好操作的一方，也就是我们的 $Alice$ 获胜的条件是更容易判断的。

具体我们有下面的规定和方法：
1. 我们的 `ALICE` 可以一步走到我们的 `BOB` 的位置，那么我们就可以直接进行我们的操作即可。
2. 我们的 `BOB` 无论怎么走，始终不能够超过我们的 `ALICE` 的范围当中。这样的结果就是：我们的 `BOB` 的结果一定是满足我们的最小值的。
3. 我们的 `ALICE` 一步可以到达我们的任意一个结点，也就是我们的 `ALICE` 一步能够覆盖整个树，而要能够覆盖整个树，一定要能够覆盖我们的直径，因此，**只需要覆盖我们的直径即可**。

```cpp
#include <bits/stdc++.h>

#define int long long

int INF=0x3f3f3f3f3f;

using namespace std;

const int N=1e5+10;

vector<int> e[N];

int dist[N];

void dfs(int u,int fa){

    dist[u]=dist[fa]+1;

    for(auto v:e[u]){

        if(v==fa){

            continue;

        }

        dfs(v,u);

    }

}

void solve(){

    int n,a,b,da,db;

    cin>>n>>a>>b>>da>>db;

    for(int i=1;i<=n;i++){

        e[i].clear();

    }

    for(int i=1;i<n;i++){

        int a,b;

        cin>>a>>b;

        e[a].push_back(b);

        e[b].push_back(a);

    }

    dfs(1,0);

    int maxw=0;

    for(int i=1;i<=n;i++){

        if(dist[maxw]<dist[i]){

            maxw=i;

        }

    }

    dfs(maxw,0);

    maxw=0;

    for(int i=1;i<=n;i++){

        if(dist[maxw]<dist[i]){

            maxw=i;

        }

    }

    if(dist[maxw]<=2*da+1){

        //cout<<dist[maxw]<<endl;

        cout<<"Alice"<<endl;

        return;

    }

    dfs(a,0);

    if(dist[b]<=da+1){

        cout<<"Alice"<<endl;

        return;

    }

    if(2*da>=db){

        cout<<"Alice"<<endl;

        return;

    }

    cout<<"Bob"<<endl;

}

signed main(){

    ios::sync_with_stdio(false),cin.tie(0);

    int t;

    cin>>t;

    while(t--){

        solve();

    }

}
```