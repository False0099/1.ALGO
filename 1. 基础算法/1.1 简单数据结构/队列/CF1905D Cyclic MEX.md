#mex #循环移动 #贡献 

# Cyclic MEX

## 题面翻译

对于一个长为 $n$ 的排列 $p$，定义其权值为 $\sum_{i=1}^n \operatorname{mex}_{j=1}^ip_j$，也就是 $p_1\sim p_i$ 中没有出现过的最小自然数的和。

然后你可以对这个排列进行移位操作，问最大权值。

## 题目描述

For an array $ a $ , define its cost as $ \sum_{i=1}^{n} \operatorname{mex} ^\dagger ([a_1, a_2,\ldots, a_i]) $ .

You are given a permutation $ ^\ddagger $ $ p $ of the set $ \{0,1,2,\ldots, n-1\} $ . Find the maximum cost across all cyclic shifts of $ p $ .

 $ ^\dagger\operatorname{mex}([b_1, b_2,\ldots, b_m]) $ is the smallest non-negative integer $ x $ such that $ x $ does not occur among $ b_1, b_2,\ldots, b_m $ .

 $ ^\ddagger $ A permutation of the set $ \{0,1,2,..., n-1\} $ is an array consisting of $ n $ distinct integers from $ 0 $ to $ n-1 $ in arbitrary order. For example, $ [1,2,0,4,3] $ is a permutation, but $ [0,1,1] $ is not a permutation ( $ 1 $ appears twice in the array), and $ [0,2,3] $ is also not a permutation ( $ n=3 $ but there is $ 3 $ in the array).

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^5 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^6 $ ) — the length of the permutation $ p $ .

The second line of each test case contain $ n $ distinct integers $ p_1, p_2, \ldots, p_n $ ( $ 0 \le p_i < n $ ) — the elements of the permutation $ p $ .

It is guaranteed that sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output a single integer — the maximum cost across all cyclic shifts of $ p $ .

## 样例 #1

### 样例输入 #1

```
4
6
5 4 3 2 1 0
3
2 1 0
8
2 3 6 7 0 1 4 5
1
0
```

### 样例输出 #1

```
15
5
31
1
```

## 提示

In the first test case, the cyclic shift that yields the maximum cost is $ [2,1,0,5,4,3] $ with cost $ 0+0+3+3+3+6=15 $ .

In the second test case, the cyclic shift that yields the maximum cost is $ [0,2,1] $ with cost $ 1+1+3=5 $ .

## 题解
对于一个排列的 `MEX`,我们有下面的结论：$mex_{k=1}^i=min_{i+1}^na[i]$,这一点，我们可以通过我们的 mex 的定义来证明，因此，我们就可以先预处理出我们的后缀最小值，然后再去 $o(n)$ 的枚举我们的变化并且更新我们的答案。

然后，我们就要去处理，我们每一次的移动对于我们答案的影响，首先，我们会有：$b_{i+1}\to b_{i}$,然后我们所有的 $b$ 对位移到末尾的 $a$ 取 $min$,最后在让我们的 $n\to b_{n}$,

注意到，无论什么时候，我们的 $b$ 都是单调递增的，所以我们就可以用我们的单调队列维护我们的每一个 $b$ 的出现的次数，一次位移将最小的 $b$ 减少一个，如果没有了就弹出，然后将 $>a$ 的 b 弹出，然后插入等同于弹出 a 数量的 a，最后插入 n 即可。
```cpp
    #include <bits/stdc++.h>
    
    #define int long long
    
    using namespace std;
    
    int32_t main()
    {
    	cin.tie(nullptr)->sync_with_stdio(false);
    	int q;
    	cin >> q;
    	while (q--)
    	{
    		int n;
    		cin >> n;
    		vector<int> a(n + 1);
    		for (int i = 1; i <= n; ++i)
    		{
    			cin >> a[i];
    		}
    		deque<pair<int, int>> dq;
    		vector<int> f(n + 1);
    		int mex = 0;
    		int sum = 0;
    		for (int i = 1; i <= n; ++i)
    		{
    			f[a[i]]++;
    			while (f[mex])
    			{
    				mex++;
    			}
    			dq.push_back({mex, 1});
    			sum += mex;
    		}//预处理出mex序列
    		int ans = sum;
    		for (int i = 1; i < n; ++i)
    		{
    			pair<int, int> me = {a[i], 0};
    			sum -= dq.front().first;
    			dq.front().second--;
    			if (dq.front().second == 0)
    			{
    				dq.pop_front();
    			}
    			while (!dq.empty() && dq.back().first >= a[i])
    			{
    				sum -= dq.back().first * dq.back().second;
    				me.second += dq.back().second;
    				dq.pop_back();
    			}
    			dq.push_back(me);
    			sum = sum + me.first * me.second;
    			dq.push_back({n, 1});
    			sum += n;
    			ans = max(ans, sum);
    		}
    		cout << ans << '\n';
    	}
    }
```