#特殊限制 #贪心 #元素种类固定
# Set Construction

## 题面翻译

### 题目描述
给你一个 $n\times n$ 的矩阵 $b$。

你需要构造 $n$ 个集合，集合里出现的数只能是 $1\sim n$。


若 $b_{i,j}=1$，则说明集合 $i$ 是集合 $j$ 的子集。否则说明集合 $i$ 不是集合 $j$ 的子集。

数据保证有解，你需要构造出这 $n$ 个集合。
### 输入格式
第一行一个数字 $t(t\le 1000)$，说明有 $t$ 组数据。

对于每组数据，第一行一个数 $n(n\le 100)$。  
第 $2\sim n+1$ 行每行 $n$ 个数为矩阵 $b$。
### 输出格式
对于每组数据，输出 $n$ 行。  
每一行的先输出该集合的元素数量，再输出该集合的元素。

## 题目描述

You are given a binary matrix $ b $ (all elements of the matrix are $ 0 $ or $ 1 $ ) of $ n $ rows and $ n $ columns.

You need to construct a $ n $ sets $ A_1, A_2, \ldots, A_n $ , for which the following conditions are satisfied:

- Each set is nonempty and consists of distinct integers between $ 1 $ and $ n $ inclusive.
- All sets are distinct.
- For all pairs $ (i, j) $ satisfying $ 1\leq i, j\leq n $ , $ b_{i, j}=1 $ if and only if $ A_i\subsetneq A_j $ . In other words, $ b_{i, j} $ is $ 1 $ if $ A_i $ is a proper subset of $ A_j $ and $ 0 $ otherwise.

Set $ X $ is a proper subset of set $ Y $ , if $ X $ is a nonempty subset of $ Y $ , and $ X \neq Y $ .

It's guaranteed that for all test cases in this problem, such $ n $ sets exist. Note that it doesn't mean that such $ n $ sets exist for all possible inputs.

If there are multiple solutions, you can output any of them.

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1\le t\le 1000 $ ) — the number of test cases. The description of test cases follows.

The first line contains a single integer $ n $ ( $ 1\le n\le 100 $ ).

The following $ n $ lines contain a binary matrix $ b $ , the $ j $ -th character of $ i $ -th line denotes $ b_{i, j} $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 1000 $ .

It's guaranteed that for all test cases in this problem, such $ n $ sets exist.

## 输出格式

For each test case, output $ n $ lines.

For the $ i $ -th line, first output $ s_i $ $ (1 \le s_i \le n) $ — the size of the set $ A_i $ . Then, output $ s_i $ distinct integers from $ 1 $ to $ n $ — the elements of the set $ A_i $ .

If there are multiple solutions, you can output any of them.

It's guaranteed that for all test cases in this problem, such $ n $ sets exist.

## 样例 #1

### 样例输入 #1

```
2
4
0001
1001
0001
0000
3
011
001
000
```

### 样例输出 #1

```
3 1 2 3
2 1 3
2 2 4
4 1 2 3 4
1 1
2 1 2
3 1 2 3
```

## 提示

In the first test case, we have $ A_1 = \{1, 2, 3\}, A_2 = \{1, 3\}, A_3 = \{2, 4\}, A_4 = \{1, 2, 3, 4\} $ . Sets $ A_1, A_2, A_3 $ are proper subsets of $ A_4 $ , and also set $ A_2 $ is a proper subset of $ A_1 $ . No other set is a proper subset of any other set.

In the second test case, we have $ A_1 = \{1\}, A_2 = \{1, 2\}, A_3 = \{1, 2, 3\} $ . $ A_1 $ is a proper subset of $ A_2 $ and $ A_3 $ , and $ A_2 $ is a proper subset of $ A_3 $ .

## 题解
我们可以先给每个集合安排一个不同的数字，容易发现，此时的集合是互不包含的，接下来，我们来处理题目中给出的包含关系，若第 i 个集合被第 j 个集合包含，我们就把 i 集合分配的数字加入到 j 集合中，容易发现，此时能刚好满足这个关系，同时，与其他集合的关系也不会被破坏。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
vector<int>q[105];
string s;
void inline slove(){
    cin>>n;
    for(int i=1;i<=n;i++)
    q[i].clear();
    for(int i=1;i<=n;i++)
    q[i].push_back(i);
    for(int i=1;i<=n;i++){
    cin>>s;
    for(int j=0;j<n;j++)
    if(s[j]=='1')
    q[j+1].push_back(i);
    }
    for(int i=1;i<=n;i++)
    {
    cout<<q[i].size()<<" ";
    for(int j=0;j<q[i].size();j++)
    cout<<q[i][j]<<" ";
    cout<<endl;
    }
}
int main(){
    cin>>t;
    while(t--)slove();
}
```