那么问题来了，假定天空是一个平面，每个星星都有一个坐标(x,y)，每颗星星都有一个等级从1到100不等，代表它的亮度，其中100是最亮的，1是最弱的。窗户是长方形的，有固定的长和宽，边平行于 x 轴和 y 轴。你的任务是告诉我如何摆放窗户，才能获得在窗口内所有星星的亮度总和最大值。注意，边框的星星不算。窗口可以被平移，但不允许旋转。

Input

在输入中有几个测试用例。每一行的第一行包含3个整数：n，w，h，表示星形的数目，矩形窗口的水平长度和垂直高度。然后N行如下，有3个整数分别为：X，Y，C，表示星星位置（x，y）和每个恒星的亮度。没有两颗星星在同一点上。  
天空中至少有1颗，最多有10000颗星星。1 <= W，h <= 1000000，0 <= x，y < 2^31。

Output

对于每个测试用例，在一行中输出最大亮度。

Sample Input

3 5 4  
1 2 3  
2 3 2  
6 3 1  
3 5 4  
1 2 3  
2 3 2  
5 3 1

Sample Output

5  
6

## 题解
题意不再过多赘述，首先我们思考一个问题，就是在什么条件下星星才会出现在窗户中。

设某颗星星的坐标为 (x,y) ，则当窗户的右上角端点的坐标出现在 )(x∼x+w−1,y∼y+h−1) 这个范围内时，星星就会出现在窗户里。

如下图：

![星星1](https://cdn.luogu.com.cn/upload/image_hosting/koqij4kr.png)

因为题目中说出现在窗户边框的星星不算，我们不妨将边框长宽都减小 0.50.5 ，所以边界坐标要 −1−1 ，即 (�+�−1,�+ℎ−1)(x+w−1,y+h−1) 。

于是我们可以将每个星星都扩展成一个矩形，这时我们注意到，若两个矩形之间有交集，他们便可以放在同一个窗户中。

如下图：

![星星2](https://cdn.luogu.com.cn/upload/image_hosting/p295zpbp.png)

图中灰色的部分就是两个星星构成的矩形的交集，只要窗户的右上角端点在灰色区域内，就能同时框住两个星星。

此时我们可以将问题转化为：平面上有若干个矩形，每个矩形都带有一个权值，求在**哪个坐标上权值的总和最大**。我们就可以**固定我们的 x 值，然后我们取找我们 y 的最大值为多少，就是我们的答案**

接下来我们就可以使用扫描线来解决这个问题了，若当前星星的亮度值为 l ,则矩形的入边的权值设为 l ，出边为 −l ，此时我们只要求扫描线上的区间最大值即可得出答案，区间查询可以使用 lazy_tag 的方式实现。

**代码实现上的一些小细节：**

- 在对 x 坐标进行升序排序时，将 val 值按降序排序，这样才能处理两个矩形贴合的情况。
- 观察到 0≤xi​,yi​≤231 所以我们需要将坐标进行离散化处理。

既然你能找到这题，我相信你能瞬间做出来的。

`Code:`

```cpp
#include<bits/stdc++.h>
typedef long long LL;
typedef long double LD;
using namespace std;//你在看我的代码对吧 
const LL N=100010;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
LL T,n,w,h,C[N];
struct Segment{
	LL l,r,h;
	LL val;
	bool operator <(const Segment &a)const{
		return (h!=a.h)?h<a.h:val>a.val;
	}
}Seg[N<<2];
struct SegmentTree{
	LL l,r;
	LL mx,add;
	#define l(x) tree[x].l
	#define r(x) tree[x].r
	#define mx(x) tree[x].mx
	#define add(x) tree[x].add
}tree[N<<2];
void init(){
	memset(Seg,0,sizeof(Seg));
	memset(tree,0,sizeof(tree));
}
void Pushup(LL x){
	mx(x)=max(mx(x<<1),mx(x<<1|1));
}
void Build(LL x,LL l,LL r){
	l(x)=l,r(x)=r,mx(x)=add(x)=0;
	if(l==r)return;
	LL mid=(l+r)>>1;
	Build(x<<1,l,mid);
	Build(x<<1|1,mid+1,r);
}
void Pushdown(LL x){
	mx(x<<1)+=add(x);
	mx(x<<1|1)+=add(x);
	add(x<<1)+=add(x);
	add(x<<1|1)+=add(x);
	add(x)=0;
}
void Change(LL x,LL L,LL R,LL d){
	LL l=l(x),r=r(x);
	if(L<=l&&r<=R){
		mx(x)+=d;
		add(x)+=d;
		return;
	}
	Pushdown(x);
	LL mid=(l+r)>>1;
	if(L<=mid)Change(x<<1,L,R,d);
	if(R>mid)Change(x<<1|1,L,R,d);
	Pushup(x);
}
int main(){
	scanf("%lld",&T);
	while(T--){
		init();
		scanf("%lld%lld%lld",&n,&w,&h);
		for(LL i=1;i<=n;i++){
			LL x,y,l;
			scanf("%lld%lld%lld",&x,&y,&l);
			C[(i<<1)-1]=y;
			C[i<<1]=y+h-1;
			Seg[(i<<1)-1]=(Segment){y,y+h-1,x,l};
			Seg[i<<1]=(Segment){y,y+h-1,x+w-1,-l};
		}
		n<<=1;
		sort(C+1,C+n+1);
		sort(Seg+1,Seg+n+1);
		LL cnt=unique(C+1,C+n+1)-C-1;
		for(LL i=1;i<=n;i++){
			LL pos1=lower_bound(C+1,C+cnt+1,Seg[i].l)-C;
			LL pos2=lower_bound(C+1,C+cnt+1,Seg[i].r)-C;
			Seg[i].l=pos1;
			Seg[i].r=pos2;
		}
		Build(1,1,cnt);
		LL ans=0;
		for(LL i=1;i<=n;i++){//枚举我们的x的范围
			Change(1,Seg[i].l,Seg[i].r,Seg[i].val);
			ans=max(ans,mx(1));
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```