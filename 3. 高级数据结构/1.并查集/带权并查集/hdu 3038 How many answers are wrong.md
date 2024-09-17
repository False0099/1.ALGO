## 题目描述
给出一个区间的长度 N，及 M 个子区间和，形如：x y z, 表示  
子区间 $[x, y]$ 的和为 z  
如果一个“子区间和”与前面的“子区间和”冲突，即为错误（而且这个“子区间和”将在接下来的判断中被忽略）。  
求总错误个数。

## 输入格式
有多组数据。

每组数据第一行两个整数N M (1 <= N <= 200000, 1 <= M <= 40000),  
接下来每行有 M 对关系 x y z;  
注：可以认为 z 为32位整型


## 输出格式
错误个数。


## 样例 #1

### 样例输入 #1

```
10 5  
1 10 100  
7 10 28  
1 3 32  
4 6 41  
6 6 1
```

### 样例输出 #1

```
1
```

## 题解
我们用**逆向前缀和思想**，维护我们从 0-n 位置的前缀和是奇数还是偶数。

这是一道带权并查集的模板题，其中我们的“权”是指从根节点到目标位置的“前缀”和。显然，我们可以得到，如果一个更新后的权比更新前的权要小，那么就说明是矛盾的

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=200010;
int s[N];
int d[N];//根节点到该点的数字和 
int ans;
void init_set(){
	for(int i=0;i<n;i++){
		s[i]=i;
		d[i]=0;
	}
}
int find_set(int x){
	if(x!=s[x]){
		int t=s[x];
		s[x]=find_set(s[x]);
		d[x]+=d[t]; 
	}
}
void merge(int a,int b,int v){
	int roota=find_set(a);
	int rootb=find_set(b);
	if(roota==rootb){
		if(d[a]-d[b]!=v){
			ans++;
		}
	}else{
		s[roota]=rootb;
		d[roota]=d[b]-d[a]+v;
	}
}
int main(){
	int n,m;
	while(scanf("%d%d",&n,&m)!=EOF){
		init_set();
		ans=0;
		while(m--){
			int a,b,v;
			cin>>a>>b>>v;
			a--;
			merge_set(a,b,v);
		}
		cout<<ans;
	}
}
```