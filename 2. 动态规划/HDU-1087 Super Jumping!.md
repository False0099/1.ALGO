Nowadays, a kind of chess game called “Super Jumping! Jumping! Jumping!” is very popular in HDU. Maybe you are a good boy, and know little about this game, so I introduce it to you now.  
  

![](https://vj.csgrandeur.cn/c8a9412325bf5c44b0434934e74e0ee0?v=1696820624)

  
  
The game can be played by two or more than two players. It consists of a chessboard（棋盘）and some chessmen（棋子）, and all chessmen are marked by a positive integer or “start” or “end”. The player starts from start-point and must jumps into end-point finally. In the course of jumping, the player will visit the chessmen in the path, but everyone must jumps from one chessman to another absolutely bigger (you can assume start-point is a minimum and end-point is a maximum.). And all players cannot go backwards. One jumping can go from a chessman to next, also can go across many chessmen, and even you can straightly get to end-point from start-point. Of course you get zero point in this situation. A player is a winner if and only if he can get a bigger score according to his jumping solution. Note that your score comes from the sum of value on the chessmen in you jumping path.  
Your task is to output the maximum value according to the given chessmen list.  

## Input

Input contains multiple test cases. Each test case is described in a line as follow:  
N value_1 value_2 …value_N  
It is guarantied that N is not more than 1000 and all value_i are in the range of 32-int.  
A test case starting with 0 terminates the input and this test case is not to be processed.  

## Output

For each case, print the maximum according to rules, and one line one case.  

## Sample

|Inputcopy|Outputcopy|
|---|---|
|3 1 3 2<br>4 1 2 3 4<br>4 3 3 2 1<br>0|4<br>10<br>3|

## 题解
我们本题相当于要在我们的数量列中找到一个单调上升且和最大的序列，并给出我们的和。

我们这一题发现，我们在每一个位置的选择，只与我们上一个位置的选择有关，并且这个是否能够选择至于我们的值域有关，与我们的决策无关，于是我们就可以用我们的 LIS 思路来更新我们的这一个东西。

$dp[i]=max(dp[j])+a[i](a[j]\leq a[i])$

```cpp
```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#pragma comment(linker, "/STACK:102400000,102400000")
#define MAXN 1010
#define eps 1e-8
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
#define lb(x) x&-x
#define FUP(i, a, b) for(register int i = (a); i <= (b); i++)
#define FDOWN(i, a, b) for(register int i = (a); i >= (b); i--)
#define MP make_pair
using namespace std;
using namespace __gnu_pbds; ////priority_queue有冲突空间
typedef long long ll;
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
int dp[MAXN], num[MAXN];
int main()
{
	int n;
	num[0] = -100000;
	while(scanf("%d", &n) == 1) {
		memset(dp, 0, sizeof(dp));
		int ans = 0;
		if(n == 0) break;
		for(int i = 1; i <= n; i++) scanf("%d", &num[i]);
		for(int i = 1; i <= n; i++) {
			for(int j = 0; j < i; j++) {
				if(num[i] > num[j]) {
					dp[i] = max(dp[i], dp[j] + num[i]);
					ans = max(ans, dp[i]);
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
```