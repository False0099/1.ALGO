# Moderate Modular Mode

## 题面翻译

给定两个**偶数** $x,y$

求一个 $n \in [1,2\times10^{18}]$ 满足 $n \bmod x = y \bmod n$

一个测试点有多组数据，数据保证有解

## 题目描述

YouKn 0 wWho has two even integers $ x $ and $ y $ . Help him to find an integer $ n $ such that $ 1 \le n \le 2 \cdot 10^{18} $ and $ n \bmod x = y \bmod n $ . Here, $ a \bmod b $ denotes the remainder of $ a $ after division by $ b $ . If there are multiple such integers, output any. It can be shown that such an integer always exists under the given constraints.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^5 $ ) — the number of test cases.

The first and only line of each test case contains two integers $ x $ and $ y $ ( $ 2 \le x, y \le 10^9 $ , both are even).

## 输出格式

For each test case, print a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^{18} $ ) that satisfies the condition mentioned in the statement. If there are multiple such integers, output any. It can be shown that such an integer always exists under the given constraints.

## 样例 #1

### 样例输入 #1

```
4
4 8
4 2
420 420
69420 42068
```

### 样例输出 #1

```
4
10
420
9969128
```

## 提示

In the first test case, $ 4 \bmod 4 = 8 \bmod 4 = 0 $ .

In the second test case, $ 10 \bmod 4 = 2 \bmod 10 = 2 $ .

In the third test case, $ 420 \bmod 420 = 420 \bmod 420 = 0 $ .

## 题解
我们首先可以考虑按照我们的 $(x,y)$ 来进行分类讨论，假设我们现在有：$(x>y)$,那么我们很简单，我们只需要构造我们的 $n=x+y$ 即可。$(x=y)$ 的时候，我们也很简单，我们只需要构造我们的 $(n=x)$ 即可

现在我们的难点是考虑我们的 $(x<y)$ 的情况，我们首先手玩之后能够发现，假如我们有 $n=(x+y)\gg 1$,那么我们是可以作为我们的某一些可能的情况的。但在这之后，我们就束手无策了，我们应该怎么办？

我们注意到，我们的 $n$ 一定是西澳娱我们的 $y$ 的，我们应该怎么样利用这一个性质，假如我们有 $n<y$,那么我们不妨先假设我们的 $n=y-k$,其中 $k$ 是一个任意的数字。

那么这个时候，我们就可以有：
$(y-k)\text{ mod } x=y\text{ mod } (y-k)=k$,我们之后就有：$(y-k)=k+tx$,也就是说，我们有：$(2k=y-tx)$ 再进一步，我们就能够得到：$k=\dfrac{y-tx}{2}$。而在这里，我们的 $t$ 的取值是有讲究的，我们不能直接取 1，~~因为取 1 会报错~~，原因在于我们的 $k$ 是一个取模后的结果，也就是说我们的 $k$ 要满足 $k<x$，并且我们还需要满足我们的 $(k<(y-k))$,于是，我们不妨直接让我们的 $y-tx$ 转换为我们的 $(y\%x)$,得到的 $k$ 一定是满足我们的答案。


但是我们的 $k$ 并不是我们需要的答案，我们需要的答案是我们的：$(y-k)$,也就是说，我们最后的 $n=y-\dfrac{y-tx}{2}$ 我们经过变换后不难看出，

```cpp
int main(){
	int T; cin >> T;
	while(T--) {
		ll x, y, d; cin >> x >> y;
		if(x > y) cout << x + y << endl;
		else d = y / x * x, cout << d + (y % d / 2) << endl;
	}
    return 0;
}
```
