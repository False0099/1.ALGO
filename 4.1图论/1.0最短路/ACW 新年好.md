# 知识点
  ## [[]]
# 题目
 重庆城里有 n 个车站，m 条双向公路连接其中的某些车站。

每两个车站最多用一条公路连接，从任何一个车站出发都可以经过一条或者多条公路到达其他车站，但不同的路径需要花费的时间可能不同。

在一条路径上花费的时间等于路径上所有公路需要的时间之和。

佳佳的家在车站 1，他有五个亲戚，分别住在车站 a, b, c, d, e。

过年了，他需要从自己的家出发，拜访每个亲戚（顺序任意），给他们送去节日的祝福。

怎样走，才需要最少的时间？

## 输入格式
第一行：包含两个整数 n, m，分别表示车站数目和公路数目。

第二行：包含五个整数 a, b, c, d, e，分别表示五个亲戚所在车站编号。

以下 m 行，每行三个整数 x, y, t，表示公路连接的两个车站编号和时间。

## 输出格式
输出仅一行，包含一个整数 T，表示最少的总时间。

## 数据范围
1≤n≤50000
,
1≤m≤10^5
,
1<a, b, c, d, e≤n
,
1≤x, y≤n
,
1≤t≤100
## 输入样例 ：
6 6
2 3 4 5 6
1 2 8
2 3 3
3 4 4
4 5 5
5 6 2
1 6 7
## 输出样例 ：
21

# 思路
·我们可以先通过构造每一个亲戚点和自己的点到其他点的最短路，作为我们未来查表的依据。
·之后我们在枚举所有可能的拜访序列，并计算这些序列中，价值最小的一个序列。
·枚举序列的工作我们可以通过 C++自带的库函数 next_permutation进行。
# AC 代码
```cpp
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair <int,int> PII;
const int N = 50010,M = 200010,K = 10,INF = 0x3f3f3f3f;
int n,m;
int id[K];
int d[K][N];
int h[N],e[M],w[M],ne[M],idx;
void add (int a,int b,int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}
void dijkstra (int s,int dist[]) {
    bool st[N] = {false};
    dist[s] = 0;
    priority_queue <PII,vector <PII>,greater <PII>> heap;
    heap.push ({0,s});
    while (!heap.empty ()) {
        int t = heap.top ().second;
        heap.pop ();
        if (st[t]) continue;
        st[t] = true;
        for (int i = h[t];~i;i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                heap.push ({dist[j],j});
            }
        }
    }
}
int main () {
    memset (h,-1,sizeof (h));
    memset (d,0x3f,sizeof (d));
    cin >> n >> m;
    id[1] = 1;
    for (int i = 2;i <= 6;i++) cin >> id[i];
    while (m--) {
        int a,b,c;
        cin >> a >> b >> c;
        add (a,b,c),add (b,a,c);
    }
    for (int i = 1;i <= 6;i++) dijkstra (id[i],d[i]);
    int a[K];
    for (int i = 1;i <= 6;i++) a[i] = i;
    int ans = INF;
    do {
        int res = d[a[1]][id[a[2]]];
        for (int i = 2;i <= 5;i++) res += d[a[i]][id[a[i + 1]]];
        ans = min (ans,res);
    }
    while (next_permutation (a + 2,a + 7));
    cout << ans << endl;
    return 0;
}
```
# 备注
