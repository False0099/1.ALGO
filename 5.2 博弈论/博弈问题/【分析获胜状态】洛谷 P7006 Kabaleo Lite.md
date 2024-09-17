
# [NEERC2013] Kabaleo Lite
## 题意翻译
有一种棋盘游戏：棋盘上有 $n$ 个格子，每个格子上可以堆叠若干个有颜色的筹码，只有每个格子中最上方的筹码的颜色是可见的。

参加游戏的每个玩家都有各自不同的一个目标颜色，以及一些彩色筹码。每个人只知道自己的目标颜色，但各自拥有的筹码颜色和数量都是公开的。每个回合中，所有玩家轮流在棋盘上选一个格子放置筹码，同时覆盖下方的筹码。游戏结束后，数出棋盘上可见筹码数最多的颜色，以该颜色为目标颜色的玩家即获胜。若该颜色不是任何玩家的目标颜色，或者棋盘上出现最多的颜色不唯一，则游戏平局。

现在，一局游戏进行到了最后，你和其他所有玩家都只剩最后一个筹码。现在恰好轮到你操作，在不知道其他人的目标颜色的前提下，你想知道你一共有哪些操作可以保证必胜。

### 输入格式

第一行 $4$ 个整数 $n,p,c,h$，分别表示棋盘格数、玩家数、筹码颜色总数和你的目标颜色；

第二行 $n$ 个整数 $b_i$，表示棋盘上现有的筹码颜色，棋盘格编号从 $1$ 开始；

第三行 $p$ 个整数 $l_i$，表示每个玩家的最后一枚筹码的颜色，玩家编号从你开始。

### 输出格式

第一行 $1$ 个整数 $w$，表示你有多少种必胜操作。

第二行 $w$ 个整数 $m_i$，表示你应该把筹码放在哪个格子上。顺序不限。

数据范围见原题。
## 题目描述


Kabaleo Lite is a board game. The board consists of several stacks of conical chips of various colors. Only the color of the top chip of the stack is visible.

Each player has a unique target color and a set of colored chips. The target color is hidden from other players, while the set of chips is visible to them. On his turn, player selects one of his chips and puts it on one of the board stacks, thus recoloring it to the color of the chosen chip.

After the last turn, the number of visible board chips of each color is calculated. The winning color is the color that occurs the maximum times. The player (if any) that has this color as his target color, wins the game. If there is no such player or if there are two or more colors that occur the maximum times, the game ends in a draw.

You are playing your last chip in the Kabaleo Lite game. Other players also have one chip left. You want to determine all possible moves that lead you to winning the game. You do not know the target colors of other players and you cannot predict their moves, so your move must guarantee your victory regardless of moves of your opponents.


## 输入输出格式
#### 输入格式



The first line contains four integers $n , p , c$ and $h$ -- the number of stacks on the board $(1 \le n \le 10^{6}),$ the number of players $(1 \le p \le 10^{6}),$ the number of chips' colors $(p \le c \le 10^{6}),$ and your hidden color $(1 \le h \le c)$ .

The second line contains $n$ integers $b_{i}$ -- the color of the visible board chip for each stack on the board $(1 \le b_{i} \le c)$ .

The third line contains $p$ integers $l_{i}$ -- the color of the last chip for each player $(1 \le l_{i} \le c)$ . The players are numbered from one (you) to $n$ in the order of their turns.


#### 输出格式



The first line must contain $w$ -- the number of winning moves.

The second line must contain $w$ distinct numbers $m_{i}$ -- the numbers of the stacks on which your chip should be put to win. Stacks are numbered starting from $1$ in the order that their visible colors are given in the input file. You can output their numbers in any order on this line.

Remember, that your move should be winning regardless of the moves of all other players.


## 输入输出样例
#### 输入样例 #1
6 3 4 2
2 1 2 3 2 2
2 1 1

#### 输出样例 #1
1
2

## 说明
Time limit: 1 s, Memory limit: 128 MB. 


## 题解
我们本体不难发现，我们最后如果想保证我们必胜，我们就需要满足我们的下面的某一个条件：
1. 我们的颜色不管怎么操作，都是我们的所有颜色中的最多的元素。

那么，我们就可以考虑枚举我们把我们的盘子放在哪一个位置，然后再让我们的其他元素贪心的处理，如果我们是与我们的目标元素相同，那么我们就放在相同颜色上，否则就覆盖我们的对应的颜色。
先考虑每次直接判断每个 $j$ 是否可行。
已经有 $b_j=l_1$,剩下的 $p-1$ 个人进行操作，可以假设这 $p-1$ 个人联合对抗你，然后就有一个显然的策略：

不管 $l_i$ 是否等于 $h_{1}$,总是会优先选择一个等于 $h_{1}$ 的数将其覆盖，然后尽量让某个 $h_{1}$ 的数出现尽可能多。

因此需要考虑 $h_{1}$ 至少有几个：
设原先有 $x$ 个 $h_1,l_i,i\in[2,p]$ 中有 $y$ 个不等于 $h_1$ 的数，则一个显然的下界是 $\max(x-y,0)$。
特别的，当 $l_p=h_1$ 时需要对 1 取 $\max$。记 $h_1$ 至少有$N=\max(x-y,[l_p=h_1])$。然后要考虑其他数最多能出现多少次：对于每个数 $a\neq h_1$,统计出 $a$ 在 $b$ 中的出现次数 $p_a$,以及在 $l_i,i\in[2,p]$ 中的出现次数 $q_a$。显然 $a$ 最后最多出现$M=\max_a\neq h_1(p_a+q_a).$
显然如果 $N>M$ ,则你是必胜的。但如果 $N\leq M$,是否有可能必胜呢？
事实上，当且仅当 $n=1,l_p=h_1$ 此时有 $N=M=1$ 你才是必胜的，否则只要其他人联合起来就一定可以让 $h_1$ 出现 $N$ 次，$a$ 出现 $M$ 次。

```
#include<bits/stdc++.h>
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
using namespace std;
int n,p,c,h;
int b[1111111],cnt[1111111];
int l[1111111];
vector<int>ans;
int mx,mmx,cy;
inline int check(int x)
{	
	if(n==1&&l[p]==h) return 1;
	--cnt[b[x]];
	++cnt[l[1]];
	int del=cnt[h]-cy;
	bool ok=1;
	if(del<=0) ok=0;
	if(cnt[mx]>=del) ok=0;
	if(cnt[mmx]>=del) ok=0;
	if(l[1]!=h&&cnt[l[1]]>=del) ok=0;
	++cnt[b[x]];
	--cnt[l[1]];
	return ok;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin>>n>>p>>c>>h;
	R(i,1,n) cin>>b[i],++cnt[b[i]];
	R(i,1,p) cin>>l[i];
	R(i,2,p) if(l[i]!=h) ++cy,++cnt[l[i]];
	//cout<<cy<<endl;
	R(i,1,c) if(i!=h) 
	{
		if(cnt[i]>cnt[mx]) mmx=mx,mx=i;
		else if(cnt[i]>cnt[mmx]) mmx=i;
	}  
	R(i,1,n) if(check(i)) ans.emplace_back(i);
	cout<<ans.size()<<endl;
	for(int x:ans) cout<<x<<' ';
	cout<<endl;
}

```