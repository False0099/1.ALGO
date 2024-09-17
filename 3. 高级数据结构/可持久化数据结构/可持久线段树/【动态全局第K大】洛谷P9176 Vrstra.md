# [COCI 2022-2023 #4 ] Vrsta

## 题目描述

Domagoj 最喜欢的课是体育课。每节体育课都以热身运动开始。体育老师有一个有趣的方法来选择带领其他同学做热身运动的学生。学生们按身高从低到高的顺序站成一排，老师会选择站在队伍中间的学生。如果有两个学生在中间，他将选择较矮的那个。例如：如果学生的身高为 $1, 3, 5, 7, 11$，身高为 $5$ 的学生将带领其他同学做热身运动。

Domagoj 记不住他同学的身高。幸运的是，站在他旁边的 Lovro 十分擅长估计他人的身高。他给了 Domagoj $n$ 条信息：「有 $a_i$ 个身高为 $v_i$ 的学生进入了体育馆。」在 Lovro 说完每条信息之后，Domagoj 都对带领其他同学做热身运动的那个同学的身高感兴趣。假定所有进入体育馆的同学都是来上体育课的。请帮他回答他的问题！

## 输入格式

第一行一个整数 $n\ (1\le n\le 200\ 000)$，表示 Lovro 的信息条数。

接下来 $n$ 行包含两个整数 $v_i,a_i\ (1\le v_i,a_i\le 10^9)$，表示 Lovro 所给信息中的身高和人数。

## 输出格式

输出 $n$ 行，表示在 Lovro 给出第 $i$ 条信息后，对 Domagoj 问题的回答。

## 样例 #1

### 样例输入 #1

```
3
2 1
3 1
1 1
```

### 样例输出 #1

```
2
2
2
```

## 样例 #2

### 样例输入 #2

```
4
17 2
23 5
11 4
9 5
```

### 样例输出 #2

```
17
23
17
11
```

## 样例 #3

### 样例输入 #3

```
3
10 20
100 5
1000 5
```

### 样例输出 #3

```
10
10
10
```

## 提示

| 子任务编号 |          附加限制          |  分值  |
| :---: | :--------------------: | :--: |
|  $0$  |          是样例           | $0$  |
|  $1$  |    $n,v_i\le 1000$     | $17$ |
|  $2$  | $a_1=a_2=\ldots=a_n=1$ | $24$ |
|  $3$  | $v_1<v_2<\ldots <v_n$  | $26$ |
|  $4$  |         无附加限制          | $33$ |
## 题解
模板化的动态求区间第 $k$ 大，我们只需要采用我们的权值线段树，就可以解决我们的问题，在我们的 query 的时候，只需要注意修改即可

```cpp
// 如果命运对你缄默, 那就活给他看。
// #pragma GCC optimize(1)
// #pragma GCC optimize(2)
// #pragma GCC optimize(3)
// #pragma GCC optimize("Ofast", "inline", "-ffast-math")
// #pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include <bits/stdc++.h>

using namespace std;
typedef long long LL; 
#define int LL
typedef vector<int> vec;
typedef pair<int, int> PII;
#define x first
#define y second
#define epb emplace_back
#define ep emplace
const int maxn = 2e5 + 10;
int n, t[maxn];
PII q[maxn];
#define lowbit(x) (x & -x)
inline void upd(int u, int v) { for(int i = u; i < maxn; i += lowbit(i)) t[i] += v; return ; }
inline int Q(int u) { int ret = 0; for(int i = u; i; i -= lowbit(i)) ret += t[i]; return ret; }
signed main() {
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);
	ios :: sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	vec v; v.epb(-1);
	for(int i = 1; i <= n; ++ i) cin >> q[i].x >> q[i].y, v.epb(q[i].x);
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	int s = 0;
	for(int i = 1; i <= n; ++ i) {
		q[i].x = lower_bound(v.begin(), v.end(), q[i].x) - v.begin();
		s += q[i].y;
		int sm = (s + 1) >> 1;
		upd(q[i].x, q[i].y);
		int l = 1, r = v.size();
		while(l < r) {
			int mid = l + r >> 1;
			if(Q(mid) >= sm) r = mid;
			else l = mid + 1;
		}
		// cout << "ANS ";
		cout << v[l] << '\n';
	}
	return 0;
}
```