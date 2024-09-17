# [USACO 18 JAN] MooTube G

## 题目背景

*本题与 [银组同名题目](/problem/P6111) 在题意上一致，唯一的差别是数据范围。*

## 题目描述

在业余时间，Farmer John 创建了一个新的视频共享服务，他将其命名为 MooTube。在 MooTube 上，Farmer John 的奶牛可以录制，分享和发现许多有趣的视频。他的奶牛已经发布了 $N$ 个视频（$1 \leq N \leq 10^5$），为了方便将其编号为  $1 \ldots N$ 。然而，FJ 无法弄清楚如何帮助他的奶牛找到他们可能喜欢的新视频。

FJ 希望为每个 MooTube 视频创建一个“推荐视频”列表。这样，奶牛将被推荐与他们已经观看过的视频最相关的视频。

FJ 设计了一个“相关性”度量标准，顾名思义，它确定了两个视频相互之间的相关性。他选择 $N-1$ 对视频并手动计算其之间的相关性。然后，FJ 将他的视频建成一棵树，其中每个视频是节点，并且他手动将 $N-1$ 对视频连接。为了方便，FJ 选择了 $N-1$ 对，这样任意视频都可以通过一条连通路径到达任意其他视频。 FJ 决定将任意一对视频的相关性定义为沿此路径的任何连接的最小相关性。

Farmer John 想要选择一个 $K$ 值，以便在任何给定的 MooTube 视频旁边，推荐所有其他与该视频至少有 $K$ 相关的视频。然而，FJ 担心会向他的奶牛推荐太多的视频，这可能会分散他们对产奶的注意力！因此，他想设定适当的 $K$ 值。 Farmer John 希望得到您的帮助，回答有关 $K$ 值的推荐视频的一些问题。

## 输入格式

第一行输入包含 $N$ 和 $Q$（$1 \leq Q \leq 10^5$）。

接下来的 $N-1$ 行描述了 FJ 手动比较的一对视频。每行包括三个整数  $p_i$，$q_i$ 和 $r_i$（$1 \leq p_i, q_i \leq N$，$1 \leq r_i \leq 10^9$），表示视频 $p_i$ 和 $q_i$ 已连接并且相关性为 $r_i$。

接下来的 $Q$ 行描述了 Farmer John 的 $Q$ 个问题。每行包含两个整数，$k_i$ 和 $v_i$（$1 \leq k_i \leq 10^9$，$1 \leq v_i \leq N$），表示 FJ 的第 $i$ 个问题询问中当 $K = k_i$ 时，第 $v_i$ 个视频推荐列表中将推荐的视频数。

## 输出格式

输出 $Q$ 行。在第 $i$ 行，输出 FJ 的第 $i$ 个问题的答案。

## 样例 #1

### 样例输入 #1

```
4 3
1 2 3
2 3 2
2 4 4
1 2
4 1
3 1
```

### 样例输出 #1

```
3
0
2
```


## 思路
既然是离线，我们就要发挥离线的优势，我们先按照 K 从大到小将我们输入的边和我们输入的查询进行排序，先将满足查询条件的边加上去，然后再去通过目前的并查集得到结果，依次类推，直到所有查询都结束。

```cpp
#include <bits/stdc++.h>
using namespace std;
int j=1,n,q,number[110000],father[110000],ans[110000];
struct kind{
	int start;
	int end;
	int w;
}bian[110000];
struct kind2{
	int k;
	int v;
	int id;
}ask[110000];
int cmp(kind x,kind y) {
	return x.w>y.w;
}
int cmp2(kind2 x,kind2 y){
	return x.k>y.k;
}
int getfather(int x){
	if(father[x]!=x){
		father[x]=getfather(father[x]);
	}
	return father[x];
}
void merge(int x,int y){
	int rootx=getfather(x);
	int rooty=getfather(y);
	if(rootx!=rooty){
		father[rootx]=rooty;
		number[rooty]+=number[rootx];
	}
	return;
}
int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		father[i]=i;
		number[i]=1;
	}	
	for(int i=1;i<n;i++){
		cin>>bian[i].start>>bian[i].end>>bian[i].w; 
	}
	sort(bian+1,bian+n+1,cmp);
	for(int i=1;i<=q;i++){
		cin>>ask[i].k>>ask[i].v;
		ask[i].id=i;
	}
	sort(ask+1,ask+1+q,cmp2);
	for(int i=1;i<=q;i++){
		while(j<n&&bian[j].w>=ask[i].k){
			merge(bian[j].start,bian[j].end);
			j++;
		}
		ans[ask[i].id]=number[getfather(ask[i].v)];
	}
	for(int i=1;i<=q;i++){
		cout<<ans[i]-1<<endl;
	}
	return 0;
}
```