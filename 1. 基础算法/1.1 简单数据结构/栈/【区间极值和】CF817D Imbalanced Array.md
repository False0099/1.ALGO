# Imbalanced Array

## 题面翻译

对于给定由 n 个元素构成的数组。一个子数组的不平衡值是这个区间的最大值与最小值的差值。数组的不平衡值是它所有子数组的不平衡值的总和。

以下是数组[1,4,1]不平衡值为 9 的例子，共有 6 个子序列：

[1] (从第一号到第一号)不平衡值为 0；

[1, 4] (从第一号到第二号), 不平衡值为 3;

[1, 4, 1] (从第一号到第三号), 不平衡值为 3;

[4] (从第二号到第二号), 不平衡值为 0;

[4, 1] (从第二号到第三号), 不平衡值为 3;

[1] (从第三号到第三号)不平衡值为 0；

## 题目描述

You are given an array $ a $ consisting of $ n $ elements. The imbalance value of some subsegment of this array is the difference between the maximum and minimum element from this segment. The imbalance value of the array is the sum of imbalance values of all subsegments of this array.

For example, the imbalance value of array $ [1,4,1] $ is $ 9 $ , because there are $ 6 $ different subsegments of this array:

- $ [1] $ (from index $ 1 $ to index $ 1 $ ), imbalance value is $ 0 $ ;
- $ [1,4] $ (from index $ 1 $ to index $ 2 $ ), imbalance value is $ 3 $ ;
- $ [1,4,1] $ (from index $ 1 $ to index $ 3 $ ), imbalance value is $ 3 $ ;
- $ [4] $ (from index $ 2 $ to index $ 2 $ ), imbalance value is $ 0 $ ;
- $ [4,1] $ (from index $ 2 $ to index $ 3 $ ), imbalance value is $ 3 $ ;
- $ [1] $ (from index $ 3 $ to index $ 3 $ ), imbalance value is $ 0 $ ;

You have to determine the imbalance value of the array $ a $ .

## 输入格式

The first line contains one integer $ n $ ( $ 1<=n<=10^{6} $ ) — size of the array $ a $ .

The second line contains $ n $ integers $ a_{1}, a_{2}...\ a_{n} $ ( $ 1<=a_{i}<=10^{6} $ ) — elements of the array.

## 输出格式

Print one integer — the imbalance value of $ a $ .

## 样例 #1

### 样例输入 #1

```
3
1 4 1
```

### 样例输出 #1

```
9
```

## 题解
第一步，首先我们注意到，我们的每一个贡献是可以进行**拆分的**，也就是说，我们可以转换为求
$$\sum_{l=1}^n\sum_{r=l}^n\max_{i=l}^r(a_i)-\sum_{l=1}^n\sum_{r=l}^n\min_{i=l}^r(a_i)$$

因此，我们考虑怎么分别求出我们上面的两个式子：
首先，我们注意到，我们可对于每一个元素，计算这一个元素对于我们的答案的贡献，对应的贡献就是这一个答案的值乘以，**以这个值位最小值的区间数**。

而我们的以这个值位最小值的**区间数**，可以通过计算，我们的一这个数为最小值的**最远左边界，最远右边界**来联合计算得出。

这个时候，我们考虑怎么求出**最远左边界，最远有边界**。首先，我们不难发现，如果我们要求出我们的最远边界，我们可以通过我们的**单调栈来进行**，我们单调栈**维护所有可能的左节点**。然后我们会发现，我们的左节点的可能值范围应该是呈现一个 min 上升，max 下降的趋势。

**我们的比较写的是什么，就代表我们求的是第一个比什么还要小的元素**。

于是，我们就可以写出我们的下面的代码：
```
#include <bits/stdc++.h>
#define int long long
const int N=1e6+10;
int a[N],l[N],r[N],top,stk[N],ans;
using namespace std;
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	top=0;
	for(int i=1;i<=n;i++){
		while(top&&a[stk[top]]>=a[i]){
			top--;
		}
		if(top==0){
			l[i]=0;
		}else{
			l[i]=stk[top];
		}
		stk[++top]=i;
	}
	top=0;
	for(int i=n;i>=1;i--){
		while(top&&a[stk[top]]>a[i]){
			top--;
		}
		if(top==0){
			r[i]=n+1;
		}else{
			r[i]=stk[top];
		}
		stk[++top]=i;
	}
	for(int i=1;i<=n;i++){
		ans+=a[i]*(i-l[i])*(r[i]-i);
	}
	top=0;
	for(int i=1;i<=n;i++){
		while(top&&a[stk[top]]<=a[i]){
			top--;
		}
		if(top==0){
			l[i]=0;
		}else{
			l[i]=stk[top];
		}
		stk[++top]=i;
	}
	top=0;
	for(int i=n;i>=1;i--){
		while(top&&a[stk[top]]<a[i]){
			top--;
		}
		if(top==0){
			r[i]=n+1;
		}else{
			r[i]=stk[top];
		}
		stk[++top]=i;
	}
	for(int i=1;i<=n;i++){
		ans-=0;
	}
	cout<<abs(ans)<<endl;
}
```

