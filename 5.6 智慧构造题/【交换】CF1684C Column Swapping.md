# Column Swapping

## 题面翻译

如果一个表格每行都单调不降，称它为好的。  
给你 $t$ 个 $n_i$ 行 $m_i$ 列的表格，对于每个表格，询问是否能通过调换某两列 **（不一定不同）** 使得这个表格是好的（这样的操作需要且仅能执行一次）。如果可以，输出两列的编号；不可以，输出 $-1$。  

**输入格式**  
第一行一个正整数 $t$，表示表格的个数。  
接下来输入 $t$ 个表格。  
对于每个表格，第一行两个正整数 $n,m$，分别表示表格的行数与列数。  
接下来 $n$ 行，每行 $m$ 个正整数，表示这个表格。  

**输出格式**  
对于每个表格，单独输出一行，如果能通过上面描述的方式将其变为好的，输出对调的两列的编号；如果不能，输出 $-1$。

**说明/提示**  
$1\le t\le 100$  
$1\le n,m\le 2\times 10^5$  
$\sum n\times m\le 2\times 10^5$  
表格中的每一个数不超过 $10^9$  

**样例解释**  
**第一个**表格原本就是好的，因此可以将第一列和自己对调。  

**第二个**表格中，对调第 $1$ 和第 $2$ 列，会变成  
$$1,4$$  
$$3,2$$  
不是好的。如果对调任意一列和它自己，就是原本的表格，不是好的。因此输出 `-1`。  

**第三个**表格中，对调第 $1$，$2$ 列，表格变为  
$$1,2$$
$$1,1$$
是好的。因此输出 `1 2`。  

**第四个**表格中，调换第 $1$，$3$ 列，表格变为  
$$1,2,6$$  
$$3,4,5$$  
表格变为好的。输出 `1 3`  

**最后一个**表格中，每一行只有一个数，是单调不降的，但是只有一列，所以需要将这一列和自己对调。

## 题目描述

You are given a grid with $ n $ rows and $ m $ columns, where each cell has a positive integer written on it. Let's call a grid good, if in each row the sequence of numbers is sorted in a non-decreasing order. It means, that for each $ 1 \le i \le n $ and $ 2 \le j \le m $ the following holds: $ a_{i, j} \ge a_{i, j-1} $ .

You have to to do the following operation exactly once: choose two columns with indexes $ i $ and $ j $ (not necessarily different), $ 1 \le i, j \le m $ , and swap them.

You are asked to determine whether it is possible to make the grid good after the swap and, if it is, find the columns that need to be swapped.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 100 $ ). Description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 2 \cdot 10^5 $ ) — the number of rows and columns respectively.

Each of the next $ n $ rows contains $ m $ integers, $ j $ -th element of $ i $ -th row is $ a_{i, j} $ ( $ 1 \le a_{i, j} \le 10^9 $ ) — the number written in the $ j $ -th cell of the $ i $ -th row.

It's guaranteed that the sum of $ n \cdot m $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

If after the swap it is impossible to get a good grid, output $ -1 $ .

In the other case output $ 2 $ integers — the indices of the columns that should be swapped to get a good grid.

If there are multiple solutions, print any.

## 样例 #1

### 样例输入 #1

```
5
2 3
1 2 3
1 1 1
2 2
4 1
2 3
2 2
2 1
1 1
2 3
6 2 1
5 4 3
2 1
1
2
```

### 样例输出 #1

```
1 1
-1
1 2
1 3
1 1
```

## 提示

In the first test case the grid is initially good, so we can, for example, swap the first column with itself.

In the second test case it is impossible to make the grid good.

In the third test case it is needed to swap the first and the second column, then the grid becomes good.

## 题解
我们首先能够发现，如果一个数列中，有超过两个错位得位置，那么就说明我们是不能变化的。
如果在共计 m 数列中，我们错位得位置是不一样的，我们也要输出 false。
我们于是就可以先对我们原来的数列进行一个排列，然后再拿排列后的数列和我们的原数列比较，如果有错误，我们就记为 1，最后我们只需要比较我们这个和上一个是不是一样的，如果所有都是，我们才是 1，否则我们就是 0

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200010];
vector<int> c[200010];
int b[200010];
vector<int> s;
vector<int> x;
bool check(int w){
	if(w==1){
		return 1;
	}
	for(int i=1;i<w;i++){
		if(c[i][x[0]-1]!=c[i][x[1]-1]){
			return 0;
		}
	}
	return 1;
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n,m;
		x.clear();
		s.clear();
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			c[i].clear();
		}
		int flag=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				scanf("%d",&a[j]);
				b[j]=a[j];
			}
			for(int j=1;j<=m;j++){
				c[i].push_back(a[j]);
			}
			x.clear();
			if(m==1){
				flag=0;
				continue;
			}
			if(flag){
				continue;
			}
			sort(b+1,b+m+1);
			for(int j=1;j<=m;j++){
				if(b[j]!=a[j]){
					x.push_back(j);
				}
			}
			if(x.size()>2){
				flag=1;
				continue;
			}
			if(x.size()==0){//特判，如果当前错点数为零，则需之前错点数也为0，或当前数组允许按照之前的错点位置交换（a[s[0]]==a[s[1]]）
				if(s.size()==0){
					continue;
				}
				if(a[s[0]]==a[s[1]]){
					continue;
				}
				flag=1;
				continue;
			}
			if(s.size()==0){//同上，check是检查之前的数组是否允许按照现在的错点位置交换
				if(check(i)){
					s.push_back(x[0]);
					s.push_back(x[1]);
					continue;
				}
				else{
					flag=1;
					continue;
				}
			}
			for(int j=0;j<x.size();j++){
				if(s[j]!=x[j]){
					flag=1;
					break;
				}
			}
		}
		if(m==1){
			flag=0;
		}
		if(flag==1){
			printf("-1\n");
			continue;
		}
		if(s.size()==0){
			printf("1 1\n");
			continue;
		}
		printf("%d %d\n",s[0],s[1]);
	}
return 0;
}
```
