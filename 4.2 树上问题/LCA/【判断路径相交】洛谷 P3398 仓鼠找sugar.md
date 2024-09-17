# 仓鼠找 sugar

## 题目描述

小仓鼠的和他的基（mei）友（zi）sugar 住在地下洞穴中，每个节点的编号为 $1\sim n$。地下洞穴是一个树形结构。这一天小仓鼠打算从从他的卧室（$a$）到餐厅（$b$），而他的基友同时要从他的卧室（$c$）到图书馆（$d$）。他们都会走最短路径。现在小仓鼠希望知道，有没有可能在某个地方，可以碰到他的基友？


小仓鼠那么弱，还要天天被 zzq 大爷虐，请你快来救救他吧！

## 输入格式

第一行两个正整数 $n$ 和 $q$，表示这棵树节点的个数和询问的个数。

接下来 $n-1$ 行，每行两个正整数 $u$ 和 $v$，表示节点 $u$ 到节点 $v$ 之间有一条边。

接下来 $q$ 行，每行四个正整数 $a$、$b$、$c$ 和 $d$，表示节点编号，也就是一次询问，其意义如上。

## 输出格式

对于每个询问，如果有公共点，输出大写字母 `Y`；否则输出 `N`。

## 样例 #1

### 样例输入 #1

```
5 5
2 5
4 2
1 3
1 4
5 1 5 1
2 2 1 4
4 1 3 4
3 1 1 5
3 5 1 4
```

### 样例输出 #1

```
Y
N
Y
Y
Y
```

## 提示

**本题时限 1 s，内存限制 128 M，因新评测机速度较为接近 NOIP 评测机速度，请注意常数问题带来的影响。**


$20\%$ 的数据 $n, q\le200$。

$40\%$ 的数据 $n, q\le 2\times10^3$。

$70\%$ 的数据 $n, q\le 5\times10^4$。

$100\%$ 的数据 $1\le n, q\le10^5$。

## 题解
线段相交-》点在路径上->点在上升部分 (a->lca)/点在下降福分 (lca->b)->a 和点的 lca=点，点和 lca 的 lca=lca。

本题的关键在于根据我们的图形找到我们的结论，我们如果进行我们的暴力，我们就对我们的每一条路径都打上我们的标记，然后把我们的另一个遍历时再去判断。

我们有结论：如果我们两个**路径之间有交点**，那么我们两个路径的 `lca` 必然满足，**`a` 的 lca 在 `b` 的路径上**，**或者 `b` 的 lca 在 a 的路径上**。

然后我们的问题就变成判断我们某一个点是否在我们的路径上，又因为我们的路径可以分为我们的上升和下降两种情况，所以我们又可以把我们的问题划分为我们的子问题：

我们判断我们的一个点是否在我们一个上升路径上，我们有两种方法，

方法一：如果三个点在一个链上，那么我们一定满足 `a` 和 `b` 的 `lca=b`, `b` 和 `c` 的 `lca=c`。

方法二：我们中间点到另外两个点的距离和就等于我们的另外两个点的距离。而我们树上任意两个点的距离，我们可以利用类似于**树上差分的思想**：我们的 $dist(a,b)=dep[a]+dep[b]-dep[lca(a,b)]-dep[fa[lca(a,b)]]$


```
#include <bits/stdc++.h>
using namespace std;
struct Tree {
    int n;
    vector<vector<int>> ver, val;
    vector<int> lg, dep;
    Tree(int n) {
        this->n = n;
        ver.resize(n + 1);
        val.resize(n + 1, vector<int>(30));
        lg.resize(n + 1);
        dep.resize(n + 1);
        for (int i = 1; i <= n; i++) { //预处理 log
            lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
        }
    }
    void add(int x, int y) { // 建立双向边
        ver[x].push_back(y);
        ver[y].push_back(x);
    }
    void dfs(int x, int fa) {
        val[x][0] = fa; // 储存 x 的父节点
        dep[x] = dep[fa] + 1;
        for (int i = 1; i <= lg[dep[x]]; i++) {
            val[x][i] = val[val[x][i - 1]][i - 1];
        }
        for (auto y : ver[x]) {
            if (y == fa) continue;
            dfs(y, x);
        }
    }
    int lca(int x, int y) {
        if (dep[x] < dep[y]) swap(x, y);
        while (dep[x] > dep[y]) {
            x = val[x][lg[dep[x] - dep[y]] - 1];
        }
        if (x == y) return x;
        for (int k = lg[dep[x]] - 1; k >= 0; k--) {
            if (val[x][k] == val[y][k]) continue;
            x = val[x][k];
            y = val[y][k];
        }
        return val[x][0];
    }
    int calc(int x, int y) { // 倍增查询两点间距离
        return dep[x] + dep[y] - 2 * dep[lca(x, y)];
    }
    void work(int root = 1) { // 在此初始化
        dfs(root, 0);
    }
};
int main(){
	int n,q;
	cin>>n>>q;
	Tree Tr=Tree(n);
	for(int i=0;i<n-1;i++){
		int a,b;
		cin>>a>>b;
		Tr.add(a,b);
	}
	Tr.work();
	while(q--){
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		if(Tr.calc(a,b)+Tr.calc(c,d)>=Tr.calc(a,c)+Tr.calc(b,d)){
			cout<<"Y"<<endl;
		}else{
			cout<<"N"<<endl;
		}
	}
		
}
```