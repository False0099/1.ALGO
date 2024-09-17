# Vlad and a Pair of Numbers

## 题面翻译

共有 $t$ 组数据。

每组数据你会得到一个正整数 $x$，你需要构造一组正整数 $a$ 和 $b$，满足：

- $a + b = x \times 2$；

- $a \operatorname{xor} b = x$，其中 $\operatorname{xor}$ 指异或。

输出你构造的 $a$ 和 $b$。如有多解，任意输出一解即可。如无解，输出 $-1$。

$1 \leq t \leq 10^4$，$1 \leq x \leq 2^{29}$。同时，你需要保证你构造的 $a$，$b$ 满足 $1 \leq a,b \leq 2^{30}$。

## 题目描述

Vlad found two positive numbers $ a $ and $ b $ ( $ a, b>0 $ ). He discovered that $ a \oplus b = \frac{a + b}{2} $ , where $ \oplus $ means the [bitwise exclusive OR](http://tiny.cc/xor_wiki_eng) , and division is performed without rounding..

Since it is easier to remember one number than two, Vlad remembered only $ a\oplus b $ , let's denote this number as $ x $ . Help him find any suitable $ a $ and $ b $ or tell him that they do not exist.

## 输入格式

The first line of the input data contains the single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases in the test.

Each test case is described by a single integer $ x $ ( $ 1 \le x \le 2^{29} $ ) — the number that Vlad remembered.

## 输出格式

Output $ t $ lines, each of which is the answer to the corresponding test case. As the answer, output $ a $ and $ b $ ( $ 0 < a, b \le 2^{32} $ ), such that $ x = a \oplus b = \frac{a + b}{2} $ . If there are several answers, output any of them. If there are no matching pairs, output -1.

## 样例 #1

### 样例输入 #1

```
6
2
5
10
6
18
36
```

### 样例输出 #1

```
3 1
-1
13 7
-1
25 11
50 22
```

## 题解
对于二进制加法，$a+b$ 可以拆分 $a$ xor $b$ 和两个 $a$ and $b$,即
$$a+b=(a\operatorname{xor}b)+2\cdot(a\operatorname{and}b)$$
结合题目给的公式
$$a+b=2\cdot(a\operatorname{xor}b)$$
得
$$a\operatorname{and}b=\frac{a\operatorname{xor}b}2$$
如果 $a\operatorname{xor}b$ 是奇数，或者 $(a\operatorname{xor}b)\operatorname{and}(a\operatorname{and}b)\neq0$,那么无解。后者是因为 $a\operatorname{xor}b$ 中的 1 说明在这个比特位上必定一个是 0 另一个是 1, and 结果必定是 0, 所以 $a\operatorname{xor}b$ 和 $a\operatorname{and}b$ 在同一个比特位上不可能都是 1，所以 $(a$ xor $b)$ and $(a$ and $b)=0$ 恒成立。从集合的角度上来说就是 $a$ xor $b$ 和 $a$ and $b$ 不相交。
现在 $a$ and $b$ 和 $a$ xor $b$ 都知道了，可以构造出一组解了。
由于 $a$ and $b$ 中的 1 在 $a$ 和 $b$ 中都有，而 $a$ xor $b$ 中的 1 要么在 $a$ 中，要么在 $b$ 中，不妨全部给 $a$,得
$$\begin{cases}a=(a\:\text{xor}\:b)\:\text{or}\:(a\:\text{and}\:b)=(a\:\text{xor}\:b)+(a\:\text{and}\:b)=\dfrac{3(a\:\text{xor}\:b)}{2}\\b=a\:\text{and}\:b=\dfrac{a\:\text{xor}\:b}{2}\end{cases}$$

```
#include<bits/stdc++.h>
using namespace std;
inline long long read();
int main()
{
	int t=read();
	while(t--)
	{
		int x=read(),a=x/2,b=x*2-a;
		if((a^b)==x)
			cout<<a<<" "<<b<<"\n";
		else
			cout<<"-1\n";
	}
	return 0;
}

```