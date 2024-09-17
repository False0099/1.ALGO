这天，称帝的 tgy 心血来潮，翻了翻族谱，发现自己竟然没有母亲（悲  
气急败坏的tgy继续翻族谱，t氏家族在新大陆四处开花，广泛地分布在新大陆的各个村庄中。经过tgy的整治，新大陆共有n个村庄和n-1条道路，任意两个村庄之间都存在唯一的简单路径（“简单”意味着沿着任意路径向前走，不会两次经过同一个村庄）  
为了消气，tgy决定折磨他的手下，不断地向他们询问两个村庄之间的路程

## Input

输入的第一行是一个整数 t，表示有 t 组数据（t<=10）每组数据第一行是 n,m 两个数字(2 <= n <= 40000, 1 <= m <= 200)，分别表示新大陆中村庄的个数，和 tgy 的询问次数，村庄从1到 n 标记  
之后第2行到第n行，每行三个整数a,b,c表示，村庄a与村庄b之间有一条距离为c的小路。（ 0 < c <=40000）  
第n+1行到第n+m行，每行两个整数：L和R，代表一次tgy的询问，也就是询问从村庄L走到村庄R所走的路程为多少。

## Output

对于每组测试数据输出m行，每行一个整数，代表从询问的L村到R村需要走的路程

## Sample Input

2
3 2
1 2 10
3 1 15
1 2
2 3

2 2
1 2 100
1 2
2 1

## Sample Output

10
25
100
100

t<=10  
2<=n<=40000  
1<=m<=200  
1<=a<=n  
1<=b<=n  
1<=c<=40000  
1<=L<=n  
1<=R<=n

## 题解
我们这一题是标准的树上 LCA 模板，我们套一下就行

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>//使用log函数
using namespace std;
const int maxn=40005;
int n,m,k,F[maxn][20];//n个结点，m个查询，F(i,j)表示i向上走2^j步的结点 
int head[maxn],dist[maxn],d[maxn],cnt;//头结点，距离，深度数组 
//边带权的数据结构 
struct Edge{   
	int to,c,next;
}e[maxn<<1];
//使用邻接表，加一条边 
void add(int u,int v,int w){
	e[++cnt].to=v;
	e[cnt].c=w;
	e[cnt].next=head[u];
	head[u]=cnt;
}//e[]用来存一条边，e[].to存边的结束点
void dfs(int u){//求深度、距离、初始化F[v][0]
    for(int i=head[u];i;i=e[i].next){
        int v=e[i].to;
        if(v==F[u][0])
			continue;
        d[v]=d[u]+1;//深度 
        dist[v]=dist[u]+e[i].c;//距离 
        F[v][0]=u; //F[v][0]存v的父节点
        dfs(v);
    }
}

void ST_create(){//构造ST表 
	for(int j=1;j<=k;j++)
		for(int i=1;i<=n;i++)//i先走2^(j-1)步到达F[i][j-1],再走2^(j-1)步
			F[i][j]=F[F[i][j-1]][j-1];
}

int LCA_st_query(int x,int y){//求区间x,y的最近公共祖先 
	if(d[x]>d[y])//保证x的深度小于等于y 
		swap(x,y);
	for(int i=k;i>=0;i--)//y向上走到与x同一深度 
		if(d[F[y][i]]>=d[x])
			y=F[y][i];
	if(x==y)
		return x;
	for(int i=k;i>=0;i--)//x,y一起向上走
		if(F[x][i]!=F[y][i])
			x=F[x][i],y=F[y][i];
	return F[x][0];//返回x的父亲 
}

int main(){
	int x,y,T,lca;
	cin>>T;
	while(T--){
		cin>>n>>m;
		k=log2(n);//log(n)/log(2);
		for(int i=1;i<=n;i++)//初始化 
			head[i]=d[i]=dist[i]=0;
		cnt=0;
		for(int i=1;i<n;i++){//输入一棵树的n-1边
			int x,y,z;
			cin>>x>>y>>z;
			add(x,y,z);
			add(y,x,z);
		}
		d[1]=1;
		dfs(1);
		ST_create();//创建ST表
		for(int i=1;i<=m;i++){
			cin>>x>>y;
			lca=LCA_st_query(x,y);
			cout<<dist[x]+dist[y]-2*dist[lca]<<endl;//输出x y的距离 
		}	
	}
	return 0;
}

```


