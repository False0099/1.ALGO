# BA-String

## 题面翻译

您拥有一个整数 $k$，以及一个由字符 `a` 与字符 `*` 组成的长度为 $n$ 的字符串。

在这其中，每一个星号都**必须**替换成 $0\sim k$ 个字符 `b`，在所有的星号替换完成后，得到的字符串我们称为 `BA-String`。

请您求出给定字符串所转化出的字典序第 $x$ 小的 `BA-String`。

本题采用多组数据，数据组数为 $T$。

$1\leqslant T,n,k\leqslant2000$

$1\leqslant x\leqslant10^{18}$

## 题目描述

You are given an integer $ k $ and a string $ s $ that consists only of characters 'a' (a lowercase Latin letter) and '\*' (an asterisk).

Each asterisk should be replaced with several (from $ 0 $ to $ k $ inclusive) lowercase Latin letters 'b'. Different asterisk can be replaced with different counts of letter 'b'.

The result of the replacement is called a BA-string.

Two strings $ a $ and $ b $ are different if they either have different lengths or there exists such a position $ i $ that $ a_i \neq b_i $ .

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- In the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

Now consider all different BA-strings and find the $ x $ -th lexicographically smallest of them.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 2000 $ ) — the number of testcases.

The first line of each testcase contains three integers $ n $ , $ k $ and $ x $ ( $ 1 \le n \le 2000 $ ; $ 0 \le k \le 2000 $ ; $ 1 \le x \le 10^{18} $ ). $ n $ is the length of string $ s $ .

The second line of each testcase is a string $ s $ . It consists of $ n $ characters, each of them is either 'a' (a lowercase Latin letter) or '\*' (an asterisk).

The sum of $ n $ over all testcases doesn't exceed $ 2000 $ . For each testcase $ x $ doesn't exceed the total number of different BA-strings. String $ s $ contains at least one character 'a'.

## 输出格式

For each testcase, print a single string, consisting only of characters 'b' and 'a' (lowercase Latin letters) — the $ x $ -th lexicographically smallest BA-string.

## 样例 #1

### 样例输入 #1

```
3
2 4 3
a*
4 1 3
a**a
6 3 20
**a***
```

### 样例输出 #1

```
abb
abba
babbbbbbbbb
```

## 提示

In the first testcase of the example, BA-strings ordered lexicographically are:

1. A
2. Ab
3. Abb
4. Abbb
5. Abbbb

In the second testcase of the example, BA-strings ordered lexicographically are:

1. Aa
2. Aba
3. Abba

Note that string "aba" is only counted once, even though there are two ways to replace asterisks with characters 'b' to get it.

## 题解
我们首先发现，如果我们有一段连续的星号，那么我们可以把这些所有星号都合并为一个，然后我们这个位置能填写的最大个数就是好我们的 $k*cnt$。

于是我们可以考虑预处理我们的对应的连续星号，然后再去从后到前去处理我们的每一个连续星号应该填多少个。

这里，我们就非常类似于我们的一个进制转换，但是我们每一个位置上的进制是不同的。

```cpp
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
cin>>n>>k>>x;
cin>>str;
x--;
ret.clear();

reverse(str.begin(),str.end());
int pow=0;
rep(i,0,n-1)
{
    if(str[i]=='a')ret.pb('a');
    else
    {
        int len=1;
        while(i+len<=n-1&&str[i+len]=='*')
            len++;
        int base=len*k+1;
        rep(j,1,x%base)ret.pb('b');
        x/=base;
        i=i+len-1;
    }
}
reverse(ret.begin(),ret.end());
cout<<ret<<endl;
```