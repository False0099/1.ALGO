## 题目描述
这天，狄大人是有名的名侦探，他也很会判案，他常常会问元芳：”元芳，你怎么看？“：  
现在有n个犯人等待被审判，每个犯人都有一个罪恶值, a1, a2, …, an. 这些犯人的罪恶之最开始都是0， 但是经过狄大人的审判，n个犯人的罪恶值会有不同程度的改变，偷偷告诉你，因为狄大人断案能力很强，所以他每一次判案都是直接审批一个连续区间$[l,r]$的犯人哦。狄大人有三个审判方式。  
第一种审判 1: 这种审判的犯人一般是一些小案件的犯人，狄大人会让受审判的犯人的罪恶值增加c。  
第二种审判 2: 这种犯人一般都是一些 大案件的犯人，狄大人会让受审判的犯人的罪恶值增加 (c-1)×a，其中a是犯人原来的罪恶值。  
第三种审判 3:这种犯人犯的错都是法律种明确规定的，狄大人会让受审判的犯人的罪恶值都变为c。 狄大人在审判犯人之后，会好奇犯人的罪恶值都是多少，因此他会询问一个区间的犯人的罪恶值。  
询问 4: 因为只是罪恶值无法表现出犯人的罪恶程度，因此狄大人想要知道相对罪恶值bk=akp的值,现在狄大人想要知道一些犯人的相对罪恶值。  
但是狄大人实在太忙了，因此他又去问了元芳：”元芳，你怎么看？“，元芳表示：”我坐着看“，元芳也不知道犯人的相对罪恶值，因此就需要聪明又机智的你来帮助狄大人找到犯人的相对罪恶值啦。

## 输入格式
输入有多组数据，数据不超过10组。  
对于每一组数据，对于每一组数据，第一行输入两个数，n 和 m。表示有n个犯人，狄大人会进行m次审判。1 <= n, m <= 100,000.  
接下来输入m行，每一行都包含一次审判的信息，每一行输入一个数 op，表示狄大人的行为. op=1,2,3:表示狄大人将要审判犯人，接下来输入三个数，x y c，表示狄大人审判的犯人的范围在[x,y]之间，并且审判的依据是c。 op=4：表示狄大人想要知道犯人的相对罪恶值，接下来输入三个数，x y p，其中x y表示狄大人想要知道的犯人的范围在[x,y]之间，并且相对罪恶值bk=akp。(1 <= x <= y <= n, 1 <= c <= 10,000, 1 <= p <= 3)  
输入 0 0时终止输入。


## 输出格式

对于狄大人的每次询问，即op=4，在一行种输出询问区间的所有相对罪恶值之和。答案可能很大，你只需要计算答案除以10007的余数。

## 样例 #1

### 样例输入 #1

```
7 7
1 5 6 4
4 5 6 1
1 1 5 2
2 3 4 6
3 3 4 6
1 3 6 3
4 1 6 2
0 0
```

### 样例输出 #1

```
8
300
```

## 提示

样例中，狄大人需要审判n个犯人，m次行为，最开始，所有犯人的罪恶值都为0， 第一次行为之后：每个犯人的罪恶值为：0 0 0 0 4 4 0 第二次行为之后：bk=ak1。所以对于该询问，ans=b4+b5=8. 第三次行为之后：每个犯人的罪恶值为：2 2 2 2 6 4 0 第四次行为之后：每个犯人的罪恶值为：2 2 12 12 6 4 0 第五次行为之后：每个犯人的罪恶值为：2 2 6 6 6 4 0 第六次行为之后：每个犯人的罪恶值为：2 2 9 9 9 7 0 第七次行为之后：bk=ak2。所以对于该询问，ans=b1+b2+b3+b4+b5+b6=300.


## 题解
这一题的难点在于要同时处理三个标记，并且还要注意处理标记的顺序，每一次修改后对其他标记的影响。我们按照先加，再乘，最后修改的方法来进行。

在因为，我们还要求出每个节点的 k 次方，这里，我们把每个节点看成 ax+b, 因为 P 只有 1-3，$(x+c)^2=x^2+2\times  x \times c+c^2$,同理，我们可以把我们的三次方转化为二次方的和的操作。

设我们 1，2，3 的懒操作分别是 add, mult, same, 当三个值同时存在时，add 和 mult 一定是后来到的。所以我们先传递的值一定是 same。对于后面的标记，我们的顺序是先传递 mul，再传递 add，因为当把一个区间标记上 mul 时，如果发现这个区间的 add 不为 0，那么我们就可以把 add 更新成 add * mult.

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
	int l;
	int r;
	int mul;
	int add;
	int change;
	int sum1;
	int sum2;
	int sum3;
}tr[N];
void pushup(int u){
	tr[u].sum1=tr[u<<1].sum1+tr[u<<1|1].sum1;
	tr[u].sum2=tr[u<<1].sum2+tr[u<<1|1].sum2;
	tr[u].sum3=tr[u<<1].sum3+tr[u<<1|1].sum3;
}
void build(int u,int l,int r){
	tr[u].l=l;
	tr[u].r=r; 
	if(l==r){
		tr[u].sum1=w[l];
		tr[u].sum2=w[l]*w[l];
		tr[u].sum3=w[l]*w[l]*w[l];
		return;
	}
	int mid=l+r>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	pushup(u);
}
void pushdown(int u){
	auto root=tr[u];
	auto left=tr[u<<1];
	auto right=tr[u<<1|1];
	if(root.change){
		int c=root.change;
		left.sum=0;
		right.sum=0;
		left.mul=1;
		right.mul=1;
		left.change=c;
		right.change=c;
		//
		left.sum1=c*(left.r-left.l+1);
		right.sum1=c*(right.r-right.l+1);
		//
		left.sum2=c*c*(left.r-left.l+1);
		right.sum2=c*c*(right.r-right.l+1);
		//
		left.sum3=c*c*c*(left.r-left.l+1);
		right.sum3=c*c*c*(right.r-right.l+1);
		//
		root.change=0; 
	}
	if(root.mul!=1){
		int c=root.mul;
		left.mul*=c;
		right.mul*=c;
		if(left.add){
			left.add*=c;
		}
		if(right.add){
			right.add*=c;
		}
		left.sum1*=c;
		right.sum1*=c;
		left.sum2*=c*c;
		right.sum2*=c*c;
		left.sum3*=c*c*c;
		right.sum3*=c*c*c;
		root.mul=1;
	}
	if(root.add){
		int c=root.add;
		left.add+=c;
		right.add+=c;
		left.sum3+=c*c*c*(left.r-left.l+1)+3*c*(left.sum2+left.sum1*c);
		right.sum3+=c*c*c*(right.r-right.l+1)+3*c*(right.sum2+c*right.sum1);
		left.sum2+=c*c+2*left.sum1*c+(left.r-left.l+1)*c*c;
		right.sum2+=c*c+2*right.sum1*c+(right.r-right.l+1)*c*c;
		left.sum1+=c*(left.r-left.l+1);
		right.sum1+=c*(right.r-right.l+1);
		root.add=0;	
	}
}
void update(int u,int l,int r,int c,int op){
	if(tr[u].l>=l&&tr[u].r<=r){
		if(op==1){
			tr[u].change+=c;
			tr[u].sum3+=(c*c*(r-l+1))+(3*c*(tr[u].sum2+tr[u].sum1*c));
			tr[u].sum2+=(c*c*(r-l+1))+(2*tr[u].sum1*c);
			tr[u].sum1+=(r-l+1)*c;
		}else if(op==2){
			tr[u].mul*=c;
			if(tr[u].change){
				tr[u].change*=c;
			}
			tr[u].sum1*=c*;
			tr[u].sum2*=c*c;
			tr[u].sum3*=c*c*c;
		}else if(op==3){
			tr[u].add=c;
			tr[u].change=0;
			tr[u].mul=1;
			tr[u].sum1=(r-1+1)*c;
			tr[u].sum2=(r-l+1)*c*c;
			tr[u].sum3=(r-l+1)*c*c*c;
		}
		return;
	}
	int mid=(l+r)>>1;
	pushdown(u);
	if(l<=mid){
		update(u<<1,l,r,d,op);
	}
	if(r>mid){
		update(u<<1|1,l,r,d,op);
	}
	pushup(u);
}
int query(int u,int l,int r,int node){
	if(tr[u].l>=l&&tr[u].r<=r){
		if(node==1){
			return tr[u].sum1
		}
		if(node==2){
			return tr[u].sum2;
		}
		if(node==3){
			return tr[u].sum3;
		}
	}
	int mid=(l+r)>>1;
	long long ans=0;
	pushdown(u);
	if(l<=mid) ans+=query(u<<1,l,r,node);
	if(r>mid) ans+=query(u<<1|1,l,r,node);
	return ans;
}
int main(){
	int n,m;
	cin>>n>>m;
	build(1,n,1);
	while(m--){
		int op;
		int a,b,c;
		cin>>a>>b>>c;
		if(op==4){
			cout<<query(1,l,r,op);
		}else{
			update(1,l,r,d,op); 
		}
	}
}
```