# Have Your Cake and Eat It Too

## 题目描述

Alice, Bob and Charlie want to share a rectangular cake cut into $ n $ pieces. Each person considers every piece to be worth a different value. The $ i $ -th piece is considered to be of value $ a_i $ by Alice, $ b_i $ by Bob and $ c_i $ by Charlie.

The sum over all $ a_i $ , all $ b_i $ and all $ c_i $ individually is the same, equal to $ tot $ .

Given the values of each piece of the cake for each person, you need to give each person a contiguous slice of cake. In other words, the indices at the left and right ends of these subarrays (the slices given to each person) can be represented as $ (l_a, r_a) $ , $ (l_b, r_b) $ and $ (l_c, r_c) $ respectively for Alice, Bob and Charlie. The division needs to satisfy the following constraints:

- No piece is assigned to more than one person, i.e., no two subarrays among $ [l_a,\ldots, r_a] $ , $ [l_b, \ldots, r_b] $ and $ [l_c, \ldots, r_c] $ intersect.
- $  \sum_{i = l_a}^{r_a} a_i, \sum_{i = l_b}^{r_b} b_i, \sum_{i = l_c}^{r_c} c_i \geq \lceil \frac{tot}{3} \rceil $ .

Here, the notation $ \lceil \frac{a}{b} \rceil $ represents ceiling division. It is defined as the smallest integer greater than or equal to the exact division of $ a $ by $ b $ . In other words, it rounds up the division result to the nearest integer. For instance $ \lceil \frac{10}{3} \rceil = 4 $ and $ \lceil \frac{15}{3} \rceil = 5 $ .

## 输入格式

The first line contains an integer $ t $ , the number of testcases, ( $ 1 \le t \le 10^4 $ )

For each testcase:

The first line contains the integer $ n $ ( $ 3 \le n \le 2 \cdot 10^5 $ ).

The following three lines contain $ n $ integers each:

One line with $ n $ integers $ a_1, a_2, \ldots, a_n $ represents the values for Alice ( $ 1 \le a_i \le 10^6 $ ).

The next line with $ n $ integers $ b_1, b_2, \ldots, b_n $ represents the values for Bob ( $ 1 \le b_i \le 10^6 $ ).

The next line with $ n $ integers $ c_1, c_2, \ldots, c_n $ represents the values for Charlie ( $ 1 \le c_i \le 10^6 $ ).

It is guaranteed that $  \sum_{i = 1}^{n} a_i = \sum_{i = 1}^{n} b_i = \sum_{i = 1}^{n} c_i $ .

The sum of $ n $ over all testcases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each testcase, output $ -1 $ if the required condition is impossible.

Otherwise, output six numbers – $ l_a, r_a, l_b, r_b, l_c, r_c $ , the respective starting and ending indices ( $ 1 $ -indexed) of the subarrays for Alice, Bob and Charlie, respectively.

## 样例 #1

### 样例输入 #1

```
10
5
5 1 1 1 1
1 1 5 1 1
1 1 1 1 5
6
1 2 3 4 5 6
5 6 1 2 3 4
3 4 5 6 1 2
4
4 4 4 4
4 4 4 4
4 4 4 4
5
5 10 5 2 10
9 6 9 7 1
10 7 10 2 3
3
4 5 2
6 1 4
1 8 2
3
10 4 10
8 7 9
10 4 10
7
57113 65383 19795 53580 74452 3879 23255
12917 16782 89147 93107 27365 15044 43095
33518 63581 33565 34112 46774 44151 41756
6
6 3 1 8 7 1
10 2 6 2 2 4
10 9 2 1 2 2
5
5 5 4 5 5
1 6 3 8 6
2 4 1 9 8
10
1 1 1 1 1001 1 1 1001 1 1
1 1 1 1 1 1 2001 1 1 1
1 1 1 1 1 1001 1 1 1 1001
```

### 样例输出 #1

```
1 1 2 3 4 5 
5 6 1 2 3 4 
-1
-1
1 1 3 3 2 2 
-1
1 2 3 4 5 7 
3 6 1 1 2 2 
1 2 3 4 5 5 
1 5 6 7 8 10
```

## 提示

In the first testcase, the sum of either of the three arrays is $ 9 $ . Each person needs a cake slice corresponding to a subarray with a total value of at least $ \lceil \frac{9}{3} \rceil = 3 $ .

If we assign the subarray ( $ 1 $ , $ 1 $ ) to Alice, its total value to her is $ 5 $ , which is $ \ge 3 $ ; the subarray ( $ 2 $ , $ 3 $ ) to Bob, its total value to him is $ 1 + 5 = 6 $ , which is $ \ge 3 $ ; and the subarray ( $ 4 $ , $ 5 $ ) to Charlie, its total value to him $ 1 + 5 = 6 $ , which is also $ \ge 3 $ . Each person gets their own separate pieces of the cake, and no piece is common to two or more people.

It can be shown that for the third test case, it is not possible to give slices of the cake in a way that satisfies the given constraints.

## 题解
本题我们发现，我们要把我们的元素分割为三段，也就是所我们有**两个断点**。考虑到我们的时间复杂度，我们可以**枚举其中的一个断点**，然后考虑**另外一个端点的位置**。我们对于我们的另一个断点的位置，显然可以通过我们的**预处理来得到我们的最优值**。

同时，我们还需要注意，我们的三个人，**每一个人去拿一个段是不固定的**，所以我还需要使用 $3!$ 的时间复杂度来枚举我们的全排列，作为我们对于每一个端点的分配。

```
// Problem: C. Have Your Cake and Eat It Too
// Contest: Codeforces - Codeforces Round #956 (Div. 2) and ByteRace 2024
// URL: https://codeforces.com/contest/1983/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

typedef long long ll;
#define int ll

int n, a[3][N], sum[3][N];

void solve() {
	cin >> n;
	
	int tot = 0;
	for (int i = 0; i < 3; ++ i )
		for (int j = 1; j <= n; ++ j ) {
			cin >> a[i][j];
			if (!i) tot += a[i][j];
			sum[i][j] = a[i][j] + sum[i][j - 1];
		}
	
	int k = (tot + 2) / 3;
	
	auto calc = [&](int x, int l, int r) {
		return sum[x][r] - (l ? sum[x][l - 1] : 0);
	};
	
	vector<int> id({0, 1, 2});
	do {
		int l = 1, r = n, p1 = -1, p2 = -1;
		while (l <= r) {
			int mid = l + r >> 1;
			if (calc(id[0], 1, mid) >= k) {
				p1 = mid;
				r = mid - 1;
			}
			else {
				l = mid + 1;
			}
		}
		
		l = 1, r = n;
		while (l <= r) {
			int mid = l + r >> 1;
			if (calc(id[2], mid, n) >= k) {
				p2 = mid;
				l = mid + 1;
			}
			else {
				r = mid - 1;
			}
		}
		
		if (~p1 && ~p2 && p1 + 1 < p2 && calc(id[1], p1 + 1, p2 - 1) >= k) {
			vector<int> L(3), R(3);
			L[id[0]] = 1;
			L[id[1]] = p1 + 1;
			L[id[2]] = p2;
			
			R[id[0]] = p1;
			R[id[1]] = p2 - 1;
			R[id[2]] = n;
			
			cout << L[0] << ' ' << R[0] << ' ' << L[1] << ' ' << R[1] << ' ' << L[2] << ' ' << R[2];
			puts("");
			return;
		}
	} while (next_permutation(id.begin(), id.end()));
	
	cout << -1; puts("");
}

signed main() {
	int T;
	cin >> T;
	while (T -- ) solve();
	return 0;
}


```