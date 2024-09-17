# 知识点
  ## [[动态规划]] [[单调队列]] [[符合条件的总数]]
# 题目
 John 打算驾驶一辆汽车周游一个环形公路。

公路上总共有 n个车站，每站都有若干升汽油（有的站可能油量为零），每升油可以让汽车行驶一千米。

John 必须从某个车站出发，一直按顺时针（或逆时针）方向走遍所有的车站，并回到起点。

在一开始的时候，汽车内油量为零，John 每到一个车站就把该站所有的油都带上（起点站亦是如此），行驶过程中不能出现没有油的情况。

任务：判断以每个车站为起点能否按条件成功周游一周。

#### 输入格式

第一行是一个整数 n，表示环形公路上的车站数；

接下来 n 行，每行两个整数 pi,di，分别表示表示第 i 号车站的存油量和第 i 号车站到 **顺时针方向** 下一站的距离。

#### 输出格式

输出共 n 行，如果从第 i 号车站出发，一直按顺时针（或逆时针）方向行驶，能够成功周游一圈，则在第 i 行输出 TAK，否则输出 NIE。

#### 数据范围

$3≤n≤10^6$  
$0≤pi≤2×10^9$  
$0≤di≤2×10^9$ 

#### 输入样例：

```
5
3 1
1 2
5 2
0 1
5 4
```

#### 输出样例：

```
TAK
NIE
TAK
NIE
TAK
```

# 思路
·对于这种环形问题，我们可以先把环拆开，然后倍长链，使得首尾相接，这样我们计算那一条长链就等价于我们在环上计算每一个点开始绕行一圈所花费。
·要判断会不会哑火，其实就是在判断在区间内的前缀和之差有没有在某一个是小于 0 的的，如果有，那么就说明会在中途哑火，反之则不会。
·判断一个区间内前缀和之差的最大值，我们还是可以按照先固定一个点，然后在根据前面的点的情况来计算即可。
# AC 代码
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 2e6 + 10;

int n;
int oil[N], dist[N];
LL s[N];
int q[N];
bool ans[N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%d%d", &oil[i], &dist[i]);
        s[i] = s[i + n] = oil[i] - dist[i];
    }
    for (int i = 1; i <= n * 2; i ++ ) s[i] += s[i - 1];

    int hh = 0, tt = 0;
    q[0] = n * 2 + 1;
    for (int i = n * 2; i >= 0; i -- )
    {
        if (q[hh] > i + n) hh ++ ;
        if (i < n)
        {
            if (s[i] <= s[q[hh]]) ans[i + 1] = true;
        }
        while (hh <= tt && s[q[tt]] >= s[i]) tt -- ;
        q[ ++ tt] = i;
    }

    dist[0] = dist[n];
    for (int i = 1; i <= n; i ++ ) s[i] = s[i + n] = oil[i] - dist[i - 1];
    for (int i = 1; i <= n * 2; i ++ ) s[i] += s[i - 1];

    hh = 0, tt = 0;
    q[0] = 0;
    for (int i = 1; i <= n * 2; i ++ )
    {
        if (q[hh] < i - n) hh ++ ;
        if (i > n)
        {
            if (s[i] >= s[q[hh]]) ans[i - n] = true;
        }
        while (hh <= tt && s[q[tt]] <= s[i]) tt -- ;
        q[ ++ tt] = i;
    }

    for (int i = 1; i <= n; i ++ )
        if (ans[i]) puts("TAK");
        else puts("NIE");

    return 0;
}

作者：yxc
链接： https://www.acwing.com/activity/content/code/content/128104/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
# 备注
