**本题是《****sakiko 的排列构造****》的困难版本，请注意数据范围。**

  

> Sakiko：“什么都愿意做”就是这么沉重的话
> 
> Sakiko：做不到的事情就不要轻易说出口
> 
> Soyo：但是，我真的……
> 
> Sakiko：你这个人，满脑子都只想到自己呢
> 
> Soyo：诶……？
> 
>   
> 
> BV 1 oG 41127 aM  
> 不会做就去听听歌吧，虽然听了也不会做，但至少听了一首歌，血赚！  

  

sakiko 要构造一个长度为 $n$ 的排列 $p$ ，使得每一个 $p_i+i\ (1\leq i\leq n)$ 都是质数。

  

排列的定义为：长度为 $n$ 的数组，其中 $1-n$ 每个数字在数组中各出现一次。

## 输入：
第一行输入一个整数 $n(1 \leq n \leq 10^6)$ 表示数组长度。

## 输出：
输出 $n$ 个整数表示答案，如果有多种解法，则输出任意一种。  
  
若无解则输出 -1。

## 样例：
输入
--

 3

```
3
```

输出
--

 1 3 2

```
1 3 2 
```

## 题解
我们这一题比较类似于我们的找平方数那一题，都是先去找最小的比 n 大的质数，然后让我们后缀能填上的都填上，并且更新我们的 n，

之后，我们再去重复上述过程，直到我们完全构造出来。

```cpp
#include<bits/stdc++.h>
using namespace std;

int ans[1000005];
bool isPrime(int x) {
	for(int i = 2; i * i <= x; i++) if(x % i == 0) return 0;
	return 1;
}
void solve(int n) {
	if(n == 0) return;
	for(int i = 1; i <= n; i++) {
		if(isPrime(n + i)) {
			for(int j = i; j <= n; j++)
            	ans[j] = n + i - j;
			solve(i - 1);
			return;
		}
	}
}

int main() {
	int n;
	cin >> n;
	solve(n);
	for(int i = 1; i <= n; i++)
    	printf("%d ", ans[i]);
	return 0;
}

```