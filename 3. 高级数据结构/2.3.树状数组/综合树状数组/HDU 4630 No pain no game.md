# 
## 题目描述
给出一个序列，这个数列是 1-n 这 n 个数字的一个全排列，给出一个区间【l，r】，求区间内任意两个数的最大公约数的最大值

## 输入格式
First line contains a number T(T <= 5),denote the number of test cases.  
Then follow T test cases.  
For each test cases,the first line contains a number n(1 <= n <= 50000).  
The second line contains n number a1, a2, ..., an.  
The third line contains a number Q(1 <= Q <= 50000) denoting the number of queries.  
Then Q lines follows,each lines contains two integer l, r(1 <= l <= r <= n),denote a query.


## 输出格式
For each test cases,for each query print the answer in one line.


## 样例 #1

### 样例输入 #1

```
1
10
8 2 4 9 5 7 10 6 1 3
5
2 10
2 4
6 9
1 4
7 10
```

### 样例输出 #1

```
5
2
2
4
3

```

## 提示




## 题解
区间内右 Q 个查询，而 Q 很大，我们需要用到离线处理，先读取所有的查询，然后统一处理，计算结束后一起输出。
我们先将所有的询问按照右端点 R 从小到大排序，从最小的 R 开始计算，再到后面其他的端点。在这个过程中，先计算的区间能用于后计算的区间，从此提高了我们的效率。

## 代码
```cpp
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

const int N = 50010;

vector<int> prime[N];
int pre[N], n, a[N], c[N], ans[N];
//树状数组维护从某个位置到右节点的最大公因数n 

struct node{
  int l, r, id;
  //int ans;
  bool operator < (const node& tmp){
    return r < tmp.r;
  }
}f[N]; 

inline int lowbit(int x){ return x & (-x); }

void getPrime(){//存储因子
  for(int i = 1; i <= N; ++i)
    for(int j = i; j <= N; j += i)
      prime[j].push_back(i);
}

void add(int x, int v){
  while(x){
    c[x] = max(c[x], v);//更新候选人
    x -= lowbit(x);
  }
}

int getMax(int x){

  int res = 0;

  while(x <= n){
    res = max(res, c[x]);//筛选候选人
    x += lowbit(x);
  }

  return res;
}

int main(){

  getPrime();

  int t, m;
  cin >> t;

  while(t--){
    memset(c, 0, sizeof(c));
    memset(pre, 0, sizeof(pre));
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> a[i];
    cin >> m;
    for(int i = 1; i <= m; ++i){
      f[i].id = i;
      cin >> f[i].l >> f[i].r;
    }
    sort(f + 1, f + m + 1);//预处理
    int p = 1;
    for(int i = 1; i <= n; ++i){//离线处理
      int x = a[i];
      for(int j = 0; j < prime[x].size(); ++j){
        int tmp = prime[x][j];//a[i]的一个因数 
        if(pre[tmp]){//这个因子在前面中出现过
          Add (pre[tmp], tmp);//更新上一个位置
        }
        pre[tmp] = i;
      }
      while(f[p].r == i && p <= m){
         ans[f[p].id] = getMax(f[p].l);//查询（按照右区间排序 
          ++p;
        }
    }

    for(int i = 1; i <= m; ++i){
      cout << ans[i] << endl;
    }
  }
  return 0;
}
```