# 知识点
  ## [[莫队算法]]
# 题目
 # XOR and Favorite Number

## 题面翻译

- 给定一个长度为 $n$ 的序列 $a$，然后再给一个数字 $k$，再给出 $m$ 组询问，每组询问给出一个区间，求这个区间里面有多少个子区间的异或值为 $k$。
- $1 \le n,m \le 10 ^ 5$，$0 \le k,a_i \le 10^6$，$1 \le l_i \le r_i \le n$。


Translated by @char 32_t，Reformed by @ [明依](https://www.luogu.com.cn/user/155826)。

## 题目描述

Bob has a favorite number $ k $ and $ a_{i} $ of length $ n $ . Now he asks you to answer $ m $ queries. Each query is given by a pair $ l_{i} $ and $ r_{i} $ and asks you to count the number of pairs of integers $ i $ and $ j $ , such that $ l<=i<=j<=r $ and the xor of the numbers $ a_{i}, a_{i+1},..., a_{j} $ is equal to $ k $ .

## 输入格式

The first line of the input contains integers $ n $ , $ m $ and $ k $ ( $ 1<=n, m<=100000 $ , $ 0<=k<=1000000 $ ) — the length of the array, the number of queries and Bob's favorite number respectively.

The second line contains $ n $ integers $ a_{i} $ ( $ 0<=a_{i}<=1000000 $ ) — Bob's array.

Then $ m $ lines follow. The $ i $ -th line contains integers $ l_{i} $ and $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) — the parameters of the $ i $ -th query.

## 输出格式

Print $ m $ lines, answer the queries in the order they appear in the input.

## 样例 #1

### 样例输入 #1

```
6 2 3
1 2 1 1 0 3
1 6
3 5
```

### 样例输出 #1

```
7
0
```

## 样例 #2

### 样例输入 #2

```
5 3 1
1 1 1 1 1
1 5
2 4
1 3
```

### 样例输出 #2

```
9
4
4
```

# 思路
·我们可以用**前缀异或数组**，这样的话我们就把区间转化为点对，原本求有多少段**区间满足就变成有多少个数对满足**$(ai \oplus a_{j}=k)$
这个时候我们就可以考虑用莫队离线计算我们的答案。以 $cnt[i]$ 表示数字 $i$ 在区间内出现的次数。
# AC 代码
```cpp
#include <cmath>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N=100010,M=1200010;
int n,m,k,l,r,T,cnt[M],a[N],pos[N];
ll ans;

struct Ask
{
	int l,r,id;
	ll ans;
}ask[N];

ll write(ll x)
{
	if (x>9) write(x/10);
	putchar(x%10+48);
} 

bool cmp1(Ask x,Ask y)  //按照块来排序
{
	if (pos[x.l]<pos[y.l]) return 1;
	if (pos[x.l]>pos[y.l]) return 0;
	return x.r<y.r;
}

bool cmp2(Ask x,Ask y)
{
	return x.id<y.id;
}

void add(int x)
{
	ans+=(ll)cnt[a[x]^k];  //加上数字a[x]^k的个数。
	cnt[a[x]]++;
}

void del(int x)
{
	cnt[a[x]]--;//在这个位置的结果不计入我们的答案
	ans-=(ll)cnt[a[x]^k];//因为k是定值，所以我们可以直接逆运算
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	T=(int)sqrt(n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		a[i]^=a[i-1];
		pos[i]=(i-1)/T+1;
	} 
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&ask[i].l,&ask[i].r);
		ask[i].l--;
		ask[i].id=i;
	}
	sort(ask+1,ask+1+m,cmp1);
	cnt[0]=1;
	for (int i=1;i<=m;i++)
	{
		for (;l<ask[i].l;l++) del(l);
		for (;l>ask[i].l;l--) add(l-1);
		for (;r<ask[i].r;r++) add(r+1);
		for (;r>ask[i].r;r--) del(r);
		ask[i].ans=ans;  //直接记录答案
	}
	sort(ask+1,ask+1+m,cmp2);
	for (int i=1;i<=m;i++)
		write(ask[i].ans),putchar(10);
	return 0;
}
```

# 备注
