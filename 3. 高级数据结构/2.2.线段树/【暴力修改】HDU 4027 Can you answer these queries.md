# [[线段树]] 
## 题目描述
很多邪恶的战列舰在战斗前被安排在一条线上。我们的指挥官决定使用我们的秘密武器来消灭战列舰。每艘战列舰都可以被标记为耐力值。对于我们秘密武器的每次攻击，它都可以降低战列舰连续部分的耐力，使它们的耐力达到其原始耐力值的平方根。在我们的秘密武器的一系列攻击中，指挥官想要评估武器的效果，所以他向你寻求帮助。  
您被要求回答的查询，即战列舰线连续部分的耐久性之和。

请注意，平方根运算应向下舍入为整数。请注意，平方根运算应向下舍入为整数。

## 输入格式
多组样例，到文件末尾停止。

先输入 n 是序列大小 (n<=1e5)。

第二行输入n个数 a1,a2,a3.....an (Σai<=2^63)

下一行 输入一个数 m (1 <= m <= 100000)

接下来m行 每行3个整数，是天幽下达的命令，0 L R或1 L R 具体见题目

注意，L可能大于R，自行交换LR。


## 输出格式
对于每个测试用例，在第一行打印用例编号。然后为每个查询打印一行。请记住在每个测试用例后遵循一个空行。


## 样例 #1

### 样例输入 #1

```
10
1 2 3 4 5 6 7 8 9 10
5
0 1 10
1 1 10
1 1 5
0 5 8
1 4 8

```

### 样例输出 #1

```
Case #1:
19
7
6


```


## 题解
这一题是要求将**区间开根号**，经过计算我们发现，当一段区间内每个都是 1 后，开根的结果就会不变，因此，我们**根据某一段和是否为段长来判断是否需要进行修改，如果不需要修改，我们就直接跳过，否则我们进行暴力的单点修改**

## 代码
```cpp
/*
特殊的区间修改 
*/
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{
	int l;
	int r;
	int v;
	int lazy;
}tr[N<<2];
void pushup(int u){
	tr[u].v=tr[u<<1].v+tr[u<<1|1].v;
}
int w[N];
void build(int u,int l,int r){
	tr[u].l=l;
	tr[u].r=r;
	if(l==r){
		tr[u].v=w[r];
		return;
	}
	int mid=l+r>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	pushup(u);
}
//void pushdown(int u){
//	auto root=tr[u];
//	auto left=tr[u<<1];
//	auto right=tr[u<<1|1];
//	if(root.lazy){
//		left.lazy=root.lazy;
//		right.lazy=root.lazy;
//		left.v+=(left.r-left.l+1)*(root.lazy);
//		right.v+=(right.r-right.l+1)*(root.lazy);
//		root.lazy=0;
//	}
//}
void update(int u,int l,int r){
	if(tr[u].l>=l&&tr[u].r<=r){
		if(tr[u].v<=tr[u].r-tr[u].l+1) return;
	}
	if(tr[u].l==tr[u].r){
		tr[u].v=sqrt(1.0*tr[u].v);
		return;
	}
	int mid=tr[u].l+tr[u].r>>1;
	if(l<=mid){
		update(u<<1,l,r);
	}
	if(r>mid){
		update(u<<1|1,l,r);
	}
	pushup(u);
}
int query(int u,int l,int r){
	if(tr[u].l>=l&&tr[u].r<=r){
		return tr[u].v;
	}
	int mid=tr[u].l+tr[u].r>>1;
	int sum=0; 
	if(l<=mid){
		sum+=query(u<<1,l,r);
	}
	if(r>mid){
		sum+=query(u<<1|1,l,r);
	}
	return sum;
}
int n;
int main(){
	cin>>n;
		for(int i=1;i<=n;i++){
			cin>>w[i];
		}
		build(1,1,n);
		int m;
		cin>>m;
		while(m--){
			int op,l,r;
			cin>>op>>l>>r;
			if(l>r) swap(l,r);
			if(op==0){
				update(1,l,r);
			}
			if(op==1){
				cout<<query(1,l,r)<<endl;
			}
		}
	
}
```