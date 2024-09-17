
## 题目描述
序是数学和计算机科学中的一个重要概念。例如，佐恩引理说:“一个每条链都有上界的部分有序集合包含一个极大元素。”顺序在程序的不动点语义推理中也很重要。  
  
这个问题既不涉及佐恩引理也不涉及不动点语义，但确实涉及顺序。  
给定一个形式为x <Y，你要写一个程序打印所有与约束条件一致的变量的顺序。  
  
例如，给定约束条件x <Y和x <变量x, y，和，有两种顺序，它们符合这些约束: x, y 和 x, z。

## 输入格式
输入由一系列约束规范组成。规范由两行组成:一行是变量列表，下一行是约束列表。约束由一对变量给出，其中 x y 表示x < y。  
  
所有变量都是单个字符，小写字母。一个规范中至少有两个变量，不超过20个变量。一个规范中至少有一个约束，不超过50个约束。至少有一个，不超过300个与规范中的约束一致的订单。  
  
输入以 end- file 结束。


## 输出格式

对于每个约束规范，应打印与约束一致的所有订单。顺序按字典（字母）顺序打印，每行一个。  
  
不同约束规范的输出用空行分隔。

## 样例 #1

### 样例输入 #1

```
a b f g
a b b f
v w x y z
v y x v z v w v
```

### 样例输出 #1

```
abfg
abgf
agbf
gabf

wxzvy
wzxvy
xwzvy
xzwvy
zwxvy
zxwvy

```

## 题解
本题有两个点，第一个点在于输入当中我们怎么样才能够把输入转换成一个图，我们只需要设定一个变量表示是否是我们的开头即可。
另外在于怎么输出一个图的所有拓扑排序，我们这是不能够采用bfs的方法，而是需要采用我们的dfs方法。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[25],dir[30][30];
int topo[25],vis[30],indegree[30];
void dfs(int z,int cnt){
	int i;
	topo[cnt]=z;
	if(cnt==n-1){
		for(int i=0;i<n;i++){
			printf("%c",topo[i]+'a');
		}
		puts("");
		return;
	}
	viz[z]=1;
	for(int i=0;i<n;i++){
		if(!vis[a[i]]&&dir[z][a[i]]){
			indegree[a[i]]--;
		}
	}
	for(int i=0;i<n;i++){
		if(!indegree[a[i]]&&!vis[a[i]]){
			dfs(a[i],cnt+1);
		}
	}
	//恢复状态 
	for(int i=0;i<n;i++){
		if(!vis[a[i]]&&dir[z][a[i]]){
			indegree[a[i]]++;
		}
	}
	vis[z]=0;
}
int main(){
	char s[100];
	int len;
	while(gets(s)!=NULL){
		memset(dir,0,sizeof dit);
		memset(vis,0,sizeof vis);
		memset(indegree,0,sizeof indegree);
		len=strlen(s);
		n=0;
		for(int i=0;i<len;i++){
			if(s[i]<='z'&&s[i]>='a'){
				a[n++]=s[i]-'a';
			}
			sort(a,a+n);
			gets(s);
			len=strlen(s);
			int first=1;
			for(int i=0;i<len;i++){
				int st,ed;
				if(first&&s[i]<='z'&&s[i]>='a'){
					first=0;
					st=s[i]-'a';
					continue;
				}
				if(!first&&s[i]<='z'&&s[i]>='a'){
					first=1;
					ed=st[i]-'a';
					dir[st][ed]=1;
					indegree[ed]++;
					continue;
				}
			}
			for(int i=0;i<n;i++){
				if(!degree[a[i]]){
					dfs(a[i],0);
				}
				puts("");
			}
		}
	} 
} 

```