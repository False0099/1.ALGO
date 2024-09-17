# 知识点
  ## [[树形DP]]
# 题目
 如果一个数 x的约数之和 y（不包括他本身）比他本身小，那么 x可以变成 y，y也可以变成 x。

例如，4 可以变为 3，1 可以变为 7。

限定所有数字变换在不超过 n 的正整数范围内进行，求不断进行数字变换且不出现重复数字的最多变换步数。

## 输入格式
输入一个正整数 n
。

## 输出格式
输出不断进行数字变换且不出现重复数字的最多变换步数。

## 数据范围
1≤n≤50000
## 输入样例 ：
7
## 输出样例 ：
3
## 样例解释
一种方案为：4→3→1→7

# 思路
·我们按照规则来构建一个森林，然后我们就直接求森林中的最大直径即可，对于建图，我们可以用到朴素的试除法，当然也可以用筛法的思想去解决每一个数的约数。
·筛法求每个数的约束和也很简单，我们先设置一个数组 sum 用于储存每个数的质数和，（同理，如果我们要求具体的数，也可以用一个 vector 来储存）
·
# AC 代码
```cpp
#include <iostream>
using namespace std;
int h[N],ne[N],e[N],idx;
int sum[N];
bool st[N];
int res;
void add(int a,int b){
	e[idx]=b;
	ne[idx]=h[a];
	h[a]=idx++;
}
int dfs(int u){
	int d1=0,d2=0;
	for(int i=h[u];i!=-1;i=ne[i]){
		int j=e[i];
		int d=dfs(j)+1;
		if(d>=d1) d2=d1,d1=d;
		else if(d>=d2) d2=d;
	}
	ans=max(ans,d1+d2);
	return d1;
}
int main(){
	for(int i=1;i<=n;i++){
		for(int j=1;j*i<=n;j++){
			sum[i*j]+=i;
		}
	}
	for(int i=1;i<=n;i++){
		if(i>sum[i]){
			add(sum[i],i);
			st[i]=true;
		}
	}	
	for(int i=2;i<=n;i++){
		if(!st[i]){
			dfs[i];
		}
	}
	cout<<ans<<endl;
}
```
# 备注
