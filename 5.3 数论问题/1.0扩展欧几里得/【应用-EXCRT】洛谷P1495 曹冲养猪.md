# 【模板】中国剩余定理（CRT）/ 曹冲养猪

## 题目描述

自从曹冲搞定了大象以后，曹操就开始捉摸让儿子干些事业，于是派他到中原养猪场养猪，可是曹冲满不高兴，于是在工作中马马虎虎，有一次曹操想知道母猪的数量，于是曹冲想狠狠耍曹操一把。举个例子，假如有 $16$ 头母猪，如果建了 $3$ 个猪圈，剩下 $1$ 头猪就没有地方安家了。如果建造了 $5$ 个猪圈，但是仍然有 $1$ 头猪没有地方去，然后如果建造了 $7$ 个猪圈，还有 $2$ 头没有地方去。你作为曹总的私人秘书理所当然要将准确的猪数报给曹总，你该怎么办？

## 输入格式

第一行包含一个整数 $n$ —— 建立猪圈的次数，接下来 $n$ 行，每行两个整数 $a_i, b_i$，表示建立了 $a_i$ 个猪圈，有 $b_i$ 头猪没有去处。你可以假定 $a_1 \sim a_n$ 互质。

## 输出格式

输出包含一个正整数，即为曹冲至少养母猪的数目。

## 样例 #1

### 样例输入 #1

```
3
3 1
5 1
7 2
```

### 样例输出 #1

```
16
```

## 提示

$1 \leq n\le10$，$0 \leq b_i\lt a_i\le100000$，$1 \leq \prod a_i \leq 10^{18}$

## 题解
本题是我们的关于我们的 excrt 的模板，我们的 excrt 所使用到的关键方法就是我们的合并方程，我们通过不断地合并我们的不定方程，最后我们可以得到我们的
$$
x \text{ mod M}=T
$$
这样的形式，最后我们的答案就是 $x=k*t+M$。

对于我们本体，我们需要了解的一点就是：对于我们的两个不定方程，我们应该如何进行合并：我们这里采用的方法是进行暴力的转化；

设两个方程分别是 $x\equiv a_1\pmod{m_1},x\equiv a_2\pmod{m_2};$

将它们转化为不定方程：$x=m_1p+a_1=m_2q+a_2$,其中 $p,q$ 是整数，则有 $m_1p-m_2q=a_2-a_1$

由裴蜀定理，当 $a_2-a_1$ 不能被 $\gcd(m_1,m_2)$ 整除时，无解；

其他情况下，可以通过扩展欧几里得算法解出来一组可行解 $(p,q);$

则原来的两方程组成的模方程组的解为 $x\equiv b$ ( mod $M)$,其中 $b=m_1p+a_1,M=\operatorname{lcm}(m_1,m_2)$

对于我们的剩余的方程，我们只需要两两合并，就能够得到我们的最终的结果。
```
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