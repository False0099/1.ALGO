# [ABC 345 D] Tiling

## 题面翻译

有一个由 $H$ 行和 $W$ 列组成的网格，每个单元格的边长为 $1$，我们有 $N$ 块瓷砖。
第 $i$ 个图块 $(1 \le i \le N)$ 是一个大小为 $A_i \times B_i$  的矩形。
请判断是否有可能将这些图块放置在网格上，从而满足以下所有条件：

- 每个单元格都正好被一个图块覆盖。
- 有未使用的瓦片也没关系。
- 瓦片在放置时可以旋转或翻转。但是，每块瓦片必须与单元格的边缘对齐，不得超出网格。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc345/tasks/abc345_d

一辺の長さが $ 1 $ のマスからなる $ H $ 行 $ W $ 列のマス目と、$ N $ 枚のタイルがあります。  
$ i $ $ (1\leq\ i\leq\ N) $ 枚目のタイルは $ A_i\times\ B_i $ の長方形です。  
以下の条件をすべてみたすようにタイルをマス目に置くことができるか判定してください。

- 全てのマスがちょうど $ 1 $ 枚のタイルで覆われている。
- 使用されないタイルがあっても良い。
- 使用するタイルは **回転したり裏返したりして置かれていても良い**。ただし、各タイルはマスの線に合わせてマス目からはみ出ることがないように置かれていなければならない。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ H $ $ W $ $ A_1 $ $ B_1 $ $ A_2 $ $ B_2 $ $ \vdots $ $ A_N $ $ B_N $

## 输出格式

問題文中の条件をみたすようにタイルをマス目に置くことができるならば `Yes` を、そうでないならば `No` を出力せよ。

## 样例 #1

### 样例输入 #1

```
5 5 5
1 1
3 3
4 4
2 3
2 5
```

### 样例输出 #1

```
Yes
```

## 样例 #2

### 样例输入 #2

```
1 1 2
2 3
```

### 样例输出 #2

```
No
```

## 样例 #3

### 样例输入 #3

```
1 2 2
1 1
```

### 样例输出 #3

```
No
```

## 样例 #4

### 样例输入 #4

```
5 3 3
1 1
2 2
2 2
2 2
2 2
```

### 样例输出 #4

```
No
```

## 提示

### 制約

- $ 1\leq\ N\leq\ 7 $
- $ 1\ \leq\ H, W\ \leq\ 10 $
- $ 1\leq\ A_i, B_i\leq\ 10 $
- 入力はすべて整数

### Sample Explanation 1

$ 2,4,5 $ 枚目のタイルを使用して次のように置くと、マス目の各マスをちょうど $ 1 $ 枚のタイルで覆うことができます。 !\ [\](https://img.atcoder.jp/abc345/0a0f2829d0485013deabba0103dbd906.png) よって、`Yes` を出力します。

### Sample Explanation 2

マス目からはみ出さないようにタイルを置くことはできません。 よって、`No` を出力します。

### Sample Explanation 3

全てのマスを覆うようにタイルを置くことができません。 よって、`No` を出力します。

### Sample Explanation 4

全てのマスはちょうど $ 1 $ 枚のタイルで覆われている必要があることに注意してください。

## 题解
题意：给你一个 $H*W$ 的矩阵，要你用 $N$ 种方法来填满我们的对应矩阵，问你是否存在一种对应的填充方法。

我们本题就是典型的爆搜模拟题，我们这一题的思路是对于我们的每一个方格，先去枚举我们采用哪一种瓷砖，再去枚举我们这一种瓷砖怎么旋转。如果最后有一种方法，能够让我们的所有都铺满，我们直接退出即可。

```cpp

#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,h,w;
bool vis[20][20],use[20];
struct node{
	int x,y;
}a[20];

bool ck(int x,int y,int ex,int ey){
	for(int i=x;i<=ex;i++){
		for(int j=y;j<=ey;j++){
			if(vis[i][j]){
				return 0;
			}
		}
	}
	return 1;
}

void put(int x,int y,int ex,int ey,int col){
	for(int i=x;i<=ex;i++){
		for(int j=y;j<=ey;j++){
			vis[x][i]=col;
		}
	}
}

void dfs(int x,int y){
	if(y>w) y=1,x++;
	if(x==h+1){cout<<"Yes",exit(0);} //放完了
	if(vis[x][y]){ //被放过了就直接搜下一个
		dfs(x,y+1);
		return;
	}
	for(int i=1;i<=n;i++){
		if(use[i]) continue; //已经用过了
		int ex=x+a[i].x-1,ey=y+a[i].y-1;
		if(ex>h||ey>w) continue; //越界
		if(!ck(x,y,ex,ey)) continue; //有点被放了
		use[i]=1;
		put(x,y,ex,ey,1);
		dfs(x,y+1);
		put(x,y,ex,ey,0);
		use[i]=0;
	}
	for(int i=1;i<=n;i++){ //考虑横着放
		if(use[i]||a[i].x==a[i].y) continue;
		int ex=x+a[i].y-1,ey=y+a[i].x-1;
		if(ex>h||ey>w) continue;
		if(!ck(x,y,ex,ey)) continue;
		use[i]=1;
		put(x,y,ex,ey,1);
		dfs(x,y+1);
		put(x,y,ex,ey,0);
		use[i]=0;
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>h>>w;
	for(int i=1;i<=n;i++) cin>>a[i].x>>a[i].y;
	dfs(1,1);
	cout<<"No";
	return 0;
}
```