# Chain Reaction

## 题面翻译

有 $n$ 个激光塔排成一行，第 $i$ 个激光塔的位置为 $a_i$ ，威力是 $b_i$ 

当第 $i$ 个激光塔被激活后，对于任意其他激光塔 $j$ ，如果 $0 < a_i-a_j \le b_i$ ，则激光塔 $j$ 被摧毁。

添加一个新激光塔 $k$ ，使 $a_k > \text{max}\{a_1,a_2, ... ,a_n\}$ 

管理员现在开始开始从右到左依次激活每个激光塔，如果一个激光塔被摧毁了，那就不激活。

请调整 $a_k$ 和 $b_k$ ，使被摧毁的激光塔总数最少。

## 题目描述

There are $ n $ beacons located at distinct positions on a number line. The $ i $ -th beacon has position $ a_{i} $ and power level $ b_{i} $ . When the $ i $ -th beacon is activated, it destroys all beacons to its left (direction of decreasing coordinates) within distance $ b_{i} $ inclusive. The beacon itself is not destroyed however. Saitama will activate the beacons one at a time from right to left. If a beacon is destroyed, it cannot be activated.

Saitama wants Genos to add a beacon strictly to the right of all the existing beacons, with any position and any power level, such that the least possible number of beacons are destroyed. Note that Genos's placement of the beacon means it will be the first beacon activated. Help Genos by finding the minimum number of beacons that could be destroyed.

## 输入格式

The first line of input contains a single integer $ n $ ( $ 1<=n<=100000 $ ) — the initial number of beacons.

The $ i $ -th of next $ n $ lines contains two integers $ a_{i} $ and $ b_{i} $ ( $ 0<=a_{i}<=1000000 $ , $ 1<=b_{i}<=1000000 $ ) — the position and power level of the $ i $ -th beacon respectively. No two beacons will have the same position, so $ a_{i}≠a_{j} $ if $ i≠j $ .

## 输出格式

Print a single integer — the minimum number of beacons that could be destroyed if exactly one beacon is added.

## 样例 #1

### 样例输入 #1

```
4
1 9
3 1
6 1
7 4
```

### 样例输出 #1

```
1
```

## 样例 #2

### 样例输入 #2

```
7
1 1
2 1
3 1
4 1
5 1
6 1
7 1
```

### 样例输出 #2

```
3
```

## 提示

For the first sample case, the minimum number of beacons destroyed is $ 1 $ . One way to achieve this is to place a beacon at position $ 9 $ with power level $ 2 $ .

For the second sample case, the minimum number of beacons destroyed is $ 3 $ . One way to achieve this is to place a beacon at position $ 1337 $ with power level $ 42 $ .
## 题解
我们这一题的思路在于我们能够发现下面的一个性质：我们的每一个最终的答案都一定是我们的某一个前缀，那么我们就可以通过计算我们每一个前缀的最大长度，然后我们再去去一个 max，就能得到我们的答案。
```cpp
#include <iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e5+100;
const int INF=1e7+100;
struct Node{
	int a,b;
	Node(){}
	Node(int a,int b):a(a),b(b){}
	bool operator<(const Node &x)const{
		return a<x.a;
	}
}node[maxn];
int f[maxn];
int n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&node[i].a,&node[i].b);
	sort(node+1,node+1+n);
	f[1]=f[0]=0;
	for(int i=2;i<=n;i++){
		int d=node[i].a-node[i].b;//摧毁起点位置
		int x=lower_bound(node+1,node+1+n,Node(d,0))-node;//二分查找摧毁位置
		f[i]=f[x-1]+i-x;//更新摧毁数量
	}
	int ans=INF;
	for(int i=n;i;i--)
		ans=min(ans,f[i]+n-i);//计算最小摧毁数
	printf("%d",ans);
    return 0;
}
```
