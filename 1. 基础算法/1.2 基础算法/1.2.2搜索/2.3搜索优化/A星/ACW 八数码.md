# 知识点
  ## [[A star 算法]] [[BFS]]
# 题目
 在一个 3×3 的网格中，1∼8 这 8 个数字和一个 X 恰好不重不漏地分布在这 3×3 的网格中。

例如：

1 2 3
X 4 6
7 5 8
在游戏过程中，可以把 X 与其上、下、左、右四个方向之一的数字交换（如果存在）。

我们的目的是通过交换，使得网格变为如下排列（称为正确排列）：

1 2 3
4 5 6
7 8 X
例如，示例中图形就可以通过让 X 先后与右、下、右三个方向的数字交换成功得到正确排列。

交换过程如下：

1 2 3   1 2 3   1 2 3   1 2 3
X 4 6   4 X 6   4 5 6   4 5 6
7 5 8   7 5 8   7 X 8   7 8 X
把 X 与上下左右方向数字交换的行动记录为 u、d、l、r。

现在，给你一个初始网格，请你通过最少的移动次数，得到正确排列。

## 输入格式
输入占一行，将 3×3 的初始网格描绘出来。

例如，如果初始网格如下所示：

1 2 3 
X 4 6 
7 5 8 
则输入为：1 2 3 x 4 6 7 5 8

## 输出格式
输出占一行，包含一个字符串，表示得到正确排列的完整行动记录。

如果答案不唯一，输出任意一种合法方案即可。

如果不存在解决方案，则输出 unsolvable。

## 输入样例 ：
2  3  4  1  5  x  7  6  8 
## 输出样例
Ullddrurdllurdruldr

# 思路
·对于朴素的八数码问题，我们都可以用最基础的枚举每一个状态下可以转移到的新的操作，最后知道能和最后状态匹配时的最短路程。
·如果我们想要采用 A 算法，我们的估计函数就要设置成当前状态中，每一个数与他最终他的目标位置的曼哈顿距离之和。
·如果我们想要用双向 BFS 去搜索，也是可以的，同时也有着类似的思路。
·在我们写 A 算法时，通常都要用到 pair，因为这样的话我们就可以用 pair 的第一个值来存储我们的估计函数，第二个储存我们的实际参数，这样就不会很乱了。
# AC 代码
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

int f(string state)
{
    int res = 0;
    for (int i = 0; i < state.size(); i ++ )
        if (state[i] != 'x')
        {
            int t = state[i] - '1';
            res += abs(i / 3 - t / 3) + abs(i % 3 - t % 3);
        }
    return res;
}

string bfs(string start)
{
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
    char op[4] = {'u', 'r', 'd', 'l'};

    string end = "12345678x";
    unordered_map<string, int> dist;
    unordered_map<string, pair<string, char>> prev;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> heap;

    heap.push({f(start), start});
    dist[start] = 0;

    while (heap.size())
    {
        auto t = heap.top();
        heap.pop();

        string state = t.second;

        if (state == end) break;

        int step = dist[state];
        int x, y;
        for (int i = 0; i < state.size(); i ++ )
            if (state[i] == 'x')
            {
                x = i / 3, y = i % 3;
                break;
            }
        string source = state;
        for (int i = 0; i < 4; i ++ )
        {
            int a = x + dx[i], b = y + dy[i];
            if (a >= 0 && a < 3 && b >= 0 && b < 3)
            {
                swap(state[x * 3 + y], state[a * 3 + b]);
                if (!dist.count(state) || dist[state] > step + 1)
                {
                    dist[state] = step + 1;
                    prev[state] = {source, op[i]};
                    heap.push({dist[state] + f(state), state});
                }
                swap(state[x * 3 + y], state[a * 3 + b]);
            }
        }
    }

    string res;
    while (end != start)
    {
        res += prev[end].second;
        end = prev[end].first;
    }
    reverse(res.begin(), res.end());
    return res;
}

int main()
{
    string g, c, seq;
    while (cin >> c)
    {
        g += c;
        if (c != "x") seq += c;
    }

    int t = 0;
    for (int i = 0; i < seq.size(); i ++ )
        for (int j = i + 1; j < seq.size(); j ++ )
            if (seq[i] > seq[j])
                t ++ ;

    if (t % 2) puts("unsolvable");
    else cout << bfs(g) << endl;

    return 0;
}
```
# 备注
