## 题目描述
给定你由N个整数构成的整数序列，你可以从中选取一些（甚至一个）进行异或（XOR）运算，从而得到很多不同的结果。

请问，所有能得到的不同的结果中第k小的结果是多少。

**数据范围**

1≤N,Q≤10000,

1≤ki≤1e18

## 输入格式
第一行包含整数T，表示共有T组测试数据。

对于每组测试数据，第一行包含整数N。

第二行包含N个整数(均在1至1e18之间)，表示完整的整数序列。

第三行包含整数Q，表示询问的次数。

第四行包含Q个整数k1,k2,…,kQ,表示Q个询问对应的k。


## 输出格式
对于每组测试数据，第一行输出“Case C:”，其中C为顺序编号（从1开始）。

接下来Q行描述Q次询问的结果，每行输出一个整数，表示第i次询问中第ki小的结果。

如果能得到的不同结果的总数少于ki，则输出“-1”。


## 样例 #1

### 样例输入 #1

```
2
2
1 2
4
1 2 3 4
3
1 2 3
5
1 2 3 4 5
```

### 样例输出 #1

```
Case #1:
1
2
3
-1
Case #2:
0
1
2
3
-1
```

## 题解
典，只要我们会用线性异或基来表示出第k大数即可，线性异或基的求法我们可以参照高斯消元求解异或方程组的方法。通过观察法，我们可以得到第k大异或和就是我们选第$2^t-k$的二进制所对应的那些行，其中t为我们的线性基元素个数。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=10100;
int n;
bool zero;
int a[N];
typedef long long ll;
void gauss(){
	int i,k=1;
	ll j=(ll)1<<62;
	for(;j;j>>1){
		for(int i=k;i<=n;i++){
			if(a[i]&j) break;//找到j位为1的 
		}
		if(i>n) continue;
		swap(a[i],a[k]);//把这一行换到上面
		for(int i=1;i<=n;i++){
			if(i!=k&&a[i]&j) a[i]^=a[k];
		} 
		k++;
	}
	k--;
	if(k!=n) zero=true;
	else zero=false;
	n=k;//线性基的个数 
}
ll query(ll k){
	ll ans=0;
	if(zero) k--;
	if(!k) return 0;
	for(int i=n;i;i--){
		if(k&1) ans^=a[i];
		k>>1;
	}
	if(k) return -1;
	return ans;
} 
int main(){
	int cnt=0;
	int t;
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		gauss();
		int q;
		cin>>q;
		while(q--){
			ll k;
			cin>>k;
			cout<<query(k)<<endl;
		}
	}
}
```