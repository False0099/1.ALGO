# [POI 2006] OKR-Periods of Words

## 题面翻译

对于一个仅含小写字母的字符串 $a$，$p$ 为 $a$ 的前缀且 $p\ne a$，那么我们称 $p$ 为 $a$ 的 proper 前缀。

规定字符串 $Q$（可以是空串）表示 $a$ 的周期，当且仅当 $Q$ 是 $a$ 的 proper 前缀且 $a$ 是 $Q+Q$ 的前缀。

例如 `ab` 是 `abab` 的一个周期，因为 `ab` 是 `abab` 的 proper 前缀，且 `abab` 是 `ab+ab` 的前缀。

求给定字符串所有前缀的最大周期长度之和。

## 题目描述

A string is a finite sequence of lower-case (non-capital) letters of the English alphabet. Particularly, it may be an empty sequence, i.e. a sequence of 0 letters. By A=BC we denotes that A is a string obtained by concatenation (joining by writing one immediately after another, i.e. without any space, etc.) of the strings B and C (in this order). A string P is a prefix of the string !, if there is a string B, that A=PB. In other words, prefixes of A are the initial fragments of A. In addition, if P!=A and P is not an empty string, we say, that P is a proper prefix of A.


A string Q is a period of Q, if Q is a proper prefix of A and A is a prefix (not necessarily a proper one) of the string QQ. For example, the strings abab and ababab are both periods of the string abababa. The maximum period of a string A is the longest of its periods or the empty string, if A doesn't have any period. For example, the maximum period of ababab is abab. The maximum period of abc is the empty string.

Task Write a programme that:

Reads from the standard input the string's length and the string itself, calculates the sum of lengths of maximum periods of all its prefixes, writes the result to the standard output.

## 输入格式

In the first line of the standard input there is one integer $k$ ($1\le k\le 1\ 000\ 000$) - the length of the string. In the following line a sequence of exactly $k$ lower-case letters of the English alphabet is written - the string.

## 输出格式

In the first and only line of the standard output your programme should write an integer - the sum of lengths of maximum periods of all prefixes of the string given in the input.

## 样例 #1

### 样例输入 #1

```
8
babababa
```

### 样例输出 #1

```
24
```


## 题解
我们等价于 $p\mathrm{re}(a,i)$ 的每一个前缀的最长周期，也就是 $a$ 的每个前缀的最小 $border$。
前缀 $p\mathrm{re}(a,i)$ 的最短 $border$ 就是 $i\to$ 根这一条链上距离根最近的那个点。
我们为此构建一颗 fail 树，在 fail 树上我们采用类似并查集的方法，求出答案后，直接连一条求这个点到根节点的边，存储我们的答案，求出每一个点到我们的根节点的就是 $o(n)$ 的复杂度。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
char a[1000010];int n,fail[1000010];
int main(){
    scanf("%d",&n);scanf("%s",a);int i,j;ll cnt=0;
    fail[0]=fail[1]=0;j=0;
    for(i=1;i<n;i++){//求解next
        while(j&&(a[i]!=a[j])) j=fail[j];
        j+=(a[i]==a[j]);fail[i+1]=j;
    }
    for(i=1;i<=n;i++){
        j=i;
        while(fail[j]) j=fail[j];
        if(fail[i]!=0) fail[i]=j;//记忆化
        cnt+=i-j;
    }
    printf("%lld",cnt);
}
```