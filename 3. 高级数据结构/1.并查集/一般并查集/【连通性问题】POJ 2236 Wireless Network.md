云大准备组建原神社团。云大的 ACM (Asia Cooperated Medical 亚洲联合医疗队) er 为新组建的原神社团装备了一个无线基站，每个玩家只要启动原神，就能与附近一定距离内的玩家的联机，并且进入同一个原神世界（提瓦特大陆）。原神社团的玩家们逐个进入游戏，他们的世界逐渐连为一体。由于受到校园网的约束，每个人的提瓦特大陆只能与距离它不超过 d 米的其它提瓦特大陆连接。但提瓦特大陆的连接关系可以通过中间传递，也就是说，如果 A 的提瓦特大陆和 B 的提瓦特大陆不能直接连接，但是他们都可以和 C 的提瓦特大陆直接连接（不超过 d 米），那么 A、B、C 的提瓦特大陆便可以相互连接。  
  
你作为社团的干事，详细地记录了每个原神世界的连接情况，同一个时刻，你会检测到某个玩家的原神被启动；或者面对来自社长的拷问：原神玩家A与B是否在同一个世界中。  

## 输入

第一行包含了两个整数 N 和 d (1 <= N <= 1001, 0 <= d <= 20000)。此处 N 是原神玩家的数目，编号从 1 到 N；同时，D 是两个提瓦特大陆能够直接连接的最大距离。接下来的 N 行，每行包含两个整数 xi, yi (0 <= xi, yi <= 10000)，表示 N 个提瓦特大陆的坐标。从第 (N+1) 行到输入结束，是逐一执行的操作，每行包含一个操作，格式是以下两者之一：  
1. "O p" (1 <= p <= N)，表示玩家p的原神启动！。  
2. "S p q" (1 <= p, q <= N)，表示社长拷问你提瓦特大陆 p 和 q 是否连接在一起。  
  
输入不超过 300000 行。  

## 输出

对于每个来自社长的拷问，如果两个提瓦特大陆连接在一起，则打印 "SUCCESS"；否则，打印 "FAIL"。

示例输入

4 1
0 1
0 2
0 3
0 4
O 1
O 2
O 4
S 1 4
O 3
S 1 4

示例输出

FAIL
SUCCESS

```CPP
// Decline is inevitable,
// Romance will last forever.
// POJ2236
//#include <bits/stdc++.h>
#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <deque>
#include <vector>
using namespace std;
#define mst(a, x) memset(a, x, sizeof(a))
#define INF 0x3f3f3f3f
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define ll long long
//#define int long long
const int maxn = 1e3 + 10;
const int maxm = 25;
const int P = 1e9 + 7;
int fa[maxn];
int n, d;
int x[maxn], y[maxn];
int repair[maxn];
int find(int x) {
    if(x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}
double dis(int a, int b) {
    return sqrt(double(x[a]-x[b]) * (x[a]-x[b]) + double(y[a]-y[b]) * (y[a]-y[b]));
}
void solve() {
    scanf("%d%d", &n, &d);
    for(int i = 0; i <= n; i++)
        fa[i] = i;
    for(int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    char cmd[2];
    int p,q,cnt=0;
    while(scanf("%s",cmd)!=EOF){
        if(cmd[0] == 'O')
        {
            scanf("%d", &p);
            p--;
            repair[cnt++] = p;
            for(int i = 0; i < cnt-1; i++)
                if(dis(repair[i], p) <= double(d) && repair[i] != p)
                    fa[find(p)] = find(repair[i]);
        }
        else
        {
//            cin >> p >> q;
            scanf("%d%d", &p, &q);
            p--, q--;
            if(find(p) == find(q))
//                puts("SUCCESS\n");
                printf("SUCCESS\n");
            else
//                puts("FAIL\n");
                printf("FAIL\n");
        }
        
    }
}
signed main() {
//    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//    int T; scanf("%d", &T); while(T--)
//    int T; cin >> T; while(T--)
    solve();
    return 0;
}
```