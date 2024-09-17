## 题目描述
TXT 在机房举行了夏日绘版活动！

为了避免服务器被 WXX 冲击而毁于一旦，她要求每位参加绘制图片的 OIer 遵守以下规则：

- 每人只能绘制一张图片，并且图片的高度等于画布的高度。
- 图片的宽度可以是任意的整数字节。
- 每张图片的形状都是规则的，且完全连续地覆盖画布。
- 在绘版活动中，画布被划分为宽度为一个字节的数段。

根据 OIer 们的需求，TXT 建造了一个足足有 1000000010000000 字节长的画布以确保每个人的图片都能绘制上去。绘版活动开始时，所有人都按顺序在画布上绘制自己的图片，OIer 们的图片在宽度上差异十分大。并且，后画上去的海报会覆盖之前画在同一位置的图片。为了减少运算量，TXT 需要知道，当所有图片绘制完毕后，还有多少张图片可以被看到。

你将从 TXT 口中得知所有的大图片小，所有图片在画布上的位置和绘制的顺序信息。你需要找出所有图片绘制完毕后依然可见的 图片数量。

## 输入格式

输入的第一行包含一个数字 c，表示接下来的案例数量。

每个案例的第一行数据包含一个数字 n，满足 1≤n≤10000。

接下来的 n 行按照放置顺序描述了图片。

在这 n 行中，第 i 行包含两个整数li​ 和ri​，分别表示第 i 张图片左端和右端占据的画布段数。

我们知道，对于每个 1≤i≤n，都有 1≤li​≤ri​≤10000000。在放置第 i 张图片后，它将完全覆盖所有编号为 li​，li​+1，…，ri​ 的画布段。

## 输出格式
对于每个输入数据集，绘制所有图片后，打印可见图片的数量。


## 样例 #1

### 样例输入 #1

```
1
5
1 4
2 6
8 10
3 4
7 10

```

### 样例输出 #1

```
4

```

## 题解
这一题我们通过线段树来维护我们的区间然后染色就行，**贴海报就整个区间染成对应的颜色，最后数一下整个区间有几种颜色就行**。另外，我们添加一个懒标记，**如果懒标记为-1，就表示我们这个区间内啥颜色都没染过，我们就直接跳过就行**。

## 代码
```cpp
/*
线段树区间覆盖 
*/
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{
	int l;
	int r;
	int color;
	int lazy;
}tr[N<<2];
void build(int u,int l,int r){
	tr[u].l=l;
	tr[u].r=r;
	tr[u].color=0;
	tr[u].lazy=-1;
	if(l==r){
		return;
	}
	int mid=l+r>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
}
void pushdown(int u){
	auto left=tr[u<<1];
	auto right=tr[u<<1|1];
	if(tr[u].lazy){
		int c=tr[u].lazy;
		left.lazy=c;
		right.lazy=c;
		left.color=tr[u].color;
		right.color=tr[u].color;
		tr[u].lazy=0;//区间都是一个颜色
	}
}
void change(int u,int l,int r,int x){
	if(l<=tr[u].l&&tr[u].r<=r){
		tr[u].color=x;
		tr[u].lazy=1;
		return;
	}
	pushup(u);
	int mid=tr[u].l+tr[u].r>>1;
	if(l<=mid){
		change(u<<1,l,r,x);
	}
	if(mid<=r){
		change(u<<1|1,l,r,x);
	}
}
void query(int u,int l,int r){
	if(tr[u].lazy==-1){//这个区间全是白色
		return;
	}
	if(tr[u].lazy!=0){//这个区间都是一个颜色
		if(!vis[tr[u].color]&&tr[u].color!=0){
			++ans;
			vis[tr[u].color]=1; 
		}
		return;
	}
	int mid=(l+r)>>1;
	query(u<<1,l,r);
	query(u<<1|1,l,r); 
}
int t;
int n;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		int ans=0;
		memset(vis,0,sizeof vis);
		pos.clear();
		pos.push_back(0);
		for(int i=1;i<=n;i++){
			cin>>l[i]>>r[i];
			pos.push_back(l[i]);
			pos.push_back(r[i]);
			pos.push_back(r[i]+1);
		}
		sort(pos.begin(),pos.end());
		pos.erase(unique(pos.begin(),pos.end()),pos.end());//离散化
		int len=pos.size();
		cnt=0;
		build(1,len,1);
		for(int i=1;i<=n;i++){
			l[i]=getpos(l[i]);
			r[i]=getpos(r[i]);
			change(l[i],r[i],1,++cnt);
		}
		query(1,len,1);、//因为只有一次查询，我们可以直接暴力查询即可
		cout<<ans;
	}
	return 0;
}
```