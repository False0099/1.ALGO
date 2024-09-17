# Subway Innovation

## 题面翻译

### 题目描述：

直线上 $n$ 个点，定义点 $i, j$ 之间的距离为 $|x_i-x_j|$。保留 $k$ 个点，使这些点**两两之间的距离和**最小。输出 $k$ 个点的下标。

### 输入格式：

第一行，一个正整数 $n$，表示点的个数。

第二行，$n$ 个整数 $x_1,x_2,...,x_n$，表示每个点的位置。

第三行，一个正整数 $k$，含义如题目描述。

### 输出格式：

一行，$k$ 个正整数 $t_1,t_2,...,t_k$，表示保留的点的下标。两个正整数之间用一个空格连接。

注意答案不唯一，所有正确的答案都会被接受。

## 题目描述

Berland is going through tough times — the dirt price has dropped and that is a blow to the country's economy. Everybody knows that Berland is the top world dirt exporter!

The President of Berland was forced to leave only $ k $ of the currently existing $ n $ subway stations.

The subway stations are located on a straight line one after another, the trains consecutively visit the stations as they move. You can assume that the stations are on the $ Ox $ axis, the $ i $ -th station is at point with coordinate $ x_{i} $ . In such case the distance between stations $ i $ and $ j $ is calculated by a simple formula $ |x_{i}-x_{j}| $ .

Currently, the Ministry of Transport is choosing which stations to close and which ones to leave. Obviously, the residents of the capital won't be too enthusiastic about the innovation, so it was decided to show the best side to the people. The Ministry of Transport wants to choose such $ k $ stations that minimize the average commute time in the subway!

Assuming that the train speed is constant (it is a fixed value), the average commute time in the subway is calculated as the sum of pairwise distances between stations, divided by the number of pairs (that is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF371E/f4fbd613cfec98600821d349b4468b3c3a570baf.png)) and divided by the speed of the train.

Help the Minister of Transport to solve this difficult problem. Write a program that, given the location of the stations selects such $ k $ stations that the average commute time in the subway is minimized.

## 输入格式

The first line of the input contains integer $ n $ ( $ 3<=n<=3·10^{5} $ ) — the number of the stations before the innovation. The second line contains the coordinates of the stations $ x_{1}, x_{2},..., x_{n} $ ( $ -10^{8}<=x_{i}<=10^{8} $ ). The third line contains integer $ k $ ( $ 2<=k<=n-1 $ ) — the number of stations after the innovation.

The station coordinates are distinct and not necessarily sorted.

## 输出格式

Print a sequence of $ k $ distinct integers $ t_{1}, t_{2},..., t_{k} $ ( $ 1<=t_{j}<=n $ ) — the numbers of the stations that should be left after the innovation in arbitrary order. Assume that the stations are numbered 1 through $ n $ in the order they are given in the input. The number of stations you print must have the minimum possible average commute time among all possible ways to choose $ k $ stations. If there are multiple such ways, you are allowed to print any of them.

## 样例 #1

### 样例输入 #1

```
3
1 100 101
2
```

### 样例输出 #1

```
2 3
```

## 提示

In the sample testcase the optimal answer is to destroy the first station (with $ x=1 $ ). The average commute time will be equal to 1 in this way.

## 题解
我们本题的思路首先是，如果我们处理的曼哈顿距离在我们的一维上，那么我们首先需要强调的一点就是，如果我们要选择 $k$ 个，那么我们一定是选择连续的 $k$ 个，我们计算出来的最大值才是最小的。

于是现在我们的问题就是，怎么快速的求出连续的 $k$ 个元素的最大和是多少。我们首先不难发现，我们如果想要我们连续的 $k$ 个元素之间的两两曼哈顿距离和是多少，那么我们的方法一般来说是采用我们的递推来实现的。

我们每一次考虑我们上一位和我们的上一部分的差距是多少，我们发现，我们新加入一个点，对于我们答案的贡献是：$\sum_{j=i-k+1}^{i-1} x_{i}-x_{j}=(k-1)x_{i}-\sum_{j=i-k+1}^{i-1}x_{j}$,

于是，我们就能够简单的计算出我们的最后的贡献。

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int n,k;
long long sum1,sum2,ans,id;
struct node{
	int x,y;
}a[300005];
bool cmp(node fir,node sed){
	//if(fir.x==sed.x){
	//	return fir.y<sed.y;
	//}
	return fir.x<sed.x;
}
int main(){
	cin>>n;
	for (int i=0;i<n;i++){
		cin>>a[i].x;
		a[i].y=i+1;
	}
	sort(a,a+n,cmp);
	cin>>k;
	for (int i=0;i<k;i++){
		sum1+=a[i].x;
	}
	for (int i=k;i<n;i++){
		sum2+=1ll*(k-1)*(a[i].x+a[i-k].x)-2ll*(sum1-a[i-k].x);
		sum1+=a[i].x-a[i-k].x;
		if(sum2<ans){
			ans=sum2;
			id=i-k+1;
		}
	}
	for (int i=0;i<k;i++){
		cout<<a[id+i].y<<" ";
	}
	return 0;
}

```