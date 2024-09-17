### Problem Statement

Let us call a positive integer $n$ that satisfies the following condition an **arithmetic number**.

-   Let $d_i$ be the $i$ \-th digit of $n$ from the top (when $n$ is written in base $10$ without unnecessary leading zeros.) Then, $(d_2-d_1)=(d_3-d_2)=\dots=(d_k-d_{k-1})$ holds, where $k$ is the number of digits in $n$.
    -   This condition can be rephrased into the sequence $(d_1,d_2,\dots,d_k)$ being arithmetic.
    -   If $n$ is a $1$ \-digit integer, it is assumed to be an arithmetic number.

For example, $234,369,86420,17,95,8,11,777$ are arithmetic numbers, while $751,919,2022,246810,2356$ are not.

Find the smallest arithmetic number not less than $X$.

### Constraints

-   $X$ is an integer between $1$ and $10^{17}$ (inclusive).

### Input

Input is given from Standard Input in the following format:


$X$


### Output

Print the answer as an integer.


## 题解
我们本题的思路是：通过我们的打表，首先我们注意到，我们满足题目中描述的数字的范围是相对较少的，再最多的情况下，也只会有：$\sum_{k=1}^9k!$ 种可能的数字，最多也不会超过 50 万次计算，完全是我们可以接受的范围，因此，我们可以完全可以考虑枚举我们所有可能的数字，然后再去用 set 记录这些数字，最后用 lower_bound 计算即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[100005];
int num;
void first(int i){
	a[++num]=i;
	for(int j=1;j<=9;j++){
		long long link=i;
		for(int k=i+j;k<=9;k+=j) link=link*10+k,a[++num]=link;
	}
}//上升
void second(int i){
	for(int j=1;j<=9;j++){
		long long link=i;
		for(int k=i-j;k>=0;k-=j) link=link*10+k,a[++num]=link;
	}
}//下降
int main(){
	long long n;
	scanf("%lld",&n);
	for(int i=1;i<=9;i++) first(i);
	for(int i=9;i>=1;i--) second(i);//进行存储
	sort(a+1,a+1+num);//排序
	printf("%lld\n",*lower_bound(a+1,a+1+num,n));//STL真香
	return 0;
}
```
