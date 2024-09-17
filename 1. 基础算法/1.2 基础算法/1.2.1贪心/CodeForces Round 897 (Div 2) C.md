#mex #博弈论
## 题目描述
salyg1n gave Alice a set S of n distinct integers s1,s2,…,sn (0≤si≤109). Alice decided to play a game with this set against Bob. The rules of the game are as follows:

- Players take turns, with Alice going first.
    
- In one move, Alice adds one number x (0≤x≤109) to the set S. The set S must not contain the number x at the time of the move.
- In one move, Bob removes one number y from the set S The set S must contain the number y at the time of the move. Additionally, the number y must be strictly smaller than the last number added by Alice.
- The game ends when Bob cannot make a move or after 2⋅n+1 moves (in which case Alice's move will be the last one).
- The result of the game is MEX†(S) (S at the end of the game).
- Alice aims to maximize the result, while Bob aims to minimize it.

Let R be the result when both players play optimally. In this problem, you play as Alice against the jury program playing as Bob. Your task is to implement a strategy for Alice such that the result of the game is always at least R.

†† MEX of a set of integers c1,c2,…,ck is defined as the smallest non-negative integer x which does not occur in the set c. For example, MEX({0,1,2,4})=3.

## 输入格式

The first line contains an integer t (1≤t≤105) - the number of test cases.

The interaction between your program and the jury program begins with reading an integer n (1≤n≤105) - the size of the set S before the start of the game.

Then, read one line - n distinct integers si (0≤s1<s2<…<sn≤109) - the set S given to Alice.

To make a move, output an integer x (0≤x≤109) - the number you want to add to the set S. S must not contain x at the time of the move. Then, read one integer y (−2≤y≤109).

- If 0≤y≤109 - Bob removes the number y from the set S. It's your turn!
- If y == −1 - the game is over. After this, proceed to handle the next test case or terminate the program if it was the last test case.
- Otherwise, y == −2. This means that you made an invalid query. Your program should immediately terminate to receive the verdict Wrong Answer. Otherwise, it may receive any other verdict.

## 样例 #1

### 样例输入 #1

```
3
5
1 2 3 5 7

7

5

-1

3
0 1 2

0

-1

3
5 7 57

-1
```

### 样例输出 #1

```
8

57

0

3

0

0
```


## 题解
本题我们采用贪心的思路来求出我们的最终结果，假设我们的目前的 $Mex$ 为 x，那么为了让我们的 Mex 尽可能的打，我们**只需要把 Mex 添加进来即可**，这就是我们的策略，而对于另一方，他**不管取哪个数，只要我们补充上这个数即可**，这么所我们最多也就进行 $2n-1$ 次，并且能最大化我们的 Mex。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve(){
	set<long long> st;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		ll x;
		cin>>x;
		st.insert(x);
	}
	ll x=0,y=0;
	while(st.count(x)){
		x++;
	}
	while(y>=0){
		cout<<x<<endl;
		cin>>y;
		x=y;
		if(y<=-1) return;
	}
}
int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
		cout.flush();
	}
}
```