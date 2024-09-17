# [ABC 349 E] Weighted Tic-Tac-Toe

## 题面翻译

有一个 $3\times3$ 的网格。$(i,j)$ 表示从顶部数第 $i$ 行、从左数第 $j$ 列的单元格 $(1\le i,j\le 3)$。单元格 $(i,j)$ 包含一个整数 $A_{i,j}$。可以保证 $\sum_{i=1}^3 \sum_{j=1}^3 A_{i,j}$ 是奇数。此外，所有单元格最初都是白色的。

Takahashi 和 Aoki 将使用这个网格进行游戏。Takahashi 先走，他们轮流执行以下操作：

选择一个仍然为白色的单元格 $(i,j)(1\le i,j\le3)$（可以证明这样的单元格在操作时总是存在的）。执行操作的玩家获得 $A_{i,j}$ 分。然后，如果玩家是 Takahashi，他将单元格 $(i,j)$ 涂成红色；如果玩家是 Aoki，他将其涂成蓝色。

每次操作后，都会进行以下检查：

- 检测是否存在三个连续的单元格被涂成相同的颜色（红色或蓝色）在任何行、列或对角线上。如果存在这样的序列，游戏立即结束，并且其颜色形成该序列的玩家获胜。

- 检查是否有白色单元格剩余。如果没有白色单元格剩余，游戏结束，得分较高的玩家获胜。

可以证明游戏将在有限次数的操作后结束，并且 Takahashi 或 Aoki 将获胜。确定如果双方的操作都是最佳的，哪位玩家会获胜。

**其实就是井字棋游戏+平局时高分获胜，输出是否有先手必胜策略。**

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc349/tasks/abc349_e

$ 3\ \times\ 3 $ のマス目があります。上から $ i $ 行目、左から $ j $ 列目 $ (1\ \leq\ i, j\ \leq\ 3) $ のマスをマス $ (i, j) $ と表します。マス $ (i, j) $ には整数 $ A_{i, j} $ が書かれています。ここで、 $ \sum_{i=1}^3\ \sum_{j=1}^3\ A_{i, j} $ は奇数であることが保証されます。また、すべてのマスははじめ白で塗られています。

高橋君と青木君が、このマス目を使ってゲームを行います。ゲームでは、高橋君を先手として、二人が交互に以下の操作を行います。

- 白で塗られているマス $ (i, j)\, (1\leq\ i, j\ \leq\ 3) $ を選ぶ（操作が行われる時点で、そのようなマスは必ず存在することが示せる）。操作をしているプレイヤーが得点 $ A_{i, j} $ を得る。次に、操作をしているプレイヤーが高橋君ならば、マス $ (i, j) $ を赤で、青木君ならば青で塗る。
 
各操作のあと、次の判定を行います。

- 赤または青の同じ色で塗られたマスが縦・横・斜めのいずれかの方向に $ 3 $ つ連続する箇所があるか判定する。そのような箇所があれば、その時点でゲームを終了し、赤が $ 3 $ つ連続しているならば高橋君が、青が $ 3 $ つ連続しているならば青木君が勝利する。
- 白で塗られているマスが存在するか判定する。存在しなければ、その時点でゲームを終了し、その時点までに獲得した累計の得点が高い方のプレイヤーが勝利する。
 
ゲームは必ず有限回の操作で終了し、高橋君または青木君の一方が勝利することが示せます。両者が勝ちを目指して最適に行動するとき、どちらが勝つか判定してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ A_{1,1} $ $ A_{1,2} $ $ A_{1,3} $ $ A_{2,1} $ $ A_{2,2} $ $ A_{2,3} $ $ A_{3,1} $ $ A_{3,2} $ $ A_{3,3} $

## 输出格式

高橋君が勝つならば `Takahashi` を、青木君が勝つならば `Aoki` を出力せよ。

## 样例 #1

### 样例输入 #1

```
0 0 0
0 1 0
0 0 0
```

### 样例输出 #1

```
Takahashi
```

## 样例 #2

### 样例输入 #2

```
-1 1 0
-4 -2 -5
-4 -1 -5
```

### 样例输出 #2

```
Aoki
```

## 提示

### 制約

- $ |A_{i, j}|\ \leq\ 10^9 $
- $ \sum_{i=1}^3\ \sum_{j=1}^3\ A_{i, j} $ は奇数
- 入力はすべて整数
 
### Sample Explanation 1

高橋君が最初の手番で $ (2,2) $ を選択すると、その後どのように青木君が行動しても、高橋君が適切に行動することで、青で塗られたマスが $ 3 $ つ連続しないようにすることができます。赤で塗られたマスが $ 3 $ つ連続した場合は高橋君が勝ちます。赤で塗られたマスが $ 3 $ つ連続せずにゲームが終了した場合、その時点で高橋君は $ 1 $ 点、青木君は $ 0 $ 点を獲得しているため、どちらにせよ高橋君が勝ちます。

## 题解
我们可以通过我们的其他的最大最小原理来进行，我们可以通过 dfs 来枚举我们的每一步下什么棋，然后就能够得到我们的最终的结果。

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF = 0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int, int> PII;

int g[3][3];
int have[3][3];  // -1表示未占用，1表示Aoki占用，2表示Takahashi占用

// 判断是否有玩家获胜
int check_winner() {
    // 检查行和列
    for (int i = 0; i < 3; i++) {
        if (have[i][0] == have[i][1] && have[i][1] == have[i][2] && have[i][0] != -1)
            return have[i][0];
        if (have[0][i] == have[1][i] && have[1][i] == have[2][i] && have[0][i] != -1)
            return have[0][i];
    }

    // 检查两条对角线
    if (have[0][0] == have[1][1] && have[1][1] == have[2][2] && have[0][0] != -1)
        return have[0][0];
    if (have[0][2] == have[1][1] && have[1][1] == have[2][0] && have[0][2] != -1)
        return have[0][2];

    // 没有胜利者
    return 0;
}

// 递归搜索，depth代表当前已走的步数
bool dfs(int depth, bool isAokiTurn) {
    // 如果有玩家获胜，终止递归
    int winner = check_winner();
    if (winner == 1) return true;  // Aoki胜利
    if (winner == 2) return false; // Takahashi胜利

    // 如果达到9步且没有人获胜，平局处理
    if (depth == 9) {
        int sumAoki = 0, sumTakahashi = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (have[i][j] == 1) sumAoki += g[i][j];
                else if (have[i][j] == 2) sumTakahashi += g[i][j];
            }
        }
        return sumAoki > sumTakahashi;  // 如果Aoki的分数高，则Aoki胜，否则Takahashi胜
    }

    // 遍历所有位置，选择未占用的位置进行尝试
    if (isAokiTurn) {  // Aoki的回合
        bool result = false;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (have[i][j] == -1) {
                    have[i][j] = 1;  // Aoki下棋
                    result = result || dfs(depth + 1, !isAokiTurn);
                    have[i][j] = -1;  // 回溯
                }
            }
        }
        return result;
    } else {  // Takahashi的回合
        bool result = true;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (have[i][j] == -1) {
                    have[i][j] = 2;  // Takahashi下棋
                    result = result && dfs(depth + 1, !isAokiTurn);
                    have[i][j] = -1;  // 回溯
                }
            }
        }
        return result;
    }
}

void solve() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> g[i][j];
            have[i][j] = -1;  // 初始状态为未占用
        }
    }
    
    // 从Aoki的回合开始搜索，深度为0
    if (dfs(0, true)) {
        cout << "Takahashi" << endl;
    } else {
        cout << "Aoki" << endl;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}
```