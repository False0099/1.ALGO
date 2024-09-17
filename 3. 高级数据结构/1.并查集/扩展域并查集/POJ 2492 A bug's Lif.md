**Background**  
Professor Hopper is researching the sexual behavior of a rare species of bugs. He assumes that they feature two different genders and that they only interact with bugs of the opposite gender. In his experiment, individual bugs and their interactions were easy to identify, because numbers were printed on their backs.  
**Problem**  
Given a list of bug interactions, decide whether the experiment supports his assumption of two genders with no homosexual bugs or if it contains some bug interactions that falsify it.

## Input

The first line of the input contains the number of scenarios. Each scenario starts with one line giving the number of bugs (at least one, and up to 2000) and the number of interactions (up to 1000000) separated by a single space. In the following lines, each interaction is given in the form of two distinct bug numbers separated by a single space. Bugs are numbered consecutively starting from one.

## Output

The output for every scenario is a line containing "Scenario i : ", where i is the number of the scenario starting at 1, followed by one line saying either "No suspicious bugs found!" if the experiment is consistent with his assumption about the bugs' sexual behavior, or "Suspicious bugs found!" if Professor Hopper's assumption is definitely wrong.

## 题解
我们这一题采用扩展域并查集的思路，对于每一个编号，我们设置两个点，一个表示他是男性，另一个表示他是女性。对于每一个交配记录，我们把他们的性别进行交叉连边。并进行路径压缩，如果到最后，我们能够得到一个点的两种性别都在一个集合里，就说明有同性恋。

```cpp
#include <iostream>
#include <stdio.h>
#define MAXN 2010
using namespace std;

int pre[MAXN*2];

int find(int x){  //***递归压缩路径
    return x==pre[x]?pre[x]:pre[x]=find(pre[x]);
}

void jion(int x, int y){//**合并
    int px=find(x);
    int py=find(y);
    if(px!=py){
        pre[px]=py;
    }
}

int main(void){
    int t, m, n;
    scanf("%d", &t);
    for(int k=1; k<=t; k++){
        scanf("%d%d", &n, &m);
        for(int i=0; i<=2*n; i++){
            pre[i]=i;
        }
        int flag=0;
        while(m--){
            int x, y;
            scanf("%d%d", &x, &y);
            if(find(x)==find(y)){//先判断是不是同性，是的话直接扶她出去
                flag=1;
            }else{
                jion(x, y+n);
                jion(x+n, y);
            }
        }
        if(flag){
            printf("Scenario #%d:\nSuspicious bugs found!\n\n", k);
        }else{
            printf("Scenario #%d:\nNo suspicious bugs found!\n\n", k);
        }
    }
    return 0;
}
```