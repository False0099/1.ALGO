# Roman Digits

## 题面翻译

我们在研究罗马数字。罗马数字只有 $4$ 个字符，$\tt{I,V,X,L}$ 分别代表 $1,5,10,50$。一个罗马数字的值为该数字包含的字符代表数字的和，而与字符的顺序无关。例如 $\tt{XXXV}=35$，$\tt{IXI}=12$。

现在求问一个长度为 $n$ 的罗马数字可以有多少种不同的值。($n \leq 10^9$)。

感谢@litble 提供翻译。

## 题目描述

Let's introduce a number system which is based on a roman digits. There are digits I, V, X, L which correspond to the numbers $ 1 $ , $ 5 $ , $ 10 $ and $ 50 $ respectively. The use of other roman digits is not allowed.

Numbers in this system are written as a sequence of one or more digits. We define the value of the sequence simply as the sum of digits in it.

For example, the number XXXV evaluates to $ 35 $ and the number IXI — to $ 12 $ .

Pay attention to the difference to the traditional roman system — in our system any sequence of digits is valid, moreover the order of digits doesn't matter, for example IX means $ 11 $ , not $ 9 $ .

One can notice that this system is ambiguous, and some numbers can be written in many different ways. Your goal is to determine how many distinct integers can be represented by exactly $ n $ roman digits I, V, X, L.

## 输入格式

The only line of the input file contains a single integer $ n $ ( $ 1 \le n \le 10^9 $ ) — the number of roman digits to use.

## 输出格式

Output a single integer — the number of distinct integers which can be represented using $ n $ roman digits exactly.

## 样例 #1

### 样例输入 #1

```
1
```

### 样例输出 #1

```
4
```

## 样例 #2

### 样例输入 #2

```
2
```

### 样例输出 #2

```
10
```

## 样例 #3

### 样例输入 #3

```
10
```

### 样例输出 #3

```
244
```

## 提示

In the first sample there are exactly $ 4 $ integers which can be represented — I, V, X and L.

In the second sample it is possible to represent integers $ 2 $ (II), $ 6 $ (VI), $ 10 $ (VV), $ 11 $ (XI), $ 15 $ (XV), $ 20 $ (XX), $ 51 $ (IL), $ 55 $ (VL), $ 60 $ (XL) and $ 100 $ (LL).

## 题解
我们这一题的思路是采用打表的方法来找到我们的规律，我们这里采用的打表代码如下所示：
```cpp
# include <bits/stdc++.h>
using namespace std;

int n;

int solve(int x) {
	// 暴力出奇迹 枚举
	map <int, bool> ojbk; //map时间换空间，妈妈再也不用担心我MLE啦！
	int num;
	for (int i = 0; i <= x; i++) {
		for (int j = 0; j <= x - i; j++) {
			for (int k = 0; k <= x - i - j; k++) {
				int qwq = i + j * 5 + k * 10 + (x - i - j - k) * 50;
				if (!ojbk[qwq]) ojbk[qwq] = 1, num++;
			}
		}
	}
	return num;
}

signed main() {
	scanf("%d", &n);
	printf("%d\n", solve(n));
	return 0;
} 
```

之后，我们再根据我们打表得到的结果去进行我们的找规律即可。

```cpp
#include <bits/stdc++.h>
using namespace std ;
long long ans,n ;
long long dfs(int x){
    map<long long,int> a ;
    a.clear() ;
    long long sum=0 ;
    for (int i=0;i<=x;i++)
    for (int j=0;i+j<=x;j++)
    for (int k=0;i+j+k<=x;k++){
        long long t=i+j*5+k*10+(x-i-j-k)*50 ;
        if (!a[t]){
            a[t]=1 ;
            sum++ ;
        }
    } 
    return sum ;
}
int main(){
    scanf("%lld",&n) ;
    if (n<=20) ans=dfs(n) ;
    else ans=dfs(20)+(n-20)*49;
    printf("%lld\n",ans) ;
}
```