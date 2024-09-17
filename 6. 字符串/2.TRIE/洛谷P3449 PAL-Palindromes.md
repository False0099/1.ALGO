# [POI 2006] PAL-Palindromes

## 题面翻译

### 题目描述

Johnny 喜欢玩文字游戏。

他写下了 $n$ 个回文串，随后将这些串两两组合，合并成一个新串。容易看出，一共会有 $n^2$ 个新串。

两个串组合时顺序是任意的，即 `a` 和 `b` 可以组合成 `ab` 和 `ba`，另外自己和自己组合也是允许的。

现在他想知道这些新串中有多少个回文串，你能帮帮他吗？

### 输入格式

第一行一个整数 $n$。

接下来 $n$ 行，第 $i$ 行包含一个数 $a_i$ 和一个长度为 $a_i$ 的回文串。

保证所有串只包含小写字母，且所有串两两不同，所有回文串的长度和不超过 $2 \times 10^6$。

### 输出格式

输出一个整数，代表满足条件的新串的数量。

## 题目描述

Little Johnny enjoys playing with words. He has chosen $n$ palindromes (a palindrome is a wordthat reads the same when the letters composing it are taken in the reverse order, such as dad, eye orracecar for instance) then generated all $n^2$ possible pairs of them and concatenated the pairs intosingle words. Lastly, he counted how many of the so generated words are palindromes themselves.

However, Johnny cannot be certain of not having comitted a mistake, so he has asked you to repeatthe very same actions and to give him the outcome. Write a programme which shall perform thistask for you.

TaskWrite a programme which:

Reads the palindromes given by Johnny from the standard input,        determines the number of words formed out of pairs of palindromes from the input, which are palindromes    themselves,        writes the outcome to the standard output.

## 输入格式

The first line of the standard input contains a single integer $n$, $n\ge 2$, denoting the number ofpalindromes given by Johnny. The following $n$ lines contain a description of the palindromes. The $(i+1)$ 'st line contains a single positive integer $a_i$ denoting the length of $i$ 'th palindrome and apalindrome of $a_i$ small letters of English alphabet. The number $a_i$ is separated from the palindromeby a single space. The palindromes in distinct lines are distinct. The total length of all palindromesdoes not exceed $2\ 000\ 000$.


## 输出格式

The first and only line of the standard output should contain a single integer: the number of distinctordered pairs of palindromes which form a palindrome upon being concatenated.

## 样例 #1

### 样例输入 #1

```
6
2 aa
3 aba
3 aaa
6 abaaba
5 aaaaa
4 abba
```

### 样例输出 #1

```
14
```


## 题解
首先，我们需要发现（抄）得到一个有趣的性质，如果一对字符是我们的答案，那么我们必须要满足：
1. 我们较短长度的那一个字符串使我们较长长度字符串的某一个前缀或者后缀