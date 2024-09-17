数轴上有 n (1<=n<=25000)个闭区间 $[ai, bi]$，选择尽量少的区间覆盖一条指定线段 $[1, t]$（ 1<=t<=1,000,000）。  
覆盖整点，即(1,2)+(3,4)可以覆盖(1,4)。  
不可能办到输出-1

输入

```r
   第一行：N和T
   第二行至N+1行: 每一行一个闭区间。
```

输出

选择的区间的数目，不可能办到输出-1

样例输入

3 10  
1 7  
3 6  
6 10

样例输出

2

提示

```
   这道题输入数据很多，请用scanf而不是cin
```


## 题解
1.将区间按照起点排序，并且保证起点相同的，终点大的排在前边

2.在前一个选取的区间范围$[L0,R0+1]$中，选取起点在此范围但终点最靠右的一个区间

3.重复这个过程

```cpp
//选择开始节点在上一区间范围内结束节点大的区间
//选择开始节点在上一区间范围内结束节点大的区间
#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAX_N 25000
using namespace std;
int n,t;
pair<int,int> s[MAX_N];
void solve(){
	sort(s,s+n);
	if(s[0].first>1){
		printf("-1\n");
		return;
	}
	int ans=0,pos=0,i=0;
	while(pos<t&&i<n){
		int temp=pos;
		if(s[i].first>pos+1)
			break;
		while(s[i].first<=pos+1&&i<n){//外层每循环一次只改变一次pos 所以int temp 
			temp=max(temp,s[i].second);
			i++;
		}
		ans++; 
		pos=temp;
	}
	if(pos<t)
		printf("-1\n");
	else
		printf("%d\n",ans);
		return;
//	fclose(stdin);
//	fclose(stdout);
}
int main(){
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout); 
	scanf("%d %d",&n,&t);
	for(int i=0;i<n;i++)
		scanf("%d %d",&s[i].first,&s[i].second);
	solve();
	return 0;
} 
```