# The Very Beautiful Blanket

## 题面翻译

你需要构造一个 $n \times m$ 的正整数矩阵，使得任意 $4 \times 4$ 大小的子矩阵中，左上角四个点的异或和和右下角四个相等，右上角四个和左下角四个相等。

```
a b c d
e f g h
i j k l 
m n o p
```
即在上图中，$a \oplus b \oplus e \oplus f = k \oplus l \oplus o \oplus p$ 且 $c \oplus d \oplus g \oplus h = i \oplus j \oplus m \oplus n$。

此外，你要使矩阵中不同的数字尽可能多，先输出不同数字的数量，再输出这个矩阵。

## 题目描述

Kirill wants to weave the very beautiful blanket consisting of $ n \times m $ of the same size square patches of some colors. He matched some non-negative integer to each color. Thus, in our problem, the blanket can be considered a $ B $ matrix of size $ n \times m $ consisting of non-negative integers.

Kirill considers that the blanket is very beautiful, if for each submatrix $ A $ of size $ 4 \times 4 $ of the matrix $ B $ is true:

- $ A_{11} \oplus A_{12} \oplus A_{21} \oplus A_{22} = A_{33} \oplus A_{34} \oplus A_{43} \oplus A_{44}, $
- $ A_{13} \oplus A_{14} \oplus A_{23} \oplus A_{24} = A_{31} \oplus A_{32} \oplus A_{41} \oplus A_{42}, $

where $ \oplus $ means [bitwise exclusive OR](https://en.wikipedia.org/wiki/Exclusive_or)

Kirill asks you to help her weave a very beautiful blanket, and as colorful as possible!

He gives you two integers $ n $ and $ m $ .

Your task is to generate a matrix $ B $ of size $ n \times m $ , which corresponds to a very beautiful blanket and in which the number of different numbers maximized.

## 输入格式

The first line of input data contains one integer number $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

The single line of each test case contains two integers $ n $ and $ m $ $ (4 \le n, \, m \le 200) $ — the size of matrix $ B $ .

It is guaranteed that the sum of $ n \cdot m $ does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, in first line output one integer $ cnt $ $ (1 \le cnt \le n \cdot m) $ — the maximum number of different numbers in the matrix.

Then output the matrix $ B $ $ (0 \le B_{ij} < 2^{63}) $ of size $ n \times m $ . If there are several correct matrices, it is allowed to output any one.

It can be shown that if there exists a matrix with an optimal number of distinct numbers, then there exists among suitable matrices such a $ B $ that $ (0 \le B_{ij} < 2^{63}) $ .

## 样例 #1

### 样例输入 #1

```
4
5 5
4 4
4 6
6 6
```

### 样例输出 #1

```
25
9740 1549 9744 1553 9748
1550 1551 1554 1555 1558
10252 2061 10256 2065 10260
2062 2063 2066 2067 2070
10764 2573 10768 2577 10772
16
3108 3109 3112 3113
3110 3111 3114 3115
3620 3621 3624 3625
3622 3623 3626 3627
24
548 549 552 553 556 557
550 551 554 555 558 559
1060 1061 1064 1065 1068 1069
1062 1063 1066 1067 1070 1071
36
25800 25801 25804 25805 25808 25809
25802 4294993099 25806 4294993103 25810 4294993107
26312 26313 26316 26317 26320 26321
26314 4294993611 26318 4294993615 26322 4294993619
26824 26825 26828 26829 26832 26833
26826 4294994123 26830 4294994127 26834 4294994131
```

## 提示

In the first test case, there is only 4 submatrix of size $ 4 \times 4 $ . Consider a submatrix whose upper-left corner coincides with the upper-left corner of the matrix $ B $ :

 $  \left[ {\begin{array}{cccc} 9740 & 1549 & 9744 & 1553 \\ 1550 & 1551 & 1554 & 1555 \\ 10252 & 2061 & 10256 & 2065 \\ 2062 & 2063 & 2066 & 2067 \\ \end{array} } \right]  $

 $ 9740 \oplus 1549 \oplus 1550 \oplus 1551 $ $ = $ $ 10256 \oplus 2065 \oplus 2066 \oplus 2067 $ $ = $ $ 8192 $ ;

 $ 10252 \oplus 2061 \oplus 2062 \oplus 2063 $ $ = $ $ 9744 \oplus 1553 \oplus 1554 \oplus 1555 $ $ = $ $ 8192 $ .

So, chosen submatrix fits the condition. Similarly, you can make sure that the other three submatrices also fit the condition.

## 题解
本题，我们通过观察我们的样例，我们就可以发现，我们如果希望我们的最终结果最大，我们显然是直接输出我们的 $n*m$ 作为我们的答案是最优的。这个时候，我们的问题就在于怎么构造我们的答案使得我们的最终结果最优：
我们首先注意到，对于我们的四个连续的书，我们有：$a\oplus a+1\oplus a+2\oplus a+3=0$ 。于是，我们对于我们的 $4 x 4$ 的矩阵，我们就可以通过下面的构造来实现：
![[Pasted image 20240812155320.png]]

考虑怎么从我们的 $4\times4$ 的矩阵扩展到其他大小的矩阵，我们理想的值域当然是**要求我们的最终结果是在 0-255**范围当中的。我们发现，我们如果希望扩展到 $4\times5$ 的矩阵，那么我们上面的哪一个矩阵，显然是不能够支持我们扩展的，于是，我们就需要通过我们的下面的方法来进行处理：
**我们让我们的下面两行原本的元素都加上一个非常大的数**，这样能够保证我们**不会和其他的元素重复**。且仍然满足我们的异或结果为 0.

这个时候，我们得到了下面的一个矩阵：
![[Pasted image 20240812155835.png]]

我们考虑怎么对于我们的这一个矩阵进行扩展，我们发现，我们如果向右进行扩展。
$$\begin{Bmatrix}1&4&5&x_1\\3&6&7&x_2\\513&516&517&x_3\\515&518&519&x_4\end{Bmatrix}$$
取出左上角和左下角四个元素，发现 $1\oplus4\oplus3\oplus6=513\oplus516\oplus515\oplus518=0$,刚好异或和为
0, 现在我们只需要让 $x_1\oplus x_2=5\oplus7,x_3\oplus x_4=517\oplus519$ 即可。
我们又发现，$5\oplus7=517\oplus519=2$,那么我们就可以从 7 和 519 开始向后枚举 $a,b$ 使 $a\oplus b=2$,
发现枚举出了 (8,10)和 (520,522), 放到之前的矩阵中：
$$\begin{Bmatrix}0&1&4&5&8\\2&3&6&7&10\\512&513&516&517&520\\514&515&518&519&522\end{Bmatrix}$$



发现 $4\times m$ 的矩阵呼之欲出了：
$$\begin{Bmatrix}0&1&4&5&8&9&11+1&11+2&\cdots\\2&3&6&7&10&11&11+3&11+4&\cdots\\512&513&516&517&520&521&522+1&522+2&\cdots\\514&515&518&519&522&522&522+3&522+4&\cdots\end{Bmatrix}$$


简单手玩一下发现矩阵合法，那么接下来需要考虑 $n>4$ 时的矩阵如何构造。仍然保持当前规律不变，设
$n=6,m=4$,尝试按照当前规律构造：
$$\begin{Bmatrix}0&1&4&5\\2&3&6&7\\512&513&516&517\\514&515&518&519\\1024&1025&1028&1029\\1026&1027&1030&1031\end{Bmatrix}$$
简单手玩，发现矩阵仍然合法，设置 $n>6,m>6$,再次检查，仍合法，最终得到构造方案：
$$\begin{gathered}\begin{Bmatrix}A_{1,1}&A_{1,2}&A_{1,2}+3&A_{1,2}+4&A_{1,2}+7&\cdots\\A_{2,1}&A_{2,2}&A_{2,2}+3&A_{2,2}+4&A_{2,2}+7&\cdots\\A_{1,1}+512&A_{1,2}+512&\cdots&\cdots&\cdots&\cdots\\A_{2,1}+512&A_{2,2}+512&\cdots&\cdots&\cdots&\cdots\\A_{1,1}+1024&A_{2,2}+1024&\cdots&\cdots&\cdots&\cdots\\\cdots&\cdots&\cdots&\cdots&\cdots&\cdots\end{Bmatrix}\end{gathered}$$


```
// LUOGU_RID: 112576339
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

bool Mbe;

int n, m;
void solve() {
  cin >> n >> m;
  cout << n * m << "\n";
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++)
      cout << (i << 8) + j << (j == m ? '\n' : ' ');
}

bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T = 1;
  cin >> T;
  while(T--) solve();
  cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
  return 0;
}
```