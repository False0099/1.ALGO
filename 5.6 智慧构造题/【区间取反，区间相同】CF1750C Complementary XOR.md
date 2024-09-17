# Complementary XOR

## 题面翻译

你有两个 $\tt{01}$ 串 $a,b$，长度均为 $n$。你可以使用不超过 $n+5$ 次下面这种操作：

- 你选择两个下标 $l,r(1\le l\le r\le n)$。
- 对于所有的 $i\in[l,r]$，取反 $a_i$（也就是说，$a_i\gets1-a_i$，下面同理）。
- 对于所有的 $i\in[1,l)\cup(r,n]$，取反 $b_i$。

现在你的任务是判断是否可以通过使用不超过 $n+5$ 次这种操作让两个串里的所有元素都变成 $\tt0$。如果可以，输出一种可能的方案。可以证明，如果使用任意次操作可以达成目标，那么至少存在一种方案可以在 $n+5$ 次操作内达成目标。

$n\ge 2$，$\sum n\le 2\times10^5$。

## 题目描述

You have two binary strings $ a $ and $ b $ of length $ n $ . You would like to make all the elements of both strings equal to $ 0 $ . Unfortunately, you can modify the contents of these strings using only the following operation:

- You choose two indices $ l $ and $ r $ ( $ 1 \le l \le r \le n $ );
- For every $ i $ that respects $ l \le i \le r $ , change $ a_i $ to the opposite. That is, $ a_i := 1 - a_i $ ;
- For every $ i $ that respects either $ 1 \le i < l $ or $ r < i \le n $ , change $ b_i $ to the opposite. That is, $ b_i := 1 - b_i $ .

Your task is to determine if this is possible, and if it is, to find such an appropriate chain of operations. The number of operations should not exceed $ n + 5 $ . It can be proven that if such chain of operations exists, one exists with at most $ n + 5 $ operations.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^5 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the length of the strings.

The second line of each test case contains a binary string $ a $ , consisting only of characters 0 and 1, of length $ n $ .

The third line of each test case contains a binary string $ b $ , consisting only of characters 0 and 1, of length $ n $ .

It is guaranteed that sum of $ n $ over all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each testcase, print first "YES" if it's possible to make all the elements of both strings equal to $ 0 $ . Otherwise, print "NO". If the answer is "YES", on the next line print a single integer $ k $ ( $ 0 \le k \le n + 5 $ ) — the number of operations. Then $ k $ lines follows, each contains two integers $ l $ and $ r $ ( $ 1 \le l \le r \le n $ ) — the description of the operation.

If there are several correct answers, print any of them.

## 样例 #1

### 样例输入 #1

```
5
3
010
101
2
11
10
4
1000
0011
2
10
10
3
111
111
```

### 样例输出 #1

```
YES
1
2 2
NO
NO
YES
2
1 2
2 2
YES
2
1 1
2 3
```

## 提示

In the first test case, we can perform one operation with $ l = 2 $ and $ r = 2 $ . So $ a_2 := 1 - 1 = 0 $ and string $ a $ became equal to 000. $ b_1 := 1 - 1 = 0 $ , $ b_3 := 1 - 1 = 0 $ and string $ b $ became equal to 000.

In the second and in the third test cases, it can be proven that it's impossible to make all elements of both strings equal to $ 0 $ .

In the fourth test case, we can perform an operation with $ l = 1 $ and $ r = 2 $ , then string $ a $ became equal to 01, and string $ b $ doesn't change. Then we perform an operation with $ l = 2 $ and $ r = 2 $ , then $ a_2 := 1 - 1 = 0 $ and $ b_1 = 1 - 1 = 0 $ . So both of string $ a $ and $ b $ became equal to 00.

In the fifth test case, we can perform an operation with $ l = 1 $ and $ r = 1 $ . Then string $ a $ became equal to 011 and string $ b $ became equal to 100. Then we can perform an operation with $ l = 2 $ and $ r = 3 $ , so both of string $ a $ and $ b $ became equal to 000.

## 题解
我们给定两个长度相同的 01 串 $a,b$,每次操作可以选中两个下表 $l,r$,然后我们对于 $a$ 在 $(l,r)$ 内，全部取反，不在 $(l,r)$ 内的 b 全部取反，然后问我们能否让我们的最后两个串都变成 $0$。
首先我们有结论，我们要不每一位都不同，要不每一位都相同，否则我们无法构造出，例如我们的 010111 和 010111。我们就不可能构造出一种方法，使得我们的这个串变成全 0，但是我们异或和为 0.

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200001],b[200001];
int t,n,i,k,s;
bool f,g,h;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);k=s=f=g=h=0;
		for(i=1;i<=n;i++) scanf("%1d",&a[i]);
		for(i=1;i<=n;i++)
		{
			scanf("%1d",&b[i]);
			if(a[i]==b[i])f=1;
			else g=1;
		}
		if(f&&g)//判断
		{puts("NO");continue;
		}
		puts("YES");
		for(i=1;i<=n;i++)
			if(a[i])k++;
		s=k;
		if((f&&(k%2)) || (g&&(k%2==0)))s+=3,h=1;//此时多了3步操作，具体见上
		printf("%d\n",s);
		for(i=1;i<=n;i++)
			if(a[i])printf("%d %d\n",i,i);//先将a置零
		if(h)printf("1 %d\n1 1\n2 %d\n",n,n); 
	}
	return 0;
}
```