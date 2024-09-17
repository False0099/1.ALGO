# 
## 题目描述
N个气球排成一排，从左到右依次编号为1,2,3....N.每次给定2个整数a b(a <= b),lele便为骑上他的“小飞鸽"牌电动车从气球a开始到气球b依次给每个气球涂一次颜色。但是N次以后lele已经忘记了第I个气球已经涂过几次颜色了，你能帮他算出每个气球被涂过几次颜色吗？

## 输入格式
每个测试实例第一行为一个整数 N,(N <= 100000).接下来的 N 行，每行包括2个整数 a b(1 <= a <= b <= N)。  
当N = 0，输入结束。


## 输出格式
每个测试实例输出一行，包括N个整数，第I个数代表第I个气球总共被涂色的次数。

## 样例 #1

### 样例输入 #1

```
3
1 1
2 2
3 3
3
1 1
1 2
1 3
0
```

### 样例输出 #1

```
1 1 1
3 2 1

```

## 题解
这是一道树状数组维护区间修改+单点查询的模板题目，我们只需要套用树状数组的模板即可，但实际上该种算法是不如差分数组优秀的。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define lowbit(x) ((x)&(-x));

//树状数组用于区间修改，单点查询 
const int N=1010; 
int tree[N]; 
void update(int x,int d){
	while(x<=N){
		tree[x]+=d;
		x+=lowbit(x);
	}
}
int sum(int x){
	int res=0;
	while(x>0){
		res+=tree[x];
		x-=lowbit(x);
	}
	return res;
}
int n;
int main(){
	cin>>n;
	memset(tree,0,sizeof tree);
	for(int i=0;i<=n;i++){
		int l,r;
		cin>>l>>r;
		update(l,1);
		update(r+1,-1);
	}
	for(int i=1;i<=n;i++){
		if(i!=n){
			cout<<sum(i)<<" ";
		}else{
			cout<<sum(i)<<endl;
		}
	}
}
```