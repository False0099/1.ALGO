## 题目
小红拿到了一棵树，每个节点上有一个字符，每个节点上的字符为'd'、'p'、'?'这三种。  
现在请你将所有'?'字符变成'd'或者'p'字符，需要满足任意两个相邻节点的字符不同。你能帮帮她吗？

## 输入：
第一行输入一个正整数 $n$，代表节点的数量。  
第二行输入一个长度为 $n$ 的、仅包含'?'、'd'和'p'的字符串。第 $i$ 个字符代表 $i$ 号节点的初始字符。  
接下来的 $n-1$ 行，每行输入两个正整数 $u,v$，代表节点 $u$ 和节点 $v$ 有一条边连接。  
  
$1\leq n \leq 10^5$

## 输出：
如果无解，请输出 -1。  
否则输出一个由'd'和'p'组成的字符串，第 $i$ 个字符代表最终 $i$ 号节点上的字符。

## 题解
我们本题的方法是通过我们的 BFS 进行我们的染色判定，因为我们要求我们的每一个节点的颜色都是不相同的，所以，我们一定是可以通过我们的 BFS 进行判定和我们的计算的。

于是，我们分别记录两个数组，red 和 blue 表示我们目前是 red 的点有哪些，目前是 blue 的点有哪些。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
string s=" ";
int h[N],ne[N<<1],e[N<<1],idx;
void add(int a,int b){
	e[idx]=b;
	ne[idx]=h[a];
	h[a]=idx++;
}

bool vis[N];
int main(){
	int n;
	cin>>n;
	string tmp;
	
	cin>>tmp;
	s+=tmp;
	queue<int> blue;//d
	queue<int> red;//p
	for(int i=1;i<=n;i++){
		if(s[i]=='d'){
			blue.push(i);
		}
	}
	
	memset(h,-1,sizeof h);
	for(int i=0;i<n-1;i++){
		int a,b;
		cin>>a>>b;
		add(a,b);
		add(b,a);
	}
	//先从D开始计算
	
	while(1){
		bool tag=false;
		while(blue.size()){
			int u=blue.front();
			blue.pop();
			tag=true;
			vis[u]=true;
			for(int i=h[u];i!=-1;i=ne[i]){
				int w=e[i];
				if(s[w]=='d'){
					cout<<-1<<endl;
					return 0;
				}else{
					if(vis[w]){
						continue;
					}
					s[w]='p';
					red.push(w);
				}
			}
		}
		while(red.size()){
			int u=red.front();
			red.pop();
			tag=true;
			vis[u]=true;
			for(int i=h[u];i!=-1;i=ne[i]){
				int w=e[i];
				if(s[w]=='p'){
					cout<<-1<<endl;
					return 0;
				}else{
					if(vis[w]){
						continue;
					}
					s[w]='d';
					blue.push(w);
				}
			}
		}
		if(tag==false){
			break;
		} 
	}
	for(int i=1;i<=n;i++){
		cout<<s[i];
	}
	
}
```