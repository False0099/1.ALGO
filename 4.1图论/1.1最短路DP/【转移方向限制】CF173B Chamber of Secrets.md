# Chamber of Secrets

## 题面翻译

**“密室再次被打开了。”**——这个消息传遍了霍格沃茨，而一些学生因为看到蛇怪而被石化。虽然邓布利多被迫离开了学校，但哈利正尝试进入密室。而这对伏地魔可不是什么好消息。他不希望任何人进入密室。因为他正在吸取金妮的灵魂。

密室是一个 $n×m$ 的矩形网格，其中一些单元格有柱子。光线（蛇怪的凝视）可以穿过柱子而不改变方向。但是通过一些魔咒，我们可以让柱子在接收光线时反射所有光线向四个方向射去。如下图所示。

左边光线穿过没有施魔法的柱子，右边光线穿过施魔法的柱子，效果如图。蛇怪在密室的右下角，向左边凝视。据传说，直接看见蛇怪的眼睛就会马上死亡，而看到通过柱子的反射光线就会被石化。我们知道，密室的入口在左上角，而进入的人必须注视他所要移动的方向。图片就是第一个样例。

给定密室的大小，和普通柱子的位置，伏地魔想要让你对最少的柱子施法，**使所有人不能进入密室**；或者表示不能完成保护密室的任务。

**输入格式：**

输入的第一行包含两个整数 $n$ 和 $m$ $(2<=N,M<=1000)$ 接下来 $n$ 行每行包含 $m$ 个字符。每个字符都是"."或"#"。表示密室的一个单元格。如果为"."表示为空，如果为"#"表示有柱子。

**输出格式：**

输出所需要施法的柱子在最小值，如果不可能完成，则输出"$-1$"。

**说明：**

图片为样例解释，将两根柱子都施魔法才可以阻止哈利进入密室。

## 题目描述

"The Chamber of Secrets has been opened again" — this news has spread all around Hogwarts and some of the students have been petrified due to seeing the basilisk. Dumbledore got fired and now Harry is trying to enter the Chamber of Secrets. These aren't good news for Lord Voldemort. The problem is, he doesn't want anybody to be able to enter the chamber. The Dark Lord is going to be busy sucking life out of Ginny.

The Chamber of Secrets is an $ n×m $ rectangular grid in which some of the cells are columns. A light ray (and a basilisk's gaze) passes through the columns without changing its direction. But with some spell we can make a column magic to reflect the light ray (or the gaze) in all four directions when it receives the ray. This is shown in the figure below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF173B/4953c68e7e028d0284ff8b33a4cd5ba770c5f7ef.png) The left light ray passes through a regular column, and the right ray — through the magic column. The basilisk is located at the right side of the lower right cell of the grid and is looking to the left (in the direction of the lower left cell). According to the legend, anyone who meets a basilisk's gaze directly dies immediately. But if someone meets a basilisk's gaze through a column, this person will get petrified. We know that the door to the Chamber is located on the left side of the upper left corner of the grid and anyone who wants to enter will look in the direction of its movement (in the direction of the upper right cell) from that position.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF173B/ba6e758f7280b60525185b5ab7cbc35edd6aeb84.png) This figure illustrates the first sample test. Given the dimensions of the chamber and the location of regular columns, Lord Voldemort has asked you to find the minimum number of columns that we need to make magic so that anyone who wants to enter the chamber would be petrified or just declare that it's impossible to secure the chamber.

## 输入格式

The first line of the input contains two integer numbers $ n $ and $ m $ ( $ 2<=n, m<=1000 $ ). Each of the next $ n $ lines contains $ m $ characters. Each character is either "." or "\#" and represents one cell of the Chamber grid. It's "." if the corresponding cell is empty and "\#" if it's a regular column.

## 输出格式

Print the minimum number of columns to make magic or -1 if it's impossible to do.

## 样例 #1

### 样例输入 #1

```
3 3
.#.
...
.#.
```

### 样例输出 #1

```
2
```

## 样例 #2

### 样例输入 #2

```
4 3
##.
...
.#.
.#.
```

### 样例输出 #2

```
2
```

## 提示

The figure above shows the first sample test. In the first sample we should make both columns magic. The dragon figure represents the basilisk and the binoculars represent the person who will enter the Chamber of secrets. The black star shows the place where the person will be petrified. Yellow lines represent basilisk gaze moving through columns.

## 题解
我们本题可以通过我们的 01 BFS 来进行，我们对于每一个点，我们考虑**它是由什么方向转移过来的**，然后我们下一步转移到下一个点应该怎么转移。我们每一次，都去枚举转移我们的所有点，然后我们就可以有我们的结果如下：
```
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1003

int dis[maxn][maxn][4];
string mp[maxn];

struct st
{
    int x, y, d;
    st(int X, int Y, int D):x(X), y(Y), d(D) {}
};

deque<st> q;
int dx[]={1, -1, 0, 0};
int dy[]={0, 0, 1, -1};
#define chk(i, j) ((i)&&(j)&&(i<=n)&&(j<=m))
#define mp(i, j) mp[i][j-1]

/*
   ^  
   1
<3   2>
   0
   v 
*/

void bfs(int n, int m)
{
    memset(dis, 0x3f, sizeof dis);
    q.emplace_back(1, 1, 2);
    dis[1][1][2]=0;
    while(!q.empty())
    {
        auto [x, y, p]=q.front();
        q.pop_front();
        if(!(dis[x+dx[p]][y+dy[p]][p]<=dis[x][y][p]||!chk(x+dx[p], y+dy[p])))
        {
            dis[x+dx[p]][y+dy[p]][p]=dis[x][y][p];
            q.emplace_front(x+dx[p], y+dy[p], p);
        }
        if(mp(x, y)=='#')
            for(int i=0;i<=3;i++)
            {
                if(i==p) continue;
                if(dis[x+dx[i]][y+dy[i]][i]<=dis[x][y][p]+1||!chk(x+dx[i], y+dy[i])) continue;
                dis[x+dx[i]][y+dy[i]][i]=dis[x][y][p]+1;
                q.emplace_back(x+dx[i], y+dy[i], i);
            }
    }
}

int main()
{
    int n, m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>mp[i];
    bfs(n, m+1);
    cout<<(dis[n][m+1][2]==0x3f3f3f3f?-1:dis[n][m+1][2]);
}
```
```