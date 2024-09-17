#字典序 
# Flipper

## 题面翻译

## 题目描述

给你一个长度为 $n$ 的数列 $ p $。



对于数列 $p$，进行一次如下操作：

- 选择一个区间 $[l, r]$（$1\le l\le r\le n$，一个区间是一串连续的数 ${p_l, p_{l+1}, \ldots, p_{r-1}, p_r}$），并将它反转过来。反转一个区间即交换如下的数对 $(p_l, p_r), (p_{l+1}, p_{r-1}),\dots, (p_{l + i}, p_{r - i})$（其中 $l + i \le r - i$）。
- 交换前缀和后缀：$[r+1, n]$ 和 $[1, l - 1]$（注意：这些区间可能是空的）。

例如，给定 $n = 5, p = \{2, \color{blue}{3}, \color{blue}{1}, 5, 4\}$，如果你选择区间 $[l = 2, r = 3]$，反转区间以后 $p = \{\color{green}{2}, \color{blue}{1}, \color{blue}{3}, \color{green}{5}, \color{green}{4}\color{black}\}$。接着交换区间 $ 4, 5]$ 与 $[1, 1]$。得到 $p = \{\color{green}{5}, \color{green}{4}, 1, 3, \color{green}{2}\color{black}\}$。可以证明这是操作后该排列的字典序的最大可能结果。

你需要输出通过一次所述操作后可以得到的字典序最大数列。

如果存在一个 $i$（$1 \le i \le n$），使 $ a_j = b_j $ 对于 $ 1 \le j < i $ 且 $ a_i > b_i $，那么一个数列 $ a $ 的字典序大于数列 $ b $ 的字典序。

## 输入格式

输入的第一行包含一个整数 $ t $，表示测试数据的组数。

对于每组数据：

第一行包含一个单一的整数 $ n $ 表示数列的长度。

第二行包含 $ n $ 个整数：$ p_1, p_2, \ldots, p_n $ 即数列 $ p $。


## 输出格式

对于每组测试数据，输出一行 $ n $ 个整数，表示经过一次操作后可以得到的字典序最大的数列。

## 说明提示

### 数据范围

对于 $ 100\% $ 的数据，$ 1 \le t \le 1000 $，$ 1 \le n \le 2000 $，保证每次 $ T $ 组测试数据的 $ n $ 之和不超过 $ 2000 $。

## 题目描述

You are given a permutation $ p $ of length $ n $ .

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ \{2,3,1,5,4\} $ is a permutation, while $ \{1,2,2\} $ is not (since $ 2 $ appears twice), and $ \{1,3,4\} $ is also not a permutation (as $ n=3 $ , but the array contains $ 4 $ ).

To the permutation $ p $ , you need to apply the following operation exactly once:

- First you choose a segment $ [l, r] $ ( $ 1 \le l \le r \le n $ , a segment is a continuous sequence of numbers $ \{p_l, p_{l+1}, \ldots, p_{r-1}, p_r\} $ ) and reverse it. Reversing a segment means swapping pairs of numbers $ (p_l, p_r) $ , $ (p_{l+1}, p_{r-1}) $ , ..., $ (p_{l + i}, p_{r - i}) $ (where $ l + i \le r - i $ ).
- Then you swap the prefix and suffix: $ [r+1, n] $ and $ [1, l - 1] $ (note that these segments may be empty).

For example, given $ n = 5, p = \{2, \color{blue}{3}, \color{blue}{1}, 5, 4\} $ , if you choose the segment $ [l = 2, r = 3] $ , after reversing the segment $ p = \{\color{green}{2}, \color{blue}{1}, \color{blue}{3}, \color{green}{5}, \color{green}{4}\} $ , then you swap the segments $ [4, 5] $ and $ [1, 1] $ . Thus, $ p = \{\color{green}{5}, \color{green}{4}, 1, 3, \color{green}{2}\} $ . It can be shown that this is the maximum possible result for the given permutation.

You need to output the lexicographically maximum permutation that can be obtained by applying the operation described exactly once.

A permutation $ a $ is lexicographically greater than permutation $ b $ if there exists an $ i $ ( $ 1 \le i \le n $ ) such that $ a_j = b_j $ for $ 1 \le j < i $ and $ a_i > b_i $ .

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

Then the descriptions of the test cases follow.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2000 $ ) — the size of the permutation.

The second line of each test case contains $ n $ integers: $ p_1, p_2, \ldots, p_n $ ( $ 1 \le p_i \le n $ ) — the permutation $ p $ itself.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2000 $ .

## 输出格式

For each test case, output in a separate line the lexicographically maximum permutation of length $ n $ that can be obtained from $ p $ by applying the operation described in the problem exactly once.

## 样例 #1

### 样例输入 #1

```
9
5
2 3 1 5 4
9
4 1 6 7 2 8 5 3 9
4
4 3 2 1
2
2 1
6
3 2 4 1 5 6
7
3 2 1 5 7 6 4
10
10 2 5 6 1 9 3 8 4 7
4
4 2 1 3
1
1
```

### 样例输出 #1

```
5 4 1 3 2 
9 4 1 6 7 2 8 5 3 
3 2 1 4 
1 2 
6 5 3 2 4 1 
7 6 4 5 3 2 1 
9 3 8 4 7 1 10 2 5 6 
3 4 2 1 
1
```

## 提示

The first example is explained in the problem statement.

In the second example, the segment $ [l = 9, r = 9] $ should be chosen.

In the third example, the segment $ [l = 1, r = 1] $ should be chosen.

In the fourth example, the segment $ [l = 1, r = 2] $ should be chosen.

In the fifth example, the segment $ [l = 5, r = 6] $ should be chosen.

In the sixth example, the segment $ [l = 4, r = 4] $ should be chosen.

In the seventh example, the segment $ [l = 5, r = 5] $ should be chosen.

## 题解
我们的整个字符串经过一次操作后，由下面的几个部分组成：
第一个部分：后缀（可以为空）
第二个部分：除了前缀后缀以外的元素反转
第三个部分：前缀

我们本题考虑把我们的整个序列分为下面几个部分：第一个部分是我们的求出我们的最大后缀。首先如果要让我们的答案最大，一定是让我们的后缀先最大，这个时候就相当于我们已经固定了我们操作的r


然后再去考虑我们的反转元素。这个位置的左端点显然应该是找 $r-1$ 以前的第一个比 $p_{1}$ 小的位置 $l$,然后我们就能得到我们的答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,p[2010];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		int l,r;
		for(int i=1;i<=n;i++){
			scanf("%d",&p[i]);
			if(p[i]==n) r=i;
		}
		if(r==1){
			for(int i=1;i<=n;i++){
				if(p[i]==n-1) r=i;
			}
		}
		if(r!=n) r--;
		l=r;
		for(int i=r-1;i>=1;i--){
			if(p[i]>p[1]) l--;
			else break;
		}
		for(int i=r+1;i<=n;i++) printf("%d ",p[i]);
		for(int i=r;i>=l;i--) printf("%d ",p[i]);
		for(int i=1;i<l;i++) printf("%d ",p[i]);
		putchar('\n');
	}
	return 0;
}
```