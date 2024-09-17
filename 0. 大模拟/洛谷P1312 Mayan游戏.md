# [NOIP 2011 提高组] Mayan 游戏

## 题目描述

Mayan puzzle 是最近流行起来的一个游戏。游戏界面是一个 $7$ 行 $\times5$ 列的棋盘，上面堆放着一些方块，方块不能悬空堆放，即方块必须放在最下面一行，或者放在其他方块之上。游戏通关是指在规定的步数内消除所有的方块，消除方块的规则如下：

1. 每步移动可以且仅可以沿横向（即向左或向右）拖动某一方块一格：当拖动这一方块时，如果拖动后到达的位置（以下称目标位置）也有方块，那么这两个方块将交换位置（参见输入输出样例说明中的图 $6$ 到图 $7$）；如果目标位置上没有方块，那么被拖动的方块将从原来的竖列中抽出，并从目标位置上掉落（直到不悬空，参见下面图 $1$ 和图 $2$）；

![](https://cdn.luogu.com.cn/upload/image_hosting/gyse4ktp.png)

2. 任一时刻，如果在一横行或者竖列上有连续三个或者三个以上相同颜色的方块，则它们将立即被消除（参见图 1 到图 3）。

![](https://cdn.luogu.com.cn/upload/image_hosting/et7at5fd.png)

注意：

a) 如果同时有多组方块满足消除条件，几组方块会同时被消除（例如下面图 $4$，三个颜色为 $1$ 的方块和三个颜色为 $2$ 的方块会同时被消除，最后剩下一个颜色为 $2$ 的方块）。

b) 当出现行和列都满足消除条件且行列共享某个方块时，行和列上满足消除条件的所有方块会被同时消除（例如下面图 5 所示的情形，$5$ 个方块会同时被消除）。

3. 方块消除之后，消除位置之上的方块将掉落，掉落后可能会引起新的方块消除。注意：掉落的过程中将不会有方块的消除。

上面图 $1$ 到图 $3$ 给出了在棋盘上移动一块方块之后棋盘的变化。棋盘的左下角方块的坐标为 $(0,0)$，将位于 $(3,3)$ 的方块向左移动之后，游戏界面从图 $1$ 变成图 $2$ 所示的状态，此时在一竖列上有连续三块颜色为 $4$ 的方块，满足消除条件，消除连续 $3$ 块颜色为 $4$ 的方块后，上方的颜色为 $3$ 的方块掉落，形成图 $3$ 所示的局面。

## 输入格式

共 $6$ 行。

第一行为一个正整数 $n$，表示要求游戏通关的步数。

接下来的 $5$ 行，描述 $7 \times 5$ 的游戏界面。每行若干个整数，每两个整数之间用一个空格隔开，每行以一个 $0$ 结束，自下向上表示每竖列方块的颜色编号（颜色不多于 $10$ 种，从 $1$ 开始顺序编号，相同数字表示相同颜色）。

输入数据保证初始棋盘中没有可以消除的方块。

## 输出格式

如果有解决方案，输出 $n$ 行，每行包含 $3$ 个整数 $x,y,g$，表示一次移动，每两个整数之间用一个空格隔开，其中 $(x,y)$ 表示要移动的方块的坐标，$g$ 表示移动的方向，$1$ 表示向右移动，$-1$ 表示向左移动。注意：多组解时，按照 $x$ 为第一关键字，$y$ 为第二关键字，$1$ 优先于 $-1$，给出一组字典序最小的解。游戏界面左下角的坐标为 $(0,0)$。

如果没有解决方案，输出一行 `-1`。

## 样例 #1

### 样例输入 #1

```
3
1 0
2 1 0
2 3 4 0
3 1 0
2 4 3 4 0
```

### 样例输出 #1

```
2 1 1
3 1 1
3 0 1
```

## 提示

**【输入输出样例说明】**

按箭头方向的顺序分别为图 $6$ 到图 $11$

![](https://cdn.luogu.com.cn/upload/image_hosting/vmb8yy6n.png)

样例输入的游戏局面如上面第一个图片所示，依次移动的三步是：$(2,1)$ 处的方格向右移动，$(3,1)$ 处的方格向右移动，$(3,0)$ 处的方格向右移动，最后可以将棋盘上所有方块消除。

**【数据范围】**

对于 $30\%$ 的数据，初始棋盘上的方块都在棋盘的最下面一行；

对于 $100\%$ 的数据，$0<n \le 5$。

## 题解
我们本题中实现思路为：先去自己在本地写一个游戏，实现我们的 `move,clear` 功能，然后我们再去写我们的 `dfs` 暴力模拟即可。最后，我们的代码实现如下：
```
#include <bits/stdc++.h>
using namespace std;
const int N=10;
int mp[N][N];
int mark[N][N];
int saved_map[N][N][N];
int read()
{
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
void save(int idx){
	for(int i=0;i<5;i++){
		for(int j=0;j<8;j++){
			saved_map[idx][i][j]=mp[i][j];
		}
	}
}
void load(int idx){
	for(int i=0;i<5;i++){
		for(int j=0;j<8;j++){
			mp[i][j]=saved_map[idx][i][j];
		}
	}
}
bool empty(){
	for(int i=0;i<5;i++){
		for(int j=0;j<8;j++){
			if(mp[i][j]!=0){
				return false;
			}
		}
	}
	return true;
}
bool clear(){
	bool havemark=false;
	for(int i=0;i<5;i++){
		for(int j=0;j<7;j++){
			if(i+2<5&&mp[i][j]!=0&&mp[i][j]==mp[i+1][j]&&mp[i+2][j]==mp[i][j]){
				havemark=true;
				mark[i][j]=true;
				mark[i+1][j]=true;
				mark[i+2][j]=true;
			}
			if(j+2<7&&mp[i][j]!=0&&mp[i][j]==mp[i][j+1]&&mp[i][j+2]==mp[i][j]){
				havemark=true;
				mark[i][j]=true;
				mark[i][j+1]=true;
				mark[i][j+2]=true;
			}
		}
	}
	if(!havemark){
		return false;
	}
	for(int i=0;i<5;i++){
		for(int j=0;j<7;j++){
			if(mark[i][j]){
				mp[i][j]=0;
				mark[i][j]=0;
			}
		}
	}
	return true; 
}
void debug(){
	puts("");
	for(int i=0;i<5;i++){
		for(int j=0;j<7;j++){
			cout<<mp[i][j]<<" ";
		}
		puts("");
	}
	puts("");
	
}
void fall(){
	//debug();
	do{
		//debug();
		for(int i=0;i<5;i++){
			for(int j=0;j<7;j++){
				if(mp[i][j]!=0){
					while(j-1>=0&&mp[i][j-1]==0){
						swap(mp[i][j],mp[i][j-1]);
						j--;
					}
				}
			}
		}
	}while(clear());
	//debug();
}

void move(int x,int y,int way){
	if(way==-1){//way=1，我们向左移动 
		swap(mp[x][y],mp[x-1][y]); 
	}else{
		swap(mp[x][y],mp[x+1][y]);
	}
	fall();
}
struct node{
	int x;
	int y;
	int type;
};
stack<node> q;
int n;
void print_ope(){
	auto u=q.top();
	q.pop();
	if(q.size()){
		print_ope();
	}
	cout<<u.x<<" "<<u.y<<" "<<u.type<<endl;
}
void dfs(int depth){
	if(empty()){
		int qq=q.size();
		print_ope();
		if(qq<n){
			for(int i=qq;i<n;i++){
				cout<<0<<" "<<0<<" "<<1<<endl; 
			}
		}
		exit(0);
	}
	if(depth==n){
		if(empty()){
			print_ope();
			exit(0);
		}	
	}else{
		for(int i=0;i<5;i++){
			for(int j=0;j<7;j++){
				if(mp[i][j]&&i+1<5){
					save(depth);
					move(i,j,1);
					//debug();
					q.push({i,j,1});
					dfs(depth+1);
					q.pop();
					load(depth);
				}
				if(mp[i][j]&&i>0){
					save(depth);
					move(i,j,-1);
					//debug();
					q.push({i,j,-1});
					dfs(depth+1);
					q.pop();
					load(depth);
				}
			}
		}
	}
}
int main(){
	cin>>n;
	for(int i=0;i<5;i++){
		for(int j=0;j<8;j++){
			int x=read();
			if(x==0){
				break;
			}
			mp[i][j]=x;
		}
	}
	//move(3,0,1);
	//debug();
	dfs(0);
	
	cout<<"-1"<<endl;
	return 0;
}
```