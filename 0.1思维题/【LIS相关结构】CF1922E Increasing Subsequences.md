Let's recall that an increasing subsequence of the array $a$ is a sequence that can be obtained from it by removing some elements without changing the order of the remaining elements, and the remaining elements are strictly increasing (i. e $a_{b_1} \lt; a_{b_2} \lt; \dots \lt; a_{b_k}$ and $b_1 \lt; b_2 \lt; \dots \lt; b_k$). Note that an empty subsequence is also increasing.

You are given a positive integer $X$. Your task is to find an array of integers of length **at most $200$**, such that it has exactly $X$ increasing subsequences, or report that there is no such array. If there are several answers, you can print any of them.

If two subsequences consist of the same elements, but correspond to different positions in the array, they are considered different (for example, the array $[2, 2]$ has two different subsequences equal to $[2]$).

**Input**

The first line contains a single integer $t$ ($1 \le t \le 1000$) — the number of test cases.

The only line of each test case contains a single integer $X$ ($2 \le X \le 10^{18}$).

**Output**

For each query, print the answer to it. If it is impossible to find the required array, print \-1 on the first line. Otherwise, print a positive integer $n$ on the first line — the length of the array. On the second line, print $n$ integers — the required array itself. If there are several answers, you can print any of them. All elements of the array should be in the range $[-10^9; 10^9]$.

## 样例：
```
4
2
5
13
37

```

```
1
0
3
0 1 0
5
2 2 3 4 2
7
-1 -1 0 0 2 3 -1
```

## 题解
我们考虑最朴素的**特殊结构**，我们一个长度为 $n$ 的上升子序列，我们能够得到的我们的最终长度就是我们的 $2^{n}$,但是，如果我们只是朴素构造的话，我们最后的长度是：$o(\log^2{n})$,显然不能够通过。

这个时候，我们考虑，能不能对我们的**特殊结构进行优化！**。发现是可以的，我们假设我们构造的原来的最长上升子序列长度最长为 $d$,并且我们两个数之间的间隔为 $u$,那么我们如果想要构造一个长度为 $d-1$ 的，那么我们只需要在我们的数字后面添加一个长度比倒数第二个元素还要小，但是比倒数第三个元素还要大，放在我们的后方，即可。例如，我们原本为 `1 4 7 9`,我们这个时候要构造长度为 3 的，我们就可以考虑：`1 4 0 7 9`,这个时候，我们如果还想要构造长度为 1 的，那么我们就 `1 4 0 7 9 -1` 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
void solve(){
	long long x;
	cin>>x;
	vector<int> dq;
	int l=114514;
	int r=114514;
	long long tmp=x;
	int digit=0;
	while(tmp){
		digit++;
		tmp/=2;
	}
	dq.push_back(114514);
	for(int i=digit-2;i>=0;i--){
		if(i==digit-2){
			long long u=(x&(1ll<<i));
			if(u==0){
				continue;
			}else{
				dq.push_back(--l);
			}
		}else{
			long long u=(x&(1ll<<i));
			if(u==0){
				dq.push_back(++r);
			}else{
				dq.push_back(++r);
				dq.push_back(--l);
			}
		}
		//cout<<(1ll<<i)<<endl;
		
	}
	cout<<dq.size()<<'\n';
	for(auto u:dq){
		cout<<u<<" ";
	}
	puts("");
}
int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
} 
```