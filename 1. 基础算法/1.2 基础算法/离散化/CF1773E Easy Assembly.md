# Easy Assembly

## 题面翻译

### 题目描述

Emma 喜欢玩积木，她有若干相同大小的、标有不同数字的积木，将它们竖直堆放。

现在，她可以进行以下操作：

- 分裂：从将一堆积木（数量大于 $1$）的顶端拿出若干块，按原来的顺序放在地上形成一堆新的积木。操作后积木堆数加一；

- 合并：将一堆积木全部按原来的顺序全部堆到另一堆积木的顶端。操作后积木堆数减一。

她想让所有木块形成一堆且积木上的数字由顶端到底端升序排列。请求出最小操作次数。

### 输入格式

第一行一个整数 $n$（$1\le n\le 10\,000$）表示初始积木堆数。

接下来 $n$ 行，第 $i$ 行开始一个整数 $k_i$（$k_i\ge 1$；$\sum\limits_{i=1}^n k_i\le 10\,000$）表示该堆木块数量。接下来 $k_i$ 个整数 $b_{i,j}$（$1\le b_{i,j}\le 10^9$），依次表示从顶端到底端的积木上的数字。

保证所有积木上的数字不同。

### 输出格式

一行两个整数 $s$ 和 $c$，表示在总操作数最小的情况下分裂和合并操作的次数。

### 样例解释

四张图依次是：初始状态、将最后一堆分裂、将第二堆合并入第一堆、将第一堆合并入第二堆。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1773E/cb220fbe8fd5a228c5c21c989706c90547f1579c.png) $\qquad\qquad$ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1773E/3de66ba621d6019801a98f584dbabf1895c3fe49.png) $\qquad\qquad$ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1773E/97be0dbdbca0329fbb6578d639115dfa0e5cb4a8.png) $\qquad\qquad$ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1773E/254fe6b8fe2b5e78600f45ccede2be36ce9161ad.png)

## 题目描述

Emma loves playing with blocks. She has several cubic blocks of the same size that are numbered with distinct integers written on them. She assembles towers from those blocks by stacking them vertically.

A configuration of her game is a set of towers that she has assembled from the blocks. Emma can perform two kinds of operations on a configuration of towers:

- Split any tower with more than one block in it by taking any number of blocks from the top of the tower and moving them to a new tower keeping their order, so that the top block of the old tower becomes the top block of the new tower. As a result of this operation, the number of towers increases by one.
- Combine any two towers by moving blocks from one tower on top of the other tower in the same order. As a result of this operation, the number of towers decreases by one.

Emma wants to stack all the blocks into a single tower so that all blocks come in order sorted by the numbers — from the block with the minimal number at the top to the block with the maximal number at the bottom. Emma wants to do as little of splitting and combining operations as possible. Your task is to find the minimal number of operations she has to make and output how many splits and combines are needed.

## 输入格式

The first line of the input file contains an integer $ n $ ( $ 1 \le n \le 10\, 000 $ ) — the number of towers in the initial configuration. Next $ n $ lines describe towers. Each tower $ i $ is described by a line that starts with the number $ k_i $ ( $ k_i \ge 1 $ ; $ \sum_1^n{k_i} \le 10\, 000 $ ) — the number of blocks in the tower, followed by $ k_i $ numbers $ b_{i, j} $ ( $ 1 \le b_{i, j} \le 10^9 $ ) — numbers written on the blocks in the $ i $ -th tower, listed from top to bottom. All block numbers listed in the input are different.

## 输出格式

Output a line with two integers $ s $ and $ c $ — the number of split and combine operations Emma should make to get a single tower with blocks sorted by their numbers, so that the total number of operations is minimized.

## 样例 #1

### 样例输入 #1

```
2
3 3 5 8
2 9 2
```

### 样例输出 #1

```
1 2
```

## 提示

The example needs the following operations (1 split and 2 combines).

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1773E/cb220fbe8fd5a228c5c21c989706c90547f1579c.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1773E/3de66ba621d6019801a98f584dbabf1895c3fe49.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1773E/97be0dbdbca0329fbb6578d639115dfa0e5cb4a8.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1773E/254fe6b8fe2b5e78600f45ccede2be36ce9161ad.png)InitialSplit lastCombined 2 nd onto 1 stCombined 1 st onto 2nd

## 题解
首先，因为我们本题只关注我们数字的相对大小，于是我们就可以对我们的塔里的数先进性离散化处理，然后，如果对于一个塔 a，塔里存在 $a_{i}-a_{i+1}\neq 1$,那么这两个元素之间必须进行一次分裂操作，我们假设分裂了 $c$ 次，那么我们就需要合并 $c+n-1$ 次，一共就是 $2c+n-1$ 次操作。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  int n,c=0,c0=0; cin>>n;
  vector<vector<int> > a(n);
  set<int> s; map<int,int> m;
  for(auto &i:a){
    int k; cin>>k; i.resize(k);
    for(auto &j:i)cin>>j,s.emplace(j); // 记录
  }
  for(auto &i:s)m[i]=++c; // 编号
  for(auto &i:a)for(auto &j:i)j=m[j]; // 赋值
  for(auto &i:a)
    for(int j=1;j<i.size();j++)
      if(i[j]-i[j-1]>1||i[j]-i[j-1]<0)c0++; // 判断
  cout<<c0<<' '<<c0+n-1<<endl;
  return 0;
}
```