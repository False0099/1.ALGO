# [ABC 171 E] Red Scarf

## 题面翻译

给出有 $n$（$N$ 为偶数）个数的序列 $a$，求还原序列 $b$，使 $a_i$ 为除 $b_i$ 以外所有数的异或和。例如 $a_1=b_2 \oplus b_3\oplus\dots\oplus b_n$，$a_2=b_1\oplus b_3\oplus \dots\oplus b_n$，$\dots$，$a_n=b_1\oplus b_2\oplus \dots\oplus b_{n-1}$。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc171/tasks/abc171_e

猫のすぬけくんが $ N\ (\textbf{偶数}) $ 匹います。各すぬけくんには $ 1,\ 2,\ \ldots,\ N $ の番号が振られています。

各すぬけくんは首に赤いスカーフを巻いており、スカーフにはそのすぬけくんが一番好きな非負整数が $ 1 $ つ書き込まれています。

すぬけくんたちは最近、整数の xor（排他的論理和）と呼ばれる演算を覚えました。

 Xor とは $ n $ 個の非負整数 $ x_1, x_2,\ \ldots,\ x_n $ について、それらの xor、 $ x_1~\textrm{xor}~x_2~\textrm{xor}~\ldots~\textrm{xor}~x_n $ は以下のように定義されます。

- $ x_1~\textrm{xor}~x_2~\textrm{xor}~\ldots~\textrm{xor}~x_n $ を二進表記した際の $ 2^k (k\ \geq\ 0) $ の位の数は、$ x_1, x_2,\ \ldots,\ x_n $ のうち、二進表記した際の $ 2^k (k\ \geq\ 0) $ の位の数が $ 1 $ となるものの個数が奇数ならば $ 1 $、そうでなければ $ 0 $ となる。
 
 例えば、$ 3~\textrm{xor}~5\ =\ 6 $ となります。早速この演算を使いたくなったすぬけくんたちは、自分以外のすぬけくんのスカーフに書かれた整数の xor を計算することにしました。

番号 $ i $ が振られたすぬけくんが計算した、自分以外のすぬけくんのスカーフに書かれた整数の xor が $ a_i $ であることが分かっています。 この情報を元に、各すぬけくんのスカーフに書かれた整数を特定してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ a_1 $ $ a_2 $ $ \ldots $ $ a_N $

## 输出格式

$ 1 $ 行に $ N $ 個の整数を空白区切りで出力せよ。

このうち左から $ i $ 番目の整数は、番号 $ i $ が振られたすぬけくんのスカーフに書かれた整数を表すものとする。

与えられた条件を満たす解が複数存在する場合、どれを出力しても構わない。

## 样例 #1

### 样例输入 #1

```
4
20 11 9 24
```

### 样例输出 #1

```
26 5 7 22
```

## 提示

### 制約

- 入力はすべて整数である
- $ 2\ \leq\ N\ \leq\ 200000 $
- $ N $ は$ \textbf{偶数} $
- $ 0\ \leq\ a_i\ \leq\ 10^9 $
- 与えられた情報と整合するようなスカーフ上の整数の組合せが存在する

### Sample Explanation 1

\- $ 5~\textrm{xor}~7~\textrm{xor}~22\ =\ 20 $ - $ 26~\textrm{xor}~7~\textrm{xor}~22\ =\ 11 $ - $ 26~\textrm{xor}~5~\textrm{xor}~22\ =\ 9 $ - $ 26~\textrm{xor}~5~\textrm{xor}~7\ =\ 24 $ より、この出力は与えられた情報と整合します。

## 题解
我们本题中的题意可以转换为：给定 n 个方程：

$$
\left.\left\{\begin{matrix}b_1=a_2\oplus a_3\oplus a_4\oplus\ldots\oplus a_n\\b_2=a_1\oplus a_3\oplus a_4\oplus\ldots\oplus a_n\\b_3=a_1\oplus a_2\oplus a_4\oplus\ldots\oplus a_n\\\cdots\\b_n=a_1\oplus a_2\oplus a_3\oplus\ldots\oplus a_{n-1}\end{matrix}\right.\right.
$$

要你根据这 n 个方程求出我们的 $a$ 是多少。

对于我们的异或方程组，如果是 n 是偶数，那么我们把我们的所有 b 给异或起来，我们的结果 $x=a_{1}\oplus a_{2}\dots \oplus a_{n}$,然后又因为我们有 $b_{1}=a_{2}\oplus a_{3}\dots \oplus a_{n}$,因此，我们就可以通过我们的 $x\oplus b_{1}$ 来得到我们的 $a_{1}$,同理，我们就可以得到我们的 $a_{n}$

于是我们就做完了我们的题目，但是我们对于我们的**n 为奇数的情况，我们是解不出来我们的上面的方程的**！

```cpp
int x=xor(1,n);
cout<<x^b[i];
```