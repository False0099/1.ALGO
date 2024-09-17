# Alice and Bob

## 题面翻译

Alice 与 Bob 发明了一种游戏。给出 $n$ 个不同的正整数，两人轮流做以下操作：

1. 从序列中选出两个数 $x,y$，要求这两个数的差的绝对值 $|x-y|$ 不在序列中；
2. 将这两个数的差的绝对值 $|x-y|$ 加入序列。

当有一方无法完成这个操作时，即失败。Alice 先手，两方均选择最优策略，问哪方将获胜。

### 输入

第一行为一个整数 $n$，表示数字个数。
第二行为 $n$ 个以空格分隔的数，代表初始的 $n$ 个数字。
## 输出
输出获胜者的名字，`Alice` 或 `Bob`。

## 题目描述

It is so boring in the summer holiday, isn't it? So Alice and Bob have invented a new game to play. The rules are as follows. First, they get a set of $ n $ distinct integers. And then they take turns to make the following moves. During each move, either Alice or Bob (the player whose turn is the current) can choose two distinct integers $ x $ and $ y $ from the set, such that the set doesn't contain their absolute difference $ |x-y| $ . Then this player adds integer $ |x-y| $ to the set (so, the size of the set increases by one).

If the current player has no valid move, he (or she) loses the game. The question is who will finally win the game if both players play optimally. Remember that Alice always moves first.

## 输入格式

The first line contains an integer $ n $ ( $ 2<=n<=100 $ ) — the initial number of elements in the set. The second line contains $ n $ distinct space-separated integers $ a_{1}, a_{2},..., a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — the elements of the set.

## 输出格式

Print a single line with the winner's name. If Alice wins print "Alice", otherwise print "Bob" (without quotes).

## 样例 #1

### 样例输入 #1

```
2
2 3
```

### 样例输出 #1

```
Alice
```

## 样例 #2

### 样例输入 #2

```
2
5 3
```

### 样例输出 #2

```
Alice
```

## 样例 #3

### 样例输入 #3

```
3
5 6 7
```

### 样例输出 #3

```
Bob
```

## 提示

Consider the first test sample. Alice moves first, and the only move she can do is to choose 2 and 3, then to add 1 to the set. Next Bob moves, there is no valid move anymore, so the winner is Alice.

## 题解
本题我们注意到，我们题目中给定的操作的实际意义就是，我们每一次都能够进行一次**辗转相除法**。我们最后能够达到的次数，显然就是我们的最终的 gcd 的次数，我们最后一定也是形成一个等差数列，其中我们的等差就是我们的全局 gcd，我们的最大值就是我们原来的蓄力中的最大值，我们你能够操作的次数就是我们的 $\frac{max}{gcd}$。

我们只需要判断我们操作次数是奇数还是偶数即可。
```
#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
int qread(){
    int w = 1, c, ret;
    while((c = getchar()) >  '9' || c <  '0') w = (c == '-' ? -1 : 1); ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}
int main(){
    int n = qread(), d = 0, m = 0;
    up(1, n, i){
        int a = qread(); m = max(m, a);
        d = __gcd(a, d);
    }
    puts((m / d - n) % 2 == 1 ? "Alice" : "Bob");
    return 0;
}
```