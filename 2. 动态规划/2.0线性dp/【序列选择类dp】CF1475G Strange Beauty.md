# Strange Beauty

## 题面翻译

题目大意：有 $n$ 个数，从中挑选一个最大的子集，使得集合中任意两个不同的数 $x,y$ ，有 $x|y$ 或 $y|x$

## 题目描述

Polycarp found on the street an array $ a $ of $ n $ elements.

Polycarp invented his criterion for the beauty of an array. He calls an array $ a $ beautiful if at least one of the following conditions must be met for each different pair of indices $ i \ne j $ :

- $ a_i $ is divisible by $ a_j $ ;
- Or $ a_j $ is divisible by $ a_i $ .

For example, if:

- $ n=5 $ and $ a=[7, 9, 3, 14, 63] $ , then the $ a $ array is not beautiful (for $ i=4 $ and $ j=2 $ , none of the conditions above is met);
- $ n=3 $ and $ a=[2, 14, 42] $ , then the $ a $ array is beautiful;
- $ n=4 $ and $ a=[45, 9, 3, 18] $ , then the $ a $ array is not beautiful (for $ i=1 $ and $ j=4 $ none of the conditions above is met);

Ugly arrays upset Polycarp, so he wants to remove some elements from the array $ a $ so that it becomes beautiful. Help Polycarp determine the smallest number of elements to remove to make the array $ a $ beautiful.
## 输入格式

The first line contains one integer $ t $ ( $ 1 \leq t \leq 10 $ ) — the number of test cases. Then $ t $ test cases follow.

The first line of each test case contains one integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ numbers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 2 \cdot 10^5 $ ) — elements of the array $ a $ .

## 输出格式

For each test case output one integer — the minimum number of elements that must be removed to make the array $ a $ beautiful.

## 样例 #1

### 样例输入 #1

```
4
5
7 9 3 14 63
3
2 14 42
4
45 9 3 18
3
2 2 8
```

### 样例输出 #1

```
2
0
1
0
```

## 提示

In the first test case, removing $ 7 $ and $ 14 $ will make array $ a $ beautiful.

In the second test case, the array $ a $ is already beautiful.

In the third test case, removing one of the elements $ 45 $ or $ 18 $ will make the array $ a $ beautiful.

In the fourth test case, the array $ a $ is beautiful.

## 题解
我们这一题发现，如果我们一个数可以是我们的美丽序列，那么我们就必须要满足，将这个集合从小到大排序后，我们序列的后一个数一定能整除我们的前一个数，我们这个数是我们上一个数的倍数，
于是我们的做法一：我们先把我们的数组进行排序，然后我们再按照类似于单调上升子序列的方法去计算我们是否能够转移。但是这样做是 $o(n^2)$ 的, 会超时。

然后我们就考虑优化：我们从我们的值域来考虑，因为我们的每一个数只会从它的倍数转移过来，所以我们可以 $o(\sqrt{ n })$ 的枚举我们的因数，然后再从我们的因数转移过来。

```cpp
void slove() {
    mst(cot); mst(dp);
    cin >> n; for (int i = 1; i <= n; i++)cin >> a[i], cot[a[i]]++;
    for (int i = 2e5; i >= 1; i--) {
        int mx = 0;
        for (int j = i; j <= 2e5; j += i) {
            mx = max(mx, dp[j]);
        }
        dp[i] = mx + cot[i];
    }
    cout << n - *max_element(dp + 1, dp + 1 + n) << endl;
}
```