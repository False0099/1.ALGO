# OR in Matrix

## 题面翻译

```
A  B 都是 n*m 的矩阵，已知 B 矩阵是由 A 矩阵以某种规则生成，
B [i][j]是由 A 矩阵的第 i 行的所有元素和第 j 列的所有元素 或运算（or）得到
```
![](https://odzkskevi.qnssl.com/cabc1d1bbab97a93cdc521dabe1cee40)
```
给定 B 矩阵，求是否存在一个矩阵 A
1 <= n,m  <= 100
```

感谢@凉凉提供的翻译

## 题目描述

Let's define logical $ OR $ as an operation on two logical values (i. e. values that belong to the set $ {0,1} $ ) that is equal to $ 1 $ if either or both of the logical values is set to $ 1 $ , otherwise it is $ 0 $ . We can define logical $ OR $ of three or more logical values in the same manner:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF486B/406211f13f2a7c95dc14e24b4ae950d102f218cc.png) where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF486B/83308fae1dcded561005b623c7c1ed2fdfdfe04f.png) is equal to $ 1 $ if some $ a_{i}=1 $ , otherwise it is equal to $ 0 $ .

Nam has a matrix $ A $ consisting of $ m $ rows and $ n $ columns. The rows are numbered from $ 1 $ to $ m $ , columns are numbered from $ 1 $ to $ n $ . Element at row $ i $ ( $ 1<=i<=m $ ) and column $ j $ ( $ 1<=j<=n $ ) is denoted as $ A_{ij} $ . All elements of $ A $ are either 0 or 1. From matrix $ A $ , Nam creates another matrix $ B $ of the same size using formula:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF486B/157692e348a7a47f249e1d0e7ed60b12dc8cb619.png).

( $ B_{ij} $ is $ OR $ of all elements in row $ i $ and column $ j $ of matrix $ A $ )

Nam gives you matrix $ B $ and challenges you to guess matrix $ A $ . Although Nam is smart, he could probably make a mistake while calculating matrix $ B $ , since size of $ A $ can be large.

## 输入格式

The first line contains two integer $ m $ and $ n $ ( $ 1<=m, n<=100 $ ), number of rows and number of columns of matrices respectively.

The next $ m $ lines each contain $ n $ integers separated by spaces describing rows of matrix $ B $ (each element of $ B $ is either $ 0 $ or $ 1 $ ).

## 输出格式

In the first line, print "NO" if Nam has made a mistake when calculating $ B $ , otherwise print "YES". If the first line is "YES", then also print $ m $ rows consisting of $ n $ integers representing matrix $ A $ that can produce given matrix $ B $ . If there are several solutions print any one.

## 样例 #1

### 样例输入 #1

```
2 2
1 0
0 0
```

### 样例输出 #1

```
NO
```

## 样例 #2

### 样例输入 #2

```
2 3
1 1 1
1 1 1
```

### 样例输出 #2

```
YES
1 1 1
1 1 1
```

## 样例 #3

### 样例输入 #3

```
2 3
0 1 0
1 1 1
```

### 样例输出 #3

```
YES
0 0 0
0 1 0
```

## 题解
我们本题注意到，如果我们一个位置为 0，那么我们对应的行和列都必须全都为 0，因此我们可以下面的方法来构造并且同时检查：
1. 我们首先构造一个全为 1 的矩阵
2. 然后我们对于每一个为 0 的位置，构造对应的行和列都为 0
3. 最后对于我们为 1 的位置，我们检查对应位置上是否存在至少一个 1.

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=110;
int a[N][N];
int b[N][N];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin>>b[i][j];
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			a[i][j]=1;
		} 
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(b[i][j]==0){
				for(int k=0;k<m;k++){
					a[i][k]=0;
				}
				for(int k=0;k<n;k++){
					a[k][j]=0;
				}
			}
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(b[i][j]==1){
				bool flag=false;
				for(int k=0;k<m;k++){
					if(a[i][k]==1){
						flag=true;
						break;
					}
				}
				if(flag){
					continue;
				}
				for(int k=0;k<n;k++){
					if(a[k][j]==1){
						flag=true;
						break;
					}
				}
				if(flag){
					continue;
				}else{
					cout<<"NO"<<endl;
					exit(0);
				}
			}
		}
	}
	cout<<"YES"<<endl;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cout<<a[i][j]<<" ";
		}
		puts("");
	}
		
}
```