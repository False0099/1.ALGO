
(树链剖分清纯迷你版)
lql 屋前有一株橘子树，每年秋天，树上长了许多橘子。lql 很喜欢橘子。树上有_N_个节点，lql 给它们编号1到_N_，根的编号永远是1.每个节点上最多结一个橘子。lql 想要了解某一个子树上一共结了多少橘子。

现在的问题是不断会有新的橘子长出来,lql也随时可能摘掉一个橘子吃掉。你能帮助lql吗?

## Input

输入数据：第一行包含一个整数_N_（_N_ <= 100000）,表示树上节点的数目。  
接下来_N_-1行，每行包含2个整数_u_和_v_，表示_u_和_v_是连在一起的。  
下一行包含一个整数_M_（_M_ ≤ 100,000）.  
接下来_M_行包含下列两种命令之一：  
"**C _x_**" 表示某个节点上的橘子发生了变化，如果原来没有橘子，则现在长出了一个橘子；如果原来有橘子，则是lql把它吃了。  
"**Q _x_**" 表示查询_x_节点上的子树上的橘子有多少。包含节点_x_.

## Output

对于每次查询，输出其结果。

## Sample Input

3
1 2
1 3
3
Q 1
C 2
Q 1

Sample Output

3
2

注意

注意, 是多组输入. 此题卡 vector 常数  
注意, 是多组输入. 此题卡 vector 常数  
注意, 是多组输入. 此题卡 vector 常数

## 题解
我们发现，我们本题的操作无非于：单点更新，区域查询，是我们树状数组的控制范围，但是我们现在的输入不是一个数组了，而是一棵树了。所以我们要对一颗树进行深搜，然后将深搜的顺序重新标上号，
注意：只有后序遍历才能保证在最后的 DFS 序中，一个节点的子孙节点都会在我们该区间的前面。

然后放到一个数组中，记下每一个分支的起点和总店，然后就可以用树状数组了。

```cpp
#include <iostream>

using namespace std;

int n, m, s, t, x, id = 0;
int c[100001], start[100001], _end[100001];
char cmd;

struct TreeNode{
    int forkno;
    TreeNode* next;
}tree[100001];

inline int min(int x, int y){return x<y?x:y;}

inline int lowbit(int x){return x&(-x);}

void add(int x, int v)
{
    for(int i=x;i<=n;i+=lowbit(i))
        c[i] += v;
}

int sum(int x)
{
    int s = 0;
    for(int i=x;i;i-=lowbit(i))
        s += c[i];
    return s;
}

void dfs(int pos)
{
    start[pos] = ++id;
    add(id, 1);
    TreeNode* p = tree[pos].next;
    while(p)
    {
        if(start[p->forkno]==0) dfs(p->forkno);
        p = p->next;
    }
    _end[pos] = id;
}

int main()
{
    scanf("%d", &n);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d", &s, &t);
        TreeNode* p = new TreeNode;
        p->forkno = t;
        p->next = tree[s].next;
        tree[s].next = p;

        TreeNode* q = new TreeNode;
        q->forkno = s;
        q->next = tree[t].next;
        tree[t].next = q;
    }
    dfs(1);
    scanf("%d", &m);
    for(int i=0;i<m;i++)
    {
        getchar();
        scanf("%c%d", &cmd, &x);
        if(cmd=='C')
        {
            int _sum = sum(start[x])-sum(start[x]-1);
            if(_sum) add(start[x], -1);
            else add(start[x], 1);
        }
        else
        {
            int _sum = sum(_end[x]) - sum(start[x]-1);
            printf("%d\n", _sum);
        }
    }
    return 0;
}


```