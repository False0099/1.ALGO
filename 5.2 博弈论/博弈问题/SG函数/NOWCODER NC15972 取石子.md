## 题目描述

现在有两堆石子，两个人轮流从中取石子，且每个人每一次只能取1、3或9个石子，取到最后一个石子的人win。  
假设先手后手都会选择最好的方式来取石子，请您判断先后手的输赢情况。

## 输入格式
多组输入  
每组一行，一行包括两个正整数n1和n2(1<=n1<=100,1<=n2<=100)，代表了两堆石子的数目

## 输出格式

如果先手能赢，输出"win"；否则就输出"lose"。

## 样例 #1

### 样例输入 #1

```
1 1 
1 2
```

### 样例输出 #1

```
lose
win
```

## 题解
打表、sg函数教学题

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N];
map<pair<int,int>,bool> mp;
int f(int x,int y){
	if(mp.count({x,y})) return mp[{x,y}];
	bool res=false;
	if(x>=1)if(!f(x-1,y)) res=true;
	if(x>=3)if(!f(x-3,y)) res=true;
	if(x>=9)if(!f(x-9,y)) res=true;
	if(y>=1)if(!f(x,y-1)) res=true;
	if(y>=3)if(!f(x,y-3)) res=true;
	if(y>=9)if(!f(x,y-9)) res=true;
	return mp[{x,y}]=res;
}
int main(){
	int n,m;
	while(cin>>n>>m){
		cout<<(f(n,m)?"win":"lose")<<endl;
	} 
}
```