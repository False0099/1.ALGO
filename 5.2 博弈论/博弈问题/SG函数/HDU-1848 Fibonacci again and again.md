任何一个大学生对菲波那契数列(Fibonacci numbers)应该都不会陌生，它是这样定义的：  
F(1)=1;  
F(2)=2;  
F(n)=F(n-1)+F(n-2)(n>=3);  
所以，1,2,3,5,8,13……就是菲波那契数列。  
在HDOJ上有不少相关的题目，比如1005 Fibonacci again就是曾经的浙江省赛题。  
今天，又一个关于Fibonacci的题目出现了，它是一个小游戏，定义如下：  
1、  这是一个二人游戏;  
2、  一共有3堆石子，数量分别是m, n, p个；  
3、  两人轮流走;  
4、  每走一步可以选择任意一堆石子，然后取走f个；  
5、  f只能是菲波那契数列中的元素（即每次只能取1，2，3，5，8…等数量）；  
6、  最先取光所有石子的人为胜者；  
  
假设双方都使用最优策略，请判断先手的人会赢还是后手的人会赢。  

Input

输入数据包含多个测试用例，每个测试用例占一行，包含3个整数m,n,p（1<=m,n,p<=1000）。  
m=n=p=0则表示输入结束。  

Output

如果先手的人能赢，请输出“Fibo”，否则请输出“Nacci”，每个实例的输出占一行。  

Sample

|Inputcopy|Outputcopy|
|---|---|
|1 1 1<br>1 4 1<br>0 0 0|Fibo<br>Nacci|

## 题解
我们这一题可以直接用我们的 SG 函数进行我们的大表，毕竟我们的范围还是比较小的，所以我们这样子打表也不会有任何的问题。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1003;
int sg[maxn], s[maxn];
int n, m, p;
int fibo[15] = { 1,2,3 };
void getsg() {
	for (int i = 0; i <= maxn; i++) {
		memset(s, 0, sizeof(s));
		for (int j = 0; j < 15 && fibo[j] <= i; j++) 
			s[sg[i - fibo[j]]] = 1;  //更新后继节点
		for (int j = 0; j <= maxn; j++)  //找最小非负整数
			if (!s[j]) {
				sg[i] = j;
				break;
			}
	}
}
int main() {
	for (int i = 3; i < 15; i++)
		fibo[i] = fibo[i - 1] + fibo[i - 2];
	getsg();
	while (~scanf("%d%d%d", &n, &m, &p) && (n + m + p)) {
		if (sg[n] ^ sg[m] ^ sg[p])
			puts("Fibo");
		else puts("Nacci");
	}
	return 0;
}

```