给定一个序列 **A={a1, a2, a3,... an}** 。定义 **P(A, l, r)**为 **{al,... ar}** 中最大数的最左位置  
定义两个序列**A**和**B**相似，当且仅当 对任意 **1 ≤ l ≤ r ≤ n, P(A, l, r) = P(B, l, r)**.  
给定一个序列 **A**，随机产生一个序列**B={b1, b2, b3,... bn}** ，其中**B**中的所有元素都是从(0,1)区间内随机选择的。如果**A**和**B**是相似的，那么**B**的"满意度"为**B**中所有值之和，否则为0，求**B**的“满意度”的期望大小  
**B**中的值随机选择的意思是说，**B**中每个数字取(0,1)区间内每个值概率相同

Input

第一行一个整数 **T**, 表示测试数据组数  
第一行一个整数n，代表**A**序列的长度  
第二行**n**个整数，代表**A**序列中的所有元素  
保证 **1 ≤ n ≤ 3*106**

Output

对每组数据，输出一行，**B** 满意度期望在模 **109 + 7**意义下的取值.

Sample Input

5
3
1 2 1
3
1 2 3
5
3 2 1 2 3
5
1 2 3 2 1
5
1 2 2 1 2

Sample Output

500000004
250000002
520833337
125000001
83333334

## 题解
解：不难看出如果 A 和 B 是 RMQ Similar，则 A 和 B 的笛卡尔树同构。考虑 B 中的每个数是0~1之间的实数，因此出现相同数字的概率为0，可以假设 B 是每个数都不相同排列。设 A 的笛卡尔树每个子树的大小为 sz[u]，则任一 B 排列与 A 同构的概率是∏n11/sz[i]，因为 B 中每个数满足均匀分布，因此期望值为1/2，和的期望为 n/2，因此满足与 A 同构的 B 中所有数之和的期望为 n/2∏n1sz[i]

```cpp
#include<bits/stdc++.h>
using namespace std;
 
typedef long long LL;
 
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int MX = 1e6 + 5;
 
struct node {
    int val, sz;
    int l, r, pre;
} t[MX];
stack<int>st;
void init (int n) {
    for (int i = 0; i <= n; i++) t[i].l = t[i].r = t[i].pre = t[i].sz = 0;
    t[0].val = INF;
    while (!st.empty() ) st.pop();
    st.push (0);
}
void build (int n) { //从右端插入
    for (int i = 1; i <= n; i++) {
        while (!st.empty() && t[st.top()].val < t[i].val) st.pop();
        int pre = st.top();
        t[i].pre = pre;
        t[i].l = t[pre].r;
        t[t[pre].r].pre = i;
        t[pre].r = i;
        st.push (i);
    }
}
void dfs (int u) {
    if (u == 0) return;
    t[u].sz = 1;
    dfs (t[u].l);
    dfs (t[u].r);
    t[u].sz += t[t[u].l].sz + t[t[u].r].sz;
}
 
LL inv[MX];
void init() {
    inv[1] = 1;
    for (int i = 2; i < MX; i++) inv[i] = inv[mod % i] * (mod - mod / i) % mod;
}
 
int main() {
    //freopen ("in.txt", "r", stdin);
    int T, n; cin >> T;
    init();
    while (T--) {
        scanf ("%d", &n);
        init (n);
        for (int i = 1; i <= n; i++) scanf ("%d", &t[i].val);
        build (n);
        dfs (t[0].r);
 
        LL ans = n * inv[2] % mod;
        for (int i = 1; i <= n; i++) ans = ans * inv[t[i].sz] % mod;
        printf ("%lld\n", ans);
    }
    return 0;
}
```