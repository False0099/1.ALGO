最近 zzuli 发生了一个可怕的事件，校长为了督促 zzuli 的学生好好学习，把每个人的电子设备都给加了一个密码，聪明又勇敢的学霸要和校长作斗争，于是校长被迫说出了一个长度为 N(1≤N≤2000)的字符串 S，然而最后的密码是由 S 中所有字母构成字典序最小的字符串 T（起初 T 是一个空串）。但是要想知道最后的密码只能以下两种操作：

·从S的头部删除一个字符，加到T的尾部

·从S的尾部删除一个字符，加到T的尾部

目标是要构造字典序尽可能小的字符串

Input

第一行一个整数N（代表字符串S的长度） 接下来的2~N+1行是字符串S中的字母（只包含大写字母）

Output

**输出时每行最多80个字符**

Sample Input

6
A
C
D
B
C
B

Sample Output

ABCBCD

## 题解
这一题看上去显然是贪心，我们设两个指针，a 表示头指针，也就是队列首端， b 表示为指针，也就是队列末端。

下面是最好容易想到的策略：

1. 当 s[a]>s[b] ，我们肯定是会选 s[b] ，随之 b−− 。
2. 当 s[a]<s[b] ，我们肯定是会选 s[a] ，随之 a++ 。

但是，通过样例我们发现，会出现 s[a]=s[b] 情况，这种情况该怎么处理呢？

其实也很简单，我们找距离 s[a] 和 s[b] **最近**的且**不等于** s[a或b] 的字符，再比较它们大小即可。
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
char s[3010];
int n,i,a,b,j,p,q;
int main () {
	scanf ("%d",&n);
	for (i=1;i<=n;i++)
		cin>>s[i];
	a=1;
	b=n;
	for (i=1;i<=n;i++) {//从i开始枚举。
		for (j=i;j<=i+79&&j<=n;j++) {//每80个字符就换行。
			if (s[a]==s[b]) {
				p=a;
				q=b;
				while (s[p]==s[q]) {
					p++;
					q--;
				}//策略3。
				if (s[p]<=s[q]) {
					printf ("%c",s[a]);
					a++;
				} //这里又可以想到上面最简单的两种策略。
				else {
					printf ("%c",s[b]);
					b--;
				}
			}
			else {
				if (s[a]>s[b]) {
					printf ("%c",s[b]);
					b--;//策略1。
				} 
				else {
					printf ("%c",s[a]);
					a++;//策略2。
				}
			}
		}
		i+=79;//继续搜索下面的80个字符。
		puts ("");
	}
	return 0;
}
```