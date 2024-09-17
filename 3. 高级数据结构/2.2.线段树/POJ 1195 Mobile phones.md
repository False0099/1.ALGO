Tampere 地区的4G 手机基站运行原理如下：信号覆盖区域被划分为若干个正方形小区域，整个信号覆盖区域是一个由若干正方形小区域组成的 S * S 矩阵（下标从 0 到 S-1）。每个小区域包含一个基站，每个基站所连接的手机数量可能会随时变化。

输入

多组输入，每行输入一个整数 op 代表操作编号：

- 操作0: 输入一个整数 S 表示初始化一个 S * S 的空区域。
- 操作1: 输入三个整数 x,y,a 代表坐标 (x,y) 的小区域中增加了 a 个手机上线。
- 操作2: 输入四个整数 x1,y1,x2,y2 分别代表一个矩形区域的左上角坐标和右下角坐标，求区域中所有小区域在线手机数量之和。
- 操作3: 结束程序。

输出

对于每个操作2，求区域中所有小区域在线手机数量之和。

样例输入

0 4
1 1 2 3
2 0 0 2 2 
1 1 1 2
1 1 2 -1
2 1 1 2 3 
3

样例输出

3
4

提示

1 <= s <= 1024

每个小区域的同时在线手机数量小于等于 32767。

指令数小于等于 60002。

每次上线的手机数量大于等于 -32768 小于等于 32767。

整个信号覆盖区域的同时在线手机量小于等于 2^30。

## 题解
虽然但是，这一题给定我们一个二维平面，然后我们由单点修改和我们的区间求和，所以我们就可以用一个二维树状数组来进行维护，这样也许会更简单一点。
二维线段树的实现，我们可以选择用 1. 树套数 2.四叉树的方法来实现。我们二维线段树同样可以采取类似的思想。既然一个区间我们将其分割成左右两个区间，运用类比的思想，我们可以把一个矩形分割成左上，右上，左下，右下四个小矩形分别维护。就像这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/5nf8ltfr.png)

```cpp
#include<bits/stdc++.h>
#define MAXN 1010
using namespace std;
typedef long long ll;
struct node{
    int x1, y1, x2, y2;
    ll tag_ass, tag_add, sum;
};
node tree[MAXN * MAXN << 2];
int n, m, q;
ll a[MAXN][MAXN];
/*
    四叉树时：
        x = 0 ——> 左上方子矩阵
        x = 1 ——> 右上方子矩阵
        x = 2 ——> 左下方子矩阵
        x = 3 ——> 右下方子矩阵
    二叉树时：
        x = 0 ——> 左/上方子矩阵
        x = 1 ——> 右/下方子矩阵
*/
int get_son(int p, int x){ return p * 4 - 2 + x; }
/*
    op = 0 ——> 二叉树
    op = 1 ——> 四叉树
*/
void push_up(int now, int op){
    tree[now].sum = tree[get_son(now, 0)].sum + tree[get_son(now, 1)].sum;
    if(op == 0) return ;
    for(int i = 2; i < 4; i++) tree[now].sum += tree[get_son(now, i)].sum;
}
void push_down(int now){
    if(tree[now].tag_add != 0){
        if(tree[now].y1 == tree[now].y2){
            int son0 = get_son(now, 0), son1 = get_son(now, 1);
            tree[son0].tag_add += tree[now].tag_add;
            tree[son1].tag_add += tree[now].tag_add;
            tree[son0].sum += (tree[son0].x2 - tree[son0].x1 + 1) * tree[now].tag_add;
            tree[son1].sum += (tree[son1].x2 - tree[son1].x1 + 1) * tree[now].tag_add;
        }else if(tree[now].x1 == tree[now].x2){
            int son0 = get_son(now, 0), son1 = get_son(now, 1);
            tree[son0].tag_add += tree[now].tag_add;
            tree[son1].tag_add += tree[now].tag_add;
            tree[son0].sum += (tree[son0].y2 - tree[son0].y1 + 1) * tree[now].tag_add;
            tree[son1].sum += (tree[son1].y2 - tree[son1].y1 + 1) * tree[now].tag_add;
        }else{
            for(int i = 0; i < 4; i++){
                int son = get_son(now, i), s = (tree[son].x2 - tree[son].x1 + 1) * ((tree[son].y2 - tree[son].y1 + 1));
                tree[son].sum += s * tree[now].tag_add;
                tree[son].tag_add += tree[now].tag_add;
            }
        }
        tree[now].tag_add = 0;
    }
    if(tree[now].tag_ass >= 0){
        if(tree[now].x1 == tree[now].x2){
            int son0 = get_son(now, 0), son1 = get_son(now, 1);
            tree[son0].tag_ass = tree[now].tag_ass;
            tree[son1].tag_ass = tree[now].tag_ass;
            tree[son0].tag_add = tree[son1].tag_add = 0;
            tree[son0].sum = (tree[son0].y2 - tree[son0].y1 + 1) * tree[now].tag_ass;
            tree[son1].sum = (tree[son1].y2 - tree[son1].y1 + 1) * tree[now].tag_ass;
        }else if(tree[now].y1 == tree[now].y2){
            int son0 = get_son(now, 0), son1 = get_son(now, 1);
            tree[son0].tag_ass = tree[now].tag_ass;
            tree[son1].tag_ass = tree[now].tag_ass;
            tree[son0].tag_add = tree[son1].tag_add = 0;
            tree[son0].sum = (tree[son0].x2 - tree[son0].x1 + 1) * tree[now].tag_ass;
            tree[son1].sum = (tree[son1].x2 - tree[son1].x1 + 1) * tree[now].tag_ass;
        }else{
            for(int i = 0; i < 4; i++){
                int son = get_son(now, i), s = (tree[son].x2 - tree[son].x1 + 1) * ((tree[son].y2 - tree[son].y1 + 1));
                tree[son].tag_add = 0;
                tree[son].sum = s * tree[now].tag_ass;
                tree[son].tag_ass = tree[now].tag_ass;
            }
        }
        tree[now].tag_ass = -1;
    }
}
// 建树
void build(int now, int x1, int y1, int x2, int y2){
    tree[now].x1 = x1; tree[now].y1 = y1; tree[now].x2 = x2; tree[now].y2 = y2;
    tree[now].tag_ass = -1; tree[now].tag_add = 0;
    if(x1 == x2 && y1 == y2){
        tree[now].sum = a[x1][y2];
        return ;
    }
    int midx = (x1 + x2) >> 1, midy = (y1 + y2) >> 1;
    if(x1 == x2){
        build(get_son(now, 0), x1, y1, x2, midy); build(get_son(now, 1), x1, midy + 1, x2, y2);
        push_up(now, 0);
    }else if(y1 == y2){
        build(get_son(now, 0), x1, y1, midx, y2); build(get_son(now, 1), midx + 1, y1, x2, y2);
        push_up(now, 0);
    }else{
        build(get_son(now, 0), x1, y1, midx, midy);
        build(get_son(now, 1), midx + 1, y1, x2, midy);
        build(get_son(now, 2), x1, midy + 1, midx, y2);
        build(get_son(now, 3), midx + 1, midy + 1, x2, y2);
        push_up(now, 1);
    }
}
// 矩阵加法
void update_add(int now, int x1, int y1, int x2, int y2, int val){
    if(tree[now].x1 > x2 || tree[now].x2 < x1 || tree[now].y1 > tree[now].y2 || tree[now].y2 < tree[now].y1) return ;
    if(tree[now].x1 >= x1 && tree[now].x2 <= x2 && tree[now].y1 >= y1 && tree[now].y2 <= y2){
        tree[now].tag_add += val;
        if(tree[now].tag_ass >= 0) tree[now].tag_ass += val;
        tree[now].sum += (tree[now].x2 - tree[now].x1 + 1) * (tree[now].y2 - tree[now].y1 + 1) * val;
        return ;
    }
    push_down(now);
    if(tree[now].x1 == tree[now].x2 || tree[now].y1 == tree[now].y2){
        update_add(get_son(now, 0), x1, y1, x2, y2, val);
        update_add(get_son(now, 1), x1, y1, x2, y2, val);
        push_up(now, 0);
    }else{
        for(int i = 0; i < 4; i++) update_add(get_son(now, i), x1, y1, x2, y2, val);
        push_up(now, 1);
    }
}
// 矩阵赋值
void update_ass(int now, int x1, int y1, int x2, int y2, int val){
    if(tree[now].x1 > x2 || tree[now].x2 < x1 || tree[now].y1 > tree[now].y2 || tree[now].y2 < tree[now].y1) return ;
    if(tree[now].x1 >= x1 && tree[now].x2 <= x2 && tree[now].y1 >= y1 && tree[now].y2 <= y2){
        tree[now].tag_add = 0;
        tree[now].tag_ass = val;
        tree[now].sum = (tree[now].x2 - tree[now].x1 + 1) * (tree[now].y2 - tree[now].y1 + 1) * val;
        return ;
    }
    push_down(now);
    if(tree[now].x1 == tree[now].x2 || tree[now].y1 == tree[now].y2){
        update_ass(get_son(now, 0), x1, y1, x2, y2, val);
        update_ass(get_son(now, 1), x1, y1, x2, y2, val);
        push_up(now, 0);
    }else{
        for(int i = 0; i < 4; i++) update_ass(get_son(now, i), x1, y1, x2, y2, val);
        push_up(now, 1);
    }
}
// 查询矩阵中所有元素的和
ll query(int now, int x1, int y1, int x2, int y2){
    if(tree[now].x1 > x2 || tree[now].x2 < x1 || tree[now].y1 > tree[now].y2 || tree[now].y2 < tree[now].y1) return 0;
    if(tree[now].x1 >= x1 && tree[now].x2 <= x2 && tree[now].y1 >= y1 && tree[now].y2 <= y2){
        return tree[now].sum;
    }
    push_down(now);
    if(tree[now].x1 == tree[now].x2 || tree[now].y1 == tree[now].y2){
        return query(get_son(now, 0), x1, y1, x2, y2) + query(get_son(now, 1), x1, y1, x2, y2);
    }else{
        ll res = 0;
        for(int i = 0; i < 4; i++) res += query(get_son(now, i), x1, y1, x2, y2);
        return res;
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            scanf("%lld",&a[i][j]);
        }
    }
    build(1, 1, 1, n, m);
    scanf("%d",&q);
    for(int i = 1; i <= q; i++){
        int op, x1, y1, x2, y2;
        scanf("%d%d%d%d%d",&op,&x1,&y1,&x2,&y2);
        if(op == 1){
            ll val; scanf("%lld",&val);
            update_add(1, x1, y1, x2, y2, val);
        }else if(op == 2){
            ll val; scanf("%lld",&val);
            update_ass(1, x1, y1, x2, y2, val);
        }else printf("%lld\n",query(1, x1, y1, x2, y2));
    }
    return 0;
}
```


当然，我们也可以用我们的二维线段树来实现。二位线段树的基本结构就是在**一维的基础上增加一个线段树，实现树套数的结构**。这里以 Y 坐标为主，在 Y 坐标基础上构建 X 坐标上的数。仍然用数组去模拟树，只不过这里用二维数组修改某个结点