# 知识点
  ## [[AC自动机]]
# 题目
 给定 n个长度不超过 50的由小写英文字母组成的单词，以及一篇长为 m的文章。

请问，其中有多少个单词在文章中出现了。

注意：每个单词不论在文章中出现多少次，仅累计 1次。

#### 输入格式
第一行包含整数 T，表示共有 T组测试数据。

对于每组数据，第一行一个整数 n，接下去 n行表示 n个单词，最后一行输入一个字符串，表示文章。

#### 输出格式
对于每组数据，输出一个占一行的整数，表示有多少个单词在文章中出现。

#### 数据范围
$1≤n≤10^4$

$1≤m≤10^6$
#### 输入样例 ：
1
5
She
He
Say
Shr
Her
Yasherhs
#### 输出样例 ：
3

# 思路
***建议直接背诵 AC 自动机模板

# AC 代码
```cpp
#include <iostream>
#include <queue>
using namespace std;
int tr[N][26],idx;
int cnt[N];
void insert(string s){
	int p=0;
	for(int i=0;s[i];i++){
		if(!tr[p][i]) tr[p][i]=++idx;
		p=tr[p][i];
	}
	cnt[p]++;
}
void build(){
	queue<int> q;
	for(int i=0;i<26;i++){
		if(tr[0][i]) q.push(tr[0][i]);
	}
	while(!q.empty()){
		int t=q.front();
		q.pop();
		
		for(int i=0;i<26;i++){
			int p=tr[t][i];
			if(!p) tr[t][i]=tr[ne[t]][i];
			else{
				ne[p]=tr[ne[u]][i];
				q.push(p);
			}
		}
	}
}
void search(string s){
	for(int k=0,i=0;s[k];k++){
		i=tr[i][k-'a'];
		for(int j=i;j&&~cnt[j];j=ne[j]){
			ans+=cnt[j];
			cnt[j]=-1;
		}
	}
}
```
# 备注
