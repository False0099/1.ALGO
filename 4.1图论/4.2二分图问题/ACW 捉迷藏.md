# 知识点
  ## [[二分图]] [[二分图最大匹配]]
# 题目
 Vani 和 cl2在一片树林里捉迷藏。这片树林里有 N座房子，M条有向道路，组成了一张有向无环图。

树林里的树非常茂密，足以遮挡视线，但是沿着道路望去，却是视野开阔。

如果从房子 A沿着路走下去能够到达 B，那么在 A和 B里的人是能够相互望见的。

现在 cl 2 要在这 N 座房子里选择 K 座作为藏身点，同时 Vani 也专挑 cl 2 作为藏身点的房子进去寻找，为了避免被 Vani 看见，cl 2 要求这 K 个藏身点的任意两个之间都没有路径相连。

为了让 Vani 更难找到自己，cl 2 想知道最多能选出多少个藏身点。

## 输入格式
输入数据的第一行是两个整数 N和 M。

接下来 M行，每行两个整数 x, y，表示一条从 x到 y的有向道路。

## 输出格式
输出一个整数，表示最多能选取的藏身点个数。

## 数据范围
$N≤200, M≤30000$
$1≤x, y≤N$

## 输入样例：
7 5
1 2
3 2
2 4
4 5
4 6
## 输出样例 ：
3

# 思路
***本题要求的是用最少条互不相交的路径，覆盖所有点。我们此时可以再次应用典中点的等式关系
  最大匹配数 = 最小点覆盖 = 总点数 - 最大独立集 = 总点数 - 最小路径覆盖
·所以这一题也就转换为了求最大匹配数。二分图的构建就采用最为朴素的染色法来，染上了同一种颜色那就是在同一侧，不同种颜色就是不在同一侧。
``求原图中互不相交路径数<=>求路径终点数最少<=>求左部非匹配点最少<=>求最大匹配

# AC 代码
```cpp
#include <iostream>
#include <cstring>

using namespace std;

const int N = 210 , M = 30010;

bool d[N][N];
bool st[N];
int n , m;
int match[N];

bool find(int x)
{
    for(int i = 1 ; i <= n ; i++)
    {
        if(d[x][i] && !st[i])
        {
            st[i] = true;
            if(!match[i] || find(match[i]))
            {
                match[i] = x;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    cin >> n >> m;

    while(m--)
    {
        int a , b;
        cin >> a >> b;
        d[a][b] = true;
    }

    for(int k = 1 ; k <= n ; k++)//求传递闭包
        for(int i = 1 ; i <= n ; i++)
            for(int j = 1 ; j <= n ; j++)
                d[i][j] |= d[i][k] & d[k][j];

    int res = 0;
    for(int i = 1 ; i <= n ; i++)
    {
        memset(st , 0 , sizeof st);
        if(find(i)) res++;
    }

    cout << n - res << endl;
    return 0;
}


```
# 备注
