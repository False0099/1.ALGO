# Sets and Union

## 题面翻译

给定 $n$ 个数字集合 $S$，第 $i$ 个集合为 $S_i$。

求最大的非负整数 $h$，使得能从 $S$ 选择一个大小为 $m$ 的子集 $T$，满足 $|\bigcup_{i=1}^{m}T_i|=h$，并使得： 
$$\bigcup_{i=1}^{n}S_i\neq\bigcup_{i=1}^{m}T_i$$

$t$ 组数据，$1\leq t\leq 100$，$1\leq n \leq 50$，$\forall i\in [1,n]$，$1\leq|S_i|\leq50$。$\forall i\in [1,n]$，$\forall j\in [1,|S_i|]$，$1\leq S_{i, j} \leq 50 $。

## 题目描述

You have $ n $ sets of integers $ S_{1}, S_{2}, \ldots, S_{n} $ . We call a set $ S $ attainable, if it is possible to choose some (possibly, none) of the sets $ S_{1}, S_{2}, \ldots, S_{n} $ so that $ S $ is equal to their union $ ^{\dagger} $ . If you choose none of $ S_{1}, S_{2}, \ldots, S_{n} $ , their union is an empty set.

Find the maximum number of elements in an attainable $ S $ such that $ S \neq S_{1} \cup S_{2} \cup \ldots \cup S_{n} $ .

 $ ^{\dagger} $ The union of sets $ A_1, A_2, \ldots, A_k $ is defined as the set of elements present in at least one of these sets. It is denoted by $ A_1 \cup A_2 \cup \ldots \cup A_k $ . For example, $ \{2, 4, 6\} \cup \{2, 3\} \cup \{3, 6, 7\} = \{2, 3, 4, 6, 7\} $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 100 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 50 $ ).

The following $ n $ lines describe the sets $ S_1, S_2, \ldots, S_n $ . The $ i $ -th of these lines contains an integer $ k_{i} $ ( $ 1 \le k_{i} \le 50 $ ) — the number of elements in $ S_{i} $ , followed by $ k_{i} $ integers $ s_{i, 1}, s_{i, 2}, \ldots, s_{i, k_{i}} $ ( $ 1 \le s_{i, 1} < s_{i, 2} < \ldots < s_{i, k_{i}} \le 50 $ ) — the elements of $ S_{i} $ .

## 输出格式

For each test case, print a single integer — the maximum number of elements in an attainable $ S $ such that $ S \neq S_{1} \cup S_{2} \cup \ldots \cup S_{n} $ .

## 样例 #1

### 样例输入 #1

```
4
3
3 1 2 3
2 4 5
2 3 4
4
4 1 2 3 4
3 2 5 6
3 3 5 6
3 4 5 6
5
1 1
3 3 6 10
1 9
2 1 3
3 5 8 9
1
2 4 28
```

### 样例输出 #1

```
4
5
6
0
```

## 提示

In the first test case, $ S = S_{1} \cup S_{3} = \{1, 2, 3, 4\} $ is the largest attainable set not equal to $ S_1 \cup S_2 \cup S_3 = \{1, 2, 3, 4, 5\} $ .

In the second test case, we can pick $ S = S_{2} \cup S_{3} \cup S_{4} = \{2, 3, 4, 5, 6\} $ .

In the third test case, we can pick $ S = S_{2} \cup S_{5} = S_{2} \cup S_{3} \cup S_{5} = \{3, 5, 6, 8, 9, 10\} $ .

In the fourth test case, the only attainable set is $ S = \varnothing $ .

## 题解
我们考虑枚举我们选择拿一些集合不方便，这样进行操作的话，我们可能会有：我们的枚举是 $o(2^n)$，显然不能够通过本题。

于是我们考虑其他的方法，我们考虑暴力枚举我们的每一个元素是否在我们的最终集合中。为了使得选出的集合的并集不是所有集合的并集，我们只要让其中至少一个数不在里面即可。枚举 S 中的每一个数，每次求出**不包含这个元素的集合个数**，这些数的最大值就是答案。

```
#include<bits/stdc++.h>
using namespace std;
namespace _wrk{;
set<int>p[100];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		set<int>s;
		for(int i=1;i<=60;i++){
			p[i].clear();
		}
		for(int i=1;i<=n;i++){
			int k;
			cin>>k;
			while(k--){
				int a;
				cin>>a;
				s.insert(a);
				p[i].insert(a);
			}
		}
		int ans=0;
		for(auto x:s){
			set<int>pp;
			for(int i=1;i<=n;i++){
				if(p[i].find(x)==p[i].end()){
					for(auto y:p[i]){
						pp.insert(y); 
					}
				}
			}
			ans=max<int>(ans,pp.size());
		}
		cout<<ans<<endl;
	}
	return 0;
}
}
signed main(){
	   return _wrk::main();
}
```