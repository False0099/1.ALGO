大学英语四级考试就要来临了，你是不是在紧张的复习？也许紧张得连短学期的 ACM 都没工夫练习了，反正我知道的 Kiki 和 Cici 都是如此。当然，作为在考场浸润了十几载的当代大学生，Kiki 和 Cici 更懂得考前的放松，所谓“张弛有道”就是这个意思。这不，Kiki 和 Cici 在每天晚上休息之前都要玩一会儿扑克牌以放松神经。  
“升级”？“双扣”？“红五”？还是“斗地主”？  
当然都不是！那多俗啊~  
作为计算机学院的学生，Kiki和Cici打牌的时候可没忘记专业，她们打牌的规则是这样的：  
1、  总共n张牌;  
2、  双方轮流抓牌；  
3、  每人每次抓牌的个数只能是2的幂次（即：1，2，4，8，16…）  
4、  抓完牌，胜负结果也出来了：最后抓完牌的人为胜者；  
假设Kiki和Cici都是足够聪明（其实不用假设，哪有不聪明的学生~），并且每次都是Kiki先抓牌，请问谁能赢呢？  
当然，打牌无论谁赢都问题不大，重要的是马上到来的CET-4能有好的状态。  
  
Good luck in CET-4 everybody!  

Input

输入数据包含多个测试用例，每个测试用例占一行，包含一个整数n（1<=n<=1000）。

Output

如果Kiki能赢的话，请输出“Kiki”，否则请输出“Cici”，每个实例的输出占一行。  

Sample

|Inputcopy|Outputcopy|
|---|---|
|1<br>3|Kiki<br>Cici|

## 题解
我们这一题可以考虑用我们的 SG 函数打表找规律来进行计算，我们发现，我们所有 3 的倍数的点都是 P 点，其余的都是我们的 N 点，

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const ll MAXN = 1e18 + 7;
const int maxn = 1200;
int SG[maxn];
int vis[20];//2^20
int a[20];
int n;
void guandy(int x){
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=11;i++){
		if(x-a[i]>=0){
			vis[SG[x-a[i]]]=i;
		}
	}
	for(int i=0;i<=11;i++){
		if(!vis[i]){
			SG[x]=i;
			break;
		}
	}
}
void init(){
	a[1]=1;
	for(int i=2;i<=11;i++){
		a[i]=a[i-1]*2;
	}
	SG[0]=1;SG[1]=1;SG[2]=1;
}
int main()
{
    ios::sync_with_stdio(false);
    init();
    for(int i=3;i<=1000;i++){
    	guandy(i);
    }
    while(cin>>n){
    	if(SG[n])
    		cout<<"Kiki"<<endl;
    	else
    		cout<<"Cici"<<endl;
    }
    return 0;
}
```