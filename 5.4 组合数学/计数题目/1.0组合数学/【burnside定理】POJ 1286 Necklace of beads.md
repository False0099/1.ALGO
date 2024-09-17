# 
## 题目描述
任选n个红、绿、蓝三种颜色的珠子穿成项链，能穿成多少种项链？项链可以旋转、翻转。


## 题解
我们考虑旋转置换时，假设我们第i个旋转与原位置错位了i个，那么我们第i个旋转的循环节节数为$gcd(n,i)$,n表示n边形。例如n=5时，循环节数分别为{$5,1,1,1,1$}。

我们考虑翻转操作，对照正方形与五边形，我们可以发现，当n为偶数时，经过顶点的对称轴为$\frac{n}{2}$个，每种置换有$\frac{n}{2}+1$个循环节。不经过顶点的对称轴有$\frac{n}{2}$个，每种置换方案都有$\frac{n}{2}$个循环节。

当n为奇数时，对称轴都经过顶点，有n种置换，每种置换有$\frac{n}{2}+1$个循环节。

所以我们的代码就可以求出来了




## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
typedef long long ll;
int main(){
	ll n;
	cin>>n;
	if(n==0) {cout<<0<<endl;return 0;}
	ll ans=0;
	for(ll i=0;i<n;i++){
		ans+=(ll)pow(3,__gcd(n,i));
	}
	if(n%2) ans+=n*(ll)pow(3,n/2+1);
	else{
		ans+=n/2*(ll)pow(3,n/2);
		ans+=n/2*(ll)pow(3,n/2+1);
	}
	printf("%lld",ans/(n*2)); 
	
	return 0;
}
```