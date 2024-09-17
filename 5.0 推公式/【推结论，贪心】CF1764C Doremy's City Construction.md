# Doremy's City Construction

## 题面翻译

有一些点，每个点有一个点权 $a_i$, 你可以在任意两个点间连边。最终你连成的图需要满足：不存在点 $u, v, w$，满足 $a_u\leq a_v\leq a_w$ 且边 $(u, v), (v, w)$ 存在。求最多能连的边数。（要求我们构成一个拟序）

Translated by Microchip 2333.

## 题目描述

Doremy's new city is under construction! The city can be regarded as a simple undirected graph with $ n $ vertices. The $ i $ -th vertex has altitude $ a_i $ . Now Doremy is deciding which pairs of vertices should be connected with edges.

Due to economic reasons, there should be no self-loops or multiple edges in the graph.

Due to safety reasons, there should not be pairwise distinct vertices $ u $ , $ v $ , and $ w $ such that $ a_u \leq a_v \leq a_w $ and the edges $ (u, v) $ and $ (v, w) $ exist.

Under these constraints, Doremy would like to know the maximum possible number of edges in the graph. Can you help her?

Note that the constructed graph is allowed to be disconnected.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 2\cdot 10^5 $ ) — the number of vertices.

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1\le a_i\le 10^6 $ ) — the altitudes of each vertex.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the maximum possible number of edges in the graph.

## 样例 #1

### 样例输入 #1

```
4
4
2 2 3 1
6
5 2 3 1 5 2
12
7 2 4 9 1 4 6 3 7 4 2 3
4
1000000 1000000 1000000 1000000
```

### 样例输出 #1

```
3
9
35
2
```

## 提示

In the first test case, there can only be at most $ 3 $ edges in the graph. A possible construction is to connect $ (1,3) $ , $ (2,3) $ , $ (3,4) $ . In the picture below the red number above node $ i $ is $ a_i $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764C/664da7a7b39c78efe9a85191f05318cb0a9df4d9.png)

The following list shows all such $ u $ , $ v $ , $ w $ that the edges $ (u, v) $ and $ (v, w) $ exist.

- $ u=1 $ , $ v=3 $ , $ w=2 $ ;
- $ u=1 $ , $ v=3 $ , $ w=4 $ ;
- $ u=2 $ , $ v=3 $ , $ w=1 $ ;
- $ u=2 $ , $ v=3 $ , $ w=4 $ ;
- $ u=4 $ , $ v=3 $ , $ w=1 $ ;
- $ u=4 $ , $ v=3 $ , $ w=2 $ .

Another possible construction is to connect $ (1,4) $ , $ (2,4) $ , $ (3,4) $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764C/7d1fc03a74b1366633e41dc227acef23827c0f69.png)

An unacceptable construction is to connect $ (1,3) $ , $ (2,3) $ , $ (2,4) $ , $ (3,4) $ . Because when $ u=4 $ , $ v=2 $ , $ w=3 $ , $ a_u\le a_v \le a_w $ holds, and the respective edges exist.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764C/02cccee9e8ea3921ef7338c4d1dd72e83e933cbc.png)


## 题解
CF 的贪心题还是挺有意思的。
·想一想，对于三个数 $a\leq b\leq c$,把 $a$ 分别和 $b,c$ 连边所构成的解会比 $a$ 和 $b$ 连边，$b$ 和 $c$ 连边所构成的解更差吗？如果是多个数呢？

上面那个问题的答案是不，不会更差，因为我们建立起 $b$ 到 $c$ 的连边时，必然就要拆除 $\alpha$ 到 $b$ 的连边或者是 $b$ 到 $c$ 的连边。当数的个数更多的时候，连出像 $a,b,c$ 的这样的链，会出现一系列连锁反应，使得答案不会更优。

 我们考略把数分成两组，一组的所有数都比另一组小。那么我们就可以进行跨组的连边，这样就能保证答
 案是最优的。
 枚举每个数，找出小于等于它的个数和严格大于它的个数，依据乘法原理更新答案。
 有一种特殊情况没有被包含，当所有数都一样的时候，答案就是 $\lfloor\frac n2\rfloor$。


```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
int T, n;
inline int read()
{
    char c=getchar(); int x=0, s=1;
    while(c<'0'||c>'9') { if(c=='-')s=-1;c=getchar();}
    while(c>='0'&&c<= '9') { x=(x<<3)+(x<<1)+c-'0';c=getchar();}
    return x*s;
}
int a[200010];
int main()
{
	T = read();
	while (T--)
	{
		LL ans = 0;
		bool tag = 1;
		n = read();
		for (int i = 1; i <= n; ++i)
		{
			a[i] = read();
			if (a[i] != a[1]) tag = 0;
		}
		a[n + 1] = 1e9;
		if (tag == 1)
		{
			printf("%d\n", n / 2);
			continue;
		}
		sort(a + 1, a + n + 2);
		for (int i = 1; i <= n; ++i)
		{
			int pos = upper_bound(a + 1, a + n + 2, a[i]) - a - 1;
			ans = max(ans, (LL)pos * (LL)(n - pos));	
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```