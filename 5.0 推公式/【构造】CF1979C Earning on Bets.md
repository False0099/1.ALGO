# Earning on Bets

## 题面翻译

有人提议让您玩一个游戏。在这个游戏中，有 $n$ 种可能的结果，对于每一种结果，您都必须下注一定**整数**的硬币。如果 $i$ 的结果是赢，您将获得与您在该结果上的投注额相等的硬币，再乘以 $k_i$。请注意， $n$ 个结果中有且只有一个结果是赢的。

你的任务是决定如何分配硬币，以便在出现任何**获胜结果时都能获胜**。更正式地说，你对所有结果下注的硬币总数必须严格地小于每个可能获胜的结果所得到的硬币数量。

## 题目描述

You have been offered to play a game. In this game, there are $ n $ possible outcomes, and for each of them, you must bet a certain integer amount of coins. In the event that the $ i $ -th outcome turns out to be winning, you will receive back the amount of coins equal to your bet on that outcome, multiplied by $ k_i $ . Note that exactly one of the $ n $ outcomes will be winning.

Your task is to determine how to distribute the coins in such a way that you will come out ahead in the event of any winning outcome. More formally, the total amount of coins you bet on all outcomes must be strictly less than the number of coins received back for each possible winning outcome.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 50 $ ) — the number of outcomes.

The second line of each test case contains $ n $ integers $ k_1, k_2,\ldots, k_n $ ( $ 2 \le k_i \le 20 $ ) — the multiplier for the amount of coins if the $ i $ -th outcome turns out to be winning.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output $ -1 $ if there is no way to distribute the coins as required. Otherwise, output $ n $ integers $ x_1, x_2,\ldots, x_n $ ( $ 1 \le x_i \le 10^{9} $ ) — your bets on the outcomes.

It can be shown that if a solution exists, there is always a solution that satisfies these constraints.

If there are multiple suitable solutions, output any of them.

## 样例 #1

### 样例输入 #1

```
6
3
3 2 7
2
3 3
5
5 5 5 5 5
6
7 9 3 17 9 13
3
6 3 2
5
9 4 6 8 3
```

### 样例输出 #1

```
27 41 12 
1 1 
-1
1989 1547 4641 819 1547 1071 
-1
8 18 12 9 24
```

## 提示

In the first test case, the coins can be distributed as follows: $ 27 $ coins on the first outcome, $ 41 $ coins on the second outcome, $ 12 $ coins on the third outcome. Then the total amount of coins bet on all outcomes is $ 27 + 41 + 12 = 80 $ coins. If the first outcome turns out to be winning, you will receive back $ 3 \cdot 27 = 81 $ coins, if the second outcome turns out to be winning, you will receive back $ 2 \cdot 41 = 82 $ coins, if the third outcome turns out to be winning, you will receive back $ 7 \cdot 12 = 84 $ coins. All these values are strictly greater than $ 80 $ .

In the second test case, one way is to bet one coin on each of the outcomes.

## 题解
本题我们考虑我们在每一个位置上安置的价格为 $t_{i}$,那么这个时候我们就有 $\forall j\in[1,n],\sum t_{i}>t_{j}k_{j}$,也就是说我们有 $n$ 个不等式，要我们构造出一个满足这个不等式的解。我们注意到，我们每一个不等式的左侧都是相同的，我么不妨设我们的不等式的左侧都是一个 $z$,那么我们就有：$z>t_{j}k_{j}$,我们这个时候，显然希望我们的 $t_{j}k_{j}$ 都是尽可能相同的。
考虑每种结果下注 $x_1,x_2,\cdots,x_n$ ，总投入 $tot=\sum_{i=1}^nx_i$ ，则有以下式子均成立：

$\begin{cases} &tot< k_1x_1 \\& tot< k_2x_2 \\ &\cdots \\& tot<k_nx_n \end{cases}$

右侧的 $k_1x_1,k_2x_2,\cdots,k_nx_n$ 应当均相等才最好，也就是说，我们的右侧可以转换为我们的下面的式子：$tot<min(k_{i}x_{i})$,因此我们最好就是让我们的右侧全部相等。反之设 $k_Mx_M$ 是其中最大的一个，且大于某一项 $k_mx_m$ ，那么还不如减少$x_M$ 到 $\frac{k_mx_m}{k_M}$ ，这样花费更少的钱，且约束条件一致。

因此，最优解中 $k_1x_1=k_2x_2=\cdots=k_nx_n$ ，如果可以取实数，则令 $x_1=1$ 就行了。这里只能输出整数，因此先求出最小公倍数 $L=\operatorname{lcm}(k_1,k_2,\cdots,k_n)$ ，然后 $x_i=\frac{L}{k_i}$ 即可。

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
void solve(){
	int n;
	cin>>n;
	vector<int> k(n);
	int lcm=1;
	for(int i=0;i<n;i++){
		cin>>k[i];
		lcm=lcm*k[i]/__gcd(k[i],lcm);
	}
	vector<int> ans(n);
	int sum=0;
	for(int i=0;i<n;i++){
		ans[i]=lcm/k[i];
		sum+=ans[i];
	}
	if (sum >= lcm) {
        printf("-1\n");
        return;
    }
	for(int i=0;i<n;i++){
		cout<<ans[i]<<" ";
	}
	puts("");
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}
```