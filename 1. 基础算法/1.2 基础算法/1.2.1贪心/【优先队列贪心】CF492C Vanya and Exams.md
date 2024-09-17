# Vanya and Exams

## 题面翻译

Venya 有 $n$ 门课程，每门课程他最多获得 $r$ 学分，他只要所有课程的平均学分大于等于 $avg$，他就可以获得奖学金。

目前对于第 $i$ 门课程，他已经获得了 $a_i$ 学分，剩下的每个学分，都需要写 $b_i$ 篇论文才能得到。请问 Venya 最少要写多少论文才能获得奖学金？

数据保证 $1\le n\le 10^5,1\le avg\le 10^6,1\le r\le 10^9$。

## 题目描述

Vanya wants to pass $ n $ exams and get the academic scholarship. He will get the scholarship if the average grade mark for all the exams is at least $ avg $ . The exam grade cannot exceed $ r $ . Vanya has passed the exams and got grade $ a_{i} $ for the $ i $ -th exam. To increase the grade for the $ i $ -th exam by 1 point, Vanya must write $ b_{i} $ essays. He can raise the exam grade multiple times.

What is the minimum number of essays that Vanya needs to write to get scholarship?

## 输入格式

The first line contains three integers n, r, avg (1 ≤ n ≤ 105, 1 ≤ r ≤ 109, 1 ≤ avg ≤ min (r, 106)) — the number of exams, the maximum grade and the required grade point average, respectively.

Each of the following n lines contains space-separated integers ai and bi (1 ≤ ai ≤ r, 1 ≤ bi ≤ 106).

## 输出格式

In the first line print the minimum number of essays.

## 样例 #1

### 样例输入 #1

```
5 5 4
5 2
4 7
3 1
3 2
2 5
```

### 样例输出 #1

```
4
```

## 样例 #2

### 样例输入 #2

```
2 5 4
5 2
5 2
```

### 样例输出 #2

```
0
```

## 提示

In the first sample Vanya can write 2 essays for the 3 rd exam to raise his grade by 2 points and 2 essays for the 4 th exam to raise his grade by 1 point.

In the second sample, Vanya doesn't need to write any essays as his general point average already is above average.

## 题解
我们本题的思路是：我们肯定是优先选择我们的水课，然后每一次选完后，再去看我们当前的学分是否已经达到要求，如果已经达到要求，那么我们直接退出即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int n,r,avg;
	cin>>n>>r>>avg;
	avg*=n;
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> heap; 
	for(int i=0;i<n;i++){
		int u,v;
		cin>>u>>v;
		avg-=u;
		heap.push({v,r-u});
	}
	if(avg<=0){
		cout<<0<<endl;
		return 0;
	}
	int prc=0;
	while(heap.size()){
		auto u=heap.top();
		heap.pop();
		int sc=u.first;
		int num=u.second;
		if(avg>num){
			prc+=num*sc;
			avg-=num;
		}else{
			prc+=avg*sc;
			break;
		}
	}
	cout<<prc<<endl;
}

```