there are N ACMers in HDU team.  
ZJPCPC Sunny Cup 2007 is coming, and lcy want to select some excellent ACMers to attend the contest. There have been M matches since the last few days(No two ACMers will meet each other at two matches, means between two ACMers there will be at most one match). lcy also asks"Who is the winner between A and B?" But sometimes you can't answer lcy's query, for example, there are 3 people, named A, B, C.and 1 match was held between A and B, in the match A is the winner, then if lcy asks "Who is the winner between A and B", of course you can answer "A", but if lcy ask "Who is the winner between A and C", you can't tell him the answer.  
As lcy's assistant, you want to know how many queries at most you can't tell lcy(ask A B, and ask B A is the same; and lcy won't ask the same question twice).

## Input

The input contains multiple test cases.  
The first line has one integer,represent the number of test cases.  
Each case first contains two integers N and M(N , M <= 500), N is the number of ACMers in HDU team, and M is the number of matchs have been held.The following M lines, each line means a match and it contains two integers A and B, means A wins the match between A and B.And we define that if A wins B, and B wins C, then A wins C.

## Output

For each test case, output a integer which represent the max possible number of queries that you can't tell lcy.

## Sample

|Inputcopy|Outputcopy|
|---|---|
|3<br>3 3<br>1 2<br>1 3<br>2 3<br>3 2<br>1 2<br>2 3<br>4 2<br>1 2<br>3 4|0<br>0<br>4|

Hint

  
in the case3, if lcy ask (1 3 or 3 1) (1 4 or 4 1) (2 3 or 3 2) (2 4 or 4 2), then you can't tell him who is the winner.


## 题解
我们的题意是给定我们 n 个人，m 个有传递性的关系，问我们有多少对选手，不能判断它们之间的胜负关系。
这一题，我们相当于求我们的传递闭包，我们于是就可以用我们的 floyd 算法去计算我们的结果，用 1 表示胜负确定，

```cpp
#include <bits/stdc++.h>

inline int read() {
    bool sym = false; int res = 0; char ch = getchar();
    while (!isdigit(ch)) sym |= (ch == '-'), ch = getchar();
    while (isdigit(ch)) res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
    return sym ? -res : res;
}

constexpr int N = 550;

int main() {
    int T = read();
    while (T--) {
        int ans = 0, n = read(), m = read();
        std::bitset<N> d[N];
        for (int i = 1; i <= n; i++) d[i][i] = 1;
        for (int i = 1; i <= m; i++) {
            int x = read(), y = read();
            d[x][y] = true;
        }
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                if (d[i][k]) {
                    d[i] |= d[k];
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = i+ 1; j <= n; j++) {
                if (d[i][j] == false && d[j][i] == false) {
                    ans++;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
```