# Corner Twist

## 题面翻译

### 题目大意
你有两个只有 $0, 1, 2 $ 的数字矩阵 $a$ 和 $b$，你可以按顺序进行以下的操作任意多次：

- 选择一个长、宽都 $ \ge 2$ 的长方形；
- 一个长方形有 $4$ 个角落，你要选择其中一组对角上的两个元素，并将它们 $+1$，并 $\bmod \ 3$；
- 最后将另外一组对角的两个元素 $+2$，并 $\bmod \ 3$。

**注意：这个操作仅改变了长方形四个角落上的值**

你需要判断是否可能通过执行任意次操作（可能是 $0$ 次）后将矩阵 $a$ 变成矩阵 $b$ 。

## 题目描述

You are given two grids of numbers $ a $ and $ b $ , with $ n $ rows and $ m $ columns. All the values in the grid are $ 0 $ , $ 1 $ or $ 2 $ .

You can perform the following operation on $ a $ any number of times:

- Pick any subrectangle in the grid with length and width $ \ge 2 $ . You are allowed to choose the entire grid as a subrectangle.
- The subrectangle has four corners. Take any pair of diagonally opposite corners of the chosen subrectangle and add $ 1 $ to their values modulo $ 3 $ .
- For the pair of corners not picked, add $ 2 $ to their values modulo $ 3 $ .

Note that the operation only changes the values of the corners of the picked subrectangle.

Is it possible to convert the grid $ a $ into grid $ b $ by applying the above operation any number of times (possibly zero)?

## 输入格式

The first line contains an integer $ t $ , the number of testcases ( $ 1 \le t \le 250 $ ).

For each testcase:

The first line contains two integers $ n $ and $ m $ , the number of rows and columns in the grid ( $ 2 \le n, m \le 500 $ ).

Each of the next n lines contain m characters — the $ j $ -th character of the $ i $ -th line represents $ a_{i, j} $ .

Each of the next n lines contain m characters — the $ j $ -th character of the $ i $ -th line represents $ b_{i, j} $ ( $ 0 \le a_{i, j}, b_{i, j} \le 2 $ ).

It is guaranteed that the sum of $ n $ over all test cases and the sum of $ m $ over all test cases do not exceed $ 500 $ .

## 输出格式

For each test case print "YES" (without quotes) if it is possible to convert grid $ a $ into grid $ b $ and "NO" (without quotes) otherwise.

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 样例 #1

### 样例输入 #1

```
7
3 3
000
000
000
111
111
111
4 4
0000
0000
0000
0000
2100
1200
0012
0021
4 4
1020
1200
1210
0000
0000
1200
2200
0000
3 3
012
012
012
010
111
011
8 8
00000000
00000000
00000000
00000000
00000000
00000000
00000000
10000000
00000000
01200000
02010000
00102000
00020100
00001020
00000210
10000000
2 7
0000000
0000000
2220111
0111222
2 7
0000000
0100010
2220111
1210202
```

### 样例输出 #1

```
YES
YES
YES
NO
YES
NO
YES
```

## 提示

In the first testcase, grid $ a $ can be converted into $ b $ in the following manner:

 $ \begin{matrix}\fbox{0} & 0 & \fbox{0}\\ 0 & 0 & 0\\ \fbox{0} & 0 & \fbox{0}\end{matrix} \Rightarrow \begin{matrix}1 & 0 & 2\\ 0 & \fbox{0} & \fbox{0}\\ 2 & \fbox{0} & \fbox{1}\end{matrix} \Rightarrow \begin{matrix}1 & 0 & 2\\ \fbox{0} & \fbox{1} & 2\\ \fbox{2} & \fbox{2} & 2\end{matrix} \Rightarrow \begin{matrix}1 & \fbox{0} & \fbox{2}\\ 1 & 0 & 2\\ 1 & \fbox{0} & \fbox{2}\end{matrix} \Rightarrow \begin{matrix}1 & 1 & 1\\ 1 & \fbox{0} & \fbox{2}\\ 1 & \fbox{2} & \fbox{0}\end{matrix} \Rightarrow \begin{matrix}1 & 1 & 1\\ 1 & 1 & 1\\ 1 & 1 & 1\end{matrix} $

Here, in each operation, the top-right and bottom-left corners highlighted by a box are incremented by $ 2 $ modulo $ 3 $ , while the top-left and bottom-right corners are incremented by $ 1 $ modulo $ 3 $ .

In the fourth testcase, it can be proven that it is not possible to convert grid $ a $ into grid $ b $ using the above-mentioned operations any number of times.

## 题解
本题，我们可以发现，我们的**任意一个操作都可以归结于我们的一个最小操作**，也就是说，我们可以通过我们的原子化操作来进行我们的**任意一个操作**。这样做一是因为可行，而是因为我们**不需要求最优解，只需要判断**。

关于这一点的证明，我们可以考虑在我们的**前缀和意义下**，我们的这一个操作是什么样的，我们可以发现，我们这一个操作，也就是对于我们的 $(l,r)$ 上的操作，可以等价于在我们的 $(R-1)(C-1)$ 的矩形前缀和数组中加 1. 

我们的另一个角度是直接通过我们的矩阵法证明：
对于一次 $2\times3$ 的矩阵修改 $\begin{bmatrix}0&0&0\\0&0&0\end{bmatrix}$ 到 $\begin{bmatrix}1&0&2\\2&0&1\end{bmatrix}$,我们可以通过直接修改完成。

考虑到我们可以用 $\begin{bmatrix}1&2\\2&1\end{bmatrix}$ 和 $\begin{bmatrix}2&1\\1&2\end{bmatrix}$ 来进行修改刚才的矩阵，

我们规定 $\begin{bmatrix}1&2\\2&1\end{bmatrix}$ 和 $\begin{bmatrix}2&1\\1&2\end{bmatrix}$ 分别为 1，2 号操作。

首先对上面矩阵左侧的 $2\times2$ 进行 1 操作，然后对右半部分实施 2 操作。

这样就得到了刚才右边的矩阵。
既然 $2\times2$ 的操作可以推广到 $2\times3$,同样依次类推也可以推广到 $2\times m$ 进而推广到 $n\times m$。于是我们得出结论：这需要用 1，2 两种 $2\times2$ 的矩阵操作即可完成其他的矩阵操作。
这样我们可以把 $a,b$ 的前 $n-1$ 行和 $m-1$ 列变得相同。
然后我们判断剩下的一行一列是否相同即可，不同就不行，相同可以。

```
#include <bits/stdc++.h>

#define int long long

int INF=0x3f3f3f3f3f;

using namespace std;

const int N=500;

int a[N][N];

int b[N][N];

void solve(){

    int n,m;

    cin>>n>>m;

    for(int i=0;i<n;i++){

        string s;

        cin>>s;

        for(int j=0;j<m;j++){

            //cin>>a[i][j];

            a[i][j]=s[j]-'0';

        }

    }

    for(int i=0;i<n;i++){

        string s;

        cin>>s;

        for(int j=0;j<m;j++){

            //cin>>b[i][j];

            b[i][j]=s[j]-'0';

        }

    }

    for(int i=0;i+1<n;i++){

        for(int j=0;j+1<m;j++){

            if(a[i][j]==b[i][j]){

                continue;

            }

            if((a[i][j]+1)%3==b[i][j]){

                a[i][j]++;

                a[i][j]%=3;

                a[i+1][j+1]++;

                a[i+1][j+1]%=3;

                a[i][j+1]+=2;

                a[i][j+1]%=3;

                a[i+1][j]+=2;

                a[i+1][j]%=3;

            }else if((a[i][j]+2)%3==b[i][j]){

                a[i][j]+=2;

                a[i][j]%=3;

                a[i+1][j+1]+=2;

                a[i+1][j+1]%=3;

                a[i+1][j]++;

                a[i+1][j]%=3;

                a[i][j+1]++;

                a[i][j+1]%=3;

            }

        }

    }

    for(int i=0;i<n;i++){

        for(int j=0;j<m;j++){

            if(a[i][j]!=b[i][j]){

                cout<<"NO"<<endl;

                return;

            }

        }

    }

    cout<<"YES"<<endl;

}

signed main(){

    ios::sync_with_stdio(false),cin.tie(0);

    int t;

    cin>>t;

    while(t--){

        solve();

    }

}
```