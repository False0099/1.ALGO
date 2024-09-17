# Is It Flower?

## 题面翻译

已知一个图，请问判断这个图是否是“k-Flower”

K-Flower 定义：
中间是一个 $k$ 边简单环，而这个环上的每一个点为一个 $k$ 边简单环上的一个点。

是的输出 `YES`，否则输出 `NO`。

Translate by @ [Gyk1013](https://www.luogu.com.cn/user/521118)

## 题目描述

Vlad found a flowerbed with graphs in his yard and decided to take one for himself. Later he found out that in addition to the usual graphs, $ k $ -flowers also grew on that flowerbed. A graph is called a $ k $ -flower if it consists of a simple cycle of length $ k $ , through each vertex of which passes its own simple cycle of length $ k $ and these cycles do not intersect at the vertices. For example, $ 3 $ -flower looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1811F/e34e743f4528bb273ae01a80cb827e1aa6e9fba5.png)Note that $ 1 $ -flower and $ 2 $ -flower do not exist, since at least $ 3 $ vertices are needed to form a cycle.

Vlad really liked the structure of the $ k $ -flowers and now he wants to find out if he was lucky to take one of them from the flowerbed.

## 输入格式

The first line of input contains the single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases in the test.

The descriptions of the cases follow. An empty string is written before each case.

The first line of each case contains two integers $ n $ and $ m $ ( $ 2 \le n \le 2 \cdot 10^5 $ , $ 1 \le m \le \min (2 \cdot 10^5, \frac{n \cdot (n-1)}{2}) $ ) — the number of vertices and edges in the graph, respectively.

The next $ m $ lines contain two integers each $ u $ and $ v $ ( $ 1 \le u, v \le n $ , $ u \ne v $ ) — numbers of vertices connected by an edge. It is guaranteed that the graph does not contain multiple edges and self-loops.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ . It is also guaranteed for the sum of $ m $ over all test cases.

## 输出格式

Output $ t $ lines, each of which is the answer to the corresponding test case. As an answer, output "YES" if Vlad's graph is a $ k $ -flower for some $ k $ , and "NO" otherwise.

You can output the answer in any case (for example, the strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive answer).

## 样例 #1

### 样例输入 #1

```
5


9 12
1 2
3 1
2 3
1 6
4 1
6 4
3 8
3 5
5 8
9 7
2 9
7 2


8 12
1 2
3 1
2 3
1 6
4 1
6 4
3 8
3 5
5 8
8 7
2 8
7 2


4 3
1 2
4 2
3 1


6 8
6 3
6 4
5 3
5 2
3 2
3 1
2 1
2 4


5 7
2 4
2 5
3 4
3 5
4 1
4 5
1 5
```

### 样例输出 #1

```
YES
NO
NO
NO
NO
```

## 样例 #2

### 样例输入 #2

```
4


2 1
1 2


8 9
1 2
8 4
8 2
6 4
6 5
4 7
3 2
3 7
2 5


9 12
2 9
2 8
6 9
6 8
6 5
6 1
9 8
9 3
9 1
8 3
8 7
5 7


3 3
1 2
1 3
2 3
```

### 样例输出 #2

```
NO
NO
NO
NO
```

## 题解
我们本题，我们首先可以发现，我们本题如果是一个花图，那么我们的对应的点数一定是满足我们的 $k^2$,其中我们的 k 是一个正整数。

除此之外，我们判断一个图是不是固定形态，我们可以通过找**我们的图上的点的度数规律**。以及我们的**这一个图上的联通情况**两个方面来进行考虑。

观察 k-flower 的性质：

· $k=\sqrt{n}$。显然如果 $n$ 不是完全平方数，直接无解。

· 图是连通的。

· 图中恰好有 $k$ 个点度数为 4，称为"中心点"。剩余所有点度数恰好为 2，且每个中心点断开后都会分出一个大小为 $k-1$ 的连通块。
·每个度数为 4 的点连接两个度数为 2 的点和 2 个度数为 4 的点。然后，就做完了。只需要逐一检验上面的条件即可。