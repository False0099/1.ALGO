Ibraheem and Husam are playing a game with group of boxes, lined next to each other on a straight line, such that each box contains a card with some value written on it. Ibraheem and Husam already know the values of all cards before the game starts.

Ibraheem and Husam take turns to play the game, Ibraheem starts first. In each turn, a player can take one box from either ends of the line, add the value of the card inside this box to his score, then remove this box from the line.

Knowing that both players play optimally, your task is to calculate the value _x_ - _y_, such that _x_ is Ibraheem's score at the end of the game, and _y_ is Husam's score at the end of the game.

## Input

The first line contains an integer _T_ (1 ≤ _T_ ≤ 500), where _T_ is the number of test cases.

The first line of each test case contains an integer _n_ (1 ≤ _n_ ≤ 103), where _n_ is the number of boxes in the line.

The second line of each test case contains _n_ integers _a_1, _a_2, ..., _a__n_ ( - 103 ≤ _a__i_ ≤ 103), giving the values of the cards inside the boxes.

## Output

For each test case, print a single line containing its answer.

Sample 1

|Inputcopy|Outputcopy|
|---|---|
|5<br>4<br>3 1 100 5<br>1<br>1000<br>4<br>-1 100 4 -5<br>1<br>-4<br>1<br>0|97<br>1000<br>92<br>-4<br>0|

## 题解
我们这一题就是问我们在最优化两个人的操作得情况下，我们能分别获得的最大值是多少。在这里，我们其实只需要计算我们先手能够获得的最大值是多少就可以了。这里，我们采用我们的 dp，
我们设 $a[l][r]$ 表示我们在原始序列区间 $[l,r]$ 进行游戏，先手能够取得的分数, $b[l][r]$ 为我们后手能够获得的分数。那么此时我们就可以转移为：

$a[l][r]=max(w_{l}+b[l+1][r],w_{r}+b[l][r-1])$
$b[l][r]=sum(l,r)-a[l][r]$

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,w[1005];
void input(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>w[i];
	}
	
}
bool vis[N][1000];
int mem[1005][1005];
int pre[1005];
void init(){
	memset(vis,0,sizeof vis);
	memset(mem,0,sizeof mem);
	for(int i=1;i<=n;i++){
		pre[i]=pre[i-1]+w[i];
	}
}
int getsum(int l,int r){
	return pre[r]-pre[l-1];
}
int A(int l,int r){
	if(l==r){
		return w[l];
	}
	if(vis[l][r]){
		return mem[l][r];
	}
	int res=max(w[l],b(l+1,r),w[r]+b(l,r-1));
	vis[l][r]=1;
	mem[l][r]=res;
	return res;
}
int B(int l,int r){
	return getsum(l,r)-a(l,r);
}

int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}
```