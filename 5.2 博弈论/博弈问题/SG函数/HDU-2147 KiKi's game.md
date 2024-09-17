Recently kiki has nothing to do. While she is bored, an idea appears in his mind, she just playes the checkerboard game.The size of the chesserboard is n * m.First of all, a coin is placed in the top right corner(1,m). Each time one people can move the coin into the left, the underneath or the left-underneath blank space.The person who can't make a move will lose the game. kiki plays it with ZZ.The game always starts with kiki. If both play perfectly, who will win the game?  

Input

Input contains multiple test cases. Each line contains two integer n, m (0<n,m<=2000). The input is terminated when n=0 and m=0.  
  

Output

If kiki wins the game printf "Wonderful!", else "What a pity!".  

Sample

|Inputcopy|Outputcopy|
|---|---|
|5 3<br>5 4<br>6 6<br>0 0|What a pity!<br>Wonderful!<br>Wonderful!|

## 题解
我们这一题依然可以采用我们的人工打表法：
![[Pasted image 20231119112106.png]]
我们通过观察不难发现，我们的 $(x,y)=P$ 当且仅当我们 $(x-1,y)=(x,y-1)=(x-1,y-1)=N$ 时，我们的之后，我们就可以通过归纳法得到我们的结果。也就是说，如果我们的 n 和 m 都是奇数，那么我们先手必败，反之则是先手必胜。
```cpp
#include<iostream>
#include<stdio.h>
#include<cmath>
#include<string.h>
using namespace std;
const int N = 2e3+10;
const double PI = acos(-1.0);

signed main(void)
{
    int n,p,q,m;
    while(cin>>n>>m&&!cin.eof()){
        if(n==0&&m==0) break;
        if((n&1)&&(m&1)) cout<<"What a pity!"<<endl;
        else cout<<"Wonderful!"<<endl;
    }
}

```


