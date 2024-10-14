# 知识点
  ## [[]]
# 题目
 给定一个具有 N个顶点的凸多边形，将顶点从 1至 N标号，每个顶点的权值都是一个正整数。

将这个凸多边形划分成 N−2个互不相交的三角形，对于每个三角形，其三个顶点的权值相乘都可得到一个权值乘积，试求所有三角形的顶点权值乘积之和至少为多少。

## 输入格式
第一行包含整数 N，表示顶点数量。

第二行包含 N 个整数，依次为顶点 1至顶点 N的权值。

## 输出格式
输出仅一行，为所有三角形的顶点权值乘积之和的最小值。

## 数据范围
N≤50,数据保证所有顶点的权值都小于 109
## 输入样例 ：
5
121 122 123 245 231
## 输出样例 ：
12214884

# 思路
我们本题的思路是：首先我们的这一题可以发现，我们最后划分出来的可以通过形如：$f[i][j]=f[i][k]+f[k][j]$ 的转移思路来进行转移。

那么这个时候，我们就需要关注的是，我们的**K**代表着什么含义。在这里，我们的 $k$ 表示，我们**用我们的 ijk**组成一个三角形后，剩余的部分对于我们的答案的贡献，于是，我们就可以有我们的转移如下所示：$f[i][j]=f[i][k]+f[k][j]+a[i]*a[j]*a[k]$.于是，我们的代码就这样完成了。
# AC 代码
```cpp
#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;

const int N = 55;

int n;
int w[N];
vector<int> f[N][N];

bool cmp(vector<int> &a, vector<int> &b)
{
    if (a.size() != b.size()) return a.size() < b.size();
    for (int i = a.size() - 1; i >= 0; i -- )
        if (a[i] != b[i])
            return a[i] < b[i];
    return true;
}
vector<int> add(vector<int> a, vector<int> b)
{
    vector<int> c;
    int t = 0;
    for (int i = 0; i < a.size() || i < b.size(); i ++ )
    {
        if (i < a.size()) t += a[i];
        if (i < b.size()) t += b[i];
        c.push_back(t % 10);
        t /= 10;
    }
    while (t) c.push_back(t % 10), t /= 10;
    return c;
}
vector<int> mul(vector<int> a, LL b)
{
    vector<int> c;
    LL t = 0;
    for (int i = 0; i < a.size(); i ++ )
    {
        t += b * a[i];
        c.push_back(t % 10);
        t /= 10;
    }
    while (t) c.push_back(t % 10), t /= 10;
    return c;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);

    //区间DP
    //此处初始状态f[l][l+1] = 0 初始就是空vector，不用额外设置
    for (int len = 3; len <= n; len ++ )
    {
        for (int l = 1, r; (r = l + len - 1) <= n; l ++ )
        {
            //初始化初始状态
            for (int k = l + 1; k < r; ++ k)
            {
                //w_l * w_k * w_r
                auto new_val = mul(mul({w[l]}, w[k]), w[r]);
                //f[l][k] + f[k][r] + cost
                new_val = add(add(new_val, f[l][k]), f[k][r]);
                //f[l][r] = min(f[l][r], f[l][k] + f[k][r] + w_sum)
                if (f[l][r].empty() || cmp(new_val, f[l][r])) f[l][r] = new_val;
            }
        }
    }
    //输出最终答案
    auto res = f[1][n];
    for (int i = res.size() - 1; i >= 0; i -- ) printf("%d", res[i]);
    puts("");

    return 0;
}
```
# 备注
