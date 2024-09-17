描述

有n只小动物，每只都有一个独特的编号，分别从1到n。现在他们从左到右依次排在一条直线上，顺序是乱的。
现在，我们只知道每个位置前面有几个比他小的数。请你根据给出的信息计算出每个位置上的数是多少。
n<=8000。

Input

输入第一行是一个正整数n，表示小动物的数量。
接下来有n-1个数，第i个数表示在第i+1个位置以前有多少个比第i+1个位置上的数小的数。

Output

输出n行，每行一个整数，表示对应位置小动物的编号。

Sample Input

5
1
2
1
0

Sample Output

2
4
5
3
1

样例解释

输入表示第2个位置前有1个比第3个位置小。
第3个位置前有2个比第3个位置小。
第4个位置前有1个比第4个位置小。
第5个位置前有0个比第5个位置小。

## 题解
首先，对于**第 n 头**牛，如果在他前面有 $A_{n}$ 头牛比他矮，那么他的高度就是我们的 $A_{n}+1$,在这之前的牛也类似，不过要考虑后面的牛可能已经占用的某些高度，所以，我们的高度就是在**剩余的数字中第 $k+1$ 小**的那一个数字。

于是我们的操作都可以归结为：
1. 从剩余的数中，找出第 $K$ 小的数
2. 删除某个数
（这个我们用平衡树能够简单的解决，但是我们不想写平衡树）

我们于是需要用二分+树状数组。

我们初始化 $a_{1}-a_{n}$ 为 1，表示我们都还可用，之后找剩余的第 K 的数，就相当于我们在我们的树状数组中二分，**找到某个位置，前面有正好 k 个数**。（操作 1）**然后我们把这个位置改为-1.**（操作 2）
```cpp
#include <cmath>
#include <cstdio>
using namespace std;

const int MAXN = 100005;

int n;
int seq[MAXN], height[MAXN], c[MAXN], prefix[MAXN];

inline int lowbit(int x)
{
    return x & -x;
}

inline int query(int x)
{
    int res = 0;
    while (x) {
        res += c[x];
        x -= lowbit(x);
    }
    return res;
}

inline void modify(int x, int val)
{
    while (x <= n) {
        c[x] += val;
        x += lowbit(x);
    }
}

void init()
{
    scanf("%d", &n);
    for (int i = 2;i <= n;++i) scanf("%d", &seq[i]);
    for (int i = 1;i <= n;++i) c[i] = lowbit(i);
}

void work()
{
    for (int i = n;i >= 1;--i) {
        int l = 1, r = n;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (query(mid) < seq[i] + 1) l = mid + 1;
            else r = mid;
        }
        height[i] = l;
        modify(l, -1);
    }
    for (int i = 1;i <= n;++i) {
        printf("%d\n",height[i]);
    }
}

int main()
{
    init();
    work();
    return 0;
}
```