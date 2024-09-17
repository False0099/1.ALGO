# Traps

## 题面翻译

这里有 $n$ 个陷阱，你需要按照给出的顺序穿过这些陷阱，每个陷阱将会对你造成 $a_i$ 的伤害

你有至多 $k$ 次机会跳过这些陷阱，可以避免你所跳过的陷阱给你造成的伤害，不过接下来的所有陷阱都会给你多造成 $1$ 点伤害

跳过陷阱所造成的额外伤害会叠加，如果你当前已经跳过了 $3$ 个陷阱，接下来的陷阱给你造成的伤害将会是 $a_i +3$

现在需要你求出受到的最小伤害

## 题目描述

There are $ n $ traps numbered from $ 1 $ to $ n $ . You will go through them one by one in order. The $ i $ -th trap deals $ a_i $ base damage to you.

Instead of going through a trap, you can jump it over. You can jump over no more than $ k $ traps. If you jump over a trap, it does not deal any damage to you. But there is an additional rule: if you jump over a trap, all next traps damages increase by $ 1 $ (this is a bonus damage).

Note that if you jump over a trap, you don't get any damage (neither base damage nor bonus damage). Also, the bonus damage stacks so, for example, if you go through a trap $ i $ with base damage $ a_i $ , and you have already jumped over $ 3 $ traps, you get $ (a_i + 3) $ damage.

You have to find the minimal damage that it is possible to get if you are allowed to jump over no more than $ k $ traps.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. Description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 1 \le k \le n $ ) — the number of traps and the number of jump overs that you are allowed to make.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — base damage values of all traps.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case output a single integer — the minimal total damage that it is possible to get if you are allowed to jump over no more than $ k $ traps.

## 样例 #1

### 样例输入 #1

```
5
4 4
8 7 1 4
4 1
5 10 11 5
7 5
8 2 5 15 11 2 8
6 3
1 2 3 4 5 6
1 1
7
```

### 样例输出 #1

```
0
21
9
6
0
```

## 提示

In the first test case it is allowed to jump over all traps and take $ 0 $ damage.

In the second test case there are $ 5 $ ways to jump over some traps:

1. Do not jump over any trap. Total damage: $ 5 + 10 + 11 + 5 = 31 $ .
2. Jump over the $ 1 $ -st trap. Total damage: $ \underline{0} + (10 + 1) + (11 + 1) + (5 + 1) = 29 $ .
3. Jump over the $ 2 $ -nd trap. Total damage: $ 5 + \underline{0} + (11 + 1) + (5 + 1) = 23 $ .
4. Jump over the $ 3 $ -rd trap. Total damage: $ 5 + 10 + \underline{0} + (5 + 1) = 21 $ .
5. Jump over the $ 4 $ -th trap. Total damage: $ 5 + 10 + 11 + \underline{0} = 26 $ .

To get minimal damage it is needed to jump over the $ 3 $ -rd trap, so the answer is $ 21 $ .

In the third test case it is optimal to jump over the traps $ 1 $ , $ 3 $ , $ 4 $ , $ 5 $ , $ 7 $ :

Total damage: $ 0 + (2 + 1) + 0 + 0 + 0 + (2 + 4) + 0 = 9 $ .

## 题解
本题我们考虑人类直觉，我们的直觉是，我们计算我们每一次的初始的“实际”贡献是多少，我们就有：我们的实际贡献是我们的：这一个点的总价值，减去我们这一个地方之后的元素之和是多少。

于是，我们就可以通过我们的优先队列来进行我们的处理，但是，我们这样做**没有考虑，如果我们的后面的点被删除了的情况**，这一个情况下，我们的这一个部分的贡献就是 $\dfrac{k\times(k-1)}{2}$。我们要删除掉被我们的多加的这一部分，于是，我们就可以有下面的代码：

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
void solve(){
	int n,k;
	cin>>n>>k;
	int tmp=k;
	vector<int> a(n);
	int sum=0;
	priority_queue<int> heap; 
	for(int i=0;i<n;i++){
		cin>>a[i];
		sum+=a[i];
		heap.push(a[i]-(n-1-i));
	}
	while(tmp--){
		auto u=heap.top();
		heap.pop();
		sum-=u;
	}
	sum-=(k)*(k-1)/2;
	cout<<sum<<endl;
	
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}
```