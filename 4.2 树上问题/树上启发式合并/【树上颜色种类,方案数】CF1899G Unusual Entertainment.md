# Unusual Entertainment

## 题面翻译

给定 $n$ 个结点的，以 $1$ 为根，编号在 $1 \dots n$ 的树。并给定排列 $p$。

$q$ 次询问每次给定 $l,\,r,\,x$，你需要回答是否存在编号在 $p_l,\,p_{l+1},\,\dots ,\, p_{r}$ 中的结点，使得其是 $x$ 的后代。

## 题目描述

A tree is a connected graph without cycles.

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [5, 1, 3, 2, 4] $ is a permutation, but $ [2, 1, 1] $ is not a permutation (as $ 1 $ appears twice in the array) and $ [1, 3, 2, 5] $ is also not a permutation (as $ n = 4 $ , but $ 5 $ is present in the array).

After a failed shoot in the BrMeast video, Alex fell into depression. Even his birthday did not make him happy. However, after receiving a gift from Timofey, Alex's mood suddenly improved. Now he spent days playing with the gifted constructor. Recently, he came up with an unusual entertainment.

Alex builds a tree from his constructor, consisting of $ n $ vertices numbered from $ 1 $ to $ n $ , with the root at vertex $ 1 $ . Then he writes down each integer from $ 1 $ to $ n $ in some order, obtaining a permutation $ p $ . After that, Alex comes up with $ q $ triples of integers $ l, r, x $ . For each triple, he tries to determine if there is at least one descendant of vertex $ x $ among the vertices $ p_l, p_{l+1}, \ldots, p_r $ .

A vertex $ u $ is a descendant of vertex $ v $ if and only if $ \mathrm{dist}(1, v) + \mathrm{dist}(v, u) = \mathrm{dist}(1, u) $ , where $ \mathrm{dist}(a, b) $ is the distance between vertices $ a $ and $ b $ . In other words, vertex $ v $ must be on the path from the root to vertex $ u $ .

Alex told Zakhar about this entertainment. Now Alex tells his friend $ q $ triples as described above, hoping that Zakhar can check for the presence of a descendant. Zakhar is very sleepy, so he turned to you for help. Help Zakhar answer all of Alex's questions and finally go to sleep.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n, q $ ( $ 1 \le n, q \le 10^5 $ ) — the number of vertices in the tree and the number of questions, respectively.

Each of the next $ n - 1 $ lines contains two integers $ u_i $ and $ v_i $ ( $ 1 \le u_i, v_i \le n $ ), indicating that there is an edge between vertices $ u_i $ and $ v_i $ (it is guaranteed that the resulting graph is a tree).

The next line contains $ n $ integers $ p_1, p_2, \dots, p_n $ ( $ 1 \le p_i \le n $ ) — the permutation $ p $ (it is guaranteed that each integer from $ 1 $ to $ n $ appears exactly once).

Then follow $ q $ lines describing Alex's questions. The $ i $ -th line contains three integers $ l, r, x $ ( $ 1 \le l \le r \le n $ , $ 1 \le x \le n $ ), as described in the statement.

It is guaranteed that the sum of $ n $ and the sum of $ q $ over all test cases do not exceed $ 10^5 $ .

## 输出格式

For each of Alex's questions, print "Yes" (without quotes) if the described descendant exists, otherwise print "No" (without quotes).

You can output the answer in any case (for example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as a positive answer).

## 样例 #1

### 样例输入 #1

```
3
3 5
1 2
2 3
1 2 3
1 2 2
1 2 3
2 3 1
1 2 3
2 3 3
10 10
2 6
2 7
2 4
1 7
2 8
10 6
8 5
9 4
3 4
10 2 5 9 1 7 6 4 3 8
8 9 8
7 8 1
7 10 6
4 8 9
5 5 10
7 10 1
9 9 2
9 10 6
6 6 2
10 10 6
1 1
1
1 1 1
```

### 样例输出 #1

```
YES
NO
YES
NO
YES

NO
YES
YES
YES
NO
YES
YES
NO
NO
NO

YES
```


## 题解
我们考虑对于每一个结点开一个 set 统计有哪些元素已经出现过，合并的时候，我们可以采用我们的启发式合并，时间复杂度预测为：$o(n\log n)$ 

然后对于每一个询问，我们只需要去我们的树上去搜索我们是否存在对应的元素在我们的序列中，我们可以二分查找我们的比右端点大的第一个数，然后拿这个数和我们的左侧比较即可
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef tuple<int,int,int> tpi;
int main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int n,q; cin>>n>>q;
    vector<pii> e(n-1);
    for(auto &[u,v]:e)cin>>u>>v; // 提前存边
    vector<int> p(n+1);
    for(int i=0;i<n;i++){
      int x; cin>>x; p[x]=i;
    } // 建立映射
    vector<vector<int> > g(n);
    for(auto &[u,v]:e){
      g[p[u]].emplace_back(p[v]);
      g[p[v]].emplace_back(p[u]);
    } // 建树
    vector<vector<tpi> > w(n);
    vector<bool> b(q);
    for(int i=0;i<q;i++){
      int l,r,x; cin>>l>>r>>x;
      w[p[x]].emplace_back(l-1,r-1,i);
    } // 离线所有询问
    vector<set<int> > s(n);
    function<void(int,int)> dfs=[&](int u,int f){
      int h=u; // h 是重儿子
      for(int i:g[u])
        if(i!=f)if(dfs(i,u);s[i].size()>s[h].size())h=i;
      if(h!=u)s[u].swap(s[h]); // 把重儿子的翻上来
      for(int i:g[u])
        if(i!=f&&i!=h)s[u].merge(s[i]); // 暴力合并
      s[u].emplace(u); // 加进它本身
      for(auto [l,r,i]:w[u])
        if(auto p=s[u].lower_bound(l);p!=s[u].end()&&*p<=r)b[i]=true;
        // 使用 lower_bound 进行二分查找
    };
    dfs(p[1],p[1]); // 注意此时的根是 p[1]！
    for(bool i:b)cout<<(i?"Yes\n":"No\n");
  }
  return 0;
}
```
```