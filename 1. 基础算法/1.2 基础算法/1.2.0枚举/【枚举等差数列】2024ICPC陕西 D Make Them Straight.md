## 题意
给你一个数组 $a$,以及一个数组 $b$,我们对 $a$ 中的每一个数字进行变换，我们的代价是 $b[i]$,问我们最少用多少次变化，能够把我们的数列变成等差数列

## 数据范围：
$n\leq 2\times10^5,a[i]\leq 10^6,b[i]\leq 10^6$

## 题解
我们本体的思路是：枚举我们的**等差数列的公比**，然后再去计算出我们以每一个位置为不变点时，我们的 $a[1]$ 是多少，然后再根据我们的 $a[1]$ 的对应的可能取值，去计算我们的答案。

这样做，我们最后的时间复杂度不会超过我们的 $1e6$,能够通过我们的本题，最多加上一个 $\log n$ 的复杂度来枚举我们的对应结果。

```
#include <bits/stdc++.h>
using namespace std;
const int N=1e6;
int main(){
	int n;
	cin>>n;
	vector<int> a(n);
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	vector<int> b(n);
	int sum=0;
	for(int i=0;i<n;i++){
		cin>>b[i];
		sum+=b[i];
	}
	int ans=sum;
	for(int k=0;k<=N;k++){
		int tmp=0;
		mp.clear();
		for(int i=0;i<n;i++){
			if(i*k>=N){
				break;
			}else{
				if(a[i]-k*i>=0){
					mp[a[i]-k*i]+=b[i];
					tmp=max(tmp,mp[a[i]-k*i]);
				}
			}
			ans=min(ans,sum-tmp);
		}
	}
	cout<<ans<<endl;
}
```