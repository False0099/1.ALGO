# Lena and Matrix

## 题面翻译

$t$ 组数据，每组给定一个由字符 `W` 或 `B` 组成的 $n\times m$ 的矩阵。求这样一个点的坐标，满足其到图中任何一个 `B` 的最大曼哈顿距离最小。

若有多解，可任意输出一个。

$1\le t\le 10000,2\le n,m\le 1000,\sum nm\le 10^6$

## 题目描述

Lena is a beautiful girl who likes logical puzzles.

As a gift for her birthday, Lena got a matrix puzzle!

The matrix consists of $ n $ rows and $ m $ columns, and each cell is either black or white. The coordinates $ (i, j) $ denote the cell which belongs to the $ i $ -th row and $ j $ -th column for every $ 1\leq i \leq n $ and $ 1\leq j \leq m $ . To solve the puzzle, Lena has to choose a cell that minimizes the Manhattan distance to the farthest black cell from the chosen cell.

More formally, let there be $ k \ge 1 $ black cells in the matrix with coordinates $ (x_i, y_i) $ for every $ 1\leq i \leq k $ . Lena should choose a cell $ (a, b) $ that minimizes

$$\max_{i=1}^{k}(|a-x_i|+|b-y_i|). $$

As Lena has no skill, she asked you for help. Will you tell her the optimal cell to choose?

## 输入格式

There are several test cases in the input data. The first line contains a single integer $ t $ ( $ 1\leq t\leq 10\, 000 $ ) — the number of test cases. This is followed by the test cases description.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 2\leq n, m \leq 1000 $ ) — the dimensions of the matrix.

The following $ n $ lines contain $ m $ characters each, each character is either 'W' or 'B'. The $ j $ -th character in the $ i $ -th of these lines is 'W' if the cell $ (i, j) $ is white, and 'B' if the cell $ (i, j) $ is black.

It is guaranteed that at least one black cell exists.

It is guaranteed that the sum of $ n\cdot m $ does not exceed $ 10^6 $ .

## 输出格式

For each test case, output the optimal cell $ (a, b) $ to choose. If multiple answers exist, output any.

## 样例 #1

### 样例输入 #1

```
5
3 2
BW
WW
WB
3 3
WWB
WBW
BWW
2 3
BBB
BBB
5 5
BWBWB
WBWBW
BWBWB
WBWBW
BWBWB
9 9
WWWWWWWWW
WWWWWWWWW
BWWWWWWWW
WWWWWWWWW
WWWWBWWWW
WWWWWWWWW
WWWWWWWWW
WWWWWWWWW
WWWWWWWWB
```

### 样例输出 #1

```
2 1
2 2
1 2
3 3
6 5
```

## 提示

In the first test case the two black cells have coordinates $ (1,1) $ and $ (3,2) $ . The four optimal cells are $ (1,2) $ , $ (2,1) $ , $ (2,2) $ and $ (3,1) $ . It can be shown that no other cell minimizes the maximum Manhattan distance to every black cell.

In the second test case it is optimal to choose the black cell $ (2,2) $ with maximum Manhattan distance being $ 2 $ .

## 题解
我们首先考虑我们怎么计算我们**给定一个点**的时候，我们距离这个点的最远的曼哈顿距离的点是哪一个？这里，我们考虑我们的**曼哈顿距离转换为切比雪夫距离**。

$$\begin{aligned}&\text{考虑空个点,只需要不注它列到他点曼恰朗距离的最大值,而实际上全局只会有 4 个点真正会都响概大}\\&\text{值。}\\&dis=|x_1-x_2|+|y_1-y_2|\text{ 将绝对值积开分为 4 种情况,如下}:\\&\bullet dis=x_1-x_2+y_1-y_2\\&\bullet dis=x_1-x_2+y_2-y_1\\&\bullet dis=x_2-x_1+y_1-y_2\\&\bullet dis=x_2-x_1+y_2-y_1\\&\bullet dis=x_2-x_1+y_2-y_1\\&\text{设定 }(x_1,y_1)\text{ 为关键点,差质距离dis最大,推广一下 }(x_2,y_2)\text{ 作为四至点 (地理)需要满足以下 4 点之}\\&\bullet\mathrm{~min}(x_2+y_2)\\&\bullet\mathrm{~min}(x_2-y_2)\\&\bullet\mathrm{~max}(x_2-y_2)\\&\bullet\mathrm{~max}(x_2+y_2)\end{aligned}$$

