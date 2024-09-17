# Game with Marbles (Hard Version)

## 题面翻译

$2$ 个 $n$ 长度的数组，如下

$$a_1,a_2,a_3,...,a_n$$

$$b_1,b_2,b_3,...,b_n$$

甲、乙两人轮流选下标 $i$ （甲先选），$i$ 一定需要满足 $a_i\not=0$ 且 $b_i\not=0$。

- 如果是甲所选，他会将 $a_i$ 减一且 $b_i$ 变为 $0$

- 如果是乙所选，他会将 $b_i$ 减一且 $a_i$ 变为 $0$

当没有 $i$ 满足 $a_i\not=0$ 且 $b_i\not=0$ 时，游戏结束。令 $A=\sum_{p=1}^{n}a_p\ , \ B=\sum_{p=1}^{n}b_p$

甲想让 $A-B$ 越大越好，乙想让 $A-B$ 越小越好，如果甲乙足够聪明，那么最后 $A-B$ 的值为多少？

## 题目描述

The easy and hard versions of this problem differ only in the constraints on the number of test cases and $ n $ . In the hard version, the number of test cases does not exceed $ 10^4 $ , and the sum of values of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ . Furthermore, there are no additional constraints on $ n $ in a single test case.

Recently, Alice and Bob were given marbles of $ n $ different colors by their parents. Alice has received $ a_1 $ marbles of color $ 1 $ , $ a_2 $ marbles of color $ 2 $ ,..., $ a_n $ marbles of color $ n $ . Bob has received $ b_1 $ marbles of color $ 1 $ , $ b_2 $ marbles of color $ 2 $ , ..., $ b_n $ marbles of color $ n $ . All $ a_i $ and $ b_i $ are between $ 1 $ and $ 10^9 $ .

After some discussion, Alice and Bob came up with the following game: players take turns, starting with Alice. On their turn, a player chooses a color $ i $ such that both players have at least one marble of that color. The player then discards one marble of color $ i $ , and their opponent discards all marbles of color $ i $ . The game ends when there is no color $ i $ such that both players have at least one marble of that color.

The score in the game is the difference between the number of remaining marbles that Alice has and the number of remaining marbles that Bob has at the end of the game. In other words, the score in the game is equal to $ (A-B) $ , where $ A $ is the number of marbles Alice has and $ B $ is the number of marbles Bob has at the end of the game. Alice wants to maximize the score, while Bob wants to minimize it.

Calculate the score at the end of the game if both players play optimally.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case consists of three lines:

- The first line contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of colors;
- The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ), where $ a_i $ is the number of marbles of the $ i $ -th color that Alice has;
- The third line contains $ n $ integers $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_i \le 10^9 $ ), where $ b_i $ is the number of marbles of the $ i $ -th color that Bob has.

Additional constraint on the input: the sum of $ n $ for all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the score at the end of the game if both Alice and Bob act optimally.

## 样例 #1

### 样例输入 #1

```
5
3
4 2 1
1 2 4
4
1 20 1 20
100 15 10 20
5
1000000000 1000000000 1000000000 1000000000 1000000000
1 1 1 1 1
3
5 6 5
2 1 7
6
3 2 4 2 5 5
9 4 7 9 2 5
```

### 样例输出 #1

```
1
-9
2999999997
8
-6
```

## 提示

In the first example, one way to achieve a score of $ 1 $ is as follows:

1. Alice chooses color $ 1 $ , discards $ 1 $ marble. Bob also discards $ 1 $ marble;
2. Bob chooses color $ 3 $ , discards $ 1 $ marble. Alice also discards $ 1 $ marble;
3. Alice chooses color $ 2 $ , discards $ 1 $ marble, and Bob discards $ 2 $ marble.

As a result, Alice has $ a = [3, 1, 0] $ remaining, and Bob has $ b = [0, 0, 3] $ remaining. The score is $ 3 + 1 - 3 = 1 $ .

It can be shown that neither Alice nor Bob can achieve a better score if both play optimally.

In the second example, Alice can first choose color $ 1 $ , then Bob will choose color $ 4 $ , after which Alice will choose color $ 2 $ , and Bob will choose color $ 3 $ . It can be shown that this is the optimal game.

## 题解
我们本题的思路是：首先我们计算出我们的操作能够对我们的答案的贡献是多少。首先，我们对于每一步策略都考虑一个贡献 $c_i$,那么我们很容易得出贡献计算的方式就为 $a_i+b_i=c_i$ , 其中 $a_i$ 为小 $A$ 的每种类型的弹珠数量，$b_i$ 为小 $B$ 的每种类型的弹珠数量，然后我们只需要将贡献排一下序，容易得出要使策略最优是必定要优先拿贡献大的地方的，因此直接贪心一下就做完了。

/*
Tips:
你数组开小了吗？
你 MLE 了吗？
你觉得是贪心，是不是该想想 dp？
一个小时没调出来，是不是该考虑换题？
```
/*
Tips:
你数组开小了吗？
你MLE了吗？
你觉得是贪心，是不是该想想dp？
一个小时没调出来，是不是该考虑换题？
*/
#include<bits/stdc++.h>
using namespace std;
#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) x&-x
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
long long t,n,ans,L,R;
struct node{
	long long a,b,c;
}a[200010];
bool cmp(node x,node y){
	return x.c<y.c;
}
/*
long long t,n,maxn,minn,a[200010],b[200010],vis[200010];
void dfs(bool pd,long long cs,long long sum)
{
	if(cs==n+1)
	{
		maxn=max(maxn,sum);
		minn=min(minn,sum);
		return ;
	}
	if(!pd)
	{
		forl(i,1,n)
			if(!vis[i])
				vis[i]=1,dfs(pd^1,cs+1,sum+a[i]-1),vis[i]=0;
	}
	else
	{
		forl(i,1,n)
			if(!vis[i])
				vis[i]=1,dfs(pd^1,cs+1,sum-b[i]+1),vis[i]=0;
	}
}
void solve()
{
	maxn=-1e18,minn=1e18;
	cin>>n;
	forl(i,1,n)
		cin>>a[i];
	forl(i,1,n)
		cin>>b[i];
	dfs(0,1,0);
	if(n%2)
		cout<<maxn<<endl;
	else
		cout<<minn<<endl;
}*/
int main()
{
	IOS;
	cin>>t;
	while(t--)
	{
		cin>>n;
		forl(i,1,n)
			cin>>a[i].a;
		forl(i,1,n)
			cin>>a[i].b,a[i].c=a[i].a+a[i].b;
		sort(a+1,a+1+n,cmp);
		ans=0,L=1,R=n;
		forl(i,1,n)
		{
			if(i%2)
			{
				if(abs(a[L].c)<=abs(a[R].c))
					ans+=a[R].a-1,R--;
				else
					ans+=a[L].a-1,L++;
			}
			else
			{
				if(abs(a[L].c)<=abs(a[R].c))
					ans-=a[R].b-1,R--;
				else
					ans-=a[L].b-1,L++;				
			}
		}
		cout<<ans<<endl;
	}
    /******************/
	/*while(L<q[i].l) */
	/*    del(a[L++]);*/
	/*while(L>q[i].l) */
	/*    add(a[--L]);*/
	/*while(R<q[i].r) */
	/*	  add(a[++R]);*/
	/*while(R>q[i].r) */
	/*    del(a[R--]);*/
    /******************/
	QwQ;
}

```
