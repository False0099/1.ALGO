# Geometry Horse

## 题面翻译

给定 n 种物品，每种物品有 Ki 个，价值为 Ci，摧毁一个物品的贡献为 Ci×f

F 为贡献因子，有一个长度为 t 的单调递增序列 p，当前摧毁的物品若超过 p[i]，则贡献因子 f=i+1

求最大贡献

## 题目描述

Vasya plays the Geometry Horse.

The game goal is to destroy geometric figures of the game world. A certain number of points is given for destroying each figure depending on the figure type and the current factor value.

There are $ n $ types of geometric figures. The number of figures of type $ k_{i} $ and figure cost $ c_{i} $ is known for each figure type. A player gets $ c_{i}·f $ points for destroying one figure of type $ i $ , where $ f $ is the current factor. The factor value can be an integer number from $ 1 $ to $ t+1 $ , inclusive. At the beginning of the game the factor value is equal to 1. The factor is set to $ i+1 $ after destruction of $ p_{i} $ $ (1<=i<=t) $ figures, so the $ (p_{i}+1) $ -th figure to be destroyed is considered with factor equal to $ i+1 $ .

Your task is to determine the maximum number of points Vasya can get after he destroys all figures. Take into account that Vasya is so tough that he can destroy figures in any order chosen by him.

## 输入格式

The first line contains the only integer number $ n $ $ (1<=n<=100) $ — the number of figure types.

Each of the following $ n $ lines contains two integer numbers $ k_{i} $ and $ c_{i} $ $ (1<=k_{i}<=10^{9}, 0<=c_{i}<=1000) $ , separated with space — the number of figures of the $ i $ -th type and the cost of one $ i $ -type figure, correspondingly.

The next line contains the only integer number $ t $ $ (1<=t<=100) $ — the number that describe the factor's changes.

The next line contains $ t $ integer numbers $ p_{i} $ $ (1<=p_{1}&lt; p_{2}&lt;...&lt; p_{t}<=10^{12}) $ , separated with spaces.

Please, do not use the %lld specificator to read or write 64-bit integers in С++. It is preferred to use cin, cout streams or the %I 64 d specificator.

## 输出格式

Print the only number — the maximum number of points Vasya can get.

## 样例 #1

### 样例输入 #1

```
1
5 10
2
3 6
```

### 样例输出 #1

```
70
```

## 样例 #2

### 样例输入 #2

```
2
3 8
5 10
1
20
```

### 样例输出 #2

```
74
```

## 提示

In the first example Vasya destroys three figures first and gets $ 3·1·10=30 $ points. Then the factor will become equal to $ 2 $ and after destroying the last two figures Vasya will get $ 2·2·10=40 $ points. As a result Vasya will get $ 70 $ points.

In the second example all $ 8 $ figures will be destroyed with factor $ 1 $ , so Vasya will get $ (3·8+5·10)·1=74 $ points.

## 题解
我们本题的贪心是显然的，我们每一次一定是先去使用我们最小的，然后再去把我们的比我们当前元素还要大的进行销毁。但是，我们如果只是朴素的暴力的话，我们的时间复杂度能够达到：$\sum k_{i}$,显然不能够通过。

那么，我们现在可能的一种方法就是，我们通过我们的堆来优化我们每一次取数计算的过程。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int,int> PII;
signed main(){
	int n;
	cin>>n;
	priority_queue<PII,vector<PII>,greater<PII>> heap;
	for(int i=0;i<n;i++){
		int a,b;
		cin>>a>>b;
		heap.push({b,a});
	}
	int m;
	cin>>m;
	int ans=0;
	int f=1;
	vector<int> fac(m);
	for(int i=0;i<m;i++){
		cin>>fac[i];
	}
	for(int i=m-1;i>0;i--){
		fac[i]=fac[i]-fac[i-1];
	}
	for(int i=0;i<m;i++){
		int k=fac[i];
		while(heap.size()&&k){
			auto u=heap.top();
			heap.pop();
			if(u.second>=k){
				ans+=(f)*(u.first)*(k);
				f++;
				u.second-=k;
				k=0;
				heap.push(u);
				break;	
			}else{
				ans+=f*u.first*u.second;
				k-=u.second;
			} 
		}
	}
	while(heap.size()){
		auto u=heap.top();
		heap.pop();
		ans+=f*u.first*u.second;
	} 
	cout<<ans<<endl; 
}
```