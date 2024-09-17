# Count Binary Strings

## 题面翻译

有一个长度为 $n$ 的 01 串 $s$（下标从 $1$ 开始）和一些限制 $a_{i,j}(1 \le i \le j \le n)$。

$a_{i,j}$ 的含义如下：

| $a_{i,j}=$ |                     含义                     |     |
| :--------: | :----------------------------------------: | --- |
|    $0$     |                    没有限制                    |     |
|    $1$     |  对于所有的 $i \le p \le q \le j$ 均有 $s_p=s_q$  |     |
|    $2$     | 存在 $i \le p \le q \le j$ 使得 $s_p \neq s_q$ |     |

求可能的 $s$ 的个数。**答案对 $998244353$ 取模。**

------------

对于 $100\%$ 的数据，$2 \le n \le 100$，$0 \le a_{i,j} \le 2$。

## 题目描述

You are given an integer $ n $ . You have to calculate the number of binary (consisting of characters 0 and/or 1) strings $ s $ meeting the following constraints.

For every pair of integers $ (i, j) $ such that $ 1 \le i \le j \le n $ , an integer $ a_{i, j} $ is given. It imposes the following constraint on the string $ s_i s_{i+1} s_{i+2} \dots s_j $ :

- If $ a_{i, j} = 1 $ , all characters in $ s_i s_{i+1} s_{i+2} \dots s_j $ should be the same;
- If $ a_{i, j} = 2 $ , there should be at least two different characters in $ s_i s_{i+1} s_{i+2} \dots s_j $ ;
- If $ a_{i, j} = 0 $ , there are no additional constraints on the string $ s_i s_{i+1} s_{i+2} \dots s_j $ .

Count the number of binary strings $ s $ of length $ n $ meeting the aforementioned constraints. Since the answer can be large, print it modulo $ 998244353 $ .

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 100 $ ).

Then $ n $ lines follow. The $ i $ -th of them contains $ n-i+1 $ integers $ a_{i, i}, a_{i, i+1}, a_{i, i+2}, \dots, a_{i, n} $ ( $ 0 \le a_{i, j} \le 2 $ ).

## 输出格式

Print one integer — the number of strings meeting the constraints, taken modulo $ 998244353 $ .

## 样例 #1

### 样例输入 #1

```
3
1 0 2
1 0
1
```

### 样例输出 #1

```
6
```

## 样例 #2

### 样例输入 #2

```
3
1 1 2
1 0
1
```

### 样例输出 #2

```
2
```

## 样例 #3

### 样例输入 #3

```
3
1 2 1
1 0
1
```

### 样例输出 #3

```
0
```

## 样例 #4

### 样例输入 #4

```
3
2 0 2
0 1
1
```

### 样例输出 #4

```
0
```

## 提示

In the first example, the strings meeting the constraints are 001, 010, 011, 100, 101, 110.

In the second example, the strings meeting the constraints are 001, 110.

## 题解
我们不妨从一个更简单的问题开始入手，假设我们没有我们的限制 2，我们应该怎么去操作？

我们如果没有限制 2，显然我们可以用一个并查集来统计我们相同的段有哪些，然后我们我们最后的结果就是我们的 $2^k$。

然后我们再去考虑我们没有限制 1，我们只考虑限制 2，我们应该怎么操作？我们的思路是：设置一个 $dp[i][j]$ 表示我们到 i 位置，并且我们的 $(j,i)$ 都相等的方案数。
然后假设我们有限制：$(a,b)$ 至少有一个不同，那么我们的转移就有两种方式：一种是连上之前的最长段，即：$f[i][u]=f[i-1][u]$ 但我们的转移需要满足条件：$u>lim[u]$,
第二种是直接连一段新的，我们就可以有：
$f[i][i]=\sum f[i-1][u]$
最后，我们考虑怎么把我们的上面的限制条件叠加起来。

我们考虑用我们的状态 2 中的 dp 方程来进行计算。

我们考虑在哪些位置限制我们的状态转移：
我们发现，我们的转移 1 需要满足：我们的 $u$ 和我们的 $i$ 不在一个并查集中。

我们的转移 2 需要满足：$i$ 不与其他位置相等。



```cpp
typedef pair<int,int> pii;
const int N = 5010,INF = 0x3f3f3f3f3f3f3f3f,mod = 998244353;

int lim[N],p[N];
int f[N][N];

int find(int x)
{
	if(p[x] != x) p[x] = find(p[x]);
	return p[x];
}

void merge(int l,int r)
{
	for(int i=find(r);i>l;i=find(i)) p[i] = p[i-1];
}

signed main()
{
	int n;
	rd(n);
	for(int i=1;i<=n;i++) p[i] = i;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
		{
			int op;
			rd(op);
			if(op == 1)	merge(i,j);
			if(op == 2) lim[j] = max(lim[j],i+1);
			if(i==j && op == 2)
			{
				cout << 0;
				return 0;
			}
		}
	f[1][1] = 1;
	for(int i=2;i<=n;i++)
	{
		for(int j=lim[i];j<=find(i);j++)
			f[i][j] = f[i-1][j];
		if(find(i) == i)
			for(int j=1;j<n;j++) 
				f[i][i] = (f[i][i] + f[i-1][j]) % mod;
	}
	int ans = 0;
	for(int i=find(i);i<=n;i++)
		ans = (ans+f[n][i]) % mod;
	cout << ans*2 % mod << endl;
	return 0;
}
```