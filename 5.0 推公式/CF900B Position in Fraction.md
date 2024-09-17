# Position in Fraction

## 题面翻译

### 题目描述

给你三个整数 $a,b,c$，问 $\dfrac{a}{b}$ 的小数部分第几位是 $c$，如果无法找到，请输出 `-1`。

### 输入格式

共一行，三个整数 $a,b,c$。

### 输出格式

共一行，输出一个整数，表示 $c$ 的位置或 `-1`。

### 数据范围

对于 $100\%$ 的数据：$1\le a<b\le 10^5,0\le c\le 9$。

## 题目描述

You have a fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF900B/eecd60ed91fbeebe74e2406ea1a11d26df905945.png). You need to find the first occurrence of digit $ c $ into decimal notation of the fraction after decimal point.

## 输入格式

The first contains three single positive integers $ a $ , $ b $ , $ c $ ( $ 1\le a<b\le 10^{5} $ , $ 0\le c\le 9 $ ).

## 输出格式

Print position of the first occurrence of digit $ c $ into the fraction. Positions are numbered from $ 1 $ after decimal point. It there is no such position, print -1.

## 样例 #1

### 样例输入 #1

```
1 2 0
```

### 样例输出 #1

```
2
```

## 样例 #2

### 样例输入 #2

```
2 3 7
```

### 样例输出 #2

```
-1
```

## 提示

The fraction in the first example has the following decimal notation: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF900B/478006b79aae95ccc3ae3b2220456bccad4ba042.png). The first zero stands on second position.

The fraction in the second example has the following decimal notation: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF900B/81c5a2a549836b2498b7beebd8cc86c8a4b47b0a.png). There is no digit $ 7 $ in decimal notation of the fraction.

## 题解
我们这一题可以仿照我们的十进制计算来进行处理，某种意义上可以算是一个大模拟题目。我们于是就可以采用我们的乘 10 取余法得到我们的每一位是多少。而我们只需要进行我们的 `1e5` 次即可。
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int mxn = 1e5+5;
int a,b,c,d,cnt;
bool ap[mxn];
int main(){
	scanf("%d%d%d",&a,&b,&c);
	a%=b;  //去除整数部分
	cnt=1;  //当前小数位数为1
	while(1){  //循环模拟除法
		a*=10;
		d=a/b;   //算小数部分
		a%=b;   //取余数
		if(d==c){  //找到第一个出现的位置，直接输出
			printf("%d",cnt);
			return 0;
		}
		if(ap[a])  //余数出现两次，有循环节，跳出
			break;
		ap[a]=true;
		cnt++;   //增加小数位数
	}
	printf("-1");  //未找到解
	return 0;
}
```