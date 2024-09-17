# Hamming Distance Sum

## 题面翻译

### 题目描述
  吉诺斯需要你的帮助。他被要求完成塞塔玛出的如下编程问题：  
  
  字符串 s 的长度被表示为 $\left|s\right|$。两个等长字符串 s 和 t 之间的“Hamming”距离被定义为 $\sum\limits_{i=1}^{\left|s\right|}\left|s_i-t_i\right|$，其中，$s_i$ 是字符串 s 的第 i 个字符，$t_i$ 是字符串 t 的第 i 个字符。  
  
  比如说，字符串“0011”和字符串“0110”之间的“Hamming”距离为 $\left|0-0\right|+\left|0-1\right|+\left|1-1\right|+\left|1-0\right|=0+1+0+1=2$。
  
  给定两个字符串 a 和 b，找到字符串 a 和所有字符串 b 的长度为 $\left|a\right|$ 的子串之间的“Hamming”距离总和。
### 输入格式
  第一行输入二进制字符串 a（$1\leqslant\left|a\right|\leqslant200000$）。  
  
  第二行输入二进制字符串 b（$\left|a\right|\leqslant\left|b\right|\leqslant200000$）。  
  
  两个字符串均只包含字符“0”和“1”。
### 输出格式
  输出一个整数，即字符串 a 和所有字符串 b 的长度为 $\left|a\right|$ 的子串之间的“Hamming”距离总和。

## 题目描述

Genos needs your help. He was asked to solve the following programming problem by Saitama:

The length of some string $ s $ is denoted $ |s| $ . The Hamming distance between two strings $ s $ and $ t $ of equal length is defined as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF608B/26f9df019bcbe60126623115c0e18c5a58de8eee.png), where $ s_{i} $ is the $ i $ -th character of $ s $ and $ t_{i} $ is the $ i $ -th character of $ t $ . For example, the Hamming distance between string "0011" and string "0110" is $ |0-0|+|0-1|+|1-1|+|1-0|=0+1+0+1=2 $ .

Given two binary strings $ a $ and $ b $ , find the sum of the Hamming distances between $ a $ and all contiguous substrings of $ b $ of length $ |a| $ .

## 输入格式

The first line of the input contains binary string $ a $ ( $ 1<=|a|<=200000 $ ).

The second line of the input contains binary string $ b $ ( $ |a|<=|b|<=200000 $ ).

Both strings are guaranteed to consist of characters '0' and '1' only.

## 输出格式

Print a single integer — the sum of Hamming distances between $ a $ and all contiguous substrings of $ b $ of length $ |a| $ .

## 样例 #1

### 样例输入 #1

```
01
00111
```

### 样例输出 #1

```
3
```

## 样例 #2

### 样例输入 #2

```
0011
0110
```

### 样例输出 #2

```
2
```

## 提示

For the first sample case, there are four contiguous substrings of $ b $ of length $ |a| $ : "00", "01", "11", and "11". The distance between "01" and "00" is $ |0-0|+|1-0|=1 $ . The distance between "01" and "01" is $ |0-0|+|1-1|=0 $ . The distance between "01" and "11" is $ |0-1|+|1-1|=1 $ . Last distance counts twice, as there are two occurrences of string "11". The sum of these edit distances is $ 1+0+1+1=3 $ .

The second sample case is described in the statement.

## 题解
我们本体的思路是：枚举我们的所有的可能的子串，然后计算我们每一个子串对应的是那些位置。**这样做，我们的时间复杂度是 $o(n^2)$，一定超市**。

我们考虑其他的方法，我们考虑枚举每一个位置作为我们的匹配位置能够匹配的 $s$ 中的字符数量是**连续的**，于是，我们可以求出我们的这一个返回，然后统计有哪些是不匹配的，我们就把他的总和记为 $s$。这个就是**单个位置的贡献**。

因此，我们就可以通过我们的上述方法来实现我们的全部计算。
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	ios::sync_with_stdio(false),cin.tie(0);
	string s;
	string t;
	cin>>s>>t;
	int n=s.length();
	int m=t.length();
	s=" "+s;
	t=" "+t;
	vector<int> pre(m+1,0);
	for(int i=1;t[i];i++){
		pre[i]=pre[i-1]+t[i]-'0';
	}
	int sum=0;
	for(int i=1;s[i];i++){
		int l=i;
		int r=m-(n-i);
		if(s[i]=='0'){
			sum+=pre[r]-pre[l-1];
		}else{
			sum+=(r-l+1)-(pre[r]-pre[l-1]);
		}
	}
	cout<<sum<<endl;
} 
```