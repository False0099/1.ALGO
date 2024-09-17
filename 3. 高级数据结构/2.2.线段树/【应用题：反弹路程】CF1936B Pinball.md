# Pinball

## 题面翻译

有一个长度为 $n$ 的一维网格。网格的第 $i$ 个单元格包含字符 $s_i$ ，是“<”或“>”。当弹球放在其中一个格子上时，它会按照以下规则移动：

如果弹球位于第 $i$ 个格子上且 $s_i$ 为 '<'，则弹球在下一秒会向左移动一个单元格；如果 $s_i$ 为 '>'，则向右移动一个单元格。弹球移动后，字符 $s_i$  会反转（即，如果 $s_i$ 原来是 '<'，则变为 '>'，反之亦然）。无论是离开左边界还是从右边界, 当弹球离开网格时，它都会停止移动。

您需要回答 $t（1\le t \le 10^5）$ 个独立的查询。每一组查询中有一个长度 $n（1\le n\le 5\times10^5）$，及一个只包含 “<” 和 “>”的字符串。弹球可以放在任意一个位置上。对于每个查询，在同一行输出 $n$ 个数，第 $i$ 个数表示弹球放置在第 $i$ 格时离开网格的时长，用空格隔开。

## 题目描述

There is a one-dimensional grid of length $ n $ . The $ i $ -th cell of the grid contains a character $ s_i $ , which is either '&lt;' or '&gt;'.

When a pinball is placed on one of the cells, it moves according to the following rules:

- If the pinball is on the $ i $ -th cell and $ s_i $ is '&lt;', the pinball moves one cell to the left in the next second. If $ s_i $ is '&gt;', it moves one cell to the right.
- After the pinball has moved, the character $ s_i $ is inverted (i. e. if $ s_i $ used to be '&lt;', it becomes '&gt;', and vice versa).
- The pinball stops moving when it leaves the grid: either from the left border or from the right one.

You need to answer $ n $ independent queries. In the $ i $ -th query, a pinball will be placed on the $ i $ -th cell. Note that we always place a pinball on the initial grid.

For each query, calculate how many seconds it takes the pinball to leave the grid. It can be shown that the pinball will always leave the grid within a finite number of steps.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). The description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 5 \cdot 10^5 $ ).

The second line of each test case contains a string $ s_1 s_2 \ldots s_{n} $ of length $ n $ consisting of characters '&lt;' and '&gt;'.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, for each $ i $ ( $ 1 \le i \le n $ ) output the answer if a pinball is initially placed on the $ i $ -th cell.

## 样例 #1

### 样例输入 #1

```
3
3
><<
4
<<<<
6
<><<<>
```

### 样例输出 #1

```
3 6 5 
1 2 3 4 
1 4 7 10 8 1
```

## 提示

In the first test case, the movement of the pinball for $ i=1 $ is shown in the following pictures. It takes the pinball $ 3 $ seconds to leave the grid.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1936B/9b874ab4c5ee491df87b5d2616ead8d797821647.png)The movement of the pinball for $ i=2 $ is shown in the following pictures. It takes the pinball $ 6 $ seconds to leave the grid.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1936B/b4fdbd3674e32422b13cf88676e6ccbb2eef3a53.png)

## 题解
本题我们考虑我们的**反弹路程**怎么求解，对于我们的反弹路程，我们的关键就是算清我们的每一步是从哪里开始，到哪里结束的。我们发现，我们每一次假设我们向右走，我们会找到**右侧的第一个左拐停止**，**然后再去找左边的第一个右拐**。以此类推。

最后，我们的每一段路程就是我们的 $\sum r_{i}-\sum l_{i}$。这个就是我们向右走的能够到达的最终的结果。最后，我们再枚举我们的起始位置和我们的方向即可。

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
char s[500005];
int cntl[500005],cntr[500005];
ll suml[500005],sumr[500005];
int sign(char c){
	if(c=='>')return -1;
	return 1;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n;
		scanf("%d",&n);
		scanf("%s",s+1);
		int pl=0,pr=0;
		for(int i=1;i<=n;i++){
			if(s[i]=='<'){
				cntl[i]=cntl[i-1]+1,cntr[i]=cntr[i-1];
				suml[pl+1]=suml[pl]+i;
				++pl;
			}
			else{
				cntl[i]=cntl[i-1],cntr[i]=cntr[i-1]+1;
				sumr[pr+1]=sumr[pr]+i;
				++pr;
			}
		}
		for(int i=1;i<=pl;i++)printf("%lld ",(suml[i]-suml[cntl[i]]-sumr[cntr[i-1]])*2+sign(s[i])*i);
		for(int i=pl+1;i<=n;i++)printf("%lld ",n+1+(suml[pl]-suml[cntl[i]]-sumr[cntr[i-1]]+sumr[i-1-pl])*2+sign(s[i])*i);
		printf("\n");
	}
	return 0;
}
// quod erat demonstrandum

```