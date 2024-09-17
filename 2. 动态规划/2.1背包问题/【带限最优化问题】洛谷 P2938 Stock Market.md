# [USACO 09 FEB] Stock Market G

## 题面翻译

# 题目描述
尽管奶牛天生谨慎，它们仍然在住房抵押信贷市场中大受打击，现在它们准备在股市上碰碰运气。贝西有内部消息，她知道 $S$ 只股票在今后 $D$ 天内的价格。

假设在一开始，她筹集了 $M$ 元钱，那么她该怎样操作才能赚到最多的钱呢？贝西在每天可以买卖多只股票，也可以多次买卖同一只股票，交易单位必须是整数，数量不限。举一个牛市的例子：

假设贝西有 10 元本金，股票价格如下：

| 股票  | 今天的价格 | 明天的价格 | 后天的价格 |
| :-: | :---: | :---: | :---: |
| $A$ |  10   |  15   |  15   |
| $B$ |  13   |  11   |  20   |


最赚钱的做法是：今天买入 $A$ 股 1 张，到明天把它卖掉并且买入 B 股 1 张，在后天卖掉 B 股，这样贝西就有 24 元了。

# 输入格式 
第一行：三个整数 S， D 和 M，$2 ≤ S ≤ 50$ ; $2 ≤ D ≤ 10$ ; $1 ≤ M ≤ 200000$

第二行到第 S + 1 行：第 i + 1 行有 D 个整数： $P_{i;1}$ 到 $P_{i;D}$，表示第 $i$ 种股票在第一天到最后一天的售价，对所有$ 1 ≤ j ≤ D $，$ 1 ≤ Pi $;$ j ≤ 1000$
# 输出格式
 单个整数：表示奶牛可以获得的最大钱数，保证这个数不会超过 $500000$

## 题目描述

Despite their innate prudence, the cows took a beating in the home mortgage market and now are trying their hand at stocks. Happily, Bessie is prescient and knows not only today's S (2 <= S <= 50) stock prices but also the future stock prices for a total of D days (2 <= D <= 10).

Given the matrix of current and future stock prices on various days (1 <= PR\_sd <= 1,000) and an initial M (1 <= M <= 200,000) units of money, determine an optimal buying and selling strategy in order to maximize the gain realized by selling stock on the final day. Shares must be purchased in integer multiples, and you need not spend all the money (or any money). It is guaranteed that you will not be able to earn a profit of more than 500,000 units of money.

Consider the example below of a bull (i.e., improving) market, the kind Bessie likes most. In this case, S=2 stocks and D=3 days. The cows have 10 units of money to invest.

| Stock | Today's price | Tomorrow's price | Two days hence Stock |
| :---: | :-----------: | :--------------: | :------------------: |
|  $A$  |      10       |        15        |          15          |
|  $B$  |      13       |        11        |          20          |

If money is to be made, the cows must purchase stock 1 on day 1. Selling stock 1 on day 2 and quickly buying stock 2 yields 4 money in the bank and one share of 2. Selling stock 2 on the final day brings in 20 money for a total of 24 money when the 20 is added to the bank.

## 输入格式

\* Line 1: Three space-separated integers: S, D, and M

\* Lines 2.. S+1: Line s+1 contains the D prices for stock s on days 1.. D: PR\_sd

## 输出格式

\* Line 1: The maximum amount of money possible to have after selling on day D.

## 样例 #1

### 样例输入 #1

```
2 3 10 
10 15 15 
13 11 20
```

### 样例输出 #1

```
24
```

## 题解
其实我们可以发现：**对于每一天只要最大化你的收益就可以达成目的**。然后问题就转换为求每一天的股票交易情况了。又知道每个股票可以无限量的购买（当然价值和不多于手中的钱），显然，就是一个完全背包。

那么对于每一天，我们都做一次完全背包，背包的体积是当前的资金，每个物品体积是当天的价值，价值为当天的价格减去前一天的价格。
首先对于每一天只要最大化我的受益就能达成目的，然后问题就转换为求每一天的交易情况了。有知道每个股票可以无限量的购买，显然这就是一个完全背包。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int s,d,m,maxx;
int map[60][20],dp[500001];
int main()
{
	scanf("%d%d%d",&s,&d,&m);
	for(int i=1;i<=s;i++)
		for(int j=1;j<=d;j++)
			scanf("%d",&map[i][j]);
	for(int i=2;i<=d;i++)
	{
		maxx=-1;
		memset(dp,0,sizeof(dp));
		for(int j=1;j<=s;j++)
			for(int k=map[j][i-1];k<=m;k++)
			{
				dp[k]=max(dp[k],dp[k-map[j][i-1]]+map[j][i]-map[j][i-1]);
				maxx=max(maxx,dp[k]);
			}
		m+=maxx;
	}
	printf("%d",m);
	return 0;
```