# Wonderful Randomized Sum

## 题面翻译

某人数学老师让他做一道难题。然后他不会，就来请你了。

给你一个数字序列，你可以选择它的某个前缀和后缀（可能是空的）中的每个数字都乘以 $-1$。前缀和后缀可以交叉也可以为空。问能得到的最大序列和是多少。

## 题目描述

Learn, learn and learn again — Valera has to do this every day. He is studying at mathematical school, where math is the main discipline. The mathematics teacher loves her discipline very much and tries to cultivate this love in children. That's why she always gives her students large and difficult homework. Despite that Valera is one of the best students, he failed to manage with the new homework. That's why he asks for your help. He has the following task. A sequence of $ n $ numbers is given. A prefix of a sequence is the part of the sequence (possibly empty), taken from the start of the sequence. A suffix of a sequence is the part of the sequence (possibly empty), taken from the end of the sequence. It is allowed to sequentially make two operations with the sequence. The first operation is to take some prefix of the sequence and multiply all numbers in this prefix by $ -1 $ . The second operation is to take some suffix and multiply all numbers in it by $ -1 $ . The chosen prefix and suffix may intersect. What is the maximum total sum of the sequence that can be obtained by applying the described operations?

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — amount of elements in the sequence. The second line contains $ n $ integers $ a_{i} $ ( $ -10^{4}<=a_{i}<=10^{4} $ ) — the sequence itself.

## 输出格式

The first and the only line of the output should contain the answer to the problem.

## 样例 #1

### 样例输入 #1

```
3
-1 -2 -3
```

### 样例输出 #1

```
6
```

## 样例 #2

### 样例输入 #2

```
5
-4 2 0 5 0
```

### 样例输出 #2

```
11
```

## 样例 #3

### 样例输入 #3

```
5
-1 10 -5 10 -2
```

### 样例输出 #3

```
18
```

## 题解
我们本题思路类似于 [[长期项目/1.算法题目/3. 高级数据结构/2.2.线段树/【最大子段和】 牛客寒假H Tokitsukaze and Power Battle (hard)]]，我们考虑按照我们答案的最终形态来进行分类，显然，我们可以分成下面的几类：
1. 纯下降
2. 先上升后下降
3. 下降上升下降
4. 先下降后上升

可以发现，一共是由这么四种方案来构成的，我们就可以先预处理出我们到每一个位置时，我们的上面四个信息的前缀和后缀分别是多少，然后我们再去考虑我们合并时怎么操作即可。

但是，我们有一种更简单的方法：我们通过我们的数学推导：
**设前缀为 A，后缀为 B，未变化部分的为 C。序列数字总和为 S（允许 A，B，C 都为空的情况，此时 A=B=C=0）**

** 因为 $A+B+C=S$，需求解为 $-（A+B）+C$ 的最大值**

所以 $-（A+B）+C$ 的最大值 = $-（S-C）+C$ 的最大值 = $2C-S$ 综上显然 S 是定值，我们要做的就是让 C 最大，问题就变成了求最大子段和了。

然后我们就可以直接求我们的最大子段和即可。