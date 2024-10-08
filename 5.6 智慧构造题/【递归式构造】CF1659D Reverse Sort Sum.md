# Reverse Sort Sum

## 题面翻译

对于序列 $a$，我们定义 $f(k,a)$ 表示将 $a$ 的前 $k$ 个元素从小到大排序后得到的序列。  
现在我们有一个长度为 $n$ 的 `01` 序列 $A$，我们将根据其进行下列操作：

- 对于 $1\sim n$ 的每个整数 $i$，设序列 $B_i=f(i,A)$。
- 然后设长度为 $n$ 的序列 $C$，满足 $C_{i}=\sum_{j=1}^nB_{j,i}$。

给你 $n$ 和 $C$，你需要构造任意一个长度为 $n$ 的 `01` 序列 $A$，满足我们根据 $A$ 经过上述操作可以得到 $C$。**保证有解**。  
每个测试点包含 $T$ 组数据。

保证：  
$1\leq T\leq10^3;$  
$1\leq n,\sum n\leq2\times10^5;0\leq C_i\leq n;$

## 题目描述

Suppose you had an array $ A $ of $ n $ elements, each of which is $ 0 $ or $ 1 $ .

Let us define a function $ f (k, A) $ which returns another array $ B $ , the result of sorting the first $ k $ elements of $ A $ in non-decreasing order. For example, $ f (4,[0,1,1,0,0,1,0]) = [0,0,1,1,0,1,0] $ . Note that the first $ 4 $ elements were sorted.

Now consider the arrays $ B_1, B_2,\ldots, B_n $ generated by $ f (1, A), f (2, A),\ldots,f (n, A) $ . Let $ C $ be the array obtained by taking the element-wise sum of $ B_1, B_2,\ldots, B_n $ .

For example, let $ A=[0,1,0,1] $ . Then we have $ B_1=[0,1,0,1] $ , $ B_2=[0,1,0,1] $ , $ B_3=[0,0,1,1] $ , $ B_4=[0,0,1,1] $ . Then $ C=B_1+B_2+B_3+B_4=[0,1,0,1]+[0,1,0,1]+[0,0,1,1]+[0,0,1,1]=[0,2,2,4] $ .

You are given $ C $ . Determine a binary array $ A $ that would give $ C $ when processed as above. It is guaranteed that an array $ A $ exists for given $ C $ in the input.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

Each test case has two lines. The first line contains a single integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ).

The second line contains $ n $ integers $ c_1, c_2, \ldots, c_n $ ( $ 0 \leq c_i \leq n $ ). It is guaranteed that a valid array $ A $ exists for the given $ C $ .

The sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single line containing $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ a_i $ is $ 0 $ or $ 1 $ ). If there are multiple answers, you may output any of them.

## 样例 #1

### 样例输入 #1

```
5
4
2 4 2 4
7
0 3 4 2 3 2 7
3
0 0 0
4
0 0 0 4
3
1 2 3
```

### 样例输出 #1

```
1 1 0 1 
0 1 1 0 0 0 1 
0 0 0 
0 0 0 1 
1 0 1
```

## 提示

Here's the explanation for the first test case. Given that $ A=[1,1,0,1] $ , we can construct each $ B_i $ :

- $ B_1=[\color{blue}{1}, 1,0,1] $ ;
- $ B_2=[\color{blue}{1},\color{blue}{1}, 0,1] $ ;
- $ B_3=[\color{blue}{0},\color{blue}{1},\color{blue}{1}, 1] $ ;
- $ B_4=[\color{blue}{0},\color{blue}{1},\color{blue}{1},\color{blue}{1}] $

 And then, we can sum up each column above to get $ C=[1+1+0+0,1+1+1+1,0+0+1+1,1+1+1+1]=[2,4,2,4] $ .

## 题解
本题，我们显然可以通过我们的对应的答案来进行处理，假设我们的最后一位满足 $a[n]=n$,那么我们这一位已定位 1，并且我们前面所有为 1 的部分都要减去 1，之后，我们如果满足 $a[i]\neq n$,那么我们的对应的位置显然为 0.

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
template <typename T>
struct Fenwick {
    int n;
    vector<T> w;

    Fenwick(int n) {
        this->n = n;
        w.resize(n + 1);
    }
    void add(int x, T k) {
        for (; x <= n; x += x & -x) {
            w[x] += k;
        }
    }
    void add(int x, int y, T k) { // 区间修改
        add(x, k), add(y + 1, -k);
    }
    T ask(int x) {  //单点查询
        auto ans = T();
        for (; x; x -= x & -x) {
            ans += w[x];
        }
        return ans;
    }
    T ask(int x, int y) { // 区间查询(区间和)
        return ask(y) - ask(x - 1);
    }
    int kth(T k) { //查找第k大的值
        int ans = 0;
        for (int i = __lg(n); i >= 0; i--) {
            int val = ans + (1 << i);
            if (val < n && w[val] < k) {
                k -= w[val];
                ans = val;
            }
        }
        return ans + 1;
    }
};
void solve(){
    int n;
    cin>>n;
    vector<int> c(n+1);
    vector<int> ans(n+1);
    int sum=0;
    for(int i=1;i<=n;i++){
        cin>>c[i];
        sum+=c[i];
    }    
    sum/=n;
    Fenwick<int> tr(n+1);
    int tot=0;
    for(int i=n;i>=1;i--){
        if(c[i]+tr.ask(i)==i){
            ans[i]=1;
        }else{
            ans[i]=0;
        }
        tr.add(i-sum+1,-1);
        if(ans[i]==1){
            sum--;
        }
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
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