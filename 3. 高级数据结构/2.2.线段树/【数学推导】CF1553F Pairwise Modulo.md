# Pairwise Modulo

## 题面翻译

给定一个由**不同**数组成的序列 $a$，定义 $p_k$ 为：

$$
p_k = \sum_{i=1}^k \sum_{j=1}^k a_i \bmod a_j
$$

其中 $a_i \bmod a_j$ 表示 $a_i$ 除以 $a_j$ 的余数。对于每个 $i \in [1,n]$，求出 $p_i$。

## 题目描述

You have an array $ a $ consisting of $ n $ distinct positive integers, numbered from $ 1 $ to $ n $ . Define $ p_k $ as $ $$$p_k = \sum_{1 \le i, j \le k} a_i \bmod a_j, $ $  where  $ x \\bmod y $  denotes the remainder when  $ x $  is divided by  $ y $ . You have to find and print  $ p\_1, p\_2, \\ldots, p\_n$$ $.

## 输入格式

The first line contains $ n $ — the length of the array ( $ 2 \le n \le 2 \cdot 10^5 $ ).

The second line contains $ n $ space-separated distinct integers $ a_1, \ldots, a_n $ ( $ 1 \le a_i \le 3 \cdot 10^5 $ , $ a_i \neq a_j $ if $ i \neq j $ ).

## 输出格式

Print $ n $ integers $ p_1, p_2, \ldots, p_n $ .

## 样例 #1

### 样例输入 #1

```
4
6 2 7 3
```

### 样例输出 #1

```
0 2 12 22
```

## 样例 #2

### 样例输入 #2

```
3
3 2 1
```

### 样例输出 #2

```
0 3 5
```


## 题解
我们不难发现，我们有：$$\begin{aligned}p_i&=p_{i-1}+\sum_{j=1}^{i-1}(a_j\bmod a_i)+\sum_{j=1}^{i-1}(a_i\bmod a_j)\end{aligned}$$

我们考虑怎么处理后面的两个部分。

对于我们的 $a_{i}\text{ mod }a_{j}$:
若 $a_j>a_i$,那么 $a_j$ 的贡献为 $a_i$。若 $a_j<a_i$,那么 $a_j$ 的贡献为 $a_i-a_j\times\lfloor\frac{a_i}{a_j}\rfloor$。注意到前者与第一种情况的和为 $a_i\times(i-1)$.而后面一部分可以在计算 $a_j$ 时枚举 $c$,对于每个 $[c\times a_j,(c+1)\times a_j-1]$ 区间加 $c\times a_j$ 预处理出来。


$a_{j}\operatorname*{mod}a_{i}\colon$ ·若 $a_j<a_i$,那么 $a_j$ 的贡献为 $a_j$。
 ·若 $a_j>a_i$,那么 $a_j$ 的贡献为 $a_j-a_i\times\lfloor\frac{a_j}{a_j}\rfloor$。注意到前者与第--种情况的和为 $\sum a_j$,而后面 i

$\alpha_{i}$
一部分可以枚举 $c$,对于每个 $[c\times a_i,(c+1)\times a_i-1]$,将答案减去 $a_j$ 落在该区间的数的个数 $num\times(c\times a_i)$ 。
对于所有在范围 $[a_i,2a_i)$ 的 $a_{k_t}$ 贡献是一 $a_{i}$ 对于所有在范围 $[2a_i,3a_i)$ 的 $a_k$,贡献是 $-2a_i$

对于所有范围 $[d\cdot a_i,(d+1)a_i)$ 的 $a_k$。贡献是一 $d\cdot a_i$

根据以上分析，用树状数组维护每个点所积累的贡献值，区间修改+单点查询，所以要维护贡献值的差分


```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int N=2e5+5;
const ll M=3e5+5;
 
ll n,sum,res;
struct BIT{
	ll c[M];
	void add(ll x,ll v){while(x<M)c[x]+=v,x+=x&-x;}
	ll query(ll x){ll s=0; while(x)s+=c[x],x-=x&-x; return s;}
}val,num;
 
int main(){
	cin>>n;
	for(ll i=1,a;i<=n;i++){
		cin>>a,res+=sum+a*(i-1)-val.query(a);
		for(ll j=a;j<M;j+=a){
			int L=min(M-1,j+a-1);
			res-=j*(num.query(L)-num.query(j-1));
			val.add(j,j),val.add(L+1,-j);
		} num.add(a,1),sum+=a,cout<<res<<" ";
	}
	return 0;
}
```

