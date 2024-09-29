# Array Optimization by Deque

## 题面翻译

给你一个序列 $a$ 和一个双端队列。

你需要**按顺序**操作 $a_i$ ，具体地，每一次操作是把 $a_i$ 从双端队列的队头或者队尾入队。

求把 $a$ 中所有的元素都入队之后，双端队列中逆序对数量的最小值。

测试包含多组数据，对于每一组数据，输出一个数，表示你的答案。

## 题目描述

In fact, the problems E 1 and E 2 do not have much in common. You should probably think of them as two separate problems.

You are given an integer array $ a[1 \ldots n] = [a_1, a_2, \ldots, a_n] $ .

Let us consider an empty [deque](https://tinyurl.com/pfeucbux) (double-ended queue). A deque is a data structure that supports adding elements to both the beginning and the end. So, if there are elements $ [3, 4, 4] $ currently in the deque, adding an element $ 1 $ to the beginning will produce the sequence $ [\color{red}{1}, 3, 4, 4] $ , and adding the same element to the end will produce $ [3, 4, 4, \color{red}{1}] $ .

The elements of the array are sequentially added to the initially empty deque, starting with $ a_1 $ and finishing with $ a_n $ . Before adding each element to the deque, you may choose whether to add it to the beginning or to the end.

For example, if we consider an array $ a = [3, 7, 5, 5] $ , one of the possible sequences of actions looks like this:

 $ \quad $ 1. Add $ 3 $ to the beginning of the deque: deque has a sequence $ [\color{red}{3}] $ in it; $ \quad $ 2. Add $ 7 $ to the end of the deque: deque has a sequence $ [3, \color{red}{7}] $ in it; $ \quad $ 3. Add $ 5 $ to the end of the deque: deque has a sequence $ [3, 7, \color{red}{5}] $ in it; $ \quad $ 4. Add $ 5 $ to the beginning of the deque: deque has a sequence $ [\color{red}{5}, 3, 7, 5] $ in it; Find the minimal possible number of inversions in the deque after the whole array is processed.

An inversion in sequence $ d $ is a pair of indices $ (i, j) $ such that $ i < j $ and $ d_i > d_j $ . For example, the array $ d = [5, 3, 7, 5] $ has exactly two inversions — $ (1, 2) $ and $ (3, 4) $ , since $ d_1 = 5 > 3 = d_2 $ and $ d_3 = 7 > 5 = d_4 $ .

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The next $ 2 t $ lines contain descriptions of the test cases.

The first line of each test case description contains an integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — array size. The second line of the description contains $ n $ space-separated integers $ a_i $ ( $ -10^9 \le a_i \le 10^9 $ ) — elements of the array.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

Print $ t $ lines, each line containing the answer to the corresponding test case. The answer to a test case should be a single integer — the minimal possible number of inversions in the deque after executing the described algorithm.

## 样例 #1

### 样例输入 #1

```
6
4
3 7 5 5
3
3 2 1
3
3 1 2
4
-1 2 2 -1
4
4 5 1 3
5
1 3 1 3 2
```

### 样例输出 #1

```
2
0
1
0
1
2
```

## 提示

One of the ways to get the sequence $ [5, 3, 7, 5] $ in the deque, containing only two inversions, from the initial array $ [3, 7, 5, 5] $ (the first sample test case) is described in the problem statement.

Also, in this example, you could get the answer of two inversions by simply putting each element of the original array at the end of the deque. In this case, the original sequence $ [3, 7, 5, 5] $ , also containing exactly two inversions, will be in the deque as-is.

## 题解
本题是我们的最左最有贪心，我们显然知道，我们到最后的最后，我们的逆序对之和是不变的，于是我们考虑**尽可能的让我们的每一步得到的逆序对都尽可能的少**。

于是，我们就可以枚举我们每一次是选择我们的头部好还是选择我们的尾部好，每一次**贪心的选择堆笑地那一个**，让我们的答案最小。
```
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
struct akldsjf{
    vector<int> lsh;
    void push(int x){
        lsh.push_back(x);
    }
    void init(){
        sort(begin(lsh),end(lsh));
        lsh.erase(unique(begin(lsh),end(lsh)));
    }
    int get_rank(int x){
        return lower_bound(begin(lsh),end(lsh),x)-begin(lsh)+1;
    }
    int get_num(int x){
        return lsh[x-1];
    }
    void clear(){
        lsh.clear();
    }
}discret;
void solve(){
    int n;
    cin>>n;
    discret.clear();
    deque<int> dq;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        discret.push(a[i]);
    }
    discret.init();
    Fenwick<int> tr(n+1);
    int sum_num=0;
    int tot=0;
    int ans=0;
    for(int i=1;i<=n;i++){
        int bigger_of_i=tot-tr.ask(discret.get_rank(a[i]));
        int smaller_of_i=tr.ask(discret.get_rank(a[i])-1);
        tr.add(discret.get_rank(a[i]),1);
        ans+=min(bigger_of_i,smaller_of_i);
        tot++;
    }
    cout<<ans<<endl;
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