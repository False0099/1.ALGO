# 知识点
  ## [[可反悔的贪心]] [[贪心]]
# 题目
 # [POI 2012]HUR-Warehouse Store

## 题目描述

现在有 $n$ 天。第 $i$ 天上午会进货 $A_i$ 件商品，中午的时候会有顾客需要购买 $B_i$ 件商品，可以选择满足顾客的要求，或是无视掉他。

如果要满足顾客的需求，就必须要有足够的库存。问最多能够满足多少个顾客的需求。

## 输入格式

第一行包含一个整数 $n$，表示有 $n$ 天。

第二行有 $n$ 个整数 $a_i$，表示第 $i$ 天上午进货 $a$ 件商品。

第三行包含 $n$ 个整数 $b_i$，表示在第 $i$ 天中午有顾客来买 $b$ 件商品。

## 输出格式

第一行一个整数，表示最多能满足几天中顾客的需求。


第二行输出满足这么哪些天顾客的需求。

## 样例 #1

### 样例输入 #1

```
6
2 2 1 2 1 0
1 2 2 3 4 4
```

### 样例输出 #1

```
3
1 2 4
```

## 提示

对于 $100\%$ 的数据，$1\leqslant n\leqslant 2.5\times 10^5$，$0\leqslant a_i,b_i \leqslant 10^9$。

# 思路
我们本题为什么要采用我们的返回贪心，这是因为我们本题中每一个物品选择的代价都是相同的，在这一种非常特殊的情况下，我们的返回贪心对于我们的背包问题是一个可行的用于缩减我们时间复杂度的方法。

因此，我们就可以通过我们的交换法来进行我们的处理，我们用一个队列来存储我们已经选择的物品当中，我们的


·对于贪心反悔，我们经常会选择用一个个优先队列，一个队列存储我们已经选择了的物品当中的花费最高的。
·对于每一个新来的物品，如果他的价值是比我们的剩余容量要低的，我们直接贪心的选择它，然后把他放入到我们的已选择的队列当中。
·如果他的价值比我们的剩余容量还要高，我们就把他放到我们的待选择的队列当中，并且判断这个价值是不是比我们已经选择所有物品中价值最高的物品还要低，如果是的话，我们就更改我们的剩余价值为两者的差，并且把我们的新的价值 push 进去。
# AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=250005;

typedef pair<long long,int> pii;

long long a[maxn],b[maxn];
bool vis[maxn];//记录是否满足每一位顾客

priority_queue<pii,vector<pii>,less<pii> > que;

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",a+i);
	for(int i=1;i<=n;i++) scanf("%lld",b+i);
	long long tot=0,cnt=0;
	for(int i=1;i<=n;i++)
	{
		tot+=a[i];
		if(tot<b[i]&&!que.empty()&&que.top().first>b[i])
		{//若无法满足当前顾客并且堆顶更贵的情况
			vis[que.top().second]=false;
			tot+=que.top().first;//删除堆顶
			que.pop();
			cnt--;
		}
		if(tot>=b[i])
		{
			tot-=b[i];
			que.push((pii){b[i],i});
			vis[i]=true;//加入当前点
			cnt++;
		}
	}
	printf("%lld\n",cnt);
	for(int i=1;i<=n;i++)
		if(vis[i]) printf("%d ",i);
	puts("");
	return 0;
}
```
# 备注
