# Fighting Tournament

## 题面翻译

## 题意 

Burenka 正准备去观看一年中最有趣的体育活动 —— 她朋友 Tonya 组织的格斗锦标赛。

有 **n** 名运动员参加了大赛，标号分别为为 1，2，... ，n 。第 **i** 名运动员的实力是 **$a_i（1 \le a_i \le n）$** 。**每个运动员的实力是不同的，也就是说，数组 a 是 n 的一种全排列** 。

大赛的流程是这样的：

一开始，运动员们**按标号从小到大**排成一列，队头为 **1** 号运动员，队尾为 **n** 号运动员。

每轮一次比赛，**队头**的两个人进行格斗，**赢的人（实力较强的人）变成队头，输的人变成队尾** 。

Burenka 问了 Tonya **q** 个问题，每个问题包含两个整数 **i** 和 **k** ，表示 **i 号运动员在前 k 轮中会胜多少场**。

### 输入格式 

第一行一个整数 **t** $(1\le t\le 10^4)$，表示数据组数。

对于每组数据：

第一行两个整数 **n** 和 **q** $(2\le n \le 10^5,1\le q\le 10^5)$，表示参加大赛的运动员数量和问题数量。

第二行 **n** 个整数 **$a_1,a_2,...,a_n(1\le a_i\le n)$**，表示数组 **a**，而且是个 **全排列**。

接下来的 **q** 行表示每个问题，每行两个整数 **i** 和 **k** $(1\le i\le n,1\le k\le 10^9)$，表示**运动员的标号** 和 **轮数**。


### 输出格式 

对于每个问题，一行一个整数表示 **问题的答案**。

## 题目描述

Burenka is about to watch the most interesting sporting event of the year — a fighting tournament organized by her friend Tonya.

 $ n $ athletes participate in the tournament, numbered from $ 1 $ to $ n $ . Burenka determined the strength of the $ i $ -th athlete as an integer $ a_i $ , where $ 1 \leq a_i \leq n $ . All the strength values are different, that is, the array $ a $ is a permutation of length $ n $ . We know that in a fight, if $ a_i > a_j $ , then the $ i $ -th participant always wins the $ j $ -th.

The tournament goes like this: initially, all $ n $ athletes line up in ascending order of their ids, and then there are infinitely many fighting rounds. In each round there is exactly one fight: the first two people in line come out and fight. The winner goes back to the front of the line, and the loser goes to the back.

Burenka decided to ask Tonya $ q $ questions. In each question, Burenka asks how many victories the $ i $ -th participant gets in the first $ k $ rounds of the competition for some given numbers $ i $ and $ k $ . Tonya is not very good at analytics, so he asks you to help him answer all the questions.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. Description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 2 \leq n \leq 10^5 $ , $ 1 \leq q \leq 10^5 $ ) — the number of tournament participants and the number of questions.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq n $ ) — the array $ a $ , which is a permutation.

The next $ q $ lines of a test case contain questions. Each line contains two integers $ i $ and $ k $ ( $ 1 \leq i \leq n $ , $ 1 \leq k \leq 10^9 $ ) — the number of the participant and the number of rounds.

It is guaranteed that the sum of $ n $ and the sum of $ q $ over all test cases do not exceed $ 10^5 $ .

## 输出格式

For each Burenka's question, print a single line containing one integer — the answer to the question.

## 样例 #1

### 样例输入 #1

```
3
3 1
3 1 2
1 2
4 2
1 3 4 2
4 5
3 2
5 2
1 2 3 5 4
5 1000000000
4 6
```

### 样例输出 #1

```
2
0
1
0
4
```

## 提示

In the first test case, the first numbered athlete has the strength of $ 3 $ , in the first round he will defeat the athlete with the number $ 2 $ and the strength of $ 1 $ , and in the second round, the athlete with the number $ 3 $ and the strength of $ 2 $ .

In the second test case, we list the strengths of the athletes fighting in the first $ 5 $ fights: $ 1 $ and $ 3 $ , $ 3 $ and $ 4 $ , $ 4 $ and $ 2 $ , $ 4 $ and $ 1 $ , $ 4 $ and $ 3 $ . The participant with the number $ 4 $ in the first $ 5 $ rounds won $ 0 $ times (his strength is $ 2 $ ). The participant with the number $ 3 $ has a strength of $ 4 $ and won $ 1 $ time in the first two fights by fighting $ 1 $ time.

## 题解
我们发现，我们的最大值到达我们的队头之后，然后我们的一个队列就具有一个周期性了，我们就再也不会变化，于是我们就可以采用我们的模拟法，我们先用我们的一个双端队列来进行一个模拟法。模拟我们的前 n 次，后面的次数我们就可以直接可以来 $o (1)$ 的解决。
现在，我们的问题就在于我们怎么处理出我们最大值前面那些数会赢多少次，可以发现，我们直接存储当前的队头，一开始为 1，随着 i 每次向后枚举，我们判断一下 i 和队头的关系。如果 i 更大，那么 i 赢得次数+1，同时队头变成 i，否则原来的队头赢得次数++。
接下来，我们考虑预处理查询。我们分成两大类：
1. 查询的次数 k 大于最大值的位置p
	 - 查询的是最大值：将 k 减去 p，这样队头就是最大值了。那么他是队头的时候，会赢多少次呢？显然是 k−p+1。但是它不是队头的时候，和队头的数比较也会赢一次，所以要加一。但注意如果他是第一个数，他不会多赢这一次，因此特判一下即可。
	 - 查询的不是最大值：我们只需要按照我们预处理的次数来即可，因为在最大值成为队头后，他永远不可能再赢了
1. **查询的次数 k 小于最大值的位置p**
	如果 k =p-1, 那么我们其实处理方法和上面一样
	如果 k 比 p-1 还小，那么我们可以把所有询问离线下来，按照询问的次数 k 排序，然后重新按照预处理的方法从 1-n 扫一遍。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=100005;
int a[MAXN],times[MAXN]; // times[i] 表示 i 赢得次数 
int ans[MAXN];
struct Node{int x,y,id;}ask[MAXN]; // 存储询问 
bool cmp1(Node xx,Node yy){ // 按照询问的打架的次数排序 
	return xx.y<yy.y;
}
int main(){
	int T; cin>>T;
	while(T--){
		int n,q; cin>>n>>q;
		int flag=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			times[i]=0; // 清空次数不要用 memset。 
			if(a[i]==n) flag=i; // 找到最大值的位置 
		}
		int lst=1; // 队头一开始是 1 
		for(int i=2;i<flag;i++){ // 只需要预处理最大值之前的就够了 
			if(a[i]<a[lst]) times[lst]++; // 如果队头更大，那么队头++ 
			else times[i]++,lst=i; // 否则 i 次数++，同时更新队头 
		}
		int tot=0;
		for(int i=1;i<=q;i++){
			int x,k; cin>>x>>k;
			if(k<flag-1) ask[++tot]=(Node){x,k,i}; // 如果小于最大值所在的位置就离线下来 
			else{ // 否则直接计算答案 
				if(x!=flag) ans[i]=times[x]; // 如果不是最大值，那么答案就是 times[x] 
				else ans[i]=k-flag+1+(flag!=1); // 否则就用 k-p+1+(p!=1) 计算一下答案 
			}
		}
		sort(ask+1,ask+1+tot,cmp1); // 排序 
		for(int i=1;i<=n;i++) times[i]=0; // 重新清零 
		int j=1; lst=1;
		for(int i=2;i<flag;i++){
			if(a[i]<a[lst]) times[lst]++;
			else times[i]++,lst=i;
			while(j<=tot && ask[j].y==i-1){ // 处理当前打架次数为 i-1 的询问 
				ans[ask[j].id]=times[ask[j].x];
				j++;
			}
		}
		for(int i=1;i<=q;i++) cout<<ans[i]<<endl; // 输出答案 
	}
	return 0;
}
```