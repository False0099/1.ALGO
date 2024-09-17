# FAVDICE - Favorite Dice

## 题面翻译

一个 n 面的骰子，求期望掷几次能使得每一面都被掷到。

## 题目描述

BuggyD loves to carry his favorite die around. Perhaps you wonder why it's his favorite? Well, his die is magical and can be transformed into an N-sided unbiased die with the push of a button. Now BuggyD wants to learn more about his die, so he raises a question:

What is the expected number of throws of his die while it has **N** sides so that each number is rolled at least once?

## 输入格式

The first line of the input contains an integer **t**, the number of test cases. **t** test cases follow.

Each test case consists of a single line containing a single integer **N** (1 <= **N** <= 1000) - the number of sides on BuggyD's die.

## 输出格式

For each test case, print one line containing the expected number of times BuggyD needs to throw his **N**-sided die so that each number appears at least once. The expected number must be accurate to 2 decimal digits.

## 样例 #1

### 样例输入 #1

```
2
1
12
```

### 样例输出 #1

```
1.00
37.24
```


## 题解
因为我们这一题的每一个的概率是相等的，我们就可以用我们期望的概率来计算，但因为我们这一题是一个无限的概率，理论上我们由无限次，这个时候，我们就可以用我们概率论里的公式来进行一波推导即可。
我们假设 $f[i]$ 表示我们已经投掷到过 i 面，还期望透支多少次筛子使得我们每一面都被投掷到，我们有两种情况：
1. 我们由 i/n 的概率，保持现在的状态
2. 我们由 $\frac{n-i}{n}$ 的概率，让我们的状态进 1 位。于是我们就有

$f[i]=f[i+1]+\frac{n}{n+1}$

于是我们就可以直接 dp。

```cpp
#include <cstdio>
#include <fstream>
using namespace std;
const int maxn = 1005;
//{{{cin
struct IO{
	template<typename T>
	IO & operator>>(T&res){
		res=0;
		bool flag=false;
		char ch;
		while((ch=getchar())>'9'||ch<'0')	 flag|=ch=='-';
		while(ch>='0'&&ch<='9') res=(res<<1)+(res<<3)+(ch^'0'),ch=getchar();
		if (flag)	 res=~res+1;
		return *this;
	}
}cin;
//}}}
int T,n;
double f[maxn];//f[i] -> 有了i个面，变成拥有n个面的期望
int main()
{
	freopen("p1026.in","r",stdin);
	freopen("p1026.out","w",stdout);
	cin>>T;
	while (T--){
		cin>>n;
		f[n]=0;
		for (int i=n-1;i>=0;--i)	f[i]=f[i+1]+1.0*n/(n-i);
		printf("%.2lf\n",f[0]);
	}
	return 0;
}
```