## 题目描述
中文版：给你一个数组 S 问你能否经过若干次操作把 S 编程 T，其中我们的操作是：选定一段 $(l,r)$，将 $(l,r)$ 中的每一个元素 $s[i]$ 都替换为 $s[i]\oplus s[i-l+1]$。


Vova really loves the [XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) operation (denoted as $\oplus$). Recently, when he was going to sleep, he came up with a fun game.

At the beginning of the game, Vova chooses two binary sequences $s$ and $t$ of length $n$ and gives them to Vanya. A binary sequence is a sequence consisting only of the numbers $0$ and $1$. Vanya can choose integers $l, r$ such that $1 \leq l \leq r \leq n$, and for all $l \leq i \leq r$ **simultaneously** replace $s_i$ with $s_i \oplus s_{i - l + 1}$, where $s_i$ is the $i$ \-th element of the sequence $s$.

In order for the game to be interesting, there must be a possibility to win. Vanya wins if, with an **unlimited** number of actions, he can obtain the sequence $t$ from the sequence $s$. Determine if the game will be interesting for the sequences $s$ and $t$.

## 题解
注意到，当我们取我们的 $l=r$ 时，我们的原操作就转变为我们的 $s[i]=s[i]\oplus s[1]$。显然，如果我们的 $s[1]$ 是一个 1 的时候，我们的后续元素可以任意进行我们的反转，但是，如果我们的 $s[1]\neq 1$ 的时候，我们应该怎么样处理？

我们首先可以知道，如果我们的第一位不是 1，并且我们的 $t[1]=1$，那么我们是一定不可能达到这一种状态的，这是因为我们的着一种状态显然是不可取的。

当我们的 $t[0]=0$ 时，这个时候，我们可以**不考虑我们的第一位，转换为我们的子问题 (2，n)范围**的子问题。这个时候，我们接着按照我们的之前的操作即可。

证明：

如果 $s_1=0$ , $t_1=0$ ,这意味着选择 $[l,r]$ 时，$s_l$ 依然保持不变；那么可以完全不考虑第一位，考虑新问题：·将 $S_{1..n-1}=s_{2..n}$ 变为 $T_{1..n-1}=t_{2..n}$ 是否可能？·两个问题是等价的，若有做法使得新问题成立，每次操作为 $[l_i,r_i]$ ,其实相当于在原问题中取
$[l_i,r_i+1]$ 这个区间。·因此，简单地不考虑这一位即可。

## 代码：
```cpp
void solve(){
	int n; cin >> n;
	string s, t; cin >> s >> t;
	for(int i = 0; i < n; i++) {
		if(s[i] == '1') {
			cout << "YES\n";
			return;
		}
		if(t[i] == '1') {
			cout << "NO\n";
			return;
		}
	}
	cout << "YES\n";
}
```