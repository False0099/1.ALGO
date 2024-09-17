# XOR Construction

## 题目描述

You are given $ n-1 $ integers $ a_1, a_2, \dots, a_{n-1} $ .

Your task is to construct an array $ b_1, b_2, \dots, b_n $ such that:

- Every integer from $ 0 $ to $ n-1 $ appears in $ b $ exactly once;
- For every $ i $ from $ 1 $ to $ n-1 $ , $ b_i \oplus b_{i+1} = a_i $ (where $ \oplus $ denotes the bitwise XOR operator).

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ).

The second line contains $ n-1 $ integers $ a_1, a_2, \dots, a_{n-1} $ ( $ 0 \le a_i \le 2 n $ ).

Additional constraint on the input: it's always possible to construct at least one valid array $ b $ from the given sequence $ a $ .

## 输出格式

Print $ n $ integers $ b_1, b_2, \dots, b_n $ . If there are multiple such arrays, you may print any of them.

## 样例 #1

### 样例输入 #1

```
4
2 1 2
```

### 样例输出 #1

```
0 2 3 1
```

## 样例 #2

### 样例输入 #2

```
6
1 6 1 4 1
```

### 样例输出 #2

```
2 3 5 4 0 1
```

## 题解
首先我们可以得出 $\oplus_{i=1}^k b_{i}=a_{1}\oplus a_{i+1}$，现在我们的目标是求出 ai​。

题目中保证有解，且是一个 0∼n−1 的排列，我们对 a1​ 按位赋值，对于每一位，扫一遍求出与 a1​ 相同的数量，因为每一位 0 的个数一定大于等于 1 的个数，判断一下即可。

```cpp
int main() {
	
	cin>>n;
	for (int i = 2; i <= n; i ++) a[i] = read() ^ a[i - 1];
    
	for (int i = 17; i >= 0; i --) { 
    	int s = 0;
		for (int j = 2; j <= n; j ++) s += (a[j] >> i) & 1;
		if (s > n / 2) t ^= 1 << i;
	}
	
	printf("%d ", t);
	for (int i = 2; i <= n; i ++) printf("%d ", t ^ a[i]);
	
	return 0;
}
```