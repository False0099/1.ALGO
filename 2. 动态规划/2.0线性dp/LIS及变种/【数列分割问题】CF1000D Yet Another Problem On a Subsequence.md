# Yet Another Problem On a Subsequence

## 题面翻译

**题目大意：**

如果一个数组 $[a_1,a_2,a_3,...,a_n]a_1=n-1$ 并且 $a1>0$，这个数组就被叫为好数组，如果一个序列能正好分为多个好数组，ta 就被叫为好序列，现在给定一个序列，求这个序列有多少好子序列，答案对 $998244353$ 取模

**输入格式：**

第一行一个整数，$n$，$n<=10^3$

以下一行有 $n$ 个整数

**输出格式：**

一个整数，即好子序列数

感谢@守望提供翻译

## 题目描述

The sequence of integers $ a_1, a_2, \dots, a_k $ is called a good array if $ a_1 = k - 1 $ and $ a_1 > 0 $ . For example, the sequences $ [3, -1, 44, 0], [1, -99] $ are good arrays, and the sequences $ [3, 7, 8], [2, 5, 4, 1], [0] $ — are not.

A sequence of integers is called good if it can be divided into a positive number of good arrays. Each good array should be a subsegment of sequence and each element of the sequence should belong to exactly one array. For example, the sequences $ [2, -3, 0, 1, 4] $ , $ [1, 2, 3, -3, -9, 4] $ are good, and the sequences $ [2, -3, 0, 1] $ , $ [1, 2, 3, -3 -9, 4, 1] $ — are not.

For a given sequence of numbers, count the number of its subsequences that are good sequences, and print the number of such subsequences modulo 998244353.

## 输入格式

The first line contains the number $n~(1 \le n \le 10^3)$ — the length of the initial sequence. The following line contains $ n $ integers $ a_1, a_2, \dots, a_n~(-10^9 \le a_i \le 10^9) $ — the sequence itself.

## 输出格式

In the single line output one integer — the number of subsequences of the original sequence that are good sequences, taken modulo 998244353.

## 样例 #1

### 样例输入 #1

```
3
2 1 1
```

### 样例输出 #1

```
2
```

## 样例 #2

### 样例输入 #2

```
4
1 1 1 1
```

### 样例输出 #2

```
7
```

## 提示

In the first test case, two good subsequences — $ [a_1, a_2, a_3] $ and $ [a_2, a_3] $ .

In the second test case, seven good subsequences — $ [a_1, a_2, a_3, a_4], [a_1, a_2], [a_1, a_3], [a_1, a_4], [a_2, a_3], [a_2, a_4] $ and $ [a_3, a_4] $ .

## 题解
**我们这里是子序列，所以不一定是连续的

这一题我们的思路是根据我们的转移过程来设置我们的状态，因为我们这一题的转移相对来说是比较简单的，就是我们从当前位置向后取 $a[i]$ 个数，然后，我们就可以考虑我们

我们这一题需要我们采用我们的 dp 来解决我们的问题，我们可以设 $f[i]$ 表示我们以 $i$ 结尾的子序列数量有多少个，那么我们就可以考虑转移，
$$
dp[i]=\sum_{j=i+a[i]+1}^{n+1}dp[j]\times C_{j-i-1}^{a[i]}
$$

在这里，我们需要这么去理解：我们假设我们是以 $i$ 开头，那么我们下一个可以选的区间就是我们的 $i+a[i]+1$ 到我们的 $n+1$ 之间，那么我们每一个转移，转移后时我们要处理两个问题，第一个是在我们的 $j$ 到 $i$ 之间选择恰好 $a[i]$ 个数字，这一步，我们的数量是我们的 $C_{j-i-1}^{a[i]}$,然后我们的下一步就是求我们的以 $j$ 新开头的总共的方案书是多少个，这里我们的答案是我们的 $dp[j]$，最后我们的答案就是把每一个 $dp[i]$ 给加起来。

```cpp
void dp(){
	for(int i=1;i<=n;i++){
		if(a[i]>0){
			for(int j=i+a[i];j<=n;j++){
				f[j]=(f[j]+1ll*(f[i-1]+1)*C[j-i][a[i]])%mod;
			}
		}
	}
	printf("%d",f[n]);
}
```