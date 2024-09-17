# Valiant's New Map

## 题面翻译

给定一个带权值的 $n×m$ 网格，你可以选取一块边长为 $l$ 的正方形区域当且仅当该区域的所有权值都大于等于 $l$，问可以选取的最大正方形区域的边长。

## 题目描述

Game studio "DbZ Games" wants to introduce another map in their popular game "Valiant". This time, the map named "Panvel" will be based on the city of Mumbai.

Mumbai can be represented as $ n \times m $ cellular grid. Each cell $ (i, j) $ ( $ 1 \le i \le n $ ; $ 1 \le j \le m $ ) of the grid is occupied by a cuboid building of height $ a_{i, j} $ .

This time, DbZ Games want to make a map that has perfect vertical gameplay. That's why they want to choose an $ l \times l $ square inside Mumbai, such that each building inside the square has a height of at least $ l $ .

Can you help DbZ Games find such a square of the maximum possible size $ l $ ?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \leq t \leq 1000 $ ). Description of the test cases follows.

The first line of each test case contains two positive integers $ n $ and $ m $ ( $ 1 \le n \le m $ ; $ 1 \leq n \cdot m \leq 10^6 $ ).

The $ i $ -th of next $ n $ lines contains $ m $ integers $ a_{i, 1}, a_{i, 2}, \dots, a_{i, m} $ ( $ 1 \leq a_{i, j} \leq 10^6 $ ) — heights of buildings on the $ i $ -th row.

It's guaranteed that the sum of $ n \cdot m $ over all test cases doesn't exceed $ 10^6 $ .

## 输出格式

For each test case, print the maximum side length $ l $ of the square DbZ Games can choose.

## 样例 #1

### 样例输入 #1

```
4
2 2
2 3
4 5
1 3
1 2 3
2 3
4 4 3
2 1 4
5 6
1 9 4 6 5 8
10 9 5 8 11 6
24 42 32 8 11 1
23 1 9 69 13 3
13 22 60 12 14 17
```

### 样例输出 #1

```
2
1
1
3
```

## 提示

In the first test case, we can choose the square of side $ l = 2 $ (i. e. the whole grid) since the heights of all buildings are greater than or equal to $ 2 $ .

In the second test case, we can only choose the side as $ 1 $ , so the answer is $ 1 $ .

In the third test case, there are no squares of size $ 2 $ that have all buildings of height at least $ 2 $ , so the answer is $ 1 $ .

## 题解
我们本题的思路，就是通过我们的二分法，来优化我们的边长的枚举，然后我们在考虑怎么去 check 我们的操作。

在这里，我们要判定一个区域内是矩形，那么我们就可以考虑用我们的 bfs 或者我们的 dfs 判断我们的连通块。

再或者，因为我们的周长是已知的，我们可以考虑用我们的一个前缀和来进行检查。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=1e6+10;
ll T,n,m,ans,t,l,r,mid;
vector<ll> a[N],f[N];
bool check(ll p){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			f[i][j]=a[i][j]<mid;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			f[i][j]+=f[i-1][j]+f[i][j-1]-f[i-1][j-1];
	for(int i=1;i+p<=n;i++)
		for(int j=1;j+p<=m;j++)
			if(!(f[i+p][j+p]+f[i-1][j-1]-f[i-1][j+p]-f[i+p][j-1]))
				return 1;
	return 0;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
		cin>>n>>m;
		f[0].clear();
		for(int i=0;i<=m;i++) f[0].push_back(0);		
		for(int i=1;i<=n;i++){
			a[i].clear();
			a[i].push_back(0);
			f[i].clear();
			f[i].push_back(0);
			for(int j=1;j<=m;j++){
				cin>>t;
				a[i].push_back(t);
				f[i].push_back(0);
			}
		}
		l=1,r=n;
		while(l<=r){
			mid=l+r>>1;
			if(check(mid-1)) l=mid+1,ans=mid;
			else r=mid-1;
		}
		cout<<ans<<"\n";
    }
	return 0;
}
```