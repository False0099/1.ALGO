 # Min Max Sort

## 题面翻译

## 题目描述

对于一个排列，定义一次操作为：在排列中任选两个数字，将它们中的最大值插入至队尾，最小值插入至队首。

现在给定多个排列，问每个排列最少各需多少次操作才能变得严格递增。

## 输入格式

第一行一个整数 $t(1 \le t \le 10^4)$，表示将要给出的排列数。

接下来 $2t$ 行，每两行描述一个排列：首行一个整数 $n(1 \le n \le 2 \times 10^5)$，表示排列的长度；下一行 $n$ 个整数，描述排列 $p$。

保证 $\sum n \le 2 \times 10^5$。

## 输出格式

$t$ 行，每行一个整数，表示使第 $i$ 个排列变得严格递增所需要的操作数。

## 题目描述

You are given a permutation $ p $ of length $ n $ (a permutation of length $ n $ is an array of length $ n $ in which each integer from $ 1 $ to $ n $ occurs exactly once).

You can perform the following operation any number of times (possibly zero):

1. Choose two different elements $ x $ and $ y $ and erase them from the permutation;
2. Insert the minimum of $ x $ and $ y $ into the permutation in such a way that it becomes the first element;
3. Insert the maximum of $ x $ and $ y $ into the permutation in such a way that it becomes the last element.

For example, if $ p = [1, 5, 4, 2, 3] $ and we want to apply the operation to the elements $ 3 $ and $ 5 $ , then after the first step of the operation, the permutation becomes $ p = [1, 4, 2] $ ; and after we insert the elements, it becomes $ p = [3, 1, 4, 2, 5] $ .

Your task is to calculate the minimum number of operations described above to sort the permutation $ p $ in ascending order (i. e. transform $ p $ so that $ p_1 < p_2 < \dots < p_n $ ).

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of the test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of elements in the permutation.

The second line of the test case contains $ n $ distinct integers from $ 1 $ to $ n $ — the given permutation $ p $ .

The sum of $ n $ over all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the minimum number of operations described above to sort the array $ p $ in ascending order.

## 样例 #1

### 样例输入 #1

```
4
5
1 5 4 2 3
3
1 2 3
4
2 1 4 3
6
5 2 4 1 6 3
```

### 样例输出 #1

```
2
0
1
3
```

## 提示

In the first example, you can proceed as follows:

1. In the permutation $ p = [1, 5, 4, 2, 3] $ , let's choose the elements $ 4 $ and $ 2 $ , then, after applying the operation, the permutation becomes $ p = [2, 1, 5, 3, 4] $ ;
2. In the permutation $ p = [2, 1, 5, 3, 4] $ , let's choose the elements $ 1 $ and $ 5 $ , then, after applying operation, the permutation becomes $ p = [1, 2, 3, 4, 5] $ .

## 题解
我们首先模拟后不难发现，分别位于首尾的 1 和 n 一定是在最后一次操作中归为的，以此类推，位于 2 和 n-1 一定是在倒数第二次操作中归位的.... 设我们元素 i 的初始位置为 $pos_{i}$,那么 k 次操作能将 p 排序，当且仅当 $pos_{k+1}<pos_{k+2}<\dots<pos_{n-k}$,首先，我们 $k=\frac{n}{2}$ 时，一定可以，如果 k 可行，并且 $pos_{k}<pos_{k+1}$，$pos_{n-k}<pos_{n-k+1}$ 那么 $k-1$ 也可行，因此我们从 $k_{0}$ 开始枚举，找到最小的 k 即可


![[Pasted image 20231011211126.png]]
```cpp
#include<stdio.h>

const int N=2e5+5;
int T,n,x,k,p[N];

int main() {
    scanf("%d",&T);
    while (T--) {
        scanf("%d",&n);
        for (int i=1; i<=n; ++i)
            scanf("%d",&x),p[x]=i;
        k=(n>>1);
        while (k&&p[k]<p[k+1]&&p[n-k+1]>p[n-k]) --k;
        printf("%d\n",k);
    }
    return 0;
}
```