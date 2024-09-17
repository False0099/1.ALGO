题目描述

> 大渣好，我四渣渣辉，点一下，玩一年，装备不花一分钱，说话战斗，罩杯回收，找一基友，极限到手。
> 
> 0 元 VIP，3 天满级，一秒一刀 999，装备全爆 666，广告做得再牛，不如进服遛一遛！
> 
> 古天乐绿了，古天乐绿了，惊喜不断，月入上万！不花钱还赚钱的绿色游戏，等级能提现，装备换点钱！

《贪玩蓝月》是目前最火爆的网页游戏。在游戏中每个角色都有若干装备，每件装备有一个特征值 w 和一个战斗力 v 。在每种特定的情况下，你都要选出特征值的和对 p 取模后在一段范围内的装备，而角色死亡时自己的装备会爆掉。每个角色的物品槽可以看成一个双端队列，得到的装备会被放在两端，自己的装备爆掉也会在两端被爆。

现在我们有若干种事件和询问，如下所示：

- `IF w v`：在前端加入一件特征值为 w 战斗力为 v 的装备
- `IG w v`：在后端加入一件特征值为 w 战斗力为 v 的装备
- `DF`：删除最前端的装备
- `DG`：删除最后端的装备
- `QU l r`：在当前的装备中选取若干装备，他们的和对 p 取模后在$[l, r]$ 中，使得这些装备的战斗力之和最大

为了锻炼你的水平，请尽量使用在线做法。

## 输入格式

第一行一个整数表示测试点编号。

第二行两个整数 m 和 p，分别表示操作数和模数。

接下来每一行一个操作，如题目描述中所述，有五种操作，在前后加或删一件物品或者询问。

输出格式

对于每个询问，输出一行，表示在当前装备中选取若干装备和对 p 取模后在 [l, r] 的装备，使得这些装备战斗力之和最大。如果没有合法方案，输出 -1。

## 样例

输入

```
0
11 10
QU 0 0
QU 1 9
IG 14 7
IF 3 5
QU 0 9
IG 1 8
DF
QU 0 4
IF 1 2
DG
QU 2 9
```

## 输出

```
0
-1
12
8
9
```

一开始没有物品，那么可以不选，特征值价值为 0，不可能凑出非 0 的特征值。

然后在后面加了一个特征值 14 价值 7 的装备，又在前面加了一个特征值 3 价值 5 的装备，询问特征值取模后为$[0, 9]$ 的装备，那么全部选择价值为 12。

然后在后面加了一个特征值为 1 价值为 8 的装备，删除了最前面的装备（特征值 3 价值 5），询问特征值取模后为 $[0, 4]$ 的装备，那么只选择特征值为 1 价值为 8 的装备，最大价值为 8。

最后又在前面加了一个特征值为 1 价值为 2 的装备，删除了最后面的装备（特征值 1 价值 8），询问特征值取模后为 $[2, 9]$的装备，那么选择当前剩余的两件装备，价值和为 9。

## 数据范围与提示

|测试点编号|m|p|特殊情况|
|---|---|---|---|
|1|$\leq$ 10|||
|2|$\leq$ 20|
|3|$\leq$ 100|
|4|$\leq$ 200|
|5|$\leq$ 3000|\leq 10|
|6||保证询问中有 l = r|
|7||
|8||= 2|
|9|$\leq$ 3|
|10|$\leq$ 5|
|11|$\leq$ 10|
|12||只有 `IF`，`IG` 操作和询问|
|13|只有 `IG`，`DG` 操作和询问|
|14|
|15|只有 `IG`，`DG` 操作和询问，且保证询问中有 l = r|
|16|保证询问中有 l = r|
|17|只有 `IG`，`DF` 操作和询问|
|18|
|19|$\leq$ 25000||
|20||

对于所有数据， m $\leq$ 50000, p $\leq$ 500, 0 $\leq$ w, v < 10^9，保证没有物品时不会进行删除操作。

## 题解 
我们本题存在一种江湖上叫做 baka's trick 的做法，**开两个栈，记录前面插入和后面插入**，用背包算出我们的答案。

询问我们可以用 ST 表合并两个栈。

删除我们可以用我们的栈直接弹出就实现了。但如果其中一个栈删完了，我们将取出另一个栈的一般放到右侧重新计算。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=50005;
typedef long long LL;
int n,MOD,Top[2],lg2[505];LL F[2][MAXN][505],S[505][11],INF;
struct xcw{int w,v;}Stk[2][MAXN];
#include<cctype>
void Insert(int a,int x,xcw c){
	Stk[a][x]=c;
	for(int j=0;j<MOD;j++) F[a][x][j]=F[a][x-1][j];
	for(int j=0,i;j<MOD;j++) i=(j+c.w>=MOD?j+c.w-MOD:j+c.w),F[a][x][i]=max(F[a][x][i],F[a][x-1][j]+c.v);
}
void Delete(int a){
	if(Top[a]){Top[a]--;return;}int END=(Top[a^1]+1)>>1;
	for(int i=1,j=END;i<=END;i++,j--) Insert(a,++Top[a],Stk[a^1][j]),Stk[a^1][j]=Stk[a^1][j+END];
	Top[a^1]-=END;Top[a]=END-1;
	for(int i=1;i<=Top[a^1];i++){xcw x=Stk[a^1][i];Insert(a^1,i,x);}
}
LL Ask(int L,int R){int K=lg2[R-L+1];return max(S[L][K],S[R-(1<<K)+1][K]);}
void Query(){
	int L=read(),R=read();LL Ans=INF;
	for(int i=0;i<MOD;i++) S[i][0]=F[1][Top[1]][i];
	for(int j=1;j<=lg2[MOD];j++) for(int i=0;i+(1<<j)-1<MOD;i++) S[i][j]=max(S[i][j-1],S[i+(1<<j-1)][j-1]);//维护区间的最大公约数
	for(int i=0;i<MOD;i++)
	if(F[0][Top[0]][i]>=0){
		int l=L-i,r=R-i;if(l<0) l+=MOD;if(r<0) r+=MOD;
		if(l<=r) Ans=max(Ans,F[0][Top[0]][i]+Ask(l,r));else Ans=max(Ans,F[0][Top[0]][i]+max(Ask(0,r),Ask(l,MOD-1)));
	}
	printf("%lld\n",Ans<0?-1:Ans);
}
int main(){
	read();n=read(),MOD=read();
	for(int i=2;i<=MOD;i++) lg2[i]=lg2[i>>1]+1;
	memset(F,192,sizeof(F)),INF=F[0][0][0],F[0][0][0]=F[1][0][0]=0;
	for(int i=1;i<=n;i++){
		char ch[10];scanf("%s",ch);
		if(ch[0]=='I') Insert(ch[1]=='G',++Top[ch[1]=='G'],(xcw){read()%MOD,read()});else
		if(ch[0]=='D') Delete(ch[1]=='G');else Query();
	}
	return 0;
} 

```