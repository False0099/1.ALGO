# [[数论]] [[倍增]]
## 题目描述
给出一个数组，求这个数组中一段连续区间使得这个区间中所有数字除以一个数字m余数相同，使这个区间尽可能大，且m>=2，输出区间长度

## 输入格式
测试数据有 T 组

第一行输入T

每一组测试数据包含一个数字n(1<=n<=2e5)，表示数组的长度，接下来一行是数组中的元素ai(1<=ai<=1e18)，保证所有的ai不相同

n的总和小于2e5

## 输出格式

你的输出应该有T行，每行是这组测试数据的答案

## 样例 #1

### 样例输入 #1

```
4
3
1
100
5
1 3 6 7 10
6  
1 4 7 3 5 10
```

### 样例输出 #1

```
1
2
3
```


## 题解
我们这一题如果采用暴力的方法显然是不可取的，我们这一题需要我们采用一种 trick，名为 baka's trick (**无需删除的双指针**)，这种技巧适用于删除某个元素不方便，或是我们不希望删除时。我们可以**遍历我们的中间指针**，然后从**两侧来扩展**我们的左右指针。

对于这类问题，因为我们由等式 $a \ mod \ b=b \ mod \ m$ 我们可以推导出 $abs(a-b)|m$  我们可以通过**做差**，**强制转化为要求取模后余数位 0**，这一下，我们就可以把原来的问题转化为子区间的 gcd 大于 1。

而因为我们求的是子区间，所以我们可以**对相邻的两数作差**，然后在这些差值组成的序列找到最大的子区间，是该区间 gcd 大于 1, 找到的 gcd 也同时就是我们要除的数字。

## 代码
```cpp
#include <bits/stdc++.h>
#define INF 1e9
#define eps 1e-6
typedef long long ll;
using namespace std;

int t, n, ans;
ll a[200010], sub[200010], st[200010][20];

ll gcd(ll x, ll y){
    if(!y) return x;
    return gcd(y, x % y);
}
 
ll query(int i, int j){
    int k = log2(j - i + 1);
    return gcd(st[i][k], st[j - (1 << k) + 1][k]);
}

inline int max(int a, int b){
	return a > b ? a : b;
}

int main(){

	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)
			scanf("%lld", &a[i]);
		if(n == 1){
			puts("1");
			continue;
		}
		for(int i = 1; i < n; i++){
			sub[i] = a[i] - a[i + 1];
			if(sub[i] < 0) sub[i] = -sub[i];
		}
		n--;
		for(int i = 1; i <= n; i++)
			st[i][0] = sub[i];//
		for(int j = 1; (1 << j) <= n; j++) 
            for(int i = 1; i + (1 << j) - 1 <= n; i++)
                st[i][j] = gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        ans = 0;
		for(int i = 1, l, r; i <= n; i++){
			l = i, r = n;
			while(l < r){
				int mid = (l + r + 1) >> 1;
				if(query(i, mid) == 1) r = mid - 1;
				else l = mid;
			}
			if(sub[i] != 1) ans = max(ans, l - i + 1);	// sub[i] = 1 时不可取答案
		}
		printf("%d\n", ans + 1);
	}

	return 0;
}
```