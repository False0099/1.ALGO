# 
## 题目描述
求两个字符串的最长公共子串

## 输入格式
每个测试输入两个字符串，每个字符串最多有100000个字符。所有字符都是小写的。


## 输出格式
输出最长公共子串的长度


## 样例 #1

### 样例输入 #1

```
banana
cianaic
```

### 样例输出 #1

```
3
```

## 题解
我们先把两个数组拼凑成一个大的字符串，我们再对现在的这个字符串进行后缀数组操作，然后转变为求一个数组中的最长重复子串，那么我们就等价于查找最大的height，并且还要满足两个属于不同的串（可以通过位置判断）

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
char s[N];
int sa[N];
int rk[N];
int cnt[N];
int t1[N];
int t2[N];
int height[N];
int n;
bool cmp_sa(int i,int j){
	if(rk[i]!=rk[j]){
		return rk[i]<rk[j];
	}else{
		int ri=i+k<=n?rk[i+k]:-1;
		int rj=j+k<=n?rk[j+k]:-1;
		return ri<rj; 
	}
}
void calc_sa(){
	int m=127;
	int i,*x=t1,*y=t2;
	for(int i=0;i<m;i++){
		cnt[i]=0;
	}
	for(int i=0;i<n;i++){
		cnt[x[i]=s[i]]++;
	}
	for(int i=1;i<m;i++){
		cnt[i]+=cnt[i-1];
	}
	for(int i=n-1;i>=0;i--){
		sa[--cnt[x[i]]]=i;
	}
	for(int k=1;k<=n;k=k*2){
		int p=0;
		for(int i=n-k;i<n;i++){
			y[p++]=i;
		}
		for(int i=0;i<n;i++){
			if(sa[i]>=k) y[p++]=sa[i]-k;
		}
		for(int i=0;i<m;i++){
			cnt[i]=0;
		}
		for(int i=0;i<n;i++){
			cnt[x[y[i]]]++;
		}
		for(int i=1;i<m;i++){
			cnt[i]+=cnt[i-1];
		}
		for(int i=n-1;i>=0;i--){
			sa[--cnt[x[y[i]]]]=y[i];
		}
		swap(x,y);
		p=1;x[sa[0]]=0;
		for(int i=1;i<n;i++){
			x[s[i]]=y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;
		}
		if(p>=n) break;
		m=p;
	}
}
void getheight(int n){
	int i,j,k=0;
	for(int i=0;i<n;i++){
		rk[sa[i]]=i;
	}
	for(int i=0;i<n;i++){
		if(k){
			k--;
		}
		int j=sa[rk[i]-1];
		while(s[i+k]==s[j+k]) k++;
		height[rk[i]]=k;
	} 
}
int main(){
	int len1,ans;
	while(cin>>s){
		n=strlen(s);
		len1=n;
		s[n]='$';
		scanf("%s",s+n+1);
		n=strlen(s);
		calc_sa();
		getheight(n);
		ans=0;
		for(int i=1;i<n;i++){
			if(height[i]>ans&&((sa[i-1]<len&&sa[i]>=len1)||(sa[i-1]>len1&&sa[i]<len1))){
				ans=height[i];//找到最大的height[i]并且在不同的子串中。 
			}
		}
		cout<<ans;
	}
} 
```