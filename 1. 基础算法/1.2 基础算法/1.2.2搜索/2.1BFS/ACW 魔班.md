# 知识点
  ## [[BFS]] [[最小步数]]
# 题目
 Rubik 先生在发明了风靡全球的魔方之后，又发明了它的二维版本——魔板。

这是一张有 88 个大小相同的格子的魔板：

```
1 2 3 4
8 7 6 5
```

我们知道魔板的每一个方格都有一种颜色。

这 8 种颜色用前 8 个正整数来表示。

可以用颜色的序列来表示一种魔板状态，规定从魔板的左上角开始，沿顺时针方向依次取出整数，构成一个颜色序列。

对于上图的魔板状态，我们用序列 (1,2,3,4,5,6,7,8)(1,2,3,4,5,6,7,8) 来表示，这是基本状态。

这里提供三种基本操作，分别用大写字母 A，B，C 来表示（可以通过这些操作改变魔板的状态）：

A：交换上下两行；  
B：将最右边的一列插入到最左边；  
C：魔板中央对的4个数作顺时针旋转。

下面是对基本状态进行操作的示范：

A：

```
8 7 6 5
1 2 3 4
```

B：

```
4 1 2 3
5 8 7 6
```

C：

```
1 7 2 4
8 6 3 5
```

对于每种可能的状态，这三种基本操作都可以使用。

你要编程计算用最少的基本操作完成基本状态到特殊状态的转换，输出基本操作序列。

**注意**：数据保证一定有解。

#### 输入格式

输入仅一行，包括 8 个整数，用空格分开，表示目标状态。

#### 输出格式

输出文件的第一行包括一个整数，表示最短操作序列的长度。

如果操作序列的长度大于0，则在第二行输出字典序最小的操作序列。

#### 数据范围

输入数据中的所有数字均为 1 到 8 之间的整数。

#### 输入样例：

```
2 6 8 4 5 7 3 1
```

#### 输出样例：

```
7
BCABCCB
```

# 思路
·我们对于这种求最小转换步数，理论上都可以采用搜索的方法来解决，而搜索再加上我们要求最短距离就限定了我们只能用 BFS 去搜索结果。
·我们将每一种操作都当作一个“方向” ,问题就转化为，经过最少多少次操作后我们能够转化到最终状态。我们因此需要一个 map 来存储每个串被使用的次数。如果重复出现我们就无视。
·需要注意的是，在每一次的转换过程中，我们需要一个数据结构来储存我们每一个新串是由哪一个串经过什么操作变形而得到的。最后我们在查找的时候就可以通过最后的串去反推前面的各个串。
·同时，我们的每一次操作，都要写成一个函数，或者像下面那样直接写成一个数组。
# AC 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <queue>
#define x first
#define y second

using namespace std;

unordered_map<string, pair<char, string>> pre;
unordered_map<string, int> dist;
string op[3] = {"87654321", "41236785", "17245368"};

string move(string s, int k)
{
    string res;
    for (int i = 0; i < 8; i ++)
        res += s[op[k][i] - '1'];
    return res;
}

int bfs(string start, string end)
{
   if (start == end) return 0;

   queue<string> q;
   q.push(start);
   dist[start] = 0;

   while (q.size())
   {
       string t = q.front();
       q.pop();

       for (int i = 0; i < 3; i ++)
       {
           string s = move(t, i);
           if (!dist.count(s))
           {
               dist[s] = dist[t] + 1;
               pre[s] = {'A' + i, t};
               q.push(s);
               if (s == end) return dist[s];
           }
       }
   }
   return -1;
}


int main()
{
    string start = "12345678";
    string end;
    for (int i = 0, x; i < 8; i ++)
    {
        cin >> x;
        end += char(x + '0');
    }

    int step = bfs(start, end);

    cout << step << '\n';

    String res;
    while (start != end)
    {
        res += pre[end].x;
        end = pre[end].y;
    }
    reverse(res.begin(), res.end());

    if (step > 0)
        cout << res << endl;
    return 0;
}

作者：4_3
链接：https://www.acwing.com/activity/content/code/content/4157671/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
# 备注
