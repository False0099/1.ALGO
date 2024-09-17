#贪心 
现在有 n 个和为 m 的正整数，你可以去掉任意一个数然  
后把剩下的 n - 1 个数分成两个集合，这两个集合中数的和  
必须都小于等于 m/2 ，试构造一个方案

## 数据范围
n ≤ 100000; m ≤ 1000000

## 要求
时间复杂度 O(n)，空间复杂度 O(1)。

n 和 m 都会在第一行输入。输出方式为对于每一个  
数字输出 0 或 1 表示它在哪一个集合中。

## 题解
我们的思路就是先把我们的最大值丢了，然后我们再考虑让我们的每个数，能加第一个就加第一个，不行我们再去加第二个。这样我们就能得到我们的答案。
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int sum1;
	int sum2;
	int n;
	int m;
	cin>>n>>m;
	for(int i=0;i<n;i++){
		cin>>a[i];
		ma=max(ma,a[i]);
	} 
	bool flag=false;
	for(int i=0;i<n;i++){
		if(a[i]==ma&&flag=false){
			flag=true;
			continue;
		}
		if(sum1+a[i]<s/2){
			sum1+=a[i];
			continue;
		}else{
			sum2+=a[i];
		}
	}
}
```