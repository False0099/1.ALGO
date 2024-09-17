# Two Permutations

## 题面翻译

给出两个排列$a, b $，长度分别为 $n,m$，你需要计算有多少个$ x $，使得 $a_1 + x,a_2 + x,...a_n + x$ 是 $b$ 的子序列  
$n \leq m \leq 2 \times 10^5$

## 题目描述

Rubik is very keen on number permutations.

A permutation $ a $ with length $ n $ is a sequence, consisting of $ n $ different numbers from 1 to $ n $ . Element number $ i $ $ (1<=i<=n) $ of this permutation will be denoted as $ a_{i} $ .

Furik decided to make a present to Rubik and came up with a new problem on permutations. Furik tells Rubik two number permutations: permutation $ a $ with length $ n $ and permutation $ b $ with length $ m $ . Rubik must give an answer to the problem: how many distinct integers $ d $ exist, such that sequence $ c $ $ (c_{1}=a_{1}+d, c_{2}=a_{2}+d,..., c_{n}=a_{n}+d) $ of length $ n $ is a subsequence of $ b $ .

Sequence $ a $ is a subsequence of sequence $ b $ , if there are such indices $ i_{1}, i_{2},..., i_{n} $ $ (1<=i_{1}&lt; i_{2}&lt;...&lt; i_{n}<=m) $ , that $ a_{1}=b_{i 1} $ , $ a_{2}=b_{i 2} $ , $ ... $ , $ a_{n}=b_{in} $ , where $ n $ is the length of sequence $ a $ , and $ m $ is the length of sequence $ b $ .


You are given permutations $ a $ and $ b $ , help Rubik solve the given problem.

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (1<=n<=m<=200000) $ — the sizes of the given permutations. The second line contains $ n $ distinct integers — permutation $ a $ , the third line contains $ m $ distinct integers — permutation $ b $ . Numbers on the lines are separated by spaces.

## 输出格式

On a single line print the answer to the problem.

## 样例 #1

### 样例输入 #1

```
1 1
1
1
```

### 样例输出 #1

```
1
```

## 样例 #2

### 样例输入 #2

```
1 2
1
2 1
```

### 样例输出 #2

```
2
```

## 样例 #3

### 样例输入 #3

```
3 3
2 3 1
1 2 3
```

### 样例输出 #3

```
0
```

## 题解
我们本题是我们线段树维护哈希值的模板，我们首先注意到，我们的 $n$ 很小，于是，我们就可以通过枚举每一个可能的 $x$，然后再去快速的判断得到我们的答案。

考虑怎么去判断我们的每一个 $x$ 是否合法，注意到，如果我们把我们的 $n$ 序列都加上 $x$ 之后，我们的值域范围就变成了: $[1+x,1+x+n]$。然后，如果我们是符合要求的，那么我们一定有：对应的在 m 中的值域也是 $[1+x,1+x+n]$,于是，我们就可以把我们的不再这个至于范围内的数字忽略掉，只考虑在我们的值域中的数字。

又因为我们有：两个序列相同，当前仅当他们出现的次序相同，且我们的数字相同，又因为我们是一个排列，所以我们可以忽略掉我们的数字相同的要求，转而只需要我们的大小出现次序相同。

同于我们的大小出现次序，我们的 x 数组本身就是一个大小出现次序，而对于我们的 y 数组来说，我们的大小出现次序需要进行转化，我们考虑用一个哈希维护一个字符串，

举例：
假如我们的 a 序列是 $145326$,
我们的 $b$ 序列是 $985674321$
那么在我们的 $x=0$ 时，我们的 b 序列经过处理后的对应的有效位应该表示为： $001101111$，我们的 $base$ 位应该修改为：$005604321$,拥有了有效位和我们的 base 位，我们就能够快速的维护我们的对应的哈希值。

而我们每一次修改，都只会修改两个位置的哈希值和 base 值。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10;
const int p=1331;
const int mod=1e9+7;
int a[N];
int b[N];
int bs[N];
int sbs[N];
int pos[N];
unsigned long long hasha=0;
struct node{
	int l,r;
	unsigned long long hash;
	int cnt; 
}tr[N<<4];
int qmi(int x,int y){
	int res=1;
	while(y>0){
		if(y&1)
			res*=x,res%=mod;
		x*=x,x%=mod,y>>=1;
	}
	return res;
}
void pushup(int u){
	tr[u].cnt=tr[u<<1].cnt+tr[u<<1|1].cnt;
	tr[u].hash=((tr[u<<1].hash*qmi(p,tr[u<<1|1].cnt)%mod)%mod+tr[u<<1|1].hash)%mod;
}
void build(int u,int l,int r){
	if(l==r){
		tr[u].l=l;
		tr[u].r=r;
		tr[u].cnt=0;
		tr[u].hash=0;
		return;
	}
	tr[u].l=l;
	tr[u].r=r;
	int mid=l+r>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	pushup(u);
}
void modify(int u,int pos,int x){
	if(tr[u].l==tr[u].r){
		tr[u].cnt=x;
		if(tr[u].cnt>=1){
			tr[u].hash=b[tr[u].r];
		}else{
			tr[u].hash=0;
		}
		return;
	}
	int mid=tr[u].l+tr[u].r>>1;
	if(pos<=mid){
		modify(u<<1,pos,x);
	}else{
		modify(u<<1|1,pos,x);
	}
	pushup(u);
}

signed main(){
	bs[0]=1;
	for (int i = 1; i <= 200000; ++i){
		bs[i]=bs[i-1]*p%mod;
	}
	sbs[0]=1;
    for (int i = 1; i <= 200000; ++i) sbs[i] = (sbs[i - 1] + bs[i]) % mod;
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		hasha=(hasha*p%mod+a[i])%mod;
	} 
	for(int j=1;j<=m;j++){
		cin>>b[j];
		pos[b[j]]=j;
	}
	build(1,1,m);
	for(int j=1;j<=n;j++){
		modify(1,pos[a[j]],1);
	}
	int ans=0;
	int l=1,r=n+1;
	if(hasha==tr[1].hash){
		ans++;
	}
	while(r<=m){
		modify(1,pos[l],0);
		modify(1,pos[r],1);
		hasha=(hasha+sbs[n-1])%mod;
		if(hasha==tr[1].hash){
			ans++;
		}
		l++;
		r++;
	}
	cout<<ans<<endl;
}
```