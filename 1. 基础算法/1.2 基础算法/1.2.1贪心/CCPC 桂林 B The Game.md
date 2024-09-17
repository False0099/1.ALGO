#可行方案 #STL库 #必要性探路 #操作序列 #集合增删 
## 题意：
Randias is playing a game. He is given two multisets (a set which can contain duplicate elements) $A$ and $B$, consists of $n$ and $m$ integers $A_{1},A_{2}, \dots ,A_{n}$, $B_{1},B_{2}. \dots ,B_{m}$ repsectively. He can perform the following operation any number of times:

-   Choose one element $x$ where $x \in A$, change $x$ to $x+1$. Then remove the minimal element in $A$, Note that if there are more than one minimal element in $A$, we only remove one of them.

For example, if $A=\{4,4,5,5,6\}$ and we choose $x=5$, $A$ will become $\{4,5,6,6\}$ after one operation.

He wants to know whether he can make $A=B$ after several (possibly zero) operations? If he can make it, please help him to determine which operations need to be performed.

Two multisets are consider to be the same, if for all $x$, the number of occurrence of $x$ in $A$ and $B$ are the same.

**Input**

The first line contains $t$ ($1\le t \le 5\cdot 10^4$), representing the number of testcases.

For each testcase, the first line contains two integers $n,m$ ($1\le m \le n \le 3\cdot 10^5$), representing the size of two multisets.

The following line contains $n$ integers $A_{1},A_{2}, \dots ,A_{n}$ ($1\le A_{i} \le 10^9$).

The following line contains $m$ integers $B_{1},B_{2}, \dots, B_{m}$ ($1\le B_{i} \le 10^9$).

It is guaranteed that the sum of $n$ and the sum of $m$ over all test cases does not exceed $3 \cdot 10^5$.

**Output**

For each test case, if Randias cannot let $A=B$, output "$-1$".

Otherwise, on the first line, output the number of operations $L$ ($0 \le L \le n$) Randias needs to make.

The following line contains $L$ integers $x_{1},x_{2},\dots,x_{L}$, representing the integer $x$ each operation choose. You must ensure that $x \in A$ before each operation.

If there are multiple solutions, output any.

## 题解
我们这一题的分析方法是进行我们的必要性探路，也就是先找到我们的总共的操作次数是多少，然后再去根据我们的操作数去构造我们的对应的操作序列和 check 操作。

另外，对于我们的一个不断删去我们的集合最小数或者不断地删去我们的集合最大数，我们可以采用我们的 `multiset` 来协助我们进行操作。

我们如果要从我们的 $A$ 数组变成我们的 $B$ 数组，我们一定经过且仅仅经过我们的 $(m-n)$ 次操作。
我们首先有，我们如果要利用好我们的这 $(m-n)$ 次操作，我们一定是让我们的目前的后 m 大数字去匹配，然后看差多少，
1. 如果我们差的数字比我们的最大次数还要多，那么我们一定是不可能实现的，我们直接 `return no`
2. 如果我们 A 数组后面的 m 个数字中的对应位置比我们的 B 数组中的数值还要大，那么我们就认为是不可能实现的，我们也可以直接 `return no`
接下来，我们的操作就是分为两个部分：第一个部分，我们贪心的只对我们的后面 M 部分进行“补天”操作，补充我们还需要的个数。第二个部分，如果我们还有冗余的部分，我们可以直接加在我们的前面，来消耗掉。

**但是，我们还需要判断一个点，就是我们的冗余操作会不会把我们的原来的序列给替换掉**。举个简单的例子：`1 1 1 1 1`, `1 1 1`，如果我们不去更新我们的前 K 大值是多少，那么我们就会出现虽然我们这个序列是不可操作的，但是我们的答案仍然认为是可行的。

这个时候，我们就还需要一个 $set$ 来**动态的维护我们的前 K 大值是多少**。这里，我们可以采用我们的 set 来进行，

但是我们如果一个值更新到了我们的前 K 大值当中，并且这个值和我们的某一个前 K 大数字是相等的，我们就要让我们的 $cnt$ 也对应的减一，也就意味着，我们**还要一次冗余的操作来消除我们的这一个数字**。因此，我们要动态的更新我们的 `cnt`。

```c++
#include <bits/stdc++.h>
#include <unordered_map>
#define int long long
using namespace std;

const int N = 1e5 + 10, mod = 1e9 + 7;

int n, m;


signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T = 1;
    cin >> T;
    while (T -- )
    {
        cin >> n >> m;
        vector<int> a(n);
        for (int i = 0; i < n; i ++ ) cin >> a[i];
        sort(a.begin(), a.end());
        vector<int> b(m);
        for (int i = 0; i < m; i ++ ) cin >> b[i];
        sort(b.begin(), b.end());
        // 统计 cnt，使匹配需要进行的操作
        int ok = 1, cnt = 0;
        for (int i = m - 1, j = n - 1; i >= 0; i -- , j -- ) 
            if (a[j] > b[i])
            {
                ok = 0;
                break;
            }else cnt += b[i] - a[j];
        if (!ok || cnt + m > n) 
        {
            cout << "-1\n";
            continue;
        }
        multiset<int> s1, s2;
        for (int i = 0; i < n - m; i ++ ) s1.insert(a[i]);
        for (int i = n - m; i < n; i ++ ) s2.insert(a[i]);
        vector<int> ans;
        while (n - m - cnt > 0) // 将无效操作操作完
        {
            if (s1.empty())
            {
                ok = 0;
                break;
            }
            int x = *s1.begin(); s1.erase(s1.begin()); 
            // cout << x << ' ';
            ans.push_back(x);
            x ++;
            // 如果新的 x > 前 m 大中最小的数，则替换上去
            if (s2.size() < m || *s2.begin() < x) 
            {
                cnt --; // 这一步非常重要，cnt是需要动态维护的
                s2.insert(x);
                s2.erase(s2.begin());
                s1.insert(x - 1);
            }else s1.insert(x);
            if (s1.size()) s1.erase(s1.begin());
            else s2.erase(s2.begin());
            n --;
        }
        // 最后验证一下合不合法，并进行操作
        for (int i = 0; i < m; i ++ )
        {
            int x = *s2.begin(); s2.erase(s2.begin());
            if (x > b[i])
            {
                ok = 0;
                break;
            }
            while (x < b[i] && s1.size())
            {
                ans.push_back(x);
                x ++;
                s1.erase(s1.begin());
            }
            if (x < b[i])
            {
                ok = 0;
                break;
            }
        }
        if (!ok) cout << "-1\n";
        else 
        {
            cout << ans.size() << '\n';
            for (int i = 0; i < ans.size(); i ++ ) cout << ans[i] << " \n"[i == ans.size() - 1];
        }

    }   
    return 0;
}
```