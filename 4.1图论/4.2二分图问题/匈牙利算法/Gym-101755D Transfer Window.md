You play a football manager. There are _n_ football players in the game, and _k_ of them — _a_1, _a_2, ..., _a__k_ — are currently playing in your team. You want players _b_1, _b_2, ..., _b__k_ to play in your team. To achieve that, you can suggest other teams to exchange one of your players to their player.

For each ordered pair of distinct players (_x_, _y_) it is known whether or not a team controlled by AI would accept to exchange your player _x_ to their player _y_. Determine whether it is possible to collect a team consisting of football players _b_1, _b_2, ..., _b__k_ and if it is, output the order of exchanges to achieve it.

Input

The first line contains two integers _n_ and _k_ (1 ≤ _n_ ≤ 300, 1 ≤ _k_ ≤ _n_) — the total number of football players in the game and the number of football players in your team.

The second line contains _k_ distinct integers _a__i_ (1 ≤ _a__i_ ≤ _n_) — the players currently playing in your team.

The third line contains _k_ distinct integers _b__i_ (1 ≤ _b__i_ ≤ _n_) — the players you want to see in your team.

Each of the next _n_ lines contains _n_ characters. Character in _i_-th line and _j_-th column equals «1», if the team controlled by AI would accept to exchange your player _i_ to their player _j_, and «0», if it wouldn't. Characters on the main diagonal are equal to zero.

Output

In the first line output «YES», if it's possible to make a team of players _b_1, _b_2,  ..., _b__k_, and «NO», if it's not.

In the case of the «YES» answer, in the second line output a single integer _q_ (0 ≤ _q_ ≤ _n_·_n_) — the number of exchanges, and then _q_ lines — the sequence of exchanges. Each of these _q_ lines must contain two distinct integers _x__j_ and _y__j_ (1 ≤ _x__j_ ≤ _n_, 1 ≤ _y__j_ ≤ _n_) — the number of player from your team you want to exchange and the number of player from another team you want to get for him. Please note that after _j_-th exchange player _y__j_ becomes a player of your team and player _x__j_ leaves your team.

If there are several sequences of exchanges leading to the desired result, output any of them. Also note that it's not required to minimize the number of exchanges, it's just enough if it doesn't exceed _n_·_n_.

Sample 1

|Inputcopy|Outputcopy|
|---|---|
|5 2<br>1 2<br>4 5<br>00100<br>00100<br>00011<br>00000<br>00000|YES<br>4<br>1 3<br>3 4<br>2 3<br>3 5|

Sample 2

|Inputcopy|Outputcopy|
|---|---|
|3 2<br>1 2<br>2 3<br>000<br>001<br>010|NO|

## 题解
本题要求我们进行一个球员交换的操作，我们于是可以通过我们的二分图，来将我们的球员之间一一建图，最后我们要看我们能否完成我们的交换任务，就是看我们最后的图中是否 K 个人恰好有 K 个匹配即可。同时，我们还要用我们的 floyd 来预处理我们传递闭包，来知道我们一个人通过一系列操作最后能换到的可能人选。然后我们的左侧是我们的不想要的球员，右侧是我们想要的，检查我们是否是满匹配即可。
```cpp
void floyd(){
	for(int i=0;i<k;i++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				f[i][j]|=f[i][k]&f[k][j]
			}
		}
	}
}
int main(){
	floyd();
	for(int i=0;i<n;i++){
		if(want[i]&&have[i]){
			continue;
		}else{
			for(auto u:g){
				build(i,u);
			}
		}
	}
	
}
```