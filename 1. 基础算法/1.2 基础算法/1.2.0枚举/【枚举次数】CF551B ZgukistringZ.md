# ZgukistringZ

## 题面翻译

要把一个字符串 a，通过调换一些字符的位置变成字符串 k，使得字符串 k 中含有尽量多的字符串 b 和字符串 c。输出更改后的字符串 a，若有多解输出任意一个。

## 题目描述

Professor GukiZ doesn't accept string as they are. He likes to swap some letters in string to obtain a new one.

GukiZ has strings $ a $ , $ b $ , and $ c $ . He wants to obtain string $ k $ by swapping some letters in $ a $ , so that $ k $ should contain as many **non-overlapping** substrings equal either to $ b $ or $ c $ as possible. Substring of string $ x $ is a string formed by consecutive segment of characters from $ x $ . Two substrings of string $ x $ overlap if there is position $ i $ in string $ x $ occupied by both of them.

GukiZ was disappointed because none of his students managed to solve the problem. Can you help them and find one of possible strings $ k $ ?

## 输入格式

The first line contains string $ a $ , the second line contains string $ b $ , and the third line contains string $ c $ ( $ 1<=|a|,|b|,|c|<=10^{5} $ , where $ |s| $ denotes the length of string $ s $ ).

All three strings consist only of lowercase English letters.

It is possible that $ b $ and $ c $ coincide.

## 输出格式

Find one of possible strings $ k $ , as described in the problem statement. If there are multiple possible answers, print any of them.

## 样例 #1

### 样例输入 #1

```
aaa
a
b
```

### 样例输出 #1

```
aaa
```

## 样例 #2

### 样例输入 #2

```
pozdravstaklenidodiri
niste
dobri
```

### 样例输出 #2

```
nisteaadddiiklooprrvz
```

## 样例 #3

### 样例输入 #3

```
abbbaaccca
ab
aca
```

### 样例输出 #3

```
ababacabcc
```

## 提示

In the third sample, this optimal solutions has three non-overlaping substrings equal to either $ b $ or $ c $ on positions $ 1–2 $ ( $ ab $ ), $ 3–4 $ ( $ ab $ ), $ 5–7 $ ( $ aca $ ). In this sample, there exist many other optimal solutions, one of them would be $ acaababbcc $ .

## 题解
直接快进到我们的下面的问题：
你现在有 $k$ 种字母，每一种字母的数量有 $a_k$ 个，现在，你有两种方案，一种是构造 $a$,这样我们的单次划分就是 $\{m,d_{m}\}$,其中我们的 $m$ 表示我们的颜色，我们的 $d_{m}$ 表示我们消耗多少个数。

**注意，我们本题不考虑我们字符串之间重叠的情况，如果考虑字符串重叠的情况，我们应该用背包 dp 来搜索进行**

如果不考虑我们的字符串重叠，我们可以考虑枚举我们勇第一类用了多少个，然后再贪心的让所有的都去符合我们的第二类。于是，我们就能画出我们的答案。