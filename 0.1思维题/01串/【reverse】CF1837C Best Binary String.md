# Best Binary String

## 题面翻译

给定由 `1` `0` `?` 所组成的字符串，你需要用 `0` 或 `1` 替换 `?`。

我们将 $s_{l},s_{l+1},\dots,s_r$ 反转称为一次操作。

你要使通过“反转”操作使原字符串成为升序的操作次数尽可能的小。

问最终构造出的字符串，有多解输出其一。

## 题目描述

You are given a string $ s $ consisting of the characters 0, 1 and/or ?. Let's call it a pattern.

Let's say that the binary string (a string where each character is either 0 or 1) matches the pattern if you can replace each character ? With 0 or 1 (for each character, the choice is independent) so that the strings become equal. For example, 0010 matches ?01?, but 010 doesn't match 1??, ??, or ????.

Let's define the cost of the binary string as the minimum number of operations of the form "reverse an arbitrary contiguous substring of the string" required to sort the string in non-descending order.

You have to find a binary string with the minimum possible cost among those that match the given pattern. If there are multiple answers, print any of them.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 3 \cdot 10^4 $ ) — the number of test cases.

The first and only line of each test case contains the string $ s $ ( $ 1 \le |s| \le 3 \cdot 10^5 $ ) consisting of characters 0, 1, and/or ?.

The sum of the string lengths over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, print a binary string with the minimum possible cost among those that match the given pattern. If there are multiple answers, print any of them.

## 样例 #1

### 样例输入 #1

```
4
??01?
10100
1??10?
0?1?10?10
```

### 样例输出 #1

```
00011
10100
111101
011110010
```

## 提示

In the first test case of the example, the cost of the resulting string is $ 0 $ .

In the second test case, the cost of the resulting string is $ 2 $ : we can reverse the substring from the $ 1 $ -st character to the $ 5 $ -th character, and we obtain the string 00101. Then we reverse the substring from the $ 3 $ -rd to the $ 4 $ -th character, and we obtain the string 00011, which is sorted in non-descending order.


## 题解
我们这一题就是我们的根据我们的结果反推构造过程的一题，我们最后的形态一定是我们的 00000111111 类似的样子。

那么我们考虑我们应该怎么通过区间反转来构造我们的答案：
首先假设我们有 $10101010101$,那么我们第一次操作肯定是选择让我们的 $[0,1]$ 翻转，因为我们这个地方位置不对之后我们就有：$011010$,以此类推

再比如，我们有：$1110001001$，我们的每一次操作一定是交换一整段 0 和一整段 1，这里我们就是交换 $1，6$，交换后的结果就是：$0001111001$,之后，我们再去交换一整段 1，0 答案就是 $0000011111$,

于是我们不难发现，我们最后的次数就是我们的 1，0 段的个数。于是我们只需要统计 1，0 段的个数即可得到答案

```cpp
#include<bits/stdc++.h>

using namespace std;
int T;
string str;
signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>str;
		if(str[0]=='?') str[0]='0';
		for(int i=1;i<str.size();i++)
			if(str[i]=='?')
				str[i]=str[i-1];
		cout<<str<<"\n";
	}
	return 0;
}
```