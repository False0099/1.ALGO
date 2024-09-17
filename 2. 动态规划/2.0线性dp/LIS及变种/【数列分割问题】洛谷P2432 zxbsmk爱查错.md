# Zxbsmk 爱查错

## 题目背景

Zxbsmk 在暑假回了一趟老家，见到了自己的外婆。然而他遇到了一个问题。

## 题目描述

外婆很喜欢给别人写信，然而因为年纪大了，信里面充斥着各种错误。所以 zxbsmk 打算帮外婆修正每个错误的句子。

因为外婆的文化水平很高，所以她写的句子都是英文句子，并且句子内的字母都是小写字母。然而 zxbsmk 的英语水平非常低，所以他买来了一本英语词典，词典里一共有 W (1<=W<=600) 个单词，每个单词的长度都不超过 25 个字母，而且都是由小写字母组成的。

那么再来看一下外婆的句子都有什么错误。例如，外婆写的一个句子是"catotail"，这并没有什么意义，因为一个多余的字母"o"出现了，所以正确的句子应该是"cattail"。

已知外婆的句子是由 L (2<=L<=300) 个字母组成的。其中有一些字母是多余的。现在，请你借助 zxbsmk 的词典，帮助他修正外婆的句子。而且你必须尽量少地去除多余的字母，使剩余的字母是一个合法的句子。

## 输入格式

第一行：输入两个整数 W 和 L。

第二行：输入 L 个字符，表示需要修正的句子。

之后的 W 行，每行输入一个合法的单词。

## 输出格式

一个整数，表示最少需要剔除的字母数。

## 样例 #1

### 样例输入 #1

```
2 8
catotail
cat
tail
```

### 样例输出 #1

```
1
```

## 提示

Catotail —> cattail


## 题解
我们本题看到我们的最少，我们应该一眼顶针，鉴定为 LIS 类 dp，然后我们就可以设 $dp[i]$ 表示我们以 $i$ 结尾，花费最少的代价是多少。于是，我们的转移就可以写成：
$dp[i]=min(dp[i],dp[j]+calc(i,j))$,其中我们的 $calc(i,j)$ 其实也就是截取我们的这个字符串，然后看我们有没有对应的字符串在我们的单词列表中出现过，如果有，我们就返回 0，否则我们就返回我们的 $len(i,j)$。这里判断我们单词的方法，哦我们可以考虑使用我们的哈希来做到 $o(1)$ 的判断。
这里，注意到我们的 $calc(i,j)$ 和我们的状态无关，所以我们可以考虑预处理我们的这一个，时间复杂度大约为 $o(n^2w)$,而我们之后的转移的时间复杂度大概为：$o(n^2)$

```cpp
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <stack>
#include <queue>
#include <vector>
#include <list>
#include <map>
#include <set>
using namespace std;
#define int long long
int f[305] ;
int n, m ;
string s ;
string d[605] ;
signed main() {
	cin >> n >> m ;
	cin >> s ;
	for(int i = 1 ; i <= n ; i++) cin >> d[i] ;
	memset(f, 0x3f, sizeof(f)) ; //要求最小值，初始化成INF
	f[0] = 0 ; //边界 f[0] = 0 
	for(int i = 1 ; i <= m ; i++) {
		f[i] = f[i - 1] + 1 ;
		for(int j = 1 ; j <= n ; j++) {
			int r1 = i, r2 = d[j].size() ;//指针的思想
			int flag = 1 ;//记录是否可以匹配成功
			while(r1 && r2) {
				if(d[j][r2 - 1] == s[r1 - 1]) r1--, r2-- ; //若匹配成功，各向前移一位
				else r1-- ; // 不然 把母串指针前移一位
				if(!r2) flag = 0 ; //匹配成功
			}
			if(!flag) f[i] = min(f[r1] + i - r1 - (int)d[j].size(), f[i]) ; // 若匹配成功，转移
		}
	}
	cout << f[m] ;
	return 0 ;
}


```