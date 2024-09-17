A dice is a small cube, with each side having a different number of spots on it, ranging from 1 to 6.

Each side in the dice has 4 adjacent sides that can be reached by rotating the dice (i.e. the current side) 90 degrees. The following picture can help you to conclude the adjacent sides for each side in the dice.

![](https://vj.csgrandeur.cn/4e06d3150d85acdddaf4d25db79131bb?v=1698254572)

In this problem, you are given a dice with the side containing 1 spot facing upwards, and a sum _n_, your task is to find the minimum number of required moves to reach the given sum.

On each move, you can rotate the dice 90 degrees to get one of the adjacent sides to the side that currently facing upwards, and add the value of the new side to your current sum. According to the previous picture, if the side that currently facing upwards contains 1 spot, then in one move you can move to one of sides that contain 2, 3, 4, or 5 spots.

Initially, your current sum is 0. Even though at the beginning the side that containing 1 spot is facing upwards, but its value will not be added to your sum from the beginning, which means that you must make at least one move to start adding values to your current sum.

Input

The first line contains an integer _T_ (1 ≤ _T_ ≤ 200), where _T_ is the number of test cases.

Then _T_ lines follow, each line contains an integer _n_ (1 ≤ _n_ ≤ 104), where _n_ is the required sum you need to reach.

Output

For each test case, print a single line containing the minimum number of required moves to reach the given sum. If there is no answer, print -1.

Sample 1

|Inputcopy|Outputcopy|
|---|---|
|2<br>5<br>10|1<br>2|

Note

In the first test case, you can rotate the dice 90 degrees one time, and make the side that contains 5 spots facing upwards, which make the current sum equal to 5. So, you need one move to reach sum equal to 5.

In the second test case, you can rotate the dice 90 degrees one time, and make the side that contains 4 spots facing upwards, which make the current sum equal to 4. Then rotate the dice another 90 degrees, and make the side that contains 6 spots facing upwards, which make the current sum equal to 10. So, you need two moves to reach sum equal to 10.

## 题解
题意：我们给定一个筛子某一个面朝上时的所有点数之和，然后问我们能够通过几次，从我们的初始状态，转移到我们的目标状态，输出我们的这一个次数。

我们这一题，如果我们直接用我们的 $f[x]$，那么我们就不能够直接得到我们的答案，因为我们不能确保我们的每一次转移都是合法的，比如说：我们不能直接从 $f[x-4]\to f[x]$,因为有可能在 $f[x-4]$ 是，我们一定是来自于我们的第 4 个位置。

（**我们计算新的位置，只能用我们已知格子的值，不可以用我们无关的值，类似于我们的马尔可夫过程**）

我们设计状态时，如果某个东西产生了后效性，我们就把它加进我们的状态表示内。我们于是本题就可以这几我们的状态 $f[x,top]$ 表示获得 x 分且目前 top 朝上的代价，那么我们的 $f[x,top]\to f[x+r,r]$,其中，$r\neq 7-top\cap r\neq top$

```cpp
#include <bits/stdc++.h>
using namespace std;
int dp[10200][10];
void solve(){
	memset(dp,0x3f,sizeof dp);
	dp[0][1]=0;
	for(int x=0;x<=10002;x++){
		for(int top=1;top<=6;top++){
			for(int r=1;r<=6;r++){
				if(top!=r&&top+r!=7){
					dp[x+r][r]=min(dp[x+r][r],dp[x][top]+1);
				}
			}
		}
	}
} 
int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}
```