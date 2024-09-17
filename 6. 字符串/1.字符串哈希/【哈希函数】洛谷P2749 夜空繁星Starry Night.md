# [USACO 5.1] 夜空繁星 Starry Night

## 题目背景

高高的星空，簇簇闪耀的群星形态万千。一个星座 (cluster)是一群连通的星组成的非空连通星系，这里的连通是指水平，垂直或者对角相邻的两个星星。一个星座不能是另一个更大星座的一部分，星座可以相似 (similar)。如果两个星座有相同的形状，而且包括相同数目的星体，那么不管其方向性如何，就算相似。一般而言，星座可能的方向有八个，如图 1 所示。

![](https://cdn.luogu.com.cn/upload/pic/1970.png)

## 题目描述

夜空可以表示为一份天体图 (sky map)，它是一个由字符 0 和 1 组成的二维矩阵，字符 1 表示所在的位置有一颗星；字符 0 表示该位置上是空的. 给定一份天体图，用同一个小写英文标识 (mark)相似的所有星座。相似的星座必须用相同的字母标识，不同的星座表示为不同的字母。标识一个星座，就是将其中各星体对应的字符 1 替换为相应的小写字母.

## 输入格式

文件的前两行分别记录了天体图的宽度 W、深度 H。而天体图则是由接下来的 H 行表示，每行包括 W 个字符. ……

## 输出格式

输出文件记录了天体图与文件 STARRY. IN 相似，不同之处在于，各个星座按照“任务”中的要求进行了标识 (mark)。

对于同一个输入文件，可能会有很多不同的标识，此时，输出字典序最小的标识。

## 样例 #1

### 样例输入 #1

```
23
15
10001000000000010000000
01111100011111000101101
01000000010001000111111
00000000010101000101111
00000111010001000000000
00001001011111000000000
10000001000000000000000
00101000000111110010000
00001000000100010011111
00000001110101010100010
00000100110100010000000
00010001110111110000000
00100001110000000100000
00001000100001000100101
00000001110001000111000
```

### 样例输出 #1

```
a000a0000000000b0000000
0aaaaa000ccccc000d0dd0d
0a0000000c000c000dddddd
000000000c0b0c000d0dddd
00000eee0c000c000000000
0000e00e0ccccc000000000
b000000e000000000000000
00b0f000000ccccc00a0000
0000f000000c000c00aaaaa
0000000ddd0c0b0c0a000a0
00000b00dd0c000c0000000
000g000ddd0ccccc0000000
00g0000ddd0000000e00000
0000b000d0000f000e00e0b
0000000ddd000f000eee000
```

## 提示

在这种情况下，天体图是一个长 23 宽为 15 的二维矩阵。请注意这幅天体图是对应（corresponds to）下面这个矩阵的图像。

Starry-2. Gif 图 starry-2：天体图

 ![](https://cdn.luogu.com.cn/upload/pic/1971.png) 

这是上述输入实例的一个可能的结果。请注意，该输出文件对应于下面的天空景象。


 ![](https://cdn.luogu.com.cn/upload/pic/1972.png) 

### 数据范围

0 <= 星空的长和宽 <= 100

0 <= 星座个数 <= 500

0 <= 不相似的星座个数 <= 26

1 <= 每个星座中星星个数 <= 160

## 题解
我们本题的思路是：首先通过我们的 dfs 求出我们满足题目要求的连通块，这一步相较于我们的常规的 dfs 求联通快来说可能会有一点不同，因为我们本题的扩展方向会相对来说比较多，因此这是我们的第一个坑点：

我们的第二个问题是在于我们应该怎么样去计算我们的哈希函数，这里我们选择的函数是我们这个连通块内的距离和，以及乘上我们这一个连通块内的元素个数。于是，哦我们呢加上我们的第一个部分，我们就能通过本题。
```
#include <bits/stdc++.h>
using namespace std;
const int N=110;
int n,m; 
int g[N][N];
int id[N][N];
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
typedef pair<int,int> PII;
vector<PII> pairs_p[N*N];//存储我们连通块对应的点集 
int ans[N*N];//存储我们每一个连通块对应的种类 
void dfs(int x,int y,int idx){
	for(int dx=-1;dx<=1;dx++){
		for(int dy=-1;dy<=1;dy++){
			int xx=x+dx;
			int yy=y+dy;
			if(xx<0||xx>=n||yy<0||yy>=m){
				continue;
			}
			if(g[xx][yy]!=1){
				continue;
			}
			if(id[xx][yy]!=0){
				continue;
			}
			id[xx][yy]=idx;
			pairs_p[idx].push_back({xx,yy});
			dfs(xx,yy,idx);
		}
	} 
}
double getdist(int x1,int y1,int x2,int y2){
	int sum=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
	return sqrt(sum);
}
double hashee(int id){
	int n=pairs_p[id].size();
	double dist=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			dist+=getdist(pairs_p[id][i].first,pairs_p[id][i].second,pairs_p[id][j].first,pairs_p[id][j].second);
		}
	}
	return dist*n;
}
int main(){
	cin>>m>>n;
	for(int i=0;i<n;i++){
		string tmp;
		cin>>tmp;
		for(int j=0;j<m;j++){
			g[i][j]=tmp[j]-'0';
		}
	}
	int cnt=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(g[i][j]!=0&&id[i][j]==0){
				dfs(i,j,++cnt);
			}
		}
	}
	int types=0;
	map<int,int> hash_to_types;
	for(int i=1;i<=cnt;i++){
		double tmp=hashee(i);
		if(hash_to_types.count(tmp)){
			ans[i]=hash_to_types[tmp];
		}else{
			hash_to_types[tmp]=++types;
		}
		ans[i]=hash_to_types[tmp];
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(id[i][j]==0){
				cout<<0;
			}else{
				cout<<(char)(ans[id[i][j]]-1+'a');
			}
		}
		puts("");
	} 
}
```