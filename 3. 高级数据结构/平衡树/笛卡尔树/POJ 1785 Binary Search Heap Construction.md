Read the statement of problem G for the definitions concerning trees. In the following we define the basic terminology of heaps. A heap is a tree whose internal nodes have each assigned a priority (a number) such that the priority of each internal node is less than the priority of its parent. As a consequence, the root has the greatest priority in the tree, which is one of the reasons why heaps can be used for the implementation of priority queues and for sorting.  
  
A binary tree in which each internal node has both a label and a priority, and which is both a binary search tree with respect to the labels and a heap with respect to the priorities, is called a treap. Your task is, given a set of label-priority-pairs, with unique labels and unique priorities, to construct a treap containing this data.  

Input

The input contains several test cases. Every test case starts with an integer n. You may assume that 1<=n<=50000. Then follow n pairs of strings and numbers l1/p1,...,ln/pn denoting the label and priority of each node. The strings are non-empty and composed of lower-case letters, and the numbers are non-negative integers. The last test case is followed by a zero.

Output

For each test case output on a single line a treap that contains the specified nodes. A treap is printed as (< left sub-treap >< label >/< priority >< right sub-treap >). The sub-treaps are printed recursively, and omitted if leafs.

Sample

|Inputcopy|Outputcopy|
|---|---|
|7 a/7 b/6 c/5 d/4 e/3 f/2 g/1<br>7 a/1 b/2 c/3 d/4 e/5 f/6 g/7<br>7 a/3 b/6 c/4 d/7 e/2 f/5 g/1<br>0|(a/7(b/6(c/5(d/4(e/3(f/2(g/1)))))))<br>(((((((a/1)b/2)c/3)d/4)e/5)f/6)g/7)<br>(((a/3)b/6(c/4))d/7((e/2)f/5(g/1)))|


## 题解
```cpp
#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
 
using namespace std;
const int N=500010;
const int INF=~0U>>1;
 
struct node
{
    int fix;
    int pre,l,r;
    char str[10];
    void clear()
    {
        pre=l=r=0;
    }
    bool operator < (node t) const
    {
        return strcmp(str,t.str)<0;
    }
};
 
node T[N];
 
void Init(int n)
{
    for(int i=0; i<=n; i++)
        T[i].clear();
    T[0].fix=INF;
}
 
int Build(int n)
{
    for(int i=1; i<=n; i++)
    {
        int j=i-1;
        while(T[j].fix<T[i].fix)
            j=T[j].pre;
        T[i].l=T[j].r;
        T[j].r=i;
        T[i].pre=j;
    }
    return T[0].r;
}
 
void dfs(int cur)
{
    if(cur==0) return;
    printf("(");
    dfs(T[cur].l);
    printf("%s/%d",T[cur].str,T[cur].fix);
    dfs(T[cur].r);
    printf(")");
}
 
int main()
{
    int n;
    char str[105];
    while(scanf("%d",&n),n)
    {
        Init(n);
        for(int i=1; i<=n; i++)
        {
            scanf("%s",str);
            sscanf(str,"%[^/]/%d",T[i].str,&T[i].fix);
        }
        sort(T+1,T+n+1);
        int root=Build(n);
        dfs(root);
        puts("");
    }
    return 0;
}
```