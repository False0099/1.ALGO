You probably know those quizzes in Sunday magazines: given the sequence 1, 2, 3, 4, 5, what is the next number? Sometimes it is very easy to answer, sometimes it could be pretty hard. Because these "sequence problems" are very popular, ACM wants to implement them into the "Free Time" section of their new WAP portal.  
ACM programmers have noticed that some of the quizzes can be solved by describing the sequence by **polynomials**. For example, the sequence 1, 2, 3, 4, 5 can be easily understood as a trivial polynomial. The next number is 6. But even more complex sequences, like 1, 2, 4, 7, 11, can be described by a polynomial. In this case, $0.5n^2-0.5.n+1$ can be used. Note that even if the members of the sequence are integers, polynomial coefficients may be any real numbers.  
  
Polynomial is an expression in the following form:  
  
  
P(n) = aD.n^D+aD-1.n^D-1+...+a1.n+a0  
  
  
. If aD <> 0, the number D is called a degree of the polynomial. Note that constant function P(n) = C can be considered as polynomial of degree 0, and the zero function P(n) = 0 is usually defined to have degree -1.  

题意：给定一串有规律的数，要求写出后面 c 个

Input

There is a single positive integer T on the first line of input. It stands for the number of test cases to follow. Each test case consists of two lines. First line of each test case contains two integer numbers S and C separated by a single space, 1 <= S < 100, 1 <= C < 100, (S+C) <= 100. The first number, S, stands for the length of the given sequence, the second number, C is the amount of numbers you are to find to complete the sequence.  
  
The second line of each test case contains S integer numbers X1, X2, ... XS separated by a space. These numbers form the given sequence. The sequence can always be described by a polynomial P(n) such that for every i, Xi = P(i). Among these polynomials, we can find the polynomial Pmin with the lowest possible degree. This polynomial should be used for completing the sequence.  

Output

For every test case, your program must print a single line containing C integer numbers, separated by a space. These numbers are the values completing the sequence according to the polynomial of the lowest possible degree. In other words, you are to print values Pmin(S+1), Pmin(S+2), .... Pmin(S+C).  
  
It is guaranteed that the results Pmin(S+i) will be non-negative and will fit into the standard integer type.  

Sample

|Inputcopy|Outputcopy|
|---|---|
|4<br>6 3<br>1 2 3 4 5 6<br>8 2<br>1 2 4 7 11 16 22 29<br>10 2<br>1 1 1 1 1 1 1 1 1 2<br>1 10<br>3|7 8 9<br>37 46<br>11 56<br>3 3 3 3 3 3 3 3 3 3|


## 题解
首先，我们的题目背景是一个拉格朗日差值多项式，即给定 $n$ 个点，能够唯一确定一个 n 次多项式，所以我们这一题当然可以采用先求出我们的多项式后再代职的方法，这么做的时间复杂度为 $o(n^3)$,思维复杂度为 $o(1)$.

但是，因为我们只需要求后面的几项，所以我们可以采用数学上的对**一个 n 长度的数列，做 $n-1$ 阶差分**，这样我们就能得到一个递推式，

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int a[120][120],m,n,i,j,t;
int main(void)
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&m,&n);
        for(i=0;i<m;i++) scanf("%d",&a[0][i]);
        //遍历到0阶的序列 
        for(i=1;i<m;i++)
        {
            for(j=0;j<m-i;j++)
            a[i][j]=a[i-1][j+1]-a[i-1][j];
        }
        //扩展0阶序列 
        for(i=1;i<=n;i++) a[m-1][i]=a[m-1][0];
        //依次向上求解，求出后面n个数的值 
        for(i=m-2;i>=0;i--)
        {
            for(j=m-i;j<m+n;j++)
            a[i][j]=a[i][j-1]+a[i+1][j-1];
        }
        for(i=m;i<m+n-1;i++) printf("%d ",a[0][i]);
        printf("%d\n",a[0][i]);
    }
    return 0;
}
```