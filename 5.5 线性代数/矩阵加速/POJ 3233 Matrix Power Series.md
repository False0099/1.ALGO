# 
## 题目描述
给一个n × n 的矩阵 A 和两个整数 k, m。现有 $S=A+A^2+\dots+A^k$

输出 S % m的结果（矩阵模上一个数等价于矩阵中每个元素模上这个数）

## 输入格式

输入只包含一个测试用例。输入的第一行包含三个正整数。n (n≤30)，k (k≤109)和m (m < 104)。然后跟着n每行包含n，32，768以下的非负整数，给出A按顺序排列的元素。

## 输出格式
输出S模数m以同样的方式A是给你的。
## 样例 #1

### 样例输入 #1

```
2 2 4
0 1
1 1
```

### 样例输出 #1

```
1 2
2 3
```

## 题解
一个矩阵的幂次，我们可以用快速幂来算，但若干个“等比“加起来，我们就需要把S看成是递推式，令$S(k)=A+A^2+\dots+A^k$,那么我们关于S的递推式也是可以写的，即$F_{k}=F_{k-1}+A^k$,于是我们仿照之前的方法，可以写出
$[F_{k},E]=[F_{k-1},E]S=\dots=[F_{0},E]S^k$
其中E是单位矩阵，使用它是为了凑出矩阵S，展开，我们就能得到S是一个分块矩阵，
$S=\left [ \begin{matrix}A& O \\A& E \\\end{matrix} \right ]$
我们再用S去进行进行矩阵快速幂，最后我们的左下角就是我们要求的答案。
## 代码
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
 
using namespace std;
 
int n,k,m;
struct Mat
{
    int mat[100][100];
};
Mat a;
 
Mat operator * (Mat a, Mat b) {
    Mat mm;
    memset(mm.mat, 0, sizeof(mm.mat));
    int i, j, k;
        for(i = 0; i < 2*n; ++i) {
           // if(a.mat[i][k] <= 0)  continue;    //***
            for(j = 0; j < 2*n; ++j) {
               // if(b.mat[k][j] <= 0)    continue;    //***
               for(k=0;k<2*n;++k)
                {
                    mm.mat[i][j] =(mm.mat[i][j]+(a.mat[i][k] * b.mat[k][j])%m)%m;
                }
            }
        }
    return mm;
}
 
Mat operator ^ (Mat a, int k) {
    Mat m,s;
    memset(s.mat,0,sizeof(s.mat));
    int i,j;
    for(i = 0; i < 2*n; ++i)
        for(j = 0; j < 2*n; ++j)
            m.mat[i][j] = (i == j);
    for( k++; k; k>>=1) {
        if(k&1) m = m*a;
         a=a*a;
    }
    return m;
}
 
int main()
{
   while(scanf("%d%d%d",&n,&k,&m)==3)
   {
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            scanf("%d",&a.mat[i][j]);
    }
 
    for(int i=0;i<n;i++)
    {
        a.mat[i+n][i+n]=a.mat[i][i+n]=1;
    }
 
    Mat sum=a^k;
    for(int i=0;i<n;i++)
    {
      sum.mat[i][i+n]--;
    }
     for(int i=0;i<n;i++)
     {
         for(int j=n;j<2*n;j++)
         {
             if(j==n)
             printf("%d",sum.mat[i][j]%m);
             else
                printf(" %d",sum.mat[i][j]%m);
         }
         puts("");
     }
   }
    return 0;
}
```