# Replace the Numbers

## 题面翻译

维护一个数列，这个数列初始为空。

对于这个数列，总共有 $q$ 次操作，每次操作分为如下两个种类：

1. `1 x`，意为在数列末尾加一个数字
2. `2 x y`，意为将数列中所有值为 $x$ 的数的值替换成 $y$

请在 $q$ 次操作后，输出这个数列。

$1\leqslant q,x,y\leqslant5*10^5$

## 题目描述

You have an array of integers (initially empty).

You have to perform $ q $ queries. Each query is of one of two types:

- " $ 1 $ $ x $ " — add the element $ x $ to the end of the array;
- " $ 2 $ $ x $ $ y $ " — replace all occurrences of $ x $ in the array with $ y $ .

Find the resulting array after performing all the queries.

## 输入格式

The first line contains a single integer $ q $ ( $ 1 \le q \le 5 \cdot 10^5 $ ) — the number of queries.

Next $ q $ lines contain queries (one per line). Each query is of one of two types:

- " $ 1 $ $ x $ " ( $ 1 \le x \le 5 \cdot 10^5 $ );
- " $ 2 $ $ x $ $ y $ " ( $ 1 \le x, y \le 5 \cdot 10^5 $ ).

It's guaranteed that there is at least one query of the first type.

## 输出格式

In a single line, print $ k $ integers — the resulting array after performing all the queries, where $ k $ is the number of queries of the first type.

## 样例 #1

### 样例输入 #1

```
7
1 3
1 1
2 1 2
1 2
1 1
1 2
2 1 3
```

### 样例输出 #1

```
3 2 2 3 2
```

## 样例 #2

### 样例输入 #2

```
4
1 1
1 2
1 1
2 2 2
```

### 样例输出 #2

```
1 2 1
```

## 样例 #3

### 样例输入 #3

```
8
2 1 4
1 1
1 4
1 2
2 2 4
2 4 3
1 2
2 2 7
```

### 样例输出 #3

```
1 3 3 7
```

## 提示

In the first example, the array changes as follows:

 $ [] $ $ \rightarrow $ $ [3] $ $ \rightarrow $ $ [3, 1] $ $ \rightarrow $ $ [3, 2] $ $ \rightarrow $ $ [3, 2, 2] $ $ \rightarrow $ $ [3, 2, 2, 1] $ $ \rightarrow $ $ [3, 2, 2, 1, 2] $ $ \rightarrow $ $ [3, 2, 2, 3, 2] $ .

In the second example, the array changes as follows:

 $ [] $ $ \rightarrow $ $ [1] $ $ \rightarrow $ $ [1, 2] $ $ \rightarrow $ $ [1, 2, 1] $ $ \rightarrow $ $ [1, 2, 1] $ .

In the third example, the array changes as follows:

 $ [] $ $ \rightarrow $ $ [] $ $ \rightarrow $ $ [1] $ $ \rightarrow $ $ [1, 4] $ $ \rightarrow $ $ [1, 4, 2] $ $ \rightarrow $ $ [1, 4, 4] $ $ \rightarrow $ $ [1, 3, 3] $ $ \rightarrow $ $ [1, 3, 3, 2] $ $ \rightarrow $ $ [1, 3, 3, 7] $ .

## 题解
我们本题的思路是：通过我们的一个并查集维护我们哪些位置的值是相同的。然后再用一个 val 来维护我们每一个相同的值具体是多少，最后再用一个 tr 表示我们每一个值的对应位置是哪里，这个是为了方便我们的操作 1。

```cpp
ll q,n,fa[500005],val[500005],tr[500005],a[500005];
il ll getfa(ll x){while(x^fa[x])x=fa[x]=fa[fa[x]];ret x;}
int main()
{
	q=rd();
	for(int i=1;i<=q;++i)
	{
		ll op=rd(),x=rd(),y;
		if(op==1)a[++n]=i,fa[i]=i,val[i]=x,(tr[x])?fa[i]=tr[x]:(tr[x]=i);
		else
		{
			y=rd();
			if(x==y||!tr[x])continue;
			if(!tr[y])val[tr[y]=tr[x]]=y,tr[x]=0;
			else fa[getfa(tr[x])]=getfa(tr[y]),tr[x]=0,fa[i]=i;
		}
	}
	for(int i=1;i<=n;++i)prt(val[getfa(a[i])]," \n"[i==n]);
	ret 0;
}
```