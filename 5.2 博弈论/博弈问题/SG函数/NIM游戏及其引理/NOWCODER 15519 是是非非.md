## 题目描述
有一些石子堆，第$i$堆有$a_{i}$个石子，你和算卦先生轮流从任意队中任取若干个石子，每次只能取自一堆，且不能不去，取到最后一颗石子的人获胜，问是否先手必胜？

## 输入格式

第一行两个正整数 n,q，表示有 n 个石堆，q 次操作。 

第二行 n 个整数，第 i 个数 ai​ 表示第 i 个石堆初始有 ai​ 个石子。 

接下去 q 行，每行两个正整数 x,y，表示把第 x 堆石子的个数修改成 y。操作是累计的，也就是说，每次操作是在上一次操作结束后的状态上操作的。


## 输出格式
共计q行，输出每次操作时候先手是否有必胜策略。
如果有，输出“KAN”，否则输出“Li”


## 样例 #1

### 样例输入 #1

```
5 4
6 7 3 4 5
1 6
2 1
2 4
5 5
```

### 样例输出 #1

```
Kan
Kan
Li
Li
```

## 题解
对NIM游戏的简单应用

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N];
int main(){
	int n,m;
	cin>>n>>m;
	int ans=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		ans^=a[i];
	}
	while(m--){
		int x,y;
		cin>>x>>y;
		ans^=a[x];
		a[x]=y;
		ans^=a[x];
		cout<<(ans?"Kan":"Li")<<endl;
	}
}
```