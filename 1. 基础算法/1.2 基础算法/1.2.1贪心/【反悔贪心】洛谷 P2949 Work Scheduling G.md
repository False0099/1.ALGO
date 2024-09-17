# [USACO09OPEN] Work Scheduling G

## 题面翻译

约翰有太多的工作要做。为了让农场高效运转，他必须靠他的工作赚钱，每项工作花一个单位时间。 他的工作日从 $0$ 时刻开始，有 $10^9$ 个单位时间。在任一时刻，他都可以选择编号 $1$ 到 $N$ 的 $N(1 \leq N \leq 10^5)$ 项工作中的任意一项工作来完成。 因为他在每个单位时间里只能做一个工作，而每项工作又有一个截止日期，所以他很难有时间完成所有N个工作，虽然还是有可能。 对于第 $i$ 个工作，有一个截止时间 $D_i(1 \leq D_i \leq 10^9)$，如果他可以完成这个工作，那么他可以获利 $P_i( 1\leq P_i\leq 10^9 )$. 在给定的工作利润和截止时间下，约翰能够获得的利润最大为多少.

## 题目描述

Farmer John has so very many jobs to do! In order to run the farm efficiently, he must make money on the jobs he does, each one of which takes just one time unit.

His work day starts at time 0 and has 1,000,000,000 time units (!).  He currently can choose from any of N (1 <= N <= 100,000) jobs

conveniently numbered 1..N for work to do. It is possible but

extremely unlikely that he has time for all N jobs since he can only work on one job during any time unit and the deadlines tend to fall so that he can not perform all the tasks.

Job i has deadline D\_i (1 <= D\_i <= 1,000,000,000). If he finishes job i by then, he makes a profit of P\_i (1 <= P\_i <= 1,000,000,000).

What is the maximum total profit that FJ can earn from a given list of jobs and deadlines?  The answer might not fit into a 32-bit integer.

## 输入格式

\* Line 1: A single integer: N

\* Lines 2..N+1: Line i+1 contains two space-separated integers: D\_i and P\_i

## 输出格式

\* Line 1: A single number on a line by itself that is the maximum possible profit FJ can earn.

## 样例 #1

### 样例输入 #1

```
3 
2 10 
1 5 
1 7
```

### 样例输出 #1

```
17
```

## 提示

Complete job 3 (1,7) at time 1 and complete job 1 (2,10) at time 2 to maximize the earnings (7 + 10 -> 17).

## 题解
我们先思考简单贪心，即现将我们的deadline为第一关键字，value作为第二关键字排序，排序后，我们再顺序遍历每一个队伍，能做就做，不能做就抛弃。

反悔贪心的思路是在原来的基础上设置一个决策堆，我们按照原来的排序依次插入我们的决策堆中，每当我们的时间不足以我们完成决策堆中的所有任务时，比较当前任务和决策堆中最小任务之间的价值，如果当前任务价值更大，我们就丢掉价值最小的一件事，选上我们当前的任务。反之则什么都不做。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct node {
    int deadline, value;
    //重载<号的定义，规定堆为关于价值的小根堆
    bool operator<(const node &v) const {
        if (value > v.value) return true;
        return false;
    }
} a[110000];
// 使用优先队列代替手写堆(节省Coding时间)
priority_queue<node> q;
int n;
ll ans = 0;
 
//自定义排序函数，将任务按截止时间从小到大排序
bool cmp(node x, node y) {
    if (x.deadline < y.deadline) return true;
    return false;
}
 
int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i].deadline >> a[i].value;
    sort(a + 1, a + 1 + n, cmp);
    for (int i = 1; i <= n; ++i) {
        //如果当前决定做的任务数小于截止日期也就是还有时间做当前任务
        if (a[i].deadline > q.size()) {
            ans += a[i].value;
            q.push(a[i]);
        } else {
            if (a[i].value > q.top().value) {
                ans -= q.top().value;
                q.pop();
                q.push(a[i]), ans += a[i].value;
            }//反悔操作 
        }//考虑是否反悔，不做之前做的任务 
    }
    cout << ans << "\n";
    return 0;
}
```