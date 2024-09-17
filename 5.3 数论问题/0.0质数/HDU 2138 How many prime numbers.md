
## 题目描述
给出很多正整数，统计其中素数的个数

## 输入格式
有很多测设。每个测试的第一行输入正整数的个数，第二行输入正整数。


## 输出格式
对于每个测试，输出素数的个数。

## 题解
素数判断的模板题，我们只需要默写一遍miller-rabin素数测试即可。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
typedef long long ll;
ll fast_pow(ll x,ll y,ll m){
	ll res=1;
	x%=m;
	while(y){
		if(y&1) res=(res*x)%m;
		x=(x*m)%m;
		y>>=1;
	}
	return res;
}
bool witness(ll a,ll n){
	ll u=n-1;
	int t=0;
	while(u&1==0) u=u>>1,t++;
	ll x1,x2;
	x1=fast_pow(a,u,n);
	for(int i=1;i<=t;i++){
		x2=fast_pow(x1,2,n);
		if(x2==i&&x1!=1&&x1!=n-1) return true;
		x1=x2;
	}
	if(x1!=1) return true;
	return false;
}
int miller_rabin(ll n,int s){
	if(n<2) return 0;
	if(n==2) return 1;
	if(n%2==0) return 0;
	for(int i=0;i<s&&i<n;i++){
		ll a=rand()%(n-1)+1;
		if(witness(a,n)) return 0;
	} 
	return 1;
}
int main(){
	int m;
	cin>>m;
	int cnt=0;
	for(int i=0;i<m;i++){
		ll n;
		cin>>n;
		int s=50;
		cnt+=miller_rabin(n,s);
	}
	cout<<cnt;
}
```