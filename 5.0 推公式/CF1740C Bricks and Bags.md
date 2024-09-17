# Bricks and Bags

## 题面翻译

hhoppitree 有 $n$ 根木棍，其中第 $i$ 根木棍的长度为 $a_i$，他想要将它们放置在三个背包中，使得**每个背包中至少有一根木棍**。

他的好朋友会从每个背包中选出一根木棍，假设从三个背包中取出的木棍的长度分别为 $x,y,z$，则他会送给 hhoppitree 一共 $|x-y|+|y-z|$ 瓶可乐，显然，**他的朋友会最小化这个数的值**。

Hhoppitree 想通过适当的分配，使得这个数的最小可能值最大，他想知道这个最大值是多少。

## 题目描述

There are $ n $ bricks numbered from $ 1 $ to $ n $ . Brick $ i $ has a weight of $ a_i $ .

Pak Chanek has $ 3 $ bags numbered from $ 1 $ to $ 3 $ that are initially empty. For each brick, Pak Chanek must put it into one of the bags. After this, each bag must contain at least one brick.

After Pak Chanek distributes the bricks, Bu Dengklek will take exactly one brick from each bag. Let $ w_j $ be the weight of the brick Bu Dengklek takes from bag $ j $ . The score is calculated as $ |w_1 - w_2| + |w_2 - w_3| $ , where $ |x| $ denotes the absolute value of $ x $ .

It is known that Bu Dengklek will take the bricks in such a way that minimises the score. What is the maximum possible final score if Pak Chanek distributes the bricks optimally?

## 输入格式

Each test contains multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 2 \cdot 10^4 $ ) — the number of test cases. The following lines contain the description of each test case.

The first line of each test case contains an integer $ n $ ( $ 3 \leq n \leq 2 \cdot 10^5 $ ) — the number of bricks.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — the weights of the bricks.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a line containing an integer representing the maximum possible final score if Pak Chanek distributes the bricks optimally.

## 样例 #1

### 样例输入 #1

```
3
5
3 1 5 2 3
4
17 8 19 45
8
265 265 265 265 265 265 265 265
```

### 样例输出 #1

```
6
63
0
```

## 提示

In the first test case, one way of achieving a final score of $ 6 $ is to do the following:

- Put bricks $ 1 $ , $ 4 $ , and $ 5 $ into bag $ 1 $ .
- Put brick $ 3 $ into bag $ 2 $ .
- Put brick $ 2 $ into bag $ 3 $ .

If Pak Chanek distributes the bricks that way, a way Bu Dengklek can take the bricks is:

- Take brick $ 5 $ from bag $ 1 $ .
- Take brick $ 3 $ from bag $ 2 $ .
- Take brick $ 2 $ from bag $ 3 $ .

The score is $ |a_5 - a_3| + |a_3 - a_2| = |3 - 5| + |5 - 1| = 6 $ . It can be shown that Bu Dengklek cannot get a smaller score from this distribution.

It can be shown that there is no other distribution that results in a final score bigger than $ 6 $ .

## 题解
我们这一题就是给定一个数列，要我们最大化 $|a-b|+|b-c|$ 的最小值，这里我们运用我们的数学推导，我们可以把原式子化简为 $x+z-2y(y\leq x\land y\leq z)$, $2*y-x-z(y\geq x\land y\geq z)$,现在，我们只需要将我们的原数列排序后，分别对于每一个 y，求出我们上面两个式子的最小值分别是多少，然后去一个 max 即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 114514
#define M 1919810
#define ll long long
#define INF 2147483647000000
ll t,n,a[M];
int main(){
	cin>>t; //注意t组数据 
	while(t--){
		cin>>n;
		ll ans=-INF,ans_=-INF;
		for(int i=1;i<=n;++i) cin>>a[i];
		sort(a+1,a+n+1);
		//因为取出时要最小化总值，所以直接取排序后的数组里的前或后一个值 
		for(int i=1;i<=n-2;++i) ans_=max(ans_,a[n]+a[i+1]-2*a[i]);  //第一种，若要最大化总值则肯定要取最大值 
		for(int i=3;i<=n;++i) ans=max(ans,2*a[i]-a[1]-a[i-1]);      //第二种，相反与第一种，取最小值 
		//注意枚举范围（第二种情况理论上应从3开始枚举，但亲测2也可以）
		cout<<max(ans,ans_)<<'\n';
	}
	return 0;
}
```

