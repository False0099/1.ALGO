There is going to be a party to celebrate the 80-th Anniversary of the Ural State University. The University has a hierarchical structure of employees. It means that the supervisor relation forms a tree rooted at the rector V. E. Tretyakov. In order to make the party funny for every one, the rector does not want both an employee and his or her immediate supervisor to be present. The personnel office has evaluated conviviality of each employee, so everyone has some number (rating) attached to him or her. Your task is to make a list of guests with the maximal possible sum of guests' conviviality ratings.  

  
  
有个公司要举行一场晚会。为了让到会的每个人不受他的直接上司约束而能玩得开心，公司领导决定：如果邀请了某个人，那么一定不会再邀请他的直接的上司，但该人的上司的上司，上司的上司的上司……都可以邀请。已知每个人最多有唯一的一个上司。  
已知公司的每个人参加晚会都能为晚会增添一些气氛，求一个邀请方案，使气氛值的和最大。

## Input

Employees are numbered from 1 to N. A first line of input contains a number N. 1 <= N <= 6 000. Each of the subsequent N lines contains the conviviality rating of the corresponding employee. Conviviality rating is an integer number in a range from -128 to 127. After that go T lines that describe a supervisor relation tree. Each line of the tree specification has the form:  
L K  
It means that the K-th employee is an immediate supervisor of the L-th employee. Input is ended with the line  
0 0 <>  
注意包含多组输入  
第1行一个整数N表示公司的人数。  
接下一行N个整数。第i行的数表示第i个人的气氛值x（-128<=x<=127）  
接N-1下来每行两个整数L,K。表示第K个人是第L个人的上司。  
输入以两个0结尾

## Output

Output should contain the maximal sum of guests' ratings.  
一个数，最大的气氛值和。

## Sample Input

7
1
1
1
1
1
1
1
1 3
2 3
6 4
7 4
4 5
3 5
0 0

## Sample Output

5

## 题解
我们本题和我们之前的没有上司的舞会是本质相同的题目，我们只需要照抄代码即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=10000;
int happy[M],head[M],shu[M][2];
struct N
{
    int to,nex;
}edge[M];
int cnt=0;
void add_edge(int x1,int x2)
{
    edge[++cnt].to=x2;
    edge[cnt].nex=head[x1];
    head[x1]=cnt;
}
bool is_son[M];
void treaDP(int S)
{
    shu[S][0]=0;
    shu[S][1]=happy[S];
    int m;
    for(int i=head[S];i!=-1;i=edge[i].nex)
    {
        m=edge[i].to;
        treaDP(m);
        shu[S][0]+=max(shu[m][0],shu[m][1]);
        shu[S][1]+=shu[m][0];
    }
}
int main()
{
    int n,m,k,x1,x2,x3,ans1,ans2,S;
    while(scanf("%d",&n)==1)
    {
        cnt=0;
        memset(head,-1,sizeof(head));
        //memset(shu,0,sizeof(shu));
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&happy[i]);
        }
        for(int i=1;i<=n-1;i++)
        {
            scanf("%d%d",&x1,&x2);
            is_son[x1]=1;
            add_edge(x2,x1);
        }
        scanf("%d%d",&x1,&x2);
        for(int i=1;i<=n;i++)
        {
            if(!is_son[i])
            {
                S=i;
                break;
            }
        }
        treaDP(S);
        cout<<max(shu[S][0],shu[S][1])<<endl;
    }
}
```