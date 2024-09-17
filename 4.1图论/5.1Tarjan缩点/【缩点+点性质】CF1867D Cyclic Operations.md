# Cyclic Operations

## 题面翻译

给定一个长为 $n$ 的数组 $a$，初始全为 $0$，可进行如下操作：

构建长为 $k$ 的序列 $l$，将 $a_{l_i}$ 变为 $l_{(i\bmod k)+1}(1\le i\le k,1\le\ l_i\le n)$。

若干操作后可得到数组 $b$，给定 $n,k$ 和数组 $b$，求 $b$ 能否由 $a$ 经过上述操作得到。

对于每组测试数据，输出 `YES` 或 `NO`，输出对大小写不敏感。

$1\le t\leq 10^5,1\le k\le n\le 10^5,1\le b_i\le n,\sum n\leq 2\times 10^5$

## 题目描述

Egor has an array $ a $ of length $ n $ , initially consisting of zeros. However, he wanted to turn it into another array $ b $ of length $ n $ .

Since Egor doesn't take easy paths, only the following operation can be used (possibly zero or several times):

- Choose an array $ l $ of length $ k $ ( $ 1 \leq l_i \leq n $ , all $ l_i $ are distinct) and change each element $ a_{l_i} $ to $ l_{(i\%k)+1} $ ( $ 1 \leq i \leq k $ ).

He became interested in whether it is possible to get the array $ b $ using only these operations. Since Egor is still a beginner programmer, he asked you to help him solve this problem.

The operation $ \% $ means taking the remainder, that is, $ a\%b $ is equal to the remainder of dividing the number $ a $ by the number $ b $ .

## 输入格式

The first line of the input contains an integer $ t $ ( $ 1 \leq t \leq 10^5 $ ) - the number of test cases.

Each test case consists of two lines. The first line contains two integers $ n $ and $ k $ ( $ 1 \leq k \leq n \leq 10^5 $ ).

The second line contains the array $ b_1, b_2, \ldots, b_n $ ( $ 1 \leq b_i \leq n $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output "YES" (without quotes) if there is a way to get the array $ b $ using only the given operation. Otherwise, output "NO" (without quotes). You can output each letter in any case (lowercase or uppercase). For example, the strings "yEs", "yes", "Yes" and "YES" will be accepted as a positive answer.

## 样例 #1

### 样例输入 #1

```
6
5 3
2 3 5 3 4
4 2
2 4 3 1
1 1
1
3 1
1 2 3
5 3
5 4 3 2 1
6 1
1 2 3 1 5 6
```

### 样例输出 #1

```
YES
NO
YES
YES
NO
NO
```

## 提示

Let's consider the first example:

- Apply the operation with $ l $ = $ [1,2,3] $ . Now $ a $ = $ [2,3,1,0,0] $ .
- Apply the operation with $ l $ = $ [3,5,4] $ . Now $ a $ = $ [2,3,5,3,4] $ = $ b $ .

 We see that it is possible to get the array $ b $ . Therefore, the answer is YES. In the second example, it can be proven that the array $ b $ cannot be obtained, therefore the answer is NO.

## 题解
首先我们需要读懂我们的题意：$a[l[i]]=l[i+1]$,于是，我们知道了我们的 $b$ 数组后，相当于我们就已经知道了两个信息，一个是我们的 $l[i](i)$,另一个是我们的 $l[i+1](a[i])$ 。于是，我们考虑把这两个信息之间连一条边。

然后我们发现，如果假如我们的图能够构成一个环，并且我们的这个环的大小是小于我们的 k，那么我们一定是可以连接构造出一个合法的方案的，例如，我们有 $1\to2 \to 3\to 1$,那么我们只需要构造 $[1,2,3]$ 即可。

考虑到我们的样例中出现了下面的情况也是合法的：![[Pasted image 20240315135359.png]]
我们考虑我们可以有覆盖，所以，我们可以先构造出我们的 $[1,2,3]$,然后再狗仔我们的 $[3,4,5]$ 来覆盖我们的答案。于是我们就可以考虑下面的结论：我们的**答案只与我们的环的大小有关**。如果我们的任意环的大小和我们的 k 相同，那么我们直接输出 true，否则我们输出 false 即可。

**注意，我们本题需要我们特判我们 $k=1$ 的情况**。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#include<queue>
#include<stack>
#define sort stable_sort
#define map unordered_map
using namespace std;
typedef long long ll;

struct edge{
    int from, to;
    int nxt;
}; // 边

int T;
int n, k;
edge e[100010];
int head[100010]; // 图
int low[100010];
int dfn[100010];
int ins[100010]; // Tarjan 所需的数组
int pos[100010]; // 每个点属于哪个强连通分量
int sz[100010]; // 强连通分量的大小，用于记录环的大小
int out[100010]; // 每个强连通分量发出边数
int sccs; // 强连通分量的数量
int num; // Tarjan 记录遍历顺序
int cnt; // 图
stack<int> st; // Tarjan 所需的栈

void add(int x, int y){ // 加边
    e[cnt].from = x;
    e[cnt].to = y;
    e[cnt].nxt = head[x];
    head[x] = cnt;
    cnt++;
}

void tarjan(int u){ // Tarjan 求强连通分量
    num++;
    low[u] = num, dfn[u] = num;
    ins[u] = 1;
    st.push(u);
    for(int i = head[u]; i != -1; i = e[i].nxt){
        int v = e[i].to;
        if(dfn[v] == 0){
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }else if(ins[v] != 0){
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(low[u] == dfn[u]){
        sccs++; 
        int now, ccnt = 0;
        do{
            now = st.top();
            ins[now] = 0;
            pos[now] = sccs;
            ccnt++;
            st.pop();
        }while(now != u);
        sz[sccs] = ccnt;
    }
}

void init(){ // 注意清空数据
    cnt = 0;
    num = 0;
    for(int i = 1; i <= n; i++){
        head[i] = -1;
        low[i] = 0;
        dfn[i] = 0;
        ins[i] = 0;
        pos[i] = 0;
        out[i] = 0;
        sz[i] = 0;
    }
    sccs = 0;
    while(st.empty() == 0){
        st.pop();
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    memset(head, -1, sizeof(head));
    cin >> T;
    while(T--){
        init();
        cin >> n >> k;
        bool flag0 = 1;
        for(int i = 1; i <= n; i++){
            int u;
            cin >> u;
            if(k == 1 && u != i){
                flag0 = 0;
            }
            add(i, u);
        }
        if(flag0 == 0){ // 特判 k = 1 的情况
            cout << "No" << endl;
            continue;
        }
        for(int i = 1; i <= n; i++){ // Tarjan
            if(dfn[i] == 0){
                tarjan(i);
            }
        }
        for(int i = 0; i < cnt; i++){ // 计算每个强连通分量的出边数量
            if(pos[e[i].from] != pos[e[i].to]){
                out[pos[e[i].from]]++;
            }
        }
        bool flag = 1;
        for(int i = 1; i <= sccs; i++){ // 判断环的大小是不是等于 k
            if(out[i] < 1){
                if(sz[i] != k){
                    flag = 0;
                    break;
                }
            }
        }
        if(flag == 1){ // 输出
            cout << "Yes" << endl;
        }else{
            cout << "No" << endl;
        }
    }
    return 0;
}
```