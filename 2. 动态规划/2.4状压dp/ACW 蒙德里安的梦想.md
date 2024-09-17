# 
## 题目描述
![[Pasted image 20230802205011.png]]

## 输入格式
![[Pasted image 20230802205022.png]]


## 输出格式
![[Pasted image 20230802205028.png]]


## 样例 #1

### 样例输入 #1

```
1 2
1 3
1 4
2 2
2 3
2 4
2 11
4 11
0 0
```

### 样例输出 #1

```
1
0
1
2
3
5
144
51205
```

## 提示
本题的关键在于状态的设计，我们设计 $f[i][S]$ 表示我们第 i 行填充完成，并且给下一行留下了 S 状态的空格，完美解决了我们会给下一行留下信息的问题。（类似于状态机的思想）那么我们的每一次转移都可以逆向利用 S 的转移，最后我们只要输出 $f[n][0]$ 即可。



## 题解


## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=20;
const int M=1<<N;
int f[N][22];
bool st[M];
vector<int> states;
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=0;i<(1<<n);i++){
		int cnt=0;
		st[i]=true;
		for(int j=0;j<n;j++){
			if(i>>j&1){
				if(cnt&1) st[i]=false;
				cnt=0;
			}else{
				cnt++;
			}
		}
		if(cnt&1) st[i]=false;
	}
	memset(f,0,sizeof f);
	f[0][0]=1;
	for(int i=1;i<=m;i++){
		for(int j=0;j<1<<n;j++){
			for(int k=0;k<1<<n;k++){
				if((j&k)==0&&st[j|k]){
					f[i][j]+=f[i-1][k];
				}
			}
		}
	}
	cout<<f[m][0];
}
```