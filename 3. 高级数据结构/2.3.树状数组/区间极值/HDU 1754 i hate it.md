 ## 题目描述
很多学校流行一种比较的习惯。老师们很喜欢询问，从某某到某某当中，分数最高的是多少。  这让很多学生很反感。  
  
不管你喜不喜欢，现在需要你做的是，就是按照老师的要求，写一个程序，模拟老师的询问。当然，老师有时候需要更新某位同学的成绩。

## 输入格式
本题目包含多组测试，请处理到文件结束。  
在每个测试的第一行，有两个正整数 N 和 M ( 0<N<=200000,0<M<5000 )，分别代表学生的数目和操作的数目。  
学生ID编号分别从1编到N。  
第二行包含N个整数，代表这N个学生的初始成绩，其中第i个数代表ID为i的学生的成绩。  
接下来有M行。每一行有一个字符 C (只取'Q'或'U') ，和两个正整数A，B。  
当C为'Q'的时候，表示这是一条询问操作，它询问ID从A到B(包括A,B)的学生当中，成绩最高的是多少。  
当C为'U'的时候，表示这是一条更新操作，要求把ID为A的学生的成绩更改为B。


## 输出格式

对于每一次询问操作，在一行里面输出最高成绩。

## 样例 #1

### 样例输入 #1

```
5 6
1 2 3 4 5
Q 1 5
U 3 6
Q 3 4
Q 4 5
U 2 9
Q 1 5

```

### 样例输出 #1

```
5
6
5
9
```

## 提示
Huge input,the C function scanf() will work better than cin
## 题解
对于**维护区间内的最大最小值**，我们使用树状数组显然是可行的，（虽然也可以用**线段树**）但具体实现中要注意，更新函数和求值函数的代码会有所不同，此处包含了某种分块的思想，在完整块内，用预处理好的，在块外，我们使用分散的碎数据。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define lowbit(x) (x&(-x))
void update(int x,int value){
	while(x<=n){
		tree[x]=value;
		for(int i=1;i<lowbit(x);i<<1){
			tree[x]=max(tree[x],tree[x-i]);//用子节点更新自己 
		}
		x+=lowbit(x);
	}
}
int num(int l,int r){
	int ans=0;
	while(l<=r){
		ans=max(ans,a[r]);
		r--;
		while(r-l>=lowbit(r)){
			ans=max(ans,tree[r]);
			r-=lowbit(r);
		}
	}
	return ans;
} 
int n,m,a[N];
int main(){
	while(~scanf("%d%d",&n,&m)){
		memset(tr,0,sizeof tr);
		for(int i=1;i<=n;i++){
			cin>>a[i];
			update(i,a[i]);
		}
		while(m--){
			char s[5];
			int A,B;
			cin>>s>>A>>B;
			if(s[0]=='Q'){
				cout<<query(A,B);
			}else{
				a[A]=B;
				update(A,B);
			}
		}
	}
}
```