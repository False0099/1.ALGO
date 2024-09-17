Long times ago, there are beautiful historic walls in the city. These walls divide the city into many parts of area.  
  
Since it was not convenient, the new king wants to destroy some of these walls, so he can arrive anywhere from his castle. We assume that his castle locates at (0.6∗2,0.6∗3)(0.6∗2​,0.6∗3​).  
  
There are n towers in the city, which numbered from 1 to n. The ith's location is (xi​,yi​). Also, there are m walls connecting the towers. Specifically, the ith wall connects the tower ui​ and the tower vi​(including the endpoint). The cost of destroying the ith wall is wi​.  
  
Now the king asks you to help him to divide the city. Firstly, the king wants to destroy as less walls as possible, and in addition, he wants to make the cost least.  
  
The walls only intersect at the endpoint. It is guaranteed that no walls connects the same tower and no 2 walls connects the same pair of towers. Thait is to say, the given graph formed by the walls and towers doesn't contain any multiple edges or self-loops.  
  
Initially, you should tell the king how many walls he should destroy at least to achieve his goal, and the minimal cost under this condition.  

Input

There are several test cases.  
  
For each test case:  
  
The first line contains 2 integer n, m.  
  
Then next n lines describe the coordinates of the points.  
  
Each line contains 2 integers xi​,yi​.  
  
Then m lines follow, the ith line contains 3 integers ui​,vi​,wi​  
  
∣xi​∣,∣yi​∣≤105  
  
3≤n≤100000,1≤m≤200000  
  
1≤ui​,vi​≤n,ui​=vi​,0≤wi​≤10000  

Output

For each test case outout one line with 2 integers sperate by a space, indicate how many walls the king should destroy at least to achieve his goal, and the minimal cost under this condition.  

Sample

|Inputcopy|Outputcopy|
|---|---|
|4 4<br>-1 -1<br>-1 1<br>1 1<br>1 -1<br>1 2 1<br>2 3 2<br>3 4 1<br>4 1 2|1 1|


## 题解
给我们一个对偶图，问我们删除最少多少条边，最少用多少权值删边？能让我们的原图联通。
通过我们的对偶图，我们就把问题转换为：这个国王被围起来，他要访问它所有的城市，必然要拆遍，不然出不去，就是说拆掉多少遍，使图成为联通的，也就是说不会保留环即可，无论这个国王在哪，这个图只要有环，就不能遍历，所以跟每个点的坐标没有任何关系，直接剔除环中的最小边，但是这样对吗？我们要使剃边花费最小，那么就要使剃边后剩下的无向无环图的边权和最最大，因为剔除环中最小边，不能保证提出的和最小，所以一遍最大生成树。
![[Pasted image 20231102161239.png]]


```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
int n, m;
struct node
{
	int x, y, s;
	bool operator <(const node &t) const
	{
		return s > t.s;
	}
};
int fa[N];

int find_(int x)
{
	return x == fa[x] ? x: fa[x] = find_(fa[x]);
}
int main()
{
	while(~scanf("%d%d", &n, &m))
	{
		for(int i = 1; i <= n; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			fa[i] = i;
		}
		vector<node> v;
		int all = 0;
		for(int i = 1; i <= m; i ++)
		{
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			v.push_back({x, y, z});
			all += z;
		}
		sort(v.begin(), v.end());
		int sum = 0;
		int ans = 0;
		for(int i = 0; i < m; i++)
		{
			int x = v[i].x, y = v[i].y;
			int x1 = find_(x), y1 = find_(y);
			if(x1 != y1)
			{
				fa[x1] = y1;
				ans ++;
				sum += v[i].s;
			}
		}
		int x = 1;
		printf("%d %d\n", m - ans, all - sum);
	}
}
```

