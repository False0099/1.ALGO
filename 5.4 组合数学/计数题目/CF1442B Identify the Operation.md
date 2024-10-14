# Identify the Operations

## 题面翻译

给你两个数组 $\{a_i\},\{b_i\}$，长度分别为 $n,m$。  
满足  
- $\{a_i\}$ 是大小为 $n$ 的置换（其实就是一个 $1$~$n$ 的排列）  
- $\forall x \in \{b_i\} ,x\in \{a_i \}$。  
- $\{b_i\}$ 中所有元素不重复

你需要进行 $m$ 次操作，每次你要从 $a$ 中选一个下标 $t$，然后选择 $a$ 中下标为 $t+1$ 或者 $t-1$ 的数放在 $c$ 数组的末尾（如果 $a$ 数组存在下标 $t-1$ 或 $t+1$），然后将 $a_t$ 删去，下标 $t$ 后面的数往前移 $1$ 位。  
最后问你有多少种方案可以使 $c=b$

## 题目描述

We start with a permutation $ a_1, a_2, \ldots, a_n $ and with an empty array $ b $ . We apply the following operation $ k $ times.

On the $ i $ -th iteration, we select an index $ t_i $ ( $ 1 \le t_i \le n-i+1 $ ), remove $ a_{t_i} $ from the array, and append one of the numbers $ a_{t_i-1} $ or $ a_{t_i+1} $ (if $ t_i-1 $ or $ t_i+1 $ are within the array bounds) to the right end of the array $ b $ . Then we move elements $ a_{t_i+1}, \ldots, a_n $ to the left in order to fill in the empty space.

You are given the initial permutation $ a_1, a_2, \ldots, a_n $ and the resulting array $ b_1, b_2, \ldots, b_k $ . All elements of an array $ b $ are distinct. Calculate the number of possible sequences of indices $ t_1, t_2, \ldots, t_k $ modulo $ 998\, 244\, 353 $ .

## 输入格式

Each test contains multiple test cases. The first line contains an integer $ t $ ( $ 1 \le t \le 100\, 000 $ ), denoting the number of test cases, followed by a description of the test cases.

The first line of each test case contains two integers $ n, k $ ( $ 1 \le k < n \le 200\, 000 $ ): sizes of arrays $ a $ and $ b $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ): elements of $ a $ . All elements of $ a $ are distinct.

The third line of each test case contains $ k $ integers $ b_1, b_2, \ldots, b_k $ ( $ 1 \le b_i \le n $ ): elements of $ b $ . All elements of $ b $ are distinct.

The sum of all $ n $ among all test cases is guaranteed to not exceed $ 200\, 000 $ .

## 输出格式

For each test case print one integer: the number of possible sequences modulo $ 998\, 244\, 353 $ .

## 样例 #1

### 样例输入 #1

```
3
5 3
1 2 3 4 5
3 2 5
4 3
4 3 2 1
4 3 1
7 4
1 4 7 3 6 2 5
3 2 4 5
```

### 样例输出 #1

```
2
0
4
```

## 提示

$ \require{cancel} $

Let's denote as $ a_1 a_2 \ldots \cancel{a_i} \underline{a_{i+1}} \ldots a_n \rightarrow a_1 a_2 \ldots a_{i-1} a_{i+1} \ldots a_{n-1} $ an operation over an element with index $ i $ : removal of element $ a_i $ from array $ a $ and appending element $ a_{i+1} $ to array $ b $ .

In the first example test, the following two options can be used to produce the given array $ b $ :

- $ 1 2 \underline{3} \cancel{4} 5 \rightarrow 1 \underline{2} \cancel{3} 5 \rightarrow 1 \cancel{2} \underline{5} \rightarrow 1 2 $ ; $ (t_1, t_2, t_3) = (4, 3, 2) $ ;
- $ 1 2 \underline{3} \cancel{4} 5 \rightarrow \cancel{1} \underline{2} 3 5 \rightarrow 2 \cancel{3} \underline{5} \rightarrow 1 5 $ ; $ (t_1, t_2, t_3) = (4, 1, 2) $ .

In the second example test, it is impossible to achieve the given array no matter the operations used. That's because, on the first application, we removed the element next to $ 4 $ , namely number $ 3 $ , which means that it couldn't be added to array $ b $ on the second step.

In the third example test, there are four options to achieve the given array $ b $ :

- $ 1 4 \cancel{7} \underline{3} 6 2 5 \rightarrow 1 4 3 \cancel{6} \underline{2} 5 \rightarrow \cancel{1} \underline{4} 3 2 5 \rightarrow 4 3 \cancel{2} \underline{5} \rightarrow 4 3 5 $ ;
- $ 1 4 \cancel{7} \underline{3} 6 2 5 \rightarrow 1 4 3 \cancel{6} \underline{2} 5 \rightarrow 1 \underline{4} \cancel{3} 2 5 \rightarrow 1 4 \cancel{2} \underline{5} \rightarrow 1 4 5 $ ;
- $ 1 4 7 \underline{3} \cancel{6} 2 5 \rightarrow 1 4 7 \cancel{3} \underline{2} 5 \rightarrow \cancel{1} \underline{4} 7 2 5 \rightarrow 4 7 \cancel{2} \underline{5} \rightarrow 4 7 5 $ ;
- $ 1 4 7 \underline{3} \cancel{6} 2 5 \rightarrow 1 4 7 \cancel{3} \underline{2} 5 \rightarrow 1 \underline{4} \cancel{7} 2 5 \rightarrow 1 4 \cancel{2} \underline{5} \rightarrow 1 4 5 $ ;

## 题解
直觉告诉我们，本题我们的可选的方案并不多，要不扇左边要不删右边，斌给我们删除左边或者删除右边之后，我们队我们的后续答案是没有影响的。于是，我们就可以通过计算我们在某一个位置删除的个数是多少来完成本题。也就是我们只需要判断我们在这个位置可以操作的次数是 1，2，0. 然后乘起来就是最终答案。

```
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
const int mod=998244353;
void solve(){
    int n,m;
    cin>>n>>m;
    map<int,int> pref;
    map<int,int> nxt;
    vector<int> a(n+1,0);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        pref[a[i]]=a[i-1];
        nxt[a[i-1]]=a[i];
    }
    nxt[a[n]]=INF;
    pref[INF]=a[n];
    set<int> st;
    vector<int> b(m+1);
    for(int i=1;i<=m;i++){
        cin>>b[i];
        st.insert(b[i]);
    }
    st.insert(0);
    st.insert(INF);
    int res=1;
    for(int i=1;i<=m;i++){
        int prev_num=pref[b[i]];
        int nxt_num=nxt[b[i]];
       // cerr<<b[i]<<" "<<prev_num<<" "<<nxt_num<<endl;
        int cnt=0;
        if(!st.count(prev_num)){
            cnt++;
        }
        if(!st.count(nxt_num)){
            cnt++;
        }
        if(cnt==0){
            cout<<0<<endl;
            return;
        }else{
            res=(res*cnt)%mod;
            nxt[prev_num]=nxt_num;
            pref[nxt_num]=prev_num;
            st.erase(b[i]);
        }
        //cerr<<cnt<<endl;
    }
    cout<<res<<endl;
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