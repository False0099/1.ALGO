# [IOI 2011] Race

## 题目描述

给一棵树，每条边有权。求一条简单路径，权值和等于 $k$，且边的数量最小。

## 输入格式

第一行包含两个整数 $n,k$，表示树的大小与要求找到的路径的边权和。

接下来 $n-1$ 行，每行三个整数 $u_i,v_i,w_i$，代表有一条连接 $u_i$ 与 $v_i$，边权为 $w_i$ 的无向边。

**注意：点从 $0$ 开始编号**。

## 输出格式

输出一个整数，表示最小边数量。

如果不存在这样的路径，输出 $-1$。

## 样例 #1

### 样例输入 #1

```
4 3
0 1 1
1 2 2
1 3 4
```

### 样例输出 #1

```
2
```

## 提示

对于 $100\%$ 的数据，保证 $1\leq n\leq 2\times10^5$，$1\leq k,w_i\leq 10^6$，$0\leq u_i,v_i<n$。


## 题解
点分治裸题。

具体说一下做法：当前重心是 r 时，计算所有经过 r 的路径。因为 $k≤106$，我们便可以开个桶，$mine[i]$ 表示从 r 开始的权值和为 i 的所有路中，边数的最小值。

更新答案时，我们用当前子树的所有距离和前面子树的桶。思想应该不难想，就是 $ans=min(ans,cnt[v]+mine[k−dis[v]])$，具体实现可以看代码。

由于没有二分，复杂度似乎是 O(nlogn)？我就说怎么一看比别人快的样子……（开O2总时间2816ms，最大点396ms）

要注意的是求的是一个最小值，不满足可减性，所以不能像洛咕日报上那样把多加的减回去。

然后这题似乎卡栈空间……把递归函数中能不用的变量不用就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200020,maxk=1000100;
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline int read(){
	char ch=getchar();int x=0,f=0;
	while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
int n,k,el,head[maxn],to[maxn*2],w[maxn*2],nxt[maxn*2];
int rt,tot,sz[maxn],son[maxn],mine[maxk],ans=INT_MAX,dis1[maxn],dis2[maxn],dl;
bool vis[maxn];
inline void add(int u,int v,int w_){
	to[++el]=v;w[el]=w_;nxt[el]=head[u];head[u]=el;
}
void getrt(int u,int f){	//求重心
	sz[u]=1;son[u]=0;
	for(int i=head[u];i;i=nxt[i]){
    	//v=to[i]不是必需的，可以去掉
		if(to[i]==f || vis[to[i]]) continue;
		getrt(to[i],u);
		sz[u]+=sz[to[i]];son[u]=max(son[u],sz[to[i]]);
	}
	son[u]=max(son[u],tot-sz[u]);
	if(son[u]<son[rt]) rt=u;
}
void getdis(int u,int f,int d1,int d2){	//dfs将子树的信息记录下来（d1是权值和，d2是边数）
	if(d1>k) return;
	dis1[++dl]=d1;dis2[dl]=d2;
	for(int i=head[u];i;i=nxt[i]){
    	//同上
		if(to[i]==f || vis[to[i]]) continue;
		getdis(to[i],u,d1+w[i],d2+1);
	}
}
void getans(int u){	//计算经过u的路径的答案
	mine[0]=0;dl=0;	//mine[0]是0！因为一个端点是u的路径也要考虑，而且0不会被其它子树记录到
	for(int i=head[u];i;i=nxt[i]){
		if(vis[to[i]]) continue;
		int pdl=dl;	//前面的子树有多少元素
		getdis(to[i],u,w[i],1);	//注意调用时w[i]和1
		FOR(j,pdl+1,dl) ans=min(ans,mine[k-dis1[j]]+dis2[j]);
        //更新答案
		FOR(j,pdl+1,dl) mine[dis1[j]]=min(mine[dis1[j]],dis2[j]);
        //更新桶
	}
	FOR(i,1,dl) mine[dis1[i]]=1e9;
}
void getall(int u){	//点分治主过程
	vis[u]=true;
	getans(u);
	for(int i=head[u];i;i=nxt[i]){
		if(vis[to[i]]) continue;
		tot=sz[to[i]];rt=0;
		getrt(to[i],u);
		getall(rt);
	}
}
int main(){
	n=read();k=read();
	FOR(i,1,n-1){
		int u=read()+1,v=read()+1,w=read();	//编号从0开始
		add(u,v,w);add(v,u,w);
	}
	son[0]=(tot=n)+1;	//son[0]设为INF
	getrt(1,0);
	MEM(mine,0x3f);
	getall(rt);
	printf("%d\n",ans>=n?-1:ans);	//最短长度超过n就是无解
}
```

