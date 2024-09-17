# Number Game

## 题面翻译

一共有 $t$ 组数据，每次有一个序列 $a$ ，两个人对它进行操作，一共进行 $k$ 个回合。在第 $i$ 个回合中，第一个人必须在序列 $a$ 不为空的情况下删除序列 $a$ 任意一个**小于等于** $k-i+1$ 的数。接着，第二个人必须在序列 $a$ 不为空的情况下将 $k-i+1$ 加到序列 $a$ 中任意一个数上。当 $k$ 个回合结束时，如果第一个人每一回合都操作过了，第一个人就赢了，否则就输了。求保证让第一个人赢的情况下 $k$ 最大是多少。

## 题目描述

Alice and Bob are playing a game. They have an array of positive integers $ a $ of size $ n $ .

Before starting the game, Alice chooses an integer $ k \ge 0 $ . The game lasts for $ k $ stages, the stages are numbered from $ 1 $ to $ k $ . During the $ i $ -th stage, Alice must remove an element from the array that is less than or equal to $ k - i + 1 $ . After that, if the array is not empty, Bob must add $ k - i + 1 $ to an arbitrary element of the array. Note that both Alice's move and Bob's move are two parts of the same stage of the game. If Alice can't delete an element during some stage, she loses. If the $ k $ -th stage ends and Alice hasn't lost yet, she wins.

Your task is to determine the maximum value of $ k $ such that Alice can win if both players play optimally. Bob plays against Alice, so he tries to make her lose the game, if it's possible.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 100 $ ) — the size of the array $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ).

## 输出格式

For each test case, print one integer — the maximum value of $ k $ such that Alice can win if both players play optimally.

## 样例 #1

### 样例输入 #1

```
4
3
1 1 2
4
4 4 4 4
1
1
5
1 3 2 1 1
```

### 样例输出 #1

```
2
0
1
3
```


## 题解
我们本题考虑寻找我们的最优策略，我们如果是找数方，那么我们的最佳策略一定是先去找到我们的最大的可选的数字，然后选上，如果我们是弹数方，我们一定是先去弹走我们的最低位的数字，然后我们就可以用我们的 **multiset 来模拟**我们的这个过程。**对于我们的答案，我们就可以通过我们的枚举答案**，并对答案进行验证。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
int a[105];
multiset<int> s;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		int ans=0;
		for(int k=1;k<=n;k++)
		{
			s.clear();
			for(int i=1;i<=n;i++) s.insert(a[i]);
			int f=0;
			for(int i=1;i<=k;i++)
			{
				while(s.upper_bound(k-i+1)!=s.end()) s.erase(*s.upper_bound(k-i+1));
				if(!s.size())
				{
					f=1;
					break;
				}
				multiset<int>::iterator it=s.upper_bound(k-i+1);
				it--;
				s.erase(it);
				if(!s.empty())
				{
					int x=*s.begin();
					s.erase(s.begin());
				}
			}
			if(!f) ans=k;
		}
		cout<<ans<<'\n';
	}
}
```