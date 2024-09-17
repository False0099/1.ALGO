# And It's Non-Zero

## 题面翻译

给定一个包含 $[l,r]$ 范围内所有整数的数组，求最少要删除多少元素，使得这个数组里面所有元素按位与之后的结果非零？

数据范围：
- $t$ 组数据，$1\leqslant t\leqslant 10^4$。
- $1\leqslant l\leqslant r\leqslant 2\times 10^5$。

Translated by Eason_AC  
2021.12.25

## 题目描述

You are given an array consisting of all integers from $ [l, r] $ inclusive. For example, if $ l = 2 $ and $ r = 5 $ , the array would be $ [2, 3, 4, 5] $ . What's the minimum number of elements you can delete to make the [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) of the array non-zero?

A bitwise AND is a binary operation that takes two equal-length binary representations and performs the AND operation on each pair of the corresponding bits.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. Then $ t $ cases follow.

The first line of each test case contains two integers $ l $ and $ r $ ( $ 1 \leq l \leq r \leq 2 \cdot 10^5 $ ) — the description of the array.

## 输出格式

For each test case, output a single integer — the answer to the problem.

## 样例 #1

### 样例输入 #1

```
5
1 2
2 8
4 5
1 5
100000 200000
```

### 样例输出 #1

```
1
3
0
2
31072
```

## 提示

In the first test case, the array is $ [1, 2] $ . Currently, the bitwise AND is $ 0 $ , as $ 1\ \& \ 2 = 0 $ . However, after deleting $ 1 $ (or $ 2 $ ), the array becomes $ [2] $ (or $ [1] $ ), and the bitwise AND becomes $ 2 $ (or $ 1 $ ). This can be proven to be the optimal, so the answer is $ 1 $ .

In the second test case, the array is $ [2, 3, 4, 5, 6, 7, 8] $ . Currently, the bitwise AND is $ 0 $ . However, after deleting $ 4 $ , $ 5 $ , and $ 8 $ , the array becomes $ [2, 3, 6, 7] $ , and the bitwise AND becomes $ 2 $ . This can be proven to be the optimal, so the answer is $ 3 $ . Note that there may be other ways to delete $ 3 $ elements.

## 题解
我们如果要让一个位置按位与之后我们仍然是 1，我们就要去除掉所有为 0 的部分。于是，我们就可以预处理出我们从 $0-2e5$ 中每一个二进制位出现了多少次，然后我们再去判断我们令某一位按位与结果为 1，我们需要的次数是多少。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int a[20][N];
void init(){
	for(int i=1;i<=2e5;i++){
		int z=i;
		int cnt=0;
		while(z){
			if(z&1==1){
				a[++cnt][i]++;
				z>>=1;
			}
		}
	}
	for(int i=1;i<=2e5;i++){
		for(int j=1;j<=20;j++){
			a[j][i]+=a[j][i-1];
		}
	}
}
int main(){
	init();
	int q;
	cin>>q;
	while(q--){
		int l,r;
		cin>>l>>r;
		int ans=0;
		for(int i=1;i<=20;i++){
			ans=max(a[i][r]-a[i][l-1],ans);
		}
		cout<<(r-l+1-ans)<<endl;
	}
}
```