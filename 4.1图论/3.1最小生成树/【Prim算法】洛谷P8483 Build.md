# 「HGOI-1」Build

## 题目背景

一次旅行，$\text{uuku}$ 到了一个奇怪的小镇。

## 题目描述

这个小镇将要和周围的其他小镇一共 $n$ 个小镇，一起修建一个能**连通**这 $n$ 个小镇，有 $m$ 条高速公路的交通网。其中每条高速公路都将会连接**不同的两个小镇**，即不存在一条高速公路的起点和终点相同。

但高速公路的修建费用是很高的，所以镇长们一致决定将共同承担高速公路的费用，所以他们希望修建的**总费用最小**。

而且由于不同小镇的基础设施建设情况不同，所以每个小镇在修建的费用也不同。经过协商，每条高速公路将由其所连接的两个小镇共同施工。每个小镇负责一半路程。为了同时结束整个施工过程，显然将会有小镇同时进行多条道路的施工，而施工的道路数量越多，所需要花费的价钱就越多。

经过计算，每个小镇施工的花费可以用函数表示，及对于小镇 $i$，有三个参数 $a_i$，$b_i$，$c_i$。对于 $i$ 小镇来说在修建其第 $j$ 条高速时，**这条**高速所需要的花费为 $a_ij^2+b_ij+c_i$。

现在，这些镇长想要 $\text{uuku}$ 给他们提供一个满足要求的**建造方案**，使**总价格最小**。

当然，$\text{uuku}$ 将这个问题交给了你。

## 输入格式

第一行两个整数 $n$，$m$。

接下来 $n$ 行，每行三个整数 $a_i$，$b_i$，$c_i$。

## 输出格式

共 $m+1$ 行

第一行一个整数表示最小价格。

接下来 $m$ 行，每行两个整数 $u$，$v$，表示你提供的方案中的一条边。

## 样例 #1

### 样例输入 #1

```
4 4
1 2 3
2 3 4
3 4 5
4 5 6
```

### 样例输出 #1

```
114
1 2
1 2
1 3
3 4
```

## 提示

#### 数据范围
本题采用**捆绑测试**，共有 $6$ 个 $\text{subtask}$，最终分数为所有 $\text{subtask}$ 分数之和。
$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|}\hline
\textbf{Task} & \textbf{Score} & \textbf{特殊限制} \cr\hline
1 & 10 & n,m\le 500  \cr\hline
2 & 20 &  n,m\le 5\times 10^3 \cr\hline
3 & 10 & \text{每个小镇的函数相同}\cr\hline
4 & 20 & a_i=0 \cr\hline
5 & 20 & m=n-1 \cr\hline
6 & 20 & \cr\hline
\end{array}
$$

对于 $100\%$ 的数据，$2\le n \le 2 \times 10^5$， $n-1 \le m \le 10^6$，$0 \le a_i$，$b_i$，$c_i \le 10^6$。

数据保证最小价格在 $\tt{long \ long}$ 范围内。

#### 说明

本题有 $\text{spj}$，价格正确可以获得 $30\%$ 的分数。每个 $\text{subtask}$ 取其中所有数据点得分的最小值。

如果你不会构造方案，也请你再输出最小价格后输出 $m$ 行，每行两个 $[1,n]$ 范围内的整数，防止 $\text{spj}$ 出现错误。

## 题解
我们本题的思路是：因为我们首先要本题联通，所以我们的最优方法一定是先去构造我们的最小生成树，然后再去看我们还需要多少条边，然后我们再去把我们的剩余边按照最小值排序，进行一个多路归并后就能得到我们的答案。

但是，我们本题需要注意的一点是，因为我们本题中的权值是动态更新的，所以我们不能够用我们的 Kruskal 算法，我们应该采用我们的 Prim 算法，这一点对于我们边权动态更新的最小生成树来说是非常好用的。

```
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
#define int long long
struct func{
	int a,b,c;
	int x;
}func[N];
typedef pair<int,int> PII;
int calc(int i){
	return func[i].a*func[i].x*func[i].x+func[i].b*func[i].x+func[i].c;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n,m;
	cin>>n>>m;
	priority_queue<PII,vector<PII>,greater<PII>> heap;
	for(int i=0;i<n;i++){
		cin>>func[i].a>>func[i].b>>func[i].c;
		func[i].x=1;
		heap.push({calc(i),i});//表示我们所有未选点的集合 
	}
	priority_queue<PII,vector<PII>,greater<PII>> q;//表示我们的已选点的集合 
	q.push(heap.top());
	heap.pop(); 
	vector<PII> ans_edge;
	int val=0;
	for(int i=1;i<n;i++){
		auto u1=heap.top();heap.pop();
		auto u2=q.top();q.pop();
		val+=u1.first+u2.first;
		int id1=u1.second;
		int id2=u2.second;
		ans_edge.push_back({id1,id2});
		func[id1].x++;
		func[id2].x++;
		q.push({calc(id1),id1});
		q.push({calc(id2),id2});
	}
	for(int i=n;i<=m;i++){
		auto u1=q.top();q.pop();
		auto u2=q.top();q.pop();
		val+=u1.first+u2.first;
		int id1=u1.second;
		int id2=u2.second;
		ans_edge.push_back({u1.second,u2.second});
		func[id1].x++;
		func[id2].x++;
		q.push({calc(id1),id1});
		q.push({calc(id2),id2});
	}
	cout<<val<<endl;
	for(auto u:ans_edge){
		cout<<u.first+1<<" "<<u.second+1<<endl;
	}
}
```