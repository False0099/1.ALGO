# Monkey King

## 题面翻译

#### 题目描述

曾经在一个森林中居住着 $N$ 只好斗的猴子。在最初他们我行我素，互不认识。但是猴子们不能避免争吵，且两只猴子只会在不认识对方时发生争吵，当争吵发生时，双方会邀请它们各自最强壮的朋友并发起决斗（决斗的为各自最强壮的朋友）。当然，在决斗之后两只猴子和他们各自的伙伴都认识对方了（成为朋友），虽然他们曾经有过冲突，但是他们之间绝不会再发生争吵了。

假设每只猴子有一个强壮值，强壮值将在一场决斗后减少为原先的一半（例如  $10$ 会减少到  $5$，而  $5$ 会减少到  $2$，即向下取整）。

我们也假设每只猴子都认识它自己（是自己的朋友）。即当他是他朋友中最强壮的，他自己就会去决斗。

#### 输入格式

有多组数据，每一组数据有两部分。

第一部分：第一行包含一个整数 $N$ 表示猴子的数量。后为 $N$ 行，每行一个数字为第 $i$ 只猴子的强壮值  $s_{i}$。

第二部分：第一行包含一个整数 $M$ 表示发生了 $M$ 次冲突。后为 $M$ 行，每行两个整数 $x$ 和 $y$，表示第 $x$ 只猴子和第 $y$ 只猴子之间发生了冲突。

#### 输出格式

对于每次冲突，如果两只猴子认识对方，输出 `-1`，否则输出决斗后他们朋友中最强壮的猴子的强壮值。

#### 说明/提示

$N,M\leq 100000$，$s_{i}\leq 32768$

## 题目描述

Once in a forest, there lived N aggressive monkeys. At the beginning, they each does things in its own way and none of them knows each other. But monkeys can't avoid quarrelling, and it only happens between two monkeys who does not know each other. And when it happens, both the two monkeys will invite the strongest friend of them, and duel. Of course, after the duel, the two monkeys and all of there friends knows each other, and the quarrel above will no longer happens between these monkeys even if they have ever conflicted.


Assume that every money has a strongness value, which will be reduced to only half of the original after a duel (that is, 10 will be reduced to 5 and 5 will be reduced to 2).


And we also assume that every monkey knows himself. That is, when he is the strongest one in all of his friends, he himself will go to duel.

## 输入格式

There are several test cases, and each case consists of two parts.


First part: The first line contains an integer N (N<=100,000), which indicates the number of monkeys. And then N lines follows. There is one number on each line, indicating the strongness value of ith monkey (<=32768).


Second part: The first line contains an integer M (M<=100,000), which indicates there are M conflicts happened. And then M lines follows, each line of which contains two integers x and y, indicating that there is a conflict between the Xth monkey and Yth.



## 输出格式

For each of the conflict, output -1 if the two monkeys know each other, otherwise output the strength value of the strongest monkey among all of its friends after the duel.

## 样例 #1

### 样例输入 #1

```
5
20
16
10
10
4
5
2 3
3 4
3 5
4 5
1 5
```

### 样例输出 #1

```
8
5
5
-1
10
```

## 提示

题目可能有多组数据

## 题解
我们这一题依然是我们左偏堆的标准模板：合并两个堆，删除堆顶元素，添加一个新元素
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h> 
using namespace std;
inline int read(){//读入优化 
    int x=0,f=1;
    char ch=getchar();
    while (ch<'0'||ch>'9') {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9') {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
const int maxn=100010;//n的最大值 
int n,m,L[maxn],R[maxn],key[maxn],npl[maxn],fa[maxn];
//L为左子树编号，R为右子树编号，key为能力值，npl请见上面，fa为并查集数组 
inline int getf(int o) { 
    return o==fa[o] ? o : fa[o]=getf(fa[o]);
    //路径压缩更快 
}
inline int join(int a,int b) {
	//合并函数 
    if (!a) return b;//判断是否为空 
    if (!b) return a;
    if (key[a]<key[b]) swap(a,b);//维护堆性质 
    R[a]=join(R[a],b);//将b合并到a的右子树 
    if (npl[R[a]]>npl[L[a]]) swap(L[a],R[a]);
	//维护左偏树性质，npl[r]<=npl[l] 
    npl[a]=npl[R[a]]+1;//获得npl值 
    return a;//返回新根编号 
}
inline void work(int a,int b) {
    a=getf(a);b=getf(b);//找根 
    if (a==b) {//已经是朋友 
        puts("-1");
        //不打了 
        return;
    }
    int rt,art,brt;
    //a所属的左偏树的操作 
    key[a]>>=1;//减半 
    rt=join(L[a],R[a]);//合并左右子树 
    L[a]=R[a]=npl[a]=0;//将根节点断掉 
    art=join(rt,a);//重新合并旧根
    fa[rt]=fa[a]=art; 
    //为了路径压缩，要将旧根和子树合并的根都指向新根 
    key[b]>>=1;
    rt=join(L[b],R[b]);
    fa[L[b]]=fa[R[b]]=rt;
    L[b]=R[b]=npl[b]=0;
    brt=join(rt,b);
    fa[rt]=fa[b]=brt;
    //同a的操作 
    rt=join(art,brt);//合并两棵左偏树 
    fa[art]=fa[brt]=rt;
    //将两个旧根指向新根 
    printf("%d\n",key[rt]);
}
int main(){
    while (~scanf("%d",&n)) {//多组数据 
        npl[0]=-1;//特殊处理 
        for (register int i=1;i<=n;++i) {
        	//初始化 
            L[i]=R[i]=npl[i]=0;
            fa[i]=i;
            key[i]=read();
        }
        m=read();
        for (register int i=1;i<=m;++i) 
            work(read(),read());//猴子打架 
    }
}
```