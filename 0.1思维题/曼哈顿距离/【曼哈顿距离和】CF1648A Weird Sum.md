# Weird Sum

## 题面翻译

### 题意简述：

给出两个整数 $n, m ( 1 \leq n \le m, n \cdot m \leq 100000) $，和一个 $n \times m$ 的矩阵。若该矩阵中两元素相同，$sum$ (初始为零)就加上它们所在位置的曼哈顿距离。求 $sum$ 的值。

## 题目描述

Egor has a table of size $ n \times m $ , with lines numbered from $ 1 $ to $ n $ and columns numbered from $ 1 $ to $ m $ . Each cell has a color that can be presented as an integer from $ 1 $ to $ 10^5 $ .

Let us denote the cell that lies in the intersection of the $ r $ -th row and the $ c $ -th column as $ (r, c) $ . We define the manhattan distance between two cells $ (r_1, c_1) $ and $ (r_2, c_2) $ as the length of a shortest path between them where each consecutive cells in the path must have a common side. The path can go through cells of any color. For example, in the table $ 3 \times 4 $ the manhattan distance between $ (1, 2) $ and $ (3, 3) $ is $ 3 $ , one of the shortest paths is the following: $ (1, 2) \to (2, 2) \to (2, 3) \to (3, 3) $ .

Egor decided to calculate the sum of manhattan distances between each pair of cells of the same color. Help him to calculate this sum.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \leq n \le m $ , $ n \cdot m \leq 100\, 000 $ ) — number of rows and columns in the table.

Each of next $ n $ lines describes a row of the table. The $ i $ -th line contains $ m $ integers $ c_{i 1}, c_{i 2}, \ldots, c_{im} $ ( $ 1 \le c_{ij} \le 100\, 000 $ ) — colors of cells in the $ i $ -th row.

## 输出格式

Print one integer — the the sum of manhattan distances between each pair of cells of the same color.

## 样例 #1

### 样例输入 #1

```
2 3
1 2 3
3 2 1
```

### 样例输出 #1

```
7
```

## 样例 #2

### 样例输入 #2

```
3 4
1 1 2 2
2 1 1 2
2 2 1 1
```

### 样例输出 #2

```
76
```

## 样例 #3

### 样例输入 #3

```
4 4
1 1 2 3
2 1 1 2
3 1 2 1
1 1 2 1
```

### 样例输出 #3

```
129
```

## 提示

In the first sample there are three pairs of cells of same color: in cells $ (1, 1) $ and $ (2, 3) $ , in cells $ (1, 2) $ and $ (2, 2) $ , in cells $ (1, 3) $ and $ (2, 1) $ . The manhattan distances between them are $ 3 $ , $ 1 $ and $ 3 $ , the sum is $ 7 $ .


## 题解
我们本体采用我们的曼哈顿距离和都会采用的方法，**排序后转换为前缀和**然后再去进行计算。这里，我们因为我们对于我们的每一种颜色都是单独处理的，我们就可以直接对于我们的每一种颜色列式子即可。

我们的最后的式子如下所示：
```
#include <bits/stdc++.h>

#define int long long

int INF=0x3f3f3f3f3f;

using namespace std;

const int N=1e5+10;

vector<int> x[N];

vector<int> y[N];

void solve(){

    int n,m;

    cin>>n>>m;

    for(int i=1;i<=n;i++){

        for(int j=1;j<=m;j++){

            int c;

            cin>>c;

            x[c].push_back(i);

            y[c].push_back(j);

        }

    }

    int res=0;

    for(int i=1;i<=100000;i++){

        sort(x[i].begin(),x[i].end());

        sort(y[i].begin(),y[i].end());

        int n_=x[i].size();

        if(n_!=0){

            vector<int> sum(n_);

            sum[0]=x[i][0];

            for(int j=1;j<n_;j++){

                sum[j]=sum[j-1]+x[i][j];

            }

            for(int j=1;j<n_;j++){

                res+=(j)*x[i][j]-sum[j-1];

            }

        }

        n_=y[i].size();

        if(n_!=0){

            vector<int> sum(n_);

            sum[0]=y[i][0];

            for(int j=1;j<n_;j++){

                sum[j]=sum[j-1]+y[i][j];

            }

            for(int j=1;j<n_;j++){

                res+=(j)*y[i][j]-sum[j-1];

            }

        }

    }

    cout<<res<<endl;

}

signed main(){

    ios::sync_with_stdio(false),cin.tie(0);

    int t;

 //   cin>>t;

    t=1;

    while(t--){

        solve();

    }

}
```