# Welfare State

## 题面翻译

有 $n$ 个数，$q$ 个操作。 

操作有两种：

``1 p x``：将 $p$ 位置上的数变为 $x$。  

``2 x``：将所有小于 $x$ 的数变为 $x$。

输出经过 $q$ 次操作后的这 $n$ 个数。

## 题目描述

There is a country with $ n $ citizens. The $ i $ -th of them initially has $ a_{i} $ money. The government strictly controls the wealth of its citizens. Whenever a citizen makes a purchase or earns some money, they must send a receipt to the social services mentioning the amount of money they currently have.

Sometimes the government makes payouts to the poor: all citizens who have strictly less money than $ x $ are paid accordingly so that after the payout they have exactly $ x $ money. In this case the citizens don't send a receipt.

You know the initial wealth of every citizen and the log of all events: receipts and payouts. Restore the amount of money each citizen has after all events.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^{5} $ ) — the numer of citizens.

The next line contains $ n $ integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ ( $ 0 \le a_{i} \le 10^{9} $ ) — the initial balances of citizens.

The next line contains a single integer $ q $ ( $ 1 \le q \le 2 \cdot 10^{5} $ ) — the number of events.

Each of the next $ q $ lines contains a single event. The events are given in chronological order.

Each event is described as either 1 p x ( $ 1 \le p \le n $ , $ 0 \le x \le 10^{9} $ ), or 2 x ( $ 0 \le x \le 10^{9} $ ). In the first case we have a receipt that the balance of the $ p $ -th person becomes equal to $ x $ . In the second case we have a payoff with parameter $ x $ .

## 输出格式

Print $ n $ integers — the balances of all citizens after all events.

## 样例 #1

### 样例输入 #1

```
4
1 2 3 4
3
2 3
1 2 2
2 1
```

### 样例输出 #1

```
3 2 3 4
```

## 样例 #2

### 样例输入 #2

```
5
3 50 2 1 10
3
1 2 0
2 8
1 3 20
```

### 样例输出 #2

```
8 8 20 8 10
```

## 提示

In the first example the balances change as follows: 1 2 3 4 $ \rightarrow $ 3 3 3 4 $ \rightarrow $ 3 2 3 4 $ \rightarrow $ 3 2 3 4

In the second example the balances change as follows: 3 50 2 1 10 $ \rightarrow $ 3 0 2 1 10 $ \rightarrow $ 8 8 8 8 10 $ \rightarrow $ 8 8 20 8 10


## 题解
我们本题的关键在于正确的认识我们的操作 2：将所有小于 $x$ 的数变为 $x$,其实这一个操作，可以转换为：$a_{i}=max(a_{i},x)$,也就是类似于 [[长期项目/1.算法题目/3. 高级数据结构/2.2.线段树/【暴力操作】hdu 5306 Gorgeous Sequence]]，我们只需要采用和这个一样的数据结构即可完成本题。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[200005];
struct node{
	int l,r,lazy;//lazy表示当前区间被哪个x值更新，叶子节点的懒标记也可以表示a数组的值
} s[800020];
void build(int k,int l,int r){//递归建树
	s[k].l=l;s[k].r=r;s[k].lazy=0;
	if(l==r){
		s[k].lazy=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
}
void change(int x){
	s[1].lazy=max(s[1].lazy,x);//区间修改，因为修改的是[1,n]所以我们只用更新根节点的懒标记
}
void pushdown(int k){//懒标记下传
	s[k<<1].lazy=max(s[k<<1].lazy,s[k].lazy);
	s[k<<1|1].lazy=max(s[k<<1|1].lazy,s[k].lazy);
	s[k].lazy=0;
}
void modify(int k,int ind,int x){//单点修改
	if(s[k].l==s[k].r){
		s[k].lazy=x;
		return;
	}
	pushdown(k);
	int mid=(s[k].l+s[k].r)>>1;
	if(ind<=mid)	modify(k<<1,ind,x);
	else			modify(k<<1|1,ind,x);
}
int ask(int k,int ind){//单点查询
	if(s[k].l==s[k].r){
		return s[k].lazy;
	}
	pushdown(k);
	int mid=(s[k].l+s[k].r)>>1;
	if(ind<=mid)	return ask(k<<1,ind);
	else			return ask(k<<1|1,ind);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>a[i];
	build(1,1,n);
	int T;cin>>T;
	while(T--){
		int type;cin>>type;
		if(type==1){
			int p,x;cin>>p>>x;
			modify(1,p,x);
		}
		else{
			int x;cin>>x;
			change(x);
		}
	}
	for(int i=1;i<=n;i++)	cout<<ask(1,i)<<" ";
}
```