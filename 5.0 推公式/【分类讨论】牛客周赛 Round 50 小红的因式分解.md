## 题目描述
小红有三个整数 $a,b,c$，要将 $ax^2+bx+c$ 分解为 $(a_1x+b_1)(a_2x+b_2)$ 的形式，其中 $a_1,b_1,a_2,b_2$ 均为整数。  
如果可以分解，请按 $a_1,b_1,a_2,b_2$ 的顺序输出，若有多解输出任意一种，若无解，输出 "NO"。

## 输入描述：
第一行输入一个整数 $T$，表示有 $T$ 组测试数据。  
接下来 $T$ 行，每行输入三个整数 $a,b,c$。  
$1 \leq T \leq 100$  

$-10^6 \leq a,b,c \leq 10^6$

$a \neq 0$

## 输出描述：
输出 $T$ 行，每行输出四个整数 $a_1,b_1,a_2,b_2$，表示 $(a_1x+b_1)(a_2x+b_2)$ 的形式，若无解，输出 "NO"。

## 题解
题意：要求一组 $a_1,b_1,a_2,b_2$ 使得 $ax^2+bx+c=(a_1x+b1)*(a_2x+b_2)$

等价于 $a=a_1*a_2,b=a_1*b_2+a_2*b_1,c=b_1*b_2$

一种方法是直接根号枚举 $a$ 和 $c$ 的因数作为 $a_1$ 和 $b_1$,代入 $a=a_1*a_2,c=b_1*b_2$ 求出 $a_2,b_2$ 然后检查是否
满足 $b=a_1*b_2+a_2*b_1$,注意负因数的情况。
另一种方法是注意到 $\frac{-b_1}{a_1},\frac{-b_2}{a_2}$ 即为方程 $ax^2+bx+c=0$ 的两个根，因此直接通过求根公式判断是否有根，有则解出两根后判断是否是有理根，然后回代解出一组 $a_1,b_1,a_2,b_2$ 即可。注意两个根的最简分数的分母的乘积必须是 $a$ 的约数才可行。
```
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=l;i<=r;++i)
using namespace std;
using ll =long long;
const int N=1e6+50;
const int mod=998244353;
void solve() {
    ll a,b,c;
    cin>>a>>b>>c;
    ll delta=b*b-4*a*c;
    if(delta<0) return cout<<"NO\n",void();
    ll t=sqrtl(delta);
    if(t*t!=delta) return cout<<"NO\n",void();
    ll x=-b+t,y=-b-t,domx=2*a,domy=2*a;
    ll gcdx=__gcd(x,domx),gcdy=__gcd(y,domy);
    domx/=gcdx,x/=gcdx,domy/=gcdy,y/=gcdy;
    if(a%abs(domx*domy)) return cout<<"NO\n",void();
    ll z=a/domx/domy;
    domx*=z,x*=z;
    cout<<-1*domx<<" "<<x<<" "<<-1*domy<<" "<<y<<"\n";
}
signed main() 
{		
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t=1;
	cin>>t;
	while(t--)solve();
	return 0;
}
```