

Chaneka writes down an array $a$ of $n$ positive integer elements. Initially, all elements are not circled. In one operation, Chaneka can circle an element. It is possible to circle the same element more than once.

After doing all operations, Chaneka makes a sequence $r$ consisting of all **uncircled** elements of $a$ following the order of their indices.

Chaneka also makes another sequence $p$ such that its length is equal to the number of operations performed and $p_i$ is the **index** of the element that is circled in the $i$ \-th operation.

Chaneka wants to do several operations such that sequence $r$ is equal to sequence $p$. Help her achieve this, or report if it is impossible! Note that if there are multiple solutions, you can print any of them.

翻译：
Chaneka 写下了一个由 $n$ 个正整数元素组成的数组 $a$。最初，所有元素都没有圈起来。在一次操作中，Chaneka 可以圈出一个元素。同一元素可以圈定多次。

完成所有操作后，Chaneka 按照索引顺序，将 $a$ 中所有未被圈出的***元素组成一个序列 $r$。

Chaneka 还制作了另一个序列 $p$，其长度等于所执行的操作次数，并且 $p_i$ 是在 $i$ \-th 操作中被圈出的元素的**索引**。

Chaneka 希望进行若干次操作，使序列 $r$ 等于序列 $p$。请帮助她实现这个目标，如果不可能，请报告！请注意，如果有多个解决方案，您可以打印其中任何一个。

**Input**

The first line contains a single integer $n$ ($1 \leq n \leq 2\cdot10^5$) — the size of array $a$.

The second line contains $n$ integers $a_1,a_2,a_3,\ldots,a_n$ ($1\leq a_i\leq n$).

 **Output**

A single line containing $-1$ if it is impossible.

Otherwise, the output consists of two lines. The first line contains an integer $z$ representing the number of operations performed. The second line contains $z$ integers, the $i$ \-th integer represents the index of the element circled in the $i$ \-th operation. If there are multiple solutions, you can print any of them.

## 题解
显然我们的答案一定是数组 a 的一个子序列
那么我们考虑每一个 $a_{i}$ 是否留下
如果留下 $a_{i}$,那么 $a_{a_{i}}$ 一定会被删去，否则有可能留下来。我们于是可以对于每一个 i 向 $a_{i}$ 连一条有向边，表示我们可以通过留下位置 i 来达到删去位置 $a_{i}$ 的目的：
对于我们连边剪出来的图，有 n 个节点，n 条有向边，那么显然，我们有且只有一个环。

于是我们可以进行分类讨论：
如果图中存在入度为 0 的点，那么这些节点的 $a_{i}$ 是无法被删去的，那么我们就必须保留；
如果我们一定要留下 $i$,那么 $a_{i}$ 就要被删去了。而一旦这个被删去，那么我们就不能够通过留下 $a_{i}$ 而删去 $a_{a_{i}}$,因此，我们要断开这条边，

因此，我们可以用拓扑排序来处理上述情况，直到图中不存在入读为 0 的点。
```cpp
ll n,a[200005],in[200005],vis[200005],flag;
queue<ll> q;
inline void solve(){
    //处理入度为0的点
    while(q.size()){
        ll u=q.front();q.pop();
        if(vis[u]==-1||vis[a[u]]==1)flag=1;//同时标记为留下和删去说明无解
        vis[u]=1;//标记为留下
        if(vis[a[u]]==-1)continue;
        vis[a[u]]=-1;//标记为删去
        if(--in[a[a[u]]]==0)q.push(a[a[u]]);
    }
}
inline void qfl_zzz(){
    n=read();
    for(ll i=1;i<=n;++i)a[i]=read(),in[a[i]]++;
    while(1){
        for(ll i=1;i<=n;++i)
            if(in[i]==0&&vis[i]==0)q.push(i);
        if(q.size()==0){
            for(ll i=1;i<=n;++i)
                if(vis[i]==0)q.push(i),solve();
            break;
        }
        else solve();
    }
    vector<ll> ans;
    for(ll i=1;i<=n;++i)
        if(vis[i]==1)ans.push_back(a[i]);
    if(flag){
        writen(-1);
        return;
    }
    writen(ans.size());
    for(ll x:ans)writet(x);
}
```