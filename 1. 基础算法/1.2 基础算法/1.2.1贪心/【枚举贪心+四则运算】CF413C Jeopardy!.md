# Jeopardy!

## 题面翻译

题意简述

“Jeopardy！”的决赛将有 n 问题，每个问题都有对应的得分 ai，其中有 m 个问题可以选择不得分，而将现有总得分翻倍。你可以安排关卡的通过顺序和策略，求最大得分。

输入输出格式

输入格式：

第一行包含两个整数。N 和 m (1<=n，m<=100；m<=min (n，30))分别代表问题总数和可翻倍问题总数。第二行包含 n 个整数 a 1, a 2,...,an (1<=ai<=1 e 7)代表每个问题的价值；第三行包含 m 个整数 b 1, b 2,...,bm (1<=bi<=n)代表可翻倍问题的编号。问题编号是从1到 n。

输出格式：

一行一个数字，表示通过所有关卡最大得分。保证该答案在 64 位带符号整型范围内。

感谢@Peter_Matthew 提供的翻译

## 题目描述

'Jeopardy!' is an intellectual game where players answer questions and earn points. Company Q conducts a simplified 'Jeopardy!' tournament among the best IT companies. By a lucky coincidence, the old rivals made it to the finals: company R 1 and company R 2.

The finals will have $ n $ questions, $ m $ of them are auction questions and $ n-m $ of them are regular questions. Each question has a price. The price of the $ i $ -th question is $ a_{i} $ points. During the game the players chose the questions. At that, if the question is an auction, then the player who chose it can change the price if the number of his current points is strictly larger than the price of the question. The new price of the question cannot be less than the original price and cannot be greater than the current number of points of the player who chose the question. The correct answer brings the player the points equal to the price of the question. The wrong answer to the question reduces the number of the player's points by the value of the question price.

The game will go as follows. First, the R 2 company selects a question, then the questions are chosen by the one who answered the previous question correctly. If no one answered the question, then the person who chose last chooses again.

All R 2 employees support their team. They want to calculate what maximum possible number of points the R 2 team can get if luck is on their side during the whole game (they will always be the first to correctly answer questions). Perhaps you are not going to be surprised, but this problem was again entrusted for you to solve.

## 输入格式

The first line contains two space-separated integers $ n $ and $ m $ $ (1<=n, m<=100; m<=min (n, 30)) $ — the total number of questions and the number of auction questions, correspondingly. The second line contains $ n $ space-separated integers $ a_{1}, a_{2},..., a_{n} $ $ (1<=a_{i}<=10^{7}) $ — the prices of the questions. The third line contains $ m $ distinct integers $ b_{i} $ $ (1<=b_{i}<=n) $ — the numbers of auction questions. Assume that the questions are numbered from $ 1 $ to $ n $ .

## 输出格式

In the single line, print the answer to the problem — the maximum points the R 2 company can get if it plays optimally well. It is guaranteed that the answer fits into the integer 64-bit signed type.

## 样例 #1

### 样例输入 #1

```
4 1
1 3 7 5
3
```

### 样例输出 #1

```
18
```

## 样例 #2

### 样例输入 #2

```
3 2
10 3 8
2 3
```

### 样例输出 #2

```
40
```

## 样例 #3

### 样例输入 #3

```
2 2
100 200
1 2
```

### 样例输出 #3

```
400
```

## 题解
本题的思路是：我们因为可以自由安排我们的顺序，我们一定是先加再乘，然后就可以枚举对于每一个 $k$,我们是选择先去加 $k$,还是去乘二，哪一个能够获得的更多。于是，我们就可以把我们的原数组按照从大到小排序，然后每一次对于我们的特殊元素，我们也将他们从大到小排序，然后每一次对于特殊元素，我们都选择贡献更大的哪一个。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int mps[10005], fb[100005];
bool cmp(int x, int y) {
	return x > y;
}
signed main() {
	int n, m, ans = 0;
	cin >> n >> m;
	for(int i = 1;i <= n;i++) {
		cin >> mps[i];
		ans += mps[i];
	}
	for(int i = 1;i <= m;i++) {
		cin >> fb[i];
		ans -= mps[fb[i]];
		fb[i] = mps[fb[i]];
	}
	sort(fb + 1, fb + 1 + n, cmp);
	for(int i = 1;i <= m;i++) {
		if(fb[i] > ans) {
			ans += fb[i];
		}
		else {
			ans *= 2;
		}
	}
	cout << ans << endl;
}

```