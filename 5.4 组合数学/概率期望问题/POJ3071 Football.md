考虑一个包括 2_n_ 支球队的单淘汰足球锦标赛，球队编号为 1, 2, …, 2_n_。在锦标赛的每一轮中，仍在比赛中的所有球队按照索引递增的顺序排列在一张名单中。然后，名单中的第一支球队对阵第二支球队，第三支球队对阵第四支球队，以此类推。这些比赛的胜者晋级下一轮，而失败者被淘汰。经过 _n_ 轮比赛后，只有一支球队保持不败；这支球队被宣布为冠军。

给定一个矩阵 $P=[pij]$，其中 $pij$ 表示球队 _i_ 在比赛中击败球队 _j_ 的概率，确定哪支球队最有可能赢得锦标赛。

### 输入

输入测试文件将包含多个测试用例。每个测试用例将以包含一个整数 _n_ (1 ≤ _n_ ≤ 7) 的单行开头。接下来的 2_n_ 行每行包含 2_n_ 个值；这里，第 _i_ 行的第 _j_ 个值代表 _pij_。矩阵 _P_ 将满足约束条件，即对于所有 _i_ ≠ _j_，有 _pij_ = 1.0 − _pji_，对于所有 _i_ 有 _pii_ = 0.0。文件结束由包含数字 -1 的单行表示。注意，本问题中的矩阵条目都以浮点数值给出。为避免精度问题，请确保使用 `double` 数据类型而不是 `float`。

### 输出

输出文件应每个测试用例包含一行，指示最有可能赢得比赛的球队编号。为避免浮点精度问题，保证前两支球队获胜概率的差距至少为 0.01。

### 样例

|Inputcopy|Outputcopy|
|---|---|
|2<br>0.0 0.1 0.2 0.3<br>0.9 0.0 0.4 0.5<br>0.8 0.6 0.0 0.6<br>0.7 0.5 0.4 0.0<br>-1|2|

### 提示

在上述测试用例中，1 号和 2 号球队以及 3 号和 4 号球队在第一轮比赛中对阵；每场比赛的胜者随后进行比赛，以确定锦标赛的冠军。在这种情况下，2 号球队赢得锦标赛的概率为：

|   |   |
|---|---|
|P(2 wins)|= _P_(2 beats 1)_P_(3 beats 4)_P_(2 beats 3) + _P_(2 beats 1)_P_(4 beats 3)_P_(2 beats 4)  <br>= _p_21_p_34_p_23 + _p_21_p_43_p_24  <br>= 0.9 · 0.6 · 0.4 + 0.9 · 0.4 · 0.5 = 0.396。|

下一个最有可能获胜的球队是 3 号球队，获胜概率为 0.372。


## 题解
我们本题的思路就是采用暴力的计算每一个球队胜利的概率，然后比较后取得最大值是多少。这里，我们计算一个球队胜利的概率，可以通过我们枚举这一次对战的球队，然后计算我们战胜对应球队的概率是多少。

于是，我们的概率转移就可以有下面的式子：
第 $i$ 轮第 $j$ 个人和第 $k$ 个人对战时，第 $j$ 个人可以斎的概率是 $f_{i,j}=f_{i-1,j}\times f_{i-1,k}\times a_{j,k}$.

现在，我们的问题就是求出我们哪些人可以作为我们的 k，这里，我们有两种方法：第一种是通过我们的暴力枚举：
```cpp
void getVSId(int curTeamId, int winTime, int & beginVSId, int & endVsId) {

    int teamMemberCapcity = pow(2, winTime);

    beginVSId = 1;

    endVsId = beginVSId + teamMemberCapcity - 1;

    while(1) {

        if (curTeamId >= beginVSId && curTeamId <= endVsId) {

            break;

        } else {

            beginVSId = endVsId + 1;

            endVsId = beginVSId + teamMemberCapcity - 1;

        }

    }

    int middleId = (beginVSId + endVsId)>>1;

    if (curTeamId <= middleId) {

        beginVSId = middleId+1;

    } else {

        endVsId = middleId;

    }

    // printf("getVSId %d %d %d %d\n", curTeamId, winTime, beginVSId, endVsId);

}
```

第二种是通过我们的位运算：
```
((i >> (k - 1)) ^ 1) == (j >> (k - 1))
```

然后我们就可以得到我们的代码：
```cpp
#include <iostream>

#include <cstring>

#include <algorithm>

  

using namespace std;

  

const int N = 130;

  

int n;

double a[N][N], f[N][N];

  

int main() {

    ios::sync_with_stdio(false);

    cin.tie(0);

  

    while (cin >> n) {

        if (n == -1) break;

        int all = 1 << n;

        for (int i = 0; i < all; i++)

            for (int j = 0; j < all; j++)

                cin >> a[i][j];

        memset(f, 0, sizeof(f));

        for (int i = 0; i < all; i++) f[0][i] = 1;

        for (int k = 1; k <= n; k++) {              // Round k

            for (int i = 0; i < all; i++) {          // person i

                for (int j = 0; j < all; j++) {      // calc p{win(i, j)}

                    if (((i >> (k - 1)) ^ 1) == (j >> (k - 1))) {

                        f[k][i] += f[k - 1][i] * f[k - 1][j] * a[i][j];

                    }

                }

            }

        }

        int pos = -1;

        double maxx = -1.0;

        for (int i = 0; i < all; i++) {

            if (f[n][i] > maxx) {

                maxx = f[n][i];

                pos = i;

            }

        }

        cout << pos + 1 << '\n';

    }

    return 0;

}
```