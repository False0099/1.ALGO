# 知识点
  ## [[DFS]] [[位运算]]
# 题目
 数独是一种传统益智游戏，你需要把一个 9×9的数独补充完整，使得数独中行、每列、每个 3×3的九宫格内数字 1∼9均恰好出现一次。

请编写一个程序填写数独。

# 输入格式
输入包含多组测试用例。每个测试用例占一行，包含 81个字符，代表数独的 81
 个格内数据（顺序总体由上到下，同行由左到右）。

每个字符都是一个数字（1−9）或一个 .（表示尚未填充）。

您可以假设输入中的每个谜题都只有一个解决方案。

文件结尾处为包含单词 end 的单行，表示输入结束。

# 输出格式

# 思路
·我们先来想最朴素的做法，我们就枚举每一个格子上的所有可能的情况，然后再判断这些情况是不是真的满足要求了，如果不满足我们就要放弃这一种情况，知道我们最后找到合理的情况
·上面的方法想要优化，就要用 2 进制来表示状态，例如一行里已经填入了 1，3，5，7，9. 还剩下 2，4，6，8。那么我们就可以在 2 进制的第 2 位处填入一个 1 表示这个位置还没有填数字。以此类推。
·有了上面的表示法，合法的状态的集合就可被我们用与运算计算出来。
·此外我们还可以通过一个函数来让我们的每一次修改都能表现在数字之上。
# AC 代码
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 9, M = 1 << N;

int ones[M], map[M];
int row[N], col[N], cell[3][3];
char str[100];

void init()//初始化二的对数表，一个每个状态数字对应的状态个数
{
    for (int i = 0; i < N; i ++ )
        row[i] = col[i] = (1 << N) - 1;

    for (int i = 0; i < 3; i ++ )
        for (int j = 0; j < 3; j ++ )
            cell[i][j] = (1 << N) - 1;
}

void draw(int x, int y, int t, bool is_set)//在数独上做更改
{
//在图上的影响
    if (is_set) str[x * N + y] = '1' + t;//把那一个位置改了
    else str[x * N + y] = '.';

    int v = 1 << t;
//在数据上的影响
    if (!is_set) v = -v;

    row[x] -= v;
    col[y] -= v;
    cell[x / 3][y / 3] -= v;
}

int lowbit(int x)
{
    return x & -x;
}

int get(int x, int y)
{
    return row[x] & col[y] & cell[x / 3][y / 3];
}

bool dfs(int cnt)
{
    if (!cnt) return true;

    int minv = 10;
    int x, y;
    for (int i = 0; i < N; i ++ )
        for (int j = 0; j < N; j ++ )//遍历这一个数独
            if (str[i * N + j] == '.')//找到当中的空位
            {
                int state = get(i, j);//找到这一个区域里的可行方案
                if (ones[state] < minv)//找到最小的方案
                {
                    minv = ones[state];
                    x = i, y = j;
                }
            }
	//找到数组里可行方案数最小的一个
    int state = get(x, y);
    for (int i = state; i; i -= lowbit(i))
    {
        int t = map[lowbit(i)];
        draw(x, y, t, true);
        if (dfs(cnt - 1)) return true;
        draw(x, y, t, false);
    }
	//然后对这一个可行性最小的方案进行dfs
    return false;
}

int main()
{
    for (int i = 0; i < N; i ++ ) map[1 << i] = i;//初始化2的对数表
    for (int i = 0; i < 1 << N; i ++ )
        for (int j = 0; j < N; j ++ )
            ones[i] += i >> j & 1;//初始化每一种情况下1的个数

    while (cin >> str, str[0] != 'e')
    {
        init();

        int cnt = 0;
        for (int i = 0, k = 0; i < N; i ++ )
            for (int j = 0; j < N; j ++, k ++ )//根据给出的字符串来画出对应的数独，对应的图形用一个字符来存储
                if (str[k] != '.')
                {
                    int t = str[k] - '1';
                    draw(i, j, t, true);
                }
                else cnt ++ ;

        dfs(cnt);//根据我们的需要遍历的空格的数目来dfs

        puts(str);
    }

    return 0;
}

作者：yxc
链接：https://www.acwing.com/activity/content/code/content/136449/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
# 备注
