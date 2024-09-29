# Reorder the Array

## 题面翻译

给出一个有 $n$ 个元素的序列，求把它们重新排列后 **排列后的元素比原来位置元素大** 的元素个数的最大值

## 题目描述

You are given an array of integers. Vasya can permute (change order) its integers. He wants to do it so that as many as possible integers will become on a place where a smaller integer used to stand. Help Vasya find the maximal number of such integers.

For instance, if we are given an array $ [10, 20, 30, 40] $ , we can permute it so that it becomes $ [20, 40, 10, 30] $ . Then on the first and the second positions the integers became larger ( $ 20>10 $ , $ 40>20 $ ) and did not on the third and the fourth, so for this permutation, the number that Vasya wants to maximize equals $ 2 $ . Read the note for the first example, there is one more demonstrative test case.

Help Vasya to permute integers in such way that the number of positions in a new array, where integers are greater than in the original one, is maximal.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \leq n \leq 10^5 $ ) — the length of the array.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — the elements of the array.

## 输出格式

Print a single integer — the maximal number of the array's elements which after a permutation will stand on the position where a smaller element stood in the initial array.

## 样例 #1

### 样例输入 #1

```
7
10 1 1 1 5 5 3
```

### 样例输出 #1

```
4
```

## 样例 #2

### 样例输入 #2

```
5
1 1 1 1 1
```

### 样例输出 #2

```
0
```

## 提示

In the first sample, one of the best permutations is $ [1, 5, 5, 3, 10, 1, 1] $ . On the positions from second to fifth the elements became larger, so the answer for this permutation is 4.

In the second sample, there is no way to increase any element with a permutation, so the answer is 0.

## 题解
我们这一题我们只需要扫一遍数组，然后对于每一个数组，找到**最近的比它大的哪个数**，这里，我们采用的是一种类似于贪心的想法，每一次找到一个最小的符合要求的数字。然后把他填上去，这样显然是最优的，关于怎么找到，我们可以用 upper_bound 函数来减少代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int yuan[100005],sum;
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>yuan[i];
	}
	sort(yuan,yuan+n);//从小到大排序，贪心的基本操作 
	int j=0;
	for(int i=0;i<n-1&&j<n;i++)
	{
		j++;
		if(yuan[j]>yuan[i])
		{
			sum++;
		}
		else i--;
	}//循环内内容已经解释。 
	cout<<sum;
	return 0;
}
```