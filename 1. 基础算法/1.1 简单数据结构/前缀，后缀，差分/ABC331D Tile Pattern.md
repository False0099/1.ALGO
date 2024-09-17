# [ABC 331 D] Tile Pattern

## 题面翻译

给出 $N$ 以及 $N\times N$ 的黑白矩阵 $P$，范围从 $P[0][0]$ 到 $P[N-1][N-1]$，其中 `B` 代表黑，`W` 代表白。\
有一个长宽均为 $10^9$ 的黑白网格，左上角的格子坐标为 $(0,0)$，格子 $(x,y)$ 的颜色与 $P[x\bmod N][y\bmod N]$ 相同。\
给出 $Q$ 个询问，每次询问黑白网格中，左上角的格子的坐标为 $(A,B)$，右下角的格子的坐标为 $(C,D)$ 的矩形中有几个格子是黑色的。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc331/tasks/abc331_d

縦横 $ 10^9 $ マスのグリッドがあります。上から $ i\ +\ 1 $ 行目、左から $ j\ +\ 1 $ 列目 $ (0\ \leq\ i,\ j\ \lt\ 10^9) $ にあるマスを $ (i,\ j) $ と呼びます。(通常と異なる index の割り当て方に注意してください。)  
 各マスは黒マスか白マスのいずれかです。マス $ (i,\ j) $ の色は文字 $ P[i\ \bmod\ N][j\ \bmod\ N] $ によって表されて、`B` ならばマス $ (i,\ j) $ は黒マス、`W` ならば白マスです。ここで $ a\ \bmod\ b $ は $ a $ を $ b $ で割った余りを意味します。

$ Q $ 個のクエリが与えられるので順に処理してください。  
 各クエリでは $ 4 $ つの整数 $ A,\ B,\ C,\ D $ が与えられるので、$ (A,\ B) $ を左上隅、$ (C,\ D) $ を右下隅とする長方形領域に含まれる黒マスの個数を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。ここで $ \text{query}_i $ は $ i $ 番目に処理するクエリである。

> $ N $ $ Q $ $ P[0][0]P[0][1]\dots\ P[0][N-1] $ $ P[1][0]P[1][1]\dots\ P[1][N-1] $ $ \vdots $ $ P[N-1][0]P[N-1][1]\dots\ P[N-1][N-1] $ $ \text{query}_1 $ $ \text{query}_2 $ $ \vdots $ $ \text{query}_Q $

各クエリは以下の形式で与えられる。

> $ A $ $ B $ $ C $ $ D $

## 输出格式

問題文の指示に従ってクエリへの答えを改行区切りで出力せよ。

## 样例 #1

### 样例输入 #1

```
3 2
WWB
BBW
WBW
1 2 3 4
0 3 4 5
```

### 样例输出 #1

```
4
7
```

## 样例 #2

### 样例输入 #2

```
10 5
BBBWWWBBBW
WWWWWBBBWB
BBBWBBWBBB
BBBWWBWWWW
WWWWBWBWBW
WBBWBWBBBB
WWBBBWWBWB
WBWBWWBBBB
WBWBWBBWWW
WWWBWWBWWB
5 21 21 93
35 35 70 43
55 72 61 84
36 33 46 95
0 0 999999999 999999999
```

### 样例输出 #2

```
621
167
44
344
500000000000000000
```

## 提示

### 制約

- $ 1\ \leq\ N\ \leq\ 1000 $
- $ P[i][j] $ は `W` または `B`
- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ A\ \leq\ C\ \lt\ 10^9 $
- $ 0\ \leq\ B\ \leq\ D\ \lt\ 10^9 $
- $ N,\ Q,\ A,\ B,\ C,\ D $ は全て整数
 
### Sample Explanation 1

グリッドの左上部分を図示すると次の図のようになります。 !\ [image\](https://img.atcoder.jp/abc331/2c3ff3c4018817a0839f1fbe0e7c431d.jpg) $ 1 $ 番目のクエリについて、$ (1,\ 2) $ を左上隅、$ (3,\ 4) $ を右下隅とする長方形領域は図の赤い枠線に囲まれた部分で、領域に含まれる黒マスの個数は $ 4 $ 個です。 $ 2 $ 番目のクエリについて、$ (0,\ 3) $ を左上隅、$ (4,\ 5) $ を右下隅とする長方形領域は図の青い枠線に囲まれた部分で、領域に含まれる黒マスの個数は $ 7 $ 個です。


## 题解
我们定义函数 $f(A, B, C, D)$ 如下。(注意每个不等号中都有/没有等号）。

- $f(A, B, C, D) =$（$(h, w)$ 与 $A \leq h \lt C$ 和 $B \leq w \lt D$ 的方格中黑色方格的个数）。

所求值为 $f(A, B, C + 1, D + 1)$。(注意 $1$ 的移动）。
虽然我们可以直接实现直接求出 $f$ 的算法，但由于有四个参数，实现起来需要大量的案例，所以我们尽量避免。

我们想要的是 (d) 部分：
![[Pasted image 20231204172221.png]]

利用累积和的技巧，我们可以将其表达如下：

$$
 \begin{aligned} &f(A, B, C, D) \\ &=(\text{The number of black squares in }(d)) \\ &= (\text{The number of black squares in }(a), (b), (c), (d)) \\ &- (\text{The number of black squares in }(a), (b)) \\ &- (\text{The number of black squares in }(a), (c)) \\ &+ (\text{The number of black squares in }(a)) \\ &= f(0, 0, C, D) - f(0, 0, C, B) - f(0, 0, A, D) + f(0, 0, A, B) \end{aligned} 
$$

通过这种变形，我们可以限制 $f$ 的参数，从而得到 $A=B=0$。也就是说，如果我们定义

- $g(H, W) =$ 与 $0 \leq h \lt H$ 和 $0 \leq w \lt W$ 的方格 $(h, w)$ 中黑色方格的个数）、

则

$$
 f(A,B,C,D) = g(C,D) - g(C, B) - g(A, D) + g(A, B), 
$$

因此只需实现只有两个参数的 $g$ 即可。

现在我们来考虑如何计算 $g(H, W)$。简单的实现会耗费太多时间，所以我们要利用周期性。  
例如，在计算 $H = 8, W = 7$ 和 $N = 3$ 时，我们可以按周期划分网格如下：


由于网格具有 $(3 \times 3)$ 周期模式，子矩形可分为以下四种类型，它们都与 $N \times N$ 重合或小于 $N \times N$：

- $4$ A 型矩形，其图案与左上方的 $3 \times 3$ 区域重合
- $2$ 图案与左上方 $2 \times 3$ 区域重合的 B 型矩形
- $2$ 图案与左上方 $3 \times 1$ 区域重合的 C 型矩形
- $1$ 图案与左上方 $2 \times 1$ 区域重合的 D 型矩形

这对一般的 $H, W, N$ 也是成立的，因此如果我们知道四种类型的矩形的数量及其尺寸，就可以简化问题。这些可以通过 $H$ 和 $W$ 除以 $N$ 的商和余数得到。

因此，通过预先计算所有 $0 \leq i \leq N, 0 \leq j \leq N$ 的 $g(i, j)$，可以在每次查询的 $\mathrm{O}(1)$ 时间内解决这个问题。  
通过再次应用第一个图中使用的技术，可以得到下面的递推关系，从而完成每次计算：

$$
 \begin{aligned} g(i, j) &= (1\text{ if } ((i-1,j-1)\text{ is a black square}) \text{ else } 0) \\ &+ g(i - 1, j) + g(i, j - 1) - g(i - 1, j - 1). \end{aligned} 
$$

因此，预计算总共只需 $\mathrm{O}(N^2)$ 时间。(如果 $i = 0$ 或 $j = 0$，则让 $g(i, j) = 0$）。
因此，我们总共只用了 $\mathrm{O}(N^2 + Q)$ 的时间就解决了问题，这已经足够快了。

- 示例代码（C++）
 ```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int N, Q, precalc[1010][1010];

long long g(int H, int W) {
  if (H <= N and W <= N) return precalc[H][W];
  int Hq = H / N, Hr = H % N;
  int Wq = W / N, Wr = W % N;
  long long ret = 0;
  ret += g(N, N) * Hq * Wq;
  ret += g(Hr, N) * Wq;
  ret += g(N, Wr) * Hq;
  ret += g(Hr, Wr);
  return ret;
}

long long f(int A, int B, int C, int D) {
  return g(C, D) - g(A, D) - g(C, B) + g(A, B);
}

int main() {
  cin >> N >> Q;
  vector<string> S(N);
  for (auto& s : S) cin >> s;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      precalc[i][j] += S[i - 1][j - 1] == 'B';
      precalc[i][j] += precalc[i - 1][j];
      precalc[i][j] += precalc[i][j - 1];
      precalc[i][j] -= precalc[i - 1][j - 1];
    }
  }
  while (Q--) {
    int A, B, C, D;
    cin >> A >> B >> C >> D;
    cout << f(A, B, C + 1, D + 1) << "\n";
  }
} 
```