```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int read(){
	char s;
	int x=0,f=1;
	s=getchar();
	while(s<'0'||s>'9'){
		if(s=='-')f=-1;
		s=getchar();
	}
	while(s>='0'&&s<='9'){
		x*=10;
		x+=s-'0';
		s=getchar();
	}
	return x*f;
}
struct tree{
	long long sum;
	long long tag;//记录要修改为哪个颜色 
	int l,r;
}t[1600040];
int c[400040];
int tot=0;
int pos[400040];//时间戳所对应的点
int in[400040];//入点时间戳 
int out[400040];//出点时间戳 
struct edge{
	int to,next;
}e[800080];
int eid=0;
int head[400040];
void insert(int u,int v){
	eid++;
	e[eid].to=v;
	e[eid].next=head[u];
	head[u]=eid;
}
void dfs(int x,int fa){//用dfs序将树形结构转为线性结构 
	tot++;
	in[x]=tot;
	pos[tot]=x;
	for(int i=head[x];i+1;i=e[i].next){
		int k=e[i].to;
		if(k==fa)continue;
		dfs(k,x);
	}
	out[x]=tot;//其实我们out记录的是该子树中dfs序最大结点的dfs序，所以tot不加一 
	return;
} 
void pushup(int rt){
	t[rt].sum=t[rt<<1].sum|t[rt<<1|1].sum;
	return;
}
void pushdown(int rt){
	if(t[rt].tag!=0){//或运算不像区间和，这里0是影响答案的 
		t[rt<<1].sum=t[rt].tag;
		t[rt<<1].tag=t[rt].tag;
		t[rt<<1|1].sum=t[rt].tag;
		t[rt<<1|1].tag=t[rt].tag;
		t[rt].tag=0;
	}	
	return;
}
void build(int rt,int l,int r){
	t[rt].l=l;
	t[rt].r=r;
	if(l==r){
		t[rt].sum=(long long)1<<(c[pos[l]]);//
		t[rt].tag=0;
		return;
	}
	int mid=(l+r)>>1;
	build(rt<<1,l,mid);
	build(rt<<1|1,mid+1,r);
	pushup(rt);
	return;
}
void modify(int rt,int l,int r,int p){//将dfs序从l到r这一区间的颜色改为p  注意状压 
	if(t[rt].l>=l&&t[rt].r<=r){
		t[rt].sum=(long long)1<<p;//
		t[rt].tag=(long long)1<<p;//
		return ;
	}
	int mid=(t[rt].l+t[rt].r)>>1;
	pushdown(rt);
	if(l<=mid)modify(rt<<1,l,r,p);
	if(r>mid)modify(rt<<1|1,l,r,p);
	pushup(rt);
	return;
}
long long query(int rt,int l,int r){//查询dfs序从l到r的颜色个数 
	if(t[rt].l>=l&&t[rt].r<=r){
		return t[rt].sum;
	}
	pushdown(rt);
	int mid=(t[rt].l+t[rt].r)>>1;
	long long rec=0;
	if(l<=mid)rec|=query(rt<<1,l,r);
	if(r>mid)rec|=query(rt<<1|1,l,r);
	pushup(rt);
	return rec;
}
int n,m;
long long lowbit(long long x){
	return x&(-x);
}
int main(){
	memset(head,-1,sizeof(head));
	n=read();
	m=read();
	for(int i=1;i<=n;i++){
		c[i]=read();
	}
	for(int i=1;i<n;i++){
		int x,y;
		x=read();
		y=read();
		insert(x,y);
		insert(y,x);
	}
	dfs(1,0);
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int a;
		a=read();
		if(a==1){
			int x,y;
			x=read();
			y=read();
			modify(1,in[x],out[x],y);
			//cout<<query(1,in[x],in[x])<<endl;
		}
		else{
			int x;
			x=read();
			long long num=query(1,in[x],out[x]);
			int ans=0;
			//cout<<num<<endl;
			for(long long j=num;j>0;j-=lowbit(j))ans++;
			cout<<ans<<endl;
		}
	}
	return 0;
}
```