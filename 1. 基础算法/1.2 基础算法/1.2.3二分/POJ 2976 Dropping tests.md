## 题目描述
![[Pasted image 20230811165917.png]]

## 输入格式
![[Pasted image 20230811165926.png]]


## 输出格式

![[Pasted image 20230811165931.png]]

## 样例 #1

### 样例输入 #1

```
3 1
5 0 2
5 1 6
4 2
1 2 7 9
5 6 7 9
0 0
```

### 样例输出 #1

```
83
100
```


## 题解
本题是标准的0-1分数规划问题，只需要按照模版解题即可。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
struct Pair{
	int a,b;
	double y;
}p[1005];
bool cmp(Pair a,Pair b){
	return a.y<b.y;
}
int n,k;
bool check(double x){
	for(int i=0;i<n;i++){
		p[i].y=p[i].a*1.0-x*p[i].b;
	}
	sort(p,p+n,cmp);
	double f=0;
	for(int i=0;i<k;i++){
		f+=p[i].y;
	}
	return f<0;
}
int main(){
	while(scanf("%d%d",&n,&k)==2&&n+k){
		k=n-k;
		for(int i=0;i<n;i++) cin>>p[i].a;
		for(int i=0;i<n;i++) cin>>p[i].b;
		double l=0,r=0;
		for(int i=0;i<n;i++) r+=p[i].a;
		for(int i=0;i<50;i++){
			double mid=l+(r-l)/2;
			if(check(mid)) r=mid;
			else l=mid;
		}
		cout<<100*(l);
	}
}
```