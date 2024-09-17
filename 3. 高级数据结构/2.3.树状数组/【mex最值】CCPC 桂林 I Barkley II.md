Prof. Hui is the coach of Pigeland University Programming Team. There are $n$ students in his team. All algorithms are numbered by Prof. Hui in ascending order of difficulty, from $1$ to $m$. Which means that algorithm $1$ is the easiest algorithm, while algorithm $m$ is the hardest. The $i$ \-th student masters the $a_i$ \-th easiest algorithm.

Now Prof. Hui wants to choose a team satisfying the following conditions:

-   The index of the students in the team forms an interval. Which means that there exists two integers $l, r$ such that $1\leq l\leq r\leq n$ and student $x$ is in the team if and only if $l\leq x\leq r$.
    
-   The rating of the team is maximized. The more algorithms the team mastered, the stronger they are, but if they cannot solve a hard problem in one contest, they will feel more disappointed. So the rating of the team is the number of **different** algorithms that the students in the team mastered minus the index of the **easiest** algorithm that no one in the team mastered. If the students in the team masters all the algorithms, the index of the **easiest** algorithm that no student in the team mastered is considered to be $m+1$. For example, if $m=5$ and there are $6$ students in the team, mastering algorithm $2,5,4,4,1,1$ respectively, the rating of the team is $4 - 3 = 1$.

Please help Prof. Hui to find the maximum rating of a team.

**Input**

The first line contains an integer $t$ ($1\leq t\leq 5\cdot 10^5$), denoting the number of test cases.

For each test case, the first line contains two integer $n, m$ ($1\leq n,m\leq 5\cdot 10^5$), denoting the number of students and the number of algorithms.

The second line contains $n$ integers, the $i$ \-th integer $a_i$ ($1\leq a_i\leq m$) denoting the number of algorithm the $i$ \-th student masters.

**Output**

For each test case, output one integer in one line, denoting the answer.



It is guaranteed that the sum of $n$ over all testcases does not exceed $5\cdot 10^5$. Please notice that there is **no limit** on sum of $m$.

## 题解
题意：给你一个数列，要你求出数列中的最大区间，满足 $区间出现数字种类-区间mex$ 最大，问最后最大值是多少


我们这一题显然可以**考虑枚举我们的 mex，这也是我们遇见 mex 题目的套路之一**。之后，我们的问题就变成了，对于给定的 mex，我们区间出现的数字种类是多少，我们发现，**对于固定的 mex 值，我们只需考虑不包含它的所有最长连续区间即可**这是因为，我们的区间长度越长，我们可能得到的种类个数就会尽可能的多。

为了快速计算，我们可以进行下面的操作：
1. 我们预处理所有的区间，按照我们的右端点排序，
2. 我们按顺序枚举我们的区间 i，同时更新我们的下表 j，新的下表更新到树状数组，同时对之前出现过的重复数字对应下标做删除处理
3. 区间更新答案时，利用树状数组得到区间的不重复元素个数 $query(r)-query(l-1)$ 再减去对应的 mex 值

```cpp
const int maxn = 500010;
const int mod = 1e9 + 7;
int n, m, q;
int a[maxn], pre[maxn];

bool cmp(const vector<int> &x, const vector<int> &y) {
    return x[1] < y[1];
}

// 树状数组 
int sum[maxn]; 
int lowbit(int x) {
    return x & (-x);
}
int query(int x) { // 查询前缀 
    int res = 0;
    for(; x > 0; x -= lowbit(x)) {
        res += sum[x];
    }
    return res;
}
void update(int x, int val) { // 在点x新增值 
    for(; x <= n; x += lowbit(x)) {
        sum[x] += val;
    }
}


void solve() { 
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        pre[i] = 0;
    }
    pre[n+1] = 0;
    vector<vector<int> > vp;//vp存储我们mex值为k时，我们的数组对应长度为多少
    for (int i = 1; i <= n; ++i) {
        if (a[i] <= n + 1 && pre[a[i]] + 1 < i) {
            vp.push_back({pre[a[i]] + 1, i - 1, a[i]});//这里的第一个元素表示长度，第二个表示我们的位置，第三个表示我们的mex值是多少
        }
        pre[a[i]] = i;
    }
    for (int i = 1; i <= n + 1; ++i) {
        if (pre[i] + 1 <= n) {
            vp.push_back({pre[i] + 1, n, i});
        }
    }

    sort(vp.begin(), vp.end(), cmp);

    for (int i = 1; i <= n + 1; ++i) {
        pre[a[i]] = 0;
        sum[i] = 0;
    }
    int sz = vp.size();
    int ans = -1;
    for (int i = 0, j = 0; i < sz; ++i) {
        while (j < vp[i][1]) {
            ++j;
            if (pre[a[j]]) {
                update(pre[a[j]], -1);
            }
            update(j, 1);
            pre[a[j]] = j;
        }
        int tmp = query(vp[i][1]) - query(vp[i][0] - 1) - vp[i][2];
        ans = max(ans, tmp);
    }
    printf("%d\n", ans);

    // clear
    for (int i = 1; i <= n + 1; ++i) {
        pre[a[i]] = 0;
    }
}
```