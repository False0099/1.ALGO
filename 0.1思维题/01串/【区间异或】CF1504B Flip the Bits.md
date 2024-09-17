# Flip the Bits

## 题面翻译

有长度为 $n$ 的两个 01 字符串 $a$ 和 $b$。如果对于一个 $i$，$a$ 的区间 $[1,i]$ 中，$0$ 的数量等于 $1$ 的数量，则你可以将这个区间的所有 $1$ 变成 $0$，$0$ 变成 $1$。求是否可以将 $a$ 变成 $b$。

## 题目描述

There is a binary string $ a $ of length $ n $ . In one operation, you can select any prefix of $ a $ with an equal number of $ 0 $ and $ 1 $ symbols. Then all symbols in the prefix are inverted: each $ 0 $ becomes $ 1 $ and each $ 1 $ becomes $ 0 $ .

For example, suppose $ a=0111010000 $ .

- In the first operation, we can select the prefix of length $ 8 $ since it has four $ 0 $ 's and four $ 1 $ 's: $ [01110100]00\to [10001011]00 $ .
- In the second operation, we can select the prefix of length $ 2 $ since it has one $ 0 $ and one $ 1 $ : $ [10]00101100\to [01]00101100 $ .
- It is illegal to select the prefix of length $ 4 $ for the third operation, because it has three $ 0 $ 's and one $ 1 $ .

Can you transform the string $ a $ into the string $ b $ using some finite number of operations (possibly, none)?

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1\le n\le 3\cdot 10^5 $ ) — the length of the strings $ a $ and $ b $ .

The following two lines contain strings $ a $ and $ b $ of length $ n $ , consisting of symbols $ 0 $ and $ 1 $ .

The sum of $ n $ across all test cases does not exceed $ 3\cdot 10^5 $ .

## 输出格式

For each test case, output "YES" if it is possible to transform $ a $ into $ b $ , or "NO" if it is impossible. You can print each letter in any case (upper or lower).

## 样例 #1

### 样例输入 #1

```
5
10
0111010000
0100101100
4
0000
0000
3
001
000
12
010101010101
100110011010
6
000111
110100
```

### 样例输出 #1

```
YES
YES
NO
YES
NO
```

## 提示

The first test case is shown in the statement.

In the second test case, we transform $ a $ into $ b $ by using zero operations.

In the third test case, there is no legal operation, so it is impossible to transform $ a $ into $ b $ .

In the fourth test case, here is one such transformation:

- Select the length $ 2 $ prefix to get $ 100101010101 $ .
- Select the length $ 12 $ prefix to get $ 011010101010 $ .
- Select the length $ 8 $ prefix to get $ 100101011010 $ .
- Select the length $ 4 $ prefix to get $ 011001011010 $ .
- Select the length $ 6 $ prefix to get $ 100110011010 $ .

In the fifth test case, the only legal operation is to transform $ a $ into $ 111000 $ . From there, the only legal operation is to return to the string we started with, so we cannot transform $ a $ into $ b $ .
\

## 题解
给定两个 01 串，可以选择一些位置，然后分别前缀取反，这些位置满足条件：前缀 0 和 1 的个数相等，询问经过若干次变换能不能使得第一个串变化成第二个串。

## Solution
首先我们有一个性质：如果我们有第一个位置的大小等于我们的最后一个位置，那么我们一定有下面的性质：我们 1-6+2-5=1-2+5-6，也就是说，我们这一题只需要判断最后是要修改的位置是否有偶数个，如果有的话，那么我们就认为我们是合理的。

首先，根据异或的性质，我们很容易发现如果一个位置我们选择偶数次操作，那就是没有意义的，如果是奇数次，那全部都跟操作一次等价。

那么相当于我们这样想：对于每一个不同的位置，它以及它后面的位置被选的总次数必须是奇数次，而对于相同的位置则必须是偶数次。

（也就是一个必须被取反，一个必须不能被取反。）

那么从前往后显然不好考虑，因为我们不知道后面的点被选择的次数，于是我们可以考虑从后往前贪心。

我们考虑记一个变量为 now 表示当前点之后的位置被我们选择了（奇数/偶数）次。（true 为奇数。）

然后讨论当前点的两种情况：

如果相同，那么如果 now 为 true，则当前点必选，因为我们要让当前点被覆盖到的次数为偶数才行，如果 now 为 false ，那不管。

如果不同，那么如果 now 为 true，则当前点不选，因为我们要让当前点被覆盖到的次数为奇数，如果 now 为 false ，那当前点必选，因为我们要使得当前这个位置的后缀被选次数和是个奇数才能使得这一位反过来。

那么我们考虑求出所有必选位置怎么判无解：

先预处理每一个位置可不可选，然后和看必选位置是不是这个可选位置的子集即可。

这样做只有遍历一次的复杂度，所以时间复杂度 O(n) 。

最后，代码也不难给出。

本题的关键性质在于：我们对于每一个位置上的操作：只有两种，一种是取反后比较，一种是不取反直接比较。

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x){
    x=0;char ch=getchar();bool f=false;
    while(!isdigit(ch)) f|=ch=='-',ch=getchar();
    while(isdigit(ch))  x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x=f?-x:x;
}
template <typename T>
inline void write(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10^48);
}
#define ll long long
const int N=3e5+5,M=1e6+5,INF=1e9+7;
int n,m,q,T,t,Ans;
int a[N],b[N];
char str1[N],str2[N];
int main(){
	read(T);
	while(T--){
		read(n);int sum=0,now=0;bool flag=0;
		scanf("%s",str1+1),scanf("%s",str2+1);
		for(int i=1;i<=n;i++){
			a[i]=b[i]=0;
			sum+=(str1[i]=='1'?1:-1);
			if(sum==0) a[i]=true;
			if(str1[i]!=str2[i]) b[i]=true;
		}
		for(int i=n;i>=1;i--){
			if(b[i]^now){
				if(a[i]) now^=1;
				else flag=true;
			}
		}
		if(flag) puts("NO");
		else puts("YES");
	}
    return 0;
}
```