# Alyona and towers

## 题面翻译

现在有 $n$ 个数，$m$ 个操作，**每次区间加一个数**，对于**每一次**操作，你要找出**最长**的$\ a_l... A_r\ $，满足

$$\exists k\! \in\![l,r],a_l<a_{l+1}<a_{l+2}<...<a_k>a_{k+1}>a_{k+2}>...>a_r$$

输出其长度。

输入：

第一行一个整数 $n$，表示数的个数。

第二行 $n$ 个整数 $a_i$。

第三行一个整数 $m$，表示操作个数。

下面 $m$ 行，每行 $3$ 个整数，$l_i,r_i,d_i$，表示将 $l_i$ 到 $r_i$ 的数字加 $d_i$。

输出：

对于**每个**操作，输出操作完后的答案 (见题意)。

样例解释：

1. 5 5 5 5 5 $\to$ 7 7 7 5 5 ，最长的是 7 5，长度为 2

2. 7 7 7 5 5 $\to$ 7 8 7 5 5 ，最长的是 7 8 7 5 ，长度为 4

3. 7 8 7 5 5 $\to$ 7 8 7 6 5 ，最长的是 7 8 7 6 5 ，长度为 5

## 题目描述

Alyona has built $ n $ towers by putting small cubes some on the top of others. Each cube has size $ 1×1×1 $ . A tower is a non-zero amount of cubes standing on the top of each other. The towers are next to each other, forming a row.

Sometimes Alyona chooses some segment towers, and put on the top of each tower several cubes. Formally, Alyouna chooses some segment of towers from $ l_{i} $ to $ r_{i} $ and adds $ d_{i} $ cubes on the top of them.

Let the sequence $ a_{1}, a_{2},..., a_{n} $ be the heights of the towers from left to right. Let's call as a segment of towers $ a_{l}, a_{l+1},..., a_{r} $ a hill if the following condition holds: there is integer $ k $ ( $ l<=k<=r $ ) such that $ a_{l}&lt; a_{l+1}&lt; a_{l+2}&lt;...&lt; a_{k}&gt; a_{k+1}&gt; a_{k+2}&gt;...&gt; a_{r} $ .

After each addition of $ d_{i} $ cubes on the top of the towers from $ l_{i} $ to $ r_{i} $ , Alyona wants to know the maximum width among all hills. The width of a hill is the number of towers in it.

## 输入格式

The first line contain single integer $ n $ ( $ 1<=n<=3·10^{5} $ ) — the number of towers.

The second line contain $ n $ integers $ a_{1}, a_{2},..., a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — the number of cubes in each tower.

The third line contain single integer $ m $ ( $ 1<=m<=3·10^{5} $ ) — the number of additions.

The next $ m $ lines contain $ 3 $ integers each. The $ i $ -th of these lines contains integers $ l_{i} $ , $ r_{i} $ and $ d_{i} $ ( $ 1<=l<=r<=n $ , $ 1<=d_{i}<=10^{9} $ ), that mean that Alyona puts $ d_{i} $ cubes on the tio of each of the towers from $ l_{i} $ to $ r_{i} $ .

## 输出格式

Print $ m $ lines. In $ i $ -th line print the maximum width of the hills after the $ i $ -th addition.

## 样例 #1

### 样例输入 #1

```
5
5 5 5 5 5
3
1 3 2
2 2 1
4 4 1
```

### 样例输出 #1

```
2
4
5
```

## 提示

The first sample is as follows:

After addition of $ 2 $ cubes on the top of each towers from the first to the third, the number of cubes in the towers become equal to $ [7,7,7,5,5] $ . The hill with maximum width is $ [7,5] $ , thus the maximum width is $ 2 $ .

After addition of $ 1 $ cube on the second tower, the number of cubes in the towers become equal to $ [7,8,7,5,5] $ . The hill with maximum width is now $ [7,8,7,5] $ , thus the maximum width is $ 4 $ .

After addition of $ 1 $ cube on the fourth tower, the number of cubes in the towers become equal to $ [7,8,7,6,5] $ . The hill with maximum width is now $ [7,8,7,6,5] $ , thus the maximum width is $ 5 $ .

## 题解
我们首先发现，我们的单峰字段不好维护，于是，我们需要对我们的单峰字段进行分类。
![[Pasted image 20240201110814.png]]
我们以我们的中间线为我们的左右儿子分界线来计算上述跨区间的类型。

于是，我们就需要求出：
1. 左单峰
2. 左单增
3. 右单减
4. 右单峰

四种形态，然后就能求出我们的答案。为了维护这些，我们还需要进行下面的操作：
1. 维护我们的左右端点的值

总结一下，我们的线段树中现在就有下面的几个标记：
1. 左右端点的值
2. 以左端点开始的最长单调减字段
3. 以右端点结束的最长单增子段
4. 以左端点开始的最长单峰
5. 以右端点结束的最长单峰
6. 区间最长单峰区间

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;

typedef long long LL;

const int N = 300010;

int n, p, m;
int w[N];
struct Node
{
    int l, r;
    int lazy;
    //int sum, add, mul;
    int lnum;//区间左端点数值 
    int rnum;//区间右端点数值 
    int radd;//以右端点为终点的最大上升区间 
	int ldivide;//区间以左端点为起点的最长单调减区间 
	int rcurl;//区间以右端点为终点的最大折现 
	int lcurl;//区间以左端点为起点的最大折现 
	int ans; 
}tr[N * 4];

void pushup(int u)
{
	tr[u].lnum=tr[u<<1].lnum;
	tr[u].rnum=tr[u<<1|1].rnum;
	tr[u].radd=tr[u<<1|1].radd;
	tr[u].lcurl=tr[u<<1].lcurl;
	tr[u].rcurl=tr[u<<1|1].rcurl;
	tr[u].ldivide=tr[u<<1].ldivide; 
	tr[u].ans=max(tr[u<<1].ans,tr[u<<1|1].ans);
	if(tr[u<<1].rnum<tr[u<<1|1].lnum){
		if(tr[u<<1].radd==tr[u<<1].r-tr[u<<1].l+1){
			tr[u].lcurl=tr[u<<1].radd+tr[u<<1|1].ldivide; 
		}
		if(tr[u<<1|1].ldivide==tr[u<<1|1].r-tr[u<<1|1].l+1){
			tr[u].rcurl=tr[u<<1].radd+tr[u<<1|1].ldivide;
		}

		if(tr[u<<1|1].radd==tr[u<<1|1].r-tr[u<<1|1].l+1){
			tr[u].radd=tr[u<<1].radd+tr[u<<1|1].radd;
		}
		if(tr[u<<1|1].lcurl==tr[u<<1|1].r-tr[u<<1|1].l+1){
			tr[u].rcurl=tr[u<<1].radd+tr[u<<1|1].lcurl;
		}
		if(tr[u<<1].radd==tr[u<<1].r-tr[u<<1].l+1){
			tr[u].lcurl=tr[u<<1].radd+tr[u<<1|1].lcurl;
		}
		tr[u].ans=max(tr[u].ans,tr[u<<1].radd+tr[u<<1|1].ldivide);
		//tr[u].ans=max(tr[i].ans,tr[u<<1].radd+tr[u<<1|1].ldivide);
		tr[u].ans=max(tr[u].ans,tr[u<<1].radd+tr[u<<1|1].lcurl);
	}
	if(tr[u<<1].rnum>tr[u<<1|1].lnum){
		if(tr[u<<1].radd==tr[u<<1].r-tr[u<<1].l+1){
			tr[u].lcurl=tr[u<<1].radd+tr[u<<1|1].ldivide; 
		}
		if(tr[u<<1|1].ldivide==tr[u<<1|1].r-tr[u<<1|1].l+1){
			tr[u].rcurl=tr[u<<1].radd+tr[u<<1|1].ldivide;
		}
		if(tr[u<<1].ldivide==tr[u<<1].r-tr[u<<1].l+1){
			tr[u].ldivide=tr[u<<1].ldivide+tr[u<<1|1].ldivide; 
		}
		if(tr[u<<1].rcurl==tr[u<<1].r-tr[u<<1].l+1){
			tr[u].lcurl=tr[u<<1].rcurl+tr[u<<1|1].ldivide;
		}
		if(tr[u<<1|1].ldivide==tr[u<<1|1].r-tr[u<<1|1].l+1){
			tr[u].rcurl=tr[u<<1].rcurl+tr[u<<1|1].ldivide;
		}
		tr[u].ans=max(tr[u].ans,tr[u<<1].rcurl+tr[u<<1|1].ldivide);
		tr[u].ans=max(tr[u].ans,tr[u<<1].radd+tr[u<<1|1].ldivide);
		
	}
	//tr[u].ans=max(tr[u<<1].ans,tr[u<<1|1].ans);
	//tr[u].ans=max(tr[u].lcurl,tr[u].ans);
	//tr[u].ans=max(tr[u].rcurl,tr[u].ans);
}

void pushdown(int u)
{
	tr[u<<1].lnum+=tr[u].lazy;
	tr[u<<1].lazy+=tr[u].lazy;
	tr[u<<1].rnum+=tr[u].lazy;
	tr[u<<1|1].lnum+=tr[u].lazy;
	tr[u<<1|1].rnum+=tr[u].lazy;
	tr[u<<1|1].lazy+=tr[u].lazy;
	tr[u].lazy=0;
}

void build(int u, int l, int r)
{
    if (l == r) {
    	tr[u].l=l;
    	tr[u].r=r;
    	tr[u].ans=1;
    	tr[u].lazy=0;
    	tr[u].ldivide=1;
    	tr[u].lcurl=1;
    	tr[u].lnum=w[l];
    	tr[u].radd=1;
    	tr[u].rcurl=1;
    	tr[u].rnum=w[l];
    	tr[u].lazy=1;
	}
    else
    {
    	tr[u].l=l;
    	tr[u].r=r;
    	tr[u].lazy=0;
        //tr[u] = {l, r, 0, 0, 1};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void modify(int u, int l, int r, int add)
{
    if (tr[u].l >= l && tr[u].r <= r){
    	tr[u].lnum+=add;
    	tr[u].rnum+=add;
    	tr[u].lazy+=add;
    	return;
	} 
    else
    {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, add);
        if (r > mid) modify(u << 1 | 1, l, r, add);
        pushup(u);
    }
}

signed main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i ++ ) scanf("%lld", &w[i]);
    build(1, 1, n);

    scanf("%lld", &m);
    while (m -- )
    {
        int l, r; LL d;
        scanf("%lld%lld%lld", &l, &r, &d);
        modify(1,l,r,d);
        printf("%lld\n", tr[1].ans);
        //cout<<tr[1].ans<<endl;
    }

    return 0;
}
```