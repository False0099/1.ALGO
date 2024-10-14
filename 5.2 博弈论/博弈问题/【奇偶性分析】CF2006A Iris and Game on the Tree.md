# Iris and Game on the Tree

## 题目描述

Iris has a tree rooted at vertex $ 1 $ . Each vertex has a value of $ \mathtt 0 $ or $ \mathtt 1 $ .

Let's consider a leaf of the tree (the vertex $ 1 $ is never considered a leaf) and define its weight. Construct a string formed by the values of the vertices on the path starting at the root and ending in this leaf. Then the weight of the leaf is the difference between the number of occurrences of $ \mathtt{10} $ and $ \mathtt{01} $ substrings in it.

Take the following tree as an example. Green vertices have a value of $ \mathtt 1 $ while white vertices have a value of $ \mathtt 0 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006A/66d8f9cca162bbc9b7dcbbd0c66de4a705cfbe4e.png)- Let's calculate the weight of the leaf $ 5 $ : the formed string is $ \mathtt{10110} $ . The number of occurrences of substring $ \mathtt{10} $ is $ 2 $ , the number of occurrences of substring $ \mathtt{01} $ is $ 1 $ , so the difference is $ 2 - 1 = 1 $ .
- Let's calculate the weight of the leaf $ 6 $ : the formed string is $ \mathtt{101} $ . The number of occurrences of substring $ \mathtt{10} $ is $ 1 $ , the number of occurrences of substring $ \mathtt{01} $ is $ 1 $ , so the difference is $ 1 - 1 = 0 $ .

The score of a tree is defined as the number of leaves with non-zero weight in the tree.

But the values of some vertices haven't been decided and will be given to you as $ \texttt{?} $ . Filling the blanks would be so boring, so Iris is going to invite Dora to play a game. On each turn, one of the girls chooses any of the remaining vertices with value $ \texttt{?} $ and changes its value to $ \mathtt{0} $ or $ \mathtt{1} $ , with Iris going first. The game continues until there are no vertices with value $ \mathtt{?} $ left in the tree. Iris aims to maximize the score of the tree, while Dora aims to minimize that.

Assuming that both girls play optimally, please determine the final score of the tree.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 5\cdot 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \leq n \leq 10^5 $ ) — the number of vertices in the tree.

The following $ n - 1 $ lines each contain two integers $ u $ and $ v $ ( $ 1 \leq u, v \leq n $ ) — denoting an edge between vertices $ u $ and $ v $ .

It's guaranteed that the given edges form a tree.

The last line contains a string $ s $ of length $ n $ . The $ i $ -th character of $ s $ represents the value of vertex $ i $ . It's guaranteed that $ s $ only contains characters $ \mathtt{0} $ , $ \mathtt{1} $ and $ \mathtt{?} $ .

It is guaranteed that the sum of $ n $ over all test cases doesn't exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the final score of the tree.

## 样例 #1

### 样例输入 #1

```
6
4
1 2
1 3
4 1
0101
4
1 2
3 2
2 4
???0
5
1 2
1 3
2 4
2 5
?1?01
6
1 2
2 3
3 4
5 3
3 6
?0????
5
1 2
1 3
1 4
1 5
11?1?
2
2 1
??
```

### 样例输出 #1

```
2
1
1
2
1
0
```

## 提示

In the first test case, all the values of the vertices have been determined. There are three different paths from the root to a leaf:

- From vertex $ 1 $ to vertex $ 2 $ . The string formed by the path is $ \mathtt{01} $ , so the weight of the leaf is $ 0-1=-1 $ .
- From vertex $ 1 $ to vertex $ 3 $ . The string formed by the path is $ \mathtt{00} $ , so the weight of the leaf is $ 0-0=0 $ .
- From vertex $ 1 $ to vertex $ 4 $ . The string formed by the path is $ \mathtt{01} $ , so the weight of the leaf is $ 0-1=-1 $ .

Thus, there are two leaves with non-zero weight, so the score of the tree is $ 2 $ .

In the second test case, one of the sequences of optimal choices for the two players can be:

- Iris chooses to change the value of the vertex $ 3 $ to $ \mathtt 1 $ .
- Dora chooses to change the value of the vertex $ 1 $ to $ \mathtt 0 $ .
- Iris chooses to change the value of the vertex $ 2 $ to $ \mathtt 0 $ .

The final tree is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006A/0fb84e35a945cc0b24925c452b0b7ffb5379f599.png)The only leaf with non-zero weight is $ 3 $ , so the score of the tree is $ 1 $ . Note that this may not be the only sequence of optimal choices for Iris and Dora.
## 题解
本题可以通过结论知道，最后一个叶子节点对应的路径对答案的贡献是否为 1，只由叶子节点和根节点的颜色是否相同决定，如果相同，那么我们的答案为 1，否则为 0. 于是，决策很显然，我们可以通过根节点的颜色是否确定来计算，如果我们的根节点的颜色确定了，那么我们只需要抢叶子节点即可。

否则，我们肯定是根据我们当前的叶子节点中的所有元素个数和来确定我们应该让我们的根节点染什么颜色。先手玩家一定是选择一个颜色最大的来进行处理，否则如果我们的两个颜色相同，我们就可以通过我们的 x 之间的结点有多少个结点，如果是奇数个，那么我们就可以让沃恩的最后的元素加一下。如果我们的叶子节点中我们的所有的元素都是最大的，
```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
const int N=1e5+10;
int sured_[N];
int f[N][2];
int din[N];
void solve(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        din[i]=0;
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        din[u]++;
        din[v]++;   
    }
    string s;
    cin>>s;
    s=" "+s;
    int zeros_=0;
    int ones_=0;
    int ask_=0;
    int x=0;
    for(int i=2;i<=n;i++){
        if(din[i]!=1){
            x+=(s[i]=='?');
            continue;
        }
        zeros_+=(s[i]=='0');
        ones_+=(s[i]=='1');
        ask_+=(s[i]=='?');
    }
    int ans=0;
    if(s[1]=='0'){
        ans+=ones_+(ask_+1)/2;
        //cout<<ans<<endl;
    }else if(s[1]=='1'){
        ans+=zeros_+(ask_+1)/2;
    }else if(zeros_!=ones_){
        ans = max(ones_, zeros_) + ask_ / 2;
    }else{
        ans=zeros_+(ask_+x%2)/2;
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