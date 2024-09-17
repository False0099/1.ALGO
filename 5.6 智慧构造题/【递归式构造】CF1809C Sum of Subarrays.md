# Sum on Subarrays

## 题面翻译

给定两个正整数 $n$ 和 $k$，构造一个长度为 $n$ 的序列 $a$ 满足：

- $-1000\le a_i\le 1000$
- 序列有恰好 $k$ 个子串的和为正数
- 剩余 $\frac{n(n+1)}2-k$ 个子串的和都是负数

你只需要输出任意一组解。

## 题目描述

For an array $ a = [a_1, a_2, \dots, a_n] $ , let's denote its subarray $ a[l, r] $ as the array $ [a_l, a_{l+1}, \dots, a_r] $ .

For example, the array $ a = [1, -3, 1] $ has $ 6 $ non-empty subarrays:

- $ a[1,1] = [1] $ ;
- $ a[1,2] = [1,-3] $ ;
- $ a[1,3] = [1,-3,1] $ ;
- $ a[2,2] = [-3] $ ;
- $ a[2,3] = [-3,1] $ ;
- $ a[3,3] = [1] $ .

You are given two integers $ n $ and $ k $ . Construct an array $ a $ consisting of $ n $ integers such that:

- All elements of $ a $ are from $ -1000 $ to $ 1000 $ ;
- $ a $ has exactly $ k $ subarrays with positive sums;
- The rest $ \dfrac{(n+1) \cdot n}{2}-k $ subarrays of $ a $ have negative sums.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 5000 $ ) — the number of test cases.

Each test case consists of one line containing two integers $ n $ and $ k $ ( $ 2 \le n \le 30 $ ; $ 0 \le k \le \dfrac{(n+1) \cdot n}{2} $ ).

## 输出格式

For each test case, print $ n $ integers — the elements of the array meeting the constraints. It can be shown that the answer always exists. If there are multiple answers, print any of them.

## 样例 #1

### 样例输入 #1

```
4
3 2
2 0
2 2
4 6
```

### 样例输出 #1

```
1 -3 1
-13 -42
-13 42
-3 -4 10 -2
```


## 题解
我们这一题有两种做法，一种是直接在我们的原数组上进行构造，假如我们的 $k=\frac{i(i-1)}{2}$，那么我们就可以通过让我们前面的除了 i 以外的元素都是 1，剩下的填-1000 即可。

如果我们的 $k$ 大于某一个 $\frac{i(i-1)}{2}$,那么对于我们的前 $i$ 项，我们全部填上一个正数，然后我们考虑怎么通过填写我们的负数使得我们能够最后满足我们的条件，我们需要让我们的然后在我们的第 $i$ 项填我们的 $-1-30\left( \left( \frac{i(i+1)}{2} \right)-k-1 \right)$ 即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 35
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,k;
int a[N];
void solve(){
	n=read(),k=read();
	if(!k) for(int i=1;i<=n;++i) printf("%d ",-1000);
	else{
		int cnt=0;
		for(int i=1;i<=n;++i){
			int d=i*(i+1)/2;
			if(d>=k){
				cnt=i;
				break;
			}
		}
		for(int i=1;i<cnt;++i) a[i]=30;
		if(cnt*(cnt+1)/2==k) a[cnt]=30;
		else a[cnt]=-1-30*(cnt*(cnt+1)/2-k-1);
		for(int i=cnt+1;i<=n;++i) a[i]=-1000;
		for(int i=1;i<=n;++i) printf("%d ",a[i]);
	}
	puts("");
}
int main(){
	int T=read();
	while(T--) solve();
	return 0;
}
```

或者，我们也可以用我们的前缀和思路，把我们的原问题转化为我们的前缀和中有 k 对 (i, j)，满足 $i<j,s_{i}<s_{j}$,也就是构造一个**正数对**为 k 的排列。

于是，我们可以通过冒泡排序交换 k 次，我们的正序对，我们的 $n+1,\mathbf{n}..,i$ 来进行。

```cpp
int a[N];
int main()
{
	int t=rd();
	while(t--)
	{
		int n=rd(),k=rd();
		for(int i=0;i<=n;i++)
			a[i]=n-i+1;
		for(int i=0;i<=n;i++)
			for(int j=i+1;j<=n;j++)
			{
				if(k>0)
				{
					k--;
					swap(a[i],a[j]);
				}
			}
		for(int i=1;i<=n;i++)
			cout<<a[i]-a[i-1]<<' ';
		cout<<endl;
	}
	return 0;
}
```