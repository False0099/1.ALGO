# Permutation Game

## 题面翻译

有一个长度为 $n$ 的仅为 $1\sim n$ 的序列，初始序列中所有的数均为红色。两个玩家依次进行以下三种操作中一种：

- 将某个数变成蓝色。
- 将所有蓝色的数重新排列（按照自己的意愿排列，红色不可进行排列，不必将所有的蓝色都交换位置）。
- 跳过此次操作。

两个玩家依次进行一次操作视为一个回合，游戏共进行 $100^{500}$ 回合。在游戏任何时刻，如果当前序列为 $\{1,2,3...,n\}$，则第一个操作的玩家胜利。如果当前序列为 $\{n,n-1,n-2...1\}$，则第二个玩家胜利。进行 $100^{500}$ 回合之后若还无人胜利，则平局。注意，两名玩家都以最优方案进行操作。他们会尽可能让自己胜利。

### 输入格式

第一个数为 $t$（$1\le t\le10^5$）表示数据组数。

对于每一组数据，第一行一个数 $n$，表示序列长度，下一行 $n$ 个数表示初始序列。

### 输出格式

如果第一个操作玩家胜利，输出 ```First	```，如果第二个玩家操作胜利，输出 ```Second```，平局输出 ```Tie```。

## 题目描述

Two players are playing a game. They have a permutation of integers $ 1 $ , $ 2 $ , ..., $ n $ (a permutation is an array where each element from $ 1 $ to $ n $ occurs exactly once). The permutation is not sorted in either ascending or descending order (i. e. the permutation does not have the form $ [1, 2, \dots, n] $ or $ [n, n-1, \dots, 1] $ ).

Initially, all elements of the permutation are colored red. The players take turns. On their turn, the player can do one of three actions:

- Rearrange the elements of the permutation in such a way that all red elements keep their positions (note that blue elements can be swapped with each other, but it's not obligatory);
- Change the color of one red element to blue;
- Skip the turn.

The first player wins if the permutation is sorted in ascending order (i. e. it becomes $ [1, 2, \dots, n] $ ). The second player wins if the permutation is sorted in descending order (i. e. it becomes $ [n, n-1, \dots, 1] $ ). If the game lasts for $ 100^{500} $ turns and nobody wins, it ends in a draw.

Your task is to determine the result of the game if both players play optimally.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^5 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 3 \le n \le 5 \cdot 10^5 $ ) — the size of the permutation.

The second line contains $ n $ integers $ p_1, p_2, \dots, p_n $ — the permutation itself. The permutation $ p $ is not sorted in either ascending or descending order.

The sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, print First if the first player wins, Second if the second player wins, and Tie if the result is a draw.

## 样例 #1

### 样例输入 #1

```
4
4
1 2 4 3
3
2 3 1
5
3 4 5 2 1
6
1 5 6 3 2 4
```

### 样例输出 #1

```
First
Tie
Second
Tie
```

## 提示

Let's show how the first player wins in the first example.

They should color the elements $ 3 $ and $ 4 $ blue during their first two turns, and then they can reorder the blue elements in such a way that the permutation becomes $ [1, 2, 3, 4] $ . The second player can neither interfere with this strategy nor win faster.

## 题解
通过本题，我们不难发现，我们的操作一：也就是我们的从新排序，对于我们的结果来说是**只会在决胜的时候使用**，因此，我们的问题就变成了：我们**先手和后手，谁能把自己需要的格子都染上自己的颜色**

这个时候，我们就可以把我们的格子分成下面的四类：第一种是**只有先手希望染色的**，第二种是**只有后手希望染色的**，第三种是**先手后手都需要染色的**，第四种就是**先手后手都不需要染色的**。

那么，我们不难发现，如果我们的先手想要获胜，一定就要先把自己的先手希望涂色的图上，然后再去吧先后手都需要染色的染完，**此时，我们的后手都还没有染完自己要染色的**。

也就是**a+c>=b**。

同理，我们也可以得出我们后手获胜的条件就是：**b+c>a**, 剩余的情况，我们一定就是一个都不涂我们共有的部分。

```
#include <bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		auto solve=[&](){
			int n;
			cin>>n;
			vector<int> a(n+1);
			for(int i=1;i<=n;i++){
				cin>>a[i];	
			}
			vector<int> ansa(n+1);
			vector<int> ansb(n+1);
			for(int i=1;i<=n;i++){
				ansa[i]=i;
				ansb[i]=n-i+1;
			}
			int c=0;
			int aa=0;
			int b=0;
			for(int i=1;i<=n;i++){
				if(a[i]!=ansa[i]&&a[i]!=ansb[i]){
					c++;
				}else if(a[i]!=ansa[i]){
					aa++;
				}else if(a[i]!=ansb[i]){
					b++;
				}
			}
			if(aa+c<=b){
				cout<<"First"<<endl;
			}else if(b+c<aa){
				cout<<"Second"<<endl;
			}else{
				cout<<"Tie"<<endl;
			}
			
		};
		solve();
	}
}
```