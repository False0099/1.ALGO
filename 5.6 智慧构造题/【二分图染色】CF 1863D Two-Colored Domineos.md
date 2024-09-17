# Two-Colored Dominoes

## 题面翻译

有一个 $n \times m$ 的棋盘，上面铺着一些 $1 \times 2$ 的多米诺骨牌（横竖均有可能），骨牌之间没有重叠。

你需要找到一种染色方案满足以下条件：

- 每个多米诺骨牌一端被染白，另一端被染黑。其他没有骨牌的格子不染色。
- 对于棋盘的每一行，被染黑的格子数等于被染白的格子数。
- 对于棋盘的每一列，被染黑的格子数等于被染白的格子数。

请输出任意一种染色方案，如果无解，输出 $-1$。

本题有多组测试数据，$1 \leq T \leq 10^{4}$，$2 \leq n,m \leq 500$，$\sum (n \times m) \leq 2.5 \times 10^{5}$。

## 题目描述

There is an $ n\times m $ board divided into cells. There are also some dominoes on this board. Each domino covers two adjacent cells (that is, two cells that share a side), and no two dominoes overlap.

Piet thinks that this board is too boring and it needs to be painted. He will paint the cells of the dominoes black and white. He calls the painting beautiful if all of the following conditions hold:

- For each domino, one of its cells is painted white and the other is painted black;
- For each row, the number of black cells in this row equals the number of white cells in this row;
- For each column, the number of black cells in this column equals the number of white cells in this column.

Note that the cells that are not covered by dominoes are not painted at all, they are counted as neither black nor white.

Help Piet produce a beautiful painting or tell that it is impossible.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10\, 000 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 2\le n, m\le 500 $ ).

The next $ n $ lines describe the tiling of the board, row by row from top to bottom. Each of these lines contains $ m $ characters, describing the cells in the corresponding row from left to right. Each character is one of U, D, L, R, or ., meaning that the cell is covered with a top, bottom, left, right half of a domino or nothing, respectively. The tiling is guaranteed to be valid.

It is guaranteed that the sum of $ n \cdot m $ over all test cases does not exceed $ 250\, 000 $ .

## 输出格式

For each test case, output a single integer $ -1 $ if a beautiful painting does not exist. Otherwise, print $ n $ lines, each containing $ m $ characters, describing the colors in the corresponding row of a beautiful painting. Every character corresponding to a cell not covered by a domino must be . (a dot), and all other characters must be B if the corresponding cell is black or W if it is white.

If there are multiple solutions, print any of them.

## 样例 #1

### 样例输入 #1

```
3
4 6
..LR..
ULRU..
DLRDUU
..LRDD
5 4
.LR.
.UU.
UDDU
D..D
LR..
2 2
..
..
```

### 样例输出 #1

```
..WB..
WWBB..
BBWWWB
..BWBW
-1
..
..
```

## 提示

In the first test case, the answer is illustrated below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1863D/c02597064063806335d0d205f181144db4826066.png)In the second test case, it is impossible to paint all cells the right way.
## 题解
对于我们的构造体，我们分为两步：第一步，判断是否可行，在这一题中，如果一个图是可行的，那么我们的每一行每一列内的数目为奇数，那么我们一定不能构造，如果为偶数，那么我们一定可以构造。

第二步：我们尝试去构造答案，我们先按行去构造，如果第一个 LR 是一黑一白，那么我们之后相同位置的 LR 就必须是交替的，一白一黑，一黑一白等等，同理：如果我们在列方向上，我们第一个设定的是上黑下摆，那么下面一个就必须是上白下黑。以此类推去构造即可

```cpp
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f
#define re register
#define inf_db 127
#define ls id << 1
#define rs id << 1 | 1
#define endl '\n'
typedef pair <int,int> pii;
const int MAXN = 1e3 + 10;
int T,n,m,ans[MAXN][MAXN],len_l[MAXN],len_r[MAXN];
char c[MAXN][MAXN];
signed main()
{
	cin >> T;
	while(T--)
	{
		int flag = false,tmp = 2;
		cin >> n >> m;
		for(int i = 1;i <= n;i++) len_l[i] = 0;
		for(int i = 1;i <= m;i++) len_r[i] = 0;
		for(int i = 1;i <= n;i++) for(int j = 1;j <= m;j++) ans[i][j] = 2;
		for(int i = 1;i <= n;i++) 
			for(int j = 1;j <= m;j++) 
			{
				cin >> c[i][j];
				if(c[i][j] != '.') len_l[i]++,len_r[j]++;
				else ans[i][j] = 1;
			}
		for(int i = 1;i <= n;i++) if(len_l[i] % 2) flag = true;
		for(int i = 1;i <= m;i++) if(len_r[i] % 2) flag = true;
		if(flag == true){puts("-1");continue;}
		for(int i = 1;i <= n;i++)
			for(int j = 1;j <= m;j++)
				if(c[i][j] == 'U') ans[i][j] = tmp,ans[i + 1][j] = tmp ^ 1,tmp ^= 1;
		for(int j = 1;j <= m;j++)
			for(int i = 1;i <= n;i++)
				if(c[i][j] == 'L') ans[i][j] = tmp,ans[i][j + 1] = tmp ^ 1,tmp ^= 1;
		for(int i = 1;i <= n;i++)
		{
			for(int j = 1;j <= m;j++)
			{
				if(ans[i][j] == 1) cout << '.';
				if(ans[i][j] == 2) cout << 'B';
				if(ans[i][j] == 3) cout << 'W'; 
			}	
			cout << endl;
		}
			
	}
	return 0;
}
```
```