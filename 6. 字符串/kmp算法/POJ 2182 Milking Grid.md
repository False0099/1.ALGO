## 题目描述
在 N * M 字符矩阵中找出一个最小子矩阵，使其多次复制所得的矩阵包含原矩阵。

## 样例 #1

### 样例输入 #1

```
aba  
bab  
aba
```

### 样例输出 #1

```
ab  
ba
```

## 题解
我们先把每一行通过字符串哈希转化为一个数字，之后我们就得到了一个字符数组，对这一个字符数组进行 KMP，我们得到了**第一个最小正周期 K，也就是找到最长 border**，表示在每一行中，我们应该的重复次数。然后再把每一列通过字符串哈希转化为一个数组，我们又得到了一个字符数组，对着一个字符数金进行 KMP，**我们又能得到一个最小正周期 J**，将 K 与 J 相乘，我们就能够得到我们的答案。

## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>

using namespace std;

const int N=10005;
char w[N][80];
int t[N],l[80],n,m,tmp;
void calc_t()
{
    t[0]=-1;
    int j;
    for (int i=0;i<n;i++)
    {
        t[i+1]=i+1;
        for (int k=0;k<m;k++)
        {
            j=t[i];
            while(w[i][k]!=w[j][k]&&j!=-1)
            j=t[j];
            t[i+1]=min(++j,t[i+1]);
        }
    }
}
void calc_w()
{
    int j;
    l[0]=-1;
    for (int i=0;i<m;i++)
    {
        l[i+1]=i+1;
        for (int k=0;k<tmp;k++)
        {
            j=l[i];
            while(w[k][i]!=w[k][j]&&j!=-1)
            j=l[j];
            l[i+1]=min(++j,l[i+1]);
        } 
    }
}
int main()
{
//  freopen("std.in","r",stdin); 
    cin>>n>>m;
    for (int i=0;i<n;i++)
    scanf("%s",w[i]);
    calc_t();
    tmp=n-t[n];
    calc_w();
    int tmp1=m-l[m];
    cout<<tmp*tmp1;
    return 0;
}
```