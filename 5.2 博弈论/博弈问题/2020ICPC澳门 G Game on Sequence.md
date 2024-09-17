Grammy is playing a game with her roommate Alice on a sequence $A$ with $n$ non-negative integers $A_1,A_2,\dots,A_n$. The rules of the game are described as follows.

1.  They play the game by moving the single token on the sequence, initially the token is at position $k$.
2.  Grammy takes the first move, and they take moves alternatively.
3.  In any move with the token at position $i$, the current player must move the token to the next position $j$ such that $j&gt;i$ and $A_j$ differs from $A_i$ on at most one bit in binary representation.
4.  The player who can't make any legal move loses the game.

They play this game many times and the sequence can be modified many times. Grammy wants to ask you for some initial states who will win the game if both play optimally.

**Input**

The first line of input contains 2 integers $n$ and $m$ ($1\leq n,m\leq 200\,000$), denoting the length of the sequence and the number of operations.

The second line contains $n$ integers $A_1,A_2,\dots,A_n$ ($0\leq A_i\leq 255$), denoting the sequence $A$.

The next $m$ lines each contains 2 integers $op$ ($1\leq op\leq 2$) and $k$, denoting each operation:

-   $op=1$ means a modification on the sequence. Grammy will append an integer $k$ ($0\leq k\leq 255$) at the end of the sequence so the sequence becomes $A_1, A_2, \dots, A_{N+1}$ where $N$ is the current length of the sequence before modification.
-   $op=2$ means a new game starts with the token at position $k$ ($1\leq k\leq N$), where $N$ is the current length of the sequence. You need to predict the winner of this game.

**Output**

For each operation with $op=2$, output one line containing "Grammy" if Grammy will win, or "Alice" if Alice will win when they play optimally.


## 题解
我们考虑这么一个问题，如果有一个数同时出现了两次，那么我们唯一会有影响的只会是我们出现的最后一个位置，只有这一个位置会影响我们的最终结果。

于是，我们可以考虑通过维护我们每一个数字最后出现的位置在哪里，然后我们再去预处理我们的某一个数字可以跳转到的数字的范围。

于是，我们的转移就有：
```
if(vis[a[i]]){
	return win[a[i]]
}
vis[a[i]]=1;
bool ok=0;
for(auto v:g[a[i]]){
	int p=last[v];
	if(p>1){
		ok|=!dfs(p);
	}
}
win[a[i]]=ok;
```

本质上还是根据我们的博弈图去连我们的边。