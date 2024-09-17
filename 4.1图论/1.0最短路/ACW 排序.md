# 知识点
  ## [[spfa算法]] [[闭包传递]]
# 题目
 给定 n个变量和 m个不等式。其中 n小于等于 26，变量分别用前 n的大写英文字母表示。

不等式之间具有传递性，即若 A>B且 B>C，则 A>C。

请从前往后遍历每对关系，每次遍历时判断：

如果能够确定全部关系且无矛盾，则结束循环，输出确定的次序；
如果发生矛盾，则结束循环，输出有矛盾；
如果循环结束时没有发生上述两种情况，则输出无定解。
#### 输入格式
输入包含多组测试数据。

每组测试数据，第一行包含两个整数 n和 m。

接下来 m行，每行包含一个不等式，不等式全部为小于关系。

当输入一行 0 0 时，表示输入终止。

#### 输出格式
每组数据输出一个占一行的结果。

结果可能为下列三种之一：

如果可以确定两两之间的关系，则输出 "Sorted sequence determined after t relations: yyy...y.", 其中't'指迭代次数，'yyy... Y'是指升序排列的所有变量。
如果有矛盾，则输出： "Inconsistency found after t relations."，其中't'指迭代次数。
如果没有矛盾，且不能确定两两之间的关系，则输出 "Sorted sequence cannot be determined."。
#### 数据范围
2≤n≤26，变量只可能为大写字母 A∼Z。

#### 输入样例 1：
4 6
A<B
A<C
B<C
C<D
B<D
A<B
3 2
A<B
B<A
26 1
A<Z
0 0
输出样例 1：
Sorted sequence determined after 4 relations: ABCD.
Inconsistency found after 2 relations.
Sorted sequence cannot be determined.
输入样例 2：
6 6
A<F
B<D
C<E
F<D
D<E
E<F
0 0
输出样例 2：
Inconsistency found after 6 relations.
输入样例 3：
5 5
A<B
B<C
C<D
D<E
E<A
0 0
#### 输出样例 3：
Sorted sequence determined after 4 relations: ABCDE.

# 思路
***我们依据两点之间的关系来建图，如果两个点之间有小于/大于关系，我们就把两点之间的距离设定为 1 ，我们想要通过中间点更新两个点之间的距离，我们就可以通过与运算，因为这里的关系具有传递性，即 a 与 b 有关，b 与 c 有关，那么 a 与 c 也一定有关。

***判断关系是否已经完全，我们通过检查函数 check，检查如果图中的同一个点之间的关系是 1，那么一定是矛盾的，如果任意两个不同点之间还没有确定关系，即距离为 0，那么我们还没有完成，鉴定为未完成。否则我们就可以鉴定为已经完成了。



# AC 代码
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 26;

int n, m;
bool g[N][N], d[N][N];
bool st[N];

void floyd()
{
    memcpy(d, g, sizeof d);

    for (int k = 0; k < n; k ++ )
        for (int i = 0; i < n; i ++ )
            for (int j = 0; j < n; j ++ )
                d[i][j] |= d[i][k] && d[k][j];
}

int check()
{
    for (int i = 0; i < n; i ++ )
        if (d[i][i])
            return 2;

    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < i; j ++ )
            if (!d[i][j] && !d[j][i])
                return 0;

    return 1;
}

char get_min()
{
    for (int i = 0; i < n; i ++ )
        if (!st[i])
        {
            bool flag = true;
            for (int j = 0; j < n; j ++ )
                if (!st[j] && d[j][i])
                {
                    flag = false;
                    break;
                }
            if (flag)
            {
                st[i] = true;
                return 'A' + i;
            }
        }
}

int main()
{
    while (cin >> n >> m, n || m)
    {
        memset(g, 0, sizeof g);
        int type = 0, t;
        for (int i = 1; i <= m; i ++ )
        {
            char str[5];
            cin >> str;
            int a = str[0] - 'A', b = str[2] - 'A';

            if (!type)
            {
                g[a][b] = 1;
                floyd();
                type = check();
                if (type) t = i;
            }
        }

        if (!type) puts("Sorted sequence cannot be determined.");
        else if (type == 2) printf("Inconsistency found after %d relations.\n", t);
        else
        {
            memset(st, 0, sizeof st);
            printf("Sorted sequence determined after %d relations: ", t);
            for (int i = 0; i < n; i ++ ) printf("%c", get_min());
            printf(".\n");
        }
    }

    return 0;
}

作者：yxc
链接：https://www.acwing.com/activity/content/code/content/145995/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
# 备注
