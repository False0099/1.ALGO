https://ac.nowcoder.com/acm/contest/55672/D

## 题目描述
又一届 SCPC 成功举办，小 A 和小 B 怀着激动的心情想要开始自己的 xCPC 生涯。

  

一排 $n$ 个连续的格子，小 A 和小 B 每次可以任意从’C’和’P’中选择一个字母填入。每次操作后，如果有连续的三个格子形成"CPC"一词，则该玩家获胜。

  

小 A 先手，他俩都足够聪明，每一步都能做出最优决策。

## 输入
第一行为样例组数 $t(1\leq t \leq10^{5})$。

  

接下来 $t$ 行每一行一个整数 $n(1\leq n \leq 10^{9})$。

## 输出
对于每组样例，小 A 胜输出‘A’，小 B 胜输出‘B’，平局输出‘draw’。

## 题解
我们分析后能够发现，CPC 这个状态是一种特殊的状态，首先我们考虑什么样的局面是必败的。只有一种必胜点：
$\dots CooC\dots$ 表示除了两个 C 之间什么都没填上，其他位置都被填满，此时先手不管填什么，后手都能取胜。

另外，如果有多个这样的必胜点，其实就等价于一个必胜点。一旦有一个棋子落在必胜点之间，游戏下一回合直接结束。因此多个必胜点和一个必胜点是等价的。

因此，我们有这么一个道理：奇数情况后手是无法胜利的，偶数情况先手是无法胜利的。因为我们这里可以直接进行一次手玩，把我们的问题转化简单；
```cpp
 #include <iostream>
 #include <cstring>
 #include <algorithm>
 ​
 using namespace std;
 const int N = 2e5 + 10;
 ​
 signed main() {
     int T = 1;
     cin >> T;
     while (T-- ) {
         int n;
         cin >> n;
         if (n >= 7 && n & 1) cout << "A" << endl;
         else if (n >= 16 && n % 2 == 0) cout << "B" << endl;
         else cout << "draw" << endl;
    }
 }
```