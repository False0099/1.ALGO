# 知识点
  ## [[长期项目/算法/算法知识点/图论/拓扑排序]]
# 题目
 # [USACO 20 FEB]Timeline G

## 题目描述

Bessie 在过去的 $M$ 天内参加了 $N$ 次挤奶。但她已经忘了她每次挤奶是在哪个时候了。

对于第 $i$ 次挤奶，Bessie 记得它不早于第 $S_i$ 天进行。另外，她还有 $C$ 条记忆，每条记忆形如一个三元组 $(a,b,x)$，含义是第 $b$ 次挤奶在第 $a$ 次挤奶结束至少 $x$ 天后进行。

现在请你帮 Bessie 算出在满足所有条件的前提下，每次挤奶的最早日期。

保证 Bessie 的记忆没有错误，这意味着一定存在一种合法的方案，使得：

- 第 $i$ 次挤奶不早于第 $S_i$ 天进行，且不晚于第 $M$ 天进行；
- 所有的记忆都得到满足；

## 输入格式

第一行三个整数 $N,M,C$。保证 $1 \leq N,C \leq 10^5$，$2 \leq M \leq 10^9$。

接下来一行包含 $N$ 个整数 $S_1, S_2 , \ldots, S_n$，保证 $\forall 1 \leq i \leq n$，都满足 $1 \leq S_i \leq M$。

下面 $C$ 行每行三个整数 $a,b,x$，描述一条记忆。保证 $a \neq b$，且 $1 \leq x \leq M$。

## 输出格式

输出 $N$ 行，每行一个整数，第 $i$ 行的数表示第 $i$ 次挤奶的最早日期。

## 样例 #1

### 样例输入 #1

```
4 10 3
1 2 3 4
1 2 5
2 4 2
3 4 4
```

### 样例输出 #1

```
1
6
3
8
```

## 提示

- 测试点 $2 \sim 4$ 满足 $N,C \leq 10^3$。
- 测试点 $5 \sim 10$ 没有特殊限制。

# 思路
·
·
·
# AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const int M=1e5+10;//注意题目里给的范围，防止越界
int din[N];
int h[N],e[M],ne[M],w[M],idx;
bool st[N];
int n;
int s[N];
void add(int a,int b,int c){
	w[idx]=c;
	e[idx]=b;
	ne[idx]=h[a];
	h[a]=idx++;
}
int ans[N];
void topsort(){
	queue<int> q;
	for(int i=1;i<=n;i++){//遍历点，要从1-n
		if(din[i]==0){
			q.push(i);	
		}
	}
	while(q.size()){
		int t=q.front();
		q.pop();
		for(int i=h[t];i!=-1;i=ne[i]){
			int j=e[i];
			s[j]=max(s[j],s[t]+w[i]);//每次都要在最外面更新，保证不会漏情况
			din[j]--;
			if(din[j]==0){
				q.push(j);
						
			}
		}
	}
}
int main(){
	cin>>n;
	int m;
	cin>>m;
	int c;
	cin>>c;
	for(int i=1;i<=n;i++){
		cin>>s[i];
	}
	memset(h,-1,sizeof h);
	for(int i=0;i<c;i++){
		int a,b,c;
		cin>>a>>b>>c;
		add(a,b,c);
		din[b]++;
	}
	topsort(); 
	for(int i=1;i<=n;i++){//一定要从1写到n，因为点的编号是从1开始的
		cout<<s[i]<<endl;
	}
}  
```
# 备注
