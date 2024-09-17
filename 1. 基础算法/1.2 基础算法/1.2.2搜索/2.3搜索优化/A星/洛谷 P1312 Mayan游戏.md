# [NOIP 2011 提高组] Mayan 游戏

## [[大模拟]] [[搜索]]

## 题目描述

Mayan puzzle 是最近流行起来的一个游戏。游戏界面是一个 $7$ 行 $\times5$ 列的棋盘，上面堆放着一些方块，方块不能悬空堆放，即方块必须放在最下面一行，或者放在其他方块之上。游戏通关是指在规定的步数内消除所有的方块，消除方块的规则如下：

1. 每步移动可以且仅可以沿横向（即向左或向右）拖动某一方块一格：当拖动这一方块时，如果拖动后到达的位置（以下称目标位置）也有方块，那么这两个方块将交换位置（参见输入输出样例说明中的图 $6$ 到图 $7$）；如果目标位置上没有方块，那么被拖动的方块将从原来的竖列中抽出，并从目标位置上掉落（直到不悬空，参见下面图 $1$ 和图 $2$）；

 ![](https://cdn.luogu.com.cn/upload/pic/103.png)  

2. 任一时刻，如果在一横行或者竖列上有连续三个或者三个以上相同颜色的方块，则它们将立即被消除（参见图 1 到图 3）。

 ![](https://cdn.luogu.com.cn/upload/pic/102.png) 

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

 ![](https://cdn.luogu.com.cn/upload/pic/104.png) 

样例输入的游戏局面如上面第一个图片所示，依次移动的三步是：$(2,1)$ 处的方格向右移动，$(3,1)$ 处的方格向右移动，$(3,0)$ 处的方格向右移动，最后可以将棋盘上所有方块消除。

**【数据范围】**

对于 $30\%$ 的数据，初始棋盘上的方块都在棋盘的最下面一行；

对于 $100\%$ 的数据，$0<n \le 5$。

## 题解
我们这一题通过枚举我们每一步的移动，来改变我们的状态，因此，我们对于每一步操作，要存储一个图，和我们的答案

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
#include<cstdlib>
#define ll long long
#define N 10
using namespace std;
int n,map[N][N],ans[N][5],last[N][N][N],xiao[N][N];
bool remove(){
    int flag=0;
    for(int i=1;i<=5;i++)
        for(int j=1;j<=7;j++){
            if(i-1>=1&&i+1<=5&&map[i][j]==map[i-1][j]&&map[i][j]==map[i+1][j]&&map[i][j]){
                xiao[i-1][j]=1;xiao[i+1][j]=1;xiao[i][j]=1;flag=1;
            }
            
            if(j-1>=1&&j+1<=7&&map[i][j]==map[i][j+1]&&map[i][j]==map[i][j-1]&&map[i][j]){
                xiao[i][j]=1;xiao[i][j+1]=1;xiao[i][j-1]=1;flag=1;
            }
        }
    if(!flag)return 0;
    for(int i=1;i<=5;i++)
        for(int j=1;j<=7;j++)
        if(xiao[i][j]){
            xiao[i][j]=0;
            map[i][j]=0;
        } 
    return 1;
}

bool check(){
    for(int i=1;i<=5;i++)
        if(map[i][1])return 0;
    return 1;
}
void copy(int x){
    for(int i=1;i<=5;i++)
        for(int j=1;j<=7;j++)
        last[x][i][j]=map[i][j];
}
void update(){
    for(int i=1;i<=5;i++){
        int wow=0;
        for(int j=1;j<=7;j++){
            if(!map[i][j])wow++;
            else{
                if(!wow)continue;
                map[i][j-wow]=map[i][j];
                map[i][j]=0;
            }
        }
    }
}
void move(int i,int j,int x){
    int tmp=map[i][j];
    map[i][j]=map[i+x][j];
    map[i+x][j]=tmp;
    update();
    while(remove())update();
}

void dfs(int x){
    if(check()){
        for(int i=1;i<=n;i++){
            if(i!=1)printf("\n");
            for(int j=1;j<=3;j++)
            printf("%d ",ans[i][j]);
        }
        exit(0);
    }
    if(x==n+1)return;
    copy(x);
    for(int i=1;i<=5;i++)
        for(int j=1;j<=7;j++){
            if(map[i][j]){
                if(i+1<=5&&map[i][j]!=map[i+1][j]){
                move(i,j,1);
                ans[x][1]=i-1;ans[x][2]=j-1;ans[x][3]=1;
                dfs(x+1);
                for(int i=1;i<=5;i++)
                    for(int j=1;j<=7;j++)
                    map[i][j]=last[x][i][j];
                ans[x][1]=-1;ans[x][2]=-1;ans[x][3]=-1;
            }
            if(i-1>=1&&map[i-1][j]==0){
                move(i,j,-1);
                ans[x][1]=i-1;ans[x][2]=j-1;ans[x][3]=-1;
                dfs(x+1);
                for(int i=1;i<=5;i++)
                    for(int j=1;j<=7;j++)
                    map[i][j]=last[x][i][j];
                ans[x][1]=-1;ans[x][2]=-1;ans[x][3]=-1;
            }
            }
        }
}
int main()
{
//    freopen("Manya.in","r",stdin);
//    freopen("Manya.out","w",stdout);
    n=read();
    for(int i=1;i<=5;i++){
        for(int j=1;j<=8;j++){
            int x=read();
            if(x==0)break;
            map[i][j]=x;
        }
    }
    memset(ans,-1,sizeof(ans));
    dfs(1);
    puts("-1");
    return 0;
}
```