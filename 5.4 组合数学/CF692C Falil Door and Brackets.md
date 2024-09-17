# Famil Door and Brackets

## 题面翻译

## 描述

Family Door 的生日就要到了，Gabi（Family Door 的好朋友）想要给他买一个礼物。Gabi 决定买一个只包含 ' ('、')' 的字符串，毕竟 Family Door 最喜欢的字符串是长度为 $n$ 的只包含 ' ('、')' 的字符串。

我们称一个只包含 ' ('、')' 的字符串“有效”当且仅当：
1. ' ('的数量等于')'的数量；
2. 对于该字符串的任意前缀，均满足' ('的数量大于等于')'的数量；

Gabi 买了一个长度为 $m$ 的只包含 ' ('、')' 的字符串 $S$。为了使它的长度达到 $n$ ，Gabi 要构造两个只包含' ('、')'的字符串 $P,Q$，然后将 $P,S,Q$ **顺次**连接得到字符串 $S'$ 。

给出 Gabi 买的字符串 $S$，要使 $S'$ 有效，Gabi 有多少种构造 $P,Q$ 的方案？（$P,Q$ 都可以为空）。

## 输入
第一行包括整数 $n,m$；第二行为长度为 $m$ 的字符串 $S$。

## 输出
输出一个正整数，表示构造 $P,Q$ 的方案数，答案对 $(10^9+7)$ 取模。

## 数据规模

$1\leq m\leq n\leq 100000,n-m\leq 2000$

## 题目描述

As Famil Door’s birthday is coming, some of his friends (like Gabi) decided to buy a present for him. His friends are going to buy a string consisted of round brackets since Famil Door loves string of brackets of length $ n $ more than any other strings!

The sequence of round brackets is called valid if and only if:

1. The total number of opening brackets is equal to the total number of closing brackets;
2. For any prefix of the sequence, the number of opening brackets is greater or equal than the number of closing brackets.

Gabi bought a string $ s $ of length $ m $ ( $ m<=n $ ) and want to complete it to obtain a valid sequence of brackets of length $ n $ . He is going to pick some strings $ p $ and $ q $ consisting of round brackets and merge them in a string $ p+s+q $ , that is add the string $ p $ at the beginning of the string $ s $ and string $ q $ at the end of the string $ s $ .

Now he wonders, how many pairs of strings $ p $ and $ q $ exists, such that the string $ p+s+q $ is a valid sequence of round brackets. As this number may be pretty large, he wants to calculate it modulo $ 10^{9}+7 $ .

## 输入格式

First line contains $ n $ and $ m $ ( $ 1<=m<=n<=100000, n-m<=2000 $ ) — the desired length of the string and the length of the string bought by Gabi, respectively.

The second line contains string $ s $ of length $ m $ consisting of characters ' (' and ')' only.

## 输出格式

Print the number of pairs of string $ p $ and $ q $ such that $ p+s+q $ is a valid sequence of round brackets modulo $ 10^{9}+7 $ .

## 样例 #1

### 样例输入 #1

```
4 1
(
```

### 样例输出 #1

```
4
```

## 样例 #2

### 样例输入 #2

```
4 4
(())
```

### 样例输出 #2

```
1
```

## 样例 #3

### 样例输入 #3

```
4 3
(((
```

### 样例输出 #3

```
0
```

## 提示

In the first sample there are four different valid pairs:

1. $ p= $ " (", $ q= $ "))"
2. $ p= $ " ()", $ q= $ ")"
3. $ p= $ "", $ q= $ " ())"
4. $ p= $ "", $ q= $ ")()"

In the second sample the only way to obtain a desired string is choose empty $ p $ and $ q $ .

In the third sample there is no way to get a valid sequence of brackets.

## 题解
我们这一题可以把我们的状态抽象为我们的类似于我们的卡特兰数，我们可以先计算出我们每一个 S 的前缀和最小是多少，然后这就决定了我们前面构造玩之后，最后我们的 P 中我们的前缀括号要比我们的后缀括号多多少个，然后我们的 Q 同时由我们的 S 和 P 中我们的括号数量决定，所以我们放在最后构造。
我们于是考虑一个计数 dp，设 $f[i][j]$ 表示我们前 i 个字符，左括号减去右括号数量为 j 的方案数
$f[i][j]=f[i-1][j-1]+f[i-1][j+1]$

接下来，我们就可以第一层枚举 P 的长度，第二层枚举 P 左括号减去右括号的数量，这里我们相当于要求我们的 $dp[i][j]$,接下来，就是我们 Q 的方案数，这里我们可以用一个等价思想，我们的 Q 的长度就是我们的 $n-m-i$，又因为我们的左右括号可以等价，我们就可以把我们的原串反过来看，最终方案书就是我们的 $f[n-m-i][j+cnt]$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rint register int
using namespace std;
namespace IO{
	#define File(x,y) freopen(#x,"r",stdin),freopen(#y,"w",stdout);
	inline int read(){
		int w=0,f=1; char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
		while(ch>='0'&&ch<='9'){w=(w<<3)+(w<<1)+(ch^48); ch=getchar();}
		return w*f;
	}
	inline void write(int x){
  		static int sta[35]; int top=0;
  		do{sta[++top]=x%10,x/=10;}while(x);
  		while(top) putchar(sta[top--]+48); puts("");
	}
}
using namespace IO;
namespace CL{
	#define fill(x,y) memset(x,y,sizeof(x))
	#define copy(x,y) memcpy(y,x,sizeof(x))
	
	const int maxn=2e3+5,maxm=1e5+5,mod=1e9+7;
	
	int n,m,cnt,minn=0x3f3f3f3f,ans;
	int f[maxn][maxn];
	char s[maxm];
	
	inline int main(){
		n=read(); m=read();
		scanf("%s",s+1);
		f[0][0]=1;
		for(int i=1;i<=2000;i++){//预处理
			f[i][0]=f[i-1][1];
			for(int j=1;j<=i;j++)
				f[i][j]=(f[i-1][j-1]+f[i-1][j+1])%mod;
		}
		for(int i=1;i<=m;i++){//clac delta num['(']-num[')'] of S
			if(s[i]=='(') cnt++;
			else cnt--;
			minn=min(minn,cnt);//max of delta num[')']-num['('] of S
		}
		for(int i=0;i<=n-m;i++)//for length of P
			for(int j=0;j<=i;j++)//for delta num['(']-num[')'] of P 
				if(j+minn>=0 && j+cnt<=n-m-i)//be sure that num['('] of P and num[')'] of Q are enough
					ans=(ans+1ll*f[i][j]*f[n-m-i][j+cnt]%mod)%mod;
		printf("%d\n",ans);
		return 0;
	}
}
signed main(){return CL::main();}
```