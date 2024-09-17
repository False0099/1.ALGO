# Domino for Young

## 题面翻译

给出一个不规则的网格。共 $n$ 列, 每列有 $a_i$ 个格子。现在要将 $1 \times 2$ 的骨牌不重叠的覆盖在网格上，求最多能放的骨牌数量。

网格满足条件 $a_1\geq a_2\geq \ldots \geq a_n\geq 1$ .

## 题目描述

You are given a Young diagram.

Given diagram is a histogram with $ n $ columns of lengths $ a_1, a_2, \ldots, a_n $ ( $ a_1 \geq a_2 \geq \ldots \geq a_n \geq 1 $ ).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1268B/2544e64d1ff8ecc95c5b673d61da4ac4a05b5734.png)Young diagram for $ a=[3,2,2,2,1] $ .Your goal is to find the largest number of non-overlapping dominos that you can draw inside of this histogram, a domino is a $ 1 \times 2 $ or $ 2 \times 1 $ rectangle.

## 输入格式

The first line of input contain one integer $ n $ ( $ 1 \leq n \leq 300\, 000 $ ): the number of columns in the given histogram.

The next line of input contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 300\, 000, a_i \geq a_{i+1} $ ): the lengths of columns.

## 输出格式

Output one integer: the largest number of non-overlapping dominos that you can draw inside of the given Young diagram.

## 样例 #1

### 样例输入 #1

```
5
3 2 2 2 1
```

### 样例输出 #1

```
4
```

## 提示

Some of the possible solutions for the example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1268B/3d8978aaa90355dc607b1f977284246d35ebb93f.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1268B/470888c1347adb69c9c5541029d57b758f46e12d.png)

## 题解