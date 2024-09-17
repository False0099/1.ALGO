# Mark and His Unfinished Essay

## 题面翻译

给定长度为 $n$ 的字符串 $s$，进行 $c$ 次操作，每次操作将 $s_l$ 到 $s_r$ 复制到字符串尾。全部操作结束后有 $q$ 次询问，每次询问字符串 $s$ 的第 $k$ 位。

$1≤n≤2⋅10^5,1\leq c\leq 40,1\leq q\leq 10^4,1≤l≤r≤10^{18},1≤k≤10^{18}$

数据保证 $r$ 不超过当前字符串长度，$k$ 不超过最终字符串长度。

By Wu_while

## 题目描述

One night, Mark realized that there is an essay due tomorrow. He hasn't written anything yet, so Mark decided to randomly copy-paste substrings from the prompt to make the essay.

More formally, the prompt is a string $ s $ of initial length $ n $ . Mark will perform the copy-pasting operation $ c $ times. Each operation is described by two integers $ l $ and $ r $ , which means that Mark will append letters $ s_l s_{l+1} \ldots s_r $ to the end of string $ s $ . Note that the length of $ s $ increases after this operation.

Of course, Mark needs to be able to see what has been written. After copying, Mark will ask $ q $ queries: given an integer $ k $ , determine the $ k $ -th letter of the final string $ s $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1\leq t\leq 1000 $ ) — the number of test cases.

The first line of each test case contains three integers $ n $ , $ c $ , and $ q $ ( $ 1\leq n\leq 2\cdot 10^5 $ , $ 1\leq c\leq 40 $ , and $ 1\leq q\leq 10^4 $ ) — the length of the initial string $ s $ , the number of copy-pasting operations, and the number of queries, respectively.

The second line of each test case contains a single string $ s $ of length $ n $ . It is guaranteed that $ s $ only contains lowercase English letters.

The following $ c $ lines describe the copy-pasting operation. Each line contains two integers $ l $ and $ r $ ( $ 1\leq l\leq r\leq 10^{18} $ ). It is also guaranteed that $ r $ does not exceed the current length of $ s $ .

The last $ q $ lines of each test case describe the queries. Each line contains a single integer $ k $ ( $ 1\leq k\leq 10^{18} $ ). It is also guaranteed that $ k $ does not exceed the final length of $ s $ .

It is guaranteed that the sum of $ n $ and $ q $ across all test cases does not exceed $ 2\cdot 10^5 $ and $ 10^4 $ , respectively.

## 输出格式

For each query, print the $ k $ -th letter of the final string $ s $ .

## 样例 #1

### 样例输入 #1

```
2
4 3 3
mark
1 4
5 7
3 8
1
10
12
7 3 3
creamii
2 3
3 4
2 9
9
11
12
```

### 样例输出 #1

```
m
a
r
e
a
r
```

## 提示

In the first test case, the copy-paste process is as follows.

- The first step is pasting string $ \texttt{mark} $ at the end, yielding the string $ \texttt{mark}\color{red}{\texttt{mark}} $ .
- The second step is pasting string $ \texttt{mar} $ at the end, yielding the string $ \texttt{markmark}\color{red}{\texttt{mar}} $ .
- The third step is pasting string $ \texttt{rkmark} $ at the end, yielding the string $ \texttt{markmarkmar}\color{red}{\texttt{rkmark}} $ .

In the second test case, the copy-paste process is as follows.

- The first step is pasting string $ \texttt{re} $ at the end, yielding the string $ \texttt{creamii}\color{red}{\texttt{re}} $ .
- The second step is pasting string $ \texttt{ea} $ at the end, yielding the string $ \texttt{creamiire}\color{red}{\texttt{ea}} $ .
- The third step is pasting string $ \texttt{reamiire} $ at the end, yielding the string $ \texttt{creamiireea}\color{red}{\texttt{reamiire}} $ .

## 题解
我们这一题的思路有点类似于我们的 ACW 5281, 我们想要计算出我们的第 k 个字符是多少，我们就需要知道他是在第几次复制之后产生的，这一点我们可以通过预处理我们每一个复制后，我们的最大长度来计算。另外，我们计算每一个复制时也是有一定的技巧，我们可以把任何一个非第一次的映射到我们的第一次映射，即我们每一次都检测我们的范围，如果我们的范围正好在我们的初始子串中，我们直接输出我们的初始字串中的元素。

```cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
const int N=2e5+15;
using namespace std;
typedef long long ll;

int t,c,q;
ll len[45],cp[45][2];//存储我们的复制字符
char a[N];

void solve(ll x){  / /递归求解，x 表示这次询问在之前那次操作时的下标
	int pt=0;
	if(x<=len[0]){printf("%c\n",a[x-1]);return;}
	while(len[pt]<x) ++pt;  //没有必要二分查找
	x-=len[--pt];  //减去先前字符串的长度
	solve(cp[pt+1][0]-1+x);  //字符串 s 粘贴位置的字符=对应复制位置的字符
	return;
}

int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%lld%d%d%s",&len[0],&c,&q,a);
		for(ll i=1;i<=c;++i)
			scanf("%lld%lld",&cp[i][0],&cp[i][1]),len[i]=len[i-1]+cp[i][1]-cp[i][0]+1; 
            	//输入时存储左，右端点，顺便处理长度
                
		while(q--){
			ll k;scanf("%lld",&k);
			solve(k);
			
		}
	}

	return 0;
}
```