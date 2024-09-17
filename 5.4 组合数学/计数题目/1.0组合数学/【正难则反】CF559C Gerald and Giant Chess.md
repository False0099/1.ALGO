#容斥原理  #消去不合法状态 
# Gerald and Giant Chess

## 题面翻译

给定一个 H * W 的棋盘，棋盘上只有 N 个格子是黑色的，其他格子都是白色的。在棋盘左上角有一个卒，每一步可以向右或者向下移动一格，并且不能移动到黑色格子中。求这个卒从左上角移动到右下角，一共有多少种可能的路线。

## 题目描述

Giant chess is quite common in Geraldion. We will not delve into the rules of the game, we'll just say that the game takes place on an $ h×w $ field, and it is painted in two colors, but not like in chess. Almost all cells of the field are white and only some of them are black. Currently Gerald is finishing a game of giant chess against his friend Pollard. Gerald has almost won, and the only thing he needs to win is to bring the pawn from the upper left corner of the board, where it is now standing, to the lower right corner. Gerald is so confident of victory that he became interested, in how many ways can he win?

The pawn, which Gerald has got left can go in two ways: one cell down or one cell to the right. In addition, it can not go to the black cells, otherwise the Gerald still loses. There are no other pawns or pieces left on the field, so that, according to the rules of giant chess Gerald moves his pawn until the game is over, and Pollard is just watching this process.

## 输入格式

The first line of the input contains three integers: $ h, w, n $ — the sides of the board and the number of black cells ( $ 1<=h, w<=10^{5}, 1<=n<=2000 $ ).

Next $ n $ lines contain the description of black cells. The $ i $ -th of these lines contains numbers $ r_{i}, c_{i} $ ( $ 1<=r_{i}<=h, 1<=c_{i}<=w $ ) — the number of the row and column of the $ i $ -th cell.

It is guaranteed that the upper left and lower right cell are white and all cells in the description are distinct.

## 输出格式

Print a single line — the remainder of the number of ways to move Gerald's pawn from the upper left to the lower right corner modulo $ 10^{9}+7 $ .

## 样例 #1

### 样例输入 #1

```
3 4 2
2 2
2 3
```

### 样例输出 #1

```
2
```

## 样例 #2

### 样例输入 #2

```
100 100 3
15 16
16 15
99 88
```

### 样例输出 #2

```
545732279
```

## 题解
我们本题中白色格子数量巨大，而黑色各自最多只有 2000 个，我们的思路是：我们的答案=总方案数-经过每个黑色格子的方案数.

我们先考虑朴素的计算：即只考虑我们从 $(a_{1},b_{1})\to(a_{2},b_{2})\to(a_{3},b_{3})$ 的路径数，显然，我们可以通过我们的公式求出，就是我们的
$$\begin{pmatrix}x_i+y_i-2\\x_i-1\end{pmatrix}\times\begin{pmatrix}h-x_i+w-y_i\\h-x_i\end{pmatrix}$$
但是我们发现，如果我们对于任意的两个格点之间都采用我们这种方法来进行计数的话，会产生我们的重复计数

例如我们要计算从我们的 $(0,0)\to(h,w)$ 的方案，我们就会去计算我们的 $(0,0)\to(x_{1},y_{1})\to(h,w)$,那么我们的 $(0,0)\to(x_{2},y_{2})\to(h,w)$ 中就会把我们的上面那一条重新计算一遍。

更加广泛的说，如果我们以 $(x_{j},y_{j})$ 作为我们的中间点进行计算时，所有满足 $(x_{i}\leq x_{j}\land y_{i}\leq y_{j})$ 的中间路径都会被我们重复计数一次。而我们被多计算的次数就是我们的 $C_{dx+dy}^{dx}$

如果想要消除这一点，一个方法是运用我们的容斥，枚举我们这个 $n$ 个偏序的组合，这里时间复杂度就会来到我们的指数级别。

另一个方法，是巧妙地根据我们容斥产生的原因去消去我们的容斥，我们不难发现，我们的容斥只会由于我们的前一步已经被包含而产生，而对我们的后续影响是可以通过后续元素的容斥来消除的。

因而，我们的思路就是改变我们前半部分的计算方法：由我们原来的前半部分改成我们的 $dp[j]$ ，这样的话，我们的从 $(0-x_{i})$ 的路径就会被我们少计算。

那么我们就有
$F[i]=C_{x_{i}-1+y_{i}-1}^{x_{i}-1}-\sum_{j=0}^{i-1}F[j]\times C_{x_{i}-x_{j}+y_{i}-y_{j}}^{x_{i}-x_{j}}$
也就是我们从左上角到 $(x_{i},y_{i})$ 不经过其他黑格子 $F[j]$,然后再从 $(x_{j},y_{j})$ 到 $(x_{i},y_{i})$ 随便走，路线书就是一个组合数。

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=3e5+50,mod=1e9+7;
int h,w,n,p[N],inv[N],f[N];
struct node{ int x,y; }a[N];
bool mycmp(node a,node b){ return a.x<b.x||(a.x==b.x&&a.y<b.y); }
int C(int m,int n){ if(m>n) return 0; return (p[n]*inv[n-m]%mod*inv[m])%mod; }
int pow(int a,int b){
	int res=1;
	while(b){ if(b&1) res=(res*a)%mod; b>>=1; a=(a*a)%mod;}
	return res%mod;
}
main(){
	scanf("%lld%lld%lld",&h,&w,&n);
	rep(i,1,n) scanf("%lld%lld",&a[i].x,&a[i].y);
	a[n+1].x=h,a[n+1].y=w;
	sort(a+1,a+n+2,mycmp);
	rep(i,0,N-10) p[i]=(i==0)?1:((p[i-1]*i)%mod),inv[i]=pow(p[i],mod-2);
	rep(i,1,n+1) f[i]=C(a[i].x-1,a[i].x+a[i].y-2);
	rep(i,1,n+1) rep(j,1,i-1){
		if(a[i].x<a[j].x||a[i].y<a[j].y) continue;
		f[i]-=f[j]*C(a[i].x-a[j].x,a[i].x+a[i].y-a[j].x-a[j].y);
		f[i]=(f[i]+mod)%mod;
	}
	printf("%lld\n",(f[n+1]+mod)%mod);
	return 0;
}
```

