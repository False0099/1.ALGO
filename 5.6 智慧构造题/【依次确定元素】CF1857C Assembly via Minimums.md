# Assembly via Minimums

## 题面翻译

有一个长度为 $n$ 序列 $A$ 和一个序列 $B$。$B$ 为 $A$ 中任意两数的最小值。那么，$B$ 的长度为 $\dfrac{n(n-1)}2$。

现将 $B$ 随机打乱，请求出相对应的 $A$。只需输出一种方案。

## 题目描述

Sasha has an array $ a $ of $ n $ integers. He got bored and for all $ i $ , $ j $ ( $ i < j $ ), he wrote down the minimum value of $ a_i $ and $ a_j $ . He obtained a new array $ b $ of size $ \frac{n\cdot (n-1)}{2} $ .

For example, if $ a= $ \[ $ 2,3,5,1 $ \], he would write \[ $ \min (2, 3), \min (2, 5), \min (2, 1), \min (3, 5), \min (3, 1), min (5, 1) $ \] $ = $ \[ $ 2, 2, 1, 3, 1, 1 $ \].

Then, he randomly shuffled all the elements of the array $ b $ .

Unfortunately, he forgot the array $ a $ , and your task is to restore any possible array $ a $ from which the array $ b $ could have been obtained.

The elements of array $ a $ should be in the range $ [-10^9,10^9] $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 200 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 2\le n\le 10^3 $ ) — the length of array $ a $ .

The second line of each test case contains $ \frac{n\cdot (n-1)}{2} $ integers $ b_1, b_2,\dots, b_{\frac{n\cdot (n-1)}{2}} $ ( $ −10^9\le b_i\le 10^9 $ ) — the elements of array $ b $ .

It is guaranteed that the sum of $ n $ over all tests does not exceed $ 10^3 $ and for each array $ b $ in the test, there exists an original array.

## 输出格式

For each test case, output any possible array $ a $ of length $ n $ .

## 样例 #1

### 样例输入 #1

```
5
3
1 3 1
2
10
4
7 5 3 5 3 3
5
2 2 2 2 2 2 2 2 2 2
5
3 0 0 -2 0 -2 0 0 -2 -2
```

### 样例输出 #1

```
1 3 3
10 10
7 5 3 12
2 2 2 2 2
0 -2 0 3 5
```

## 提示

In the first sample, Sasha chose the array $ [1,3,3] $ , then the array $ b $ will look like $ [\min (a_1, a_2)=1, \min (a_1, a_3)=1, \min (a_2, a_3)=3] $ , after shuffling its elements, the array can look like $ [1,3,1] $ .

In the second sample, there is only one pair, so the array $ [10,10] $ is suitable. Another suitable array could be $ [15,10] $ .

## 题解
若已知原数组 $A$, 且其单调不降，考虑 $B$ 序列的构造过程。由于序列单调不降，每个元素与其后方元素进行 min 操作所得均为该元素本身。例如序列 $A=$[1,2,3,4], 得到的 $B$ 序列为 [1,1,1,2,2,3]。这意味着，在 $B$ 序列中，有 $n-i$ 个在 $A$ 序列中第 $i$ 小的元素。

有了这个结论，我们只需要将给定的 $B$ 序列排序，依次从开头取走 $(n-1),(n-2),...$ 个数即可。在
这之后，原序列 $A$ 中还剩下一个最大的数没有得出来，只需要随意再添加一个比其他数大的数即可。
```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<string.h>

using namespace std;

const int N=1e6+10;

int T;
int n;
int b[N];

void Solve(){
	
	scanf("%d",&n);
	int m=n*(n-1)/2;
	for(int i=1;i<=m;i++)
		scanf("%d",&b[i]);
	sort(b+1,b+1+m);
	int i=1,j=n-1;
	while(i<=m){
		printf("%d ",b[i]);
		i+=j;
		j--;
	}
	printf("%d\n",b[m]);
	return ;
	
}

int main(){
	
	scanf("%d",&T);
	while(T--){
		Solve();
	}
	return 0;
	
}
```