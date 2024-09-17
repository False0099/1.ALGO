# Add One

## 题面翻译

称“将一个数上每一位的值 $+~1$”为一次操作，例如对于 $93$ 进行一次操作后的结果为 $104$。输入 $n ,m$，你需要对 $n$ 进行 $m$ 次 $+~1$ 运算。 

在进行 $m$ 次 $+~1$ 运算后，你需要求出 $n$ 的长度（位数）。由于答案可能非常大，请打印出对 $10^9+7$ 取模后的答案。

## 题目描述

You are given an integer $ n $ . You have to apply $ m $ operations to it.

In a single operation, you must replace every digit $ d $ of the number with the decimal representation of integer $ d + 1 $ . For example, $ 1912 $ becomes $ 21023 $ after applying the operation once.

You have to find the length of $ n $ after applying $ m $ operations. Since the answer can be very large, print it modulo $ 10^9+7 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 2 \cdot 10^5 $ ) — the number of test cases.

The only line of each test case contains two integers $ n $ ( $ 1 \le n \le 10^9 $ ) and $ m $ ( $ 1 \le m \le 2 \cdot 10^5 $ ) — the initial number and the number of operations.

## 输出格式

For each test case output the length of the resulting number modulo $ 10^9+7 $ .

## 样例 #1

### 样例输入 #1

```
5
1912 1
5 6
999 1
88 2
12 100
```

### 样例输出 #1

```
5
2
6
4
2115
```

## 提示

For the first test, $ 1912 $ becomes $ 21023 $ after $ 1 $ operation which is of length $ 5 $ .

For the second test, $ 5 $ becomes $ 21 $ after $ 6 $ operations which is of length $ 2 $ .

For the third test, $ 999 $ becomes $ 101010 $ after $ 1 $ operation which is of length $ 6 $ .

For the fourth test, $ 88 $ becomes $ 1010 $ after $ 2 $ operations which is of length $ 4 $ .


## 题解
因为我们每一个数位都是独立的，所以我们可以考虑预处理出 $[0-9]$ 的数字在经过 i 次操作后的长度，但是我们 $[1-9]$ 的数字都可以由 0 操作过来，所以我们只需要预处理 0 即可，对于一个数字 $0$,我们只有 9+1=10 这一步是不太好计算的，所以我们也需要记录出来 0 经过 i 次操作后，每个数字都出现了多少次。但后我们的 dp 就是
```cpp
struct node{
	int len;
	int cot[10];
}dp[MAXN];
for(int i=1;i<MAXN;i++){
	dp[i].len=(d[i-1].len+dp[i-1].cot[9])%=mod;
	for(int j=1;j<=9;j++){
		dp[i].cot[j]=(dp[i-1].cot[j-1])%=mod;
		dp[i].cot[1]+=dp[i-1].cot[9]%=mod;
		dp[i].cot[0]+=dp[i-1].cot[9]%=mod;
	}
}
```cpp
void slove() {
    cin >> n >> m;
    int ans = 0;
    while (n) {
        (ans += dp[n % 10 + m].len)%=mod;
        n /= 10;
    }
    cout << ans << endl;
}
```
```