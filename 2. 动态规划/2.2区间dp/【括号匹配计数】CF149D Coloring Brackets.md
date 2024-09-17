# Coloring Brackets

## 题面翻译

### 题意描述

给出一个配对的括号序列（如 “$\texttt{(())()}$”、“$\texttt{()}$” 等，“$\texttt{)()}$”、“$\texttt{(()}$”是不符合要求的），对该序列按照以下方法染色。

1. 一个括号可以染成红色、蓝色或者不染色。
2. 一对匹配的括号需要且只能将其中一个染色。
3. 相邻两个括号颜色不能相同（但都可以不染色）。

求符合条件的染色方案数，对 $1000000007$ 取模。

### 输入格式

一行一个字符串 $s$，表示括号序列（$2 \leqslant |s| \leqslant 700$）。

### 输出格式

一个数字，表示染色的方案数（对 $1000000007$ 取模）。

## 题目描述

Once Petya read a problem about a bracket sequence. He gave it much thought but didn't find a solution. Today you will face it.

You are given string $ s $ . It represents a correct bracket sequence. A correct bracket sequence is the sequence of opening (" (") and closing (")") brackets, such that it is possible to obtain a correct mathematical expression from it, inserting numbers and operators between the brackets. For example, such sequences as " (())()" and " ()" are correct bracket sequences and such sequences as ")()" and " (()" are not.

In a correct bracket sequence each bracket corresponds to the matching bracket (an opening bracket corresponds to the matching closing bracket and vice versa). For example, in a bracket sequence shown of the figure below, the third bracket corresponds to the matching sixth one and the fifth bracket corresponds to the fourth one.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF149D/18f69b22b88c3423241947f144f2105947738984.png)You are allowed to color some brackets in the bracket sequence so as all three conditions are fulfilled:

- Each bracket is either not colored any color, or is colored red, or is colored blue.
- For any pair of matching brackets exactly one of them is colored. In other words, for any bracket the following is true: either it or the matching bracket that corresponds to it is colored.
- No two neighboring colored brackets have the same color.

Find the number of different ways to color the bracket sequence. The ways should meet the above-given conditions. Two ways of coloring are considered different if they differ in the color of at least one bracket. As the result can be quite large, print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

The first line contains the single string $ s $ ( $ 2<=|s|<=700 $ ) which represents a correct bracket sequence.

## 输出格式

Print the only number — the number of ways to color the bracket sequence that meet the above given conditions modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 样例 #1

### 样例输入 #1

```
(())
```

### 样例输出 #1

```
12
```

## 样例 #2

### 样例输入 #2

```
(()())
```

### 样例输出 #2

```
40
```

## 样例 #3

### 样例输入 #3

```
()
```

### 样例输出 #3

```
4
```

## 提示

Let's consider the first sample test. The bracket sequence from the sample can be colored, for example, as is shown on two figures below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF149D/ad2ef7e7b880dbb2c74d687b33fa5bb065b49c19.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF149D/e8aaa9835b069771e0292b8744b88177f6af495e.png)The two ways of coloring shown below are incorrect.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF149D/8d4dd8946c17ff03c7f54ecbd76a12b35b8a0520.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF149D/50e873752a97d444a4a9e6af478d696b8b1a6cff.png)
## 题解
我们本题的思路类似于我们的 [[【括号匹配计数】洛谷 P7914 括号序列]]，就是通过我们的状态设计来实现我们的计数问题。我们设计 $dp$ 的思路就是通过我们的枚举我们的左端点和右端点，并且**假设我们这两个端点已经是我们的一对匹配的括号**，然后再用乘法原理计算我们内部的可能的情况。 我们设 $dp[i][j]$ 表示我们的左端为 $i$,右侧为 $j$ 的方案数。

但是我们上面的方法是不太好进行转移的，于是我们只能通过我们的 $dp[i][j][col_{1}][col_{2}]$ 来实现我们的对应转移，接下来，我们考虑怎么处理我们的各个状态之间的转移。

规定：
0 表示我们这个位置的颜色为空
1 表示我们这个位置颜色为蓝
2 表示我们这个位置颜色为绿

初始化：
首先对于我们的一对括号来说，我们的 $dp[i][j][0][1],dp[i][j][1][0],dp[i][j][2][0],dp[i][j][0][2]$ 可以设置为 1，其他的都设置为 0（满足我们的一对括号颜色只有一种）

转移：
假设我们的 $(i,j)$ 是一对匹配的位置，那么我们的可能的方案书，就是我们下一对括号的可能方案书加起来：
$dp[i][j][0][1]=dp[i+1][j-1]\left[ \sum \right]\left[ \sum!1 \right]$。
$dp[i][j][1][0]=dp[i+1][j-1]\left[ \sum!1 \right]\left[ \sum \right]$
$dp[i][j][2][0]=dp[i+1][j-1]\left[ \sum!2 \right]\left[ \sum \right]$
$dp[i][j][0][2]=dp[i+1][j-1]\left[ \sum \right]\left[ \sum!2 \right]$

假设我们的 $(i,j)$ 不是匹配的位置，并且我们的左端点是左括号，那么我们的可能的形态就如下所示：
![[Pasted image 20240311112744.png]]

我们假设我们左端点对应的匹配位置为 $match[l]$,那么我们的方案数就是同构我们的：
$dp[l][r][s_{1}][s_{2}]=dp[l][match[l]][s][!s]*dp[match[l]+1][r][s][s_{2}]$

综上，我们就完成了我们的基本转移，但是我们现在还有一个问题就是，我们**怎么保证我们从不合法的状态转移**过来，这里，我们就需要使用我们的**记忆化搜索**来避免。只有我们再左端点为 $($,且右端点为 $)$ 的才会被我们设计状态。

综上，我们的代码如下：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;
const int maxn=710;
const int mod=1e9+7;
int n,match[maxn];
long long dp[maxn][maxn][3][3];
char s[maxn];
stack <int> St;

void dfs(int l,int r){
	if(l+1==r) dp[l][r][0][1]=dp[l][r][0][2]=dp[l][r][1][0]=dp[l][r][2][0]=1;
	else if(match[l]==r){
		dfs(l+1,r-1);
		for(int i=0;i<=2;i++)
			for(int j=0;j<=2;j++){
		        if(j!=1) dp[l][r][0][1]=(dp[l][r][0][1]+dp[l+1][r-1][i][j])%mod;
		        if(j!=2) dp[l][r][0][2]=(dp[l][r][0][2]+dp[l+1][r-1][i][j])%mod;
		        if(i!=1) dp[l][r][1][0]=(dp[l][r][1][0]+dp[l+1][r-1][i][j])%mod;
		        if(i!=2) dp[l][r][2][0]=(dp[l][r][2][0]+dp[l+1][r-1][i][j])%mod;
			}
	}
	else{
		dfs(l,match[l]),dfs(match[l]+1,r);
		for(int i=0;i<=2;i++)
			for(int j=0;j<=2;j++)
				for(int p=0;p<=2;p++)
					for(int q=0;q<=2;q++){
						if((j==1&&p==1)||(j==2&&p==2)) continue;
						dp[l][r][i][q]=(dp[l][r][i][q]+dp[l][match[l]][i][j]*dp[match[l]+1][r][p][q]%mod)%mod;
					}
	}
}

int main(){
	scanf("%s",s);
	n=strlen(s);
	for(int i=0;i<n;i++){
		if(s[i]=='(') St.push(i);
		else match[St.top()]=i,match[i]=St.top(),St.pop();
	}
	dfs(0,n-1);
	long long ans=0;
	for(int i=0;i<=2;i++)
		for(int j=0;j<=2;j++)
			ans=(ans+dp[0][n-1][i][j])%mod;
	printf("%lld\n",ans);
	return 0;
}
```
