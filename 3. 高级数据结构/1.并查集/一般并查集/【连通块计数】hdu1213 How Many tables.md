
## 题目描述
集训队要进行一项测试，所有人都早早的来到了实验室，但是现在有一个问题，我们需要多少张桌子来安排测试呢？  
众所周知集训队的桌子非常非常的大，每张桌子都足以坐下所有人，但是我们不想让不认识的人坐在一起，否则会影响发挥  
比如如果A认识B，B认识C，那么ABC三个人就可以坐在同一张桌子上  
但如果A认识B，C认识D，那我们就默认AB和CD不认识，需要准备两张桌子  
现在我们需要你计算出，我们一共最少需要多少张桌子

## 输入格式
输入第一行为一个整数 T，表示包含 T 组数据（1<=T<=25）  
对于每组数据，第一行为两个整数N，M，表示有N个人，M对人相互认识（1 <= N，M <= 1000）  
接下来M行，每个行输入两个整数u、v，表示u认识v。


## 输出格式
对于每个测试用例，只需输出至少需要多少张桌子


## 样例 #1

### 样例输入 #1

```
2
5 3
1 2
2 3
4 5

5 1
2 5

```

### 样例输出 #1

```
2
4

```

## 提示




## 题解
简单来说，这个题就是并查集的模板题，不需要任何转化

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int f[N];
int n,m;
void init(){
	for(int i=0;i<n;i++){
		f[i]=i;
	}
}
int find_set(int x){//查询根节点 
	return x==s[x]?s[x]:find_set(s[x]);
}
void merge(int x,int y){
	x=find_set(x);
	y=find_set(y);
	if(x!=y){
		s[x]=s[y];
	}
}
int main(){
	cin>>n>>m;
	init();
	for(int i=0;i<m;i++){
		int a,b;
		cin>>a>>b;
		merge(a,b);
	}
	int ans=0;
	for(int i=0;i<n;i++){
		if(s[i]==i){
			ans++;
		}
	}
	cout<<ans;
}
```