# Min-Max Array Transformation

## 题面翻译

## 题目描述
给你一个升序数组 $a_1,a_2,...,a_n$。你要通过以下步骤去得到数组 $b_1,b_2,...,b_n$ ：

1. 生成数组 $d$，由 $n$ 个非负整数组成。
2. 通过 $b_i=a_i+d_i$ 计算每一个 $b_i$。
3. 给 $b$ 进行升序排序。

你现在又知道了结果 $b$，你要算出每一个 $d_i$ 可能的最小值和最大值（每个 $d_i$ 的最值可以是由不同的数组 $d$ 满足的）。

## 输入格式

第一行一个整数 $t (1\le t \le 10^4)$，样例数。

每个样例的第一行一个整数 $n (1 \le n \le 2 * 10^5)$ 。

下一行 $n$ 个整数，$a_1,a_2,...,a_n (1 \le a_1 \le a_2 \le ... \le a_n \le 10^9)$。

下一行 $n$ 个整数，$b_1,b_2,...,b_n (1 \le b_1 \le b_2 \le ... \le b_n \le 10^9)$。

输入数据满足至少有一个满足题意的 $d$。
所有的 $n$ 和不超 $2 * 10^5$。

## 输出格式

每个样例两行：

第一行 $d_1^{min}, d_2^{min},..., d_n^{min}$。
第二行 $d_1^{max}, d_2^{max},..., d_3^{max}$。

## 说明/提示

第一个样例中，$d=[5,10,6]$ 满足 $d_1^{min}=5,b=[2+5,3+10,5+6]=[7,13,11]=[7,11,13]$。

第一个样例中，$d=[9,4,8]$ 满足 $d_2^{min}=4,b=[2+9,3+4,5+8]=[11,7,13]=[7,11,13]$。

## 题目描述

You are given an array $ a_1, a_2, \dots, a_n $ , which is sorted in non-descending order. You decided to perform the following steps to create array $ b_1, b_2, \dots, b_n $ :

1. Create an array $ d $ consisting of $ n $ arbitrary non-negative integers.
2. Set $ b_i = a_i + d_i $ for each $ b_i $ .
3. Sort the array $ b $ in non-descending order.

You are given the resulting array $ b $ . For each index $ i $ , calculate what is the minimum and maximum possible value of $ d_i $ you can choose in order to get the given array $ b $ .

Note that the minimum (maximum) $ d_i $ -s are independent of each other, i. e. they can be obtained from different possible arrays $ d $ .

## 输入格式

The first line contains the single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of arrays $ a $ , $ b $ and $ d $ .

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ; $ a_i \le a_{i+1} $ ) — the array $ a $ in non-descending order.

The third line contains $ n $ integers $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_i \le 10^9 $ ; $ b_i \le b_{i+1} $ ) — the array $ b $ in non-descending order.

Additional constraints on the input:

- There is at least one way to obtain the array $ b $ from the $ a $ by choosing an array $ d $ consisting of non-negative integers;
- The sum of $ n $ doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print two lines. In the first line, print $ n $ integers $ d_1^{min}, d_2^{min}, \dots, d_n^{min} $ , where $ d_i^{min} $ is the minimum possible value you can add to $ a_i $ .

Secondly, print $ n $ integers $ d_1^{max}, d_2^{max}, \dots, d_n^{max} $ , where $ d_i^{max} $ is the maximum possible value you can add to $ a_i $ .

All $ d_i^{min} $ and $ d_i^{max} $ values are independent of each other. In other words, for each $ i $ , $ d_i^{min} $ is just the minimum value among all possible values of $ d_i $ .

## 样例 #1

### 样例输入 #1

```
4
3
2 3 5
7 11 13
1
1000
5000
4
1 2 3 4
1 2 3 4
4
10 20 30 40
22 33 33 55
```

### 样例输出 #1

```
5 4 2
11 10 8
4000
4000
0 0 0 0
0 0 0 0
12 2 3 15
23 13 3 15
```

## 提示

In the first test case, in order to get $ d_1^{min} = 5 $ , we can choose, for example, $ d = [5, 10, 6] $ . Then $ b $ $ = $ $ [2+5,3+10,5+6] $ $ = $ $ [7,13,11] $ $ = $ $ [7,11,13] $ .

For $ d_2^{min} = 4 $ , we can choose $ d $ $ = $ $ [9, 4, 8] $ . Then $ b $ $ = $ $ [2+9,3+4,5+8] $ $ = $ $ [11,7,13] $ $ = $ $ [7,11,13] $ .

## 题解
对于我们的最小，我们可以考虑才一个结论：我们的答案就是我们的第一个比我们当前位置还要大的数的对应的差。这里，我们就可以通过我们的 `lower_bound` 来直接找到我们的答案。

对于我们的最大，我们从大到小去考虑我们的元素，对于我们的每一个元素，我们最好当然是能够去找到最大值去和他对应。
但是，并不是所有的元素都能够对应上我们的最大值，例如：
```
2 3 5 7
3 6 6 9
```
我们的 5 就不能去匹配我们的最大值，因为 5 一旦去匹配了我们的最大值，我们的 7 就没有其他的可以去匹配了。
对于这种情况，我们要找的就是我们的最大的，比我们的第二位数字要小的数字，这个匹配的结果就是我们的答案了。

```cpp
const int N = 3e5 + 5;

int a[N],b[N];
multiset<int> s;
int d[N];

int main(){
    int T = read();
    while(T--){
        s.clear();
        int n = read();
        for(int i = 1;i <= n;++i) a[i] = read();
        for(int i = 1;i <= n;++i) s.insert(b[i] = read());
        for(int i = 1;i <= n;++i)
            printf("%d ",*lower_bound(b + 1,b + n + 1,a[i]) - a[i]);
        printf("\n");
        for(int i = n;i >= 1;--i){
            d[i] = *prev(s.end());
            s.erase(s.lower_bound(a[i]));
        }
        for(int i = 1;i <= n;++i) printf("%d ",d[i] - a[i]);
        printf("\n");
    }
    return 0;
}
```