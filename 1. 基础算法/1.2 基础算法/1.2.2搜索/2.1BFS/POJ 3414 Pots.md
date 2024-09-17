You are given two pots, having the volume of **A** and **B** liters respectively. The following operations can be performed:

1. FILL(i)        fill the pot **i** (1 ≤ **i** ≤ 2) from the tap;
2. DROP(i)      empty the pot **i** to the drain;
3. POUR(i,j)    pour from pot **i** to pot **j**; after this operation either the pot **j** is full (and there may be some water left in the pot **i**), or the pot **i** is empty (and all its contents have been moved to the pot **j**).

Write a program to find the shortest possible sequence of these operations that will yield exactly **C** liters of water in one of the pots.

Input

On the first and only line are the numbers **A**, **B**, and **C**. These are all integers in the range from 1 to 100 and **C**≤max(**A**,**B**).

Output

The first line of the output must contain the length of the sequence of operations **K**. The following **K** lines must each describe one operation. If there are several sequences of minimal length, output any one of them. If the desired result can’t be achieved, the first and only line of the file must contain the word ‘**impossible**’.

Sample

|Inputcopy|Outputcopy|
|---|---|
|3 5 4|6<br>FILL(2)<br>POUR(2,1)<br>DROP(1)<br>POUR(2,1)<br>FILL(2)<br>POUR(2,1)|
## 翻译
我们由两口锅，一口锅有体积 A，另一口有体积 B，我们可以有下面三种操作：
A：把一口锅填满
B：把一口锅挖空
C：把我们的 A 中的水倒进 B 中或把 B 中的水倒入 A 中
问，是否存在一个**最短**操作序列，使得我们能够把我们的某一口锅的体积证号为 C。
## 题解
本题是一个多借口（两个以上的桶），我们对于这种多借口的，就需要利用我们的数据结构，例如 pair 来优化我们的操作。


我们这一题仍然存在一个 BFS 做法：
1. 我们把我们的初始状态点对放入到我们的队列中
2. 每次更新，从我们的队列中取出一个点，然后判断我们的点是否在之前出现过，如果没有出现过，我们就要把这个点放入我们的队列中，并且我们还要判断是否达到 C 了，如果有，我们直接推出即可

```cpp
#include<bits/stdc++.h>
using namespace std;
int v1 , v2;		//瓶子容量
int c;		//目标水量
int k1 , k2;		//瓶子内含水量
 
class pot{		//BFS*-对于多入口的复杂BFS，需要类/结构体来储存入口 
	public:
		int x , y;	//当前两个瓶子的剩余水量(状态) 
		int pos;		//记录当前状态在操作链p中的下标
		int step;		//当前步数 		 
};
class process{		//记录操作链 
	public:
		int pre;		//记录上一个操纵的下标 
		string op;		//记录操作 
};
string combAB(int a,int b)	//把整数a、b整合为 "a,b"  的字符串形式(不包括引号)，用于标记状态
{
	string s;
	{	ostringstream oss;
		oss<<a;
		oss<<',';
		oss<<b; 
		s=oss.str();
	}
	return s;
}
//BFS-值位移函数
void Fill(int i){
	switch(i){
		case 1:	k1 = v1;	return;
		case 2: k2 = v2;	return;
	}
} 
void Drop(int i){
	switch(i){
		case 1: k1 = 0;		return;
		case 2: k2 = 0;		return;
	}
}
void Pour(int i, int j){
	switch(i){
		case 1:if(k1+k2<=v2){
				    k2 += k1;	
				    k1 = 0;	
			   }
			   else{
			   		k1 = k1+k2-v2;
			   		k2 = v2;
			   }return;
		case 2:if(k2+k1<=v1){
				    k1 += k2;	
					k2 = 0; 	
			   }
			   else{
			   		k2 = k1+k2-v1;
			   		k1 = v1;
			   }return;
	}
}
string dev(int k, int i, int j){
	switch(k){
		case 0: Fill(i);	return "Fill(1)";
		case 1: Fill(j);	return "Fill(2)";
		case 2: Drop(i);	return "Drop(1)";
		case 3: Drop(j);	return "Drop(2)";
		case 4: Pour(i,j);	return "Pour(1,2)";
		case 5: Pour(j,i);	return "Pour(2,1)";
	}
}
void BFS(){
	queue<pot> q;		//BFS-核心队列  
	put head , next;
	process p[1000];
	map<string,bool> vis;		//BFS-访问标记
	head.x = 0;
	head.y = 0;
	head.pos = 0;
	q.push(head);
	int ptr = 0;		//记录操作下标： 
	while(!q.empty()){
		head = q.front();
		q.pop();
		for(int k=0;k<6;k++){
			k1 = head.x;
		    k2 = head.y;             
			string st = dev(k,1,2);			//临时储存操作 
			string str = combAB(k1,k2);
			if(vis[str])	continue;
			next.pos = ptr++;
			p[next.pos].pre = head.pos;
			p[next.pos].op = st;		//未被跳过，入列 
			next.x = k1;
			next.y = k2;
			next.step = head.step + 1;
			vis[str] = true;
			q.push(next);
			if(next.x==c || next.y==c){
				cout<<next.step<<endl;		//输出步数 
				stack<string> s;		//用栈完成倒序输出 
				int k = next.pos;
				for(int i=0;i<next.step;i++){
					s.push(p[k].op);
					k = p[k].pre;
				}
				while(!s.empty()){
					cout<<s.top()<<endl;
					s.pop();
				}
				return;
			}
		}
	}
	cout<<"impossible"<<endl;
}
int main(){
	cin>>v1>>v2>>c;
	BFS();
} 
```