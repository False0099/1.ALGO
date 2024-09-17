# [CQOI 2016] 手机号码

## 题目描述

人们选择手机号码时都希望号码好记、吉利。比如号码中含有几位相邻的相同数字、不含谐音不吉利的数字等。手机运营商在发行新号码时也会考虑这些因素，从号段中选取含有某些特征的号码单独出售。为了便于前期规划，运营商希望开发一个工具来自动统计号段中满足特征的号码数量。

工具需要检测的号码特征有两个：号码中要出现至少 $3$ 个相邻的相同数字；号码中不能同时出现 $8$ 和 $4$。号码必须同时包含两个特征才满足条件。满足条件的号码例如：13000988721、23333333333、14444101000。而不满足条件的号码例如：1015400080、10010012022。

手机号码一定是 $11$ 位数，前不含前导的 $0$。工具接收两个数 $L$ 和 $R$，自动统计出 $[L,R]$ 区间内所有满足条件的号码数量。$L$ 和 $R$ 也是 $11$ 位的手机号码。

## 输入格式

输入文件内容只有一行，为空格分隔的 $2$ 个正整数 $L,R$。

## 输出格式

输出文件内容只有一行，为 $1$ 个整数，表示满足条件的手机号数量。

## 样例 #1

### 样例输入 #1

```
12121284000 12121285550
```

### 样例输出 #1

```
5
```

## 提示

样例解释：满足条件的号码： 12121285000、 12121285111、 12121285222、 12121285333、 12121285550。

数据范围：$10^{10}\leq L\leq R<10^{11}$。

## 题解
我们本题中，我们要使用我们的数位 dp，然后用我们的减法减去我们的 L, R 即可计算出我们的答案。然后我们考虑我们计算式需要哪些？
1. 我们需要知道相邻相同数字有多少个了？
2. 我们需要知道有没有同时出现 8 和 4？
于是我们的 dfs 就可以写成如下形式

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long lint;
lint l,r,dp[15][11][11][2][2][2];
//dp[pos][a][b][state][eight][four]
// pos	当前位置
// a	上一位数字
// b	再上一位数字
// state 是否出现3个连续相同数字
// eight 是否出现8
// four  是否出现4
int st[15];
lint dfs(int pos,int a,int b,bool state,bool eight,bool four,bool limit)
{
	// limit 当前位置上数字是否达到上限
	if(eight&&four) return 0;
    //见题面，8和4不能同时出现
	if(!pos) return state;
	if(!limit&&dp[pos][a][b][state][eight][four]!=-1) return dp[pos][a][b][state][eight][four];
    //记忆化
	lint res=0;
	int maxn=limit?st[pos]:9; 
	for(int i=0;i<=maxn;i++)
	{
		res+=dfs(pos-1,i,a,state||(i==a&&i==b),eight||(i==8),four||(i==4),limit&&(i==maxn));
        //用下一位状态更新该位
	}
	if(!limit) dp[pos][a][b][state][eight][four]=res;
	return res;
}
lint find(lint x)
{
	int len=0;
	while(x)
	{
		st[++len]=x%10;
		x/=10;
	}
	if(len!=11) return 0;//注意这里！！！手机号码一定为11位，不特判这里只有70分
	memset(&dp,-1,sizeof(dp));
	lint ans=0;
    //问:如何避开第一位上的前导0？
    //答:枚举1到第一位上的数字，从下一位开始搜索
	for(int i=1;i<=st[len];i++)
	{
		ans+=(long long)dfs(len-1,i,0,0,i==8,i==4,i==st[len]);
	}
	return ans;
}
int main()
{
	scanf("%lld%lld",&l,&r);
	printf("%lld\n",find(r)-find(l-1));
}
/*
input:
10000000000 53628881996
output:
2186241614
*/
```