# 
## 题目描述
有两个长度相等，都只由小写字母构成的字符串A和B. 现在你有一把充满魔♂力的刷子。使用这把刷子，你可以把字符串中连续的一段区间刷♂成一个相同的字符，例如，对于字符串"vandarkholme"，把区间[3,6]刷成'd'，可以变成"vanddddholme"。现在你要用这把刷♂子把字符串A变成B，最少要刷多少次？

## 输入格式
多组数据，每组数据都有两行:  
第一行是字符串A.  
第二行是字符串B.  
字符串长度不超过100.


## 输出格式
在单独的一行中输出结果


## 样例 #1

### 样例输入 #1

```
zzzzzfzzzzz
abcdefedcba
abababababab
cdcdcdcdcdcd
```

### 样例输出 #1

```
6
7
```


## 题解
这一题与我们有一题叫做给空白串，要刷成制定类型，求最小次数有点类似，我们对于这一题，则要在那一题的基础上，加一些附加条件。
我们考虑从一个空串转换为目标串所需的最小步数，之后再比较A串和空串用哪一种能更快。最坏情况下，相当于空串
如果两者之前有相同部分，我们可以减少我们的操作次数，因此，我们就可以采用类似于KMP算法的思路，先计算一个“next”数组，然后根据next数组再去更新我们的结果。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	char A[110], B[110];
	int dp[110][110], ans[110];
	while(~scanf("%s%s", A, B)){
		memset(dp, 0, sizeof(dp));
		int len=strlen(A);
		for(int i=0; i<len; i++) dp[i][i]=1;
		for(int l=2; l<=len; l++){//枚举长度
			for(int i=0; i+l<=len; i++){//枚举起始位置
				int j=l+i-1;
				dp[i][j]=dp[i][j-1]+1;
				for(int k=i; k<j; k++){
					if(B[j]==B[k]){
						dp[i][j]=min(dp[i][j], dp[i][k-1]+dp[k][j-1]);
					}
				}
			}
		}
		for(int i=0; i<len; i++){
			ans[i]=dp[0][i];
			if(A[i]==B[i]){
				if(i==0) ans[i]=0;
				else ans[i]=ans[i-1];
			}
			for(int k=0; k<=i; k++){
				ans[i]=min(ans[i], ans[k]+dp[k+1][i]);
			}
		}
		printf("%d\n", ans[len-1]);
	}
	return 0;
}
```