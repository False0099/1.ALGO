# Qpwoeirut And The City

## 题面翻译

给定长为 $n$ 的数列 $\{h_n\}$，对于其中的一个元素 $h_i(1< i < n)$，我们称它为“好的”，当且仅当 $h_i>h_{i-1}$ 且 $h_i>h_{i+1}$。

你可以进行若干次操作，每次可以选定一个 $i(1\le i\le n)$，并将 $h_i$ 增加 $1$。求使得 $\{h_n\}$ 中 “好的”元素最多，至少需要多少次操作。

多测，$1\le t\le 10^4$，$3\le n\le 10^5$，$1\le h_i\le 10^9$，$\sum n\le 2\times10^5$。

Translated by @Sya_Resory

## 题目描述

Qpwoeirut has taken up architecture and ambitiously decided to remodel his city.

Qpwoeirut's city can be described as a row of $ n $ buildings, the $ i $ -th ( $ 1 \le i \le n $ ) of which is $ h_i $ floors high. You can assume that the height of every floor in this problem is equal. Therefore, building $ i $ is taller than the building $ j $ if and only if the number of floors $ h_i $ in building $ i $ is larger than the number of floors $ h_j $ in building $ j $ .

Building $ i $ is cool if it is taller than both building $ i-1 $ and building $ i+1 $ (and both of them exist). Note that neither the $ 1 $ -st nor the $ n $ -th building can be cool.

To remodel the city, Qpwoeirut needs to maximize the number of cool buildings. To do this, Qpwoeirut can build additional floors on top of any of the buildings to make them taller. Note that he cannot remove already existing floors.

Since building new floors is expensive, Qpwoeirut wants to minimize the number of floors he builds. Find the minimum number of floors Qpwoeirut needs to build in order to maximize the number of cool buildings.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains the single integer $ n $ ( $ 3 \le n \le 10^5 $ ) — the number of buildings in Qpwoeirut's city.

The second line of each test case contains $ n $ integers $ h_1, h_2, \ldots, h_n $ ( $ 1 \le h_i \le 10^9 $ ) — the number of floors in each of the buildings of the city.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the minimum number of additional floors Qpwoeirut needs to build in order to maximize the number of cool buildings.

## 样例 #1

### 样例输入 #1

```
6
3
2 1 2
5
1 2 1 4 3
6
3 1 4 5 5 2
8
4 2 1 3 5 3 6 1
6
1 10 1 1 10 1
8
1 10 11 1 10 11 10 1
```

### 样例输出 #1

```
2
0
3
3
0
4
```

## 提示

In the first test case, it is optimal for Qpwoeirut to make the second building cool by building $ 2 $ additional floors on top of it, making it taller than both of its adjacent buildings. The final heights of buildings will be $ [2, \underline{3}, 2] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/5b747d1e682e5f282bdd90fc1247bc9f2859b4d3.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/ca7bffe47191f356c4fd58ef8f125ae9f7e465e2.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/c25e1e8b92772ee4d6c001b5263ad32fc0bed1d3.png)In the second test case, the number of cool buildings is already maximized, so Qpwoeirut does not need to do anything.

In the third test case, it is optimal for Qpwoeirut to make the third and fifth buildings cool by building $ 2 $ additional floors onto the third building and $ 1 $ additional floor onto the fifth building. The final heights of buildings will be $ [3, 1, \underline{6}, 5, \underline{6}, 2] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/d8dd96553e5aa6fe2bbad7a9bf1dc528da32254c.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/ca7bffe47191f356c4fd58ef8f125ae9f7e465e2.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/6d7185baf1e5e2a187bb01c943d100104f7de6bc.png)It can be shown that it is impossible to make more than $ 2 $ of the buildings cool, or to make $ 2 $ buildings cool using fewer than $ 3 $ additional floors.

In the fourth test case, Qpwoeirut can either make the second building cool, or he can make the third building cool. Either way, he will be building $ 3 $ additional floors and maximizing the number of cool buildings. The final heights of buildings will be $ [4, 2, \underline{4}, 3, 5, 3, 6, 1] $ or $ [4, \underline{5}, 1, 3, 5, 3, 6, 1] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/27f107a434b26468932a928c7c16fd0abda918f0.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/ca7bffe47191f356c4fd58ef8f125ae9f7e465e2.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/4e2e7951e438027228057e8a21e8bea81f160a32.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/8e41aee337358c3f261ed9626c0e19808d3f7d2c.png)
## 题解
我们首先这一题要先去判断我们需要构造多少个我们的 cool building ，那我们现在有一个显然的结论，我们一定要构造总计 $\left[ \frac{n}{2} \right]-1$ 个 cool building。然后我们就可以掐头去尾剩下的部分，平均分成 $k$ 组，然后我们就会发现，我们每一组中一定要选取**不相邻的两项来构造我们的最大值**。而在没两组之前，我们只可能是下面几种情况
1. 1001
2. 0101
3. 1010
而我们在进行转移的时候，发现，如果我们设置两个一组来进行我们的转移，我们不太好转移，因为两个一组我们一共有 4 种情况 00，01，10，11，其中有两个是无关项，我们转移只能是10 10-》01 01-》01，10-》10，也就是一共三种转移，总结就是，如果我们选择了奇数位，那么我们下一次转移必须是奇数位，如果我们选择了偶数位，我们下一次可以任意转移
![[Pasted image 20231113155717.png]]


```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N = 1e5+5;
int n;
int a[N];
int add[N];
long long dp[N];

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=2;i<n;i++)
			add[i] = max(0, max(a[i-1]-a[i], a[i+1]-a[i])+1);
		if(n&1)
		{
			long long ans = 0;
			for(int i=2;i<n;i+=2)
				ans += add[i];
			cout<<ans<<endl;
		}
		else
		{
			memset(dp, 0x3f, sizeof dp);
			dp[1] = 0;
			dp[2] = add[2];
			dp[3] = add[3];
			for(int i=4;i<n;i++)
			{
				if(i&1)
					dp[i] = min(dp[i-2], dp[i-3]) + add[i];
				else
					dp[i] = dp[i-2] + add[i];
			}
			cout<<min(dp[n-1], dp[n-2])<<endl;
		}
	}
	return 0;
}
```