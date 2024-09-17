#mex #权值线段树 
# Rmq Problem / mex

## 题目描述

有一个长度为 $n$ 的数组 $\{a_1,a_2,\ldots,a_n\}$。

$m$ 次询问，每次询问一个区间内最小没有出现过的自然数。

## 输入格式

第一行，两个正整数 $n,m$。  
第二行，$n$ 个非负整数 $a_1, a_2, \ldots , a_n$。  
接下来 $m$ 行，每行两个正整数 $l,r$，表示一次询问。

## 输出格式

输出 $m$ 行，每行一个数，依次表示每个询问的答案。

## 样例 #1

### 样例输入 #1

```
5 5
2 1 0 2 1
3 3
2 3
2 4
1 2
3 5
```

### 样例输出 #1

```
1
2
3
0
3
```

## 提示

对于 $30\%$ 的数据：$1\leq n,m\leq 1000$。  
对于 $100\%$ 的数据：$1\leq n,m\leq 2\times {10}^5$，$1\leq l\leq r\leq n$，$0\leq a_i\leq 2\times 10^5$。

## 题解
我们要求解我们的 $mex$ 问题，本质上就是在求解我们的一个区间内，出现的**数字的种类**有哪些，然后我们再根据我们的相关条件来进行我们的处理。
而我们可以发现，我们这一题要求我们 $[l,r]$ 内，每一个数字出现的次数是多少，这个，我们如果直接用我们的权值线段树，权值假如记录的是我们每一个权值出现的次数，那么我们显然是无法解决我们的问题的。
我们的权值可以设置为我们对应数字出现的**最靠左的位置** $l_{0}$,利用这一个权值，我们想要求出 $[l,r]$ **区间内**我们的 $mex$,我们查询**权值比我们的 $l$ 要大的，数值最小的 w**, 这个 w 就是我们要求的 $mex$, 于是我们就可以变成：**查询（下标）[1, w]内，满足我们的权值小于 l 的最小的下标是多少**，换成人话就是说：我们要找到上一次出现的位置在我们的 l 之后的，并且数字最小的那一个数字

然后，我们就变成了一个主席树的题目。

注意：
1. 我们的主席树的对应每一个结点都是这一个区间所拥有的 l 的最小值，我们一定要通过我们的 push 来进行更新，方便我们后续查找。

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#define space putchar(' ')
#define enter putchar('\n')
typedef long long ll;
using namespace std;
template <class T>
void read(T &x){
    char c;
    bool op = 0;
    while(c = getchar(), c < '0' || c > '9')
	if(c == '-') op = 1;
    x = c - '0';
    while(c = getchar(), c >= '0' && c <= '9')
	x = x * 10 + c - '0';
    if(op) x = -x;
}
template <class T>
void write(T x){
    if(x < 0) putchar('-'), x = -x;
    if(x >= 10) write(x / 10);
    putchar('0' + x % 10);
}

const int N = 400005, M = 5000005;
int n, m, a[N], lst[N], idx;
int tot, root[N], ls[M], rs[M], data[M];

void change(int old, int &k, int l, int r, int p, int x){
    k = ++tot;
    ls[k] = ls[old], rs[k] = rs[old];
    if(l == r) return (void)(data[k] = x);
    int mid = (l + r) >> 1;
    if(p <= mid) change(ls[old], ls[k], l, mid, p, x);
    else change(rs[old], rs[k], mid + 1, r, p, x);
    data[k] = min(data[ls[k]], data[rs[k]]);
}
int query(int k, int l, int r, int x){
    if(!k || l == r) return lst[l];
    int mid = (l + r) >> 1;
    if(data[ls[k]] >= x) return query(rs[k], mid + 1, r, x);
    return query(ls[k], l, mid, x);
}

int main(){

    read(n), read(m);
    lst[++idx] = 0;
    for(int i = 1; i <= n; i++)
	read(a[i]), lst[++idx] = a[i], lst[++idx] = a[i] + 1;
    sort(lst + 1, lst + idx + 1);
    idx = unique(lst + 1, lst + idx + 1) - lst - 1;
    for(int i = 1; i <= n; i++){
        a[i] = lower_bound(lst + 1, lst + idx + 1, a[i]) - lst;
        change(root[i - 1], root[i], 1, idx, a[i], i);
    }
    while(m--){
        int l, r;
        read(l), read(r);
        write(query(root[r], 1, idx, l)), enter;
    }

    return 0;
}
```