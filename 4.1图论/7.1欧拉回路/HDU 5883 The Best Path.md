Alice is planning her travel route in a beautiful valley. In this valley, there are N lakes, and M rivers linking these lakes. Alice wants to start her trip from one lake, and enjoys the landscape by boat. That means she need to set up a path which go through every river exactly once. In addition, Alice has a specific number (a_1, a_2, ... , a_n) for each lake. If the path she finds is P_0 \rightarrow P_1 \rightarrow ... \rightarrow P_t, the lucky number of this trip would be a_{P_0} \quad XOR \quad a_{P_1} \quad XOR \quad... \quad XOR \quad a_{P_t}. She want to make this number as large as possible. Can you help her?

Input

The first line of input contains an integer t, the number of test cases. t test cases follow.  
  
For each test case, in the first line there are two positive integers N~(N \leq 100000) and M~(M \leq 500000), as described above. The i-th line of the next N lines contains an integer a_i(\forall i, 0 \leq a_i \leq 10000) representing the number of the i-th lake.  
  
The i-th line of the next M lines contains two integers u_i and v_i representing the i-th river between the u_i-th lake and v_i-th lake. It is possible that u_i=v_i.

Output

For each test cases, output the largest lucky number. If it dose not have any path, output "Impossible".

Sample

|Inputcopy|Outputcopy|
|---|---|
|2<br>3 2<br>3<br>4<br>5<br>1 2<br>2 3<br>4 3<br>1<br>2<br>3<br>4<br>1 2<br>2 3<br>2 4|2<br>Impossible|

## 题解
我们本题要求一条异或路径之最大的欧拉回路，于是，我们求欧拉回路的时候，就要注意 
1. 首先判断是不是联通的，
2. 如果我们是否存在两个度为基数的点，如果有，那么就是欧拉路径，否则，就是欧拉回路。
3. 如果图中存在欧拉路，那么起点和终点被异或的次数就是其度数/2+1, 其他节点的就是度数的一半。
4. 如果存在欧拉回路，那么起点和终点不是规定过的，就有多种走法，而每种走法，只有起点多访问了一次，对于其他店，被异或的次数还是度数的一半，对于起来来说，是读度数的一半+1，这样，我们就只要枚举起点然后取最大值即可。

另外，欧拉回路的题中，如果不要求输出我们的欧拉回路，我们就不需要进行我们的建边，我们直接去计算即可。

```cpp
//https://www.cnblogs.com/shuitiangong/
#include<set>
#include<map>
#include<list>
#include<stack>
#include<queue>
#include<cmath>
#include<ctime>
#include<cstdio>
#include<cctype>
#include<string>
#include<vector>
#include<climits>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define endl '\n'
#define rtl rt<<1
#define rtr rt<<1|1
#define lson rt<<1, l, mid
#define rson rt<<1|1, mid+1, r
#define zero(a) memset(a, 0, sizeof(a))
#define INF(a) memset(a, 0x3f, sizeof(a))
#define IOS ios::sync_with_stdio(false)
#define _test printf("==================================================\n")
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
typedef pair<ll, ll> P2;
const double pi = acos(-1.0);
const double eps = 1e-8;
const ll MOD =  1000000009;
const int INF = 0x3f3f3f3f;
const int maxn = 1e5+10;
int n, m, p[maxn], deg[maxn], val[maxn];
int find(int root) {
    int son = root, tmp;
    while(root != p[root]) root = p[root];
    while(son != root) {
        tmp = p[son];
        p[son] = root;
        son = tmp;
    }
    return root;
}
void merge(int a, int b) {
    p[find(a)] = find(b);
}
int main(void) {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i<=n; ++i) {
            p[i] = i;
            deg[i] = 0;
            scanf("%d", &val[i]);
        }
        while(m--) {
            int a, b;
            scanf("%d%d", &a, &b);
            ++deg[a], ++deg[b];
            merge(a, b);
        }
        int root = 0, cnt = 0;
        for (int i = 1; i<=n; ++i) {
            if (p[i]==i) ++root; //并查集检查图的连通性
            if (deg[i]&1) ++cnt; //记录度为奇数的结点个数
        }
        if (root>1 || cnt>2) printf("Impossible\n"); 
        else {
            int ans = 0;
            if (cnt) {
                for (int i = 1; i<=n; ++i)
                    if ((deg[i]+1)>>1&1) ans ^= val[i];
                //对于欧拉路径来说，有2个度为奇数的结点，两个结点的访问次数比度数的一半多1
            }
            else {
                for (int i = 1; i<=n; ++i)
                    if (deg[i]>>1&1) ans ^= val[i];
                for (int i = 1; i<=n; ++i)
                    ans = max(ans, ans^val[i]);
                //对于欧拉回路来说，结点的度数都是偶数，起点的访问次数比度数的一半多1
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
```