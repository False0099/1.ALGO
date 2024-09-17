# Description

![](https://vj.csgrandeur.cn/7c7b3f87295d3c387b8e9bfb99992141?v=1626583183)**Background** 骑士厌倦了一次又一次地看到同样的黑白方块，决定去旅行 环游世界。每当骑士移动时，一个方向是两个正方形，与此垂直的是一个正方形。骑士的世界就是他赖以生存的棋盘。我们的骑士生活在一个长方形棋盘上。你能帮这个爱冒险的骑士制定旅行计划吗？  
**Problem** 找到一条字典序最小路径，让骑士遍历整个棋盘。骑士可以在棋盘的任何方块上开始和结束。

# Input

输入从第一行的正整数 n 开始。下面的行包含 n 个测试用例。每个测试用例由一行两个正整数 p 和 q 组成，保证 1≤p×q≤26。表示有一个 p×q 棋盘，每个方块的位置用两个字符表示，列用大写字母表示（A 表示第一列），行用阿拉伯数字表示（11 表示第一行）

## Output

输出字典序最小的路径，如果没有这种路径，则应该在单行上输出 `impossible`。

## Sample

|Inputcopy|Outputcopy|
|---|---|
|3<br>1 1<br>2 3<br>4 3|Scenario #1 :<br>A1<br><br>Scenario #2 :<br>impossible<br><br>Scenario #3 :<br>A1B3C1A2B4C2A3B1C3A4B2C4|

## 题解
对于这种**求出具体路径**的问题，我们应该首先考虑 dfs，因为 dfs 可以记录我们的路径，同时，我们在 dfs 时，因为题目要求我们输出一条字典序最小的路径，所以我们在走路的时候贪心的，**先走字典序较小的那一部分，然后再走字典序较大的哪一个部分**。

终止条件：
1. 我们已经遍历完所有的点（cnt>=row* col）

过程转移：
1. 我们用一个棋盘

```cpp
#include <bits/stdc++.h>
using namespace std;
bool chess[26][26];
int dx[8]={-1,1,-2,2,-2,2,-1,1};
int dy[8]={-2,-2,-1,-1,1,1,2,2};
int row,col,counts,flag;
int result[26*26+10][2];
void dfs(int currow,int curcol){
	if(counts>=row*col){//如果所有的格子都被遍历过了 
		flag=1;
		return;
	}else{
		for(int i=0;i<8;i++){
			int nextrow=currow+dx[i];
			int nextcol=curcol+dy[i];
			if(nextrow>row||nextcol>col||nextrow<=0||nextcol<=0||chess[nextrow][nextcol]){
				continue;
			}
			chess[nextrow][nextcol]=1;
			counts++;
			result[counts-1][0]=nextrow;
			result[counts-1][1]=nextcol;
			dfs(nextrow,nextcol);
			if(flag) return;
			counts--;
			chess[nextrow][nextcol]=0;
		}
		return;
	}
}
int main(){
	int test;
	cin>>test;
	for(int i=1;i<=test;i++){
		cin>>row>>col;
		cout<<"Scenario #"<<i<<":"<<endl;
		if(row==1&&col==1){
			cout<<"A1"<<endl<<endl;
			continue;
		}
		if(row<3||col<3){
			cout<<"impossible"<<endl;
			continue;
		}
		flag=0,counts=1;
		memset(chess,0,sizeof chess);
		chess[0][0]=1;
		result[0][0]=0;
		result[0][1]=1;
		dfs(0,0);
		if(flag){
			for(int j=0;j<row*col;j++){
				char c=result[j][1]+'A';
				cout<<c<<result[j][0]+1;
			}
			cout<<endl<<endl;
		}else cout<<"impossible"<<endl; 
	}
}
```