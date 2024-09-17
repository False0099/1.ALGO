## 题目描述
输入整数n，输出一串数字，其中包含所有可能的n为数字序列，而且只包含一次，注意输出的这串数字，每个n为数字只能出现一个，例如，n=2,可能的两位数字有00,01,02,...,97,98,99,输出的序列就应该为001020304050607080911...。

## 输入格式
有多个测试，每个测试输入整数n


## 输出格式
对每个测试，输出一个序列，表示n位的序列


## 样例 #1

### 样例输入 #1

```

```

### 样例输出 #1

```

```

## 提示
我们把**每一个数字的前n-1位看成一个点**，一共有$10^{n-1}$个点，把n-1位数字后面加一个数字$0-9$，得到一组n位的数，看作一条边，共有$10^n$条边，这$10^n$条边对应了$10^n$组数字，
然后我们就建模成了欧拉回路问题:在$10^{n-1}$个点，$10^n$条边的图中，求一条字典序最小的欧拉回路。


## 题解


## 代码
```cpp
 #include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int num[N];
int st_edge[N],top_s;
char st_ans[N*10];
int top_a;
int m;
void no_dfs(int v){
	int edge;
	while(num[v]<10){
		edge=10*v+num[v];
		num[v]++;
		st_edge[tops++]=edge;
		v=edge%m;
	}
}
int main(){
	int n,edge;
	while(cin>>n&&n!=0){
		top_s=top_a=edge=0;
		m=1;
		for(int i=0;i<n-1;i++){
			m*=10;
		}
		for(int i=0;i<m;i++){
			num[i]=0;
		}
		no_dfs(0);
		while(top_s){
			edge=st_edge[--top_s];
			st_ans[top_a++]=edge%10+'0';
			no_dfs(edge/10);
		}
		for(int i=1;i<n;i++){
			cout<<"0";
		}
		while(top_a){
			printf("%c",st_ans[--top_a]);
		}
		puts("");
	}
}


```