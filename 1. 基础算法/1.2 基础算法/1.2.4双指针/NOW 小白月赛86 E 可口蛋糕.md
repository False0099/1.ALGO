## 题目
小蓝制作了 $n$ 个蛋糕并将其从左往右排成一行，其中第 $i$ 个蛋糕的饱腹度为 $w_i$ 其可口值为 $d_i$。  
  
由于手法过于生疏，尽管每个蛋糕的饱腹度必然为正数，但是可能存在蛋糕的可口值为负数！  
  
作为可口蛋糕大赛的评委，小灰灰需要吃掉一段连续的蛋糕，使得蛋糕的饱腹度之和至少为 $W$。  
  
而小蓝的得分就是小灰灰吃掉蛋糕所对应的可口值之和，她想知道在小灰灰帮助她的情况下，她的最大可能得分是多少。

## 输入：
第一行两个空格分隔的整数分别代表 $n$ 和 $W$。  
  
接下来一行 $n$ 个空格分隔的整数分别代表：$w_1, w_2, ..., w_n$。  
  
再接下来一行 $n$ 个空格分隔的整数分别代表：$d_1,d_2,...,d_n$。  
  
保证：  
$1 \le n \le 10^6$  
  

$1 \le W,w_i\le10^9$

  

$0\le |d_i|\le10^9$  

  

$W \le \sum_{i=1}^n w_i$

## 输出：
输出一行一个整数代表答案。

## 题解
我们这一题可以考虑先保证一个性质一定可以满足的情况下，再去求我们的另一个性质。首先，我们可以把我们的求和转换为我们 sum 数组上找点。于是，我们原本的问题就转换为求 $I,j$ 满足我们的 $s[r]-s[l]\geq w$,的 $r,l$。
这里，我们的思路是固定我们的一个左端点 $l$，然后我们要去求我们的 $r$ 满足我们的 $w+s[l]\leq s[r]$,这里，我们就可以通过我们的二分法去维护。也就是我们可以直接采用一个 lowerbound 即可。

找到了我们的区间右端点的最小值后，我们可以考虑把我们的原来的区间求和问题，变成我们的前缀和相减的问题。于是，我们就可以考虑维护一个后缀的最大值：`mx[pos]`,表示我们在这个点之后的所有数据的一个最大值，然后我们直接相减即可得到我们的答案。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
long long n,W,w[N],d[N]; 
int main(){
	ios::sync with stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>w;
	for(int i=1;i<=n;i++){
		cin>>w[i];
		sumw[i]=sumw[i-1]+w[i];
	}
	for(int i=1;i<=n;i++){
		cin>>d[i];
		sumd[i]=sumd[i-1]+d[i];
	}
	mx[n+1]=-1e15;
	for(int i=n;i>=1;i--){
		mx[i]=max(mx[i+1],sumd[i]);
	}
	long long ans=-1e15;
	for(int i=1;i<=n;i++){
		int pos=lower_bound(sumw+1,sumw+1+n,sumw[i-1]+w)-sumw;
		ans=max(ans,mx[pos]-sumd[i-1]);
	}
	cout<<ans<<endl;
	return 0;
}
```