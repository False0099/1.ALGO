# Omsk Metro (simple version)

## 题面翻译

有一棵节点带权的树，权重只可能为 $1$ 或者 $-1$ ，初始时树中只有一个权重为 $1$ 的根节点 $1$ ，然后进行 $n$ 次操作，操作 `+` 表示添加一个权重为 $x_i$ 的新节点和 $v_i$ 相连，新节点的编号按添加顺序分配；操作 `?` 表示查询 $v_i$ 到 $u_i$ 的路径上，是否存在一个可以为空的子路径的权重和为 $k_i$ 。

其中 $F_{1}$ 保证 $u_i = 1$ 。

## 题目描述

This is the simple version of the problem. The only difference between the simple and hard versions is that in this version $ u = 1 $ .

As is known, Omsk is the capital of Berland. Like any capital, Omsk has a well-developed metro system. The Omsk metro consists of a certain number of stations connected by tunnels, and between any two stations there is exactly one path that passes through each of the tunnels no more than once. In other words, the metro is a tree.

To develop the metro and attract residents, the following system is used in Omsk. Each station has its own weight $ x \in \{-1, 1\} $ . If the station has a weight of $ -1 $ , then when the station is visited by an Omsk resident, a fee of $ 1 $ burle is charged. If the weight of the station is $ 1 $ , then the Omsk resident is rewarded with $ 1 $ burle.

Omsk Metro currently has only one station with number $ 1 $ and weight $ x = 1 $ . Every day, one of the following events occurs:

- A new station with weight $ x $ is added to the station with number $ v_i $ , and it is assigned a number that is one greater than the number of existing stations.
- Alex, who lives in Omsk, wonders: is there a subsegment $ \dagger $ (possibly empty) of the path between vertices $ u $ and $ v $ such that, by traveling along it, exactly $ k $ burles can be earned (if $ k < 0 $ , this means that $ k $ burles will have to be spent on travel). In other words, Alex is interested in whether there is such a subsegment of the path that the sum of the weights of the vertices in it is equal to $ k $ . Note that the subsegment can be empty, and then the sum is equal to $ 0 $ .

You are a friend of Alex, so your task is to answer Alex's questions.

 $ \dagger $ Subsegment — continuous sequence of elements.

## 输入格式

The first line contains a single number $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains the number $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the number of events.

Then there are $ n $ lines describing the events. In the $ i $ -th line, one of the following options is possible:

- First comes the symbol "+" (without quotes), then two numbers $ v_i $ and $ x_i $ ( $ x_i \in \{-1, 1\} $ , it is also guaranteed that the vertex with number $ v_i $ exists). In this case, a new station with weight $ x_i $ is added to the station with number $ v_i $ .
- First comes the symbol "?" (without quotes), and then three numbers $ u_i $ , $ v_i $ , and $ k_i $ ( $ -n \le k_i \le n $ ). It is guaranteed that the vertices with numbers $ u_i $ and $ v_i $ exist. In this case, it is necessary to determine whether there is a subsegment (possibly empty) of the path between stations $ u_i $ and $ v_i $ with a sum of weights exactly equal to $ k_i $ . In this version of the task, it is guaranteed that $ u_i = 1 $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each of Alex's questions, output "Yes" (without quotes) if the subsegment described in the condition exists, otherwise output "No" (without quotes).

You can output the answer in any case (for example, the strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive answer).

## 样例 #1

### 样例输入 #1

```
1
8
+ 1 -1
? 1 1 2
? 1 2 1
+ 1 1
? 1 3 -1
? 1 1 1
? 1 3 2
? 1 1 0
```

### 样例输出 #1

```
NO
YES
NO
YES
YES
YES
```

## 样例 #2

### 样例输入 #2

```
1
10
+ 1 -1
+ 1 -1
+ 3 1
+ 3 -1
+ 3 1
? 1 6 -1
? 1 6 2
? 1 2 0
? 1 5 -2
? 1 4 3
```

### 样例输出 #2

```
YES
NO
YES
YES
NO
```

## 提示

Explanation of the first sample.

The answer to the second question is "Yes", because there is a path $ 1 $ .

In the fourth question, we can choose the $ 1 $ path again.

In the fifth query, the answer is "Yes", since there is a path $ 1-3 $ .

In the sixth query, we can choose an empty path because the sum of the weights on it is $ 0 $ .

It is not difficult to show that there are no paths satisfying the first and third queries.

## 题解
我们这一题可以用我们的树上 dp 来解决，我们求出从某一个点到终点的最小权值和最大权值和，然后看我们的 $k$ 是否在这个范围内。在的话，我们就直接输出 YE s，否则我们就输出 No。

```cpp
```cpp
#include<bits/stdc++.h>
using namespace std;
int tot,first[200010],nnext[400010],to[400010],w[200010],q[200010],r[200010],maxx[200010],minn[200010];
void add(int x,int y){
	nnext[++tot]=first[x];
	first[x]=tot;
	to[tot]=y;
}
void fun(int u,int fa){
	if(u==1){
		maxx[u]=1;
	}
	else{
		maxx[u]=max(w[u],maxx[fa]+w[u]);  //dp核心
		minn[u]=min(w[u],minn[fa]+w[u]);
	}
	for(int e=first[u];e;e=nnext[e]){
		if(to[e]!=fa){
			fun(to[e],u);
		}
	}
}
void fun1(int u,int fa){
	maxx[u]=max(maxx[fa],maxx[u]);
	minn[u]=min(minn[fa],minn[u]);
	for(int e=first[u];e;e=nnext[e]){
		if(to[e]!=fa){
			fun1(to[e],u);
		}
	}
}
int main(){
	int t,sum,sum1,n,a,p;
	char s;
	scanf("%d",&t);
	while(t--){
		memset(first,0,sizeof(first));
		memset(maxx,0,sizeof(maxx));
		memset(minn,0,sizeof(minn));
		sum=1;
		w[1]=1;
		sum1=0;
		scanf("%d",&n);
		while(n--){
			cin>>s;
			if(s=='+'){
				scanf("%d%d",&a,&p);
				add(a,++sum);  //建树
				add(sum,a);
				w[sum]=p;
			}
			else{
				sum1++;
				scanf("%d%d%d",&q[sum1],&q[sum1],&r[sum1]);  //离线
			}
		}
		fun(1,0);  //dp
		fun1(1,0);  //推下来
		for(int i=1;i<=sum1;i++){
			if(r[i]>=minn[q[i]]&&r[i]<=maxx[q[i]]){  //处理询问
				printf("YES\n");
			}
			else{
				printf("NO\n");
			}
		}
	}
}
```
```