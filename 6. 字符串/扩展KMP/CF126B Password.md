# Password

## 题面翻译

Asterix，Obelix 和他们的临时伙伴 Suffix、Prefix 已经最终找到了和谐寺。然而和谐寺大门紧闭，就连 Obelix 的运气也没好到能打开它。

不久他们发现了一个字符串 S（|S|<=1000000），刻在和谐寺大门下面的岩石上。Asterix 猜想那一定是打开寺庙大门的密码，于是就大声将字符串朗读了出来，然而并没有什么事发生。于是 Asterix 又猜想密码一定是字符串 S 的子串 T。

Prefix 认为 T 是 S 的前缀，Suffix 认为 T 是 S 的后缀，Obelix 却认为 T 应该是 S 中的某一部分，也就是说，T 既不是 S 的前缀，也不是 S 的后缀。

Asterix 选择子串 T 来满足所有伙伴们的想法。同时，在所有可以被接受的子串变形中，Asterix 选择了最长的一个（因为 Asterix 喜欢长的字符串）当 Asterix 大声读出子串 T 时，寺庙的大门开了。 （也就是说，你需要找到既是 S 的前缀又是 S 的后缀同时又在 S 中间出现过的最长子串）

现在给你字符串 S，你需要找到满足上述要求的子串 T。

输入格式：

一个长度在[1,1000000]间的只包含小写字母的字符串 S。

输出格式：

输出子串 T，如果 T 不存在，输出 "Just a legend"，不包含引号。

感谢@Chemist 提供的翻译

## 题目描述

Asterix, Obelix and their temporary buddies Suffix and Prefix has finally found the Harmony temple. However, its doors were firmly locked and even Obelix had no luck opening them.

A little later they found a string $ s $ , carved on a rock below the temple's gates. Asterix supposed that that's the password that opens the temple and read the string aloud. However, nothing happened. Then Asterix supposed that a password is some substring $ t $ of the string $ s $ .

Prefix supposed that the substring $ t $ is the beginning of the string $ s $ ; Suffix supposed that the substring $ t $ should be the end of the string $ s $ ; and Obelix supposed that $ t $ should be located somewhere inside the string $ s $ , that is, $ t $ is neither its beginning, nor its end.

Asterix chose the substring $ t $ so as to please all his companions. Besides, from all acceptable variants Asterix chose the longest one (as Asterix loves long strings). When Asterix read the substring $ t $ aloud, the temple doors opened.

You know the string $ s $ . Find the substring $ t $ or determine that such substring does not exist and all that's been written above is just a nice legend.

## 输入格式

You are given the string $ s $ whose length can vary from $ 1 $ to $ 10^{6} $ (inclusive), consisting of small Latin letters.

## 输出格式

Print the string $ t $ . If a suitable $ t $ string does not exist, then print "Just a legend" without the quotes.

## 样例 #1

### 样例输入 #1

```
fixprefixsuffix
```

### 样例输出 #1

```
fix
```

## 样例 #2

### 样例输入 #2

```
abcdabc
```

### 样例输出 #2

```
Just a legend
```

## 题解
本体要我们求一个最长子串，既是前缀又是后缀，那么我们就看也 i 考虑用我们的扩展 kmp，扩展 kmp 中的 z 函数，并且我们 z 函数到我们的结尾得距离，恰好为我们的 $z[i]$，那么我们就能求得我们的答案。

```cpp
#include<bits/stdc++.h>
#define F(i,l,r) for(register int i=l;i<=r;i++)
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define p_b push_back
#define m_p make_pair
#define il inline
using namespace std;
const int N=1e6+5;
int z[N],n;
char s1[N];
il void get_z(char *s1){//获得串s1的z数组
	int L=0,R=0;//这个L，R最后是用来看当前开始的最大匹配长度的
	F(i,1,n-1) {
		if(i>R) {//如果i>R，那么说明这个区间的信息一点点都没有被刚刚的递推所更新到，那么怎么办呢？只能一个一个区匹配咯。
			L=i,R=i;
			while(R<n&&s1[R-L]==s1[R]) R++;//这里的一个一个匹配看上去最劣的复杂度是O(n)的，那么整个算法不就是O(n^2)了么？
            //但是你想，我们这里的递推是因为当前的点i是没有被之前的递推所覆盖到的，也就是说我们不知道这里到底是个什么情况。但是当我们此处递推了很多，那后面（看后面else的第一个if）是不是不用递推，直接O(1)获得答案了？
			z[i]=--R-L+1;//最后的R多加了一个，手动模拟就想清楚了
		}
		else {
			int k=i-L;//那么此处就是Z算法的精华了，它利用了L，R单调不减的特性求出了i这个位置一定是在哪里被求过z了的
			if(z[k]<R-i+1) z[i]=z[k];//如果i这个位置的z全部都被求过了，那么直接更新（应该是z[k]+i-1<R，这样应该更好理解）
			else {//不然就说明我们只有一部分被更新了，那么把剩下的烂摊子继续一个个匹配完即珂
				L=i;
				while(R<n&&s1[R-L]==s1[R]) R++;
				z[i]=--R-L+1;
			}
		}
	}
}
int maxn=-10,pos;//maxn是本题的另一个核心
//maxn是来看当前最大的z[i]的，如果说我们已经找到了一个后缀前缀，并且在i前面的最大的z[i]是要比n-i长的，说明在中间至少也出现了一个相同的子串（举个栗子就能懂啦！）
int main() {
	scanf("%s",s1);
	n=strlen(s1);
	get_z(s1);
	F(i,1,n-1) {
		if(z[i]+i==n&&maxn>=n-i) {//显然,z[i]+i==n就说明了这个串既是前缀又是后缀，因为i+与从i开始与总串的前缀匹配长度的最大值一旦等于了n，那么说明这个串从i开始一直接到了最后。
			pos=i;//如果符合条件就记录一下合法的位置
            //此处没有判断最大长度是因为我枚举的循环就已经保证了长度是由大向小递减的了
			break;//break;
		}
		maxn=max(maxn,z[i]);//寻找最大的z[i]
	}
	if(!pos) puts("Just a legend");//没有就输出这个
	else F(i,0,n-pos-1) printf("%c",s1[i]);//有就输出呗
	return 0;
}
```