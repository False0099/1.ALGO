# Matrix Game

## 题面翻译

### 题目描述
一个 $n$ 行 $m$ 列的网格图，有些格子上已经有 $1$，`Ashish` 和 `Vivek` 在这张网格图上做游戏，`Ashish` 先手。  

对于当前玩家，他需要在网格图上找一个位置设置为 $1$，条件是这一个位置所在的行以及列上都没有其他的 $1$，如果他不能操作了，那么他就输了。

求对于输入的网格图，谁能获胜。

### 输入格式
**本题有多组数据**

第一行有一个正整数 $T$，表示有 $T$ 组数据。  

每组数据的第一行有两个正整数 $n, m$，表示网格图的行数以及列数。  

之后 $n$ 行，每行一个长度为 $m$ 的 01 串，描述了这组数据的网格图上的这一行的初始状态。

保证 $1\le t,n,m\le50$。
### 输出格式
对于每组数据，输出胜者的名字。

## 题目描述

Ashish and Vivek play a game on a matrix consisting of $ n $ rows and $ m $ columns, where they take turns claiming cells. Unclaimed cells are represented by $ 0 $ , while claimed cells are represented by $ 1 $ . The initial state of the matrix is given. There can be some claimed cells in the initial state.

In each turn, a player must claim a cell. A cell may be claimed if it is unclaimed and does not share a row or column with any other already claimed cells. When a player is unable to make a move, he loses and the game ends.

If Ashish and Vivek take turns to move and Ashish goes first, determine the winner of the game if both of them are playing optimally.

Optimal play between two players means that both players choose the best possible strategy to achieve the best possible outcome for themselves.

## 输入格式

The first line consists of a single integer $ t $ $ (1 \le t \le 50) $ — the number of test cases. The description of the test cases follows.

The first line of each test case consists of two space-separated integers $ n $ , $ m $ $ (1 \le n, m \le 50) $ — the number of rows and columns in the matrix.

The following $ n $ lines consist of $ m $ integers each, the $ j $ -th integer on the $ i $ -th line denoting $ a_{i, j} $ $ (a_{i, j} \in \{0, 1\}) $ .

## 输出格式

For each test case if Ashish wins the game print "Ashish" otherwise print "Vivek" (without quotes).

## 样例 #1

### 样例输入 #1

```
4
2 2
0 0
0 0
2 2
0 0
0 1
2 3
1 0 1
1 1 0
3 3
1 0 0
0 0 0
1 0 0
```

### 样例输出 #1

```
Vivek
Ashish
Vivek
Ashish
```

## 提示

For the first case: One possible scenario could be: Ashish claims cell $ (1, 1) $ , Vivek then claims cell $ (2, 2) $ . Ashish can neither claim cell $ (1, 2) $ , nor cell $ (2, 1) $ as cells $ (1, 1) $ and $ (2, 2) $ are already claimed. Thus Ashish loses. It can be shown that no matter what Ashish plays in this case, Vivek will win.

For the second case: Ashish claims cell $ (1, 1) $ , the only cell that can be claimed in the first move. After that Vivek has no moves left.

For the third case: Ashish cannot make a move, so Vivek wins.

For the fourth case: If Ashish claims cell $ (2, 3) $ , Vivek will have no moves left.

## 题解
本题我们注意到，我们每一次操作，都会**让我们的可选行以及可选列都减少 1**。因此，我们最多可以操作的次数就是 $min(a,b)$ 其中 $a$ 表示我们的行可以操作多少，$b$ 表示我们的列可以操作多少。

那么，我们如果 $min(a,b)$ 是一个奇数，那么我们一定是先手必胜，否则我们就一定是后手必胜。

```
#include <bits/stdc++.h>
using namespace std;
 
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define int long long

const int N = 51;

int n, m;
int a[N][N];

int32_t main()
{
	IOS;
	int t;
	cin >> t;
	while(t--)
	{
		cin >> n >> m;
		set< int > r, c;
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= m; j++)
			{
				cin >> a[i][j];
				if(a[i][j] == 1)
					r.insert(i), c.insert(j);
			}
		}
		int mn = min(n — r.size(), m — c.size());
		if(mn % 2)
			cout << "Ashish" << endl;
		else
			cout << "Vivek" << endl;
	}
	return 0;
}

```