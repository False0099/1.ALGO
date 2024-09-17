小苯有一个长度为 $n$ 的排列 $p$。他很想知道这个排列中有多少个逆序对满足互素。  
  
形式化的，有多少个满足 $(i < j)$ 且 $($$a_i > a_j$$)$ 且 $gcd(a_i, a_j) = 1$ 的 $(i, j)$ 对。

## 输入：
输入包含两行。  
第一行一个正整数 $n(1 \leq n \leq 2\times 10^5)$。表示排列的长度  
第二行 $n$ 个正整数 $p_i (1 \leq p_i \leq n)$ 表示排列 $p$，保证 $1$ 到 $n$ 的每个正整数出现且恰好仅出现一次。

## 输出：
输出包含一行一个整数，表示排列 $p$ 的互素逆序对个数。

## 题解
本题我们首先考虑两个子问题：
1. 怎么求出我们每一个元素对应的满足 $gcd(i,a)=1$ 的 i，
2. 怎么求出我们一端固定为 $i$ 的逆序对。

这里，我们的思路是：通过我们的 dp 来解决我们的第一个问题：

我们设 $dp[i]$ 表示，所有的 gcd 可以是  $i$ 的倍数的数字组成的数组，假设我们已经有了这个数组，那么我们只需要从小到大进行容斥，$dp[i]=dp[i]-dp[2*i]-dp[3*i]-\dots$
就可以得到我们的答案。

接着我们考虑怎么得到我们的一开始的答案，这里，我们考虑枚举我们的 i，然后对所有能够除尽 $i$ 的数字组成的对数，就可以用组合数公式计算得到。

那么如果我们考虑到我们的第二个问题呢？我们不妨把我们的第一步中的组合数公式，转换为我们的这个数对我们的答案的贡献。

但是，如果我们直接暴力计算，我们是会超市的，我们考虑下面的优化：
1. 我们考虑每一次计算我们树状数组的的时候，开的空间是我们的 $\frac{n}{i}$，这样可以让我们开树状数组的复杂度也做到 $n\log n$,否则我们的时间复杂度依然是 $n^2$（重要优化，不加不能过）
2. 我们考虑对于每一个 i，只枚举到 $\frac{n}{2}$,因为一旦超过这个数，我们的 dp 一定是 0（小优化，可有可无）

```cpp
#include <bits/stdc++.h>
using namespace std;
class BIT {
public:
    BIT(int size) : size_(size), tree_(size + 1, 0) {}
 
    void update(int index, int delta) {
        for (int i = index + 1; i <= size_; i += (i & -i)) {
            tree_[i] += delta;
        }
    }
 
    int query(int index) {
        int sum = 0;
        for (int i = index + 1; i > 0; i -= (i & -i)) {
            sum += tree_[i];
        }
        return sum;
    }
 
    int queryRange(int left, int right) {
        return query(right) - query(left - 1);
    }
 
private:
    int size_;
    vector<int> tree_;
};
const int N=2e5+10;
vector<int> factors[N];
int n;
void init(){
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j+=i){
			factors[j].push_back(i);	
		} 
	}
}
vector<int> g[N];
int main(){
	cin>>n;
	init();
	//vector<int> a(n);
	
	for(int i=0;i<n;i++){
		int t;
		cin>>t;
		for(auto u:factors[t]){
			g[u].push_back(t);
		}
	}
	vector<int> dp(n+1,0);
	
	for(int i=1;i<=n;i++){
		BIT b(n+1);
		for(int j=g[i].size()-1;j>=0;j--){
			b.update(g[i][j],1);
			dp[i]+=b.query(g[i][j]-1);
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=2;j*i<=n;j++){
			dp[i]-=dp[i*j];
		}
	}
	cout<<dp[1]<<endl;
} 
```