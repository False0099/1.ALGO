给定 n，m，求
$$
\sum_{i=1}^n \sum_{j=1}^m [gcd(i,j)\in Pr\mathrm{Im}]
$$

## 题解
我们这一题因为我们最后的 gcd 答案并不是固定的，所以我们在转化的时候可能还要多写几步, 我们首先把原本抽象的范围抽象成我们的限制条件。
$$
\sum_{i=1}^n \sum_{j=1}^m [gcd(i,j)\in Pr\mathrm{Im}]
$$
= $\sum_{i=1}^n \sum_{j=1}^m\sum_{k=1}^n [gcd(i,j)=k][k \in Pr\mathrm{Im}]$
= $\sum_{k=1}^n \sum_{i=1}^{n/k}\sum_{j=1}^{m/k} [gcd(i,j)=1][k \in Pr\mathrm{Im}]$
= $\sum_{i=1}^n \sum_{j=1}^m\sum_{k=1}^n \sum_{d=1}^{n/k} [d|i][d|j]\mu(d)[k \in Pr\mathrm{Im}]$
= $\sum_{k=1}^n \sum_{d=1}^{n/k}\mu(d)\left[ \frac{n}{kd} \right]\left[ \frac{m}{kd} \right][k\in prime]$

我们令我们的 T=kd，则我们的原始变为

$\sum_{k=1}^n \sum_{\frac{T}{k}=1}^{n/k}\mu\left( \frac{T}{k} \right)\left[ \frac{n}{T} \right]\left[ \frac{m}{T} \right][k \in Prims]$
= $\sum_{k=1}^n \sum_{T=1}^{n}\mu\left( \frac{T}{k} \right)\left[ \frac{n}{T} \right]\left[ \frac{m}{T} \right][k \in Prims]$
= $\sum_{T=1}^n \left[ \frac{n}{T} \right]\left[ \frac{m}{T} \right]\sum_{k \in Prims} \mu\left( \frac{T}{k} \right)$

这一步我们又可以通过我们的整除分块去做
```cpp
void init(){
	mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			prime[++cnt]=j;
			mu[i]=-1; 
		}
		for(int j=2;j*p[i]<N;j++){
			vis[j*p[i]]=1;
			if(i%p[j]==0) break;
			mu[i*p[j]]=-mu[i];
		}
	}
	for(int i=1;i<=cnt;i++){
		for(int j=p[i];j<n;j++){
			F[j]+=mu[j/p[i]];
		}
	}
	for(int i=1;i<N;i++){
		F[i]+=F[i-1];
	}
}
ll calc(int n,int m){
	if(n>m) swap(n,m);
	LL ans=0;
	for(int l=1,r;l<=n;l=r+1){
		r=min(n/(n/l)),m/(m/l);
		ans+=1ll*(F[r]-F[l-1])*(n/l)*(m/l);
	}
	return ans;
}
```