# Fox And Jumping

## 题面翻译

给出 $n$ 张卡片，分别有 $l_i$ 和 $c_i$。在一条无限长的纸带上，你可以选择花 $c_i$ 的钱来购买卡片 $i$，从此以后可以向左或向右跳 $l_i$ 个单位。问你至少花多少元钱才能够跳到纸带上全部位置。若不行，输出 $-1$。

## 题目描述

Fox Ciel is playing a game. In this game there is an infinite long tape with cells indexed by integers (positive, negative and zero). At the beginning she is standing at the cell 0.

There are also $ n $ cards, each card has 2 attributes: length $ l_{i} $ and cost $ c_{i} $ . If she pays $ c_{i} $ dollars then she can apply $ i $ -th card. After applying $ i $ -th card she becomes able to make jumps of length $ l_{i} $ , i. e. from cell $ x $ to cell $ (x-l_{i}) $ or cell $ (x+l_{i}) $ .

She wants to be able to jump to any cell on the tape (possibly, visiting some intermediate cells). For achieving this goal, she wants to buy some cards, paying as little money as possible.

If this is possible, calculate the minimal cost.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=300 $ ), number of cards.

The second line contains $ n $ numbers $ l_{i} $ ( $ 1<=l_{i}<=10^{9} $ ), the jump lengths of cards.

The third line contains $ n $ numbers $ c_{i} $ ( $ 1<=c_{i}<=10^{5} $ ), the costs of cards.

## 输出格式

If it is impossible to buy some cards and become able to jump to any cell, output -1. Otherwise output the minimal cost of buying such set of cards.

## 样例 #1

### 样例输入 #1

```
3
100 99 9900
1 1 1
```

### 样例输出 #1

```
2
```

## 样例 #2

### 样例输入 #2

```
5
10 20 30 40 50
1 1 1 1 1
```

### 样例输出 #2

```
-1
```

## 样例 #3

### 样例输入 #3

```
7
15015 10010 6006 4290 2730 2310 1
1 1 1 1 1 1 10
```

### 样例输出 #3

```
6
```

## 样例 #4

### 样例输入 #4

```
8
4264 4921 6321 6984 2316 8432 6120 1026
4264 4921 6321 6984 2316 8432 6120 1026
```

### 样例输出 #4

```
7237
```

## 提示

In first sample test, buying one card is not enough: for example, if you buy a card with length 100, you can't jump to any cell whose index is not a multiple of 100. The best way is to buy first and second card, that will make you be able to jump to any cell.

In the second sample test, even if you buy all cards, you can't jump to any cell whose index is not a multiple of 10, so you should output -1.

## 题解
我们考虑在什么情况下，我们是可以满足我们最后可以人一走，也就是说，我们有 $ax_{1}+bx_{2}+\dots+kx_{n}=1$ 要找到一组可行解。

那么，根据我们的 `exgcd` 的相关结论，我们就有：$gcd(a,\mathbf{b}..,k)=1$，我们于是就转变成下面的问题：在我们的原来的数列中，找到任意的数，使得他们的 $gcd$ 为 1，并且我们最后的代价最小。

那么我们就可以有：我们可以暴力枚举我们以 $i$ 为结尾时，我们的迁回一共有多少种可能的 gcd 值，然后计算我们的每一种 gcd 值对应的最小的代价是多少。于是，我们就可以计算出我们的结果。

```
// LUOGU_RID: 160702668
#include <bits/stdc++.h>
#define int long long
using namespace std;
void solve(){
	int n;
	cin>>n;
	vector<int> a(n);
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	vector<int> c(n);
	for(int i=0;i<n;i++){
		cin>>c[i];
	}
	map<int,int> gcdd;
	for(int i=0;i<n;i++){
		map<int,int> tmp=gcdd;
		if(gcdd[a[i]]==0){
			gcdd[a[i]]=c[i];
		}else{
			gcdd[a[i]]=min(c[i],gcdd[a[i]]);
		}
		for(auto u:tmp){
			int num=u.first;
			int cost=u.second;
			int v=__gcd(num,a[i]);
			if(gcdd[v]!=0){
				gcdd[v]=min(gcdd[v],cost+c[i]);
			}else{
				gcdd[v]=cost+c[i];
			}
		}
	}
	if(gcdd[1]==0){
		cout<<-1<<endl;
	} else{
		cout<<gcdd[1]<<endl;
	}
}
signed main(){
	int t;
	t=1;
	while(t--){
		solve();
	}
}
```