## 题意：

给你 n 个数列，每一次你可以选择一个数列，把当前的数修改为 $mex(x,a_{1},\dots a_{li})$。现在问你，将 $0-m$ 分别作为初始值时，我们变化后最大值的和时多少。（每个操作只能使用一次）

**The two versions are different problems. In this version of the problem, you can't choose the same integer twice or more. You can make hacks only if both versions are solved.**

One day, Turtle was playing with $n$ sequences. Let the length of the $i$ \-th sequence be $l_i$. Then the $i$ \-th sequence was $a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i}$.

Piggy gave Turtle a problem to solve when Turtle was playing. The statement of the problem was:

-   There was a non-negative integer $x$ at first. Turtle would perform an arbitrary number (possibly zero) of operations on the integer.
-   In each operation, Turtle could choose an integer $i$ such that $1 \le i \le n$ and **$i$ wasn't chosen before**, and set $x$ to $\text{mex}^{\dagger}(x, a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i})$.
-   Turtle was asked to find the answer, which was the **maximum** value of $x$ after performing an arbitrary number of operations.

Turtle solved the above problem without difficulty. He defined $f(k)$ as the answer to the above problem when the initial value of $x$ was $k$.

Then Piggy gave Turtle a non-negative integer $m$ and asked Turtle to find the value of $\sum\limits_{i = 0}^m f(i)$ (i.e., the value of $f(0) + f(1) + \ldots + f(m)$). Unfortunately, he couldn't solve this problem. Please help him!

$^{\dagger}\text{mex}(c_1, c_2, \ldots, c_k)$ is defined as the smallest **non-negative** integer $x$ which does not occur in the sequence $c$. For example, $\text{mex}(2, 2, 0, 3)$ is $1$, $\text{mex}(1, 2)$ is $0$.

**Input**

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.

The first line of each test case contains two integers $n, m$ ($1 \le n \le 2 \cdot 10^5, 0 \le m \le 10^9$).

Each of the following $n$ lines contains several integers. The first integer $l_i$ ($1 \le l_i \le 2 \cdot 10^5$) represents the length of the $i$ \-th sequence, and the following $l_i$ integers $a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i}$ ($0 \le a_{i, j} \le 10^9$) represent the elements of the $i$ \-th sequence.

**Output**

For each test case, output a single integer — the value of $\sum\limits_{i = 0}^m f(i)$.


It is guaranteed that the sum of $n$ over all test cases does not exceed $2 \cdot 10^5$ and the sum of $\sum l_i$ over all test cases does not exceed $2 \cdot 10^5$.

## 题解
我们首先考虑每一次操作对于我们的 $x$ 的贡献，我们可以分类讨论，如果我们的 $x$ 和我们的对应数列的 $mex$ 相等，那么我们 x 最后一定会变大，而这个变大后的值，我们也可以通过我们的**预处理计算得到**。

当然，如果我们的 $x$ 不等于我们的 $mex$，那么我们一定有答案：变为我们的 mex。

根据上面的两个信息，我们理论上显然可以建图，但是建图的时间复杂度为 $o(mn)$,显然无法接收，我们考虑只对我们的**基本图进行处理**。也就是只考虑两个数之间的连边。

我们这个时候，显然我们可以得到一个**拓扑图**，我们的每一个点能够通过**一次操作到达的最大点**显然就是这个**拓扑图中和他联通的，数值最大的点**。

我们还有一个比较显然的变大的方法，就是让我们的**一个数字编程当前的所有数字当前的最大的 mex**。

于是，我们就可以比较上面的三个元素：本身，所有当前的最大的 mex，拓扑图中连通的 mex。

但是我们其实是**漏了一种情况的**，我们漏的情况：我们如果有一个 mex 同时出现了两次，我们可以断言一定存在一种构造，首先把我们的 x 变成这一个数，然后再让我们的数字变成上满的三种情况。

于是，我们就可以进行我们的分类讨论来进行。

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
void solve(){
    int n,m;
    map<int,vector<int>> edge;
    map<int,int> dout;
    unordered_set<int> point;
    map<int,int> ans_of_i;
    //vector<int> vis(n+1,0);
    cin>>n>>m;
    vector<int> mex_of_arr(n);
    set<int> baodi;
    set<int> in;
    int maxx=-1;
    int max_range=-1;
    for(int i=0;i<n;i++){
        int l;
        cin>>l;
        unordered_set<int> st;
        for(int j=0;j<l;j++){
            int u;
            cin>>u;
            st.insert(u);
        }
        int from=-1;
        int to=-1;
        for(int k=0;;k++){
            if(st.count(k)==false&&from==-1){
                from=k;
            }else if(st.count(k)==false&&from!=-1){
                to=k;
                break;
            }
        }
        maxx=max(maxx,from);
        max_range=max(max_range,to);
        if(in.count(from)){
            baodi.insert(from);
        }
        in.insert(from);

        point.insert(from);
        point.insert(to);
        edge[to].push_back(from);
        dout[from]++;
    }   
    queue<int> q;
    for(auto u:point){
        if(dout.count(u)==false||dout[u]==0){
            ans_of_i[u]=u;
            q.push(u);
        }
    }
    //cerr<<endl;
    while(q.size()){
        auto u=q.front();
        q.pop();
        //cerr<<u<<endl;
        for(auto v:edge[u]){
            dout[v]--;
            ans_of_i[v]=max(ans_of_i[u],ans_of_i[v]);
            ans_of_i[u]=max(ans_of_i[u],ans_of_i[v]);
            if(dout[v]==0){
                q.push(v);
            }
        }
    }
    int tot=(m)*(m+1)/2;
    //cerr<<tot<<endl;
    int max_change=-1;
    for(auto u:baodi){
        max_change=max(max_change,ans_of_i[u]);
    }
    cerr<<max_change<<endl;
//    cerr<<min(max_range,m)<<" "<<min(maxx,m)<<endl;
    for(int i=0;i<=min(max_range,m);i++){
        tot-=i;
        tot+=max({maxx,ans_of_i[i],max_change,i});
        cerr<<i<<" "<<max({maxx,ans_of_i[i],max_change})<<endl;
    }
    cerr<<endl;
    cout<<tot<<endl;
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
    cin>>t;
    init();
    while(t--){
        solve();
    }
}
```