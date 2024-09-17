# 
## 题目描述
![[Pasted image 20230810174944.png]]

## 输入格式
第一行输入时一个整数t(1 <= t <= 20) ，说明有t组样例。

每组样例的第一行是整数n(1 <= n <= 15) ，说明墙的ch尺寸。

之后的n行代表了这个墙上每块砖的颜色

' y'是黄色  ' w'是白色


## 输出格式
对于每组输入，输出一行代表cww需要刷墙的最小次数。如果cww不能把所有墙都变成黄色，输出" inf"( 不包括引号)


## 样例 #1

### 样例输入 #1

```
2
3
yyy
yyy
yyy
5
wwwww
wwwww
wwwww
wwwww
wwwww
```

### 样例输出 #1

```
0
15
```

## 提示
我们首先把这个问题转换为线性方程组求解的问题，定义变量$x_{i}$，$x_{i}=1$表示第i块砖被刷了1次，$x_{i}=0$表示没有被刷。定义$a_{ij}$为第i和第j块砖之间的关系，$a_{ij}=1$表明刷i会影响到j，$a_{ij}=0$表明刷i不会影响到j，对于方砖，我们用0表示黄色，1表示白色，一块方砖的颜色，取决于它的起始颜色，和所有邻居格子的异或操作情况，这样就有n* n个方程，如下

$$
    \begin{cases}
        a_{11}x_{1} \otimes a_{12}x_{2} \otimes \dots\otimes a_{1k}x_{k}\otimes s_{1}= 0 \\
        a_{21}x_{1} \otimes a_{22}x_{2} \otimes \dots\otimes a_{2k}x_{k}\otimes s_{2}= 0 \\
        \dots\dots\dots \\
        a_{k1}x_{1} \otimes a_{k2}x_{2} \otimes \dots\otimes a_{kk}x_{k}\otimes s_{k}= 0 \\
    \end{cases}
$$

之后的任务就是解出这一个同余方程组即可。

由于异或运算满足交换律和结合律，所以我们可以按照高斯消元法逐步求解，值得注意的是，我们在消元的时候应采用异或消元而非加减消元。

## 代码
```cpp
//<span style="font-size:18px;">
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
using namespace std;
const int MAXN = 3e2+5;
const int INF = 1e9+5;
int equ, var;///equ个方程 var个变量
int a[MAXN][MAXN];///增广矩阵
int x[MAXN];///解的数目
bool free_x[MAXN];///判断是不是自由变元
int free_xx[MAXN];
int free_num;///自由变元的个数
inline int GCD(int m, int n)
{
    if(n == 0)
        return m;
    return GCD(n, m%n);
}
inline int LCM(int a, int b)
{
    return a/GCD(a,b)*b;
}
int n;
int Gauss()
{
    int Max_r;///当前列绝对值最大的存在的行
    ///col：处理当前的列
    int row = 0;
    int cnt = 0;///自由变元的编号
    for(int col=0; row<equ&&col<var; row++,col++)
    {
        Max_r = row;
        for(int i=row+1; i<equ; i++)///找当前列中最大的行
            if(abs(a[i][col]) > abs(a[Max_r][col]))
                Max_r = i;
        ///交换Max_r行 与 当前行
        if(Max_r != row)
            for(int i=0; i<var+1; i++)
                swap(a[row][i], a[Max_r][i]);

        if(a[row][col] == 0)
        {
            row--;
            free_xx[cnt++] = col;///后面的
            continue;
        }
        for(int i=row+1; i<equ; i++)
        {
            if(a[i][col])
            {
                for(int j=col; j<var+1; j++)
                    a[i][j] ^= a[row][j];
            }
        }
    } // row的值就是 rank 
    for(int i=row; i<equ; i++)
        if(a[i][var])
            return -1;///无解
    return var - row;///自由变元的个数
}
int Solve(int S)
{
    int s = (1<<S);///所有的状态
    int ans = INF;
    for(int i=0; i<s; i++)///枚举状态
    {
        int cnt = 0;
        memset(x, 0, sizeof(x));
        for(int j=0; j<S; j++)
        {
            if(i & (1<<j))
            {
                cnt++;///1的个数，也就是能够操作的个数
                x[free_xx[j]] = 1;//想象一个矩阵乘一个一维列向量，对应的是列向量的值 
            }
        }
        for(int j=var-S-1; j>=0; j--)
        {
            int tmp = a[j][var], tp, ok = 1;
            for(int k=j; k<var; k++)
            {
                if(a[j][k] && ok) //得找到该行第一个非0值，作为当前x的答案 
                {
                    tp = k;
                    ok = 0;
                }
                if(a[j][k] && k!=j)
                    tmp ^= x[k];
            }
            x[tp] = tmp;
            cnt += x[tp];
        }
        ans = min(ans, cnt);///最少的操作数
    }
    return ans;
}
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        cin>>n;
        equ = var = n*n;
        memset(a, 0, sizeof(a));//将网格编号，从左到右从上到下1到n，每一行表示第i个开关影响的是哪些个开关 
        for(int i=0; i<var; i++)
        {
            int ta = i%n, tb = i/n;
            a[i][i] = 1;
            if(ta > 0)
                a[i][i-1] = 1;
            if(ta < n-1)
                a[i][i+1] = 1;
            if(tb > 0)
                a[i][i-n] = 1;
            if(tb < n-1)
                a[i][i+n] = 1;//第i+n个开关对第i个开关影响1
        }
       /* for(int i = 0 ; i < var;i ++){
            for(int j = 0 ; j < var; j ++){
                cout << a[i][j] << " ";
            }
            cout<< endl;
        }*/ 
        //增广矩阵的最后一列，表示每个开关的状态 
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                char ch;
                cin>>ch;
                if(ch == 'y')
                    a[i*n+j][var] = 0;
                else
                    a[i*n+j][var] = 1;
            }
        }
        int S = Gauss();
        if(S == -1)
            puts("inf");
        else
            cout<<Solve(S)<<endl;
    }
    return 0;
}
```