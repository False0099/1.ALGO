# Long Legs

## 题面翻译

给你一个无限大小的棋盘，一个机器人初始位置为 $(0,0)$，初始每次可移动的长度为 $1$。  
对于一个当前在 $(x,y)$ 的机器人，且它当前的可移动长度为 $m$（初始为 $1$)。则它可以耗费一个时间进行如下操作：  
$\qquad$ 1. 移动到 $(x+m,y)$。  
$\qquad$ 2. 移动到 $(x,y+m)$。   
$\qquad$ 3. 使得 $m=m+1$。  
注意：在当前位置使得 $m=m+1$ 后会影响后面的操作。  
现在给你两个正整数 $a,b(1 \leq a,b \leq 10^9)$，问机器人最少需要多少单位时间可以到达 $(a,b)$。

## 题目描述

A robot is placed in a cell $ (0, 0) $ of an infinite grid. This robot has adjustable length legs. Initially, its legs have length $ 1 $ .

Let the robot currently be in the cell $ (x, y) $ and have legs of length $ m $ . In one move, it can perform one of the following three actions:

- Jump into the cell $ (x + m, y) $ ;
- Jump into the cell $ (x, y + m) $ ;
- increase the length of the legs by $ 1 $ , i. e. set it to $ m + 1 $ .

What's the smallest number of moves robot has to make to reach a cell $ (a, b) $ ?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases.

The only line of each test case contains two integers $ a $ and $ b $ ( $ 1 \le a, b \le 10^9 $ ) — the ending cell.

## 输出格式

For each test case, print a single integer — the smallest number of moves the robot is required to make to reach a cell $ (a, b) $ from a cell $ (0, 0) $ .

## 样例 #1

### 样例输入 #1

```
3
1 1
1 6
8 4
```

### 样例输出 #1

```
2
5
6
```

## 提示

In the first testcase, the robot can first jump to $ (0, 1) $ , then to $ (1, 1) $ . If it ever increases the length of its legs, it will only be able to jump past $ (1, 1) $ .

In the second testcase, the robot can jump to $ (1, 0) $ , then increase the length of its length to $ 2 $ and jump three times to reach $ (1, 6) $ .

In the third testcase, the robot can increase the length of its legs three times to make it $ 4 $ . Then jump to $ (0, 4) $ . Then jump twice to reach $ (8, 4) $ .

## 题解
本题的思路首先，我们确定我们的步长要变成多少，然后再根据我们要变成的步长，确定我们要预先走多少步。我们就能得到我们的公式：
$ans=\frac{x}{t}+\frac{y}{t}+(t-1)+(x\%t)+(t\%t)$,这里，我们因为我们的整出运算，所以我们就需要枚举我们的 $t$ 的可能的取值范围，注意到，我们的 $t$ 是一个单峰函数，所以理论上可以采用我们的三分法，不过因为我们的范围较小，我们也可以考虑枚举我们的答案。
```cpp
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T, a, b, ans;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while (T--) {
		cin >> a >> b;
		ans = a + b;           //初始化 ans 最大值 
		for (int i = 1; i <= 100000; i++) {           //枚举到 10^5 即可 
			ans = min(ans, (a + i - 1) / i + (b + i - 1) / i + (i - 1));   //带入公式 
		}
		cout << ans << "\n";
	}
	return 0;
}
```
```

