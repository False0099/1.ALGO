# Woodcutters

## 题面翻译

给 $n$ 棵树在一维数轴上的坐标 $x_i$，以及它们的长度 $h_i$。现在要你砍倒这些树，树可以向左倒也可以向右倒，砍倒的树不能重合、当然也不能覆盖其他的树原来的位置，现在求最大可以砍倒的树的数目。

$ 1 \le n \le {10}^5$

$ 1 \le x_i, h_i \le {10}^9$

## 题目描述

Little Susie listens to fairy tales before bed every day. Today's fairy tale was about wood cutters and the little girl immediately started imagining the choppers cutting wood. She imagined the situation that is described below.

There are $ n $ trees located along the road at points with coordinates $ x_{1}, x_{2},..., x_{n} $ . Each tree has its height $ h_{i} $ . Woodcutters can cut down a tree and fell it to the left or to the right. After that it occupies one of the segments $ [x_{i}-h_{i}, x_{i}] $ or $ [x_{i}; x_{i}+h_{i}] $ . The tree that is not cut down occupies a single point with coordinate $ x_{i} $ . Woodcutters can fell a tree if the segment to be occupied by the fallen tree doesn't contain any occupied point. The woodcutters want to process as many trees as possible, so Susie wonders, what is the maximum number of trees to fell.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of trees.

Next $ n $ lines contain pairs of integers $ x_{i}, h_{i} $ ( $ 1<=x_{i}, h_{i}<=10^{9} $ ) — the coordinate and the height of the $ і $ -th tree.

The pairs are given in the order of ascending $ x_{i} $ . No two trees are located at the point with the same coordinate.

## 输出格式

Print a single number — the maximum number of trees that you can cut down by the given rules.

## 样例 #1

### 样例输入 #1

```
5
1 2
2 1
5 10
10 9
19 1
```

### 样例输出 #1

```
3
```

## 样例 #2

### 样例输入 #2

```
5
1 2
2 1
5 10
10 9
20 1
```

### 样例输出 #2

```
4
```

## 提示

In the first sample you can fell the trees like that:

- Fell the $ 1 $ -st tree to the left — now it occupies segment $ [-1; 1] $
- Fell the $ 2 $ -nd tree to the right — now it occupies segment $ [2; 3] $
- Leave the $ 3 $ -rd tree — it occupies point $ 5 $
- Leave the $ 4 $ -th tree — it occupies point $ 10 $
- Fell the $ 5 $ -th tree to the right — now it occupies segment $ [19; 20] $

In the second sample you can also fell $ 4 $ -th tree to the right, after that it will occupy segment $ [10; 19] $ .

## 题解
我们本题的思路是，首先让我们两端的树直接往两端倒，然后对于每一棵树，我们计算能不能向左倒，可以的话，我们就尽可能的向左倒，否则，我们就判断我们向右导会不会覆盖到我们之前的元素，如果会覆盖，那么我们就不倒这一颗树，否则，我们让我们的这一颗树向右倒。

这样的话，我们最后得到的结果一定是我们的最终结果。因为我们如果这个结果不优的话，我们也不会得到更优的策略了。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> PII;
int main(){
	int n;
	cin>>n;
	vector<PII> tr(n); 
	for(int i=0;i<n;i++){
		int x,h;
		cin>>x>>h;
		tr[i]={x,h};
	}
	if(n==1){
		cout<<1<<endl;
		return 0;
	}
	sort(tr.begin(),tr.end());
	int ans=0;
	ans+=2;
	for(int i=1;i<n-1;i++){
		if(tr[i].first-tr[i-1].first>tr[i].second){
			ans++;
		}else if(tr[i+1].first-tr[i].first>tr[i].second){
			ans++;
			tr[i].first=tr[i].first+tr[i].second; 
		}
	}
	cout<<ans<<endl;
	
}
```