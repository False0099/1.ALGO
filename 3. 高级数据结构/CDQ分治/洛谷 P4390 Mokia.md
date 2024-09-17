# [BalkanOI 2007] Mokia 摩基亚

## 题目描述

摩尔瓦多的移动电话公司摩基亚（Mokia）设计出了一种新的用户定位系统。和其他的定位系统一样，它能够迅速回答任何形如 “用户 C 的位置在哪？” 的问题，精确到毫米。但其真正高科技之处在于，它能够回答形如 “给定区域内有多少名用户？” 的问题。

在定位系统中，世界被认为是一个 $w\times w$ 的正方形区域，由 $1\times 1$ 的方格组成。每个方格都有一个坐标 $(x, y)$，$1\leq x,y\leq w$。坐标的编号从 $1$ 开始。对于一个 $4\times 4$ 的正方形，就有 $1\leq x\leq 4$，$1\leq y\leq 4$（如图）：

![](https://cdn.luogu.com.cn/upload/pic/17271.png)

请帮助 Mokia 公司编写一个程序来计算在某个矩形区域内有多少名用户。

## 输入格式

有三种命令，意义如下：

|命令|参数|意义|
|:-:|:-:|:-:|
| $0$ | $w$ |初始化一个全零矩阵。本命令仅开始时出现一次。|
| $1$ | $x\ y\ a$ |向方格 $(x, y)$ 中添加 $a$ 个用户。$a$ 是正整数。|
| $2$ | $x_1\ y_1\ x_2\ y_2$ |查询 $x_1\leq x\leq x_2$，$y_1\leq y\leq y_2$ 所规定的矩形中的用户数量。|
| $3$ |无参数|结束程序。本命令仅结束时出现一次。|

输入共若干行，每行有若干个整数，表示一个命令。

## 输出格式

对所有命令 $2$，输出一个一行整数，即当前询问矩形内的用户数量。

## 样例 #1

### 样例输入 #1

```
0 4
1 2 3 3
2 1 1 3 3
1 2 2 2
2 2 2 3 4
3
```

### 样例输出 #1

```
3
5
```

## 提示

#### 数据规模与约定


对于 $100\%$ 的数据，保证：
- $1\leq w\leq 2\times 10 ^ 6$。
- $1\leq x_1\leq x_2\leq w$，$1\leq y_1\leq y_2\leq w$，$1\leq x,y\leq w$，$0<a\leq 10000$。
- 命令 $1$ 不超过 $160000$ 个。
- 命令 $2$ 不超过 $10000$ 个。

## 题解
本题在静态状态下，就是我们的标准的扫描线算法，求我们矩形内的点数。于是我们就可以用我们的 cdq 分治+扫描线算法，其中扫描线算法是作为我们的归并部分来解决。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
#define N 2000100
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x*f;
}
int s,w,n,opt,id,bit[N],mx;
ll ans[N];
struct Query{//id表示是第几个询问,type指操作类型
	int x,y,type,val,id;//val在修改中表示加上的权值,在询问中表示加上还是减去(1/-1)
}q[N],a[N];
struct Note{//ans还要加上矩形大小*s,所以要记录矩形坐标
	int X1,Y1,X2,Y2;
}qwq[N];
bool cmp2(Query a,Query b){
	return a.x==b.x?a.y<b.y:a.x<b.x;
}
//下面是树状数组基本操作,不说了
inline int lowbit(int x){
	return x&(-x);
}
inline void Add(int x,int d){
	while(x<=mx){
		bit[x]+=d;
		x+=lowbit(x);
	}
} 
inline int Ask(int x){
	int ans=0;
	while(x){
		ans+=bit[x];
		x-=lowbit(x);
	}
	return ans;
}
void CDQ(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	CDQ(l,mid),CDQ(mid+1,r);
	sort(a+l,a+mid+1,cmp2);
	sort(a+mid+1,a+r+1,cmp2);//sort即可,还可以用归排
	int i=mid+1,j=l;
	while(i<=r){
		while(j<=mid&&a[j].x<=a[i].x){//扫描l-mid的修改对mid+1-r的询问的影响
			if(a[j].type==1){
				Add(a[j].y,a[j].val);
			}
			++j;
		}
		if(a[i].type==2){
			ans[a[i].id]+=1LL*a[i].val*Ask(a[i].y);
		}
		++i;
	} 
	for(int i=l;i<j;i++){
		if(a[i].type==1)Add(a[i].y,-a[i].val);//别忘了回溯
	}
}
int main(){
	s=read(),w=read();mx=2000000;
	while(opt=read(),opt^3){
		++n;
		if(opt==1){
			q[n].x=read(),q[n].y=read(),q[n].val=read();
			q[n].type=opt;
		}
		else{
			int X1=read(),Y1=read(),X2=read(),Y2=read();
			++id;
            //拆成四个询问
			q[n].x=X2,q[n].y=Y2;
			q[n].val=1,q[n].id=id,q[n].type=opt;
			++n;
			q[n].x=X1-1,q[n].y=Y2;
			q[n].val=-1,q[n].id=id,q[n].type=opt;
			++n;
			q[n].x=X2,q[n].y=Y1-1;
			q[n].val=-1,q[n].id=id,q[n].type=opt;
			++n;
			q[n].x=X1-1,q[n].y=Y1-1;
			q[n].val=1,q[n].id=id,q[n].type=opt;
			qwq[id].X1=X1,qwq[id].X2=X2,qwq[id].Y1=Y1,qwq[id].Y2=Y2;
		}
	}
	for(int i=1;i<=n;i++){
		a[i]=q[i];//闲的复制一下
	}
	CDQ(1,n);
	for(int i=1;i<=id;i++){
		printf("%lld\n",ans[i]+1LL*(qwq[i].X2-qwq[i].X1+1)*(qwq[i].Y2-qwq[i].Y1+1)*s);
	}
	return 0;//bye bye
}
``` 