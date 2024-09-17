You have been given a matrix $CN*M,$ each element E of $CN*M$ is positive and no more than 1000, The problem is that if there exist N numbers a1, a2, … an and M numbers b1, b2, …, bm, which satisfies that each elements in row-i multiplied with ai and each elements in column-j divided by bj, after this operation every element in this matrix is between L and U, L indicates the lowerbound and U indicates the upperbound of these elements.

Input

There are several test cases. You should process to the end of file.  
Each case includes two parts, in part 1, there are four integers in one line, N,M,L,U, indicating the matrix has N rows and M columns, L is the lowerbound and U is the upperbound (1<=N、M<=400,1<=L<=U<=10000). In part 2, there are N lines, each line includes M integers, and they are the elements of the matrix.  
  

Output

If there is a solution print "YES", else print "NO".

Sample

|Inputcopy|Outputcopy|
|---|---|
|3 3 1 6<br>2 3 4<br>8 2 6<br>5 2 9|YES|

## 题解
![[Pasted image 20231105200900.png]]
我们这一题给定了若干个不等式的形式，我们对我们的每一个 $a[i],b[j]$ 设点， 问我们满足 $n*m$ 个不等式的 A 和 B 有哪些？我们理论上是一个构造题，但这题，我们有一个 trick，就是用我们的两侧同时取对数，然后我们就变成了我们的差分约束题。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define inf 0x7fffffff
const int maxn = 405;
int  head[maxn * maxn], n, m,cnt[maxn * maxn],nm,k;
double low[maxn * maxn],l,u;
bool used[maxn * maxn];
struct Edge
{
    int to, next;
    double w;
} edge[maxn * maxn * 10];
int SPFA(int start,int n)
{
    nm = sqrt(n*1.0);
    for(int i = 0; i <= n; ++i)
    {
        low[i] = inf;
        used[i] = 0;
        cnt[i] = 0;
    }
    queue<int> a;
    used[start] = 1;
    low[start] = 0;
    a.push(start);
    while (!a.empty())
    {
        int top = a.front();
        a.pop();
        used[top]=0;
        for (int k = head[top]; k != -1; k = edge[k].next)
        {
            if (low[edge[k].to] > low[top] + edge[k].w)
            {
                low[edge[k].to] = low[top] + edge[k].w;
                if (!used[edge[k].to])
                {
                    if(++cnt[edge[k].to]>nm){return 0;}
                    used[edge[k].to] = 1;
                    a.push(edge[k].to);
                }
            }
        }
    }
    return 1;
}

void add(int a,int b,double w)
{
    edge[k].to = b;
    edge[k].w = w;
    edge[k].next = head[a];
    head[a] = k++;
}

int main()
{
    while (~scanf("%d %d %lf %lf",&n,&m,&l,&u))
    {
        double L = log(l),U = log(u);
        k = 0;
        memset(head,-1,sizeof head);
        for (int i = 0 ; i < n; i++)
        {
          for (int j = 0; j < m; j++)
          {
              double c;
              scanf("%lf",&c);
              add(j + n,i,U - log(c));
              add(i,j + n,-(L - log(c)));
          }
        }
        if(SPFA(0,n+m))
        {
            printf("YES\n");
        }
        else printf("NO\n");
    }
}

```