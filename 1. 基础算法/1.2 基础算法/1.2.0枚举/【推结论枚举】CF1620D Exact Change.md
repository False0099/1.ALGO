# Exact Change

## 题面翻译

- 有 $n$ 个物品，第 $i$ 个物品价格为 $a_i$。
- 有三种货币，面值分别为 $1,2,3$。
- 求最小需要多少张货币，才能表出所有的 $a_i$。
- 多组测试数据。
- $1 \leq t \leq 1000,1 \leq n \leq 100,1 \leq a_i \leq 10^9$。

## 题目描述

One day, early in the morning, you decided to buy yourself a bag of chips in the nearby store. The store has chips of $ n $ different flavors. A bag of the $ i $ -th flavor costs $ a_i $ burles.

The store may run out of some flavors, so you'll decide which one to buy after arriving there. But there are two major flaws in this plan:

1. You have only coins of $ 1 $ , $ 2 $ and $ 3 $ burles;
2. Since it's morning, the store will ask you to pay in exact change, i. e. if you choose the $ i $ -th flavor, you'll have to pay exactly $ a_i $ burles.

Coins are heavy, so you'd like to take the least possible number of coins in total. That's why you are wondering: what is the minimum total number of coins you should take with you, so you can buy a bag of chips of any flavor in exact change?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

The first line of each test case contains the single integer $ n $ ( $ 1 \le n \le 100 $ ) — the number of flavors in the store.

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the cost of one bag of each flavor.

## 输出格式

For each test case, print one integer — the minimum number of coins you need to buy one bag of any flavor you'll choose in exact change.

## 样例 #1

### 样例输入 #1

```
4
1
1337
3
10 8 10
5
1 2 3 4 5
3
7 77 777
```

### 样例输出 #1

```
446
4
3
260
```

## 提示

In the first test case, you should, for example, take with you $ 445 $ coins of value $ 3 $ and $ 1 $ coin of value $ 2 $ . So, $ 1337 = 445 \cdot 3 + 1 \cdot 2 $ .

In the second test case, you should, for example, take $ 2 $ coins of value $ 3 $ and $ 2 $ coins of value $ 2 $ . So you can pay either exactly $ 8 = 2 \cdot 3 + 1 \cdot 2 $ or $ 10 = 2 \cdot 3 + 2 \cdot 2 $ .

In the third test case, it's enough to take $ 1 $ coin of value $ 3 $ and $ 2 $ coins of value $ 1 $ .

## 题解
我们本题的思路是：找到我们的关键性质：我们的 1 元纸币和 2 元元纸币的张数每一种最多不超过 2 种。

于是，我们可以考虑枚举我们 1 元元纸币的张数和二元纸币的张数，然后再去依次计算我们每一个取值的最大花费是多少。然后我们再去去区间 max 即可。

```cpp
ll slv(ll t1,ll t2)
{
	ll res=-1;
	for(int i=1;i<=n;++i)
	{
		ll u=inf;
		for(int j=0;j<=t1;++j)
		{
			for(int k=0;k<=t2;++k)
			{
				ll r=a[i]-j-k-k;
				if(r<0)continue;
				if(!(r%3))tomin(u,r/3);
			}
		}
		tomax(res,u);
	}
	ret res+t1+t2;
}
```