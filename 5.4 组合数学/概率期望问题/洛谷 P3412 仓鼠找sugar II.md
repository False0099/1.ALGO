# 仓鼠找 sugar II

## 题目描述

小仓鼠的和他的基（mei）友（zi）sugar 住在地下洞穴中，每个节点的编号为 1~n。地下洞穴是一个树形结构。这一天小仓鼠打算从从他的卧室（a，是任意的）他的基友卧室（b，还是任意的）。（注意，a 有可能等于 b。）然而小仓鼠学 OI 学傻了，不知道怎么怎么样才能最短的走到目的地。于是他只能随便乱走。当他在每一个节点时，等概率到这个点的母亲或者所有孩子节点（例如这个节点有一个母亲节点和两个子节点，那么下一步走到这 3 个节点的概率都是 1/3）。一但走到了他基友的卧室，就会停下。

现在小仓鼠希望知道，他走到目的地时，走的步数的期望。这个期望本来是一个有理数，但是为了避免误差，我们要求对这个有理数取模，%998244353。

下面是“分数”模运算的定义：

B, m 互质


k = a/b (mod m) <=> kb = a (mod m)

这里求 x = 1/17 (mod 2668)


```cpp
<=>
17x = 1 (mod 2668)
<=>
17x = 2668k + 1 （k∈整数）
```
取合适的 k 使得 17|(2668 k+1)
这里刚好 17 | (2668 + 1)

所以 k = 1, x = (2668+1)/17 = 157


当然，当 k = 1 + 17 n 时，

X = (2668 + 17·n·2668 + 1)/17 = 157 + 2668 n

也符合条件（n 任意整数）


但如果限定 2668 > x > 0，x 是唯一的。



小仓鼠那么弱，还要天天被 JOHNKRAM 大爷虐，请你快来救救他吧！

## 输入格式

第一行一个正整数 n，表示这棵树节点的个数。

接下来 n-1 行，每行两个正整数 u 和 v，表示节点 u 到节点 v 之间有一条边。

## 输出格式

一个整数，表示取模后的答案。

## 样例 #1

### 样例输入 #1

```
3
1 2
1 3
```

### 样例输出 #1

```
110916041
```

## 提示

对于 30%的数据 n<=5；

对于 50%的数据 n<=5000；

对于所有数据 n<=100000。


样例解释

期望是 16/9

如果 a 在叶子 b 在根，E 1=1。有 2 种情况。

如果 a 在根，b 在叶子。E 2=1/2+3\*1/4+5\*1/8...=3。有 2 种情况。

如果 a 和 b 都在不同的叶子，E 3=E 2+1。有 2种情况。

如果 a=b，E 4=0，有 3 种情况。

所以期望是 16/9，有理数取模后就是输出。


## 题解
给定一个树，我们在每一个点都随机走动，问我们从 a 走到 b 的期望距离是多少。
对于我们的随机游走，我们的常见思路都是**列出我们从某个点出发走到下一个点的期望步数是多少**，

我们于是先处理出，我们从父亲到每个子节点的期望游走距离，和子节点到父亲的期望游走距离，**这样，我们就相当于把我们的双向边拆分为了两条单向边**。然后考虑怎么样统计答案。
令 $d_u$ 表示结点 $u$ 的度数，$f_u$ 表示 $u\to fa(u)$ 的期望步数，其中 $u\neq$ root, $f_\mathrm{root}$ 没有定义

$$
f_u=\frac{1}{d_u}[1+\sum_{fa(v)=u}(f_v+f_u+1)]
$$

解方程得到

$$
f_u=d_u+\sum_{fa(v)=u}f_v
$$

令 $g_u$ 表示 $fa(u)\to u$ 的期望步数，定义 $g_{\mathrm{root}}=0$ 当 $fa( u) \neq$ root

$$
g_u=\frac{1}{d_{fa(u)}}[1+(1+g_{fa(u)}+g_u)+\sum_{fa(v)=fa(u),v\neq u}(1+f_v+g_u)]
$$

 解方程得到
$$
g_u=d_{fa(u)}+g_{fa(u)}+\sum_{fa(v)=fa(u),v\neq u}f_v=f_{fa(u)}-f_u+g_{fa(u)}
$$




方法一：我们从 $s\to t$ 的期望游走距离位我们从 $s$ 到 $lca$ 的期望游走距离，在加上我们从 $lca\to t$ 的期望游走距离，所以我们只需要枚举我们中间的 $lca$,然后再用树形 dp+乘法原理统计答案即可。

方法二：我们考虑统计每一条边对于我们答案的贡献，枚举某条边 E，其对答案产生的贡献就是在 E 一边的点数 $\times$ E 在另一边的点数。

代码:
```cpp
```cpp
#include<bits/stdc++.h>
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<cstring>
#include<complex>
#include<vector>
#include<cstdio>
#include<string>
#include<bitset>
#include<cmath>
#include<queue>
#include<stack>
#include<map>
#include<set>
#define mp make_pair
#define pb push_back
#define RG register
#define il inline
using namespace std;
typedef unsigned long long ull;
typedef vector<int>VI;
typedef long long ll;
typedef double dd;
const dd eps=1e-10;
const int mod=998244353;
const int N=100010;
const int M=90000;
il ll read(){
	RG ll data=0,w=1;RG char ch=getchar();
	while(ch!='-'&&(ch<'0'||ch>'9'))ch=getchar();
	if(ch=='-')w=-1,ch=getchar();
	while(ch<='9'&&ch>='0')data=data*10+ch-48,ch=getchar();
	return data*w;
}

il ll poww(ll a,ll b){
	RG ll ret=1;
	for(a%=mod;b;b>>=1,a=a*a%mod)if(b&1)ret=ret*a%mod;
	return ret;
}

il void file(){
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
}

int n,rev,head[N],d[N],p[N],nxt[N<<1],to[N<<1],cnt,totd,ans;
il void add(int u,int v){
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
	d[v]++;
}

int sz[N],fa[N];
il void dfs(int u,int f){
	sz[u]=1;fa[u]=f;
	for(RG int i=head[u];i;i=nxt[i]){
		RG int v=to[i];if(v==f)continue;
		dfs(v,u);sz[u]+=sz[v];d[u]+=d[v];
	}
}

int main()
{
	file();
	n=read();rev=poww(1ll*n*n%mod,mod-2);
	for(RG int i=1,u,v;i<n;i++){
		u=read();v=read();
		add(u,v);add(v,u);
	}

	for(RG int i=1;i<=n;i++)totd+=d[i];
	dfs(1,0);//以一号节点为根节点
	
	for(RG int u=1;u<=n;u++)//
		for(RG int i=head[u];i;i=nxt[i]){
			RG int v=to[i];
			if(v==fa[u]){
				ans=(ans+1ll*d[u]*sz[u]%mod*(n-sz[u])%mod)%mod;
			}
			else{
				ans=(ans+1ll*(totd-d[v])*(n-sz[v])%mod*sz[v]%mod)%mod;
			}
		}

	
	printf("%lld\n",1ll*ans*rev%mod);
	return 0;
}
```
```

