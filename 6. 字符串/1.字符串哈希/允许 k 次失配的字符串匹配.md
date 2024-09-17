![[Pasted image 20231203172913.png]]
## 题解
我们首先枚举所有可能匹配的子串，这里因为我们字串的长度是已知的，所以我们枚举的时间复杂度都是固定的 $o(n)$ 假设我们现在枚举的子串为 $s'$,那么我们就可以通过我们的哈希+二分快速查找到我们的 $s'$ 和 $p$ 第一个不同的位置。之后我们把 $s'$ 和 $p$ 在这个失配位置以及之前的部分删除掉，继续查找下一个适配的位置，这样的过程最多发生 $k$ 次。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define ull unsigned long long 
const int N = 1e5 + 10;
const int b = 131;//base
//自然溢出，没有被卡
int T,ans,n,m;
char s[N],t[N];
ull p[N];
ull f[N],g[N];
ull h(ull *hash,int l,int r){//求子串的hash值
	return (hash[r]-hash[l-1]*p[r-l+1]);
}
int lcp(int x,int y,int r){
	int l = 1;
	while(l<=r){//二分
		int mid = l+r >>1;
		if(h(f,x,x+mid-1)==h(g,y,y+mid-1)) l=mid+1;
		else r = mid-1;
	}
	return l-1;//返回长度
}
bool check(int x){
	int y=1,r=x+m-1,l;//x是s0子串的开头，y是s子串的开头，r是s0子串的结尾
	for(int i=1;i<=3;i++){
		l = lcp(x,y,m-y+1);//
		x += l+1;//跳过失配的位置
		y += l+1;
		if(y>m) return 1;
	}
	return h(f,x,r)==h(g,y,m);
}
int main(){
	scanf("%d",&T);
	p[0] = 1;
	for(int i=1;i<=N-10;i++){//预处理
		p[i] = p[i-1]*b;
	}
	while(T--){
		ans = 0;
		scanf("%s%s",s+1,t+1);
		n = strlen(s+1);
		m = strlen(t+1);
		if(n<m){
			puts("0");
			continue;
		}
		f[0] = g[0] = 0;
		for(int i=1;i<=n;i++){
			f[i] = (f[i-1]*b + s[i]);
		}
		for(int i=1;i<=m;i++){
			g[i] = (g[i-1]*b + t[i]);
		}
		for(int i=1;i<=n-m+1;i++){
			if(check(i)) ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}

```