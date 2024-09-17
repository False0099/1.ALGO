# 
## 题目描述
Victor loves to play with string. He thinks a string is charming as the string is a palindromic string.  
  
Victor wants to play n times. Each time he will do one of following four operations.  
  
Operation 1 : add a char c to the beginning of the string.  
  
Operation 2 : add a char c to the end of the string.  
  
Operation 3 : ask the number of different charming substrings.  
  
Operation 4 : ask the number of charming substrings, the same substrings which starts in different location has to be counted.  
  
At the beginning, Victor has an empty string.

## 输入格式
The input contains several test cases, at most 55 cases.  
  
In each case, the first line has one integer n means the number of operations.  
  
The first number of next n line is the integer op, meaning the type of operation. If op=1 or 2, there will be a lowercase English letters followed.  
  
1≤n≤100000.


## 输出格式

For each query operation(operation 3 or 4), print the correct answer.

## 样例 #1

### 样例输入 #1

```
6
1 a
1 b
2 a
2 c
3
4
8
1 a
2 a
2 a
1 a
3
1 b
3
4
```

### 样例输出 #1

```
4
5
4
5
11
```

## 提示
对于这一题，我们就是需要回文串树的末班提，即在字符串的首尾扩展新字符，统计回文串的数量。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3e5+10;
int s[N];
struct node{
	int len,fail,son[26],siz;
	void init(int _len){
		memset(son,0,sizeof son);
		fail=siz=0;
		len=_len;
	}
}tree[N];
ll num,last[2],ans,l,r;
void init(){
	last[0]=last[1]=0;
	ans=0;
	num=1;
	l=1e5+8;
	r=1e5+7;
	tree[0].init(0);
	memset(s,-1,sizeof s);
	tree[1].init(-1);
	tree[0].fail=1;
}
int getfail(int p,int d){
	if(d){
		while(s[r-tree[p].len-1]!=s[r]){
			p=tree[p].fail;
		}
	}else{
		while(s[l+tree[p].len+1]!=s[l]){
			p=tree[p].fail;
		}
	}
	return p;
}
void insert(int x,int d){
	if(d) s[++r]=x;
	else s[--l]=x;
	int father=getfail(last[d],d);
	int now=tree[father].son[x];
	if(!now){
		now=++num;
		tree[now].init(tree[father].len+2);
		tree[now].fail=tree[getfail(tree[father].fail,d)].son[x];
		tree[now].siz=tree[tree[now].fail].siz+1;
		tree[father].son[x]=now; 
	}
	last[d]=now;
	if(r-l+1==tree[now].len) last[d^1]=now;
	ans+=tree[now].siz;
}
int main(){
	int op,n;
	while(scanf("%d",&n)!=EOF){
		init();
		while(n--){
			char c;
			cin>>op;
			if(op==1){
				cin>>c,insert(c-'a',0);
			}
			if(op==2){
				cin>>c,insert(c-'a',1);
			}
			if(op==3){
				cout<<num-1<<endl;
			}
			if(op==4){
				cout<<ans<<endl;
			}
		}
	}
	return 0;
}
```