# Zookeeper and The Infinite Zoo

## 题面翻译

## 题目描述

有一个无限图，其中有无数个节点，从 $1$ 开始标号。有一条从 $u$ 到 $u+v$ 的单向边，当且仅当 $u \&  v = v$ (这里的 $\&$ 指 [按位与](https://zh.wikipedia.org/wiki/位操作#按位与（AND）) 。除此以外没有其它边。

有 $q$ 个询问，询问是否存在一条从 $u$ 到 $v$ 的路径。

## 输入格式

第一行一个整数 $q$ （$1\le q\le 10^5 $） —— 询问的个数

接下来 $q$ 行中，每行有两个整数 $u,v$ ($1 \leq u,v < 2^{30}$)，意义如上

## 输出格式

对于每个询问，输出一行 `YES` 来表示存在从 $u$ 到 $v$ 的一条路径，或输出一行 `NO` 表示不存在这样一条路径。(你可以以任意大小写形式来输出 `YES` 或 `NO`)

## 题目描述

There is a new attraction in Singapore Zoo: The Infinite Zoo.

The Infinite Zoo can be represented by a graph with an infinite number of vertices labeled $ 1,2,3,\ldots $ . There is a directed edge from vertex $ u $ to vertex $ u+v $ if and only if $ u\&v=v $ , where $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND). There are no other edges in the graph.

Zookeeper has $ q $ queries. In the $ i $ -th query she will ask you if she can travel from vertex $ u_i $ to vertex $ v_i $ by going through directed edges.

## 输入格式

The first line contains an integer $ q $ ( $ 1 \leq q \leq 10^5 $ ) — the number of queries.

The $ i $ -th of the next $ q $ lines will contain two integers $ u_i $ , $ v_i $ ( $ 1 \leq u_i, v_i < 2^{30} $ ) — a query made by Zookeeper.

## 输出格式

For the $ i $ -th of the $ q $ queries, output "YES" in a single line if Zookeeper can travel from vertex $ u_i $ to vertex $ v_i $ . Otherwise, output "NO".

You can print your answer in any case. For example, if the answer is "YES", then the output "Yes" or "yeS" will also be considered as correct answer.

## 样例 #1

### 样例输入 #1

```
5
1 4
3 6
1 6
6 2
5 5
```

### 样例输出 #1

```
YES
YES
NO
NO
YES
```

## 提示

The subgraph on vertices $ 1,2,3,4,5,6 $ is shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1491D/3e9f4f0ae45942255adad5106d073ee5450fdd69.png)

## 题解
我们本题不妨先手动连接几条边观察。通过观察我们不难发现，我们 $a$ 和  $b$ 之间如果存在连边，一定要满足：b 是由我们的 a 构成的集合中的某些元素组合后与 a 相加。

但是上面所说的只是连接相邻的边，如果要扩展到一整个图上，我们就需要下面的结论：如果我们的 a 和 b 之间想要存在路径可以到达，那么有下面的要求：
1. 如果 a 的二进制位数比 b 多，那么我们一定可以到达。
2. 如果我们 a 的二进制位数与 b 的二进制位数相同，那么我们一定要求我们 a 在每一个前缀都比我们的 b 要小。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int q;
	cin>>q;
	while(q--){
		int a,b;
		cin>>a>>b;
		if(b<a){
			cout<<"NO"<<endl;
			continue;
		}
		int cnta=0,cntb=0;
		bool flag=true;
		for(int i=0;i<=30;i++){
			int u=((a>>i)&1);
			int v=((b>>i)&1);
			cnta+=u;
			cntb+=v;
			if(cnta<cntb){
				flag=false;
				break;
			}
		}
		if(flag){
			cout<<"YES"<<endl;
		}else{
			cout<<"NO"<<endl;
		}
	}
}
```