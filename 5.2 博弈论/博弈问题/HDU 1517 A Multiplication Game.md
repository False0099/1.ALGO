Stan and Ollie play the game of multiplication by multiplying an integer p by one of the numbers 2 to 9. Stan always starts with p = 1, does his multiplication, then Ollie multiplies the number, then Stan and so on. Before a game starts, they draw an integer 1 < n < 4294967295 and the winner is who first reaches p >= n.  

Input

Each line of input contains one integer number n.  

Output

For each line of input output one line either  
  
Stan wins.  
  
or  
  
Ollie wins.  
  
assuming that both of them play perfectly.  

Sample

|Inputcopy|Outputcopy|
|---|---|
|162<br>17<br>34012226|Stan wins.<br>Ollie wins.<br>Stan wins.|

## 题解
我们这一题可以用我们的 SG 函数进行一个简单的打表
```cpp
int dp[u];
bool dfs(int u){
	if(u>=n){
		dp[u]=true;
	}
	if(dp[u]){
		return dp[u];
	}
	for(int i=2;i<=9;i++){
		dp[u]|=dfs(u*i);
	}
}
```

然后我们就可以有下面的规律：如果我们 $2\leq n\leq 9$,那么我们的 S 必胜

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main()
{
	int winner;
	unsigned int n;
	while(~scanf("%ud",&n))
	{
		while(n!=1)
		{
			if(n!=1)  winner=0,n=ceil((double)n/9);
			if(n!=1)  winner=1,n=ceil((double)n/2);
		}
		puts(winner?"Ollie wins.":"Stan wins.");
	}
	return 0;
}

```