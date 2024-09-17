# 知识点
  ## [[AC自动机]]
# 题目
 某人读论文，一篇论文是由许多单词组成的。但他发现一个单词会在论文中出现很多次，现在他想知道每个单词分别在论文中出现多少次。

#### 输入格式
第一行一个整数 N，表示有多少个单词。

接下来 N 行每行一个单词，单词中只包含小写字母。

#### 输出格式
输出 N 个整数，每个整数占一行，第 i 行的数字表示第 i 个单词在文章中出现了多少次。

#### 数据范围
1≤N≤200,所有单词长度的总和不超过 10^6。

#### 输入样例 ：
3
A
Aa
Aaa
#### 输出样例 ：
6
3
1

# 思路
***开背

# AC 代码
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1000010;

int n;
int tr[N][26], f[N], idx;
int q[N], ne[N];
char str[N];
int id[210];

void insert(int x)
{
    int p = 0;
    for (int i = 0; str[i]; i ++ )
    {
        int t = str[i] - 'a';
        if (!tr[p][t]) tr[p][t] = ++ idx;
        p = tr[p][t];
        f[p] ++ ;
    }
    id[x] = p;
}

void build()
{
    int hh = 0, tt = -1;
    for (int i = 0; i < 26; i ++ )
        if (tr[0][i])
            q[ ++ tt] = tr[0][i];

    while (hh <= tt)
    {
        int t = q[hh ++ ];
        for (int i = 0; i < 26; i ++ )
        {
            int &p = tr[t][i];
            if (!p) p = tr[ne[t]][i];
            else
            {
                ne[p] = tr[ne[t]][i];
                q[ ++ tt] = p;
            }
        }
    }
}

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; i ++ )
    {
        scanf("%s", str);
        insert(i);
    }

    build();

    for (int i = idx - 1; i >= 0; i -- ) f[ne[q[i]]] += f[q[i]];

    for (int i = 0; i < n; i ++ ) printf("%d\n", f[id[i]]);

    return 0;
}


```
# 备注
