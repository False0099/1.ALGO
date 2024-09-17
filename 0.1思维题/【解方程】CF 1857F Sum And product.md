# Sum and Product

## 题面翻译

给定一个长度为 $n$ 的序列 $a$，你将得到 $q$ 次询问，求同时满足以下条件的二元组 $(i,j)$ 数量：
- $1\leq i < j \leq n$。
- $a_i+a_j=x$。
- $a_i\times a_j=y$。

$t$ 组数据，$1\leq t \leq 10^4$，$2\leq  \sum n ,\sum q\leq 2\times10^5$，$1\leq |a_i| \leq 10^9$，$1\leq |x| \leq 2\times 10^9$，$1\leq |y| \leq 10^{18}$。

## 题目描述

You have an array $ a $ of length $ n $ .

Your task is to answer $ q $ queries: given $ x, y $ , find the number of pairs $ i $ and $ j $ ( $ 1 \le i < j \le n $ ) that both $ a_i + a_j = x $ and $ a_i \cdot a_j = y $ .

That is, for the array $ [1,3,2] $ and asking for $ x=3, y=2 $ the answer is $ 1 $ :

- $ i=1 $ and $ j=2 $ fail because $ 1 + 3 = 4 $ and not $ 3, $ also $ 1 \cdot 3=3 $ and not $ 2 $ ;
- $ i=1 $ and $ j=3 $ satisfies both conditions;
- $ i=2 $ and $ j=3 $ fail because $ 3 + 2 = 5 $ and not $ 3, $ also $ 3 \cdot 2=6 $ and not $ 2 $ ;

## 输入格式

The first line contains one integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases.

The second line of each test case contains one integer $ n $ ( $ 1 \le n \le 2\cdot 10^5 $ ) — the length of the array $ a $ .

The third line of each test case contains $ n $ integers $ a_1, a_2,\dots, a_n $ ( $ 1 \le |a_i| \le 10^9 $ ) — array $ a $ .

The fourth line of each test case contains the integer $ q $ ( $ 1 \le q \le 2\cdot 10^5 $ ) — the number of requests.

The next $ q $ lines contain two numbers each $ x $ and $ y $ ( $ 1 \le |x|\le 2\cdot 10^9,1\le |y|\le 10^{18} $ ) — request.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ . This is also guaranteed for the sum of $ q $ values.

## 输出格式

For each test case print a line with $ q $ numbers — the answers to the queries.

## 样例 #1

### 样例输入 #1

```
3
3
1 3 2
4
3 2
5 6
3 1
5 5
4
1 1 1 1
1
2 1
6
1 4 -2 3 3 3
3
2 -8
-1 -2
7 12
```

### 样例输出 #1

```
1 1 0 0 
6 
1 1 3
```

## 提示

For the first test case, let's analyze each pair of numbers separately:

- Pair $ (a_1, a_2) $ : $ a_1 + a_2 = 4 $ , $ a_1 \cdot a_2 = 3 $
- Pair $ (a_1, a_3) $ : $ a_1 + a_3 = 3 $ , $ a_1 \cdot a_3 = 2 $
- Pair $ (a_2, a_3) $ : $ a_2 + a_3 = 5 $ , $ a_2 \cdot a_3 = 6 $

 From this, we can see that for the first query, the pair $ (a_1, a_3) $ is suitable, for the second query, it is $ (a_2, a_3) $ , and there are no suitable pairs for the third and fourth queries. In the second test case, all combinations of pairs are suitable.


## 题解
我们首先发现，我们的 $a_{i}+a_{j}$ 和我们的 $a_{i}\times a_{j}$ 是不会相互影响的，于是，我们就可以开一个 map 记录我们的每一个对是哪些，即可。


当然骂我们也存在一些巧妙地想法，比如说利用我们的二次方程求解：

我们看到 $a_{i}+a_{j},a_{i}\times a_{j}$,**不难想到**，我们可以把我们的原式子转换为在所有的序列中，求 $a_{i}$ 的数量，要求满足 $f(a_{i})=0$,其中 $f$ 是一个二次函数，现在我们就可以 $o(n)$ 的枚举解决了。

再或者，我们可以求出我们的解 $x=\frac{-x\pm\sqrt{ x^2-4y }}{-2}$
然后我们只需要找出 $x_{1}$ 在我们的序列中出现了多少次，$x_{2}$ 在我们序列中出现了多少次，然后我们的答案就是 $\frac{k(k-1)}{2}$.

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+10;
int n,a[maxn],q,ans;
void solve(){
	map<int,int> mp;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		mp[a[i]]++;
	}
	cin>>q;
	for(int i=1;i<=q;i++){
		int x,y;
		cin>>x>>y;
		int num=x*x-4*y;
		if(num<0){
			cout<<0<<" ";
			continue;
		}
		int sq=sqrt(num);
		if(sq*sq!=num){
			cout<<0<<" ";
			continue;
		}
		if(num==0){
			cout<<mp[(x-sq)/2]*(mp[(x-sq)/2]-1)/2<<" ";
			continue;
		}
		int n1=x-sq,n2=x+sq;
		int ans=0;
		cout<<mp[n1/2]*mp[n2/2]<<" ";
	}
	cout<<endl;
}
signed main(){
 	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```