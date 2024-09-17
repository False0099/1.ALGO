## Description

马上假期就要结束了，zjm还有 n 个作业，完成某个作业需要一定的时间，而且每个作业有一个截止时间，若超过截止时间，一天就要扣一分。  
zjm想知道如何安排做作业，使得扣的分数最少。  
Tips: 如果开始做某个作业，就必须把这个作业做完了，才能做下一个作业。

## Input

有多组测试数据。第一行一个整数表示测试数据的组数  
第一行一个整数 n(1<=n<=15)  
接下来n行，每行一个字符串(长度不超过100) S 表示任务的名称和两个整数 D 和 C，分别表示任务的截止时间和完成任务需要的天数。  
这 n 个任务是按照字符串的字典序**从小到大**给出。

## Output

每组测试数据，输出最少扣的分数，并输出完成作业的方案，如果有多个方案，输出字典序最小的一个。

## Sample Input

2
3
Computer 3 3
English 20 1
Math 3 2
3
Computer 3 3
English 6 3
Math 6 3

## Sample Output

2
Computer
Math
English
3
Computer
English
Math
 

Hint

在第二个样例中，按照 Computer->English->Math 和 Computer->Math->English 的顺序完成作业，所扣的分数都是 3，由于 English 的字典序比 Math 小，故输出前一种方案。

## 题解
我们如果知道了现在的最小值，我们想要转移到后面的状态，我们需要知道：1. 现在我们现在是哪一个时间 2. 我们现在是做到了 ddl 里的哪一个任务。

上面的方法是不能够表示的，因为这只代表了我们按照从小到达顺序进行的方案，我们也存在一种不能被上面表示出来的顺序： 1-4-5-6-2-3。因此，我们就需要用我们的状压来表示我们的每一种状态。

而现在是哪一个时间这个需要我们用我们单独的一个状态来表示（类似于我们背包问题中的容量），而我们背包问题中的价值我们则同时与我们的价值和我们的当前状态等有关。而因为我们本题中我们的状态表示较为简单，所以我们就可以用我们的状压来表示：我们设 $dp[i]$ 为我们完成状态 $i$ 所有作业所扣的最少分数，那么我们的转移方程就是
$dp[S]=min(dp[S']+f(i^{1\ll(ir-1)}))$,

1. & : 按位逻辑 ^(交)
    
2. | : 按位逻辑 v(并)
    
3. ^ : 按位逻辑 异或

## 题解
```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cstdio>
using namespace std;
#define N 1<<16
int dp[N],T[N],cost[20],dead[20],ans[20];
int order[N]; //状态i下的最优写作业顺序下最后一本书的编号 
string subject[20];
void output(int state){
	if( state==0 )
		return;
	output( state^( 1<<(order[state]-1) ) );
	cout<<subject[order[state]]<<endl;
}
int main(){
	int i,j,n,t;
	cin>>t;
	while( t-- )
	{
		cin>>n;
		for( i=1;i<=n;i++ )
		{
			cin>>subject[i]>>dead[i]>>cost[i];
		}
		for( i=1;i<(1<<n);i++ )
		{
			dp[i]=1<<26;
			for( j=n;j>=1;j-- )
			{
				int tt=1<<(j-1);
				if( !(tt&i) )	continue;
				int pre=tt^i;  //状态i中除去第j本书
				int losescore=T[pre]+cost[j]-dead[j];
				losescore=(losescore<0)?0:losescore;
				if( dp[pre]+losescore<dp[i] )
				{
					dp[i]=dp[pre]+losescore;
					T[i]=T[pre]+cost[j];
					order[i]=j;
				}
			}
		}
		//cout<<1<<n-1<<endl;
		cout<<dp[(1<<n)-1]<<endl;
		output((1<<n)-1);
	}
	return 0;
}
```
