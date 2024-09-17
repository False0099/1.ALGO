# Cards

## 题面翻译

有 $m$ 张牌，其中一张是王牌。现在你执行 $n$ 次如下操作：洗牌后查看第一张牌是什么。

令 $x$ 为洗牌后第一张牌为王牌的次数，现在假设洗牌时 $m!$ 种牌的排列出现的概率均相等，求 $x^k$ 的期望值。

## 题目描述

Consider the following experiment. You have a deck of $ m $ cards, and exactly one card is a joker. $ n $ times, you do the following: shuffle the deck, take the top card of the deck, look at it and return it into the deck.

Let $ x $ be the number of times you have taken the joker out of the deck during this experiment. Assuming that every time you shuffle the deck, all $ m! $ possible permutations of cards are equiprobable, what is the expected value of $ x^k $ ? Print the answer modulo $ 998244353 $ .

## 输入格式

The only line contains three integers $ n $ , $ m $ and $ k $ ( $ 1 \le n, m < 998244353 $ , $ 1 \le k \le 5000 $ ).

## 输出格式

Print one integer — the expected value of $ x^k $ , taken modulo $ 998244353 $ (the answer can always be represented as an irreducible fraction $ \frac{a}{b} $ , where $ b \mod 998244353 \ne 0 $ ; you have to print $ a \cdot b^{-1} \mod 998244353 $ ).

## 样例 #1

### 样例输入 #1

```
1 1 1
```

### 样例输出 #1

```
1
```

## 样例 #2

### 样例输入 #2

```
1 1 5000
```

### 样例输出 #2

```
1
```

## 样例 #3

### 样例输入 #3

```
2 2 2
```

### 样例输出 #3

```
499122178
```

## 样例 #4

### 样例输入 #4

```
998244352 1337 5000
```

### 样例输出 #4

```
326459680
```

## 题解
我们首先考虑我们的暴力推公式：令 $$p=1/m,\:q=1-p$$ 我们洗牌后王牌在第一张牌出现 x 次的概率为：$$\sum_{i=0}^n\binom nip^iq^{n-i}$$

再加上他对我们的结果的贡献，我们就有：
$$\sum_{i=0}^n\binom nip^iq^{n-i}i^k$$

我们可以吧我们后面的 $i^k$ 展开为第二类斯特林数。
$$\begin{gathered}
\sum_{i=0}^n\binom nip^iq^{n-i}\sum_{j=1}^k\begin{Bmatrix}k\\j\end{Bmatrix}i^{\underline{j}} \\
=\sum_{j=1}^k\begin{Bmatrix}k\\j\end{Bmatrix}\sum_{i=0}^n\binom nip^iq^{n-i}i^{\underline{j}} 
\end{gathered}$$
然后就是一系列痛苦的拆式子：
$$\begin{gathered}
=\sum_{i=j}^n\binom nip^i(1-p)^{n-i}\binom ijj! \\
=j!\binom nj\sum_{i=j}^n\binom{n-j}ip^i(1-p)^{n-i} \\
=n^j\sum_{i=0}^{n-j}\binom{n-j}ip^{i+j}(1-p)^{n-j-i} \\
=n^{\underline{j}}p^j 
\end{gathered}$$


$$\sum_{j=0}^k\begin{Bmatrix}k\\j\end{Bmatrix}n^jp^j$$

