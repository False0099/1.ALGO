# Hossam and Friends

## 题面翻译

有 $t$ 组数据，每组数据中给出两个数 $n$ 和 $m$，和 $m$ 个数对 $(x_i, y_i)$。求有多少个数对 $(a, b)$ 满足 $1\le a \le b \le n$ ，且不存在一个 $i$，使得 $a \le x_i, y_i \le b$。

## 题目描述

Hossam makes a big party, and he will invite his friends to the party.

He has $ n $ friends numbered from $ 1 $ to $ n $ . They will be arranged in a queue as follows: $ 1, 2, 3, \ldots, n $ .

Hossam has a list of $ m $ pairs of his friends that don't know each other. Any pair not present in this list are friends.

A subsegment of the queue starting from the friend $ a $ and ending at the friend $ b $ is $ [a, a + 1, a + 2, \ldots, b] $ . A subsegment of the queue is called good when all pairs of that segment are friends.

Hossam wants to know how many pairs $ (a, b) $ there are ( $ 1 \le a \le b \le n $ ), such that the subsegment starting from the friend $ a $ and ending at the friend $ b $ is good.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 2 \cdot 10^4 $ ), the number of test cases. Description of the test cases follows.

The first line of each test case contains two integer numbers $ n $ and $ m $ ( $ 2 \le n \le 10^5 $ , $ 0 \le m \le 10^5 $ ) representing the number of friends and the number of pairs, respectively.

The $ i $ -th of the next $ m $ lines contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i, y_i\le n $ , $ x_i \neq y_i $ ) representing a pair of Hossam's friends that don't know each other.

Note that pairs can be repeated.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ , and the sum of $ m $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case print an integer — the number of good subsegments.

## 样例 #1

### 样例输入 #1

```
2
3 2
1 3
2 3
4 2
1 2
2 3
```

### 样例输出 #1

```
4
5
```

## 提示

In the first example, the answer is $ 4 $ .

The good subsegments are:

\[1\]

\[2\]

\[3\]

\[1, 2\]

In the second example, the answer is $ 5 $ .

The good subsegments are:

\[1\]

\[2\]

\[3\]

\[4\]

\[3, 4\]

## 题解
题意：一个长度为 $n$ 的序列，有 $m$ 条边，求有多少对台法的 $l,r$,满足 $\forall l\leq i,j\leq r,i\neq j$, $i$ 和 $j$ 之间没有连边。
 设第 $i$ 条边连的两个点为 $l_i$ 和 $r_i$,其中 $l_i<r_i$,那么对于每一个 $l$,其对应的 $r$ 必须满足：$\forall1\leq i\leq$
 $m,l_i\geq l,\:r<r_{i\circ}$
 于是把边离线下来从右往左扫一遍就好了。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Std{
void gi(int &x){
	x=0;
	int y=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')y=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+(c&15);
		c=getchar();
	}
	x*=y;
}
int T,n,m,l[200010],r[200010],id[200010];
bool cmp(int x,int y){
	return l[x]<l[y];
}
void solve(){
	gi(n);
	gi(m);
	for(int i(1);i<=m;++i){
		gi(l[i]);
		gi(r[i]);
		if(l[i]>r[i])swap(l[i],r[i]);
		id[i]=i;
	}
	sort(id+1,id+1+m,cmp);
	int now(m),rr(n);
	long long ans(0);
	for(int i(n);i;--i){
		while(now&&l[id[now]]==i){
			rr=min(rr,r[id[now]]-1);
			--now;
		}
		ans+=rr-i+1;
	}
	printf("%lld\n",ans);
}
void main(){
	gi(T);
	while(T--)solve();
}
}  // namespace Std
#undef int
int main(){
	Std::main();
	return 0;
}
```