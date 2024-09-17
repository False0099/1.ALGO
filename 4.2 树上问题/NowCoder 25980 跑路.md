# 
## 题目描述


  
n 点树， m 次询问，每次给出参数 d ，选出 l 条一端为根的长度 $\leq d$ 的路径  
使路径并内点数最大，求这个最大值

## 输入格式


第一行两个正整数 n, m  
第二行 n-1 个正整数，其中第 i 个数 $fi$ 表示点 i+1 与 $fi​$ 之间有一条边  
（保证 $1≤fi≤i$）  
第三行一个正整数 l  
第四行 m 个非负整数，为每次询问的参数 d

## 输出格式

m 行，每行一个正整数  
其中第 i 行为第 i 次询问对应的最大点数

## 样例 #1

### 样例输入 #1

```
6 3
1 1 3 3 3
2
0 1 2

```

### 样例输出 #1

```
1
3
4

```

## 提示
首先，我们能贪心的得到，如果我们走的时最大的，那么我们一定要尽量走长链。
对于每一条链的贡献，我们可以把我们的贡献直接记录在我们的
## 题解


## 代码
```cpp
#include <cstdio>
#include <vector>

using std::vector;

const int MAXN=3000011;

inline void relax(int &p, int v){
	if(p<v)	p=v;
}

int N, M, L;
int F[MAXN];
int Dep[MAXN], Md[MAXN];
int Ms[MAXN];
int Ans[MAXN];
vector<int> Add[MAXN];

int Val[MAXN];

int main(){
	
	scanf("%d%d", &N, &M);
	
	for(int i=2;i<=N;++i)	scanf("%d", &F[i]);
	
	scanf("%d", &L);
	
	Dep[1]=1;
	for(int i=2;i<=N;++i)	Dep[i]=Dep[F[i]]+1;
	
	for(int i=1;i<=N;++i)	Md[i]=Dep[i];
	for(int i=N;i>=2;--i)
		relax(Md[F[i]], Md[i]);
	
	for(int i=N, f;i>=2;--i){
		f=F[i];
		if(Md[Ms[f]]<Md[i])	Ms[f]=i;
	}
	
	for(int i=N, f;i>=2;--i){
		f=F[i];
		if(Ms[f]==i)	continue;
		for(int k=Dep[f]+1;k<=Md[i];++k)
			Add[k].push_back(k-Dep[f]);
	}
	
	for(int i=1;i<=Md[1];++i)	Add[i].push_back(i);
	
	for(int i=1;i<=Md[1];++i){
		Ans[i]=Ans[i-1];
		for(int p=0, s=Add[i].size(), k;p<s;++p){
			k=Add[i][p];
			++Val[k];
			if(Val[k]<=L)	++Ans[i];
		}
	}
	
	for(int v;M--;){
		scanf("%d", &v);
		++v;if(v>Md[1])	v=Md[1];
		printf("%d\n", Ans[v]);
	}
	
	return 0;
}

/*
6 3
1 1 3 3 3
2
0
1
2

1
3
4

*/

```