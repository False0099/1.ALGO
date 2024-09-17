# Swap Game

## 题面翻译

Alice 和 Bob 两个人在玩游戏。

有一个长度为 $n$ 的序列 $a$，Alice 和 Bob 两人轮流完成一个操作，Alice 先开始。

每个人可以将数列的第一个数减 $1$，并将它与后面序列的一个数进行交换，如果一个人操作之前发现当前序列中的第一个数为 $0$，这个人就输了。

问如果两人都足够聪明，最后谁会赢？

输入输出格式及数据规模见原题面。

Translated by @ [CLCK](https://www.luogu.com.cn/user/323183)

## 题目描述

Alice and Bob are playing a game on an array $ a $ of $ n $ positive integers. Alice and Bob make alternating moves with Alice going first.

In his/her turn, the player makes the following move:

- If $ a_1 = 0 $ , the player loses the game, otherwise:
- Player chooses some $ i $ with $ 2\le i \le n $ . Then player decreases the value of $ a_1 $ by $ 1 $ and swaps $ a_1 $ with $ a_i $ .

Determine the winner of the game if both players play optimally.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ $ (1 \leq t \leq 2 \cdot 10^4) $ — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ $ (2 \leq n \leq 10^5) $ — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2 \ldots a_n $ $ (1 \leq a_i \leq 10^9) $ — the elements of the array $ a $ .

It is guaranteed that sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, if Alice will win the game, output "Alice". Otherwise, output "Bob".

You can output each letter in any case. For example, "alIcE", "Alice", "alice" will all be considered identical.

## 样例 #1

### 样例输入 #1

```
3
2
1 1
2
2 1
3
5 4 4
```

### 样例输出 #1

```
Bob
Alice
Alice
```

## 提示

In the first testcase, in her turn, Alice can only choose $ i = 2 $ , making the array equal $ [1, 0] $ . Then Bob, in his turn, will also choose $ i = 2 $ and make the array equal $ [0, 0] $ . As $ a_1 = 0 $ , Alice loses.

In the second testcase, once again, players can only choose $ i = 2 $ . Then the array will change as follows: $ [2, 1] \to [1, 1] \to [1, 0] \to [0, 0] $ , and Bob loses.

In the third testcase, we can show that Alice has a winning strategy.

## 题解
我们 Alice 的第一步操作肯定是把除了现在在操作的数字以外我们的最小的数换到我们的前面，那么如果在我们的剩余数字都很大的情况下，我们不难发现，我们的 $Bob$ 是必败的，那么我们的 $Bob$ 其实也不是没有获胜的可能性的，只有一种可能，也就是我们 $Alice$ 第一次操作完之后，我们的数字是最小的。

一道很水的博弈论，首先我们看先手情况，能发现无论 $b$ 怎么换 (后手称为 $b)$ , $a$ 只要找一个最小的数放上去，那在经过一番减后都为 0,也就是说无论 $b$ 一直选哪个数，只要 $a$ 一直把那个最小的数放上来，那 $b$ 每次肯定只能让那个数减，且 $b$ 没有选择空间，那 $b$ 该怎么赢呢？我们发现，$a$ 第一次减的一定是 $a_{1}$ ,也就是说，当后面所有数都大于或等于 $a_{1}$ 时，$b$ 肯定会一直换 $a_{1}$,即 $b$ 必胜，特判一下 $a_{1}$ 大于 $a_{i}$ 的情况就可以了。

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[100005]; 
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		bool fl=1;
		for(int j=2;j<=n;j++){
			if(a[1]>a[j]){
				cout<<"Alice"<<endl;
				fl=0;
				break;
			}
		}
		if(fl){
			cout<<"Bob"<<endl; 
		}
	} 
}

```