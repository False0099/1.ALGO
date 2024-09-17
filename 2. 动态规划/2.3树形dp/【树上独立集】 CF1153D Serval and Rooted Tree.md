# Serval and Rooted Tree

## 题面翻译

N 个节点以 1 为根的一棵树，每个非叶子节点都有一个操作 max 或 min（0 表示 min，1 表示 max），表示这个节点中的值应该分别等于其子节点中所有值的最大值或最小值。假设树上有 k 个叶节点，你可以将每个叶节点填上[1, k]的数字，且每个数字只使用一次，求根节点的最大值

## 题目描述

Now Serval is a junior high school student in Japari Middle School, and he is still thrilled on math as before.

As a talented boy in mathematics, he likes to play with numbers. This time, he wants to play with numbers on a rooted tree.

A tree is a connected graph without cycles. A rooted tree has a special vertex called the root. A parent of a node $ v $ is the last different from $ v $ vertex on the path from the root to the vertex $ v $ . Children of vertex $ v $ are all nodes for which $ v $ is the parent. A vertex is a leaf if it has no children.

The rooted tree Serval owns has $ n $ nodes, node $ 1 $ is the root. Serval will write some numbers into all nodes of the tree. However, there are some restrictions. Each of the nodes except leaves has an operation $ \max $ or $ \min $ written in it, indicating that the number in this node should be equal to the maximum or minimum of all the numbers in its sons, respectively.

Assume that there are $ k $ leaves in the tree. Serval wants to put integers $ 1, 2, \ldots, k $ to the $ k $ leaves (each number should be used exactly once). He loves large numbers, so he wants to maximize the number in the root. As his best friend, can you help him?

## 输入格式

The first line contains an integer $ n $ ( $ 2 \leq n \leq 3\cdot 10^5 $ ), the size of the tree.

The second line contains $ n $ integers, the $ i $ -th of them represents the operation in the node $ i $ . $ 0 $ represents $ \min $ and $ 1 $ represents $ \max $ . If the node is a leaf, there is still a number of $ 0 $ or $ 1 $ , but you can ignore it.

The third line contains $ n-1 $ integers $ f_2, f_3, \ldots, f_n $ ( $ 1 \leq f_i \leq i-1 $ ), where $ f_i $ represents the parent of the node $ i $ .

## 输出格式

Output one integer — the maximum possible number in the root of the tree.

## 样例 #1

### 样例输入 #1

```
6
1 0 1 1 0 1
1 2 2 2 2
```

### 样例输出 #1

```
1
```

## 样例 #2

### 样例输入 #2

```
5
1 0 1 0 1
1 1 1 1
```

### 样例输出 #2

```
4
```

## 样例 #3

### 样例输入 #3

```
8
1 0 0 1 0 1 1 0
1 1 2 2 3 3 3
```

### 样例输出 #3

```
4
```

## 样例 #4

### 样例输入 #4

```
9
1 1 0 0 1 0 1 0 1
1 1 2 2 3 3 4 4
```

### 样例输出 #4

```
5
```

## 提示

Pictures below explain the examples. The numbers written in the middle of the nodes are their indices, and the numbers written on the top are the numbers written in the nodes.

In the first example, no matter how you arrange the numbers, the answer is $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1153D/6708db6b93ae87595a2a5e6a14824b45296d26be.png)In the second example, no matter how you arrange the numbers, the answer is $ 4 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1153D/55298e44ca1267165e9d58705a4fc29c70e74b01.png)In the third example, one of the best solution to achieve $ 4 $ is to arrange $ 4 $ and $ 5 $ to nodes $ 4 $ and $ 5 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1153D/13208157ec6652f71e197305f666d97c9ee17111.png)In the fourth example, the best solution is to arrange $ 5 $ to node $ 5 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1153D/7e271f8f21b87048c8998b0ecd2a589e99082246.png)
 ## 题解
我们考虑维护一个 $dp[i]$ 表示 i 节点能够获得的最低排名是多少，然后我们就可以根据我们的方程进行转移，如果我们的对应的操作是取最大，那么我们的 $dp[i]$ 就是我们子树的最小值，如果我们的操作是取最小，那么我们的 $dp[i]$ 就是就是我们子树大小之和。




```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=3e5+10,imax=INT_MAX;

int n,h[N],a[N],ne[N<<1],e[N<<1],idx,f[N],res;

void add(int u,int v) {ne[++idx]=h[u],e[idx]=v,h[u]=idx;}

void dfs(int u,int father)

{

    int tot=0; if(a[u] == 1) f[u]=imax;

    for(int i=h[u];~i;i=ne[i])

    {

        int j=e[i];

        if(j == father) continue ;

        tot++; dfs(j,u);

        if(! a[u]) f[u]+=f[j]; else f[u]=min(f[u],f[j]);        

    }

    if(! tot) res++,f[u]=1;

}

int main()

{

    memset(h,-1,sizeof h); scanf("%d",&n);

    for(int i=1;i<=n;i++) scanf("%d",&a[i]);

    for(int i=2;i<=n;i++)

    {

        int x; scanf("%d",&x);

        add(x,i); add(i,x);

    }

    dfs(1,0);

    printf("%d",res+1-f[1]);

    return 0;

}
```