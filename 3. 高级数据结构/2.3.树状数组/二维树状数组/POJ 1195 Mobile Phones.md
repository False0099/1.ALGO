Tampere 地区的4G 手机基站运行原理如下：信号覆盖区域被划分为若干个正方形小区域，整个信号覆盖区域是一个由若干正方形小区域组成的 S * S 矩阵（下标从 0 到 S-1）。每个小区域包含一个基站，每个基站所连接的手机数量可能会随时变化。

## 输入

多组输入，每行输入一个整数 op 代表操作编号：

- 操作0: 输入一个整数 S 表示初始化一个 S * S 的空区域。
- 操作1: 输入三个整数 x,y,a 代表坐标 (x,y) 的小区域中增加了 a 个手机上线。
- 操作2: 输入四个整数 x1,y1,x2,y2 分别代表一个矩形区域的左上角坐标和右下角坐标，求区域中所有小区域在线手机数量之和。
- 操作3: 结束程序。

## 输出

对于每个操作2，求区域中所有小区域在线手机数量之和。

## 样例输入

0 4
1 1 2 3
2 0 0 2 2 
1 1 1 2
1 1 2 -1
2 1 1 2 3 
3

## 样例输出

3
4

## 提示

1 <= s <= 1024

每个小区域的同时在线手机数量小于等于 32767。

指令数小于等于 60002。

每次上线的手机数量大于等于 -32768 小于等于 32767。

整个信号覆盖区域的同时在线手机量小于等于 2^30。

## 题解
我们这一题说标准的二维树状数组，我们只需要按照模板写一下即可
```cpp
#include <cstring>
#include <cstdio>
using namespace std;
int tr[1500][1500], n;
int lowbit(int x){
	return x&(-x);
}
void updata(int x, int y, int a){
	for(int i=x; i<=n; i+=lowbit(i)){
		for(int j=y; j<=n; j+=lowbit(j)){
			tr[i][j]+=a;
		}
	}
}
int getsum(int x, int y){
	int s=0;
	for(int i=x; i>0; i-=lowbit(i)){
		for(int j=y; j>0; j-=lowbit(j)){
			s+=tr[i][j];
		}
	}
	return s;
}
int main(){
	int op, x, y, a, l, b, r, t;
	memset(tr, 0, sizeof(tr));
	scanf("%d%d", &op, &n);
	while(scanf("%d", &op)){
		if(op==3) break;
		if(op==1){
			scanf("%d%d%d", &x, &y, &a);
			updata(x+1, y+1, a);
		}
		if(op==2){
			scanf("%d%d%d%d", &l, &b, &r, &t);
			printf("%d\n", getsum(r+1, t+1)-getsum(l, t+1)-getsum(r+1, b)+getsum(l, b));
		}
	}
	return 0;
}
```