# Make It Good

## 题面翻译

- 给定你一个长为 $n$ 的序列 $A$ ,请问要在这个序列中擦除长度为多少的前缀，才能使这个序列是一个好的序列。

- 对好的序列的定义: 假定有一个序列 $B$，你可以每次从序列的首项或末项取出一个数字放在序列 $C$ 的末尾。假如存在一种方案使得 $C$ 不降，那么 $B$ 就是好的序列。

- 本题有 $T$ 组数据。$1\leq T\leq 2\times 10^4$
$1\leq \sum n\leq 2\times 10^5$

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. You have to find the length of the smallest (shortest) prefix of elements you need to erase from $ a $ to make it a good array. Recall that the prefix of the array $ a=[a_1, a_2, \dots, a_n] $ is a subarray consisting several first elements: the prefix of the array $ a $ of length $ k $ is the array $ [a_1, a_2, \dots, a_k] $ ( $ 0       \le k \le n $ ).

The array $ b $ of length $ m $ is called good, if you can obtain a non-decreasing array $ c $ ( $ c_1 \le c_2 \le \dots \le c_{m} $ ) from it, repeating the following operation $ m $ times (initially, $ c $ is empty):

- Select either the first or the last element of $ b $ , remove it from $ b $ , and append it to the end of the array $ c $ .

For example, if we do $ 4 $ operations: take $ b_1 $ , then $ b_{m} $ , then $ b_{m-1} $ and at last $ b_2 $ , then $ b $ becomes $ [b_3, b_4, \dots, b_{m-3}] $ and $ c =[b_1,       b_{m}, b_{m-1}, b_2] $ .

Consider the following example: $ b = [1, 2, 3, 4, 4, 2, 1] $ . This array is good because we can obtain non-decreasing array $ c $ from it by the following sequence of operations:

1. Take the first element of $ b $ , so $ b = [2, 3, 4, 4,         2, 1] $ , $ c = [1] $ ;
2. Take the last element of $ b $ , so $ b = [2, 3, 4, 4,         2] $ , $ c = [1, 1] $ ;
3. Take the last element of $ b $ , so $ b = [2, 3, 4, 4] $ , $ c = [1, 1, 2] $ ;
4. Take the first element of $ b $ , so $ b = [3, 4, 4] $ , $ c = [1, 1, 2, 2] $ ;
5. Take the first element of $ b $ , so $ b = [4, 4] $ , $ c         = [1, 1, 2, 2, 3] $ ;
6. Take the last element of $ b $ , so $ b = [4] $ , $ c =         [1, 1, 2, 2, 3, 4] $ ;
7. Take the only element of $ b $ , so $ b = [] $ , $ c = [1,         1, 2, 2, 3, 4, 4] $ — $ c $ is non-decreasing.

Note that the array consisting of one element is good.

Print the length of the shortest prefix of $ a $ to delete (erase), to make $ a $ to be a good array. Note that the required length can be $ 0 $ .

You have to answer $ t $ independent test cases.

## 输入格式

The first line of the input contains one integer $ t $ ( $ 1       \le t \le 2 \cdot 10^4 $ ) — the number of test cases. Then $ t $ test cases follow.

The first line of the test case contains one integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of $ a $ . The second line of the test case contains $ n $ integers $ a_1,       a_2, \dots, a_n $ ( $ 1 \le a_i \le 2 \cdot 10^5 $ ), where $ a_i $ is the $ i $ -th element of $ a $ .

It is guaranteed that the sum of $ n $ does not exceed $ 2       \cdot 10^5 $ ( $ \sum n \le 2 \cdot 10^5 $ ).

## 输出格式

For each test case, print the answer: the length of the shortest prefix of elements you need to erase from $ a $ to make it a good array.

## 样例 #1

### 样例输入 #1

```
5
4
1 2 3 4
7
4 3 3 8 4 5 2
3
1 1 1
7
1 3 1 4 5 3 2
5
5 4 3 2 3
```

### 样例输出 #1

```
0
4
0
2
3
```

## 提示

In the first test case of the example, the array $ a $ is already good, so we don't need to erase any prefix.

In the second test case of the example, the initial array $ a $ is not good. Let's erase first $ 4 $ elements of $ a $ , the result is $ [4, 5, 2] $ . The resulting array is good. You can prove that if you erase fewer number of first elements, the result will not be good.

## 题解
首先，本题我们需要一个重要的结论：如果我们的数列能够被双端队列的方式排序，也就是我们的循环左移或者是循环右移的方式进行排序，当且仅当我们的数列形态是一个山峰形的（即左侧上升，右侧下降）

于是，我们本体就转变为了，找到我们体中的一个最长后缀，满足这个后缀是山峰形状的。而于是，我们就可以通过我们的从后王座检查，得到哦我们的答案。
```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fr(i,a,b) for(int i=a;i<=b;i++)
#define fo(i,a,b) for(int i=a;i>=b;i--)
#define PII pair<int,int>
#define il inline
const int M=200005;
int t,n,a[M];
int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		fr(i,1,n) scanf("%d",&a[i]);
		int k=n;//初始为n
		while(a[k-1]>=a[k]&&k>1) k--;//上山，直到山顶
		while(a[k-1]<=a[k]&&k>1) k--;//下山
        //注意这里的k-1是确定满足的答案
		printf("%d\n",k-1);
	}
    return 0;
}

```

 