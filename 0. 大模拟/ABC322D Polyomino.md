# [ABC 322 D] Polyomino

## 题面翻译

给定一个 $4 \times 4$ 的地图，地图上存在三个连通块，每个连通块用 ```#``` 连接。

现在你可以将这三个连通块任意平移、旋转到任何位置摆放，但你不可以翻转，问是否能**刚好**覆盖地图（即三个连通块不能有重合、超出地图或铺不满地图）。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc322/tasks/abc322_d

いくつかの正方形を辺でつなげてできる、連結な多角形の形をしたパズルのピースのことを **ポリオミノ** と呼びます。

縦 $ 4 $ マス、横 $ 4 $ マスのグリッドと、グリッドに収まる大きさの $ 3 $ 個のポリオミノがあります。  
 $ i $ 番目のポリオミノの形は $ 16 $ 個の文字 $ P_{i, j, k} $ ($ 1\ \leq\ j,\ k\ \leq\ 4 $) によって表されます。$ P_{i,\ j,\ k} $ は何も置かれていないグリッドに $ i $ 番目のポリオミノを置いたときの状態を意味して、$ P_{i,\ j,\ k} $ が `#` の場合は上から $ j $ 行目、左から $ k $ 列目のマスにポリオミノが置かれていることを、`.` の場合は置かれていないことを意味します。(入出力例 $ 1 $ の図も参考にしてください。)

あなたは次の条件を全て満たすように $ 3 $ 個のポリオミノ全てをグリッドに敷き詰めることにしました。

- グリッドの全てのマスはポリオミノで覆われている。
- ポリオミノ同士が重なるように置くことはできない。
- ポリオミノがグリッドからはみ出るように置くことはできない。
- ポリオミノの平行移動と回転は自由に行うことができるが、裏返すことはできない。
 
条件を満たすようにグリッドにポリオミノを敷き詰めることは可能ですか？

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ P_{1,1,1}P_{1,1,2}P_{1,1,3}P_{1,1,4} $ $ P_{1,2,1}P_{1,2,2}P_{1,2,3}P_{1,2,4} $ $ P_{1,3,1}P_{1,3,2}P_{1,3,3}P_{1,3,4} $ $ P_{1,4,1}P_{1,4,2}P_{1,4,3}P_{1,4,4} $ $ P_{2,1,1}P_{2,1,2}P_{2,1,3}P_{2,1,4} $ $ P_{2,2,1}P_{2,2,2}P_{2,2,3}P_{2,2,4} $ $ P_{2,3,1}P_{2,3,2}P_{2,3,3}P_{2,3,4} $ $ P_{2,4,1}P_{2,4,2}P_{2,4,3}P_{2,4,4} $ $ P_{3,1,1}P_{3,1,2}P_{3,1,3}P_{3,1,4} $ $ P_{3,2,1}P_{3,2,2}P_{3,2,3}P_{3,2,4} $ $ P_{3,3,1}P_{3,3,2}P_{3,3,3}P_{3,3,4} $ $ P_{3,4,1}P_{3,4,2}P_{3,4,3}P_{3,4,4} $

## 输出格式

問題文の条件を満たすようにポリオミノを敷き詰めることが可能である場合は `Yes` を、そうでない場合は `No` を出力せよ。

## 样例 #1

### 样例输入 #1

```
....
###.
.#..
....
....
.###
.##.
....
..#.
.##.
.##.
.##.
```

### 样例输出 #1

```
Yes
```

## 样例 #2

### 样例输入 #2

```
###.
#.#.
##..
....
....
..#.
....
....
####
##..
#...
#...
```

### 样例输出 #2

```
Yes
```

## 样例 #3

### 样例输入 #3

```
##..
#..#
####
....
....
##..
.##.
....
.#..
.#..
.#..
.#..
```

### 样例输出 #3

```
No
```

## 样例 #4

### 样例输入 #4

```
....
..#.
....
....
....
..#.
....
....
....
..#.
....
....
```

### 样例输出 #4

```
No
```

## 样例 #5

### 样例输入 #5

```
....
####
#...
#...
....
####
...#
..##
....
..##
..#.
..##
```

### 样例输出 #5

```
No
```

## 样例 #6

### 样例输入 #6

```
###.
.##.
..#.
.###
....
...#
..##
...#
....
#...
#...
#...
```

### 样例输出 #6

```
Yes
```

## 提示

### 制約

- $ P_{i,\ j,\ k} $ は `#` または `.`
- 与えられるポリオミノは連結である。つまり、ポリオミノを構成する正方形同士は、正方形のみを上下左右に辿って互いに行き来できる
- 与えられるポリオミノは空でない
 
### Sample Explanation 1

入力例 $ 1 $ に対応するポリオミノの形は次の図のようになります。 !\ [image1\](https://img.atcoder.jp/abc322/f0e25c2abcdbeade76fcb12eaee39f23.jpg) この場合、次の図のようにポリオミノを配置することで、問題文の条件を満たすようにグリッドにポリオミノを敷き詰めることができます。 !\ [image2\](https://img.atcoder.jp/abc322/81e983f85e958e0d612063adcc455c71.jpg) よって答えは `Yes` になります。

### Sample Explanation 2

入力例 $ 2 $ の $ 1 $ 番目のポリオミノのように、ポリオミノは穴の空いた多角形の形をしている場合があります。

### Sample Explanation 3

ポリオミノを敷き詰めるときに、ポリオミノを裏返してはならないのに注意してください。

## 题解
我们这一题的困难在于我们的分类讨论，我们首先要计算我们把每个物体旋转，然后再计算把每个物体平移的情况，最后再去依次匹配。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
#define ll long long
const int N=1e5+10,INF=INT_MAX,Mod=998244353;
char x,mp[20][20];
bool ans=false;
int num,a[12][4][4],c[4][4];
void change(ll t){//将多米诺骨牌转向
	ll i,j;
	for(i=0;i<4;i++)for(j=0;j<4;j++)c[i][j]=a[t][j][3-i];
	for(i=0;i<4;i++)for(j=0;j<4;j++)a[t][i][j]=c[i][j];
}
void dfs(int step)
{
	if(step==3)
	{
		f(i,4,7)f(j,4,7)if(mp[i][j]!=1)return ;
		cout<<"Yes";
		exit(0);		
	}
	f(i,0,3)
	{
		f(j,1,7)f(k,1,7)
		{
			f(g,0,3)f(h,0,3)mp[j+g][k+h]+=a[step][g][h];
			dfs(step+1);
			f(g,0,3)f(h,0,3)mp[j+g][k+h]-=a[step][g][h];
		}
		change(step);
	}
		
		
}
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    f(i,0,2)
    	f(j,0,3)
    		f(k,0,3)
    			cin>>x,num+=a[i][j][k]=(x=='#');
    if(num==16)dfs(0);
    cout<<"No";
	return 0;
}
```