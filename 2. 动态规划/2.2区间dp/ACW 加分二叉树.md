# 知识点
  ## [[区间DP]]
# 题目
 设一个 n 个节点的二叉树 tree 的中序遍历为（1,2,3,…, n），其中数字 1,2,3,…, n为节点编号。

每个节点都有一个分数（均为正整数），记第 i个节点的分数为 di，tree 及它的每个子树都有一个加分，任一棵子树 subtree（也包含 tree 本身）的加分计算方法如下：     

Subtree 的左子树的加分 × Subtree 的右子树的加分 ＋ Subtree 的根的分数 

若某个子树为空，规定其加分为 1。

叶子的加分就是叶节点本身的分数，不考虑它的空子树。

试求一棵符合中序遍历为（1,2,3,…, n）且加分最高的二叉树 tree。

要求输出： 

（1）tree 的最高加分 

（2）tree 的前序遍历

## 输入格式
第 1 行：一个整数 n，为节点个数。 

第 2 行：n 个用空格隔开的整数，为每个节点的分数（0<
分数<100）。

## 输出格式
第 1 行：一个整数，为最高加分（结果不会超过 int 范围）。     

第 2 行：n个用空格隔开的整数，为该树的前序遍历。如果存在多种方案，则输出字典序最小的方案。

## 数据范围
N<30
## 输入样例 ：
5
5 7 1 2 10
## 输出样例 ：
145
3 1 2 4 5

# 思路
·首先，我们要知道给定一个中序遍历，我们并不能唯一确定一颗子数，因为如果我们把中序遍历看作是一个线段，那么线段的任意一个点都有可能是原树头节点。所以我们不能唯一确定一颗二叉树，但因为给的是一个中序遍历，所以如果我们能假设中间节点是 k，那么 $f[i][j]=f[i][k-1]+f[k+1][j]+k$。
·如果要我们按照前序遍历输出节点，我们可以先存储下来每一步是怎样转移的，是从哪一个中序节点遍历而成的，然后我们再把 root 按中序遍历输出即可。

# AC 代码
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;

const int N = 50;

int n;
int w[N];
unsigned f[N][N];
int root[N][N];

void dfs(int l, int r)
{
    if (l > r) return;

    int k = root[l][r];
    printf("%d ", k);
    dfs(l, k - 1);
    dfs(k + 1, r);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);
    for (int len = 1; len <= n; len ++ )//区间长度划分
        for (int l = 1; l + len - 1 <= n; l ++ )//列举左节点
        {
            int r = l + len - 1;//右节点显然

            for (int k = l; k <= r; k ++ )//由他们的中间来更新
            {
                int left = k == l ? 1 : f[l][k - 1];
                int right = k == r ? 1 : f[k + 1][r];
                int score = left * right + w[k];
                if (l == r) score = w[k];
                if (f[l][r] < score)
                {
                    f[l][r] = score;
                    root[l][r] = k;
                }
            }
        }

    printf("%d\n", f[1][n]);
    dfs(1, n);
    puts("");

    return 0;
}
```
# 备注
