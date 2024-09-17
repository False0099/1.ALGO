# Gambling

## 题面翻译

### 题目大意：
两个人 $A,B$ 玩游戏，每个人有 1 个长度为 $n$ 的序列，每次一个人可以从序列中拿一个数并加入自己的分数，或者把对手序列中没选的数中去掉一个，这两个人都足够聪明，求 $A$ 分数与 $B$ 分数的差

### 输入格式：
第一行一个整数 $n$

第二行 $n$ 个整数，表示 A 的序列

第三行 $n$ 个整数，表示 B 的序列

### 输出格式：
一个整数，表示 $A$ 分数与 $B$ 分数的差

```
### 题目大意：
两个人$A,B$玩游戏，每个人有1个长度为$n$的序列，每次一个人可以从序列中拿一个数并加入自己的分数，或者把对手序列中没选的数中去掉一个，这两个人都足够聪明，求$A$分数与$B$分数的差

### 输入格式：
第一行一个整数$n$

第二行$n$个整数，表示A的序列

第三行$n$个整数，表示B的序列

### 输出格式：
一个整数，表示$A$分数与$B$分数的差
```

## 题目描述

Two players A and B have a list of $ n $ integers each. They both want to maximize the subtraction between their score and their opponent's score.

In one turn, a player can either add to his score any element from his list (assuming his list is not empty), the element is removed from the list afterward. Or remove an element from his opponent's list (assuming his opponent's list is not empty).

Note, that in case there are equal elements in the list only one of them will be affected in the operations above. For example, if there are elements $ \{1, 2, 2, 3\} $ in a list and you decided to choose $ 2 $ for the next turn, only a single instance of $ 2 $ will be deleted (and added to the score, if necessary).

The player A starts the game and the game stops when both lists are empty. Find the difference between A's score and B's score at the end of the game, if both of the players are playing optimally.

Optimal play between two players means that both players choose the best possible strategy to achieve the best possible outcome for themselves. In this problem, it means that each player, each time makes a move, which maximizes the final difference between his score and his opponent's score, knowing that the opponent is doing the same.

## 输入格式

The first line of input contains an integer $ n $ ( $ 1 \le n \le 100\, 000 $ ) — the sizes of the list.

The second line contains $ n $ integers $ a_i $ ( $ 1 \le a_i \le 10^6 $ ), describing the list of the player A, who starts the game.

The third line contains $ n $ integers $ b_i $ ( $ 1 \le b_i \le 10^6 $ ), describing the list of the player B.

## 输出格式

Output the difference between A's score and B's score ( $ A-B $ ) if both of them are playing optimally.

## 样例 #1

### 样例输入 #1

```
2
1 4
5 1
```

### 样例输出 #1

```
0
```

## 样例 #2

### 样例输入 #2

```
3
100 100 100
100 100 100
```

### 样例输出 #2

```
0
```

## 样例 #3

### 样例输入 #3

```
2
2 1
5 6
```

### 样例输出 #3

```
-3
```

## 提示

In the first example, the game could have gone as follows:

- A removes $ 5 $ from B's list.
- B removes $ 4 $ from A's list.
- A takes his $ 1 $ .
- B takes his $ 1 $ .

Hence, A's score is $ 1 $ , B's score is $ 1 $ and difference is $ 0 $ .

There is also another optimal way of playing:

- A removes $ 5 $ from B's list.
- B removes $ 4 $ from A's list.
- A removes $ 1 $ from B's list.
- B removes $ 1 $ from A's list.

The difference in the scores is still $ 0 $ .

In the second example, irrespective of the moves the players make, they will end up with the same number of numbers added to their score, so the difference will be $ 0 $ .

## 题解
我们本题的思路是：我们注意到我们的**操作相当于让我们的自己的价值最大，对方的价值最小**，也就是说，我们每一次的操作是对称的。于是，我们就可以通过我们的简单的单调队列来实现我们的排序工作，并且每一次选取了九八我们的对应的头部给 pop 掉即可。

```
#include<bits/stdc++.h>
#define ll long long//需要开long long 
using namespace std;

const int MAXN=1e6+10;
ll n,a[MAXN]={0},b[MAXN]={0},ans=0,sum=0;
//a为 A的序列  b为 B的序列  ans是 A的分数  sum是 B的分数 

bool cmp(int x,int y){//自定义排序 
      return x>y;
}

int main(){
	ios::sync_with_stdio(0);//开下优化 
	cin.tie(0);cout.tie(0); 
	
	cin>>n;
	for(ll i=0;i<n;i++)
	{
		cin>>a[i];
	}
	for(ll i=0;i<n;i++)
	{
		cin>>b[i];
	}
	sort(a,a+n,cmp);//按从大到小排序 
	sort(b,b+n,cmp);
	for(ll i=0,j=0;i<n&&i+j<n*2||j<n&&i+j<n*2;)//模拟队列 
	{
		//如果队列 a中最大的数大于等于队列 b中最大的数 或队列 b为空 
		//那么ans就加上队列 a中最大的数
		//否则去掉队列 b中最大的数 
		if(a[i]>=b[j]||j>=n) 
		{
			ans+=a[i];
			i++; 
		} 
		else
		{
			j++;
		}
		//如果队列 b中最大的数大于等于队列 a中最大的数 或队列 b为空 
		//那么sum就加上队列 b中最大的数
		//否则去掉队列 a中最大的数
		if(a[i]<=b[j]||i>=n)
		{
			sum+=b[j];
			j++; 
		}
		else
		{
			i++;
		}
	}
	cout<<ans-sum;//最后输出A与B分数之差 
	return 0;//代码部分结束 
}
```

