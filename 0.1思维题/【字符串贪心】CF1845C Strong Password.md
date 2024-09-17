# Strong Password

## 题面翻译

给定一个字符串 $s$，以及两个长度为 $m$ 的字符串 $l,r$。你需要判断是否**没有**长度为 `m` 的字符串 $t$ 满足以下要求：

1. 对于 $1\le i\le n$，$l_i\le t_i\le r_i$。
2. $t$ **不是** $s$ 的一个子序列。

## 题目描述

Monocarp finally got the courage to register on ForceCoders. He came up with a handle but is still thinking about the password.

He wants his password to be as strong as possible, so he came up with the following criteria:

- The length of the password should be exactly $ m $ ;
- The password should only consist of digits from $ 0 $ to $ 9 $ ;
- The password should not appear in the password database (given as a string $ s $ ) as a subsequence (not necessarily contiguous).

Monocarp also came up with two strings of length $ m $ : $ l $ and $ r $ , both consisting only of digits from $ 0 $ to $ 9 $ . He wants the $ i $ -th digit of his password to be between $ l_i $ and $ r_i $ , inclusive.

Does there exist a password that fits all criteria?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

The first line of each testcase contains a string $ s $ ( $ 1 \le |s| \le 3 \cdot 10^5 $ ), consisting only of digits from $ 0 $ to $ 9 $ — the password database.

The second line contains a single integer $ m $ ( $1 \le m \le10$ ) — the required length of the password.

The third line contains a string $ l $ ( $ |l| = m $ ), consisting only of digits from $ 0 $ to $ 9 $ — the lower restriction on each digit.

The fourth line contains a string $ r $ ( $ |r| = m $ ), consisting only of digits from $ 0 $ to $ 9 $ — the upper restriction on each digit. $ l_i \le r_i $ for all $ i $ from $ 1 $ to $ m $ .

The sum of lengths of $ s $ over all testcases doesn't exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each testcase, print "YES" if there exists a password that fits all criteria. Print "NO" otherwise.

## 样例 #1

### 样例输入 #1

```
5
88005553535123456
2
50
56
123412341234
3
111
444
1234
4
4321
4321
459
2
49
59
00010
2
10
11
```

### 样例输出 #1

```
YES
NO
YES
NO
YES
```

## 提示

In the first testcase, Monocarp can choose password "50". It doesn't appear in $ s $ as a subsequence.

In the second testcase, all combinations of three digits, each of them being from $ 1 $ to $ 4 $ , fit the criteria on $ l $ and $ r $ . However, all of them appear in $ s $ as subsequences. For example, "314" appears at positions $ [3, 5, 12] $ and "222" appears at positions $ [2, 6, 10] $ .

In the third testcase, Monocarp can choose password "4321". Actually, that is the only password that fits the criteria on $ l $ and $ r $ . Luckily, it doesn't appear in $ s $ as a subsequence.

In the fourth testcase, only "49" and "59" fit the criteria on $ l $ and $ r $ . Both of them appear in $ s $ as subsequences.

In the fifth testcase, Monocarp can choose password "11".

## 题解
我们这一题是我们的存在性问题，我们考虑怎么样构造出复合要求的答案。我们首先如果采用我们的暴力做法，我们就枚举 m 位中每一位分别可以是多少，然后再看是否复合我们的要求。但这这做法显然是 tle 的。

所以我们考虑有没有什么性质？首先，我们能够注意到，我们因为要求我们的子序列，所以我们一旦确定了我们的起始位置，并且知道在这个位置往后面的最远的数字是多少，那么我们肯定是优先考虑构造我们最远的数字。

另外，我们只要第一个字母确定，我们按照上面的方法如果能构造出一个字符，那么我们就一定输出 yes，反之我们直接输出 no 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve()
{
    string s;cin>>s;
    set<int> p[10];
    for(int i=1;i<=s.size();i++) p[s[i-1]-'0'].insert(i);
    int m,lst=0;cin>>m;
    string l,r;cin>>l>>r;
    for(int i=0;i<m;i++)
    {
        int tmp=0;
        for(int j=l[i]-'0';j<=r[i]-'0';j++)
        {
            auto it=p[j].upper_bound(lst);
            if(it==p[j].end()) {puts("YES");return;}
            tmp=max(tmp,*it);
        }
        lst=max(lst,tmp);
    }
    puts("NO");
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--) solve();
}
```