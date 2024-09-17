# Selling a Menagerie

## 题面翻译

动物园里有 $n$ 个动物，第 $i$ 个动物害怕第 $a_i$ 个动物，第 $i$ 个动物价值 $c_i$ 元。现在我要将这些动物全部卖掉。显然，卖掉的动物编号可以构成一个排列 $p$。

考虑卖掉这些动物时：
1. 若 $a_i$ 在 $i$ 还没有卖掉之前就被卖掉了，现在卖掉 $i$，可以获得 $c_i$ 元；
2. 若 $a_i$ 在 $i$ 还没有卖掉之前没被卖掉，现在卖掉 $i$，可以获得 $2·c_i$ 元；

构造并输出赚钱最多的动物卖出顺序。

## 题目描述

You are the owner of a menagerie consisting of $ n $ animals numbered from $ 1 $ to $ n $ . However, maintaining the menagerie is quite expensive, so you have decided to sell it!

It is known that each animal is afraid of exactly one other animal. More precisely, animal $ i $ is afraid of animal $ a_i $ ( $ a_i \neq i $ ). Also, the cost of each animal is known, for animal $ i $ it is equal to $ c_i $ .

You will sell all your animals in some fixed order. Formally, you will need to choose some permutation $ ^\dagger $ $ p_1, p_2, \ldots, p_n $ , and sell animal $ p_1 $ first, then animal $ p_2 $ , and so on, selling animal $ p_n $ last.

When you sell animal $ i $ , there are two possible outcomes:

- If animal $ a_i $ was sold before animal $ i $ , you receive $ c_i $ money for selling animal $ i $ .
- If animal $ a_i $ was not sold before animal $ i $ , you receive $ 2 \cdot c_i $ money for selling animal $ i $ . (Surprisingly, animals that are currently afraid are more valuable).

Your task is to choose the order of selling the animals in order to maximize the total profit.

For example, if $ a = [3, 4, 4, 1, 3] $ , $ c = [3, 4, 5, 6, 7] $ , and the permutation you choose is $ [4, 2, 5, 1, 3] $ , then:

- The first animal to be sold is animal $ 4 $ . Animal $ a_4 = 1 $ was not sold before, so you receive $ 2 \cdot c_4 = 12 $ money for selling it.
- The second animal to be sold is animal $ 2 $ . Animal $ a_2 = 4 $ was sold before, so you receive $ c_2 = 4 $ money for selling it.
- The third animal to be sold is animal $ 5 $ . Animal $ a_5 = 3 $ was not sold before, so you receive $ 2 \cdot c_5 = 14 $ money for selling it.
- The fourth animal to be sold is animal $ 1 $ . Animal $ a_1 = 3 $ was not sold before, so you receive $ 2 \cdot c_1 = 6 $ money for selling it.
- The fifth animal to be sold is animal $ 3 $ . Animal $ a_3 = 4 $ was sold before, so you receive $ c_3 = 5 $ money for selling it.

Your total profit, with this choice of permutation, is $ 12 + 4 + 14 + 6 + 5 = 41 $ . Note that $ 41 $ is not the maximum possible profit in this example.

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ , but $ 4 $ is present in the array).

## 输入格式

The first line of the input contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Then follow the descriptions of the test cases.

The first line of each test case description contains an integer $ n $ ( $ 2 \le n \le 10^5 $ ) — the number of animals.

The second line of the test case description contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ , $ a_i \neq i $ ) — $ a_i $ means the index of the animal that animal $ i $ is afraid of.

The third line of the test case description contains $ n $ integers $ c_1, c_2, \dots, c_n $ ( $ 1 \le c_i \le 10^9 $ ) — the costs of the animals.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

Output $ t $ lines, each containing the answer to the corresponding test case. The answer should be $ n $ integers — the permutation $ p_1, p_2, \ldots, p_n $ , indicating in which order to sell the animals in order to maximize the profit. If there are multiple possible answers, you can output any of them.

## 样例 #1

### 样例输入 #1

```
8
3
2 3 2
6 6 1
8
2 1 4 3 6 5 8 7
1 2 1 2 2 1 2 1
5
2 1 1 1 1
9 8 1 1 1
2
2 1
1000000000 999999999
7
2 3 2 6 4 4 3
1 2 3 4 5 6 7
5
3 4 4 1 3
3 4 5 6 7
3
2 1 1
1 2 2
4
2 1 4 1
1 1 1 1
```

### 样例输出 #1

```
1 2 3
2 4 5 1 6 3 7 8
3 4 5 1 2
1 2
7 5 1 3 2 6 4
5 3 2 4 1
3 2 1
3 4 1 2
```

## 题解
首先，我们考虑如果我们是一个有向无环图，那么我们只需要按照我们的拓扑序去卖一定是最优的。如果是一个有环图的话，我们考虑把环上的那一个最小的元素给牺牲掉，也就是让他先卖了，然后剩下的我们在按照我们的正常顺序卖即可。

知道了我们的形态后，我们考虑怎么输出我们的答案，考虑我们的 tarjan 算法中，我们的 `scc` 标号，相当于我们的拓扑拟序，于是，我们就可以用一个数组存储每一个 `scc` 标号对应的点有哪些，然后先输出我们其他，最后再输出我们的最小点，即可得到我们的答案。
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a,v[100005],cdfn,dfn[100005],low[100005],z[100005],top,in_z[100005],minn,p;
int e[200005],ne[200005],h[200005],idx,ans[100005],ccnt;
int tem[200005],tcnt;
inline void add(int a,int b){e[idx]=b,ne[idx]=h[a],h[a]=idx++;}
void dfs(int u)
{
	dfn[u]=low[u]=++cdfn,z[++top]=u,in_z[u]=1;
	for(int i=h[u];i;i=ne[i])
		if(!dfn[e[i]]) dfs(e[i]),low[u]=min(low[u],low[e[i]]);
		else if(in_z[e[i]]) low[u]=min(low[u],dfn[e[i]]);
	if(dfn[u]==low[u])
	{
		tcnt=1,p=1,minn=v[z[top]],tem[1]=z[top],in_z[z[top--]]=0;
		while(z[top+1]!=u)//栈中顺序就是一种遍历顺序
		{
			tem[++tcnt]=z[top];
			if(minn==-1) minn=v[z[top]],p=tcnt;
			else if(minn>v[z[top]]) minn=v[z[top]],p=tcnt;//记录最小值的位置
			in_z[z[top--]]=0;
		}
		for(int i=p;i<=tcnt;++i) ans[++ccnt]=tem[i];
		for(int i=1;i<p;++i) ans[++ccnt]=tem[i];//记录答案
	}
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		ccnt=0,cdfn=0,memset(dfn,0,sizeof(dfn)),memset(low,0,sizeof(low)),memset(h,0,sizeof(h)),idx=1,memset(in_z,0,sizeof(in_z)),top=0;
		scanf("%d",&n);
		for(int i=1;i<=n;++i) scanf("%d",&a),add(i,a);//建边
        for(int i=1;i<=n;++i) scanf("%d",&v[i]);
		for(int i=1;i<=n;++i) if(!dfn[i]) dfs(i);//tarjan
		for(int i=ccnt;i>=1;--i) printf("%d ",ans[i]);puts("");//注意：答案是反着记录的。
	}
}
```