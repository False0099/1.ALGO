# Binary Strings are Fun

## 题面翻译

给你一个长度为 $m$ 的二进制字符串 $a$, 我们对于此长度为 $m$ 的字符串，以每两位为单位，分别向其中插入 0 或 1。可以证明，这一共有 $2^{m-1}$ 种情况，因为在补充时，每一位都有 0 或 1 两种选择，一共 $m-$ 1 组，所以一共有这么多种情况。现在需要在这些情况中，求出“好字符串"的数量。

 关于“好字符串”的定义：在一个长度为 $m$ 的字符串中，已经完成插入操作，得到新字符串后，若对于所有
 在 $1\leq i\leq2\times m-1$ 的奇数 $i$, $a_i$ 是在 $a_1\sim a_i$ 中出现次数最多的字符，则该字符串是“好字符串”。

## 题目描述

A binary string $ ^\dagger $ $ b $ of odd length $ m $ is good if $ b_i $ is the median $ ^\ddagger $ of $ b[1, i]^\S $ for all odd indices $ i $ ( $ 1 \leq i \leq m $ ).

For a binary string $ a $ of length $ k $ , a binary string $ b $ of length $ 2 k-1 $ is an extension of $ a $ if $ b_{2 i-1}=a_i $ for all $ i $ such that $ 1 \leq i \leq k $ . For example, 1001011 and 1101001 are extensions of the string 1001. String $ x= $ 1011011 is not an extension of string $ y= $ 1001 because $ x_3 \neq y_2 $ . Note that there are $ 2^{k-1} $ different extensions of $ a $ .

You are given a binary string $ s $ of length $ n $ . Find the sum of the number of good extensions over all prefixes of $ s $ . In other words, find $ \sum_{i=1}^{n} f (s[1, i]) $ , where $ f (x) $ gives number of good extensions of string $ x $ . Since the answer can be quite large, you only need to find it modulo $ 998\, 244\, 353 $ .

 $ ^\dagger $ A binary string is a string whose elements are either $ \mathtt{0} $ or $ \mathtt{1} $ .

 $ ^\ddagger $ For a binary string $ a $ of length $ 2 m-1 $ , the median of $ a $ is the (unique) element that occurs at least $ m $ times in $ a $ .

 $ ^\S $ $ a[l, r] $ denotes the string of length $ r-l+1 $ which is formed by the concatenation of $ a_l, a_{l+1},\ldots, a_r $ in that order.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ), where $ n $ is the length of the binary string $ s $ .

The second line of each test case contains the binary string $ s $ of length $ n $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print the answer modulo $ 998\, 244\, 353 $ .

## 样例 #1

### 样例输入 #1

```
6
1
1
1
0
2
11
3
010
9
101101111
37
1011011111011010000011011111111011111
```

### 样例输出 #1

```
1
1
3
3
21
365
```

## 提示

In the first and second test cases, $ f (s[1,1])=1 $ .

In the third test case, the answer is $ f (s[1,1])+f (s[1,2])=1+2=3 $ .

In the fourth test case, the answer is $ f (s[1,1])+f (s[1,2])+f (s[1,3])=1+1+1=3 $ .

 $ f (\mathtt{11})=2 $ because two good extensions are possible: 101 and 111.

 $ f (\mathtt{01})=1 $ because only one good extension is possible: 011.

## 题解
我们题目是给定一个 01字符串，问这个 01 字符串的所有子串经过扩展后有多少字符串是美的？

我们考虑对于每一个前缀由上一个前缀推导而来，这里我们可以考虑递推。并且我们**当前位置是否合法**，只与我们当前位置填什么，以及**上一个位置合法的方案数**有关。**与我们上一个状态是什么没有关系**。

首先，因为我们是 0-1 字符串，并且我们的长度一定为奇数，所以我们的 0-1 字符串的中位数一定是我们 0-1 字符串中出现更多的那一个数字，如果我们 0 出现的多，那么我们的结果就是 0，如果我们的 1 出现的多，那么我们的结果就是 1.

首先，我们可以发现，如果我们前后两个字符是相同的，那么我们扩展的时候，这个位置能填的方案书就是我们上一个位置能填的方案数 * 2，这里是因为我们不管选择什么，更多的一定是我们的前面出现的那个数，而那个数字出现在奇数位，我们的偶数位没有影响。

之后，我们思考，如果我们前后两个字符是不同的，那么我们扩展的时候，这个位置能填的方案数只有 1 种，就是和后面的一样。这是因为我们如果填和前面一样的话，我们的后一位肯定不可能是出现次数最多的，不满足我们的条件。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define pf printf
#define test int T = rd(); while (T--)
#define F(i, a, b) for (int i = (a); i <= (b); ++i)
#define fr freopen("input.txt", "r", stdin);
#define IO ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define yes printf("YES\n");
#define no printf("NO\n");
#define int long long
inline int rd()
{
    char c=getchar(); int x=0, s=1;
    while(c<'0'||c>'9') { if(c=='-')s=-1;c=getchar();}
    while(c>='0'&&c<= '9') { x=(x<<3)+(x<<1)+c-'0';c=getchar();}
    return x*s;
}
char a[2000010];
const int mod = 998244353;
signed main()
{
	test
	{
		int n, ans = 1, tot = 0;
		cin >> n;
		a[0] = '!';
		F(i, 1, n)
		{
			cin >> a[i];
			if (a[i] == a[i - 1]) ans = ans * 2 % mod;
			else ans = 1;
			tot = (tot + ans) % mod;
		}
		printf("%lld\n", tot);
	}
    return 0;
}
```