# 【模板】扩展中国剩余定理（EXCRT）

## 题目描述

给定  $n$ 组非负整数  $a_i, b_i$ ，求解关于  $x$ 的方程组的最小非负整数解。
$$\begin{cases} x \equiv b_1\ ({\rm mod}\ a_1) \\ x\equiv b_2\ ({\rm mod}\ a_2) \\ ... \\ x \equiv b_n\ ({\rm mod}\ a_n)\end{cases}$$

## 输入格式

输入第一行包含整数 $n$。

接下来 $n$ 行，每行两个非负整数 $a_i, b_i$。

## 输出格式

输出一行，为满足条件的最小非负整数 $x$。

## 样例 #1

### 样例输入 #1

```
3
11 6
25 9
33 17
```

### 样例输出 #1

```
809
```

## 提示

对于 $100 \%$ 的数据，$1 \le n \le {10}^5$，$1 \le b_i,a_i \le {10}^{12}$，保证所有 $a_i$ 的最小公倍数不超过 ${10}^{18}$。

**请注意程序运行过程中进行乘法运算时结果可能有溢出的风险。**

数据保证有解。

## 题解
本题我们的思路是采用我们的**迭代法进行校园，相比较于我们的一般的中国剩余定理，这是更通用的**。

我们的迭代法的核心是，**合并我们的两个同余方程为一个**。例如：我们有
$$
\begin{align}
x=2(\text{mod \ 3}) \\
x=3(\text{mod \ 5})
\end{align}
$$
那么如果我们希望能够合并我们的这两个同余方程，我们首先有我们的第一个转换为 $x=2t+3$,然后我们把这个带入我们的 $x=3\text{\ mod\ 5}$，之后，我们再去把我们的对应的求解，我们就有：$3t=1\text{\ mod 5}$。然后我们在可以转换为：$t=5u+2$,我们再把这一个式子回带到我们的答案中，我们就有：
$x=8\text{mod 15}$。

我们上述的合并过程写成我们的代码形式，我们就有：
![[Pasted image 20240826153337.png]]



```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100010;
int n;
ll ai[N];
ll mi[N];
ll mul(ll a,ll b,ll m){
	ll res=0;
	while(b){
		if(b&1) res=(res+a)%m;
		a=(a+a)%m;
		b>>=1;
	}
	return res;
}
ll extend_gcd(ll a,ll b,ll &x,ll &y){
	if(b==0){
		x=1;
		y=0;
		return a;
	}
	ll d=extend_gcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}
ll excrt(){
	ll x,y;
	ll m1=mi[1],a1=ai[1];
	ll ans=ai[1];
	for(int i=2;i<=n;i++){
		ll a2=ai[i],m2=mi[i];
		ll a=m1,b=m2,c=(a2-a1%m2+m2)%m2;
		ll d=extend_gcd(a,b,x,y);
		if(c%d!=0) return -1;
		x=mul(x,c/d,b/d);
		ans=a1+x*m1;
		m1=m2/d*m1;
		ans=(ans%m1+m1)%m1;
		a1=ans;
	}
	return ans;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>mi[i]>>ai[i];
	}
	cout<<excrt();
	return 0;
}
```
