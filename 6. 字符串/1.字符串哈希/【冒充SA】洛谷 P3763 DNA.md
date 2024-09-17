# [TJOI 2017] DNA

## 题目描述

加里敦大学的生物研究所，发现了决定人喜不喜欢吃藕的基因序列 $S$,有这个序列的碱基序列就会表现出喜欢吃藕的性状，但是研究人员发现对碱基序列 $S$，任意修改其中不超过 $3$ 个碱基，依然能够表现出吃藕的性状。现在研究人员想知道这个基因在 DNA 链 $S_0$ 上的位置。所以你需要统计在一个表现出吃藕性状的人的 DNA 序列 $S_0$ 上，有多少个连续子串可能是该基因，即有多少个 $S_0$ 的连续子串修改小于等于三个字母能够变成 $S$。

## 输入格式

第一行有一个整数 $T$，表示有几组数据。

每组数据第一行一个长度不超过 $10^5$ 的碱基序列 $S_0$。

每组数据第二行一个长度不超过 $10^5$ 的吃藕基因序列 $S$。

## 输出格式

共 $T$ 行，第 $i$ 行表示第 $i$ 组数据中，在 $S_0$ 中有多少个与 $S$ 等长的连续子串可能是表现吃藕性状的碱基序列。

## 样例 #1

### 样例输入 #1

```
1
ATCGCCCTA
CTTCA
```

### 样例输出 #1

```
2
```

## 提示

对于 $20\%$ 的数据，$S_0,S$ 的长度不超过 $10^4$。

对于 $100\%$ 的数据，$S_0,S$ 的长度不超过 $10^5$，$0\lt T\leq 10$。

注：DNA 碱基序列只有 ATCG 四种字符。

## 题解
翻译：**我们给定一个模式串 S，给定一个格式串 T，允许失配不超过 3 次**，问我们匹配数是多少，我们这一题如果采用我们的暴力字符串哈希做法，我们的时间复杂度大概是一个 $n\log n$ 的复杂度，可以通过本题。

于是，我们就可以通过我们的字符串算法按照下面的流程来进行：
第一步：二分答案找到我们第一个不匹配的位置是在哪里，

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define ull unsigned long long 
const int N = 1e5 + 10;
const int b = 131;//base
//自然溢出，没有被卡
int T,ans,n,m;
char s[N],t[N];
ull p[N];
ull f[N],g[N];
ull h(ull *hash,int l,int r){//求子串的hash值
	return (hash[r]-hash[l-1]*p[r-l+1]);
}
int lcp(int x,int y,int r){
	int l = 1;
	while(l<=r){//二分
		int mid = l+r >>1;
		if(h(f,x,x+mid-1)==h(g,y,y+mid-1)) l=mid+1;
		else r = mid-1;
	}
	return l-1;//返回长度
}
bool check(int x){
	int y=1,r=x+m-1,l;//x是s0子串的开头，y是s子串的开头，r是s0子串的结尾
	for(int i=1;i<=3;i++){
		l = lcp(x,y,m-y+1);
		x += l+1;//跳过失配的位置
		y += l+1;
		if(y>m) return 1;
	}
	return h(f,x,r)==h(g,y,m);
}
int main(){
	scanf("%d",&T);
	p[0] = 1;
	for(int i=1;i<=N-10;i++){//预处理
		p[i] = p[i-1]*b;
	}
	while(T--){
		ans = 0;
		scanf("%s%s",s+1,t+1);
		n = strlen(s+1);
		m = strlen(t+1);
		if(n<m){
			puts("0");
			continue;
		}
		f[0] = g[0] = 0;
		for(int i=1;i<=n;i++){
			f[i] = (f[i-1]*b + s[i]);
		}
		for(int i=1;i<=m;i++){
			g[i] = (g[i-1]*b + t[i]);
		}
		for(int i=1;i<=n-m+1;i++){
			if(check(i)) ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}

```