# Row Major

## 题面翻译

对于一个字符矩阵 $A$，定义函数 $f(A)$ 为将这个矩阵的每一行顺次连接起来得到的字符串，例如当 $A=\begin{bmatrix}\text{a}&\text{b}\\\text{c}&\text{d}\\\text{e}&\text{f}\end{bmatrix}$ 时，$f(A)=\text{abcdef}$。

定义一个矩阵 $A$ 是坏的，当且仅当它存在两个相邻元素相同。例如当 $A=\begin{bmatrix}\text{a}&\text{b}\\\text{c}&\text{b}\end{bmatrix}$ 时，$A$ 是坏的。

给定 $n$，请构造一个只包含小写字母的长度为 $n$ 的字符串 $s$，使得不存在坏的矩阵 $A$，使得 $f(A)=s$，并且最小化 $s$ 中的不同字母的数量。

## 题目描述

The row-major order of an $ r \times c $ grid of characters $ A $ is the string obtained by concatenating all the rows, i.e. $ $$$ A_{11}A_{12} \dots A_{1c}A_{21}A_{22} \dots A_{2c} \dots A_{r1}A_{r2} \dots A_{rc}.  $ $ </p><p>A grid of characters  $ A $  is <span class="tex-font-style-it">bad</span> if there are some two adjacent cells (cells sharing an edge) with the same character.</p><p>You are given a positive integer  $ n $ . Consider all strings  $ s $  consisting of only lowercase Latin letters such that they are <span class="tex-font-style-bf">not</span> the row-major order of <span class="tex-font-style-bf">any</span> bad grid. Find any string with the minimum number of distinct characters among all such strings of length  $ n$$ $.

It can be proven that at least one such string exists under the constraints of the problem.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The only line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^6 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output a string with the minimum number of distinct characters among all suitable strings of length $ n $ .

If there are multiple solutions, print any of them.

## 样例 #1

### 样例输入 #1

```
4
4
2
1
6
```

### 样例输出 #1

```
that
is
a
tomato
```

## 提示

In the first test case, there are $ 3 $ ways $ s $ can be the row-major order of a grid, and they are all not bad:

Tththathatat It can be proven that $ 3 $ distinct characters is the minimum possible. In the second test case, there are $ 2 $ ways $ s $ can be the row-major order of a grid, and they are both not bad:

Iiss It can be proven that $ 2 $ distinct characters is the minimum possible. In the third test case, there is only $ 1 $ way $ s $ can be the row-major order of a grid, and it is not bad.

In the fourth test case, there are $ 4 $ ways $ s $ can be the row-major order of a grid, and they are all not bad:

Ttotomtomatoomaatomtoato It can be proven that $ 4 $ distinct characters is the minimum possible. Note that, for example, the string "orange" is not an acceptable output because it has $ 6 > 4 $ distinct characters, and the string "banana" is not an acceptable output because it is the row-major order of the following bad grid: banana

## 题解
我们翻译一下题意：即对于任意 $i,j\in N+,$ 若 $j-i|n$,则 $s_{i}\neq s_{j}$。
我们注意到，对于每一个数字 $n$,对应的引述个数 $α(n)$ 相对来说比较小，因此，我们可以考虑暴力米欸据每一个数字对应的因数有哪些，对于每一个因子，求出对应的不等关系。

之后，我们再去考虑我们对于每一个位置可以取哪些字母，然后我们再去从低到高贪心的求出我们的每一个位置应该选择什么字母。

其中，为了方便我们的一个计算，我们进行预处理，而是先处理出我们的因数，然后再一边枚举我们的字母，一边更新我们的后需要的元素。

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define pob pop_back
#define mp make_pair
using namespace std;
typedef long long ll;
typedef long double db;
const int maxn=1000007;
const ll inf=1300000007ll,p=998244353;
ll n,fac[maxn],inv[maxn],cnt;
bool vis[maxn<<1][26];
ll ans[maxn],tar;
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
	ll T=1;
	cin>>T;
	for(int tcs=1;tcs<=T;tcs++){
		cin>>n; cnt=0;
		for(int i=1;i<=n;i++){
			for(int j=0;j<26;j++) vis[i][j]=0;
		}
		for(int i=2;i*i<=n;i++){
			if(n%i==0) fac[++cnt]=i,inv[cnt]=n/i,fac[++cnt]=n/i,inv[cnt]=i;
		}
		for(int i=1;i<=n;i++){
			for(int j=0;j<26;j++){
				if(!vis[i][j]){
					tar=j;
					break;
				}
			}
			ans[i]=tar,vis[i+1][tar]=1;
			for(int j=1;j<=cnt;j++) vis[i+fac[j]][tar]=1;
		}
		for(int i=1;i<=n;i++) cout<<(char)(ans[i]+'a');
		cout<<"\n";
	}
	return 0;
}

```