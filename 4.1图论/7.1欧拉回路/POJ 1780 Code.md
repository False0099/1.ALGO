## 题目描述
输入整数 n，输出一串数字，其中包含所有可能的 n 为数字序列，而且只包含一次，注意输出的这串数字，每个 n 位数字只能出现一个，例如，n=2,可能的两位数字有00,01,02,...,97,98,99,输出的序列就应该为001020304050607080911...。

## 输入格式
有多个测试，每个测试输入整数n


## 输出格式
对每个测试，输出一个序列，表示n位的序列



## 提示
我们这一题就可以等价于**找一条回路，使得我们每个点都经历了一遍**。这一题的我们的边，我们可以遵循下面的规则：我们把**每一个数字的前 n-1位看成一个点**，一共有 $10^{n-1}$ 个点，把 n-1位数字后面加一个数字 $0-9$，得到一组 n 位的数，看作一条边，共有 $10^n$ 条边，这 $10^n$ 条边对应了 $10^n$ 组数字，显然，每个点的入度和出度都为10，则一定存在欧拉回路。


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
			m*=10;//十条边
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