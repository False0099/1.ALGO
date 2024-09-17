# Add Modulo 10

## 题面翻译

### 题意
每个测试点含多组测试数据。

对于每组测试数据

第 1 行一个整数 $n$ ，表示该数据个数

第 2 行 $n$ 个整数，你需要判断是否符合题意的数据

对每组数据，你可以对其作若干次（可以为零）如下操作：

选取数据中的一个数  $a_i$  将其替换为 $a_i + (a_i \bmod 10)$ 

问经过若干次变换后，该组数据能否全部相同

### 输入

第一行一个整数 $ t $ ( $ 1 \le t \le 10^4 $ ) 

每组测试数据第一行一个整数 $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) 

每组测试数据第二行 $ n $ 个整数 $ a_i $ ( $ 0 \le a_i \le 10^9 $ ) 
### 输出

对每组数据，若满足题意，输出 YES，反之输出 NO，对大小写不作要求。

## 题目描述

You are given an array of $ n $ integers $ a_1, a_2, \dots, a_n $

You can apply the following operation an arbitrary number of times:

- Select an index $ i $ ( $ 1 \le i \le n $ ) and replace the value of the element $ a_i $ with the value $ a_i + (a_i \bmod 10) $ , where $ a_i \bmod 10 $ is the remainder of the integer dividing $ a_i $ by $ 10 $ .

For a single index (value $ i $ ), this operation can be applied multiple times. If the operation is applied repeatedly to the same index, then the current value of $ a_i $ is taken into account each time. For example, if $ a_i=47 $ then after the first operation we get $ a_i=47+7=54 $ , and after the second operation we get $ a_i=54+4=58 $ .

Check if it is possible to make all array elements equal by applying multiple (possibly zero) operations.

For example, you have an array $ [6, 11] $ .

- Let's apply this operation to the first element of the array. Let's replace $ a_1 = 6 $ with $ a_1 + (a_1 \bmod 10) = 6 + (6 \bmod 10) = 6 + 6 = 12 $ . We get the array $ [12, 11] $ .
- Then apply this operation to the second element of the array. Let's replace $ a_2 = 11 $ with $ a_2 + (a_2 \bmod 10) = 11 + (11 \bmod 10) = 11 + 1 = 12 $ . We get the array $ [12, 12] $ .

Thus, by applying $ 2 $ operations, you can make all elements of an array equal.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. What follows is a description of each test case.

The first line of each test case contains one integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the size of the array.

The second line of each test case contains $ n $ integers $ a_i $ ( $ 0 \le a_i \le 10^9 $ ) — array elements.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case print:

- YES if it is possible to make all array elements equal;
- NO otherwise.

You can print YES and NO in any case (for example, the strings yEs, yes, Yes and YES will be recognized as a positive answer) .

## 样例 #1

### 样例输入 #1

```
10
2
6 11
3
2 18 22
5
5 10 5 10 5
4
1 2 4 8
2
4 5
3
93 96 102
2
40 6
2
50 30
2
22 44
2
1 5
```

### 样例输出 #1

```
Yes
No
Yes
Yes
No
Yes
No
No
Yes
No
```

## 提示

The first test case is clarified above.

In the second test case, it is impossible to make all array elements equal.

In the third test case, you need to apply this operation once to all elements equal to $ 5 $ .

In the fourth test case, you need to apply this operation to all elements until they become equal to $ 8 $ .

In the fifth test case, it is impossible to make all array elements equal.

In the sixth test case, you need to apply this operation to all elements until they become equal to $ 102 $ .

## 题解
我们经过我们的模拟之后，我们可以发现，我们每一次操作后，我们的数字变化是有规律的。
![[Pasted image 20240106221301.png]]
并且，可以想到，经过若干次变化后，我们的最后一定是能够都变成 $xx2$ 这一种形式的，而又因为我们一次转换，我们总共会加 20，所以，我们只需要按照下面的步骤进行：
1. 判断我们的原数组中是否有 5 或者 0，如果有，那么经过一次加之后，应该全部都相等，否则我们输出 `false`
2. 如果我们没有 5 或者 0，我们就对我们的所有数字同时膜上我们的 20，如果我们最后的摸完的结果是每个数都相同，那么我们就认为这一组是 `true`,否则，我们认为是 ``false``。
```cpp
//We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define For(i,j,k) for(int i=(j),i##_=(k);i<=i##_;i++)
#define N 200010
int n,a[N];
void calc(int &x){ while(x%10!=2 && x%10!=0) x+=x%10; }
void work(){
	cin>>n;
	For(i,1,n) cin>>a[i];
	int cnt=0;
	For(i,1,n) if(a[i]%5==0) cnt++;
	if(cnt>0 && cnt<n){
		cout<<"NO"<<endl;
		return ;
	}
	For(i,1,n) calc(a[i]);
	if(!cnt) For(i,1,n) a[i]%=20;
	For(i,2,n) if(a[i]!=a[i-1]){
		cout<<"NO"<<endl;
		return ;
	}
	cout<<"YES"<<endl;
}
signed main(){ios::sync_with_stdio(false),cin.tie(nullptr);
	int T;cin>>T;
	while(T--)work();
return 0;}
```