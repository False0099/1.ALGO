# 知识点
  ## [[DFS]] [[迭代加深]]
# 题目
 满足如下条件的序列 X（序列中元素被标号为 1、2、3…m）被称为“加成序列”：

$X[1]=1$
$X[m]=n$
$X[1]<X[2]<…<X[m−1]<X[m]$
对于每个 k（2≤k≤m）都存在两个整数 i 和 j $（1≤i, j≤k−1，）$ i 和 j 可相等），使得 $X[k]=X[i]+X[j]$。
你的任务是：给定一个整数 n，找出符合上述条件的长度 m最小的“加成序列”。
如果有多个满足要求的答案，只需要找出任意一个可行解。

# 输入格式
输入包含多组测试用例。

每组测试用例占据一行，包含一个整数 n。
当输入为单行的 0时，表示输入结束。

# 输出格式
对于每个测试用例，输出一个满足需求的整数序列，数字之间用空格隔开。

每个输出占一行。

数据范围
$1≤n≤100$

# 思路
对于这一类题，我们可以去枚举我们每一位的可能的数，然后再去判断我们是否符合规定即可。或者我们可以**枚举我们前面两个数的组合**，**这个数一定是前两个数的某种组合**，之后再去判断这个数是否比我们的 k 还要大。
另外，我们本题还可以采用迭代加深的方法进行优化，我们限制我们遍历的深度不能超过 k，如果超过 k，我们就跳过，否则我们再去进行计算。
# AC 代码
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 110;

int n;
int path[N];

bool dfs(int u, int k)//限制遍历的深度不超过k
{
    if (u == k) return path[u - 1] == n;

    bool st[N] = {0};
    for (int i = u - 1; i >= 0; i -- )
        for (int j = i; j >= 0; j -- )
        {
            int s = path[i] + path[j];
            if (s > n || s <= path[u - 1] || st[s]) continue;
            st[s] = true;
            path[u] = s;
            if (dfs(u + 1, k)) return true;
        }

    return false;
}

int main()
{
    path[0] = 1;
    while (cin >> n, n)
    {
        int k = 1;
        while (!dfs(1, k)) k ++ ;//一个长度下没找到合适的长度才扩展长度

        for (int i = 0; i < k; i ++ ) cout << path[i] << ' ';
        cout << endl;
    }

    return 0;
}
```
# 备注
