# Binary String Copying

## 题面翻译

小 C 获得了一个长度为 $n$ 的 01 串 $S$。

小 C 有 $m$ 次操作，每次操作形如 $[l, r]$，代表将 $S$ 复制，生成一个 $S$ 的副本，将副本 $[l, r]$ 区间内数字字符从小到大排序，第 $i$ 次操作生成的新串记为 $S_i$。操作间**互不影响，互相独立**。

求出有多少不同的 $S_i$。

**多测**，$t$ 组数据。

$1 \le t \le 10^4$$1 \le \sum n,\sum m \le 2 \times 10^5$。

感谢@ [船酱魔王](/user/420998)提供的翻译。

## 题目描述

You are given a string $ s $ consisting of $ n $ characters 0 and/or 1.

You make $ m $ copies of this string, let the $ i $ -th copy be the string $ t_i $ . Then you perform exactly one operation on each of the copies: for the $ i $ -th copy, you sort its substring $ [l_i; r_i] $ (the substring from the $ l_i $ -th character to the $ r_i $ -th character, both endpoints inclusive). Note that each operation affects only one copy, and each copy is affected by only one operation.

Your task is to calculate the number of different strings among $ t_1, t_2, \ldots, t_m $ . Note that the initial string $ s $ should be counted only if at least one of the copies stays the same after the operation.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 2 \cdot 10^5 $ ) — the length of $ s $ and the number of copies, respectively.

The second line contains $ n $ characters 0 and/or 1 — the string $ s $ .

Then $ m $ lines follow. The $ i $ -th of them contains two integers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le n $ ) — the description of the operation applied to the $ i $ -th copy.

The sum of $ n $ over all test cases doesn't exceed $ 2 \cdot 10^5 $ . The sum of $ m $ over all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

Print one integer — the number of different strings among $ t_1, t_2, \ldots, t_m $ .

## 样例 #1

### 样例输入 #1

```
3
6 5
101100
1 2
1 3
2 4
5 5
1 6
6 4
100111
2 2
1 4
1 3
1 2
1 1
0
1 1
```

### 样例输出 #1

```
3
3
1
```

## 提示

Consider the first example. Copies below are given in order of the input operations. Underlined substrings are substrings that are sorted:

1. 101100 $ \rightarrow $ 011100;
2. 101100 $ \rightarrow $ 011100;
3. 101100 $ \rightarrow $ 101100;
4. 101100 $ \rightarrow $ 101100;
5. 101100 $ \rightarrow $ 000111.

There are three different strings among $ t_1, t_2, t_3, t_4, t_5 $ : 000111, 011100 and 101100.

Consider the second example:

1. 100111 $ \rightarrow $ 100111;
2. 100111 $ \rightarrow $ 001111;
3. 100111 $ \rightarrow $ 001111;
4. 100111 $ \rightarrow $ 010111.

There are three different strings among $ t_1, t_2, t_3, t_4 $ : 001111, 010111 and 100111.

## 题解

**注意：我们的跳过要预处理，否则会超时

我们对于可以发现，对于每一个查询，只要我们在这个区间内已经是有序的了，那么这个对我们的贡献就是 0。对于每一个查询，我们只取他的**有效部分**：即如果末尾为 1，我们就直接跳过，不去考虑这个位置。然后我们记录这个有效部分，如果这个部分是之前已经记录过的，我们就直接跳过。最后计算我们一共有的总共次数即可。**另外，我们开头的 0 也可以直接跳过。**

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
char s[200010];
int l[200010];//左边第一个 0 的位置
int r[200010];//右边第一个 1 的位置
map<pair<int,int>,bool> p;

void solve()
{
	p.clear();
	cin >> n >> m >> s+1;
	int pos = 0;
	for (int i=1;i<=n;i++) 
	{
		if(s[i]=='0') pos = i;
		l[i] = pos;
	}
	pos = n+1;
	for (int i=n;i>=1;i--)
	{
		if(s[i]=='1') pos = i;
		r[i] = pos;
	}
	int ans = 0;
	for (int i=1;i<=m;i++)
	{
		int a,b;
		cin >> a >> b;
		a = r[a];//过滤掉左边的 0，相当于跳到右边的 1 
		b = l[b];//过滤掉右边的 1，相当于跳到左边的 0
		if(a>b) a = 1,b = 1;//这种情况属于排序排了个寂寞 
		if(p[make_pair(a,b)]==false)
		{
			p[make_pair(a,b)] = true;
			ans++;
		}
	}
	cout << ans << "\n";
	return;
} 
 
signed main()
{
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}
```