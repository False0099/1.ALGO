# Reverse Sort

## 题面翻译

题目描述：

题目共给出 $t(1 \le t \le 1000)$ 组数据，每组数据包含一个正整数 $n(1 \le n \le 1000)$ 和一个长度为 $n$ 的 $01$ 串 $s$，现在你需要在 $s$ 中选出一个子序列，将这个子序列中的字符翻转（如字符串 $10100$，选出子序列 $1100$，翻转得到 $0011$，放回原串中得到 $00011$），使得翻转后的字符串字典序最小。

输入格式：

第一行一个 $t$，表示样例组数。

每组一个正整数 $t$ 和一个字符串 $s$，表示字符串的长度和你将要进行操作的字符串。

输出格式：

对于每组数据，第一行输出需要操作的次数（一次提取和一次翻转总称为一次操作，若不需修改则输出 $0$，详见样例），若操作次数不为零，则在第二行输出：

第一个数字 $k$，表示需要提取出来的数字个数，后 $k$ 个数字，表示提取出来的数字在原串中的位置（下标 + 1）

样例解释：

对于第一组样例，不需要进行任何操作，本身字典序最小，输出 $0$

对于第二组样例，需要进行一次操作，即将 $10100$ 中的 $1100$ 提取出来翻转，原串变为 $00011$

对于第三组样例，需要进行一次操作，即将 $001000$ 中的 $100$ 提取出来翻转，原串变为 $000001$

## 题目描述

Ashish has a binary string $ s $ of length $ n $ that he wants to sort in non-decreasing order.

He can perform the following operation:

1. Choose a subsequence of any length such that its elements are in non-increasing order. Formally, choose any $ k $ such that $ 1 \leq k \leq n $ and any sequence of $ k $ indices $ 1 \le i_1 \lt i_2 \lt \ldots \lt i_k \le n $ such that $ s_{i_1} \ge s_{i_2} \ge \ldots \ge s_{i_k} $ .
2. Reverse this subsequence in-place. Formally, swap $ s_{i_1} $ with $ s_{i_k} $ , swap $ s_{i_2} $ with $ s_{i_{k-1}} $ , $ \ldots $ and swap $ s_{i_{\lfloor k/2 \rfloor}} $ with $ s_{i_{\lceil k/2 \rceil + 1}} $ (Here $ \lfloor x \rfloor $ denotes the largest integer not exceeding $ x $ , and $ \lceil x \rceil $ denotes the smallest integer not less than $ x $ )

Find the minimum number of operations required to sort the string in non-decreasing order. It can be proven that it is always possible to sort the given binary string in at most $ n $ operations.

## 输入格式

The first line contains a single integer $ t $ $ (1 \le t \le 1000) $ — the number of test cases. The description of the test cases follows.

The first line of each test case contains an integer $ n $ $ (1 \le n \le 1000) $ — the length of the binary string $ s $ .

The second line of each test case contains a binary string $ s $ of length $ n $ containing only $ 0 $ s and $ 1 $ s.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 1000 $ .

## 输出格式

For each test case output the following:

- The minimum number of operations $ m $ in the first line ( $ 0 \le m \le n $ ).
- Each of the following $ m $ lines should be of the form: $ k $ $ i_1 $ $ i_2 $ ... $ i_{k} $ , where $ k $ is the length and $ i_1 \lt i_2 \lt ... \lt i_{k} $ are the indices of the chosen subsequence. For them the conditions from the statement must hold.

## 样例 #1

### 样例输入 #1

```
3
7
0011111
5
10100
6
001000
```

### 样例输出 #1

```
0
1
4 1 3 4 5 
1
3 3 5 6
```

## 提示

In the first test case, the binary string is already sorted in non-decreasing order.

In the second test case, we can perform the following operation:

- $ k = 4: $ choose the indices $ \{1, 3, 4, 5\} $  $ \underline{1} $ $ 0 $ $ \underline{1} $ $ \underline{0} $ $ \underline{0} $ $ \rightarrow  $ $ \underline{0} $ $ 0 $ $ \underline{0} $ $ \underline{1} $ $ \underline{1} $

In the third test case, we can perform the following operation:

- $ k = 3: $ choose the indices $ \{3, 5, 6\} $  $ 0 $ $ 0 $ $ \underline{1} $ $ 0 $ $ \underline{0} $ $ \underline{0} $ $ \rightarrow  $ $ 0 $ $ 0 $ $ \underline{0} $ $ 0 $ $ \underline{0} $ $ \underline{1} $

## 题解
对于这类题，我们都有一种统一的方法：我们先考虑我们是否存在一种仅用 1 次或是两次就能直接完成的，那么我们只需要直接构造即可。
事实上，我们存在这么一种方法：我们用双指针，对于我们扫描到的前指针的 0，我们忽略，对于我们扫描到的前指针的 1，我们直接加进去，后指针同理，然后我们就已经构造出了一个我们的反转序列。

把特殊情况特判，就是 $01$ 串一开始就已经是递增的了，那么无需操作，操作次数为0。


对于这种可能有若干次操作的题目，我们可以假定它“一定可以在一次（或两次）操作中完成”，于是问题就变为了如何构造出一种仅需一次的操作方法。

  

题目要求操作后$01$串变为升序，于是我们可以知道：

  

1.子序列里面肯定得有$1$也有$0$，否则翻转没有意义。

  

2.我们要做的是将右侧的$0$搬到左侧，左侧的$1$搬到右侧。

  

于是我们可以构造出一种操作方法，使得对于非特殊情况，一次操作一定可以使得串变为升序。

  

左右跑双指针即可，对于每一个左侧的$1$都有一个右侧的$0$与之对应即可。

  

### 代码

```cpp

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll N = 1e6 + 9;

  

char s[N];

  

void solve()

{

    int n;cin >> n;

    cin >> s + 1;

    bool tag = true;//tag表示01串为升序

    for(int i = 2;i <= n; ++ i)if(s[i] < s[i - 1])tag = false;

    if(tag)cout << 0 << '\n';

    else

    {

        vector<int> v;

        int l = 1, r = n;

        while(l < r)

        {

            while(l < r && s[l] == '0')l ++;

            while(l < r && s[r] == '1')r --;

            if(l < r)//注意一定要保证l < r才能加到答案里

            {

                v.push_back(l), v.push_back(r);

                l ++, r --;

            }

        }

        //输出前记得排序

        sort(v.begin(), v.end());

        cout << 1 << '\n' << v.size() << ' ';

        for(const auto &i : v)cout << i << ' ';

        cout << '\n';

    }

}

  

int main()

{

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    int _;cin >> _;

    while(_ --)solve();

    return 0;

}

```