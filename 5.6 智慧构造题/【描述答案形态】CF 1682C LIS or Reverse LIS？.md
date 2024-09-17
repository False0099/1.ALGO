# LIS or Reverse LIS?

## 题面翻译

设一个长为 $n$ 的整数序列 $a$ 是 $\{a_1,a_2,a_3,\cdots,a_n\}$，那么 $a'$ 表示 $\{a_n,a_{n-1},a_{n-2},\cdots,a_1\}$，$\operatorname{LIS}(a)$ 表示 $a$ 的最长严格上升子序列的长度。

现在给定 $a$ 数组，请你将 $a$ 数组重新排列，使得重排后的 $\min(\operatorname{LIS}(a),\operatorname{LIS}(a'))$ 最大。

输入 $t$ 组数据，每组数据先输入 $n$ ，然后输入 $n$ 个整数，所有 $n$ 之和不超过 $2 \times 10^5$。

输出 $t$ 行，每行一组数据的答案，按输入顺序输出。

## 题目描述

You are given an array $ a $ of $ n $ positive integers.

Let $ \text{LIS}(a) $ denote the length of [longest strictly increasing subsequence](https://en.wikipedia.org/wiki/Longest_increasing_subsequence) of $ a $ . For example,

- $ \text{LIS}([2, \underline{1}, 1, \underline{3}]) $ = $ 2 $ .
- $ \text{LIS}([\underline{3}, \underline{5}, \underline{10}, \underline{20}]) $ = $ 4 $ .
- $ \text{LIS}([3, \underline{1}, \underline{2}, \underline{4}]) $ = $ 3 $ .

We define array $ a' $ as the array obtained after reversing the array $ a $ i.e. $ a' = [a_n, a_{n-1}, \ldots , a_1] $ .

The beauty of array $ a $ is defined as $ min (\text{LIS}(a),\text{LIS}(a')) $ .

Your task is to determine the maximum possible beauty of the array $ a $ if you can rearrange the array $ a $ arbitrarily.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ $ (1 \leq t \leq 10^4) $ — the number of test cases. Description of the test cases follows.

The first line of each test case contains a single integer $ n $ $ (1 \leq n \leq 2\cdot 10^5) $ — the length of array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots ,a_n $ $ (1 \leq a_i \leq 10^9) $ — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the maximum possible beauty of $ a $ after rearranging its elements arbitrarily.

## 样例 #1

### 样例输入 #1

```
3
3
6 6 6
6
2 5 4 5 2 4
4
1 3 2 2
```

### 样例输出 #1

```
1
3
2
```

## 提示

In the first test case, $ a $ = $ [6, 6, 6] $ and $ a' $ = $ [6, 6, 6] $ . $ \text{LIS}(a) = \text{LIS}(a') $ = $ 1 $ . Hence the beauty is $ min (1, 1) = 1 $ .

In the second test case, $ a $ can be rearranged to $ [2, 5, 4, 5, 4, 2] $ . Then $ a' $ = $ [2, 4, 5, 4, 5, 2] $ . $ \text{LIS}(a) = \text{LIS}(a') = 3 $ . Hence the beauty is $ 3 $ and it can be shown that this is the maximum possible beauty.

In the third test case, $ a $ can be rearranged to $ [1, 2, 3, 2] $ . Then $ a' $ = $ [2, 3, 2, 1] $ . $\text{LIS}(a) = 3$ , $\text{LIS}(a') = 2$ . Hence the beauty is $min (3, 2) = 2$ and it can be shown that $ 2 $ is the maximum possible beauty.


## 题解
我们不难发现，如果想要我们的最后答案最大，我们最后构造出来的形状是大致能够确定的，就是把我们的最大值放在中间，两边去分别填不同的数即可。
但是我们有一个问题，就是如果有多个数的出现次数是奇数次的，我们应该怎么处理。不难发现，我们只需要让出现只出现 1 次的数字分别在我们的左和右分别出现即可。例如：$132$
就是我们的一个最优的情况。

这个时候，我们只需要统计我们出现了 1 次的数字在左右两侧分别出现了多少次即可。
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pii pair<int,int>
#define fir first
#define sec second 
const int inf=0x3f3f3f3f3f3f3f3f;
#define ISMOD998244353
#ifdef ISMOD998244353
const int mod=998244353;
#else
const int mod=1e9+7;
#endif
void chmax(int &a,int b)
{
	a=max(a,b);
}
void chmin(int &a,int b)
{
	a=min(a,b);
}
int popcount(int x)
{
	return __builtin_popcount(x);
}
void eadd(int &a,int b)
{
	a=(a+b)%mod;
}
void esub(int &a,int b)
{
	a=((a-b)%mod+mod)%mod;
}
void emul(int &a,int b)
{
	a=(a*b)%mod;
}
int add(int a,int b)
{
	return (a+b)%mod;
}
int sub(int a,int b)
{
	return ((a-b)%mod+mod)%mod;
}
int mul(int a,int b)
{
	return (a*b)%mod;
}
const int maxn=2e3;
int jc[maxn+10],jcn[maxn+10];
int quickpow(int x,int p)
{
    int base=x;
    int ans=1;
    while(p)
    {
        if(p&1)ans=ans*base%mod;
        p>>=1;
        base=base*base%mod;
    }
    return ans%mod;
}
void init()
{
    jc[0]=jc[1]=1;
    for(int i=2;i<=maxn;i++)jc[i]=jc[i-1]*i%mod;
    jcn[maxn]=quickpow(jc[maxn],mod-2);
    for(int i=maxn-1;i>=0;i--)jcn[i]=jcn[i+1]*(i+1)%mod;
}
int C(int n,int m)
{
    if(m<0)return 0;
    if(m==0)return 1;
    if(m>n)return 0;
    return ((jc[n]*jcn[m])%mod*jcn[n-m])%mod;
}
void undir_add_edge(vector <int> g[],int u,int v)
{
	g[u].push_back(v);
	g[v].push_back(u);
}
void dir_add_edge(vector <int> g[],int u,int v)
{
	g[u].push_back(v);
}
void output_judge(bool b)
{
	cout<<(b?"yes":"no");
}
void output_Judge(bool b)
{
	cout<<(b?"Yes":"No");
}
void output_JUDGE(bool b)
{
	cout<<(b?"YES":"NO");
}
#define outlen(X) fixed<<setprecision(X)
const double precision=1e-6;
bool dequal(double a,double b)
{
	return (abs(a-b)<=precision);
}
bool dless(double a,double b)
{
	return (b-a>=precision);
}
bool dgreater(double a,double b)
{
	return (a-b>=precision);
}
#define IS_MULTI_TEST

int n,cnt1,cnt2;
map<int,int>mp;
void main_solve()
{
	mp.clear();
	cnt1=cnt2=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		mp[x]++;
	}
	for(auto it=mp.begin();it!=mp.end();it++)
	{
		int id=it->fir,x=it->sec;
		if(x>=2)cnt1++;
		else cnt2++;
	}
	cout<<cnt1+(cnt2+1)/2<<endl;	
}
signed main()
{
	#ifdef IS_MULTI_TEST
		int t;
		cin>>t;
		while(t--)main_solve();
	#else
		main_solve();
	#endif
	return 0;
}
```